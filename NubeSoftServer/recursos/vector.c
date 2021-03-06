/*Descripción.- Estructura dinámica utilizada para la implementación de colas de procesos activos y suspendidos*/
//Fuente: http://happybearsoftware.com/implementing-a-dynamic-array.html
// vector.c

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void vector_init(Vector *vector) {
  // initialize size and capacity
  vector->size = 0;
  vector->capacity = VECTOR_INITIAL_CAPACITY;

  // allocate memory for vector->data
  vector->data = malloc(sizeof(int) * vector->capacity);
  vector->uso = malloc(sizeof(float) * vector->capacity);
}

void vector_append(Vector *vector, int value, float uso) {
  // make sure there's room to expand into
  vector_double_capacity_if_full(vector);

  // append the value and increment vector->size
  int size=vector->size++;
  vector->data[size] = value;
  vector->uso[size] = uso;
}

float vector_get_USO(Vector *vector, int index) {
  if (index >= vector->size || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
    exit(1);
  }
  return vector->uso[index];
}
int vector_get_PID(Vector *vector, int index) {
  if (index >= vector->size || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
    exit(1);
  }
  return vector->data[index];
}
void vector_set(Vector *vector, int index, int value,float uso) {
  // zero fill the vector up to the desired index
  while (index >= vector->size) {
    vector_append(vector, 0,uso);
  }

  // set the value at the desired index
  vector->data[index] = value;
   vector->uso[index] = uso;
}

void vector_double_capacity_if_full(Vector *vector) {
  if (vector->size >= vector->capacity) {
    // double vector->capacity and resize the allocated memory accordingly
    vector->capacity *= 2;
    vector->data = realloc(vector->data, sizeof(int) * vector->capacity);
    vector->uso = realloc(vector->uso, sizeof(float) * vector->capacity);
  }
}
int vector_size(Vector *vector){
  return vector->size ;

}

void vector_ordernar( Vector *vector){
  int c,d;
  

for (c = 0 ; c < ( vector_size(vector) - 1 ); c++)
  {
    for (d = 0 ; d <  vector_size(vector)  - c - 1; d++)
    {
      if (vector->uso[d] > vector->uso[d+1]) /* For decreasing order use < */
      {
        int swap       = vector->data[d];
        vector->data[d]   = vector->data[d+1];
        vector->data[d+1] = swap;
        float swapUso       = vector->uso[d];
        vector->uso[d]   = vector->uso[d+1];
        vector->uso[d+1] = swapUso;
      }
    }
  }
 
}

void vector_encolar(Vector * cola, Vector *vector, int pid){
  int d;
 Vector nuevoVector;
 vector_init(&nuevoVector);
  
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
           vector_append(&nuevoVector, swap,swapUso);
        }
      }
     
  vector_free(vector);  
  vector_init(vector);
  for (d = 0 ; d <  vector_size(&nuevoVector); d++)
        {       
           int swap       =        vector_get_PID(&nuevoVector,d);
           float swapUso       = vector_get_USO(&nuevoVector,d);
           vector_append(vector, swap,swapUso);       
      } 

       vector_free(&nuevoVector);
}
void vector_desencolar(Vector * cola, Vector *vector){
  int d;
  int swap       = cola->data[0];         
    float swapUso       = cola->uso[0];
    vector_append(vector, swap,swapUso);
          
  Vector nuevaCola;
  vector_init(&nuevaCola);
  for (d = 1 ; d <  vector_size(cola); d++)
      {             
           int swap       = cola->data[d];          
           float swapUso       = cola->uso[d];
           vector_append(&nuevaCola, swap,swapUso);        
      }
    vector_free(cola);  
      vector_init(cola);
       for (d = 0 ; d <  vector_size(&nuevaCola); d++)
        {       
           int swap       =        vector_get_PID(&nuevaCola,d);
           float swapUso       = vector_get_USO(&nuevaCola,d);
           vector_append(cola, swap,swapUso);       
      } 
       vector_free(&nuevaCola);
     
      
}

void vector_eliminar( Vector *vector, int pid){
    int d;    
  Vector  nuevoVector;
  vector_init(&nuevoVector);
  for (d = 0 ; d <  vector_size(vector); d++)
      {
        if (!(vector->data[d] == pid)) { 
           int swap       = vector->data[d];          
           float swapUso       = vector->uso[d];
           vector_append(&nuevoVector, swap,swapUso);
        }
      } 
      vector_free(vector);  
      vector_init(vector);
  for (d = 0 ; d <  vector_size(&nuevoVector); d++)
        {       
           int swap       =        vector_get_PID(&nuevoVector,d);
           float swapUso       = vector_get_USO(&nuevoVector,d);
           vector_append(vector, swap,swapUso);       
      } 

       vector_free(&nuevoVector);
}

void vector_free(Vector *vector) {
  free(vector->data);
  free(vector->uso);
}