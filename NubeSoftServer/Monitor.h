#ifndef MONITOR_H_   /* Include guard */
#define MONITOR_H_

 

int iniciarMonitoreo(int pid);  /* An example function declaration */
void init_Monitor(int yMax,int yMin, int z);
float infoCpuLoad(int pid);
void operacionProceso(int operacion, int pid);

#endif