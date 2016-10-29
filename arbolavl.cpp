#include "arbolavl.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "iostream"
#include "sstream"

using namespace std;
bool r=false;
std::stringstream contenido;
#define MAX(A,B) ((A)>(B)?(A):(B))

NodoAVL::NodoAVL(int dato){
    this->dato = dato;
    this->fe = 0;
    this->hijoIzquierdo = NULL;
    this->hijoDerecho = NULL;
}

NodoAVL* ArbolAVL::obtenerRaiz(){
    return raiz;
}

NodoAVL* ArbolAVL::buscar(int d, NodoAVL* r){
    NodoAVL* actual = r;
    while(actual != NULL){
        if(actual->dato > d){
            actual = actual->hijoDerecho;
        }else if(actual->dato < d){
            actual = actual->hijoIzquierdo;
        }else if(actual->dato == d){
            return actual;
            break;
        }
    }

    if(actual==NULL){
        return NULL;
    }
}

int ArbolAVL::obtenerFE(NodoAVL* x){
    if(x==NULL){
        return -1;
    }else{
        return x->fe;
    }
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* c){
    NodoAVL* aux = c->hijoIzquierdo;
    c->hijoIzquierdo = aux->hijoDerecho;
    aux->hijoDerecho = c;
    c->fe = MAX(obtenerFE(c->hijoIzquierdo), obtenerFE(c->hijoDerecho)) + 1;
    aux->fe = MAX(obtenerFE(aux->hijoIzquierdo), obtenerFE(aux->hijoDerecho)) + 1;
    return aux;
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL *c){
    NodoAVL* aux = c->hijoDerecho;
    c->hijoDerecho = aux->hijoIzquierdo;
    aux->hijoIzquierdo = c;
    c->fe = MAX(obtenerFE(c->hijoIzquierdo), obtenerFE(c->hijoDerecho)) + 1;
    aux->fe = MAX(obtenerFE(aux->hijoIzquierdo), obtenerFE(aux->hijoDerecho)) + 1;
    return aux;
}

NodoAVL* ArbolAVL::rotacionDobleIzquierda(NodoAVL *c){
    NodoAVL* tmp;
    c->hijoIzquierdo = rotacionDerecha(c->hijoIzquierdo);
    tmp = rotacionIzquierda(c);
    return tmp;
}

NodoAVL* ArbolAVL::rotacionDobleDerecha(NodoAVL *c){
    NodoAVL* tmp;
    c->hijoDerecho = rotacionIzquierda(c->hijoDerecho);
    tmp = rotacionDerecha(c);
    return tmp;
}

NodoAVL* ArbolAVL::insertarAVL(NodoAVL *nuevo, NodoAVL *subAr){
    NodoAVL* nuevoPadre = subAr;
    if(nuevo->dato < subAr->dato){
        if(subAr->hijoIzquierdo == NULL){
            subAr->hijoIzquierdo = nuevo;
        }else{
            subAr->hijoIzquierdo = insertarAVL(nuevo, subAr->hijoIzquierdo);
            if((obtenerFE(subAr->hijoIzquierdo) - obtenerFE(subAr->hijoDerecho)) == 2){
                //desvalanceado
                if(nuevo->dato < subAr->hijoIzquierdo->dato){
                    nuevoPadre = rotacionIzquierda(subAr);
                }else{
                    nuevoPadre = rotacionDobleIzquierda(subAr);
                }
            }
        }
    }else if(nuevo->dato > subAr->dato){
        if(subAr->hijoDerecho == NULL){
            subAr->hijoDerecho = nuevo;
        }else{
            subAr->hijoDerecho = insertarAVL(nuevo, subAr->hijoDerecho);
            if((obtenerFE(subAr->hijoDerecho) - obtenerFE(subAr->hijoIzquierdo)) == 2){
                if(nuevo->dato > subAr->hijoDerecho->dato){
                    nuevoPadre = rotacionDerecha(subAr);
                }else{
                    nuevoPadre = rotacionDobleDerecha(subAr);
                }
            }
        }
    }else{
        cout<<"nodo ya ingresado"<<endl;
    }

    if((subAr->hijoIzquierdo == NULL) && (subAr->hijoDerecho != NULL)){
        subAr->fe = subAr->hijoDerecho->fe+1;
    }else if((subAr->hijoDerecho == NULL) && (subAr->hijoIzquierdo != NULL)){
        subAr->fe = subAr->hijoIzquierdo->fe+1;
    }else{
        subAr->fe = MAX(obtenerFE(subAr->hijoIzquierdo), obtenerFE(subAr->hijoDerecho)) + 1;
    }

    return nuevoPadre;
}

void ArbolAVL::insertar(int d){
    NodoAVL* nuevo = new NodoAVL(d);
    if(raiz!=NULL){
        if(r==false){
            raiz = nuevo;
            r=true;
        }else{
            raiz = insertarAVL(nuevo, raiz);
        }
    }
}

