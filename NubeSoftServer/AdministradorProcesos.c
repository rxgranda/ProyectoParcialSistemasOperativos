#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "AdministradorProcesos.h"
#include "Monitor.h"

#define MAX_PROC_COUNT 1000


pthread_attr_t attr [MAX_PROC_COUNT];
pthread_t esperarTerminarCliente[MAX_PROC_COUNT];
long pids [MAX_PROC_COUNT];
int process_count=0;

void * notificarTerminacionCliente( void * param){

	long * parametros=param;
	int cpid=(int)*parametros;
	int status;	
	pid_t w;
	//fprintf(stderr,"Waiting in the father %ld for child %d\n",(long) getpid(),cpid);
	w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
	eliminarProceso(cpid); //Eliminar procesos de Monitorer		 
	fprintf(stderr,"\nProceso cliente finalizado\n");	
}

int iniciarClienteSimulado(int perc_cpu,int max_time,int N){

	pid_t cpid;	
	char *argv[5];
	char tmp1[20];
	char tmp2[20];
	char tmp3[20];
	sprintf( tmp1, "%d", perc_cpu );
	sprintf( tmp2, "%d", max_time );
	sprintf( tmp3, "%d", N );		
	argv[1]=tmp1;
	argv[2]=tmp2;
	argv[3]=tmp3;   
	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	 if (cpid == 0) {            //Code executed by child 
	 	printf("<< Inicializando Proceso Cliente Simulado con PID= %ld >>\n", (long) getpid());
	 	argv[0] ="recursos/procesoCliente"; argv[4]=0;
	 	execv(argv[0], argv);		
	 	printf("Inside original child\n");
	 	exit(EXIT_SUCCESS);

	 } else {		
	 	iniciarMonitoreo(cpid);	 	
	 	pids[process_count]=(long)cpid;
	 	pthread_create(&esperarTerminarCliente[process_count],&attr[process_count],notificarTerminacionCliente,(void*)&pids[process_count]);
	 	process_count++;	 	 
	 }

}

int estadoProcesoCliente(int pid){
	return 0;
} 

int enviarSenialProceso(){
	return 0;
}

