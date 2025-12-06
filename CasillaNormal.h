//
// Created by santiago on 5/12/2025.
//
#ifndef CARRERA_AL_CENTRO_CASILLANORMAL_H
#define CARRERA_AL_CENTRO_CASILLANORMAL_H
#include "Casilla.h"


class CasillaNormal : public Casilla {
public:
    ///Constructor
    CasillaNormal(int fila, int columna);

    ///Indica que No es especial
    bool esEspecial() override;

    ///No hace nada al activar
    void activar(Jugador *jugador, int pvInicial) override;
};


#endif //CARRERA_AL_CENTRO_CASILLANORMAL_H