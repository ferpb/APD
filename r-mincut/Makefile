#*****************************************************************
# File:   Makefile
# Author: Daniel Subías Sarrato (NIA: 759533)
#	      Fernando Peña Bes (NIA: 756012)
# Date:   diciembre 2020
# Coms:   Ejecutar "make" para compilar (o "make -f Makefile")
#         Ejecutar "make clean" para limpiar (borrar lo que genere)
#*****************************************************************

CC=g++
CPPFLAGS=-std=c++11 -Wall -O3
SRC=src

all: min_cut $(FILE)

##linkar
min_cut: min_cut.o random.o 
	$(CC) $(CPPFLAGS) $(LDFLAGS) random.o min_cut.o -o min_cut 

generar_datos: generar_datos.o random.o
	$(CC) $(CPPFLAGS) $(LDFLAGS) random.o $(SRC)/generar_datos.cpp -o generar_datos

##compilar
generar_datos.o: $(SRC)/generar_datos.cpp $(SRC)/random.hpp
	$(CC) $(CPPFLAGS) $(SRC)/generar_datos.cpp -c

random.o: $(SRC)/random.cpp $(SRC)/random.hpp
	$(CC) $(CPPFLAGS) $(SRC)/random.cpp -c

min_cut.o: $(SRC)/min_cut.cpp $(SRC)/tabla_hash.hpp $(SRC)/grafo.hpp
	$(CC) $(CPPFLAGS) $(SRC)/min_cut.cpp -c

##borrar
clean:
	rm -rf *o $(FILE)
