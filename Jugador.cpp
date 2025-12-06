//
// Created by keuss on 5/12/2025.
//
#include "Jugador.h"
#include <iostream>
using namespace std;
/// Constructor
Jugador::Jugador(){}

Jugador::Jugador(string n, int pvIni)
    : nombre(n), pv(pvIni), fila(0), columna(0) {}

/// Moetodos de Vida
void Jugador::restarPV(int cantidad) {
    if (this -> eliminado) {
        return;
    }
    pv -= cantidad;
    if (pv <= 0) {
        eliminado = true;
    }
}

void Jugador::agregarPv(int cantidad) {
    if (this -> eliminado) {
        return;
    }
    pv += cantidad;
}


bool Jugador::estaEliminado() {
    return eliminado;
}


///Setter
void Jugador::setPosicion(int fila, int Columna) {
    this -> fila = fila;
    this -> columna = Columna;
}

///Getter
string Jugador::getNombre() {
    return this -> nombre;
}

int Jugador::getIdJugador() {
    return this -> idJugador;
}

int Jugador::getPv() {
    return this -> pv;
}

int Jugador::getFila() {
    return this -> fila;
}

int Jugador::getColumna() {
    return this -> columna;
}

bool Jugador::getEliminado() {
    return this -> eliminado;
}

void Jugador::setPv(int pv) {
    this -> pv = pv;
}