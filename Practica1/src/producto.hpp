/*********************************************************************************
 * Definicion de una estructura de datos tabla hash
 *
 * File: tabla_hash.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 7/12/2020
 * Coms: Algoritmia para Problemas Difíciles, 2020-2021
 **********************************************************************************/

#include <iostream>

struct Producto {

  public:
    std::string nombre;
    int cantidad;
    float precio;

    Producto(std::string _nombre, int _cantidad, float _precio) : nombre(_nombre), cantidad(_cantidad), precio(_precio){};
    Producto(){};
};