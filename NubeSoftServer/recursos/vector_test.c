//Fuente: http://happybearsoftware.com/implementing-a-dynamic-array.html
// vector-usage.c

#include <stdio.h>
#include "vector.h"
#include <sys/time.h>

#include <unistd.h>
/*Vector vector;
Vector cola;
Vector nuevoVector;
Vector nuevaCola;

  unsigned long inicio;
unsigned long fin;



#define MAX_THREAD_COUNT 1000
long resumen[MAX_THREAD_COUNT][4];
int acumulador;
void resumenGlobal(){
	printf("+++++Resumen Global ejecucion++++++++\nPID   Tiempo ejecucion   Tiempo Espera\n");
	int i;
	for (i = 0; i < acumulador; ++i)
	{

		printf("%ld %ld %ld %ld\n",resumen[i][0],resumen[i][1],resumen[i][2] );	


		/* code 
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
   // printf("Elapsed time: %ld milliseconds\n", mtime);
	return 0;
}
*/



float infoCpuLoad(int pid){
  float cpu;
  FILE *fp;
  int status;
  char path[1035];

  /* Open the command for reading. */
  const char * str="top -bn 1 | awk 'NR>6{s+=$9} END {print s/4}' ";
  /*char str2[80];
  char strtmp1[]="/bin/ps -p ";
  char strtmp2[]=" -L -o pcpu ";
  strcpy (str,strtmp1);
  sprintf(str2, "%d", pid);  
  strcat (str,str2);
  strcat (str,strtmp2);*/
 //printf("%s\n",str );
  fp = popen(str, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    return 0.0;
  }

  /* Read the output a line at a time - output it. */
  int i=0;
  float acum;
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    //if(i==1){    
      printf("\n///////// CARGA EN STRING %s\n",path );   
    sscanf(path, "%f", &cpu);
      acum+=cpu;
     // break;
  //}
  i++;
   
  }
  printf("\n///////// TOTAL %f\n",acum );

  /* close */
  pclose(fp);
  if(cpu<0.0)
    return 0.0;
  else
  return cpu/4.0;


}






int main() {
infoCpuLoad(0);
/*uevoProceso(1);
nuevoProceso(2);
nuevoProceso(3);

usleep(1000000);
registrarProceso(1,1);
usleep(1000000);
usleep(1000000);
//usleep(1000000);
registrarProceso(2,1);
usleep(1000000);
usleep(1000000);
registrarProceso(1,1);
//registrarProceso(22,1);
//usleep(1000000);
resumenGlobal();

*/










	/*struct timeval start, end;

    long mtime, seconds, useconds;    

    gettimeofday(&start, NULL);
    usleep(2000);
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);

    return 0;

	/*
  vector_init(&vector); 
   vector_init(&cola); 
   vector_init(&nuevoVector);  
//vector_init(&nuevaCola);

   int i;
  float f=0.0;
  for (i = 0; i < 20; i++) {
    vector_append(&vector, i,-1.0*f);
   
    f++;
  }
  for (i = 0; i < vector_size(&vector); i++) {
     printf("%4.2f \n",vector_get_USO(&vector, i));
 }
 //eliminar(&vector,5);
    encolar(&cola,&vector,10);
     encolar(&cola,&vector,11);
 printf("***************************** \n");
   for (i = 0; i < vector_size(&vector); i++) {
     printf("%4.2f \n",vector_get_USO(&vector, i));
 }
printf("***************************** \n");
  for (i = 0; i <  vector_size(&cola); i++) {
     printf("%4.2f \n",vector_get_USO(&cola, i));
 }
 desencolar(&cola,&vector);

 printf("***************************** \n");
   for (i = 0; i < vector_size(&vector); i++) {
     printf("%4.2f \n",vector_get_USO(&vector, i));
 }
printf("***************************** \n");
  for (i = 0; i <  vector_size(&cola); i++) {
     printf("%4.2f \n",vector_get_USO(&cola, i));
 }
 /*  encolar(&cola,&vector,10, &nuevoVector);
printf("***************************** \n");
  for (i = 0; i < vector_size(&nuevoVector); i++) {
     printf("%4.2f \n",vector_get(&nuevoVector, i));
 }
  printf("***************************** \n");
 for (i = 0; i <  vector_size(&cola); i++) {
     printf("%4.2f \n",vector_get(&cola, i));
 }
 desencolar(&cola,&nuevoVector,&nuevaCola);
 printf("***************************** \n");
  for (i = 0; i < vector_size(&nuevoVector); i++) {
     printf("%4.2f \n",vector_get(&nuevoVector, i));
 }
  printf("***************************** \n");
 for (i = 0; i <  vector_size(&nuevaCola); i++) {
     printf("%4.2f \n",vector_get(&nuevaCola, i));
 }
 vector_ordernar(&nuevoVector);
 printf("***************************** \n");
  for (i = 0; i < vector_size(&nuevoVector); i++) {
     printf("%4.2f \n",vector_get(&nuevoVector, i));
 }
/*
int i;
  float f=0.0;
  for (i = 0; i < 20; i++) {
    vector_append(&vector, i,-1.0*f);
    printf("%4.8f \n",f);
    f++;
  }
   printf("***************************** %f\n",vector_get(&vector, 19));
for (i = 0; i < 10; i++) {
     printf("%4.2f \n",vector_get(&vector, i));
 }
 printf("***************************** \n");
vector_ordernar(&vector);
for (i = 0; i < 20; i++) {
     printf("%4.2f \n",vector_get(&vector, i));
 }
  //vector_set(&vector, 4452, 21312984);


  //printf("Heres the value at 27: %d\n", vector_get(&vector, 0));
*/

//vector_free(&vector);
 // vector_free(&cola);
  // vector_free(&nuevoVector);
}