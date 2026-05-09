#ifndef LISTAENLAZADA_HPP
#define LISTAENLAZADA_HPP

#include <iostream>
using namespace std;
#include "Nodo.hpp"

template <typename T>
class ListaEnlazada {
    protected:
        Nodo<T> * head;
        int size;
    public:
        Nodo<T>* getHead() {
            return head;
        }
        int getSize() {
            return size;
        }
        ListaEnlazada() {
            this->head = nullptr;
            this->size = 0;
        }
        void insertar(T value);
        void remover(int index);
        T get(int index);
        void imprimir();

        ~ListaEnlazada();
};

template <typename T>
void ListaEnlazada<T>::insertar(T data) {
    Nodo<T>* nuevo = new Nodo<T>(data);
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
    // ESTA LÍNEA ES VITAL:
    this->size++;
}
template <typename T>
void ListaEnlazada<T>::imprimir() {
    Nodo<T>* temp = head;

    if (!temp) {
        cout << "\n[!] La lista esta vacia." << endl;
        return;
    }

    while (temp) {
        temp->dato->mostrar();
        temp = temp->next;
    }
}

template <typename T>
ListaEnlazada<T>::~ListaEnlazada() {
    Nodo<T>* temp = head;
    while (temp != nullptr) {
        Nodo<T>* siguiente = temp->next;
        delete temp;
        temp = siguiente;
    }
}

#endif // LISTAENLAZADA_HPP