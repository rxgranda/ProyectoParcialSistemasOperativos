# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <math.h>


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>



# include "recursos/normal.h"




int nuevoClienteSocket(int perc_cpu,int max_time,int iteraciones){
  printf("\nIniciar cliente a traves de socket\n");

  int sockfd;
  int len, rc ;
  struct sockaddr_in address;
  int result;
  char ch = 'A';

   //Create socket for client.
  sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) { 
    perror("Socket create failed.\n") ; 
    return -1 ; 
  } 
  
  //Name the socket as agreed with server.
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(7777);
  len = sizeof(address);

  result = connect(sockfd, (struct sockaddr *)&address, len);
  if(result == -1)
  {
    perror("Error has occurred");
    exit(-1);
  }
  

    //Read and write via sockfd
    char cpu[5],tiempo[5],iteracionesCliente[5];
   
    sprintf(cpu, "%d", perc_cpu);  
    rc = write(sockfd, &cpu, 5);    
    read(sockfd, &ch, 1);

    sprintf(tiempo, "%d", max_time);  
    rc = write(sockfd, &tiempo, 5);    
    read(sockfd, &ch, 1);

    sprintf(iteracionesCliente, "%d", iteraciones);  
    rc = write(sockfd, &iteracionesCliente, 5);     // 10 numero de caracteres escritos
    read(sockfd, &ch, 1);
    


    printf("Cliente Solicitado = %c\n", ch);  

   
  close(sockfd);
return 0;



}







 int  main(int argc, char  *argv[]){
  int N,o,t,iteraciones=1;
   long int i;
  int opt = 0;
  while ((opt = getopt(argc, argv, "N:o:t:")) != -1) {
    switch(opt) {
      case 'N':
      N=atoi(optarg);
        printf("\nNumero de procesos cliente =%d", N);
      break;

      case 'o':
      o=atoi(optarg);
        printf("\nOpcion de simulacion=%d\n", o);
      break;

      case 't':
        t=atoi(optarg);
        printf("\nTiempo de simulacion de cada proceso cliente (seg)=%d", t);
      break;



      case '?':
      if (optopt == 'N') {
        printf("\nIngrese N (Numero de procesos cliente)");   
      } else if (optopt == 'o') {
        printf("\nnIngrese o (opcion de simulacion {1,2,3})");
      } else {
        printf("\nArgumento desconocido");
      }
      break;
    }
  }

//Tiempo de ejecucion por default
  if(t==NULL)
    t=3;

  

  if (o==1){
     printf("\nTipo simulacion 1: 70 por ciento CPU ");
      for (  i = 1; i <= N; i++ )
      {     
        nuevoClienteSocket( 70,t,iteraciones);
      }

  }else if(o==2){
    printf("\nTipo simulacion 2: N/2 80 por ciento CPU, 40 por ciento CPU ");
      int temp=N/2;
      int temp2=(int)((float)N/2+0.5);

      for (  i = 1; i <= temp; i++ )
      {     
        nuevoClienteSocket( 80,t,iteraciones);
      }
      for (  i = 1; i <= temp2; i++ )
      {     
        nuevoClienteSocket( 40,t,iteraciones);
      }

  }else if(o==3){
    double a;
    double b;
   
    long int seed;
    long int seed_init = 123456789;

    a = 65.0;
    b = 10.0;
    seed = seed_init;

    printf ( "\n" );
    printf ( "  Media  = %f\n", a );
    printf ( "  Desviacion Estandard= %f\n", b ); 
    printf ( "\n" );

    for ( i = 1; i <= N; i++ )
    {
      int cpu_burst_normal= i8_normal_ab ( a, b, &seed );
      printf ( "  %8d  %8d\n", i,cpu_burst_normal );
      nuevoClienteSocket(cpu_burst_normal,t,iteraciones);
    }

   
  }else{
     printf("\nIngrese correctamente el tipo de simulacion {1,2,3} ");   

  }
  
  return 0;
}

