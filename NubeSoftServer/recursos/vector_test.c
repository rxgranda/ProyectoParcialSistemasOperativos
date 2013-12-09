//Fuente: http://happybearsoftware.com/implementing-a-dynamic-array.html
// vector-usage.c

#include <stdio.h>
#include "vector.h"
Vector vector;
Vector cola;
Vector nuevoVector;
Vector nuevaCola;

  




int main() {
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

vector_free(&vector);
 // vector_free(&cola);
   vector_free(&nuevoVector);
}