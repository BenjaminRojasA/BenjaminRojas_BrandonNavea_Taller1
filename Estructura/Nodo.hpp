
#ifndef NODO_HPP
#define NODO_HPP
template <typename T>
struct Nodo {
    public:
        T dato;
        Nodo<T>* next;
        Nodo<T> *anterior;

    Nodo(T valor) {
        this->dato = valor;
        this->next = nullptr;
        this->anterior = nullptr;
    }
};
#endif //NODO_HPP



