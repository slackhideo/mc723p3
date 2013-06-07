#include <stdio.h>

volatile int proc = 0;
volatile int *mutex=(int*)5242884;


int main(int argc, char *argv[]){
    int proc_id = 0;
    int i;

    while(*mutex);

    proc_id=++proc;
    printf("Hi from processor %d!\n", proc_id);

    *mutex=0;    

    exit(0); // To avoid cross-compiler exit routine
    return 0; // Never executed, just for compatibility
}
