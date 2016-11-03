// Win32Project1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "arbolavl.h"
#include <stdlib.h>
#include <malloc.h>

using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	arbolavl* miarbol = (arbolavl*)malloc(sizeof(arbolavl));
	
	miarbol->insertar(32);
	miarbol->insertar(15);
	miarbol->insertar(78);
	miarbol->insertar(46);
	miarbol->insertar(74);
	arbolavl* raiz = miarbol->obtenerRaiz();
	miarbol->preOrden(raiz);
	miarbol->graficar(raiz);
	system("pause");
}

