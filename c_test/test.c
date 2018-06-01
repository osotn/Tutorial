#include <stdio.h>
#include <stdlib.h>


int main(int arg, char **argv)
{
  char str[] = "vn0";
  char str1[] = "vn3";
  char str2[] = "0";
  char str3[] = "3";
  char str4[] = "vn0fdfdf";
  char str5[] = "vn3fdfd";
  char str6[] = "ddfdfd";
  long ret;
  char *ptr;


  ret = strtol(str1, &ptr, 10);
  printf(" %s => %ld +  %s\n", str1, ret, ptr);

  ret = strtol(str, &ptr, 10);
  printf(" %s => %ld +  %s\n", str, ret, ptr);   
  
  ret = strtol(str2, &ptr, 10);
  printf(" %s => %ld +  %s\n", str2, ret, ptr); 
  
  ret = strtol(str3, &ptr, 10);
  printf(" %s => %ld +  %s\n", str3, ret, ptr); 

  ret = strtol(str4, &ptr, 10);
  printf(" %s => %ld +  %s\n", str4, ret, ptr);

  ret = strtol(str5, &ptr, 10);
  printf(" %s => %ld +  %s\n", str5, ret, ptr);  return 0;

  ret = strtol(str6, &ptr, 10);
  printf(" %s => %ld +  %s\n", str6, ret, ptr);} 
