#!/bin/bash

programa="./min_cut"
dirPruebas="pruebas"

for productos in $dirPruebas/productos*; do
    id=$(gsed -e 's/.*productos_//' <<< $productos)

    matriz="$dirPruebas"/matriz_"$id"

    echo $id
    echo "--------------------"

    echo "$programa -productos $productos -matriz $matriz -r 5"

    $programa -productos $productos -matriz $matriz -r 5

    echo
done
