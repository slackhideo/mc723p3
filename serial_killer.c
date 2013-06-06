/* 
 * Victor Accarini D'Lima RA 105753
 * 
 * Variáveis
 * a -> valor inicial de x
 * b -> valor final de x
 * n -> numero de subintervalos
 * h -> tamanho dos subintervalos
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double f(double x){
	double ret;
	//ret = x*x-(4*x)+5;
	ret = log10(x);
	return ret;
}

double Trap(double left_endpt, double right_endpt, int trap_count, double base_len) {

	double estimate = 0, x = 0;
	int i;
	
	estimate = (f(left_endpt) + f(right_endpt))/2.0;
	for(i=1;i<trap_count;i++) {
		x=left_endpt + i*base_len;
		estimate += f(x);
	}
	estimate = estimate*base_len;

	return estimate;

} /* Trap */

int main(int argc, char* argv[]) {
	double h, a, b, total_int;
	int n;
	struct timeval start, end;
	
	printf("Digite o numero de subintervalos:\n");
	scanf("%d", &n);
	printf("Digite o inicio e o final do intervalo:\n");
	scanf("%lf", &a);
	scanf("%lf", &b);
	
	gettimeofday(&start, NULL);
	
	h=(b-a)/n;

	total_int = Trap(a,b,n,h);
	
	//Tempo
	gettimeofday(&end, NULL);
	
	double totalt = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

	printf("A estimativa foi: %.15e\n",total_int);
	printf("Tempo: %lf\n", totalt);

	//free(tinfo);
	return 0;
} /* main */