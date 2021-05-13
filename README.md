# r-min cut y Cobertura de Vértices
* Autor: Fernando Peña Bes
* Autor: José Daniel Subías Sarrato

*Algoritmia para Problemas Difíciles- Universidad de Zaragoza, curso 2020-21*

# Descripción
Este repositorio contiene:

1. La implementación de un programa para la resolución del problema del **r-min cut**. Dicho problema es resuelto con la temática de un reestructuración de la multinacional Amazon en **r** sub-tiendas. Los algoritmos implementados para resolver el problema entre son: 
    * Karger
    * Karger-Stein
    * Karger con seleccion de aristas por pesos

    Todo el código de la implementación puede encontrarse en la carpeta [r-mincut](r-mincut) en lenguaje **C++**. La explicación detallada con el desarrollo matemático, así como las pruebas de eficiencia realizadas pueden verse en el [informe](r-mincut/Memoria.pdf) correspondiente.

2. La resolución de forma aproximada del problema de Cobertura de Vértices con pesos (wVC) mediante dos métodos diferentes: Programación Lineal y *Pricing Method*. Ambos métodos son una 2-aproximación del problema original. La implementación del primer método utiliza la API **OR-Tools**, mientras la del segundo segunda es una implementación de caracter propio. El código puede encontrarse en la carpeta [vertex-cover](vertex-cover), está programado en lenguaje **Python**. En el [informe](vertex-cover/Memoria.pdf) sometido puede verse el análisis desarrollado en base a las pruebas de eficiciencia realizadas.
