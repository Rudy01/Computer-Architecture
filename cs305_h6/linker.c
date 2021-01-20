#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define HEADERS         1
#define NO_HEADERS      0

typedef struct nament {
  char   name[26];
  int    addr;
  struct nament *next;
} SYMTABENTRY;

void  add_symbol(char * symbol, int line_number);
void  generate_code(int);
void  print_first_pass(int);
void  append_table(void);
void  dump_table(void);
int get_sym_val(char*);

SYMTABENTRY *symtab = NULL;
FILE  *p1, *p2;
char  cstr_12[13];

int main(int argc, char *argv[]) {
  int  i, start, pc_offset = 0, pc = 0;
  int  linum = 0, object_file = 0, dump_tab = 0;
  int  line_number, new_pc;
  char instruction[18];
  char symbol[26];
  
  if(argc > 1 && (strcmp(argv[1], "-s") == 0))
    dump_tab = linum = 1;
  if(argc > 1 && (strcmp(argv[1], "-o") == 0))
    object_file = 1;
  
  if(dump_tab == 1 | object_file == 1)
    start=2;
  else
    start = 1; 
  
  p1 = fopen("/tmp/passone", "w+");
  unlink("/tmp/passone");
  
  for(i = start; i < argc; ++i) {
    if((p2 = fopen(argv[i], "r")) == NULL) {
      printf("ERROR: cannot open file %s\n", argv[i]);
      exit(6);
    }
    while(fscanf(p2,"%d %s", &pc, instruction) != EOF) {
      if(pc == 4096)
	break;
      new_pc = pc + pc_offset;
      symbol[0] = '\0';
      if(instruction[0] == 'U') {
	fscanf(p2, "%s", symbol);
      }
      
      fprintf(p1, "  %d  %s  %s\n", new_pc, instruction, symbol);
    }
    while(fscanf(p2,"%s %d",symbol, &line_number) != EOF){
      add_symbol(symbol, line_number+pc_offset);
    }

    pc_offset = new_pc + 1;
    fclose(p2);
  } 
}

int get_sym_val(char *symbol) {
  int i, j;
  struct nament *element, *list;
  
  for(list = symtab; list != (struct nament *)0; list = list->next) {
    if(strcmp(list->name, symbol) == 0) {
      return(list->addr);
    }
  }
  return -1;
}

void add_symbol( char *symbol, int line_number) {
  SYMTABENTRY *newSym;
  
  if(symtab == NULL) {
    symtab = newSym;
    newSym->next = NULL;
  } else {
    newSym->next = symtab;
    symtab = newSym;
  }
  
  strcpy(newSym->name, symbol);
  newSym->addr = line_number;
}

void generate_code(int linum) {
  char linbuf[10] = {'0'};
  char instruction[18] = {'0'};
  int  line_number = 0;
  int  pc = 0, mask = 0, sym_val = 0, old_pc = 0, diff = 0;
  char symbol[26] = {'0'};

  rewind(p1);

  sprintf(linbuf,"%5d:  ", line_number);

  while (fscanf(p1,"%d %s", &pc, instruction) != EOF) {
    if ((diff = pc - old_pc ) > 1) {
      for (int j=1; j<diff; j++) {
        sprintf(linbuf,"%5d:  ", line_number++);
        printf("%s1111111111111111\n",(linum ? linbuf: "\0"));
      }
    }
    sprintf(linbuf,"%5d:  ", line_number++);
    old_pc = pc;

    if (instruction[0] == 'U') {
      fscanf(p1, "%s", symbol);
      if ((sym_val = get_sym_val(symbol)) == -1) {
        fprintf(stderr, "no symbol in symbol table: %s\n", symbol);
        exit(27);
      }

      for (int i=0; i<12; i++) {
        cstr_12[i] = '0';
      }
      cstr_12[12] = '\0';

      mask = 2048;
      for (int i=0; i<12; i++) {
        if (sym_val & mask) {
          cstr_12[i] = '1';
        }
        mask >>= 1;
      }
      for (int i=0; i<12; i++) {
        instruction[i+5] = cstr_12[i];
      }
      printf("%s%s\n", (linum ? linbuf: "\0"), &instruction[1]);
    } else {
      printf("%s%s\n", (linum ? linbuf: "\0"), instruction);
    }
  }
  fclose(p1);
}

void print_first_pass(int headers) {
  char inbuf[81];

  if (headers == HEADERS) {
    printf("\n  FIRST PASS \n");
    rewind(p1);
    while (fgets(inbuf, 80, p1) != NULL) {
      printf("   %s", inbuf);
    }
    printf("\n  SECOND PASS \n");
  } else {
    rewind(p1);
    while (fgets(inbuf, 80, p1) != NULL) {
      printf("   %s", inbuf);
    }
  }
}

void append_table(void) {
  printf("  %d %s\n", 4096, "x");
  for (struct nament *list = symtab; list != NULL; list = list->next) {
    printf("    %-25s %4d\n",list->name, list->addr);
  }
}

void dump_table(void) {
  FILE *fd;
  fd = popen("sort", "w");
  printf("\n  SYMBOL TABLE \n");
  printf("***********************************************\n");
  for (struct nament *list = symtab; list != NULL; list = list->next) {
    fprintf(fd,"%-25s %4d\n",list->name, list->addr);
  }
  fclose(fd);
  wait(NULL);
  printf("***********************************************\n");
}
