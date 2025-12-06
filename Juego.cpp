//
// Created by JuanD on 6/12/2025.
//

#include "Juego.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

std::string nombreDireccion(Direccion d) {
    switch (d) {
        case Direccion::ARRIBA: return "ARRIBA";
        case Direccion::ABAJO: return "ABAJO";
        case Direccion::IZQUIERDA: return "IZQUIERDA";
        case Direccion::DERECHA: return "DERECHA";
        default: return "DESCONOCIDA";
    }
}

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

    //  Mostrar ganador
    Jugador* ganador = obtenerGanador();
    if (ganador) {
        std::cout << "\n=============================\n";
        std::cout << " EL GANADOR ES: " << ganador->getNombre() << " 🎉\n";
        std::cout << "PV restantes: " << ganador->getPv() << "\n";
        std::cout << "=============================\n";
    }
}

Jugador* Juego::obtenerGanador(){
    for (auto j : jugadores) {
        if (!j->estaEliminado())
            return j;
    }
    return nullptr;
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

    if (op == 1) {
        moverJugador(jugador);
    }
    else if (op == 2) {
        guardarPartida();
    }
    else if (op == 3) {
        jugador->restarPV(jugador->getPv()); // se elimina
    }
}


void Juego::moverJugador(Jugador* jugador) {

    struct Opcion {
        Direccion dir;
        int pasos;
    };

    std::vector<Opcion> opciones;

    // Dados: uno por dirección
    Dado dado(6);
    int dArriba    = dado.Lanzar();
    int dAbajo     = dado.Lanzar();
    int dIzquierda = dado.Lanzar();
    int dDerecha   = dado.Lanzar();

    int f = jugador->getFila();
    int c = jugador->getColumna();
    int pv = jugador->getPv();

    // ARRIBA
    if (dArriba < pv && f - dArriba >= 0)
        opciones.push_back({Direccion::ARRIBA, dArriba});

    // ABAJO
    if (dAbajo < pv && f + dAbajo < tablero->getFilas())
        opciones.push_back({Direccion::ABAJO, dAbajo});

    // IZQUIERDA
    if (dIzquierda < pv && c - dIzquierda >= 0)
        opciones.push_back({Direccion::IZQUIERDA, dIzquierda});

    // DERECHA
    if (dDerecha < pv && c + dDerecha < tablero->getColumnas())
        opciones.push_back({Direccion::DERECHA, dDerecha});

    // Regla 2: ninguna válida
    if (opciones.empty()) {
        std::cout << "No hay movimientos validos. Pierdes el turno.\n";
        return;
    }

    // Mostrar opciones
    std::cout << "Movimientos validos:\n";
    for (size_t i = 0; i < opciones.size(); i++) {
        std::cout << i << ") ";

        switch (opciones[i].dir) {
            case Direccion::ARRIBA:    std::cout << "ARRIBA"; break;
            case Direccion::ABAJO:     std::cout << "ABAJO"; break;
            case Direccion::IZQUIERDA: std::cout << "IZQUIERDA"; break;
            case Direccion::DERECHA:   std::cout << "DERECHA"; break;
        }

        std::cout << " (" << opciones[i].pasos << " pasos)\n";
    }

    // Regla 3: solo una opción
    int eleccion = 0;
    if (opciones.size() > 1) {
        std::cin >> eleccion;
    }

    Direccion dir = opciones[eleccion].dir;
    int pasos = opciones[eleccion].pasos;

    // Ejecutar movimiento paso a paso
    for (int i = 0; i < pasos; i++) {

        if (jugador->getPv() <= 0) {
            return;
        }

        int nf = jugador->getFila();
        int nc = jugador->getColumna();

        switch (dir) {
            case Direccion::ARRIBA:    nf--; break;
            case Direccion::ABAJO:     nf++; break;
            case Direccion::IZQUIERDA: nc--; break;
            case Direccion::DERECHA:   nc++; break;
        }

        jugador->setPosicion(nf, nc);
        jugador->restarPV(1);
    }

    // Activar casilla final
    Casilla* destino = tablero->getCasilla(
        jugador->getFila(),
        jugador->getColumna()
    );

    if (destino)
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

    if (!file.is_open()) {
        std::cout << "Error al abrir el archivo para guardar.\n";
        return;
    }

    file << jugadores.size() << "\n";
    file << pvInicial << "\n";

    for (auto j : jugadores) {
        file << j->getNombre() << " "
             << j->getPv() << " "
             << j->getFila() << " "
             << j->getColumna() << "\n";
    }

    file.close(); //  MUY IMPORTANTE
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

    crearTableroSegunDificultad(1); // luego se puede mejorar

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

    file.close();
    std::cout << "Partida cargada.\n";

    cicloDeTurnos(); //  IMPORTANTE
}


