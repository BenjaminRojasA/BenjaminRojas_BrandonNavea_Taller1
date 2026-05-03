#ifndef CANCION_HPP
#define CANCION_HPP

#include <iostream>
#include <string>
using namespace std;

class cancion {
private:
    int id;
    string nombre;
    string artista;
    string album;
    string año;
    string duracion;
    string ubicacion;

public:
    cancion();
    cancion(int id, string nombre, string artista, string album, string año,string duracion, string ubicacion);
};
#endif CANCION_HPP