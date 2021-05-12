#!/bin/bash

mkdir -p datos
cd datos
generador='../generar_datos'

for num_prods in 100 1000 5000 10000; do

    echo "Generando casos con $num_prods productos"

    $generador -num_casos 1 -num_prods $num_prods -prob 0.0
    $generador -num_casos 1 -num_prods $num_prods -prob 1.0
    $generador -num_casos 3 -num_prods $num_prods -prob 0.25
    $generador -num_casos 3 -num_prods $num_prods -prob 0.5
    $generador -num_casos 3 -num_prods $num_prods -prob 0.75

done
