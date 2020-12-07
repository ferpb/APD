# Práctica 1

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

El fichero fichero de la matriz de adyacencia contiene los siguientes datos:

    <num_prods>
    <matriz_adyacencia>

La matriz de adyacencia es una matriz booleanos, simétrica y de dimensión
`<num_prods>x<num_prods>`. Los valores de las columnas aparecen separados por
espacios y las filas, por saltos de línea. Cada posición _(i, j)_ de la
matriz contiene el carácter `1` si los productos _i_ y _j_ han sido comprados
juntos alguna vez, y `0` en el caso contrario.
