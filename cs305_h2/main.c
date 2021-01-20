#include "main.h"

int main(int argc, char **argv) {
  FLOAT_UN float_32_s1, float_32_s2, float_32_rslt;
  float the_hardware_result;
  int   mant_s1, mant_s2, mant_res, exp_s1, exp_s2;
  int   shift_count;

  printf("************************************************************************\n");
  printf("This program will emulate the addition of two IEEE 754 floating point numbers\n");
  printf("Please enter two positive floating point values each with:\n");
  printf("- no more than 6 significant digits\n");
  printf("- a value between + 10**37 and 10**-37\n");
  printf("Enter Float 1: ");
  scanf("%g", &float_32_s1.floating_value_in_32_bits);

  if(float_32_s1.floating_value_in_32_bits >= 10e37 || float_32_s1.floating_value_in_32_bits <= -10e37) {
    printf("ERROR: Float 1 is out of range\n");
    return 1;
  }

  if(float_32_s1.floating_value_in_32_bits < 0) {
    printf("ERROR: Float 1 cannot be nagative\n");
    return 1;
  }
  
  printf("Enter Float 2: ");
  scanf("%g", &float_32_s2.floating_value_in_32_bits);

  if(float_32_s2.floating_value_in_32_bits >= 10e37 || float_32_s2.floating_value_in_32_bits <= -10e37) {
    printf("ERROR: Floae 2 is out of range\n");
    return 1;
  }
  
  if(float_32_s2.floating_value_in_32_bits < 0){
    printf("ERROR: Float 2 cannot be negative\n");
    return 1;
  }
  
  char *t1 = "Original pattern of Float 1: ";
  print_bits(float_32_s1, t1);
  char *t2 = "Original pattern pf Float 2: ";
  print_bits(float_32_s1, t2);
  
  the_hardware_result = float_32_s1.floating_value_in_32_bits + float_32_s2.floating_value_in_32_bits;
  
  mant_s1 = float_32_s1.f_bits.mantissa;
  mant_s2 = float_32_s2.f_bits.mantissa;
  exp_s1  = float_32_s1.f_bits.exponent;
  exp_s2  = float_32_s2.f_bits.exponent;
  
  if(float_32_s1.floating_value_in_32_bits > float_32_s2.floating_value_in_32_bits) {
    shift_count = exp_s1 - exp_s2;
    if(shift_count >= 23)
      mant_s2 = 0;
    else
      mant_s2 = mant_s2 >> shift_count;
    
    mant_res = mant_s1 + mant_s2;
    mant_res = mant_res - 8388608;
    float_32_rslt.f_bits.mantissa = mant_res;
    float_32_rslt.f_bits.exponent = exp_s1;
    float_32_rslt.f_bits.sign = 0;
  }
  
  if(float_32_s1.floating_value_in_32_bits < float_32_s2.floating_value_in_32_bits) {
    shift_count = exp_s2 - exp_s1;
    if(shift_count >= 23)
      mant_s1 = 0;
    else
      mant_s1 = mant_s1 >> shift_count;
    
    mant_res = mant_s1 + mant_s2;
    mant_res = mant_res - 8388608;
    float_32_rslt.f_bits.mantissa = mant_res;
    float_32_rslt.f_bits.exponent = exp_s2;
    float_32_rslt.f_bits.sign = 0;
  }

  if(float_32_s1.floating_value_in_32_bits == float_32_s2.floating_value_in_32_bits)
    float_32_rslt.floating_value_in_32_bits = float_32_s1.floating_value_in_32_bits * 2;

  char *t3 = "Bit pattern of result: ";
  print_bits(float_32_rslt, t3);
  
  printf("HARDWARE FLOATING RESULT FROM PRINTF ==>>> %.2f\n", the_hardware_result);
  printf("EMULATED FLOATING RESULT FROM PRINTF ==>>> %.2f\n", float_32_rslt.floating_value_in_32_bits);
  printf("*********************************************************************************\n");
  return 0;
}
