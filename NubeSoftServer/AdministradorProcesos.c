#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "AdministradorProcesos.h"

int iniciarProcesoCliente(int perc_cpu,int max_time,int N){
	pid_t cpid, w;
	int status;
	char *argv[5];
	char tmp1[20];
	char tmp2[20];
	char tmp3[20];
	sprintf( tmp1, "%d", perc_cpu );
	sprintf( tmp2, "%d", max_time );
	sprintf( tmp3, "%d", N );	
	printf("\n%s %s %s \n",tmp1,tmp2,tmp3 );
	//argv[0]="exec";
	argv[1]=tmp1;
	argv[2]=tmp2;
	argv[3]=tmp3;   
	 cpid = fork();
	 if (cpid == -1) {
		 perror("fork");
		 exit(EXIT_FAILURE);
	 }
	 
	 if (cpid == 0) {            //Code executed by child 
		 printf("Child PID is %ld\n", (long) getpid());
	     argv[0] ="recursos/procesoCliente"; argv[4]=0;
		 execv(argv[0], argv);
		// sleep(10000);
		 printf("Inside original child\n");
		 exit(EXIT_SUCCESS);
		 
	 } else {                    // Code executed by parent 
		 fprintf(stderr,"Waiting in the father %ld for child %d\n",(long) getpid(),cpid);
		 w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
		 fprintf(stderr,"\nChild finished");			 
		 exit(EXIT_SUCCESS);
	 }
		 printf("\nHola");	
	
}

int estadoProcesoCliente(int pid){
	return 0;
} 

int enviarSenialProceso(){
	return 0;
}

