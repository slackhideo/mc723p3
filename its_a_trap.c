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
#include <pthread.h>

//SHARED VARIABLES
double total_int = 0.0, a = 0.0, b = 3.0, h = 0.0;
long int thread_count;
int n = 1000;
pthread_mutex_t trava;

struct thread_info {    /* Used as argument */
	pthread_t thread_id;  /* ID returned by pthread_create() */
	int thread_num;       /* Application-defined thread # */
};

double f(double x){
	return log10(x);
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
	printf("%f\n",estimate);
	return estimate;

} /* Trap */

void *thread_start(void* arg){
	double local_n, local_int;
	double local_a= 0.0, local_b= 0.0;
	struct thread_info *tinfo = (struct thread_info *) arg;

	local_n = n/thread_count;
	if (tinfo->thread_num < n%thread_count)
		local_n++;
	local_a = a+tinfo->thread_num*local_n*h;
	local_b = local_a+local_n*h;
	local_int = Trap(local_a,local_b,local_n,h);

	pthread_mutex_lock(&trava);	
	total_int += local_int;
	pthread_mutex_unlock(&trava);
}

int main(int argc, char* argv[]) {
	int rank, s;
	struct timeval start, end;
	struct thread_info *tinfo;
	

	
	thread_count = strtol(argv[1], NULL, 10); /* Numero de threads a serem iniciadas */
	tinfo = calloc(thread_count, sizeof(struct thread_info));
	
	printf("Digite o numero de subintervalos:\n");
	scanf("%d", &n);
	printf("Digite o inicio e o final do intervalo:\n");
	scanf("%lf", &a);
	scanf("%lf", &b);
	
	gettimeofday(&start, NULL);
	
	h=(b-a)/n;
	
	pthread_mutex_init(&trava, NULL);
	
	//Criando as threads
	for (rank = 0; rank < thread_count; rank++) {
			tinfo[rank].thread_num = rank;
			s = pthread_create(&tinfo[rank].thread_id, NULL, thread_start, &tinfo[rank]);
	}
	
	for (rank = 0; rank < thread_count; rank++){
		pthread_join(tinfo[rank].thread_id, NULL);
	}
	
	pthread_mutex_destroy(&trava);
	//Tempo
	gettimeofday(&end, NULL);
	
	double totalt = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

	printf("A estimativa foi: %.15e\n",total_int);
	printf("Tempo: %lf\n", totalt);

	//free(tinfo);
	return 0;
} /* main */
