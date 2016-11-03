#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#define MAX(A,B) ((A)>(B)?(A):(B))
std::stringstream contenido;
using namespace std;

class arbolavl{
	int dato;
	int fe;
	arbolavl* hijoIzquierdo;
	arbolavl* hijoDerecho;
	arbolavl* raiz = NULL;
	bool r = true;
public:
	arbolavl(int d){
		dato = d;
		fe = 0;
		hijoDerecho = NULL;
		hijoIzquierdo = NULL;
	}
	
	void insertar(int d){
		arbolavl* nuevo = new arbolavl(d);
		if (raiz != NULL){
			if (r){
				raiz = nuevo;
				r = false;
			}
			else{
				raiz = insertarAVL(nuevo, raiz);
			}
		}
	}
	
	void preOrden(arbolavl* r){
		cout << "===============================" << endl;
		if (r){
			cout << r->dato << endl;
			preOrden(r->hijoIzquierdo);
			preOrden(r->hijoDerecho);
		}
	}
	
	void graficar(arbolavl* r){
		contenido.str("");

		inOrden(r);
		char *ruta = "dot -Tpng C:\\Users\\Edu\\Downloads\\arbolavl.dot -O";

		std::string tod = contenido.str(); //se concatena todo en una variable string
		char *pass = new char[tod.length() + 1]; //se declara un char* aux q contendra todo lo de la variable "todo"
		strcpy(pass, tod.data());

		std::stringstream cuerpo;
		/*inicio del documento*/
		cuerpo << "digraph G{\n node[shape=circle, style=filled];\n edge[color=blue];rankdir=UD \n ";

		cuerpo << pass;
		cuerpo << "\n}";
		std::string todo = cuerpo.str(); //se concatena todo en una variable string
		char *pass1 = new char[todo.length() + 1]; //se declara un char* aux q contendra todo lo de la variable "todo"
		strcpy(pass1, todo.c_str()); //se igualan los valores

		/*se escribe en el archivo*/
		FILE * pFile;
		pFile = fopen("C:\\Users\\Edu\\Downloads\\arbolavl.dot", "w");
		if (pFile != NULL){
			fputs(pass1, pFile);
			fclose(pFile);

			system(ruta);
		}
	}
	
	bool eliminar(int d){
		arbolavl* aux = raiz;
		arbolavl* padre = raiz;
		bool esHijoIzq = true;
		while (aux->dato != d){
			padre = aux;
			if (d<aux->dato){
				esHijoIzq = true;
				aux = aux->hijoIzquierdo;
			}
			else{
				esHijoIzq = false;
				aux = aux->hijoDerecho;
			}
			if (aux == NULL){
				return false;
			}
		}

		if (aux->hijoIzquierdo == NULL && aux->hijoDerecho == NULL){
			//nodo hoja o puede ser la raiz
			if (aux == raiz){
				//unico nodo osea la raiz
				free(raiz);
				r = true;
			}
			else if (esHijoIzq){
				padre->hijoIzquierdo = NULL;
			}
			else{
				padre->hijoDerecho = NULL;
			}
		}
		else if (aux->hijoDerecho == NULL){
			if (aux == raiz){
				raiz = aux->hijoIzquierdo;
			}
			else if (esHijoIzq){
				padre->hijoIzquierdo = aux->hijoIzquierdo;
			}
			else{
				padre->hijoDerecho = aux->hijoIzquierdo;
			}
		}
		else if (aux->hijoIzquierdo == NULL){
			if (aux == raiz){
				raiz = aux->hijoDerecho;
			}
			else if (esHijoIzq){
				padre->hijoIzquierdo = aux->hijoDerecho;
			}
			else{
				padre->hijoDerecho = aux->hijoIzquierdo;
			}
		}
		else{
			arbolavl* reemplazo = obtenerNodoReemplazo(aux);
			if (aux == raiz){
				raiz = reemplazo;
			}
			else if (esHijoIzq){
				padre->hijoIzquierdo = reemplazo;
			}
			else{
				padre->hijoDerecho = reemplazo;
			}

			reemplazo->hijoIzquierdo = aux->hijoIzquierdo;
		}
		return true;
	}
	
	arbolavl* obtenerRaiz(){
		return raiz;
	}
	
	arbolavl* buscar(int d, arbolavl* r){
		arbolavl* actual = r;
		while (actual != NULL){
			if (actual->dato > d){
				actual = actual->hijoDerecho;
			}
			else if (actual->dato < d){
				actual = actual->hijoIzquierdo;
			}
			else if (actual->dato == d){
				return actual;
				break;
			}
		}

		if (actual == NULL){
			return NULL;
		}
	}
private:
	int obtenerFE(arbolavl* x){
		if (x == NULL){
			return -1;
		}else{
			return x->fe;
		}
	}
	
