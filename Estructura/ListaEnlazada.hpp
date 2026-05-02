#include <iostream>

#include "Nodo.hpp"

template <typename T>
class ListaEnlazada {
    protected:
        Nodo<T> * head;
        int size;
    public:
        ListaEnlazada() : head(NULL), size(0) {}
        void insertar(T value);
        void remover(int index);
        T get(int index);

        ~ListaEnlazada();
};




