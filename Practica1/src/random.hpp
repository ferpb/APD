/*********************************************************************************
 * Random number generation functions 
 *
 * File: random.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 7/12/2020
 * Coms: Algoritmia para Problemas Difíciles, 2020-2021
 **********************************************************************************/

#pragma once

#include <random>

// Devuelve un número real entre 0 y 1
float random_float();

// Devuelve un número real entre 0 y <n>
float random_float(float n);

// Devuelve un número real entre <min> y <max>
float random_float(float min, float max);

// Devuelve un número entero entre 0 y 1
int random_int();

// Devuelve un número entero entre 0 y <n>
int random_int(float n);

// Devuelve un número entero entre <min> y <max>
int random_int(float min, float max);

// Devuelve una cadena aleatoria con <size> caracteres
std::string random_string(int size);