#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "AdministradorProcesos.h"
#include "Monitor.h"

#define MAX_THREAD_COUNT 1000
int thread_count=0;
pthread_attr_t attr [MAX_THREAD_COUNT];
pthread_t esperarTerminarCliente[MAX_THREAD_COUNT];
long pids [MAX_THREAD_COUNT];

void * notificarTerminacionCliente( void * param){

		
		 long * parametros=param;
		 int cpid=(int)*parametros;
		 int status;	

		 pid_t w;
		 fprintf(stderr,"Waiting in the father %ld for child %d\n",(long) getpid(),cpid);
		 w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
		// printf("\nSenal enviada a %d\n",cpid);
		 eliminarProceso(cpid); //kill		 
		 fprintf(stderr,"\nProceso cliente finalizado\n");
		 
		 /// PONER EN INFO PROCES TERMINADO			 */
}

int iniciarClienteSimulado(int perc_cpu,int max_time,int N){
//void* iniciarClienteSimulado(void * param){
	
	pid_t cpid;	
	char *argv[5];
	char tmp1[20];
	char tmp2[20];
	char tmp3[20];
	sprintf( tmp1, "%d", perc_cpu );
	sprintf( tmp2, "%d", max_time );
	sprintf( tmp3, "%d", N );	
	printf("\n%s %s %s \n",tmp1,tmp2,tmp3 );
	//argv[0]="exec";
	argv[1]=tmp1;
	argv[2]=tmp2;
	argv[3]=tmp3;   
	 cpid = fork();
	 if (cpid == -1) {
		 perror("fork");
		 exit(EXIT_FAILURE);
	 }
	 
	 if (cpid == 0) {            //Code executed by child 
		 printf("Inicializando Proceso Cliente Simulado con PID= %ld\n", (long) getpid());
	     argv[0] ="recursos/procesoCliente"; argv[4]=0;
		 execv(argv[0], argv);
		// sleep(10000);
		 printf("Inside original child\n");
		 exit(EXIT_SUCCESS);
		 
	 } else {		
	 	iniciarMonitoreo(cpid);	 	
 		pids[thread_count]=(long)cpid;
	 	pthread_create(&esperarTerminarCliente[thread_count],&attr[thread_count],notificarTerminacionCliente,(void*)&pids[thread_count]);
	 	thread_count++;
	 	 // float carga=infoCpuLoad(cpid);
	   
		
	 }
		

	
	 //long * parametros=param;
	 //printf("CPU BURST %ld\n", *parametros);
}

int estadoProcesoCliente(int pid){
	return 0;
} 

int enviarSenialProceso(){
	return 0;
}

