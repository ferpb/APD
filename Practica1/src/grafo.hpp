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

    bool operator==(const Arista &a) {
        return this->dest == a.dest && this->src == a.src;
    };
};

inline std::ostream &operator<<(std::ostream &out, const Arista &a) {
    out << "(" << a.src << "," << a.dest << ")";
    return out;
};

struct Grafo {

    // Numero de aristas
    std::vector<Arista> aristas;
    // Lista de conjuntos de nodos para guardar la traza
    std::vector<std::string> conjuntos;
    // Matriz de adyacencia
    std::vector<std::vector<short int>> matriz_adj;
    int num_vertices, init_num_nodes, num_aristas;

    Grafo(){};
    Grafo(std::vector<Arista> _aristas,
          std::vector<std::string> _conjuntos,
          std::vector<std::vector<short int>> _matriz_adj,
          int _num_vertices,
          int _num_aristas)
        : aristas(_aristas), conjuntos(_conjuntos), matriz_adj(_matriz_adj),
          num_vertices(_num_vertices), init_num_nodes(_num_vertices), num_aristas(_num_aristas){};

    void contraer_arista(const Arista arista) {

        conjuntos[arista.src] = conjuntos[arista.src] + "-" + conjuntos[arista.dest];
        conjuntos[arista.dest] = "";
        for (int i = 0; i < init_num_nodes; i++) {
            matriz_adj[arista.src][i] = matriz_adj[arista.src][i] + matriz_adj[arista.dest][i];
        }

        for (int i = 0; i < init_num_nodes; i++) {
            matriz_adj[arista.dest][i] = -1;
        }

        matriz_adj[arista.src][arista.src] = 0;
        matriz_adj[arista.src][arista.dest] = 0;

        for (int i = 0; i < init_num_nodes; i++) {
            if (conjuntos[i] != "" && i != arista.src) {
                matriz_adj[i][arista.src] = matriz_adj[i][arista.src] + matriz_adj[i][arista.dest];
                matriz_adj[i][arista.dest] = 0;
            }
        }
        num_vertices--;
        eliminar_arista(arista);
    }

    void eliminar_arista(const Arista arista) {

        aristas.erase(std::remove(aristas.begin(), aristas.end(), arista),
                      aristas.end());

        aristas.erase(std::remove(aristas.begin(), aristas.end(), Arista(arista.dest, arista.src)),
                      aristas.end());
        for (Arista &a : aristas) {

            if (a.src == arista.dest)
                a.src = arista.src;
            else if (a.dest == arista.dest)
                a.dest = arista.src;
        }
        aristas.erase(std::unique(aristas.begin(), aristas.end()), aristas.end());
        num_aristas = aristas.size();
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

    void ver_aristas() {

        for (const Arista &a : aristas)
            std::cout << a << std::endl;
    };

    int get_cut() {
        int acum = 0, posicion = 0;

        while (conjuntos[posicion] == "") {

            posicion++;
        }

        for (int i = 0; i < init_num_nodes; i++) {

            acum += matriz_adj[posicion][i];
        }
        ver_aristas();
        return acum;
    }

    Arista get_prob_arista() {

        int acum = 0, count = 0, random;
        std::vector<Arista> aristas_unique = aristas;
        aristas_unique.erase(std::unique(aristas_unique.begin(), aristas_unique.end()), aristas_unique.end());
        std::vector<int> grados_acumulados(aristas_unique.size());
        for (const Arista &a : aristas_unique) {

            acum += matriz_adj[a.src][a.dest];
            grados_acumulados[count] = acum;
            count++;
        }
        random = random_int(0, acum);

        for (unsigned long int i = 0; i < aristas.size(); i++) {

            if (random < grados_acumulados[i])
                return aristas_unique[i];
        }

        return Arista();
    }
};