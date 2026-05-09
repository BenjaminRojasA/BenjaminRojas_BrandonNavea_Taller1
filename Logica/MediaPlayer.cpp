
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
    enPausa = false;
}

void MediaPlayer::saveStatus() {
    ofstream archivo("status.cfg");
    if (!archivo.is_open()) return;

    int idActual = (previaPlaying != nullptr) ? previaPlaying->getId() : -1;

    archivo << "CANCION_ACTUAL " << idActual << endl;
    archivo << "MODO_ALEATORIO " << (random ? 1 : 0) << endl;
    archivo << "MODO_REPETICION " << modoRepetir << endl;

    archivo.close();
}

void MediaPlayer::loadSongs() {
    ifstream archivo("music_source.txt");
    string linea;
    if (!archivo.is_open()) {
        cout << "\n[DEBUG] Error: No se encontro music_source.txt en la ruta actual." << endl;
        system("pause");
        return;
    }

    cout << "\n[DEBUG] Archivo abierto con exito. Cargando canciones..." << endl;
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
    if (canciones.getHead() != nullptr) {
        this->nodoActual = canciones.getHead();
        this->previaPlaying = nodoActual->dato;
    }
    archivo.close();
}

void MediaPlayer::loadStatus() {
    ifstream archivo("status.cfg");
    if (!archivo.is_open()) return;

    string parametro;
    int valor;
    int idBuscado = -1;


    while (archivo >> parametro >> valor) {
        if (parametro == "CANCION_ACTUAL") idBuscado = valor;
        else if (parametro == "MODO_ALEATORIO") this->random = (valor == 1);
        else if (parametro == "MODO_REPETICION") this->modoRepetir = valor;
    }


    if (idBuscado != -1) {
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
    loadStatus();

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
        system("cls");


        cout << "===========================================" << endl;
        cout << "       REPRODUCTOR DE MUSICA (UCN)         " << endl;
        cout << "===========================================" << endl;

        if (previaPlaying != nullptr) {
            cout << " REPRODUCIENDO: [" << previaPlaying->getId() << "] "
                 << previaPlaying->getNombre();


            if (enPausa) cout << " [PAUSADO]";
            cout << endl;

            cout << " ARTISTA: " << previaPlaying->getArtista() << endl;
        } else {
            cout << " [!] No hay canciones seleccionadas." << endl;
        }

        cout << "-------------------------------------------" << endl;
        cout << " W - Pause  | Q - Anterior | E - Siguiente " << endl;
        cout << " S - Random [" << (random ? "ON " : "OFF") << "] | ";
        cout << " R - Repetir [";
        if (modoRepetir == 0) cout << "OFF";
        else if (modoRepetir == 1) cout << "ONE";
        else cout << "ALL";
        cout << "]" << endl;


        cout << " L - Lista | A - Cola (" << colaReproduccion.getSize() << ") | X - Salir" << endl;
        cout << "-------------------------------------------" << endl;

        cout << " Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(1000, '\n'); // Esto limpia el "Enter"
        opcion = toupper(opcion);

        switch (opcion) {
            case 'A':
                agregarACola();
                break;
            case 'W':
                if (previaPlaying != nullptr) {
                    enPausa = !enPausa;
                    break;
                    case 'E':
                    if (colaReproduccion.getSize() > 0 && colaReproduccion.getSize() < 1000) {
                        cancion* extraida = colaReproduccion.dequeue();

                        if (extraida != nullptr) {

                            previaPlaying = extraida;
                            cout << "\n[COLA] Reproduciendo pedido especial..." << endl;
                            break;
                        }
                    }

                    // --- 2. SI NO HAY COLA, AVANCE NORMAL ---
                    if (this->random == true) {
                        int total = canciones.getSize();
                        if (total > 0) {
                            int idx = rand() % total;
                            Nodo<cancion*>* t = canciones.getHead();
                            for(int i = 0; i < idx && t != nullptr; i++) t = t->next;
                            nodoActual = t;
                        }
                    }
                    else {
                        if (modoRepetir == 1) {
                            // Repeat One: no movemos nada
                        }
                        else if (nodoActual != nullptr && nodoActual->next != nullptr) {
                            nodoActual = nodoActual->next;
                        }
                        else if (modoRepetir == 2) {
                            nodoActual = canciones.getHead();
                        }
                        else {
                            cout << "\n[!] Fin de la lista." << endl;
                            system("pause");
                        }
                    }


                    if (nodoActual != nullptr) {
                        previaPlaying = nodoActual->dato;
                    }
                    break;
                    case 'Q':

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
                            cout << "\n[INFO] Modo Repeat One: Reproduciendo de nuevo..." << endl;
                        }
                        else if (nodoActual != nullptr && nodoActual->anterior != nullptr) {

                            nodoActual = nodoActual->anterior;
                        }
                        else if (modoRepetir == 2) {

                            cout << "\n[INFO] Inicio de lista. Volviendo al final (Modo Repeat All)..." << endl;
                            Nodo<cancion*>* temp = canciones.getHead();

                            while (temp != nullptr && temp->next != nullptr) {
                                temp = temp->next;
                            }
                            nodoActual = temp;
                        }
                        else {

                            cout << "\n[!] Principio de la lista de reproduccion." << endl;
                            system("pause");
                        }
                    }

                    // ACTUALIZACIÓN DE LA INTERFAZ
                    if (nodoActual != nullptr) {
                        previaPlaying = nodoActual->dato;
                    }
                    break;

                    case 'S':
                    random = !random;
                    break;

                    case 'L':
                    showGeneralList();
                    system("pause"); // Aquí sí pausamos para que alcances a leer
                    break;

                    case 'X':
                    saveStatus(); // Guarda antes de cerrar como pide la pauta
                    ejecutando = false;
                    break;
                    case 'R':

                    modoRepetir = (modoRepetir + 1) % 3;
                    break;

                    default:
                    cout << "\n[!] Opcion no valida.";
                    system("pause");
                    break;
                }


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

void MediaPlayer::agregarACola() {
    int idBuscado;
    cout << "\n[COLA] Ingrese el ID de la cancion: ";
    if (!(cin >> idBuscado)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    Nodo<cancion*>* temp = canciones.getHead();
    while (temp != nullptr) {
        if (temp->dato != nullptr && temp->dato->getId() == idBuscado) {

            this->colaReproduccion.enqueue(temp->dato);

            cout << "[OK] " << temp->dato->getNombre() << " agregada." << endl;
            cout << "[DEBUG] Canciones en cola ahora: " << this->colaReproduccion.getSize() << endl;
            system("pause");
            return;
        }
        temp = temp->next;
    }
    cout << "[!] ID no encontrado." << endl;
    system("pause");
}