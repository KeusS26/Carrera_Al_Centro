//
// Created by keuss on 5/12/2025.
//
#include "Dado.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Constructor
Dado::Dado(int valorMax) {
    this->valorMax = valorMax;
    srand(time(nullptr)); //Esto es para inicializar (Solo se usa una vez)
}

//Metodos
int Dado::Lanzar() {
    return 1 + rand() % valorMax;
}

//Getters
int Dado::getValorMax() {
    return this->valorMax;
}