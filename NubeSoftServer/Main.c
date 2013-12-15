#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

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


sigset_t myset;

static void sig_handler(int signo)
{
	resumenGlobal();
	printf("\n************   Programa Terminado   ************\n"); 	
	exit(EXIT_SUCCESS);
}


void *nuevoCliente(void * param){
	int * parametros=(int *)param;
	int client_sockfd=parametros[0];
	
	int rc;
	char  ch[5];
	char temp='1';
	char *ok=&temp;
	int cpu_burst,tiempo,iteraciones;			

	printf("Nuevo Cliente Solicitado ");
	rc = read(client_sockfd, ch, 5); // numero de caracteres leidos			
	printf(" CPU Burst= %s ", ch ) ; 
	cpu_burst=atoi(ch);				
	write(client_sockfd, ok, 1);
	
	rc = read(client_sockfd, ch, 5); // numero de caracteres leidos
	printf(" Tiempo de Ejecucion(Seg)= %s ", ch ) ; 
	tiempo=atoi(ch);					
	write(client_sockfd, ok, 1);
	
	rc = read(client_sockfd, ch, 5); // numero de caracteres leidos
	printf(" Iteraciones= %d\n", 10 ) ;
	iteraciones=atoi(ch);			
	write(client_sockfd, ok, 1);
	iteraciones=10;
				
	iniciarClienteSimulado(cpu_burst,tiempo,iteraciones);
	close(client_sockfd);

}

void* abrirSocket(){
	//Declarar variables de proceso.
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

	//Crear una conexion y esperar a una solicitud de cliente	
	while(1)
	{
		rc = listen(server_sockfd, 5);
		printf("\nEscuchando Socket status ok= %d\n", rc ) ; 
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);		
		int parametros[3]={client_sockfd}; 	
		nuevoCliente((void *)parametros);
	}

	printf("server exiting\n");
	return 0;
}


 /*
 *Descripcion: Punto de inicio de la Instancia del servidor Nubesoft
 */
 int  main(int argc, char  *argv[])
 {
 	(void) sigemptyset(&myset);
	sigaddset(&myset,SIGINT);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGINT\n");

 	int yMax;
 	int yMin;
 	int z;
 	int opt = 0;

 	while ((opt = getopt(argc, argv, "M:m:z:")) != -1) {
 		switch(opt) {
 			case 'm':
 			yMin=atoi(optarg); 
 			break;

 			case 'M':
 			yMax=atoi(optarg); 			
 			break;

 			case 'z':  
 			z=atoi(optarg); 			
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
 
 	return 0;
 }


