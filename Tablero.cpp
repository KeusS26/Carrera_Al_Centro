//
// Created by santiago on 6/12/2025.
//

#include "Tablero.h"
#include  <iostream>
#include  <ctime>

Tablero::Tablero(int filas, int columnas) {
    this -> filas= filas;
    this -> columnas = columnas;

    //Generar porcaentaje de casillas especiales
    int total = filas * columnas;
    int minimo = total * 0.06;
    int maximo = total * 0.10;

    std::srand(std::time(nullptr));
    cantidadEspeciales = minimo + (std::rand() % (maximo - minimo + 1));

    ///Crear una Matriz Dinamica
    matriz = new Casilla **[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new Casilla*[columnas];
    }

    generarCasillas();
    generarCasillasEspecialesAleatorias();

}

void Tablero::generarCasillasEspecialesAleatorias() {
    int generadas = 0;

    while (generadas < cantidadEspeciales) {
        int f = std::rand() % filas;
        int c = std::rand() % columnas;

        /// Si la Casilla no es Especial, la hacemos Especial
        if (!matriz[f][c] -> esEspecial()) {
            TipoEspecial tipo;

            /// %50 Especial, %50 Castigo
            if (std::rand() % 2 == 0) {
                tipo = TipoEspecial::RECOMPENSA;
            } else {
                tipo = TipoEspecial::CASTIGO;
            }
            delete matriz[f][c];
            matriz[f][c] = new CasillaEspecial(f,c,tipo);
            generadas++;
        }
    }
}

Casilla* Tablero::getCasilla(int filas, int columnas){
    if (filas < 0 || filas >= filas || columnas < 0 || columnas >= columnas) {
        return nullptr;
    }
    return matriz[filas][columnas];
}

void Tablero::mostrar() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (matriz[i][j] -> esEspecial()) {
                if (matriz[i][j] -> fueDescubierta()) {
                    std::cout << "[E]";
                } else {
                    std::cout << "[?]";
                }
            } else {
                std::cout << "[.]";
            }
        }
        std::cout << std::endl;
    }
}