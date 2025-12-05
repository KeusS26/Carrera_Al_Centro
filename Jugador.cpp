//
// Created by keuss on 5/12/2025.
//
#include "Jugador.h"
#include <iostream>
using namespace std;
/// Constructor
Jugador::Jugador(){}
Jugador::Jugador(string nombre, int idJugador) {
    this -> nombre = nombre;
    this -> idJugador = idJugador;
    this -> pv = 0;
    this -> fila = 0;
    this -> columna = 0;
    this -> eliminado = false;
}

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

///Movimiento
void Jugador::Mover(Direccion dir,int pasos) {
    if (this -> eliminado) {
        return;
    }
    for (int i = 0; i < pasos; i++) {
        if (pv <= 0) {
            eliminado = true;
            break;
        }
        switch (dir) {
            case Direccion::ARRIBA:
                fila--;
                break;
            case Direccion::ABAJO:
                fila++;
                break;
            case Direccion::IZQUIERDA:
                columna--;
                break;
            case Direccion::DERECHA:
                columna++;
                break;
        }
        pv--;
        if (pv <= 0) {
            eliminado = true;
            break;
        }
    }
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