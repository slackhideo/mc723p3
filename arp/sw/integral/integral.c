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


/// mutex macros
#define LOCK while(*lockd)
#define UNLOCK *lockd=0
#define PROC_NUM 3


/// volatile variables
volatile int done = 0;
volatile int proc = 0;
volatile int    n = 1000;
volatile double a = 0.0;
volatile double b = 0.0;
volatile double h = 0.0;
volatile double result = 0.0;
volatile int *lockd = (int*) 5242884;


/// function to be evaluated
double f(double x){
  return log10(x);
}


/// trapezium rule appoximate numerical integration
double trap(double a, double b, int n, double h) {
  int i;
  double approx = 0.0;
  double x = 0.0;
 
  /// TODO: hw area calculator!
  approx = (f(a) + f(b))/2.0;
  for(i = 1; i < n; i++) {
    x = a + i*h;
    approx += f(x);
  }
  
  approx = approx*h;
  return approx; 
}


void proc_run(int proc_id){
  int proc_n = 0;
  double proc_a = 0.0;
  double proc_b = 0.0;
  double proc_result = 0.0;
  
  /// this processor intervals number
  proc_n = n/PROC_NUM;
  if(proc_id < n%PROC_NUM)
    proc_n++;

  /// this processor first and last interval points
  proc_a = a + proc_id * proc_n * h;
  proc_b = proc_a + proc_n * h;

  /// DEBUG
  LOCK;
  printf("proc_id: %d\t proc_n: %d\nh: %lf\n",proc_id,proc_n, h);
  printf("proc_a: %lf\t proc_b: %lf\n",proc_a,proc_b);
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
  printf("Processor %d running!\n", proc_id);
  
  if(proc_id == 0){
    /// interval count
    printf("Digite o numero de subintervalos:\n");
    scanf("%d", &n);
    
    /// interval start
    printf("Digite o inicio e o final do intervalo:\n");
    scanf("%lf", &a);
    
    /// interval end
    scanf("%lf", &b);
    
    /// interval size
    h = (b - a)/n;
  }
  UNLOCK;
  
  /// execute
  proc_run(proc_id);

  /// workaround
  if(proc_id == 0){
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