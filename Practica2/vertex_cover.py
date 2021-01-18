#!/usr/bin/env python
import sys
from ortools.linear_solver import pywraplp
import time


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


# Programación lineal

def MinWeightVC(grafo):
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

            # print(variables[i].solution_value())
            if(variables[i].solution_value() >= 0.5):
                sum = sum + grafo[1][i]
                solucion.append(i)

        # print(len(grafo[1]), ' ', len(grafo[0]), ' ', sum)
        # print(solucion)
        # print(sum)
        # print(solver.Objective().Value())
        return sum

    else:

        if status == solver.FEASIBLE:
            print('A potentially suboptimal solution was found.')
        else:
            print('The solver could not solve the problem.')


def wVC_entero(grafo):
    # print("\nEntero")
    # print("======")
    # print(grafo)

    # Crear solver MIP utilizando SCIP como backend
    # solver = pywraplp.Solver(
    #    'SolveSimpleSystem', pywraplp.Solver.SCIP_MIXED_INTEGER_PROGRAMMING)
    solver = pywraplp.Solver.CreateSolver('SCIP')

    variables = []
    objective = solver.Objective()

    # Definicion de la funcion objetivo
    # min (sum(w_v * x_v)) donde v es un vertice del grafo.
    # Por cada vertice se crea una variable x_v

    for i in range(0, len(grafo[1])):
        variables.append(solver.IntVar(0, solver.infinity(), str(i)))
        # print(variables[i])

        # print("Coeficiente", variables[i], grafo[1][i])

        objective.SetCoefficient(variables[i], grafo[1][i])

    objective.SetMinimization()

    # print('Number of variables', solver.NumVariables())

    # Definicion de la restriciones

    # Restriciones de las aristas
    # x(u) + x(v) >= 1
    for i in range(0, len(grafo[0])):
        arista = grafo[0][i]
        solver.Add(variables[arista[0]] + variables[arista[1]] >= 1.0)
        # print("Restriccion", variables[arista[0]], "+", variables[arista[1]])
        # print("Restriccion", arista[0], "+", arista[1])

    # Restriciones de los vertices
    # x(v) = {0, 1}
    for i in range(0, len(grafo[1])):
        solver.Add(0 <= variables[i] <= 1)

    # print('Number of constraints', solver.NumConstraints())

    status = solver.Solve()
    solucion = []

    sum = 0

    if status == solver.OPTIMAL:

        solucion = []

        # print('Solution:')
        # print('Objective value = ', solver.Objective().Value())
        for i in range(0, len(grafo[1])):
            # v = variables[i]
            # print(str(v), "=", v.solution_value())
            if variables[i].solution_value() >= 1:
                # sum = sum + grafo[1][i]
                solucion.append(i)

        # print(len(grafo[1]), ' ', len(grafo[0]),
        #       ' ', solver.Objective().Value())
        # print(solucion)
        # print(solver.Objective().Value())
        return solver.Objective().Value()
        # print(sum)
        # return sum

    else:

        if status == solver.FEASIBLE:
            print('A potentially suboptimal solution was found.')
        else:
            print('The solver could not solve the problem.')


# Pricing method

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


def incrementar_peso(pesos_aristas, num_arista, arista, grafo):

    resto_v1 = resto_vertice(pesos_aristas, arista[0], grafo)
    resto_v2 = resto_vertice(pesos_aristas, arista[1], grafo)
    pesos_aristas[num_arista] = min(resto_v1, resto_v2)


def PricingMethod2(grafo):

    pesos_aristas = []
    solucion = []
    sum = 0.0

    for _ in range(0, len(grafo[0])):
        pesos_aristas.append(0.0)

    for e in range(0, len(grafo[0])):
        arista = grafo[0][e]
        if((not is_tight(grafo, arista[0], pesos_aristas)) and (not is_tight(grafo, arista[1], pesos_aristas))):
            incrementar_peso(pesos_aristas, e, arista, grafo)

    for v in range(0, len(grafo[1])):
        if(is_tight(grafo, v, pesos_aristas)):
            sum = sum + grafo[1][v]
            solucion.append(v)

    # print(len(grafo[1]), ' ', len(grafo[0]), ' ', sum)
    # print(solucion)
    return sum


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

    arista, e = get_arista(grafo, pesos_aristas)

    while arista != []:

        incrementar_peso(pesos_aristas, e, arista, grafo)
        arista, e = get_arista(grafo, pesos_aristas)




    for v in range(0, len(grafo[1])):
        if is_tight(grafo, v, pesos_aristas):
            sum = sum + grafo[1][v]
            solucion.append(v)

    # print(len(grafo[1]), ' ', len(grafo[0]), ' ', sum)
    # print(solucion)
    # print(sum)
    return sum


