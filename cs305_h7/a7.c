#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void) {
  char    msg_buf[100];
  int     msg_pipe[2];
  
  if(pipe(msg_pipe) == -1) {
    perror("failed in Parent pipe creation:");
    exit(7);
  }
  
  printf("\nThis is the Parent process report:\n");
  pid_t pid  = getpid();
  pid_t ppid = getppid();
  int ruid = getuid();
  int euid = geteuid();
  int rgid = getgid();
  int egid = getegid();
  char priority = getpriority(PRIO_PROCESS, 0);
  
  printf("\nPARENT PROG:  Process ID is:\t\t%d\n", pid);
  printf("PARENT PROC:  Process parent ID is:\t%d\n", ppid);
  printf("PARENT PROC:  Real UID is:\t\t%d\n", ruid);
  printf("PARENT PROC:  Real GID is:\t\t%d\n", rgid);
  printf("PARENT PROC:  Effective UID is:\t\t%d\n", euid);
  printf("PARENT PROC:  Effective GID is:\t\t%d\n", egid);
  printf("PARENT PROC:  Process priority is:\t%d\n", priority);
  
  printf("\nPARENT PROC: will now create child, write pipe, and do a normal termination\n");
  
  sprintf(msg_buf, "This is the pipe message from the parent with PID %d\n", pid);
 
  switch(pid = fork()) {
  case -1:
    printf("Call to fork failed.");
    exit(1);
    
  default:
    printf("\nPARENT PROG: Created child with %d PID\n", pid);
    write(msg_pipe[1], msg_buf, 100);
    exit(0);

  case 0:
    printf("\nThis is the Child process report:\n");
    pid  = getpid();
    ppid = getppid();
    ruid = getuid();
    euid = geteuid();
    rgid = getgid();
    egid = getegid();
    priority = getpriority(PRIO_PROCESS, 0);
    
    printf("\nCHILD PROG:  Process ID is:\t\t%d\n", pid);
    printf("CHILD PROC:  Process child ID is:\t%d\n", ppid);
    printf("CHILD PROC:  Real UID is:\t\t%d\n", ruid);
    printf("CHILD PROC:  Real GID is:\t\t%d\n", egid);
    printf("CHILD PROC:  Effective UID is:\t\t%d\n", euid);
    printf("CHILD PROC:  Effective GID is:\t\t%d\n", egid);
    printf("CHILD PROC:  Process priority is:\t%d\n", priority);
    
    printf("\nCHILD PROG: about to read pipe and report parent message:\n\n");
    
    read(msg_pipe[0], msg_buf, 100);
    printf("CHILD PROC: parent's msg is:\n %s\n\n", msg_buf);
    printf("CHILD PROC: Process parent ID now is:   %d\n", getppid());
    printf("CHILD PROC: ### Goodbye ###\n");
  }
  
  return 0;
}