void ArbolAVL::preOrden(NodoAVL *r){
    if(r){
        cout<<r->dato<<endl;
        preOrden(r->hijoIzquierdo);
        preOrden(r->hijoDerecho);
    }
}

bool ArbolAVL::eliminar(int d){
    NodoAVL* aux = raiz;
    NodoAVL* padre = raiz;
    bool esHijoIzq=true;
    while(aux->dato != d){
        padre = aux;
        if(d<aux->dato){
            esHijoIzq=true;
            aux = aux->hijoIzquierdo;
        }else{
            esHijoIzq=false;
            aux = aux->hijoDerecho;
        }
        if(aux==NULL){
            return false;
        }
    }

    if(aux->hijoIzquierdo == NULL && aux->hijoDerecho == NULL){
        //nodo hoja o puede ser la raiz
        if(aux == raiz){
            //unico nodo osea la raiz
            free(raiz);
            r=false;
        }else if(esHijoIzq){
            padre->hijoIzquierdo = NULL;
        }else{
            padre->hijoDerecho = NULL;
        }
    }else if(aux->hijoDerecho == NULL){
        if(aux == raiz){
            raiz = aux->hijoIzquierdo;
        }else if(esHijoIzq){
            padre->hijoIzquierdo = aux->hijoIzquierdo;
        }else{
            padre->hijoDerecho = aux->hijoIzquierdo;
        }
    }else if(aux->hijoIzquierdo == NULL){
        if(aux == raiz){
            raiz = aux->hijoDerecho;
        }else if(esHijoIzq){
            padre->hijoIzquierdo = aux->hijoDerecho;
        }else{
            padre->hijoDerecho = aux->hijoIzquierdo;
        }
    }else{
        NodoAVL* reemplazo = obtenerNodoReemplazo(aux);
        if(aux == raiz){
            raiz=reemplazo;
        }else if(esHijoIzq){
            padre->hijoIzquierdo = reemplazo;
        }else{
            padre->hijoDerecho = reemplazo;
        }

        reemplazo->hijoIzquierdo = aux->hijoIzquierdo;
    }
    return true;
}

NodoAVL* ArbolAVL::obtenerNodoReemplazo(NodoAVL *nodoReemp){
    NodoAVL* reemplazarPadre=nodoReemp;
    NodoAVL* reemplazo=nodoReemp;
    NodoAVL* aux = nodoReemp->hijoDerecho;
    while(aux!=NULL){
        reemplazarPadre=reemplazo;
        reemplazo=aux;
        aux=aux->hijoIzquierdo;
    }

    if(reemplazo!=nodoReemp->hijoDerecho){
        reemplazarPadre->hijoIzquierdo = reemplazo->hijoDerecho;
        reemplazo->hijoDerecho = nodoReemp->hijoDerecho;
    }

    return reemplazo;
}

void ArbolAVL::inOrden(NodoAVL *r){
    if(r){
        inOrden(r->hijoIzquierdo);

        contenido<<"\""<<r->dato
            <<"\"  [ label = \" Dato: "<<r->dato
            <<' '<<"\n Algo: "<<"4"
            <<' '<<"  \" shape = \"ellipse\" ] ; \n";

        if(r->hijoIzquierdo){
            contenido<<"\""<<r->dato<<"\"->\""<<r->hijoIzquierdo->dato<<"\";\n";
        }

        if(r->hijoDerecho){
            contenido<<"\""<<r->dato<<"\"->\""<<r->hijoDerecho->dato<<"\";\n";
        }

        inOrden(r->hijoDerecho);
    }
}

void ArbolAVL::graficar(NodoAVL *r){
    contenido.str("");

    inOrden(r);
    char *ruta="dot -Tpng /home/eduardo/Descargas/arbolavl.dot -o /home/eduardo/arbolavl.png";

    std::string tod=contenido.str(); //se concatena todo en una variable string
    char *pass=new char[tod.length()+1]; //se declara un char* aux q contendra todo lo de la variable "todo"
    strcpy(pass,tod.c_str());

    std::stringstream cuerpo;
    /*inicio del documento*/
    cuerpo <<"digraph G{\n node[shape=circle, style=filled];\n edge[color=blue];rankdir=UD \n ";

    cuerpo<<pass;
    cuerpo<< "\n}";
    std::string todo=cuerpo.str(); //se concatena todo en una variable string
    char *pass1=new char[todo.length()+1]; //se declara un char* aux q contendra todo lo de la variable "todo"
    strcpy(pass1,todo.c_str()); //se igualan los valores

    /*se escribe en el archivo*/
    FILE * pFile;
    pFile = fopen("/home/eduardo/Descargas/arbolavl.dot","w");
    if(pFile!=NULL){
        fputs (pass1,pFile);
        fclose (pFile);

        system(ruta);
    }
}
