/*********************************************************************************
 * Definicion de una estructura de datos tabla hash
 *
 * File: tabla_hash.hpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 7/12/2020
 * Coms: Algoritmia para Problemas Difíciles, 2020-2021
 **********************************************************************************/

#pragma once

#include <iostream>

struct Producto {

  public:
    std::string nombre;
    std::string atributos;

    Producto(std::string _nombre, std::string _atributos) : nombre(_nombre), atributos(_atributos){};
    Producto(){};
};