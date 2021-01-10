#!/usr/bin/env python

import argparse
import random
import itertools


# Formato del fichero;
#
#   num_vertices num_aristas
#   vertice vertice
#   vertice vertice
#   vertice vertice
#   ... (num_aristas líneas)
#   peso
#   peso
#   peso
#   ... (num_vertices líneas)
def generar(fichero, num_vertices, densidad, pesos):

    vertices = set([v for v in range(num_vertices)])

    aristas = set()

    # Combinaciones sin repeticiones de los vértices
    for combination in itertools.combinations(vertices, 2):
        if random.uniform(0, 1) < densidad:
            aristas.add(combination)

    # generar pesos vértices
    pesos = [round(random.uniform(pesos[0], pesos[1]), 2)
             for _ in range(num_vertices)]

    # escribir fichero
    fichero.write("%d %d\n" % (len(vertices), len(aristas)))
    for arista in aristas:
        fichero.write("%d %d\n" % (arista[0], arista[1]))
    for peso in pesos:
        fichero.write("%.2f\n" % peso)


if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description='Generación de grafos aleatorios')
    parser.add_argument('-v', '--num-vertices', type=int,
                        default=1, help='Número de nodos')
    parser.add_argument('-d', '--densidad', type=float,
                        default=1, help='Densidad del grafo (entre 0 y 1)')
    parser.add_argument('-p', '--pesos_vertices', type=int, nargs=2,
                        default=[0, 1], help='Intervalo de los pesos de los vértices')
    parser.add_argument('-f', '--fichero', type=str, required=True,
                        help='Fichero de salida')

    args = parser.parse_args()

    with open(args.fichero, "w") as fichero:
        generar(fichero, args.num_vertices, args.densidad, args.pesos_vertices)
