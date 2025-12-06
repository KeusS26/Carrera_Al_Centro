//
// Created by santiago on 5/12/2025.
//
#ifndef CARRERA_AL_CENTRO_CASILLA_H
#define CARRERA_AL_CENTRO_CASILLA_H
#include "Jugador.h"

class Casilla {
protected:
    int fila;
    int columna;
    bool descubierta;
public:
    ///Constructor
    Casilla(int fila, int columna);

    ///Metodos
    int getFila();
    int getColumna();

    bool fueDescubierta();
    void marcarDescubierta();

    ///Identificacion y los metodos sobre escritos
    virtual bool esEspecial();
    virtual void activar(Jugador* jugador) = 0;

};


#endif //CARRERA_AL_CENTRO_CASILLA_H