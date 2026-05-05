#include "../Logica/MediaPlayer.hpp"
#include <ctime>

int main() {
    srand (time(NULL));
    MediaPlayer reproductor;
    reproductor.run();
    return 0;
}