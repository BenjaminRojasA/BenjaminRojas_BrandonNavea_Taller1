
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
    nodoActual = nullptr;
}

void MediaPlayer::saveStatus() {
    ofstream archivo("status.cfg");
    if (!archivo.is_open()) return;

    int idActual = (previaPlaying!= nullptr) ? previaPlaying->getId() : -1;
    archivo << idActual << ","
            << (random ? 1: 0) << ","
            << modoRepetir;

    archivo.close();
}
void MediaPlayer::loadSongs() {
    ifstream archivo("music_source.txt");
    string linea;
    if (!archivo.is_open()) {
        // Si ves este mensaje, el problema es la ubicación del archivo
        cout << "\n[DEBUG] Error: No se encontro music_source.txt en la ruta actual." << endl;
        system("pause");
        return;
    }

    cout << "\n[DEBUG] Archivo abierto con exito. Cargando canciones..." << endl;
    if (!archivo.is_open()) {
        return;
    }
    if (canciones.getHead() != nullptr) {
        this->nodoActual = canciones.getHead();
        this->previaPlaying = nodoActual->dato;
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
void MediaPlayer::loadStatus() {
    ifstream archivo("status.cfg");
    if (!archivo.is_open()) return; // Si no existe el archivo, no pasa nada

    string linea;
    if (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, randomStr, modoStr;

        getline(ss, idStr, ',');
        getline(ss, randomStr, ',');
        getline(ss, modoStr, ',');

        // 1. Restauramos los modos
        this->random = (randomStr == "1");
        this->modoRepetir = stoi(modoStr);

        // 2. Buscamos la canción por ID para poner el nodoActual ahí
        int idBuscado = stoi(idStr);
        Nodo<cancion*>* temp = canciones.getHead();
        while (temp != nullptr) {
            if (temp->dato->getId() == idBuscado) {
                this->nodoActual = temp;
                this->previaPlaying = temp->dato;
                break;
            }
            temp = temp->next;
        }
    }
    archivo.close();
}
void MediaPlayer::run() {
    loadSongs();
    loadStatus(); // Carga el estado inicial del taller

    // Inicializamos el puntero al inicio si no se cargó nada del status
    if (canciones.getHead() != nullptr && nodoActual == nullptr) {
        nodoActual = canciones.getHead();
        previaPlaying = nodoActual->dato;
    }

    char opcion;
    bool ejecutando = true;

    while (ejecutando) {
        if (nodoActual == nullptr) {
            nodoActual = canciones.getHead();
        }
        system("cls"); // 1. Limpiar

        // 2. Mostrar la info arriba (Encabezado único)
        cout << "===========================================" << endl;
        cout << "       REPRODUCTOR DE MUSICA (UCN)         " << endl;
        cout << "===========================================" << endl;

        if (previaPlaying != nullptr) {
            cout << " REPRODUCIENDO: [" << previaPlaying->getId() << "] "
                 << previaPlaying->getNombre() << endl;
            cout << " ARTISTA: " << previaPlaying->getArtista() << endl;
        } else {
            cout << " [!] No hay canciones seleccionadas." << endl;
        }

        cout << "-------------------------------------------" << endl;
        cout << " W - Pause | Q - Anterior | E - Siguiente " << endl;
        cout << " S - Random [" << (random ? "ON " : "OFF") << "] | ";
        cout << " R - Repetir [";
        if (modoRepetir == 0) cout << "OFF";
        else if (modoRepetir == 1) cout << "ONE";
        else cout << "ALL";
        cout << "]" << endl;
        cout << " L - Lista | X - Salir     " << endl;
        cout << "-------------------------------------------" << endl;

        cout << " Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(1000, '\n'); // Esto limpia el "Enter"
        opcion = toupper(opcion);

        switch (opcion) {
            case 'E':
                // 1. PRIORIDAD: MODO ALEATORIO (Si está prendido, da igual el modo repetir)
                if (random && canciones.getSize() > 0) {
                    int total = canciones.getSize();
                    int indiceAzar = rand() % total;
                    Nodo<cancion*>* temp = canciones.getHead();

                    for (int i = 0; i < indiceAzar && temp != nullptr; i++) {
                        temp = temp->next;
                    }

                    if (temp != nullptr) {
                        nodoActual = temp;
                    }
                }
                // 2. MODO NORMAL (Random OFF)
                else {
                    if (modoRepetir == 1) {
                        // --- MODO REPEAT ONE ---
                        // Simplemente no movemos el puntero 'nodoActual'
                        // Así se queda en la misma canción actual
                        cout << "\n[INFO] Modo Repeat One: Reproduciendo de nuevo..." << endl;
                    }
                    else if (nodoActual != nullptr && nodoActual->next != nullptr) {
                        // AVANCE NORMAL: Si hay una canción siguiente, vamos a ella
                        nodoActual = nodoActual->next;
                    }
                    else if (modoRepetir == 2) {
                        // --- MODO REPEAT ALL ---
                        // Si llegaste a la última (next == nullptr), saltamos a la primera
                        cout << "\n[INFO] Fin de lista. Volviendo al inicio (Modo Repeat All)..." << endl;
                        nodoActual = canciones.getHead();
                    }
                    else {
                        // --- MODO OFF ---
                        // No hay siguiente y no hay repetición activada
                        cout << "\n[!] Fin de la lista de reproduccion." << endl;
                        system("pause");
                    }
                }

                // ACTUALIZACIÓN DE LA INTERFAZ
                if (nodoActual != nullptr) {
                    previaPlaying = nodoActual->dato;
                }
                break;
            case 'S': // TOGGLE ALEATORIO
                random = !random;
                break;

            case 'L': // LISTA
                showGeneralList();
                system("pause"); // Aquí sí pausamos para que alcances a leer
                break;

            case 'X': // SALIR
                saveStatus(); // Guarda antes de cerrar como pide la pauta
                ejecutando = false;
                break;
            case 'R':
                // Cicla entre 0, 1 y 2
                modoRepetir = (modoRepetir + 1) % 3;
                break;

            default:
                cout << "\n[!] Opcion no valida.";
                system("pause");
                break;
                // Al final de cualquier tecla (E, Q, S), actualizamos la canción que se muestra


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
