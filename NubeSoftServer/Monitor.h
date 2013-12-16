#ifndef MONITOR_H_  /* Incluir restriccion */
#define MONITOR_H_
	int iniciarMonitoreoProceso(int pid);  
	void init_Monitor(int yMax,int yMin, int z);

	//infoProceso
	float infoTotalCpuLoad();	
	float infoProcessCpuLoad(int pid);

	//operacionProceso
	void eliminarProceso( int pid);
	void operacionProceso(int operacion, int pid);
#endif