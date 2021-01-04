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

#include "producto.hpp"
#include "random.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Tabla_Hash {
  private:
    // Usar como tamanyo un numero primo cercano
    // a una  potencia de
    // 2. 16381 = 2^14 - 3
    int tamanyo = 16381;
    std::vector<int> T;
    std::vector<std::vector<Producto>> tabla_hash;
    // bool success;

  public:
    Tabla_Hash() {
        T = std::vector<int>(255);

        for (int n = 1; n <= 255; n++)
            T[n - 1] = n;

        std::shuffle(T.begin(), T.end(), gen);

        tabla_hash = std::vector<std::vector<Producto>>(tamanyo);
        for (int i = 0; i < tamanyo; i++)
            tabla_hash.push_back(std::vector<Producto>());
    }

    void insertar(Producto producto) {

        int posicion = funcion_dispersion(producto.nombre);
        tabla_hash[posicion].push_back(producto);
    }

    Producto buscar(std::string nombre, bool &success) {

        int posicion = funcion_dispersion(nombre);
        Producto aux;
        success = true;

        for (long unsigned int n = 0; n < tabla_hash[posicion].size(); n++) {
            aux = tabla_hash[posicion][n];

            if (aux.nombre == nombre)
                return aux;
        }
        success = false;
        return aux;
    }

    int funcion_dispersion(std::string nombre) {

        int h = 0;
        for (long unsigned int n = 0; n < nombre.length(); n++) {

            h = T[(h ^ nombre[n])];
        }

        return h % tamanyo;
    }
};
