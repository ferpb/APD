#!/bin/bash

programa="./min_cut"
# dirPruebas="pruebas-cortas"

# $1 directorio en el que están las pruebas
# $2 r con el que se realizan las pruebas

dirPruebas=$1

for productos in $dirPruebas/productos*; do
    id=$(gsed -e 's/.*productos_//' <<< $productos)

    matriz="$dirPruebas"/matriz_"$id"

    echo $id
    echo "--------------------"

    echo "$programa -productos $productos -matriz $matriz -r $2"

    $programa -productos $productos -matriz $matriz -r 5

    echo
done
