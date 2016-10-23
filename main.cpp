#include <QCoreApplication>
#include "iostream"
#include "arbolavl.h"
#include "string.h"
#include "cstdlib"
#include "iostream"
#include "fstream"
#include "cstdlib"

using namespace std;

ArbolAVL* miarbol= (ArbolAVL*)malloc(sizeof(ArbolAVL));

int main()
{
    cout<<"algo"<<endl;
    miarbol->insertar(10);
    miarbol->insertar(5);
    miarbol->insertar(13);
    miarbol->insertar(1);
    miarbol->insertar(6);
    miarbol->insertar(17);
    miarbol->insertar(16);
    NodoAVL* raiz = miarbol->obtenerRaiz();
    miarbol->preOrden(raiz);
    cout<<"otro"<<endl;
}
