//Fuente: http://happybearsoftware.com/implementing-a-dynamic-array.html
// vector-usage.c

#include <stdio.h>
#include "vector.h"
Vector vector;
Vector cola;
Vector nuevoVector;
Vector nuevaCola;

void encolar(Vector * cola, Vector *vector, int pid, Vector * nuevoVector){
	int d;
	
	
	for (d = 0 ; d <  vector_size(vector); d++)
	    {
	      if (vector->data[d] == pid) /* For decreasing order use < */
	      {
	        int swap       = vector->data[d];	        
	        float swapUso       = vector->uso[d];
	        vector_append(cola, swap,swapUso);
	        
	      }else{	      	
	      	 int swap       = vector->data[d];	        
	       	 float swapUso       = vector->uso[d];
	       	 vector_append(nuevoVector, swap,swapUso);
	      }
	    }
	   
	    
}
void desencolar(Vector * cola, Vector *vector,Vector *nuevaCola){
	int d;
	int swap       = cola->data[0];	        
    float swapUso       = cola->uso[0];
    vector_append(vector, swap,swapUso);
	        
	
	for (d = 1 ; d <  vector_size(cola); d++)
	    {	     	      
	      	 int swap       = cola->data[d];	        
	       	 float swapUso       = cola->uso[d];
	       	 vector_append(nuevaCola, swap,swapUso);	      
	    }
	   
	    
}

int main() {
  vector_init(&vector); 
   vector_init(&cola); 
   vector_init(&nuevoVector);  
vector_init(&nuevaCola);

   int i;
  float f=0.0;
  for (i = 0; i < 20; i++) {
    vector_append(&vector, i,-1.0*f);
   
    f++;
  }
  for (i = 0; i < vector_size(&vector); i++) {
     printf("%4.2f \n",vector_get(&vector, i));
 }
   encolar(&cola,&vector,10, &nuevoVector);
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

vector_free(&vector);
  vector_free(&cola);
   vector_free(&nuevoVector);
}