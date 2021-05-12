# r-min cut y Covertura de Vértices
* Autor: Fernando Peña Bes
* Autor: José Daniel Subías Sarrato

*Algoritmia para Problemas Difíciles- Universidad de Zaragoza, curso 2020-21*

# Descripción
Este repositorio contiene:

1. La implementación de un programa para la resolución del problema del **r-min cut**. Dicho problema es resuelto con la temática de un regmentación de la multinacional Amazón en **r** sub-tiendas. Los algoritmos implementados para resolver el problemas entre los que se puede elegir son: 
    * `Karger`.
    * `KargerStein`.
    * `Karger` con seleccion de aristas por pesos.

    Todo el código de la implementación puede encontrarse en la carpeta [r-mincut](r-mincut) en lenguaje **C++**. La explicación detallada con todo el desarrollo matemático, así como la pruebas de eficiencia realizadas pueden verse en el [Informe](r-mincut/Memoria.pdf) correspondiente.

2. La implementación del algoritomo de Covertura de Vértices resuelto mediante dos implementaciones: Covertura de Vértices con pesos mediante `Programación Lineal` y `Pricing Method`. La primera implmentación utiliza la API **OR-Tools**, mientras que la segunda es una implementación de caracter propio. Todo el código de la implementación puede encontrarse en la carpeta [vertex-cover](vertex-cover) en lenguaje **python**. En el [Informe](vertex-cover/Memoria.pdf) sometido puede verse el análisis desarrollado en base a las pruebas de eficiciencia realizadas.

# r-min cut

## Ejeución
Para la ejecución del programa debe utilizarse el sigueinte comando:

    ./min -productos <fichero_prods> -matriz <fichero_matriz> -r <valor_r>
      
 * `<fichero_prods>` : indica el path del fichero donde se guarda la lista de productos y su informacion.
 * `<fichero_matriz>` : indica el path del fichero que alamcena la matriz que representa el grafo.
 * `<valor_r>` : indica el número de conjuntos r a generar.

## Ficheros auxiliares
En el directorio src tambien pueden encontrarse lo ficheros `generar_datos.cpp` usado para la generacion de datos, `grafo.hpp` donde se define la estrutura grafo utilizada, `producto.hpp` que especifica el tipo de dato producto, `random.cpp` y `random.hpp` que continen la libreria de generadores aleatorios utilizada y `tabla_hash.hpp` donde se define la estrutura tabla hash usada para almacenar los productos. 

## Generación de datos de prueba
Los datos de prueba se han generado de manera aleatoria en C++. Como
generador pseudo-aleatorio, se ha utilizando el algoritmo Mersenne Twister
con 19937 bits (`std::mt19937`). El generador se ha inicializado con una
semilla producida por un generador de números aleatorios no determinista
(`std::random_device`).

Se han generado _n_ instancias, en las que se ha ido variando el número de
productos y la probabilidad de que dos productos cualesquiera hayan sido
comprados juntos alguna vez.

Al aumentar el número de productos, aumenta el número de vértices del grafo,
y conforme aumenta la probabilidad, aumenta el número de aristas (el grafo es
más denso). El máximo número de aristas que puede tener un grafo con _k_
vértices es _k * (k - 1) / 2_.

### Nombres de los ficheros
Por cada instancia del problema hay dos ficheros, uno contiene los productos
y otro, la matriz de adyacencia. Sus nombres tienen el siguiente formato:

    productos_<num_prods>_<prob>_<instancia>.txt

    matriz_<num_prods>_<prob>_<instancia>.txt

El valor `<num_prods>` indica el número de productos que contiene la
instancia, `<prob>` es la probabilidad de que dos productos aparezcan
conectados en la matriz de adyacencia e `<instancia>` es el número de la
instancia generada con los parámetros anteriores.

### Contenidos de los ficheros
El fichero de productos contiene `<num_prods>` líneas con el siguiente formato:

    <ID_producto> <cantidad> <precio>
    ...

El valor `<ID_producto>` contiene una cadena aleatoria de entre 1 y 20
caracteres, que puede servir para identificar el producto. <cantidad> es el
número de unidades disponibles del producto (entre 1 y 1000), y `<precio>` es
un valor real con dos cifras de precisión que representa su precio (entre
0.01 y 9999).

El fichero de la matriz de adyacencia contiene los siguientes datos:

    <num_prods>
    <matriz_adyacencia>

