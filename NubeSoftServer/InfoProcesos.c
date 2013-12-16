#include "InfoProcesos.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

// Constante
#define MAX_PROC_COUNT 1000

long resumen[MAX_PROC_COUNT][4];
int acumulador=0; // Contador de procesos creados

/*Descripción.- Función utilizada para la impresión de todo los
 datos recopilados de procesos cuando el porgrama termina*/
void resumenGlobal(){
    if(!acumulador==0){
       printf("\n+++++     Resumen Global ejecucion    ++++++++\n    PID   Tiempo Total ejecucion [mseg]  Tiempo Espera [mseg]\n");
       int i;
       for (i = 0; i < acumulador; ++i)
       {
          printf("    %ld            %ld                %ld \n",resumen[i][0],resumen[i][1],resumen[i][2] );	
        }
    }
}

/*Descripción.- Función utilizada la creación de un 
nuevo registro de tiempo de proceso cliente*/
int nuevoProceso(int pid){
    struct timeval  end;
    long mtime, seconds, useconds;    
    gettimeofday(&end, NULL);
    seconds  = end.tv_sec;
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



/*Descripción.- Función utilizada para el registro de 
tiempo en el cambio de estado de los procesos clientes*/
int registrarCambioEstadoProceso(int opt,int pid){
    int i=buscar(pid);
    if(i==-1) 
       return 0;
    struct timeval end;
    long mtime, seconds, useconds;    
    gettimeofday(&end, NULL);
    seconds  = end.tv_sec   ;
    useconds = end.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    if(opt==1){	// 1 PAUSAR // 2CONTINUAR
        resumen[i][opt]+=mtime-resumen[i][3]; // Guardar ejecucion
    }else{ 
        resumen[i][opt]+=mtime-resumen[i][3];
        resumen[i][1]+=mtime-resumen[i][3]; // Guardar pausa
    }
    resumen[i][3]=mtime;    
    return 0;
}

/*Descripción.- Función utilizada para imprimir información recopilada del proceso*/
int resumenProceso(int pid, float cpu){
     int i=buscar(pid);     
    if(i==-1) 
       return 0;
    struct timeval end;
    long mtime, seconds, useconds;    
    gettimeofday(&end, NULL);
    seconds  = end.tv_sec   ;
    useconds = end.tv_usec;
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;     
     printf("\n      --------------------------------------------\n                -- --Resumen Proceso-- --\n        PID        %%cpu     Tiempo ejecucion [mseg] \n        %d      %4.2f            %ld\n      --------------------------------------------\n",pid,cpu,  resumen[i][1]+mtime-resumen[i][3]);
    return 0;    
}



