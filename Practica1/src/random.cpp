/*********************************************************************************
 * Random number generation functions 
 *
 * File: random.cpp
 * Author: Fernando Peña (NIA: 756012)
 * Author: Jose Daniel Subias Sarrato (NIA: 759533)
 * Date: 7/12/2020
 * Coms: Algoritmia para Problemas Difíciles, 2020-2021
 **********************************************************************************/

#include "random.hpp"

static thread_local std::random_device rd;                                   // obtain a random number from hardware
static thread_local std::mt19937 gen(rd());                                  // seed the generator
static thread_local std::uniform_real_distribution<float> distr(0.0f, 1.0f); // define the range

float random_float() {
    return distr(gen);
}

float random_float(float n) {
    return n * distr(gen);
}

float random_float(float min, float max) {
    return (max - min) * distr(gen) + min;
}

int random_int() {
    return distr(gen);
}

int random_int(float n) {
    return n * distr(gen);
}

int random_int(float min, float max) {
    return (max - min) * distr(gen) + min;
}

std::string random_string(int size) {
    char alphanum[] = "abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMOPQRSTUVWXYZ1234567890";

    std::string s = "";
    for (int i = 0; i < size; i++) {
        s += alphanum[random_int(sizeof(alphanum) - 1)];
    }

    return s;
}