def pricingMethod_mas_rapido(grafo):

    # Guardar tuplas (precio, arista)
    posibles_aristas = grafo[0].copy()

    vertices_justos = []
    precios_acumulados_vertices = [0] * len(grafo[1])

    # print()
    
    repe = 0
    while posibles_aristas != []:
        # print("\nVuelta")

        # Elegir la primera de la lista
        arista = posibles_aristas[0]

        # print("print arista elegida", arista)
        # print(grafo[1][arista[0]])
        # print(grafo[1][arista[1]])

        # Calcular cantidad a incrementar en los dos vértices de la arista
        incrementar = min(grafo[1][arista[0]] - precios_acumulados_vertices[arista[0]],
                          grafo[1][arista[1]] - precios_acumulados_vertices[arista[1]])

        # print("incrementar", incrementar)


        precios_acumulados_vertices[arista[0]] += incrementar
        precios_acumulados_vertices[arista[1]] += incrementar

        # Si alguno de los dos vértices es justo, añadirlo a la lista
        # y eliminar todas las aristas con ese vértice

        if precios_acumulados_vertices[arista[0]] >= grafo[1][arista[0]]:
            vertices_justos.append(arista[0])
            posibles_aristas[:] = [a for a in posibles_aristas if a[0] != arista[0] and a[1] != arista[0]]
            # Eliminar aristas que contienen ese vértice
                # print("Para u:",e)

            # for e in posibles_aristas:
                # if e[0] == arista[0] or e[1] == arista[0]:
                #     # eliminar de la lista posibles aristas
                #     posibles_aristas.remove(e)


        if precios_acumulados_vertices[arista[1]] >= grafo[1][arista[1]]:
            vertices_justos.append(arista[1])
            posibles_aristas[:] = [a for a in posibles_aristas if a[0] != arista[1] and a[1] != arista[1]]

        # print(vertices_justos)
        # print(precios_acumulados_vertices)
        # print("posibles aristas", posibles_aristas)

        # sys.exit(1)

        # if repe == 2:
            # sys.exit(1)
        
        repe += 1

        
    sum = 0
    for v in vertices_justos:
        sum += grafo[1][v]
    
    return sum

def pricingMethod_mucho_mas_rapido(grafo):

    # Guardar tuplas (precio, arista)
    vertices_justos = []
    precios_acumulados_vertices = [0] * len(grafo[1])

    for arista in grafo[0]:

        i = arista[0]
        j = arista[1]

        if precios_acumulados_vertices[i] == grafo[1][i] or precios_acumulados_vertices[j] == grafo[1][j]:
            continue

        # Calcular cantidad a incrementar en los dos vértices de la arista
        incrementar = min(grafo[1][i] - precios_acumulados_vertices[i],
                          grafo[1][j] - precios_acumulados_vertices[j])


        precios_acumulados_vertices[arista[0]] += incrementar
        precios_acumulados_vertices[arista[1]] += incrementar
        
    sum = 0
    for i in range(len(grafo[1])):
        if precios_acumulados_vertices[i] == grafo[1][i]:
            sum += grafo[1][i]
            vertices_justos.append(i)

    # vertices_justos.sort()
    # print()
    # print(vertices_justos)
    
    return sum
    
def pricingMethod(grafo):

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
    
    # cubrimiento.sort()
    # print()
    # print(cubrimiento)
    return sum


if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("Uso: vertex_cover fichero")
        exit(1)

    grafo=leer_entrada(sys.argv[1])

    # print("Grafo:", grafo)

    # # print("LP entero")
    # start = time.time()
    # res = wVC_entero(grafo)
    # end = time.time()
    # # print("tiempo:", end - start)
    # print(f"{res:.3f}, {end-start:.5f}", end=", ")

    # print("LP relajado")
    start=time.time()
    res=MinWeightVC(grafo)
    end=time.time()
    # print("tiempo:", end - start)
    print(f"{res:.3f}, {end-start:.5f}", end=", ", flush=True)

    # # print("Pricing method")
    # start=time.time()
    # # res = PricingMethod_bueno(grafo)
    # res=PricingMethod_bueno(grafo)
    # end=time.time()
    # # print("tiempo:", end-start)
    # print(f"{res:.3f}, {end-start:.5f}", end=", ", flush=True)

    # # print("Pricing method")
    # start=time.time()
    # # res = PricingMethod_bueno(grafo)
    # res=pricingMethod_mas_rapido(grafo)
    # end=time.time()
    # # print("tiempo:", end-start)
    # print(f"{res:.3f}, {end-start:.5f}", end=", ", flush=True)

    # # print("Pricing method")
    # start=time.time()
    # # res = PricingMethod_bueno(grafo)
    # res=pricingMethod_mucho_mas_rapido(grafo)
    # end=time.time()
    # # print("tiempo:", end-start)
    # print(f"{res:.3f}, {end-start:.5f}", end=", ", flush=True)

    # print("Pricing method")
    start=time.time()
    # res = PricingMethod_bueno(grafo)
    res=pricingMethod(grafo)
    end=time.time()
    # print("tiempo:", end-start)
    print(f"{res:.3f}, {end-start:.5f}")

