//
// Created by JuanD on 6/12/2025.
//

#include "Juego.h"
#include <iostream>
#include <fstream>
#include <cstdlib>


Juego::Juego() {
    tablero = nullptr;
    pvInicial = 0;
    turnoActual = 0;
}


void Juego::menuPrincipal() {
    int opcion;

    do {
        std::cout << "\n=== MENU PRINCIPAL ===\n";
        std::cout << "1) Nuevo juego\n";
        std::cout << "2) Cargar partida\n";
        std::cout << "3) Salir\n";
        std::cout << "Elige: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1: iniciarNuevoJuego(); break;
            case 2: cargarPartida(); break;
            case 3: std::cout << "Saliendo...\n"; break;
            default: std::cout << "Opción inválida.\n";
        }
    } while (opcion != 3);
}

void Juego::iniciarNuevoJuego() {
    int dificultad;
    std::cout << "Seleccione dificultad:\n";
    std::cout << "1) Facil (15 PV)\n";
    std::cout << "2) Medio (23 PV)\n";
    std::cout << "3) Dificil (31 PV)\n";
    std::cin >> dificultad;

    crearTableroSegunDificultad(dificultad);

    int cantJug;
    std::cout << "Cantidad de jugadores (2-4): ";
    std::cin >> cantJug;

    crearJugadores(cantJug);

    cicloDeTurnos();
}



void Juego::crearTableroSegunDificultad(int opcion) {
    int f, c;

    if (tablero) delete tablero;

    switch(opcion) {
        case 1: pvInicial = 15; f = 15; c = 15; break;
        case 2: pvInicial = 23; f = 23; c = 23; break;
        case 3: pvInicial = 31; f = 31; c = 31; break;
        default: pvInicial = 15; f = 15; c = 15; break;
    }

    tablero = new Tablero(f, c);
}

void Juego::crearJugadores(int cantidad) {
    jugadores.clear();

    std::vector<std::pair<int,int>> esquinas = {
        {0, 0},
        {0, tablero->getColumnas() - 1},
        {tablero->getFilas() - 1, tablero->getColumnas() - 1},
        {tablero->getFilas() - 1, 0}
    };

    for (int i = 0; i < cantidad; i++) {
        std::string nombre;
        std::cout << "Nombre del jugador " << i + 1 << ": ";
        std::cin >> nombre;

        Jugador* j = new Jugador(nombre, pvInicial);

        j->setPosicion(esquinas[i].first, esquinas[i].second);

        jugadores.push_back(j);
    }
}


void Juego::cicloDeTurnos() {
    turnoActual = 0;

    while (!hayGanador()) {
        Jugador* j = jugadores[turnoActual];

        if (!j->estaEliminado())
            turnoJugador(j);

        turnoActual = (turnoActual + 1) % jugadores.size();
    }
}

void Juego::turnoJugador(Jugador* jugador) {
    std::cout << "\nTurno de " << jugador->getNombre()
              << " PV: " << jugador->getPv() << "\n";

    tablero->mostrar(jugadores);

    std::cout << "1) Lanzar Dados\n";
    std::cout << "2) Guardar partida\n";
    std::cout << "3) Rendirse\n";
    int op;
    std::cin >> op;

    if (op == 2) {
        guardarPartida();
        return;
    }

    if (op == 3) {
        jugador->restarPV(jugador->getPv()); // queda eliminado
        return;
    }

    Dado dado(6);
    int pasos = dado.Lanzar();

    std::cout << "Pasos obtenidos: " << pasos << "\n";
    std::cout << "Direccion (0=ARRIBA,1=ABAJO,2=IZQ,3=DER): ";
    int d;
    std::cin >> d;

    moverJugador(jugador, pasos, (Direccion)d);
}

void Juego::moverJugador(Jugador* jugador, int pasos, Direccion dir) {

    int f = jugador->getFila();
    int c = jugador->getColumna();

    switch (dir) {
        case Direccion::ARRIBA:    f -= pasos; break;
        case Direccion::ABAJO:     f += pasos; break;
        case Direccion::IZQUIERDA: c -= pasos; break;
        case Direccion::DERECHA:   c += pasos; break;
    }

    // ✅ limitar al tablero
    if (f < 0) f = 0;
    if (c < 0) c = 0;
    if (f >= tablero->getFilas()) f = tablero->getFilas() - 1;
    if (c >= tablero->getColumnas()) c = tablero->getColumnas() - 1;

    // ✅ RESTAR PV POR MOVIMIENTO
    jugador->restarPV(pasos);

    if (jugador->estaEliminado()) {
        std::cout << jugador->getNombre() << " se quedo sin PV.\n";
        return;
    }

    Casilla* destino = tablero->getCasilla(f, c);
    if (!destino) {
        std::cout << "Movimiento invalido.\n";
        return;
    }

    jugador->setPosicion(f, c);
    destino->activar(jugador, pvInicial);
}


bool Juego::hayGanador() const {
    int vivos = 0;

    for (auto j : jugadores)
        if (!j->estaEliminado())
            vivos++;

    return vivos <= 1;
}

void Juego::guardarPartida() {
    std::ofstream file("partidas.txt");

    file << jugadores.size() << "\n";
    file << pvInicial << "\n";

    for (auto j : jugadores) {
        file << j->getNombre() << " "
             << j->getPv() << " "
             << j->getFila() << " "
             << j->getColumna() << "\n";
    }

    std::cout << "Partida guardada.\n";
}

void Juego::cargarPartida() {
    std::ifstream file("partidas.txt");
    if (!file) {
        std::cout << "No hay partida guardada.\n";
        return;
    }

    int cant;
    file >> cant;
    file >> pvInicial;

    crearTableroSegunDificultad(1); // provisional

    for (auto j : jugadores) delete j;
    jugadores.clear();


    for (int i = 0; i < cant; i++) {
        std::string name;
        int pv, f, c;
        file >> name >> pv >> f >> c;

        Jugador* j = new Jugador(name, pvInicial);
        j->setPv(pv);
        j->setPosicion(f, c);

        jugadores.push_back(j);
    }

    std::cout << "Partida cargada.\n";

}
