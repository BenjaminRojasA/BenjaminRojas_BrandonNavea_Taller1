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
int cancion::getId() {
    return id;
}
string cancion::getNombre() {
    return nombre;
}
string cancion::getArtista() {
    return artista;
}
void cancion::mostrar() {
    cout << "[" << id << "] " << nombre << " - " << artista << " (" << album << ")" << endl;
}
