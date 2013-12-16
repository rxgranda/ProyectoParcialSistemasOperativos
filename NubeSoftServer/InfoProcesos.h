#ifndef INFOPROCESOS_H_   /* Incluir restriccion */
#define INFOPROCESOS_H_

	void resumenGlobal();
	int resumenProceso(int pid, float cpu);
	int registrarCambioEstadoProceso(int opt,int pid);

#endif