/*********************************************************************************
 * Programa principal
 *
 * File: min_cut.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 7/12/2020
 * Coms: Algoritmia para Problemas Difíciles, 2020-2021
 **********************************************************************************/

#include "grafo.hpp"
#include "random.hpp"
#include "tabla_hash.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
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

void mostrar_matrix(const std::vector<std::vector<short int>> &matriz) {

    int n = matriz.size();

    for (int i = 0; i < n; i++) {

        for (int m = 0; m < n; m++) {

            std::cout << matriz[i][m];
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<short int>> lee_matriz(std::string fichero) {

    std::ifstream in(fichero, std::ios::in);
    std::string num_prods;
    int tamanyo;
    short int aux;
    if (!in.is_open())
        throw "Error al abrir fichero " + fichero;

    std::getline(in, num_prods);
    tamanyo = std::stoi(num_prods);
    std::vector<std::vector<short int>> matriz(tamanyo, std::vector<short int>(tamanyo));

    for (int i = 0; i < tamanyo; i++) {

        for (int m = 0; m < tamanyo; m++) {
            in >> aux;
            matriz[i][m] = aux;
        }
    }

    return matriz;
}

void hacer_simetrica(std::vector<std::vector<short int>> &matriz_adj, int n) {

    for (int i = 0; i < n; i++) {

        for (int m = 0; m < n; m++) {

            if (matriz_adj[i][m] == 1)
                matriz_adj[m][i] = 1;
        }
    }
}
std::vector<Arista> get_aristas(const std::vector<std::vector<short int>> &matriz_adj, int n) {

    std::vector<Arista> aristas;

    for (int i = 0; i < n; i++) {

        for (int m = i + 1; m < n; m++) {

            if (matriz_adj[i][m] == 1)
                aristas.push_back(Arista(i, m));
        }
    }

    return aristas;
}

void crear_conjuntos(std::vector<std::string> &conjuntos, int n) {

    for (int i = 0; i < n; i++) {
        conjuntos[i] = std::to_string(i);
    }
}

Grafo crear_grafo(std::string fichero) {

    std::vector<std::vector<short int>> matriz_adj = lee_matriz(fichero);
    std::vector<Arista> aristas;
    // Representa el numero de aristas en el grafo
    int m;
    // Representa el numero de nodos en el grafo
    int n = matriz_adj.size();
    std::vector<std::string> conjuntos(n, "");

    hacer_simetrica(matriz_adj, n);
    aristas = get_aristas(matriz_adj, n);
    crear_conjuntos(conjuntos, n);

    m = aristas.size();
    //show_matrix(matriz_adj);
    std::cout << "Grafo creado:" << std::endl;
    std::cout << "* Numero de nodos:" << n << std::endl;
    std::cout << "* Numero de aristas:" << m << std::endl;

    Grafo grafo(aristas, conjuntos, matriz_adj, n, m);

    return grafo;
};

std::string get_valor_arg(int argc, char **argv, int i, std::string default_value) {
    std::string value = default_value;
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        std::cout << "Falta el valor de la opción " << argv[i] << std::endl;
        exit(1);
    }

    value = argv[i + 1];

    return value;
}

int get_valor_arg(int argc, char **argv, int i, int default_value) {

    int value = default_value;
    if (i + 1 >= argc || argv[i + 1][0] == '-') {
        throw "Falta el valor de la opción r";
    }
    if (!(std::string(argv[i + 1]) == "r")) {

        value = std::stoi(argv[i + 1]);
    } else
        throw "La opcion r debe ser un entero";
    return value;
}

void read_args(int argc, char **argv, std::string &path_matriz, std::string &path_productos, int &r) {

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg[0] == '-' && arg == "-productos") {
            path_productos = get_valor_arg(argc, argv, i, "");
            i++;
        } else if (arg[0] == '-' && arg == "-matriz") {
            path_matriz = get_valor_arg(argc, argv, i, "");
            i++;
        } else if (arg[0] == '-' && arg == "-r") {
            r = get_valor_arg(argc, argv, i, 2);
            i++;
        }
    }
}

void contraer_r(Grafo &grafo, int r) {
    int ran;
    Arista ran_arista;
    while (grafo.num_vertices > r) {
        ran = random_int(0, grafo.num_aristas - 1);
        ran_arista = grafo.aristas[ran];
        grafo.contraer_arista(ran_arista);
    }
}

void contraer_r_probs(Grafo &grafo, int r) {

    Arista ran_arista;
    while (grafo.num_vertices > r) {

        ran_arista = grafo.get_prob_arista();
        grafo.contraer_arista(ran_arista);
    }
}

int Karger(Grafo &grafo, int r, int k) {
    Grafo grafo2;
    int cut = std::numeric_limits<int>::max();

    for (int i = 0; i < k; i++) {
        grafo2 = grafo;
        contraer_r(grafo2, r);
        cut = std::min(grafo2.get_cut(), cut);
    }
    return cut;
}

int KargerProbsAristas(Grafo &grafo, int r, int k) {
    Grafo grafo2;
    int cut = std::numeric_limits<int>::max();

    for (int i = 0; i < k; i++) {
        grafo2 = grafo;
        contraer_r_probs(grafo2, r);
        cut = std::min(grafo2.get_cut(), cut);
    }
    return cut;
}

int KargerStein(Grafo &grafo, int r) {

    Grafo grafo2;
    int t;
    if (grafo.num_vertices <= 6) {
        contraer_r(grafo, r);
        return grafo.get_cut();

    } else if (grafo.num_vertices != r) {
        grafo2 = grafo;
        t = 1.0f + (float)grafo.num_vertices / std::sqrt(2.0f);
        contraer_r(grafo, std::max(r, t));
        contraer_r(grafo2, std::max(r, t));
        return std::min(KargerStein(grafo, r), KargerStein(grafo2, r));
    } else {
        return grafo.get_cut();
    }
}

int main(int argc, char **argv) {

    std::string path_productos, path_matriz;
    Tabla_Hash tabla_hash;
    Grafo grafo;
    int r;
    unsigned timepo_antes, tiempo_despues;

    try {
        read_args(argc, argv, path_matriz, path_productos, r);
        tabla_hash = leer_productos(path_productos);
        std::cout << "Creando grafo..." << std::endl;
        grafo = crear_grafo(path_matriz);
    } catch (std::string s) {
        std::cout << s << std::endl;
    }
    timepo_antes = clock();
    int cut = Karger(grafo, r, 1);
    tiempo_despues = clock();
    std::cout << "Corte: " << cut << std::endl;
    std::cout << "Tiempo Karger: " << (float(timepo_antes - tiempo_despues) / CLOCKS_PER_SEC) << std::endl;
    timepo_antes = clock();
    cut = KargerProbsAristas(grafo, r, 1);
    tiempo_despues = clock();
    std::cout << "Corte: " << cut << std::endl;
    std::cout << "Tiempo KargerProbs: " << (float(timepo_antes - tiempo_despues) / CLOCKS_PER_SEC) << std::endl;
    timepo_antes = clock();
    cut = KargerStein(grafo, r);
    tiempo_despues = clock();
    std::cout << "Corte: " << cut << std::endl;
    std::cout << "Tiempo Karger Stein: " << (float(timepo_antes - tiempo_despues) / CLOCKS_PER_SEC) << std::endl;
}