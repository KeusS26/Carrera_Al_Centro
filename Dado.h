//
// Created by keuss on 5/12/2025.
//
#ifndef CARRERA_AL_CENTRO_DADO_H
#define CARRERA_AL_CENTRO_DADO_H
#include <iostream>
using namespace std;

class Dado {
private:
    int valorMax;

public:
    //Constructor
    Dado(int valorMax);

    //Metodos
    int Lanzar();

    //Getters
    int getValorMax();
};


#endif //CARRERA_AL_CENTRO_DADO_H