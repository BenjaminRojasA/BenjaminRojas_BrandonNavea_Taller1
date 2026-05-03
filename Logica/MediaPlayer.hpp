#ifndef MediaPlayer_hpp
#define MediaPlayer_hpp

#include "../Estructura/ListaEnLazada.hpp"
#include "../Clases/cancion.hpp"

class MediaPlayer {
    private:
        ListaEnlazada<cancion*> canciones;

        ListaEnlazada<cancion*> previaPlaylist;

        cancion* previaPlaying;
        bool random;
        int modoRepetir;

    public:
        MediaPlayer();

        void run();
        void loadSongs();
        void saveStatus();
        void showGeneralList();
        void showCurrentPlaylist();

};

#endif