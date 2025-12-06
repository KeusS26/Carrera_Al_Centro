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
    int columna;
    int cantidadEspeciales;

    //Matriz dinamica de Punteros a Casilla
    Casilla*** matriz;
public:
    ///Constructor
    Tablero(int fila, int columna);

    ///Accceso a Casillas
    Casilla* getCasilla(int fila,int columna);

    ///Mostrar tablero en consola
    void mostrar();

private:
    /// Metodos Privados
    void generarCasillas();
    void generarCasillasEspecialesAleatorias();

};


#endif //CARRERA_AL_CENTRO_TABLERO_H