#ifndef MediaPlayer_hpp
#define MediaPlayer_hpp

#include "../Estructura/ListaEnLazada.hpp"
#include "../Clases/cancion.hpp"

class MediaPlayer {
    private:
        Nodo<cancion*>* nodoActual;
        ListaEnlazada<cancion*> canciones;

        ListaEnlazada<cancion*> previaPlaylist;

        cancion* previaPlaying;
        bool random;
        int modoRepetir;

    public:
        MediaPlayer();
        cancion* getHead();
        void run();
        void loadSongs();
        void loadStatus();
        void saveStatus();
        void showGeneralList();
        void showCurrentPlaylist();

};

#endif