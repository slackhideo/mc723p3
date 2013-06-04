#include <stdio.h>

int main(int argc, char *argv[]){
  int i;
  for(i=0;i<10;i++)
    printf("Hi from processor MIPS!\n");

    int *test;
    test = (int*) 5242880;
    printf("%d\n",*test);
    printf("%d\n",*test);
    *test = 10;
    printf("%d\n",*test);
    printf("%d\n",*test);

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}
