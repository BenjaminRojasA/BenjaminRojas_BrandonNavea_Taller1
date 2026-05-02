#include <iostream>

template <typename T>
struct Nodo {
    public:
        T dato;
        Nodo<T>* siguiente;
        Nodo<T>* anterior;

    Nodo(T valor) {
        this->dato = valor;
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }
};




