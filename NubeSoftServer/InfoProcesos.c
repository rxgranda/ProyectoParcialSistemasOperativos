#include "InfoProcesos.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#define MAX_THREAD_COUNT 1000
long resumen[MAX_THREAD_COUNT][4];
int acumulador;

void resumenGlobal(){
	if(!acumulador==0){

	printf("+++++Resumen Global ejecucion++++++++\nPID   Tiempo ejecucion   Tiempo Espera\n");
	int i;
	for (i = 0; i < acumulador; ++i)
	{

		printf("%ld %ld %ld \n",resumen[i][0],resumen[i][1],resumen[i][2] );	


		/* code */
	}
}
}

int nuevoProceso(int pid){
	struct timeval  end;

    long mtime, seconds, useconds;    
        
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec   ;
    useconds = end.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	resumen[acumulador][0]=(long)pid;
	resumen[acumulador][1]=0;
	resumen[acumulador][2]=0;
	resumen[acumulador][3]=mtime;	
	acumulador++;
}

int buscar(int pid){
	int i;
	for ( i = 0; i < acumulador; ++i)
	{
		if(resumen[i][0]==pid)
			return i;
	}
	return -1;
}





int registrarProceso(int opt,int pid){
	int i=buscar(pid);
	if(i==-1) 
		return 0;
	struct timeval end;

    long mtime, seconds, useconds;    
        
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec   ;
    useconds = end.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    
    if(opt==1)	// 1 PAUSAR // 2CONTINUAR
    	resumen[i][opt]+=mtime-resumen[i][3]; // Guardar ejecucion
    else 
    	resumen[i][opt]+=mtime-resumen[i][3]; // Guardar pausa
    //else // pausa
    	//resumen[i][opt]=mtime-resumen[i][3];

    resumen[i][3]=mtime; // 
    printf("Elapsed time: %ld milliseconds\n", mtime);
	return 0;
}

int resumenProceso(int pid){
	return 0;
}



