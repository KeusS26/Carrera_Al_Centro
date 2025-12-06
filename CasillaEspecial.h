//
// Created by santiago on 5/12/2025.
//

#ifndef CARRERA_AL_CENTRO_CASILLAESPECIAL_H
#define CARRERA_AL_CENTRO_CASILLAESPECIAL_H
#include "Casilla.h"
#include "Dado.h"

enum class TipoEspecial{RECOMPENSA,CASTIGO};


class CasillaEspecial : public Casilla {
private:
    TipoEspecial tipo;
    bool revelada; ///Se conoce el tipo Despues de activarla
public:
    ///Constructor
    CasillaEspecial(int fila, int columna, TipoEspecial tipo);

    ///Identificacion
    bool esEspecial() override;

    ///Logica para crear la casilla
    void activar(Jugador *jugador) override;

    ///Consultar el tipo
    TipoEspecial getTipo();

};


#endif //CARRERA_AL_CENTRO_CASILLAESPECIAL_H