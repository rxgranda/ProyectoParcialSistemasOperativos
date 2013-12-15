#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include <signal.h>
static volatile int flag;

static void sig_handler(int signo)
{
	/*
    if (signo == SIGUSR1){
    	flag=1;
    	printf("SENIAL RECIBIDA PARAR %d\n", getpid() ); 
    	while (flag==1) sleep(500)   	
        
   } else {
   	 printf("SENIAL RECIBIDA CONTINUAR %d\n", getpid() );
   		flag=0;
       
    }*/
   		sigset_t myset;
(void) sigemptyset(&myset);
while (1) {
    (void) printf("I'm running, waiting for a signal...\n");
    (void) sigsuspend(&myset);
}
}

int  main(int argc, char *argv[])
{
	//sleep(10000);
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR1\n");
    if (signal(SIGUSR2, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR2\n");

	printf("\nInicio ejecutador cliente \n");
	int perc_cpu,time_cpu,time_cpu_burst,i,N;
	int max_time,time_io,time_io_burst;
	double diff;
	struct timespec t0,tn;

	if (argc!=4){
		printf("usage porcentaje_cpu[1-100] tiempo_de_ejecucion[Secs] num_iteraciones, argumentos %d %s \n ", argc,argv[0]);
		exit(0);}

		perc_cpu=atoi(argv[1]);
		max_time=atoi(argv[2]);
		N=atoi(argv[3]);
//colocar aqui envio de mensaje de hora inicio

time_cpu=1000*max_time*perc_cpu/100;   //tiempo en milisegundos
time_io=1000*max_time*(100-perc_cpu)/100;

time_cpu_burst=time_cpu/N;
time_io_burst=time_io/N;

printf("Tiempo de cpu burst %d (mseg), Tiempo de IO burst (mseg) %d\n",time_cpu_burst,time_io_burst);

for (i=1;i<=N;i++){
	//while(flag==1){
	//	usleep(5000);
	//}
	clock_gettime(CLOCK_MONOTONIC,  &t0);
	
	diff=0;
	printf("burst CPU\n");
	printf("Esperando\n");
	while(diff<time_cpu_burst)
	{
		clock_gettime(CLOCK_MONOTONIC,  &tn);
		diff= (tn.tv_sec - t0.tv_sec)*1000 + (double) (tn.tv_nsec - t0.tv_nsec) * 1e-6;		    
	}
	printf("burst IO\n");
	usleep((unsigned int)time_io_burst*1000);

}
printf("\nFin cliente");
exit(EXIT_SUCCESS);
return 0;
//colocar aqui envio de mensaje de hora fin

}