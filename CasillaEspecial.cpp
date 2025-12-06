//
// Created by santiago on 5/12/2025.
//

#include "CasillaEspecial.h"

CasillaEspecial::CasillaEspecial(int fila, int columna, TipoEspecial tipo): Casilla(fila,columna) {
    this->fila = fila;
    this->columna = columna;
    this->tipo = tipo;
    this->revelada = false;
}

bool CasillaEspecial::esEspecial() {
    return true;
}

TipoEspecial CasillaEspecial::getTipo() {
    return tipo;
}

void CasillaEspecial::activar(Jugador *jugador, int pvInicial) {
    ///Marca la casilla Como descubierta
    this -> marcarDescubierta();

    Dado dado = Dado(pvInicial);
    int d = dado.Lanzar();

    std::cout << "Casilla especial activada en ("
              << fila << ", " << columna << ") Valor del dado: "
              << d << endl;

    if (tipo == TipoEspecial::CASTIGO) {
        ///Castigo le resta vida al jugador
        jugador -> restarPV(d);
        std::cout << "Castigo: -" << d << endl;
    } else {
        std::cout <<"RECOMEPENSA encontrada" << endl ;
        std::cout <<"1) Ganar "<< d <<" PV "<< endl;
        std::cout <<"2) Restar "<< d <<" PV de todos los otros jugadores"<< endl;

        int option;
        std::cin >> option;
        if (option == 1) {
            jugador -> agregarPv(d);
            std::cout << "Ganas " << d << "PV"<< endl;
        } else {
            /*Esta parte de la funcion se completa en la clase Juego ya que se
             *necesita manipular la clase jugadores para poder restar la vida de los otros
            */
            std::cout<< "Seleccionada la Opcion de dañar a otros jugadores. "<< endl;
        }
    }

}


