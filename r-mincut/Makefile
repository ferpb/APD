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
FILE=generar_datos
SRC=src

all: min_cut $(FILE)

##linkar
min_cut: min_cut.o random.o 
	$(CC) $(CPPFLAGS) $(LDFLAGS) random.o min_cut.o -o min_cut 

$(FILE): $(FILE).o random.o
	$(CC) $(CPPFLAGS) $(LDFLAGS) random.o $(SRC)/$(FILE).cpp -o $(FILE)

##compilar
$(FILE).o: $(SRC)/$(FILE).cpp $(SRC)/random.hpp
	$(CC) $(CPPFLAGS) $(SRC)/$(FILE).cpp -c

random.o: $(SRC)/random.cpp $(SRC)/random.hpp
	$(CC) $(CPPFLAGS) $(SRC)/random.cpp -c

min_cut.o: $(SRC)/min_cut.cpp $(SRC)/tabla_hash.hpp $(SRC)/grafo.hpp
	$(CC) $(CPPFLAGS) $(SRC)/min_cut.cpp -c

##borrar
clean:
	rm -rf *o $(FILE)
