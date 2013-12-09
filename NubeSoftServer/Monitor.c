#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "Monitor.h"
#include "recursos/vector.h"


Vector procesosClientes;
int yMax;
int yMin;
int z;

pthread_attr_t attrMonitor;
pthread_t monitorThread;


int iniciarMonitoreo( int pid){
	vector_append(&procesosClientes, pid);
	printf("\nAgregado al monitor PID=%d",pid);
	return pid;
}

void *monitor(){
	long nIntervaloEspera=z*1000;
	int i;
	while(1){
		printf("Loop Monitor\n");
		usleep(nIntervaloEspera);
		int size=vector_size(&procesosClientes);
		if(size>0){
			for (i=0; i<size;i++){
				int pid= vector_get(&procesosClientes, i);
				float cpu=infoCpuLoad(pid);
				printf("\nLa carga del proceso  %d es %f", pid, cpu);
			}
		}

	}

}
void init_Monitor(int yMaxT,int yMinT, int zT){
	vector_init(&procesosClientes);
	yMax=yMaxT;	
	yMin=yMinT;
	z=zT;
	printf("\n************** Inicializar Monitor **************");	
	printf("\nCarga mínima de CPU =%d",yMin);
	printf("\nCarga máxima de CPU=%d", yMax);
	printf("\nIntervalo de monitoreo=%d",z );	
	pthread_create(&monitorThread,&attrMonitor,monitor,NULL);
	

}

void operacionProceso(int operacion, int pid){

 		switch(operacion) {
 			case 1://kill
 			kill (cpid, SIGTERM);
 			
 			
 			break;

 			case 2: //pausar
 			
 			
 			
 			break;

 			case 3://continuar  
 			
 			
 			break;
		}

}


float infoCpuLoad(int pid){
	float cpu;
  FILE *fp;
  int status;
  char path[1035];

  /* Open the command for reading. */
  char str[80];
  char str2[80];
  char strtmp1[]="/bin/ps -p ";
  char strtmp2[]=" -L -o pcpu ";
	strcpy (str,strtmp1);
	sprintf(str2, "%d", pid);  
	strcat (str,str2);
	strcat (str,strtmp2);
// printf("%s\n",str );
  fp = popen(str, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    return 0.0;
  }

  /* Read the output a line at a time - output it. */
  int i=0;
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
  	if(i==1){  	  	
	  	sscanf(path, "%f", &cpu);
	    break;
	}
	i++;
   
  }

  /* close */
  pclose(fp);
  return cpu;

}


