#include <stdio.h>

int main(int argc, char *argv[]){
  int i;
  for(i=0;i<10;i++)
    printf("Hi from processor MIPS!\n");

    int *test;
    test = (int*) 5242880;
    printf("Mutex: %d\n",*test); // aberto, leitura e lock
    printf("Mutex: %d\n",*test); // fechado
    *test = 0;                   // libera
    printf("%d\n",*test);        // aberto, leitura e lock
    printf("%d\n",*test);        // fechado

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}
