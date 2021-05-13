# Cobertura de Vértices

## Ejecución
Lo más sencillo es utilizar un entorno virtual e instalarlos ahí.

### Preparar el entorno virtual

En Python hay diferentes alternativas para trabajar con entornos virtuales.
Nosotros hemos elegido `venv`, que es la manera recomendada de crear entornos
virtuales desde Python 3.6.

Estos son los pasos para usar `venv`: 

1. Ir al directorio raíz del proyecto y crear el entorno mediante el siguiente comando:

        python3 -m venv env

2. A continuación, activarlo:

        source env/bin/activate

3. Por último, instalar los paquetes requeridos en el entorno:

        pip3 install -r requirements.txt

Para desactivar el entorno se puede usar `deactivate`.

### Ejecutar el programa

	python3 vertex_cover.py [-h] [-r] [-p] [-e] entrada salida

El programa toma como entrada un fichero con la descripción de un grafo
cuyos vértices tienen asignados un peso, con el formato descrito en el
guión de la práctica:

> Cada ítem debe estar en un línea diferente:
> 1. El número de vértices y el número de aristas separados por espacio o
tabulador (los vértices para un grafo con *n* vértices se identifican con los
enteros {0,1,...,*n*−1});
> 2. una línea para cada arista con los dos extremos de la arista en orden
arbitrario separados por espacio o tabulador;
> 3. una línea para cada vértice con el peso del vértice.

Mediante las opciones `-r` (problema de programación lineal relajado), `-p`
(*pricing method*) y `-e` (programación lineal entera) se puede seleccionar
el método para resolver el problema de wVC sobre el grafo de entrada.

Como salida, se produce un fichero con dos líneas. La primera
contiene el número de vértices del grafo, el número de aristas del grafo, y
el peso del cubrimiento encontrado. En la segunda se escriben los vértices
del cubrimiento calculado separados por espacios.

Además, se escribe por salida estándar el peso del cubrimiento y el tiempo de
ejecución, para poder tener un registro de los resultados a la hora de
realizar pruebas.

### Ejecutar las pruebas automáticas
Se ha creado un script que se encarga de ejecutar pruebas con distintos grafos de manera automática, se puede ejecutar de la siguiente forma:
	
	./ejecutar_pruebas.sh
