/*********************************************************************************
 * Programa principal
 *
 * File: min_cut.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 7/12/2020
 * Coms: Algoritmia para Problemas Difíciles, 2020-2021
 **********************************************************************************/

#include "random.hpp"
#include "tabla_hash.hpp"
#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Tabla_Hash leer_productos(std::string fichero) {

    Tabla_Hash T;
    Producto producto;
    std::string nombre, atributos;
    std::ifstream in(fichero, std::ios::in);

    if (!in.is_open())
        throw "Error al abrir fichero " + fichero;

    while (!in.eof()) {

        std::getline(in, nombre, '\t');
        std::getline(in, atributos, '\n');
        producto = Producto(nombre, atributos);
        T.insertar(producto);
    }

    return T;
};

std::vector<bool> lee_matriz(std::string fichero) {

    std::vector<bool> matriz;
    std::ifstream in(fichero, std::ios::in);
    std::string num_prods;

    int tamanyo, aux;
    if (!in.is_open())
        throw "Error al abrir fichero " + fichero;
    std::getline(in, num_prods);
    tamanyo = std::stoi(num_prods) * std::stoi(num_prods);
    matriz = std::vector<bool>(tamanyo);

    for (int i = 0; i < tamanyo; i++) {

        in >> aux;
        matriz[i] = (bool)aux;
    }

    return matriz;
}

std::string get_valor_arg(int argc, char **argv, int i, std::string default_value) {
    std::string value = default_value;
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        std::cout << "Falta el valor de la opción " << argv[i] << std::endl;
        exit(1);
    }

    value = argv[i + 1];

    return value;
}

void read_args(int argc, char **argv, std::string &path_matriz, std::string &path_productos) {

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-' && arg == "-productos") {
            path_productos = get_valor_arg(argc, argv, i, "");
            i++;
        } else if (arg[0] == '-' && arg == "-matriz") {
            path_matriz = get_valor_arg(argc, argv, i, "");
            i++;
        }
    }
}

void Karger(std::vector<bool> &graph, int r) {

    int num_vertices = std::sqrt(graph.size());

    while (num_vertices > r) {
    }
}

int main(int argc, char **argv) {

    std::string path_productos, path_matriz;
    Tabla_Hash tabla_hash;
    std::vector<bool> matriz;

    read_args(argc, argv, path_matriz, path_productos);

    try {
        tabla_hash = leer_productos(path_productos);
        matriz = lee_matriz(path_matriz);
    } catch (std::string s) {
        std::cout << s << std::endl;
    }
}