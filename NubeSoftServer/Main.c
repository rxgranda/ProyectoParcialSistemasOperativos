#include <stdio.h>
#include <unistd.h>
#include "recursos/vector.h"
#include "Monitor.h"

// Constantes

//Variable Globales
Vector procesosClientes;
int yMax=0;
int yMin=0;
int z=0;

/*
 *Descripcion: Inicializar  variables de instancia principal del servidor Nubesoft
 */
 void init_NubeSoftServer(){	
 	vector_init(&procesosClientes);
 }
 int  iniciar_cliente(){
 	int pid=0;
 	vector_append(&procesosClientes, pid);
 	return pid;
 }


 /*
 *Descripcion: Punto de inicio de la Instancia del servidor Nubesoft
 */
 int  main(int argc, char  *argv[])
 {
 	init_NubeSoftServer();
 	int i;
 	for (i = 200; i > -50; i--) {
 		vector_append(&procesosClientes, i);
 	}
 	vector_set(&procesosClientes, 4452, 21312984);
 	printf("Heres the value at 27: %d\n", vector_get(&procesosClientes, 0));
 	vector_free(&procesosClientes);
 	printf("Hola mundo %d \n",hello(20));
 	
 	int opt = 0;
 	while ((opt = getopt(argc, argv, "M:m:z:")) != -1) {
 		switch(opt) {
 			case 'm':
 			yMin=atoi(optarg);
 			printf("\nCarga mínima de CPU =%d", yMin);
 			break;

 			case 'M':
 			yMax=atoi(optarg);
 			printf("\nCarga máxima de CPU=%d", yMax);
 			break;

 			case 'z':  
 			z=atoi(optarg);
 			printf("\nIntervalo de monitoreo=%d",z );
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
 	return 0;
 }


