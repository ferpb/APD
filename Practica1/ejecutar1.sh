#!/bin/bash
make

# programa que se va a probar
programa="./min_cut"

# directorio en el que se encuentran las pruebas
dirPruebas="pruebas"
# valor de r con el que se realizan las pruebas
r=5

for productos in $dirPruebas/productos*; do
    id=$(gsed -e 's/.*productos_//' <<< $productos)

    matriz="$dirPruebas"/matriz_"$id"

    echo $id
    echo "--------------------"

    echo "$programa -productos $productos -matriz $matriz -r $r"

    $programa -productos $productos -matriz $matriz -r $r

    echo
done
