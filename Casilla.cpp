//
// Created by santiago on 5/12/2025.
//

#include "Casilla.h"
#include "Jugador.h"

Casilla::Casilla(int fila, int columna) {
    this -> fila = fila;
    this -> columna = columna;
    this -> descubierta = false;
}

int Casilla::getFila() {
    return this -> fila;
}

int Casilla::getColumna() {
    return this -> columna;
}

bool Casilla::fueDescubierta() {
    return this -> descubierta;
}

void Casilla::marcarDescubierta() {
    descubierta = true;
}

bool Casilla::esEspecial() {
    return false; ///Por defecto no es especial la casiila normal
}


