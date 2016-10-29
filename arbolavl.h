#ifndef ARBOLAVL_H
#define ARBOLAVL_H
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "iostream"

typedef struct NodoAVL NodoAVL;
typedef struct ArbolAVL ArbolAVL;

struct NodoAVL{
    int dato;
    int fe;
    NodoAVL* hijoIzquierdo;
    NodoAVL* hijoDerecho;
    NodoAVL(int dato);
};

struct ArbolAVL{
    NodoAVL* raiz;
    NodoAVL* obtenerRaiz();
    NodoAVL* buscar(int d, NodoAVL* r);
    int obtenerFE(NodoAVL* x);
    NodoAVL* rotacionIzquierda(NodoAVL* c);
    NodoAVL* rotacionDerecha(NodoAVL* c);
    NodoAVL* rotacionDobleIzquierda(NodoAVL* c);
    NodoAVL* rotacionDobleDerecha(NodoAVL* c);
    NodoAVL* insertarAVL(NodoAVL* nuevo, NodoAVL* subAr);
    NodoAVL* obtenerNodoReemplazo(NodoAVL* aux);
    void insertar(int d);
    void preOrden(NodoAVL* r);
    void inOrden(NodoAVL* r);
    bool eliminar(int d);
    void graficar(NodoAVL* r);
};

#endif // ARBOLAVL_H
