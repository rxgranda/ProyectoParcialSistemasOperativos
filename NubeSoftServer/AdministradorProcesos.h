
#ifndef ADMINISTRADOR_H_   /* Include guard */
#define ADMINISTRADOR_H_

// Define a vector type
typedef struct {
  int pid;      // ID de Proceso Cliente
  char* estado;  // Estado de Proceso 
} Cliente;

int iniciarClienteSimulado(int perc_cpu,int max_time,int N);
//void* iniciarClienteSimulado(void * param);
int estadoProcesoCliente();
int enviarSenialProceso();

#endif