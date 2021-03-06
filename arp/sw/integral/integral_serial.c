/* 
 * @file     serial_killer.c
 * @author   Victor Accarini D'Lima (105753)
 * 
 * @version  1.1
 *
 * @brief    Implements a Trapezium Rule Approximate Numerical Integration
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

/// mutex macros
#define LOCK while(*lockd)
#define UNLOCK *lockd=0
#define PROC_NUM 8


typedef struct timeval time;

// processor identification
volatile int proc_id = 0;

// lock address
volatile int *lockd = (int*) 5242884;

/// function to be evaluated
float f(float x){
    return log10((double)x);
}

float f2(float x) {
    float *arg_addr = (float*) 5242888;
    *arg_addr = x;

    float *res_addr = (float*) 5242896;

    return *res_addr;
}

/// trapezium rule appoximate numerical integration
float trap(float left_endpt, float right_endpt, int trap_count, float base_len){
  float estimate = 0;
  float x = 0;
  int i;
  
  estimate = (f(left_endpt) + f(right_endpt))/2.0;
  for(i = 1; i < trap_count; i++){
    x = left_endpt + i*base_len;
    estimate += f(x);
  }
  estimate = estimate*base_len;
  
  return estimate;
}

/// serial main
int main() {
  int n;
  float h, a, b, t, total;

  LOCK;
  proc_id++;
  UNLOCK;

  LOCK;
  if (proc_id == 1){
  printf("Digite o numero de subintervalos:\n");
  /// interval count
  scanf("%d", &n);

  printf("Digite o inicio e o final do intervalo:\n");
  /// interval start
  scanf("%f", &a);
  /// interval end
  scanf("%f", &b);
  
  /// interval size
  h=(b-a)/n;
  total = trap(a,b,n,h);
  
  printf("A estimativa foi: %.15e\n",total);
  }
  proc_id++;
  
  return 0;
}
