#include <iostream>

#include "Nodo.hpp"

template <typename T>
class ListaEnlazada {
    protected:
        Nodo<T> * head;
        int size;
    public:
        ListaEnlazada();
        void insertar(T value);
        void remover(int index);
        T get(int index);

        ~ListaEnlazada();
};

template <typename T>
ListaEnlazada<T>::ListaEnlazada() {
    head = nullptr;
}

template <typename T>
void ListaEnlazada<T>::insertar(T data) {
    Nodo<T>* nuevo = new Nodo<T>{data};
    if (!head) {
        head = nuevo;
    } else {
        Nodo<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nuevo;
        nuevo->anterior = temp;

    }

}

