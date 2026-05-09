#ifndef STACK_HPP
#define STACK_HPP

#include "ListaEnlazada.hpp"


template <typename T>
class Queue : public ListaEnlazada<T> {
public:
    void enqueue(T value) { this->insertar(value); }
    
    T dequeue() {
        if (this->head == nullptr) {
            this->size = 0;
            return nullptr;
        }

        Nodo<T>* temp = this->head;
        T data = temp->dato;
        this->head = this->head->next;

        if (this->head != nullptr) {
            this->head->anterior = nullptr;
        }

        delete temp;


        if (this->size > 0) this->size--;

        return data;
    }

    int getSize() {
        return this->size;
    }
    Queue() : ListaEnlazada<T>() {}
};


template <typename T>
class Stack : public ListaEnlazada<T> {
public:
    void push(T value) {
        Nodo<T>* nuevo = new Nodo<T>(value);
        if (!this->head) this->head = nuevo;
        else {
            nuevo->next = this->head;
            this->head->anterior = nuevo;
            this->head = nuevo;
        }
        this->size++;
    }

};

#endif