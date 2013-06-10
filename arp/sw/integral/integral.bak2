/* 
 * @file     its_a_trap.c
 * @author   Grupo 40 & Victor Accarini D'Lima (105753)
 * 
 * @version  2.0
 *
 * @brief    Implements a Trapezium Rule Approximate Numerical Integration in
 *           a Multi-Processor MIPS simulator
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

/// mutex macros
#define LOCK while(*lockd)
#define UNLOCK *lockd=0
#define PROC_NUM 8
//#define PERIFERICO

typedef struct timeval time;


/// volatile variables
volatile int done = 0;
volatile int proc = 0;
volatile int running_proc = 0;
volatile int   n = 1000;
volatile float a = 0.0;
volatile float b = 0.0;
volatile float h = 0.0;
volatile float result = 0.0;
volatile int *lockd = (int*) 5242884;


/// function to be evaluated

#ifndef PERIFERICO
float f(float x){
    return (float) log10((double)x);
}
#endif


#ifdef PERIFERICO
// requests to the function unit function log10(x)
float f(float x) {
    LOCK;
    float *arg_addr = (float*) 5242888;
    *arg_addr = x;

    float res_local, *res_addr = (float*) 5242896;
    res_local = *res_addr;
    UNLOCK;

    return res_local;
}
#endif


/// trapezium rule appoximate numerical integration
float trap(float l, float r, int n, float h) {
  int i;
  float approx = 0.0;
  float x = 0.0;
 
  /// TODO: hw area calculator!
  approx = (f(l) + f(r))/2.0;
  for(i = 1; i < n; i++) {
    x = l + i*h;
    approx += f(x);
  }
  
  approx = approx*h;
  return approx; 
}


void proc_run(int proc_id){
  int proc_n = 0;
  float proc_a = 0.0;
  float proc_b = 0.0;
  float proc_result = 0.0;
  
  /// this processor intervals number
  proc_n = n/PROC_NUM;
  if(proc_id < n%PROC_NUM)
    proc_n++;

  /// this processor first and last interval points
  proc_a = a + proc_id * proc_n * h;
  proc_b = proc_a + proc_n * h;

  /// DEBUG
  LOCK;
  printf("proc_id: %d\t proc_n: %d proc_a: %f, proc_b: %f\n",proc_id,proc_n, proc_a,proc_b);
  UNLOCK;

  /// approximation
  proc_result = trap(proc_a,proc_b,proc_n,h);

  /// results
  LOCK;
  result += proc_result;
  done++;
  UNLOCK;
}


int main() {
  int self = 0;
  int proc_id = 0;

  LOCK;
  proc_id = proc++;
  running_proc++;
  printf("Processor %d running!\n", proc_id);
  
  if(proc_id == 0){
    /// interval count
    printf("Digite o numero de subintervalos:\n");
    scanf("%d", &n);
    
    /// interval start
    printf("Digite o inicio e o final do intervalo:\n");
    scanf("%f", &a);
    
    /// interval end
    scanf("%f", &b);
    
    /// interval size
    h = (b - a)/n;

    printf("h: %f\n\n", h);

  }
  UNLOCK;
  
  /// execute
  proc_run(proc_id);

  running_proc--;
  
  /// workaround
  if(proc_id == 0){
    // wait all processors to finish
    while (running_proc > 0);

    while(!self){
      LOCK;
      if(done == PROC_NUM){
        printf("A estimativa foi: %e\n", result);
        self = 1;
      }
      UNLOCK;
    }
  }
  
  return 0;
}
