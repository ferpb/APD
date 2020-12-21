/*********************************************************************************
 * Generar datos de prueba aleatorio
 *
 * File: random.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 7/12/2020
 * Coms: Algoritmia para Problemas Difíciles, 2020-2021
 **********************************************************************************/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "random.hpp"

#define MAX_NOMBRE 20
#define MAX_UNIDADES 1000
#define MAX_PRECIO 9999

#define FICHERO_PRODUCTOS "productos"
#define FICHERO_MATRIZ "matriz"
#define EXT_FICHERO ".txt"

// Genera <num_prods> productos aleatorios
bool generar_productos(std::string fichero, int num_prods) {
    std::ofstream os(fichero, std::ios::out);
    if (!os.is_open()) {
        return false;
    }

    for (int i = 0; i < num_prods; i++) {
        os << random_string(random_int(1, MAX_NOMBRE))
           << "\t" << random_int(1, MAX_UNIDADES)
           << "\t" << std::fixed << std::setprecision(2) << random_float(0.01, MAX_PRECIO) << std::endl;
    }

    return true;
}

// Genera una matriz de adyacencia aleatorio para <num_prods> productos
// Cada pareja de productos tienen probabilidad <prob> de estar conectados
bool generar_matriz(std::string fichero, int num_prods, float prob) {
    std::ofstream os(fichero, std::ios::out);
    if (!os.is_open()) {
        return false;
    }

    os << num_prods << std::endl;
    for (int i = 0; i < num_prods; i++) {
        for (int j = 0; j < num_prods; j++) {
            if (i == j) {
                os << "0";
            } else {
                random_float() < prob ? os << "1" : os << "0";
            }
            j == num_prods - 1 ? os << "\n" : os << " ";
        }
    }

    return true;
}

float get_valor_arg(int argc, char **argv, int i, float default_value) {
    float value = default_value;
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        std::cout << "Falta el valor de la opción " << argv[i] << std::endl;
        exit(1);
    }
    try {
        value = std::stof(argv[i + 1]);
    } catch (std::invalid_argument const &e) {
        std::cout << "El valor de la opción debe ser un número: " << argv[i + 1];
        exit(1);
    }
    return value;
}

std::string generar_nombre_fichero(std::string prefijo, int num_prods, float prob, int indice, std::string ext) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << prob;
    std::string p = stream.str();

    std::replace(p.begin(), p.end(), '.', '-');

    return prefijo + "_" + std::to_string(num_prods) + "_" + p + "_" + std::to_string(indice) + ext;
}

int main(int argc, char **argv) {
    int num_casos = 0;
    int num_prods = 0;
    float prob = 0.5;

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-' && arg == "-num_casos") {
            num_casos = get_valor_arg(argc, argv, i, 1);
            i++;
        } else if (arg[0] == '-' && arg == "-num_prods") {
            num_prods = get_valor_arg(argc, argv, i, 1);
            i++;
        } else if (arg[0] == '-' && arg == "-prob") {
            prob = get_valor_arg(argc, argv, i, 0.5);
            i++;
        }
    }

    for (int i = 0; i < num_casos; i++) {
        generar_productos(generar_nombre_fichero(FICHERO_PRODUCTOS, num_prods, prob, i, EXT_FICHERO), num_prods);
        generar_matriz(generar_nombre_fichero(FICHERO_MATRIZ, num_prods, prob, i, EXT_FICHERO), num_prods, prob);
    }
    return 0;
}