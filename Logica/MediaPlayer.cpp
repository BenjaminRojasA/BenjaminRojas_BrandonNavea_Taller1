
#include <string>
#include <fstream>
#include "../Clases/cancion.hpp"
#include <sstream>
using namespace std;
#include "MediaPlayer.hpp"

MediaPlayer::MediaPlayer() {

    previaPlaying = nullptr;
    random = false;
    modoRepetir = 0;
}

void MediaPlayer::loadSongs() {
    ifstream archivo("music_source.txt");
    string linea;
    if (!archivo.is_open()) {
        return;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id_str, nombre, artista, album, año, duracion, ubicacion;

        getline(ss, id_str, ',');
        getline(ss, nombre, ',');
        getline(ss, artista, ',');
        getline(ss, album, ',');
        getline(ss, año, ',');
        getline(ss, duracion, ',');
        getline(ss, ubicacion, ',');

        int id = stoi(id_str);

        cancion* nueva = new cancion(id, nombre, artista, album, año, duracion, ubicacion);
        canciones.insertar(nueva);

    }
    archivo.close();
}

void MediaPlayer::run() {
    loadSongs();

    char opcion;
    bool ejecutando = true;

    while (ejecutando) {

        system("cls");

        // Interfaz del menú
        cout << "=== REPRODUCTOR DE MUSICA ===" << endl;
        cout << "-----------------------------" << endl;
        cout << "W - Reproducir / Pausar" << endl;
        cout << "Q - Pista Anterior" << endl;
        cout << "E - Pista Siguiente" << endl;
        cout << "L - Mostrar lista general" << endl;
        cout << "X - Salir" << endl;
        cout << "-----------------------------" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        opcion = toupper(opcion);

        switch (opcion) {
            case 'L':
                showGeneralList();
                system("pause");
                break;
            case 'X':
                ejecutando = false;
                break;
                //demas opciones que faltan

            default:
                cout << "Error: Opcion no valida. Intente de nuevo.";
                system("pause");
                break;

        }

    }
}

void MediaPlayer::showGeneralList(){
        system("cls");
        cout << "===========================================" << endl;
        cout << "          LISTA GENERAL DE CANCIONES       " << endl;
        cout << "===========================================" << endl;

        canciones.imprimir();

        cout << "===========================================" << endl;
        cout << "\nPresione cualquier tecla para volver...";
        system("pause > nul");
    }

