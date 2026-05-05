
#include "ListaEnlazada.hpp"
#include "../Clases/cancion.hpp"
template <typename T>
class Stack : public ListaEnlazada<T> {
    private:
        ListaEnlazada<cancion*>* canciones;
        Nodo<cancion*>* nodoActual;
    public:
        void push(T value) {
            this->insertar(value);

        }
        T pop() {
            
        }

};



