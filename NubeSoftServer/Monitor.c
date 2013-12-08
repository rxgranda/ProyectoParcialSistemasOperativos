#include <pthread.h>
#include <stdio.h>
# include <stdlib.h>
#include "Monitor.h"

int yMax;
int yMin;
int z;
int iniciarMonitoreo( int pid){
	return 20;
}

void init_Monitor(int yMaxT,int yMinT, int zT){
	
	yMax=yMaxT;	
	yMin=yMinT;
	z=zT;
	printf("\n************** Inicializar Monitor **************");	
	printf("\nCarga mínima de CPU =%d",yMin);
	printf("\nCarga máxima de CPU=%d", yMax);
	printf("\nIntervalo de monitoreo=%d",z );
}



