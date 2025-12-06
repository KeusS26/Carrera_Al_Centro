cmake_minimum_required(VERSION 4.0)
project(Carrera_Al_Centro)

set(CMAKE_CXX_STANDARD 20)

add_executable(Carrera_Al_Centro main.cpp
        Jugador.cpp
        Jugador.h
        Dado.cpp
        Dado.h
        Casilla.cpp
        Casilla.h
        CasillaNormal.cpp
        CasillaNormal.h
        CasillaEspecial.cpp
        CasillaEspecial.h
        Tablero.cpp
        Tablero.h
        Juego.cpp
        Juego.h)
