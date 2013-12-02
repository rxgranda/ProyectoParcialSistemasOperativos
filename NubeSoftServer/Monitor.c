#include <pthread.h>
#include <stdio.h>
#include "Monitor.h"

int yMax;
int yMin;
int z;
int iniciarMonitoreo( int pid){
	return 20;
}

void *init_Monitor(void *param){
	int * parametros=(int *)param;
	yMax=parametros[0];
	yMin=parametros[1];
	z=parametros[2];
	printf("\nCarga mínima de CPU =%d", yMin);
	printf("\nCarga máxima de CPU=%d", yMax);
	printf("\nIntervalo de monitoreo=%d",z );
}



