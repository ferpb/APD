#!/usr/bin/env python
import sys
from ortools.linear_solver import pywraplp


def leer_entrada(ficheroDeEntrada):

    with open(ficheroDeEntrada) as f:
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


def MinWeightVC(grafo):
    solver = pywraplp.Solver(
        'SolveSimpleSystem', pywraplp.Solver.GLOP_LINEAR_PROGRAMMING)

    variables = [[]] * len(grafo[1])
    objective = solver.Objective()

    # Definicion de la funcion objetivo
    # min (sum(w_v * x_v)) donde v es un vertice del grafo.
    # Por cada vertice se crea una variable x_v

    for i in range(0, len(grafo[1])):
        variables[i] = solver.NumVar(0.0, solver.infinity(), str(i))
        objective.SetCoefficient(variables[i], grafo[1][i])
    objective.SetMinimization()

    # Definicio de la restriciones

    # Restriciones de las aristas
    for i in range(0, len(grafo[0])):
        arista = grafo[0][i]
        solver.Add(variables[arista[0]] + variables[arista[1]] >= 1.0)

    # Restriciones de los vertices
    for i in range(0, len(grafo[1])):
        solver.Add(0.0 <= variables[i] <= 1.0)

    status = solver.Solve()
    solucion = []
    sum = 0.0

    if status == solver.OPTIMAL:

        for v in range(0, len(grafo[1])):

            if(variables[v].solution_value() >= 0.5):
                sum = sum + grafo[1][v]
                solucion.append(v)

        print(len(grafo[1]), ' ', len(grafo[0]), ' ', sum)
        print(solucion)

    else:

        if status == solver.FEASIBLE:
            print('A potentially suboptimal solution was found.')
        else:
            print('The solver could not solve the problem.')


def acum_vertice(pesos_aristas, vertice, grafo):

    acum = 0.0
    for v in range(0, len(grafo[0])):

        arista = grafo[0][v]
        if(arista[0] == vertice or arista[1] == vertice):
            acum = acum + pesos_aristas[v]
    return acum


def resto_vertice(pesos_aristas, vertice, grafo):

    return grafo[1][vertice] - acum_vertice(pesos_aristas, vertice, grafo)


def is_tight(grafo, vertice, pesos_aristas):
    w_i = grafo[1][vertice]
    acum = acum_vertice(pesos_aristas, vertice, grafo)
    return w_i == acum


def incremetar_peso(pesos_aristas, num_arista, arista, grafo):

    resto_v1 = resto_vertice(pesos_aristas, arista[0], grafo)
    resto_v2 = resto_vertice(pesos_aristas, arista[1], grafo)
    pesos_aristas[num_arista] = min(resto_v1, resto_v2)


def PricingMethod(grafo):

    pesos_aristas = []
    solucion = []
    sum = 0.0

    for _ in range(0, len(grafo[0])):
        pesos_aristas.append(0.0)

    for e in range(0, len(grafo[0])):
        arista = grafo[0][e]
        if((not is_tight(grafo, arista[0], pesos_aristas)) and (not is_tight(grafo, arista[1], pesos_aristas))):
            incremetar_peso(pesos_aristas, e, arista, grafo)

    for v in range(0, len(grafo[1])):
        if(is_tight(grafo, v, pesos_aristas)):
            sum = sum + grafo[1][v]
            solucion.append(v)

    print(len(grafo[1]), ' ', len(grafo[0]), ' ', sum)
    print(solucion)


def get_arista(grafo, pesos_aristas):

    for e in range(0, len(grafo[0])):
        arista = grafo[0][e]
        if((not is_tight(grafo, arista[0], pesos_aristas)) and (not is_tight(grafo, arista[1], pesos_aristas))):
            return grafo[0][e], e
    return [], -1


def PricingMethod_bueno(grafo):

    pesos_aristas = []
    solucion = []
    sum = 0.0

    for _ in range(0, len(grafo[0])):
        pesos_aristas.append(0.0)

    arista,  e = get_arista(grafo, pesos_aristas)

    while arista != []:

        incremetar_peso(pesos_aristas, e, arista, grafo)
        arista,  e = get_arista(grafo, pesos_aristas)

    for v in range(0, len(grafo[1])):
        if(is_tight(grafo, v, pesos_aristas)):
            sum = sum + grafo[1][v]
            solucion.append(v)

    print(len(grafo[1]), ' ', len(grafo[0]), ' ', sum)
    print(solucion)


# grafo[0] representa el conjunto de aristas
# grafo[1] representa el conjunto de vertices
grafo = leer_entrada(sys.argv[1])
MinWeightVC(grafo)
PricingMethod_bueno(grafo)
