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
#include <time.h>
#include <math.h>

/// function to be evaluated
double f(double x){
  return log10(x);
}

/// trapezium rule appoximate numerical integration
double trap(double left_endpt, double right_endpt, int trap_count, double base_len){
  double estimate = 0;
  double x = 0;
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
  double h, a, b, t, total;
  struct timeval start, end;
  
  printf("Digite o numero de subintervalos:\n");
  /// interval count
  scanf("%d", &n);

  printf("Digite o inicio e o final do intervalo:\n");
  /// interval start
  scanf("%lf", &a);
  /// interval end
  scanf("%lf", &b);

  /// timer init
  gettimeofday(&start, NULL);

  /// interval size
  h=(b-a)/n;
  total = trap(a,b,n,h);
  
  /// timer finish
  gettimeofday(&end, NULL);
  t = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
  
  printf("A estimativa foi: %.15e\n",total);
  printf("Tempo: %lf\n", t);
  
  return 0;
}
