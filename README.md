ProyectoParcialSistemasOperativos
=================================

NubeSoft, proyecto del primer parcial de Sistemas Operativos



Para ejecutar en la carpete NubeSoftServer:

1.- Ejecutar NubeSoftServer (Componente Servidor)

Compilación:
 gcc -o NubeSoftServer Main.c recursos/vector.c Monitor.c AdministradorProcesos.c InfoProcesos.c -pthread

Ejecución
 	./NubeSoftServer -M 60 -m 10 -z 1000
Parámetros:
	M: Porcentaje de carga promedio máxima de CPU para actuación del monitor
m: Porcentaje de carga promedio mínima de CPU para actuación del monitor
z: Intervalo [mseg] de Monitor

2.- Ejecutar NubeSoftClient (Componente Cliente)

Compilación:
gcc -o NubeSoftClient NubeSoftClient.c recursos/normal.c -lm
Ejecución
./NubeSoftClient -N 5 -o 3 -t 5

Parámetros:	

N: Número de solicitudes de ejecución generadas
o: Opción de simulación 

Valores posibles [1,2.3]
1: N procesos con 70% de tiempo para operaciones con el CPU

2:N/2 procesos con 80% de tiempo para operaciones con el CPU y N/2 procesos con 40% de tiempo para operaciones con el de uso del CPU.

3: N procesos x% de tiempo para operaciones con el CPU, donde x es un valor aleatorios extraído de la distribución normal N(65,10).

t: Tiempo de ejecución solicitudes clientes generadas [mseg]	




