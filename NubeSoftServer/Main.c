#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#include "AdministradorProcesos.h"
#include "Monitor.h"
#include "InfoProcesos.h"

// Constantes

//Variable Globales
pthread_attr_t attr;
pthread_t administradorProcesos; /* adm Procesos */
pthread_t infoProcesos;
pthread_t monitorProcesos;
pthread_t conexionSocket;



void *nuevoCliente(void * param){
	int * parametros=(int *)param;
	int client_sockfd=parametros[0];
	
			int rc;
			char  ch[5];
			char temp='1';
			char *ok=&temp;
			int cpu_burst,tiempo,iteraciones;			
		
			printf("Nuevo Cliente Solicitado\n");
			rc = read(client_sockfd, ch, 5); // numero de caracteres leidos			
			printf("CPU Burst= %s\n", ch ) ; 
			cpu_burst=atoi(ch);				
			write(client_sockfd, ok, 1);
			
			rc = read(client_sockfd, ch, 5); // numero de caracteres leidos
			printf("Tiempo (Seg)= %s\n", ch ) ; 
			tiempo=atoi(ch);					
			write(client_sockfd, ok, 1);

			
			rc = read(client_sockfd, ch, 5); // numero de caracteres leidos
			printf("Iteraciones= %s\n", ch ) ;
		 	iteraciones=atoi(ch);			
			write(client_sockfd, ok, 1);
			iteraciones=10;

	/*long  parametrosH[3];
 	parametrosH[0]=(long)cpu_burst;
 	parametrosH[1]=(long)tiempo;
 	parametrosH[2]=(long)iteraciones;
 	pthread_create(&monitorProcesos,&attr,iniciarClienteSimulado,(void* )parametrosH);*/
			iniciarClienteSimulado(cpu_burst,tiempo,iteraciones);
			
	
	close(client_sockfd);

}

void* abrirSocket(){
	//Declaring process variables.
	int server_sockfd, client_sockfd;
	int server_len ; 
	int rc ; 
	unsigned client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	//Remove any old socket and create an unnamed socket for the server.
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	server_address.sin_port = htons(7777) ; 
	server_len = sizeof(server_address);

	rc = bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
	printf("\n************** Inicializar Servidor Socket **************\nInicializar Socket = %d", rc ) ; 
	
	//Create a connection queue and wait for clients
	
	while(1)

	{
		rc = listen(server_sockfd, 5);
		printf("\nEscuchando Socket status ok= %d\n", rc ) ; 

		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
		printf("after accept()... client_sockfd = %d\n", client_sockfd) ; 
		int parametros[3]={client_sockfd}; 
		/*pthread_create(&monitorProcesos,&attr,atender,(void *)parametros);*/
		nuevoCliente((void *)parametros);
		
	}

	printf("server exiting\n");

	
	return 0;
}


/*
 *Descripcion: Inicializar  variables de instancia principal del servidor Nubesoft
 
 void init_NubeSoftServer(int yMax,int yMin, int z){
	//Inicializar los módulos
 	//pthread_create(&administradorProcesos,&attr,runner,NULL);
 	//pthread_create(&infoProcesos,&attr,runner,NULL);
 	
 	long  parametros[3];
 	parametros[0]=(long)yMax;
 	parametros[1]=(long)yMin;
 	parametros[2]=(long)z;
 	
 	//int * par= parametros;
 	//long a=(long)sizeof(par);
	//printf("\nCarga mínima de CPU =%ld",a);
 	//pthread_create(&monitorProcesos,&attr,init_Monitor,(void* )parametros);
 
 }
 
 int  iniciar_cliente(){
 	vector_init(&procesosClientes);
 	int pid=0;
 	vector_append(&procesosClientes, pid);
 	return pid;
 }
*/

 /*
 *Descripcion: Punto de inicio de la Instancia del servidor Nubesoft
 */
 int  main(int argc, char  *argv[])
 {
 	int yMax;
	int yMin;
	int z;
	

 	
 	
 /*	int i;
 	for (i = 200; i > -50; i--) {
 		vector_append(&procesosClientes, i);
 	}
 	vector_set(&procesosClientes, 4452, 21312984);
 	printf("Heres the value at 27: %d\n", vector_get(&procesosClientes, 0));
 	vector_free(&procesosClientes);
 	printf("Hola mundo %d \n",iniciarMonitoreo(20));
 	*/
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

 	init_Monitor(yMax,yMin,z); 	
 	pthread_create(&conexionSocket,&attr,abrirSocket,NULL); 
 	pthread_join(conexionSocket,NULL);
 	//pthread_join(conexionSocket,NULL);
 	//iniciarProcesoCliente(50,2,2); //iniciar_cliente();



 	printf("\n************   Programa Terminado   ************\n");
 	//Finalizar los módulos
 	//pthread_join(administradorProcesos,NULL); 	
 	//pthread_join(infoProcesos,NULL);
 	//pthread_join(monitorProcesos,NULL);

 	return 0;
 }


