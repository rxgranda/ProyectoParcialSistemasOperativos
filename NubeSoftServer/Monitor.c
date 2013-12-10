#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "Monitor.h"
#include "InfoProcesos.h"
#include "recursos/vector.h"


Vector procesosClientes;
Vector procesosSuspendidos;




int yMax;
int yMin;
int z;
float acumuladorCPU;
float numProcesosCPU;

pthread_attr_t attrMonitor;
pthread_t monitorThread;

int bloqueo;
int bloqueoInicio;
int bloqueoRegulacion;

int iniciarMonitoreo( int pid){	
		bloqueoInicio=1;
		while (bloqueo==1||bloqueoRegulacion==1)
			usleep(100);
		vector_append(&procesosClientes, pid,0);//infoCpuLoad(pid));
		//vector_ordernar(&procesosClientes); 	
		printf("\nAgregado al monitor PID=%d",pid);
		nuevoProceso(pid);
		bloqueoInicio=0;
		
		
 
	
	return pid;
}

void reinciarEstadistica(){
	acumuladorCPU=0;
	numProcesosCPU=0;

}

int calcularEstadistica(){	
	int i;
	int flag;
	int size=vector_size(&procesosClientes);
	if(size<1)
		return -1;
	for (i=0; i<size;i++){
		
		//while (bloqueo==1||bloqueoInicio==1)
		//usleep(100);
		int pid= vector_get_PID(&procesosClientes, i);
		if (pid==0){
			printf("\n 00000000000000000000000000000000000000000000"); /////// ELIMINAR LUEGO
		}else{						
			float cpuLoad=infoCpuLoad(pid);
			if(cpuLoad>=0.0&&cpuLoad<=100.0){
				flag++;
				acumuladorCPU+=cpuLoad;
				numProcesosCPU++;
			}
			printf("\nLa carga del proceso  %d es %f", pid, cpuLoad);
		}
}
//if (flag>0)
	return 0;
//else 
//	return -1;
}
int regularProcesos(){
	bloqueoRegulacion=1;
	printf("\nIniciar Regulacion");
	while (bloqueo==1||bloqueoInicio==1)
			usleep(100);
	//vector_ordernar(&procesosClientes);
	reinciarEstadistica();
	int flag=calcularEstadistica();

	if (flag==-1){
		bloqueoRegulacion=0;
		printf("\nFinaliza Regulacion por no tener procesos");
		return 0;
	}
		
	
	float cargaCPUPromedio=acumuladorCPU/(float)numProcesosCPU;	
	if(cargaCPUPromedio>yMax||cargaCPUPromedio<yMin){
		vector_ordernar(&procesosClientes);
		if(cargaCPUPromedio>(float)yMax){			
			
			int size_proceso=vector_size(&procesosClientes);
			int pid=vector_get_PID(&procesosClientes, size_proceso-1);
			vector_encolar(&procesosSuspendidos,&procesosClientes,pid);
			operacionProceso(1,pid); // SUSPENDER
		}
		if(cargaCPUPromedio<(float)yMin){
			if(vector_size(&procesosSuspendidos)<1){
				bloqueoRegulacion=0;
					printf("\nFinaliza Regulacion, la cola de espera esta vacia");
				return 0;	
				
				}	
			int pid=vector_get_PID(&procesosSuspendidos, 0);	
			vector_desencolar(&procesosSuspendidos,&procesosClientes);
			operacionProceso(2,pid); // Reanudar
		}
		
		reinciarEstadistica();
		flag=calcularEstadistica();

		if(flag!=-1){
			cargaCPUPromedio=acumuladorCPU/(float)numProcesosCPU;
		printf("\n La carga Promedio es %4.8f", cargaCPUPromedio);
		}else{
			cargaCPUPromedio=0.0;
		printf("\n La carga Promedio es FlAG -1 %4.8f", cargaCPUPromedio);	
		}
	}
	bloqueoRegulacion=0;
	printf("\nFinaliza Regulacion");
	return 0;
}

void *monitor(){
	long nIntervaloEspera=z*1000;
	int i;
	while(1){
		printf("Loop Monitor\n");
		usleep(nIntervaloEspera);
		while (bloqueo==1||bloqueoInicio==1)
			usleep(100);
			int size=vector_size(&procesosClientes);
			if(size>0){				
				regularProcesos();
				
				
			}else{
				resumenGlobal();
			}
		

	}
}


void init_Monitor(int yMaxT,int yMinT, int zT){
	vector_init(&procesosClientes);
	vector_init(&procesosSuspendidos);
	
	yMax=yMaxT;	
	yMin=yMinT;
	z=zT;
	printf("\n************** Inicializar Monitor **************");	
	printf("\nCarga mínima de CPU =%d",yMin);
	printf("\nCarga máxima de CPU=%d", yMax);
	printf("\nIntervalo de monitoreo=%d",z );	
	pthread_create(&monitorThread,&attrMonitor,monitor,NULL);
	

}

void eliminarProceso(int pid){
while (bloqueoInicio==1||bloqueoRegulacion==1)
		usleep(100);
	bloqueo=1;	 		 	
 			printf("\n2.Terminar a %d\n",pid); 			
 			vector_eliminar(&procesosClientes,pid);
 			//vector_ordernar(&procesosClientes); 
 			registrarProceso(1,pid);			
 			kill (pid, SIGTERM); 			 	 	
	bloqueo=0;

}

void operacionProceso(int operacion, int pid){
		switch(operacion) {
			case 1://Pausar
			printf("\nPausar a PID %d\n",pid);
			registrarProceso(1,pid); 							
			kill (pid, SIGUSR1);
			 	
			break;

			case 2: //reinciar
			printf("\nReiniciar a PID %d\n",pid); 
			registrarProceso(2,pid);						
			kill (pid, SIGUSR2);
			
			
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
 //printf("%s\n",str );
  fp = popen(str, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    return 0.0;
  }

  /* Read the output a line at a time - output it. */
  int i=0;
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
  	if(i==1){  	 
  	//printf("\n///////// CARGA EN STRING %s\n",path ); 	
	  	sscanf(path, "%f", &cpu);
	    break;
	}
	i++;
   
  }

  /* close */
  pclose(fp);
  if(cpu<0.0)
  	return 0.0;
  else
  return cpu/4.0;

}


