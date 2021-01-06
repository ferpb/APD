# Práctica 1 LEEME
 * Peña Bes, Fernando   756012@unizar.es    a756012
 * Subías Sarrato, Jose Daniel  759533@unizar.es    a759533

## Fichero principal

El programa principal de la práctia corresponde con el fichero `src/min_cut.cpp`. 
En el pueden econtrarse las implementaciones de losaalgoritmos de `Karger`, `KargerStein` y la version de `Karger` con seleccion de aristas por pesos.
Para la ejecución del programa debe utilizarse el sigueinte comando:

    ./min -productos <fichero_prods> -matriz <fichero_matriz> -r <valor_r>
      
 * `<fichero_prods>` : indica el path del fichero donde se guarda la lista de productos y su informacion.
 * `<fichero_matriz>` : indica el path del fichero que alamcena la matriz que representa el grafo.
 * `<valor_r>` : indica el número de conjuntos r a generar.

### Ficheros auxiliares
En el directorio src tambien pueden encontrarse lo ficheros `generar_datos.cpp` usado para la generacion de datos, `grafo.hpp` donde se define la estrutura grafo utilizada, `producto.hpp` que especifica el tipo de dato producto, `random.cpp` y `random.hpp` que continen la libreria de generadores aleatorios utilizada y `tabla_hash.hpp` donde se define la estrutura tabla hash usada para almacenar los productos. 