/*********************************************************************************
 * Estrutura de datos que representa un grafo
 *
 * File: random.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 7/12/2020
 * Coms: Algoritmia para Problemas Difíciles, 2020-2021
 **********************************************************************************/

#pragma once

#include "random.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Arista {

    short int src, dest;

    Arista(){};

    Arista(short int _src, short int _dest) : src(_src), dest(_dest) {}
};

inline std::ostream &operator<<(std::ostream &out, const Arista &a) {
    out << "(" << a.src << "," << a.dest << ")";
    return out;
};

struct Grafo {

    std::vector<Arista> aristas;
    std::vector<std::string> conjuntos;
    std::vector<std::vector<short int>> matriz_adj;
    int num_vertices;
    int num_aristas;

    Grafo(){};
    Grafo(std::vector<Arista> _aristas,
          std::vector<std::string> _conjuntos,
          std::vector<std::vector<short int>> _matriz_adj,
          int _num_vertices,
          int _num_aristas)
        : aristas(_aristas), conjuntos(_conjuntos), matriz_adj(_matriz_adj),
          num_vertices(_num_vertices), num_aristas(_num_aristas){};

    void contraer_arista(const Arista arista, int position) {

        conjuntos[arista.src] = conjuntos[arista.src] + "-" + conjuntos[arista.dest];
        conjuntos[arista.dest] = "";

        for (int i = 0; i < num_vertices; i++) {
            matriz_adj[arista.src][i] = matriz_adj[arista.src][i] + matriz_adj[arista.dest][i];
        }

        matriz_adj[arista.src][arista.src] = 0;
        matriz_adj[arista.src][arista.dest] = 0;

        for (int i = 0; i < num_vertices; i++) {
            if (conjuntos[i] != "" && i != arista.src) {
                matriz_adj[i][arista.src] = matriz_adj[i][arista.src] + matriz_adj[i][arista.dest];
                matriz_adj[i][arista.dest] = 0;
            }
        }

        eliminar_arista(arista, position);
    }

    void eliminar_arista(const Arista arista, int position) {

        aristas.erase(aristas.begin() + position);
        for (Arista &a : aristas) {

            if (a.src == arista.dest)
                a.src = arista.src;

            if (a.dest == arista.dest)
                a.dest = arista.src;
        }

        num_aristas--;
    }

    void ver_conjuntos() {

        int count = 1;
        for (const std::string &conjunto : conjuntos) {
            if (conjunto != "") {
                std::cout << "{" << count << "} = " << conjunto << std::endl;
                count++;
            }
        }
    }
};