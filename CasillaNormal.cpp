//
// Created by santiago on 5/12/2025.
//

#include "CasillaNormal.h"

CasillaNormal::CasillaNormal(int fila, int columna): Casilla(fila, columna) {
    this -> fila = fila;
    this -> columna = columna;
}

///Indica que No es especial
bool CasillaNormal::esEspecial() {
    return  false;
}

///No hace nada al activar
void CasillaNormal::activar(Jugador *jugador) {
    /// Aqui no hace nada cuando el jugador cae en ella
}