La matriz de adyacencia es una matriz booleanos, simétrica y de dimensión
`<num_prods>x<num_prods>`. Los valores de las columnas aparecen separados por
espacios y las filas, por saltos de línea. Cada posición _(i, j)_ de la
matriz contiene el carácter `1` si los productos _i_ y _j_ han sido comprados
juntos alguna vez, y `0` en el caso contrario.

## Generación de datos de prueba
Los datos de prueba se han generado de manera aleatoria en C++. Como
generador pseudo-aleatorio, se ha utilizando el algoritmo Mersenne Twister
con 19937 bits (`std::mt19937`). El generador se ha inicializado con una
semilla producida por un generador de números aleatorios no determinista
(`std::random_device`).

Se han generado _n_ instancias, en las que se ha ido variando el número de
productos y la probabilidad de que dos productos cualesquiera hayan sido
comprados juntos alguna vez.

Al aumentar el número de productos, aumenta el número de vértices del grafo,
y conforme aumenta la probabilidad, aumenta el número de aristas (el grafo es
más denso). El máximo número de aristas que puede tener un grafo con _k_
vértices es _k * (k - 1) / 2_.

### Nombres de los ficheros
Por cada instancia del problema hay dos ficheros, uno contiene los productos
y otro, la matriz de adyacencia. Sus nombres tienen el siguiente formato:

    productos_<num_prods>_<prob>_<instancia>.txt

    matriz_<num_prods>_<prob>_<instancia>.txt

El valor `<num_prods>` indica el número de productos que contiene la
instancia, `<prob>` es la probabilidad de que dos productos aparezcan
conectados en la matriz de adyacencia e `<instancia>` es el número de la
instancia generada con los parámetros anteriores.

### Contenidos de los ficheros
El fichero de productos contiene `<num_prods>` líneas con el siguiente formato:

    <ID_producto> <cantidad> <precio>
    ...

El valor `<ID_producto>` contiene una cadena aleatoria de entre 1 y 20
caracteres, que puede servir para identificar el producto. <cantidad> es el
número de unidades disponibles del producto (entre 1 y 1000), y `<precio>` es
un valor real con dos cifras de precisión que representa su precio (entre
0.01 y 9999).

El fichero de la matriz de adyacencia contiene los siguientes datos:

    <num_prods>
    <matriz_adyacencia>

La matriz de adyacencia es una matriz booleanos, simétrica y de dimensión
`<num_prods>x<num_prods>`. Los valores de las columnas aparecen separados por
espacios y las filas, por saltos de línea. Cada posición _(i, j)_ de la
matriz contiene el carácter `1` si los productos _i_ y _j_ han sido comprados
juntos alguna vez, y `0` en el caso contrario.

# Covertura de Vértices

## Ejeución
Lo más sencillo es utilizar un entorno virtual e instalarlos ahí.

### Preparar el entorno virtual

En Python hay diferentes alternativas para trabajar con entornos virtuales.
Nosotros hemos elegido `venv` que es la manera recomendada de crear entornos
virtuales desde Python 3.6.

Estos son los pasos para usar `venv`: 

1. Ir al directorio raíz del proyecto y crear el entorno mediante el siguiente comando:

        python3 -m venv practica2_env

2. A continuación, activarlo:

        source practica2_env/bin/activate

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
enteros {0, 1, . . . , *n* − 1});
> 2. una línea para cada arista con los dos extremos de la arista en orden
arbitrario separados por espacio o tabulador;
> 3. una línea para cada vértice con el peso del vértice.

Mediante las opciones `-r` (problema de programación lineal relajado), `-p`
(*pricing method*) y `-e` (programación lineal entera) se puede seleccionar
el método para resolver el problema de wVC sobre el grafo de entrada.

Como salida, se produce un fichero de salida con dos líneas. La primera
contiene el número de vértices del grafo, el número de aristas del grafo, y
el peso del cubrimiento encontrado. En la segunda se escriben los vértices
del cubrimiento calculado separados por espacios.

Además, se escribe por salida estándar el peso del cubrimiento y el tiempo de
ejecución, para poder tener un registro de los resultados a la hora de
realizar pruebas.

### Ejecutar las pruebas automáticas
Se ha creado un script que se encarga de ejecutar pruebas con distintos grafos de manera automática, se puede ejecutar de la siguiente forma:
	
	./ejecutar2.sh

