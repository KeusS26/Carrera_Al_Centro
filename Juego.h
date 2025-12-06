//
// Created by JuanD on 6/12/2025.
//

#ifndef CARRERA_AL_CENTRO_JUEGO_H
#define CARRERA_AL_CENTRO_JUEGO_H
//Creado Por Juan // 06 diciembre 2025

#include "Tablero.h"
#include "Jugador.h"
#include "Dado.h"
#include <vector>
#include <string>

class Juego {
private:
    Tablero* tablero;
    std::vector<Jugador*> jugadores;
    int pvInicial;
    int turnoActual;

public:
    Juego();


    void menuPrincipal();

private:
    void iniciarNuevoJuego();
    void cargarPartida();
    void guardarPartida();

    void crearJugadores(int cantidad);
    void crearTableroSegunDificultad(int opcion);

    void cicloDeTurnos();
    void turnoJugador(Jugador* jugador);
    Jugador* obtenerGanador();


    void moverJugador(Jugador* jugador);

    bool hayGanador() const;

};


#endif //CARRERA_AL_CENTRO_JUEGO_H