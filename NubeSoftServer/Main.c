#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "recursos/vector.h"
#include "AdministradorProcesos.h"
#include "Monitor.h"
#include "InfoProcesos.h"

// Constantes

//Variable Globales
pthread_attr_t attr;
Vector procesosClientes;
pthread_t administradorProcesos; /* adm Procesos */
pthread_t infoProcesos;
pthread_t monitorProcesos;



/*
 *Descripcion: Inicializar  variables de instancia principal del servidor Nubesoft
 */
 void init_NubeSoftServer(int yMax,int yMin, int z){
	//Inicializar los módulos
 	//pthread_create(&administradorProcesos,&attr,runner,NULL);
 	//pthread_create(&infoProcesos,&attr,runner,NULL);
 	int parametros[3]={yMax, yMin, z}; 	
 	pthread_create(&monitorProcesos,&attr,init_Monitor,(void *)parametros);
 	
 }
 int  iniciar_cliente(){
 	vector_init(&procesosClientes);
 	int pid=0;
 	vector_append(&procesosClientes, pid);
 	return pid;
 }


 /*
 *Descripcion: Punto de inicio de la Instancia del servidor Nubesoft
 */
 int  main(int argc, char  *argv[])
 {
 	/*int yMax;
	int yMin;
	int z;

 	
 	iniciar_cliente();
 	int i;
 	for (i = 200; i > -50; i--) {
 		vector_append(&procesosClientes, i);
 	}
 	vector_set(&procesosClientes, 4452, 21312984);
 	printf("Heres the value at 27: %d\n", vector_get(&procesosClientes, 0));
 	vector_free(&procesosClientes);
 	printf("Hola mundo %d \n",iniciarMonitoreo(20));
 	
 	int opt = 0;
 	while ((opt = getopt(argc, argv, "M:m:z:")) != -1) {
 		switch(opt) {
 			case 'm':
 			yMin=atoi(optarg);
 			//printf("\nCarga mínima de CPU =%d", yMin);
 			break;

 			case 'M':
 			yMax=atoi(optarg);
 			//printf("\nCarga máxima de CPU=%d", yMax);
 			break;

 			case 'z':  
 			z=atoi(optarg);
 			//printf("\nIntervalo de monitoreo=%d",z );
 			break;

 			case '?':
 			if (optopt == 'M') {
 				printf("\nIngrese Carga mínima de CPU");   
 			} else if (optopt == 'm') {
 				printf("\nnIngrese Carga máxima de CPU");
 			} else if (optopt == 'z') {
 				printf("\nnIngrese Intervalo de monitoreo");
 			} else {
 				printf("\nArgumento desconocido");
 			}
 			break;
 		}
 	}
 	init_NubeSoftServer(yMax,yMin,z);
 	pthread_join(monitorProcesos,NULL);
 	*/
 	iniciarProcesoCliente(50,2,2);

 	printf("\nDebug Terminado\n");
 	//Finalizar los módulos
 	//pthread_join(administradorProcesos,NULL); 	
 	//pthread_join(infoProcesos,NULL);
 	//pthread_join(monitorProcesos,NULL);

 	return 0;
 }


