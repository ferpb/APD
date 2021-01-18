#!/bin/bash

dir_pruebas='pruebas'
generador='python3 ../generar_pruebas.py'

mkdir -p $dir_pruebas
cd $dir_pruebas

for num_vertices in 100 250 500 1000 2000 5000; do

    echo "Generando casos con $num_vertices vértices"

    for densidad in 0.0 1.0 0.25 0.5 0.75; do
        echo "  densidad $densidad"
        densidad_fichero=$(echo $densidad | tr "." "-")
        ${generador} -v $num_vertices -d $densidad -p 0 100 -f "${num_vertices}_${densidad_fichero}_prueba.txt"
    done

    # ${generador} -v $num_prods -p 0 1000 -d 0.0 -f "${num_vertices}_0-0_prueba.txt"
    # ${generador} -v $num_prods -p 0 1000 -d 1.0 -f "${num_vertices}_1-0_prueba.txt"
    # ${generador} -v $num_prods -p 0 1000 -d 0.25 -f "${num_vertices}_0-25_prueba.txt"
    # ${generador} -v $num_prods -p 0 1000 -d 0.5 -f "${num_vertices}_0-5_prueba.txt"
    # ${generador} -v $num_prods -p 0 1000 -d 0.75 -f "${num_vertices}_0-75_prueba.txt"

done
