#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "Monitor.h"
#include "InfoProcesos.h"
#include "recursos/vector.h"


Vector procesosClientes; // Cola de procesos en ejecución
Vector procesosSuspendidos; // Cola de procesos suspendidos

int yMax; // Parámetro de carga promedio máxima de CPU
int yMin; // Parámetros de carga promedio mínima de CPU
int z; // Intervalo de Monitor


pthread_attr_t attrMonitor;
pthread_t monitorThread;

// Flags utilizados para la ejecución de secciones de código críticas
int bloqueoAccion;
int bloqueoInicio;
int bloqueoRegulacion;

/*Descripción.- Función utilizada para el inicio de monitoreo de nuevos clientes */
int iniciarMonitoreoProceso( int pid){	
	
	bloqueoInicio=1; //Iniciar Sección crítica

		nuevoProceso(pid);
		while (bloqueoAccion==1||bloqueoRegulacion==1)
			usleep(100);
		vector_append(&procesosClientes, pid,0);	
		printf("\nAgregado al monitor PID=%d",pid);
		float cargaCPU=infoProcessCpuLoad(pid);
		resumenProceso(pid,cargaCPU);

	bloqueoInicio=0; //Finalizar Sección crítica
	return pid;
}

/*Descripción.- Función utilizada para el control de procesos clientes*/
int regularProcesos(){	 
	printf("\n-->Iniciar Revision carga de Procesos");

	while (bloqueoAccion==1||bloqueoInicio==1)
		usleep(100);
	bloqueoRegulacion=1;
	float cargaCPUPromedio=infoTotalCpuLoad();
	int cnt=0;
	while(cargaCPUPromedio>yMax||cargaCPUPromedio<yMin){
		cnt++;
		vector_ordernar(&procesosClientes);
	
		if(cargaCPUPromedio<(float)yMin){
			printf("\n    La carga Promedio es %4.2f <yMin, Intentar reactivar procesos", cargaCPUPromedio);		
			
			if(vector_size(&procesosSuspendidos)<1){
				bloqueoRegulacion=0;
				printf("\n-->Finaliza Regulacion, no hay procesos para reiniciar");
				return 0;	
			}

			int pid=vector_get_PID(&procesosSuspendidos, 0);	
			vector_desencolar(&procesosSuspendidos,&procesosClientes);			
			operacionProceso(2,pid); // Reanudar
		}

		if(cargaCPUPromedio>(float)yMax){			
			printf("\n    La carga Promedio es %4.2f >yMax, Intentar suspender procesos", cargaCPUPromedio);
			if(vector_size(&procesosClientes)<1){
				bloqueoRegulacion=0;
				printf("\n-->Finaliza Regulacion, no hay procesos para suspender");
				return 0;	

			}

			int size_proceso=vector_size(&procesosClientes);
			int pid=vector_get_PID(&procesosClientes, size_proceso-1);
			vector_encolar(&procesosSuspendidos,&procesosClientes,pid);
			operacionProceso(1,pid); // SUSPENDER
		}
		
		cargaCPUPromedio=infoTotalCpuLoad();				
	}
	bloqueoRegulacion=0;
	if (cnt!=0)
	{
		printf("\n-->Fin Revision de carga Procesos");
	}else
	{
		printf("\n      Sistema estable, no es necesario regular procesos\n-->Fin Revision de carga Procesos");
	}
	
	return 0;
}

/*Descripción.- Seccion de hilo permanente de monitor*/
void *monitor(){
	long nIntervaloEspera=z*1000;
	int i;
	while(1){
		printf("\nCiclo de Monitor\n");
		usleep(nIntervaloEspera);
		while (bloqueoAccion==1||bloqueoInicio==1)
			usleep(100);
		int sizeActivos=vector_size(&procesosClientes);
		int sizeSuspendidos=vector_size(&procesosSuspendidos);
		if(sizeActivos>0||sizeSuspendidos>0){				
			regularProcesos();
		}	
	}
}

//Inicialización de Monitor
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

/*Descripción.- Función utilizada paralas acciones a realizar durante la eliminación de un proceso*/
void eliminarProceso(int pid){
	while (bloqueoInicio==1||bloqueoRegulacion==1)
		usleep(100);
	bloqueoAccion=1;	 		 	
	printf("\n << Termina el proceso con PID= %d >>\n",pid); 			
	vector_eliminar(&procesosClientes,pid);
	vector_ordernar(&procesosClientes);
	float cargaCPU=infoProcessCpuLoad(pid);
	resumenProceso(pid,cargaCPU);
	kill (pid, SIGTERM); 			 	 	
	registrarCambioEstadoProceso(1,pid);			
	bloqueoAccion=0;
}

/*Descripción.- Función utilizada paralas acciones a realizar durante la suspensión o reanudación de un proceso*/
void operacionProceso(int operacion, int pid){
	switch(operacion) {
		case 1://Pausar
		printf("\n    Pausar proceso PID %d",pid);
		float cargaCPU=infoProcessCpuLoad(pid);
		resumenProceso(pid,cargaCPU);
		kill (pid, SIGUSR1);
		registrarCambioEstadoProceso(1,pid); 	
		break;

		case 2: //reinciar
		printf("\n    Reiniciar proceso PID %d",pid); 
		float cargaCPU2=infoProcessCpuLoad(pid);
		resumenProceso(pid,cargaCPU2);
		kill (pid, SIGUSR2);
		registrarCambioEstadoProceso(2,pid);						
		break;
	}
}

/*Descripción.- Función utilizada para el calculo de carga de CPU del sistema*/
float infoTotalCpuLoad(){

	float cpu;
	FILE *fp;
	int status;
	char path[1035];
	const char * str="top -bn 1 | awk 'NR>6{s+=$9} END {print s}' "; // Obtener carga del sistema

	fp = popen(str, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return 0.0;
	}

	/* Leer la lineas de carga de procesos individuales */
	int i=0;
	float acum;
	while (fgets(path, sizeof(path)-1, fp) != NULL) {        
		sscanf(path, "%f", &cpu);
		acum+=cpu;     
	}	
	pclose(fp);
	return cpu/4;
}    

/*Descripción.- Función utilizada para el cálculo de carga de CPU de un proceso específico*/
float infoProcessCpuLoad(int pid){
	float cpu;
	FILE *fp;
	int status;
	char path[1035]; 
	char str[80];
	char str2[80];
	char strtmp1[]="/bin/ps -p ";
	char strtmp2[]=" -L -o pcpu ";
	strcpy (str,strtmp1);
	sprintf(str2, "%d", pid);  
	strcat (str,str2);
	strcat (str,strtmp2); 
	fp = popen(str, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return 0.0;
	} 
	int i=0;
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		if(i==1){           
             
			sscanf(path, "%f", &cpu);
			break;
		}
		i++;
	}

	pclose(fp);	   
	if(cpu<0.0)
		return 0.0;
	else
		return cpu/4.0;

}
