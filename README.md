# :musical_note: C-Player | Reproductor de Consola (Taller 01 EDD)

## :pencil: De qué trata esto
Este es nuestro proyecto para el Taller 1 de Estructuras de Datos (UCN). La idea principal fue armar un reproductor de música de la nada misma usando C++ puro. Aquí la regla de oro era **cero STL** (nada de `std::list`, `std::vector` ni librerías que te hacen la vida fácil). Todo el control de los datos, los enlaces de los nodos y la memoria dinámica lo manejamos a mano peleando directamente con los punteros.

---

## :busts_in_silhouette: El Equipo

| Integrante | RUT | Carrera | GitHub |
| :--- | :--- | :--- | :--- |
| **Benjamín Rojas** | 22.086.016-7 | ICCI | [@BenjaminRojasA](https://github.com/BenjaminRojasA) |
| **Brandon Navea** | 22.042.679-3 | ICCI | [@brandonnavea](https://github.com/brandonnavea) |

* **Profesor:** Bastian Ruiz Garay
* **Ayudante:** Pablo Guzmán Vargas

---

## :construction: Qué logramos armar (Funcionalidades)
El reproductor se encuentra 100% funcional y cumple con toda la pauta exigida. Le pusimos harto empeño a estas mecánicas:

* **Gestión de Archivos y Persistencia:** Apenas arranca, el programa lee el `music_source.txt` y arma los nodos al vuelo usando `stringstream`. Además, cuando sales del programa (X), el estado actual se guarda en `status.cfg` respetando estrictamente el formato `PARÁMETRO VALOR`, así cuando vuelves a abrirlo, te deja en la misma canción y con los mismos modos activados.
* **Navegación a prueba de balas:** Implementamos avance (E) y retroceso (Q) lidiando con los punteros `next` y `anterior`. También le agregamos un sistema de pausa (W) que actualiza la interfaz en tiempo real.
* **Modos de Reproducción:** La lógica matemática del Random está lista (salta a nodos aleatorios ignorando el orden), al igual que el ciclo de Repetición (OFF, ONE, ALL), haciendo que los punteros den la vuelta de extremo a extremo cuando corresponde.
* **Cola de Pedidos (Opción A):** Para cumplir con el uso de una segunda estructura, implementamos una `Queue` (Cola). Funciona como el "Agregar a la cola" de Spotify: pides un ID de canción y se guarda ahí para reproducirse con prioridad antes de seguir con la lista normal.

---

## :brain: La Arquitectura (Estructuras de Datos)
Para no repetir código innecesario, armamos nuestra `ListaEnlazada` y el `Nodo` utilizando **Templates** (`<T>`). Así dejamos una estructura genérica que nos sirve para todo. Luego, hicimos que tanto la Pila (`Stack`) como la Cola (`Queue`) heredaran de esta lista base, reutilizando sus métodos.

El núcleo de todo es la clase `MediaPlayer`, que funciona como el cerebro: agrupa la lista general, la cola de reproducción y gestiona la lógica de los punteros. Aquí dejamos el diagrama de clases para que se entienda mejor:

```mermaid
classDiagram
    class cancion {
        -int id
        -string nombre
        -string artista
        -string album
        -string año
        -string duracion
        -string ubicacion
        +cancion()
        +cancion(id, nombre, artista, album, año, duracion, ubicacion)
        +getId() int
        +getNombre() string
        +getArtista() string
        +mostrar() void
    }

    class Nodo~T~ {
        +T dato
        +Nodo~T~* next
        +Nodo~T~* anterior
        +Nodo(T valor)
    }

    class ListaEnlazada~T~ {
        #Nodo~T~* head
        #int size
        +ListaEnlazada()
        +~ListaEnlazada()
        +getHead() Nodo~T~*
        +getSize() int
        +insertar(T value) void
        +remover(int index) void
        +get(int index) T
        +imprimir() void
    }

    class Queue~T~ {
        +Queue()
        +enqueue(T value) void
        +dequeue() T
        +getSize() int
    }

    class Stack~T~ {
        +push(T value) void
    }

    class MediaPlayer {
        -Nodo~cancion*~* nodoActual
        -ListaEnlazada~cancion*~ canciones
        -Queue~cancion*~ colaReproduccion
        -ListaEnlazada~cancion*~ previaPlaylist
        -cancion* previaPlaying
        -bool random
        -int modoRepetir
        -bool enPausa
        +MediaPlayer()
        +getHead() cancion*
        +run() void
        +agregarACola() void
        +loadSongs() void
        +loadStatus() void
        +saveStatus() void
        +showGeneralList() void
        +showCurrentPlaylist() void
    }

    ListaEnlazada <|-- Queue : Herencia
    ListaEnlazada <|-- Stack : Herencia
    ListaEnlazada *-- Nodo : Composición
    MediaPlayer o-- ListaEnlazada : Agregación
    MediaPlayer o-- Queue : Agregación
    MediaPlayer o-- cancion : Agregación/Uso
    Nodo o-- cancion : Contiene