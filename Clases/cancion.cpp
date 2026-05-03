#include "cancion.hpp"

cancion::cancion(int id, string nombre, string artista, string album, string año, string duracion, string ubicacion) {
    this->id = id;
    this->nombre = nombre;
    this->artista = artista;
    this->album = album;
    this->año = año;
    this->duracion = duracion;
    this->ubicacion = ubicacion;

}