	arbolavl* rotacionIzquierda(arbolavl* c){
		arbolavl* aux = c->hijoIzquierdo;
		c->hijoIzquierdo = aux->hijoDerecho;
		aux->hijoDerecho = c;
		c->fe = MAX(obtenerFE(c->hijoIzquierdo), obtenerFE(c->hijoDerecho)) + 1;
		aux->fe = MAX(obtenerFE(aux->hijoIzquierdo), obtenerFE(aux->hijoDerecho)) + 1;
		return aux;
	}
	
	arbolavl* rotacionDerecha(arbolavl* c){
		arbolavl* aux = c->hijoDerecho;
		c->hijoDerecho = aux->hijoIzquierdo;
		aux->hijoIzquierdo = c;
		c->fe = MAX(obtenerFE(c->hijoIzquierdo), obtenerFE(c->hijoDerecho)) + 1;
		aux->fe = MAX(obtenerFE(aux->hijoIzquierdo), obtenerFE(aux->hijoDerecho)) + 1;
		return aux;
	}

	arbolavl* rotacionDobleIzquierda(arbolavl* c){
		arbolavl* tmp;
		c->hijoIzquierdo = rotacionDerecha(c->hijoIzquierdo);
		tmp = rotacionIzquierda(c);
		return tmp;
	}
	
	arbolavl* rotacionDobleDerecha(arbolavl* c){
		arbolavl* tmp;
		c->hijoDerecho = rotacionIzquierda(c->hijoDerecho);
		tmp = rotacionDerecha(c);
		return tmp;
	}
	
	arbolavl* insertarAVL(arbolavl* nuevo, arbolavl* subAr){
		arbolavl* nuevoPadre = subAr;
		if (nuevo->dato < subAr->dato){
			if (subAr->hijoIzquierdo == NULL){
				subAr->hijoIzquierdo = nuevo;
			}
			else{
				subAr->hijoIzquierdo = insertarAVL(nuevo, subAr->hijoIzquierdo);
				if ((obtenerFE(subAr->hijoIzquierdo) - obtenerFE(subAr->hijoDerecho)) == 2){
					//desvalanceado
					if (nuevo->dato < subAr->hijoIzquierdo->dato){
						nuevoPadre = rotacionIzquierda(subAr);
					}
					else{
						nuevoPadre = rotacionDobleIzquierda(subAr);
					}
				}
			}
		}
		else if (nuevo->dato > subAr->dato){
			if (subAr->hijoDerecho == NULL){
				subAr->hijoDerecho = nuevo;
			}
			else{
				subAr->hijoDerecho = insertarAVL(nuevo, subAr->hijoDerecho);
				if ((obtenerFE(subAr->hijoDerecho) - obtenerFE(subAr->hijoIzquierdo)) == 2){
					if (nuevo->dato > subAr->hijoDerecho->dato){
						nuevoPadre = rotacionDerecha(subAr);
					}
					else{
						nuevoPadre = rotacionDobleDerecha(subAr);
					}
				}
			}
		}
		else{
			cout << "nodo ya ingresado" << endl;
		}

		if ((subAr->hijoIzquierdo == NULL) && (subAr->hijoDerecho != NULL)){
			subAr->fe = subAr->hijoDerecho->fe + 1;
		}
		else if ((subAr->hijoDerecho == NULL) && (subAr->hijoIzquierdo != NULL)){
			subAr->fe = subAr->hijoIzquierdo->fe + 1;
		}
		else{
			subAr->fe = MAX(obtenerFE(subAr->hijoIzquierdo), obtenerFE(subAr->hijoDerecho)) + 1;
		}

		return nuevoPadre;
	}
	
	arbolavl* obtenerNodoReemplazo(arbolavl* nodoReemp){
		arbolavl* reemplazarPadre = nodoReemp;
		arbolavl* reemplazo = nodoReemp;
		arbolavl* aux = nodoReemp->hijoDerecho;
		while (aux != NULL){
			reemplazarPadre = reemplazo;
			reemplazo = aux;
			aux = aux->hijoIzquierdo;
		}

		if (reemplazo != nodoReemp->hijoDerecho){
			reemplazarPadre->hijoIzquierdo = reemplazo->hijoDerecho;
			reemplazo->hijoDerecho = nodoReemp->hijoDerecho;
		}

		return reemplazo;
	}
	
	void inOrden(arbolavl* r){
		if (r){
			inOrden(r->hijoIzquierdo);

			contenido << "\"" << r->dato
				<< "\"  [ label = \" Dato: " << r->dato
				<< ' ' << "\n Algo: " << "4"
				<< ' ' << "  \" shape = \"ellipse\" ] ; \n";

			if (r->hijoIzquierdo){
				contenido << "\"" << r->dato << "\"->\"" << r->hijoIzquierdo->dato << "\";\n";
			}

			if (r->hijoDerecho){
				contenido << "\"" << r->dato << "\"->\"" << r->hijoDerecho->dato << "\";\n";
			}

			inOrden(r->hijoDerecho);
		}
	}
};