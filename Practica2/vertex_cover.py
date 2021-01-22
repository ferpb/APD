#!/usr/bin/env python
import sys
from ortools.linear_solver import pywraplp
import argparse
import time


def leer_entrada(fichero):

    with open(fichero, "r") as f:
        info = f.readline().split()
        num_vert = int(info[0])
        num_arist = int(info[1])
        aristas = []
        vertices = []

        for _ in range(0,  num_arist):
            arista = f.readline().split()
            aristas.append([int(arista[0]), int(arista[1])])

        for _ in range(0, num_vert):
            vertice = f.readline()
            vertices.append(float(vertice))

        return [aristas, vertices]


# Programación lineal

def wVC_relajacion(grafo):
    solver = pywraplp.Solver(
        'SolveSimpleSystem', pywraplp.Solver.GLOP_LINEAR_PROGRAMMING)

    variables = [None] * len(grafo[1])
    objective = solver.Objective()

    # Definicion de la funcion objetivo
    # min (sum(w_v * x_v)) donde v es un vertice del grafo.
    # Por cada vertice se crea una variable x_v

    for i in range(0, len(grafo[1])):
        variables[i] = solver.NumVar(0.0, solver.infinity(), str(i))
        objective.SetCoefficient(variables[i], grafo[1][i])

    objective.SetMinimization()

    # Definicion de la restriciones

    # Restriciones de las aristas
    # x(u) + x(v) >= 1
    for i in range(0, len(grafo[0])):
        arista = grafo[0][i]
        solver.Add(variables[arista[0]] + variables[arista[1]] >= 1.0)

    # Restriciones de los vertices
    # 0 <= x(v) <= 1
    for i in range(0, len(grafo[1])):
        solver.Add(0.0 <= variables[i] <= 1.0)

    status = solver.Solve()
    solucion = []
    sum = 0.0

    if status == solver.OPTIMAL:

        for i in range(0, len(grafo[1])):
            if(variables[i].solution_value() >= 0.5):
                sum = sum + grafo[1][i]
                solucion.append(i)

        return (sum, solucion)

    else:
        if status == solver.FEASIBLE:
            print('A potentially suboptimal solution was found.')
        else:
            print('The solver could not solve the problem.')


def wVC_entero(grafo):
    # Crear solver MIP utilizando SCIP como backend
    solver = pywraplp.Solver.CreateSolver('SCIP')

    variables = [None] * len(grafo[1])
    objective = solver.Objective()

    # Definicion de la funcion objetivo
    # min (sum(w_v * x_v)) donde v es un vertice del grafo.
    # Por cada vertice se crea una variable x_v
    for i in range(0, len(grafo[1])):
        variables[i] = (solver.IntVar(0, solver.infinity(), str(i)))
        objective.SetCoefficient(variables[i], grafo[1][i])

    objective.SetMinimization()

    # Definicion de la restriciones

    # Restriciones de las aristas
    # x(u) + x(v) >= 1
    for i in range(0, len(grafo[0])):
        arista = grafo[0][i]
        solver.Add(variables[arista[0]] + variables[arista[1]] >= 1.0)

    # Restriciones de los vertices
    # x(v) = {0, 1}
    for i in range(0, len(grafo[1])):
        solver.Add(0 <= variables[i] <= 1)

    status = solver.Solve()

    solucion = []

    if status == solver.OPTIMAL:
        for i in range(0, len(grafo[1])):
            if variables[i].solution_value() >= 1:
                solucion.append(i)

        return (solver.Objective().Value(), solucion)

    else:
        if status == solver.FEASIBLE:
            print('A potentially suboptimal solution was found.')
        else:
            print('The solver could not solve the problem.')


# Pricing method

def wVC_pricing_method(grafo):

    # Inicializamos los precios restantes con los pesos del grafo
    precios_restantes = grafo[1].copy()

    # Inicializar resultados
    sum = 0
    cubrimiento = []

    for arista in grafo[0]:

        i = arista[0]
        j = arista[1]

        if precios_restantes[i] == 0 or precios_restantes[j] == 0:
            # No se puede incrementar el precio de la arista
            continue

        if (precios_restantes[i] == precios_restantes[j]):
            # Los dos vértices se vuelven tight
            precios_restantes[i] = 0
            precios_restantes[j] = 0
            sum += grafo[1][i] + grafo[1][j]
            cubrimiento.append(i)
            cubrimiento.append(j)
        elif (precios_restantes[i] < precios_restantes[j]):
            # El vértice i se vuelve tight
            restar = precios_restantes[i]
            precios_restantes[i] = 0
            precios_restantes[j] -= restar
            sum += grafo[1][i]
            cubrimiento.append(i)
        else:
            # El vértice j se vuelve tight
            restar = precios_restantes[j]
            precios_restantes[i] -= restar
            precios_restantes[j] = 0
            sum += grafo[1][j]
            cubrimiento.append(j)

    return (sum, cubrimiento)


# Escribir el resultado

def escribir_resultado(fichero, grafo, tiempo, peso_cubrimiento, cubrimiento):
    with open(fichero, "w") as f:
        # num_vértices num_aristas peso_cubrimiento
        f.write(f"{len(grafo[1])} {len(grafo[0])} {peso_cubrimiento}\n")
        # vértices del cubrimiento separados por espacios
        f.write(f'{" ".join(map(str, cubrimiento))}\n')

    print(f"{peso_cubrimiento:.3f}, {end-start:.5f}", end=", ", flush=True)


if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description='Resolución de forma aproximada del problema de cobertura de vértices con pesos')

    parser.add_argument('fichero_entrada', metavar='entrada', type=str,
                        help='Fichero de entrada con el grafo a resolver')
    parser.add_argument('fichero_salida', metavar='salida', type=str,
                        help='Fichero de salida con el grafo a resolver')

    parser.add_argument('-r', '--relajacion-PL', action='store_true',
                        help='Utiliza la relajación de PL para resolver el problema')
    parser.add_argument('-p', '--pricing-method', action='store_true',
                        help='Utiliza el pricing method para resolver el problema')
    parser.add_argument('-e', '--PL-entera', action='store_true',
                        help='Utiliza PL entera para resolver el problema')

    args = parser.parse_args()

    grafo = leer_entrada(args.fichero_entrada)

    if args.relajacion_PL:
        start = time.time()
        (peso, cubrimiento) = wVC_relajacion(grafo)
        end = time.time()
        escribir_resultado(args.fichero_salida, grafo,
                           end-start, peso, cubrimiento)

    if args.pricing_method:
        start = time.time()
        (peso, cubrimiento) = wVC_pricing_method(grafo)
        end = time.time()
        escribir_resultado(args.fichero_salida, grafo,
                           end-start, peso, cubrimiento)

    if args.PL_entera:
        start = time.time()
        (peso, cubrimiento) = wVC_entero(grafo)
        end = time.time()
        escribir_resultado(args.fichero_salida, grafo,
                           end-start, peso, cubrimiento)

    print()
