//
// Created by keuss on 5/12/2025.
//

#ifndef CARRERA_AL_CENTRO_JUGADOR_H
#define CARRERA_AL_CENTRO_JUGADOR_H
#include <iostream>
using namespace std;

enum class Direccion {ARRIBA,ABAJO,IZQUIERDA,DERECHA};

class Jugador {
private:
    string nombre;
    int idJugador{};
    int pv{};
    int fila{};
    int columna{};
    bool eliminado{};
public:
    /// Constructor
    Jugador();
    Jugador(string nombre, int idJugador);

    /// Moetodos de Vida
    void restarPV(int cantidad);
    void agregarPv(int cantidad);
    bool estaEliminado();

    ///Setter
    void setPosicion(int fila, int Columna);
    void setPv(int pv);

    ///Getter
    string getNombre();
    int getIdJugador();
    int getPv();
    int getFila();
    int getColumna();
    bool getEliminado();
};


#endif //CARRERA_AL_CENTRO_JUGADOR_H