//Fuente: http://happybearsoftware.com/implementing-a-dynamic-array.html
// vector.h

#define VECTOR_INITIAL_CAPACITY 100

// Define a vector type
typedef struct {
  int size;      // slots used so far
  int capacity;  // total available slots
  int *data;     // array of integers we're storing
  float *uso;
} Vector;

void vector_init(Vector *vector);

void vector_append(Vector *vector, int value, float uso);

float vector_get(Vector *vector, int index);

void vector_set(Vector *vector, int index, int value,float uso);

void vector_double_capacity_if_full(Vector *vector);

int vector_size(Vector *vector);

int vector_ordenar(Vector *vector);

void encolar(Vector * cola, Vector *vector, int pid, Vector * nuevoVector);

void desencolar(Vector * cola, Vector *vector,Vector *nuevaCola);

void vector_free(Vector *vector);