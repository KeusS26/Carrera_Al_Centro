//
// Created by santiago on 6/12/2025.
//
#ifndef CARRERA_AL_CENTRO_TABLERO_H
#define CARRERA_AL_CENTRO_TABLERO_H
#include "Casilla.h"
#include "CasillaNormal.h"
#include "CasillaEspecial.h"
#include <cstdlib>

class Tablero {
private:
    int filas;
    int columnas;
    int cantidadEspeciales;

    //Matriz dinamica de Punteros a Casilla
    Casilla*** matriz;

public:
    ///Constructor
    Tablero(int filas, int columnas);

    ///Accceso a Casillas
    Casilla* getCasilla(int filas,int columnas);

    ///Mostrar tablero en consola
    void mostrar();

private:
    /// Metodos Privados
    void generarCasillas();
    void generarCasillasEspecialesAleatorias();

};


#endif //CARRERA_AL_CENTRO_TABLERO_H