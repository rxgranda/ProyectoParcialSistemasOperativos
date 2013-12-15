#ifndef MONITOR_H_  /* Incluir restriccion */
#define MONITOR_H_
	int iniciarMonitoreo(int pid);  /* An example function declaration */
	void init_Monitor(int yMax,int yMin, int z);
	float infoCpuLoad();
	void eliminarProceso( int pid);
	void operacionProceso(int operacion, int pid);
	float processCpuLoad(int pid);
#endif