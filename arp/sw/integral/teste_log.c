#include <stdio.h>
#include <math.h>

/// mutex macros
#define LOCK while(*lockd)
#define UNLOCK *lockd=0
#define PROC_NUM 3

volatile int *lockd = (int*) 5242884;


int main() {

    LOCK;
 
    float* p = (float*) 5242888;
    *p = 100;
    volatile float* r = (float*) 5242896;
    printf("Log=%f\n", *r);

    *p = 1000;
    printf("Log=%f\n", *r);
    
    *p = 500;
    printf("Log=%f\n", *r);
 
    UNLOCK;
    
    return 0;
}
