#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <climits>
#include <vector>
using namespace std;
// OPCION CON 03: g++ -no-pie -c -m64 -O3 ej2.cpp -o ej2f.o && g++ -no-pie -O3 -o ./ej2 -m64 ej2f.o
// Compilacion tranqui: g++ -c ej2.cpp && g++ -o ej2.exe ej2.o

int CANT_FILAS; // Se inicializa en el main
int CANT_COLS; // Se inicializa en el main
int etiqDisp = 0;
int compConex = 0;
struct componenteConexa{
    int etiqueta;
};

// Funcion de Debug. Se puede comentar en la entrega
void debugDePobre(vector<componenteConexa*> *K){
    cout<<"[ ";
    for (int i = 0; i < K->size(); ++i){
        if(K->at(i)==nullptr){
            cout<<"0 ";
        }else{
            cout<<K->at(i)->etiqueta<<" ";
        }
    }
    cout<<"]"<<endl;
}

void borroComponentes(vector<componenteConexa*> *v_1){
    componenteConexa* punteroABorrar;
    bool borreUnaComponenteRecien = false;
    for(int i = 0; i<v_1->size(); ++i){
        if(v_1->at(i) != nullptr && !borreUnaComponenteRecien){
            punteroABorrar = v_1->at(i);
            borreUnaComponenteRecien = true;
            delete(v_1->at(i));
            //cout << "Se borro la memoria de " << punteroABorrar << ", ";
        }else if(v_1->at(i) != nullptr && borreUnaComponenteRecien){
            //cout << "Ya se borro la memoria de " << punteroABorrar << ", ";
        } else {
            borreUnaComponenteRecien = false;
            //cout << "Era null, ";
        }
    }
    //cout << endl;
}

void asignoComponenteConEtiqueta(vector<componenteConexa*> *v, int indice, int etiqueta){
    struct componenteConexa *componente;
    componente = (componenteConexa*) malloc(sizeof(struct componenteConexa));
    componente->etiqueta = etiqueta;
    v->at(indice) = componente;
    //cout << "Agregue una nueva componente en el indice "<< indice << " con la etiqueta: "<<etiqueta<<" guardando la posicion "<< v->at(indice) <<endl;
}

void apuntoAComponenteDeIzq(vector<componenteConexa*> *v, int indice){
    v->at(indice) = v->at(indice-1); 
    //cout << "En la posicion "<<indice<< " asigne la direccion: "<< v->at(indice)<< " que debe concordar con el de la izq, que es: "<< v->at(indice-1) <<endl;
}


void unificoComponenteConIzq(vector<componenteConexa*> *v, int indice){
    v->at(indice-1)->etiqueta = v->at(indice)->etiqueta; 
    //cout << "En la posicion "<<indice-1<< " asigne la etiqueta: "<< v->at(indice-1)->etiqueta<< " que debe concordar con el de la der, que es: "<< v->at(indice)->etiqueta <<endl;
}

void cargoPrimeraFila(vector<componenteConexa*> *v_1){
    int valorEnMatriz;
    for (int j = 0; j < CANT_COLS; j++){ 
        cin>>valorEnMatriz;
        if(j>0 && v_1->at(j-1)!=nullptr && valorEnMatriz==1){ 
            // Caso 1 1: Apunto a la misma componente que el de la izquierda
            //cout<< "--Estoy en la primera fila y hay un 1 1. Copio la componente de la izq" << endl;
            apuntoAComponenteDeIzq(v_1, j);
        } else if((j==0 && valorEnMatriz==1) || (j>0 && v_1->at(j-1)==nullptr && valorEnMatriz==1)){ 
            // Caso - 1 y Caso 0 1: Aumento mi etiqueta. Es una nueva componente
            etiqDisp++;
            compConex++; 
            //cout<< "--Estoy en la primera fila y hay un 0 1 o - 1. Creo una nueva" << endl;
            asignoComponenteConEtiqueta(v_1, j, etiqDisp);
            } // Caso 1 0 y Caso 0 0: no hago nada
    }
}

void cargoRestoFilas(vector<componenteConexa*> *v_1, vector<componenteConexa*> *v_2){
    //*** Cargo el resto de filas de la Matriz
    for (int i = 0; i < CANT_FILAS-1; i++){
        int valorEnMatriz;
        for (int j = 0; j < CANT_COLS; j++){
            cin>>valorEnMatriz;
            //cout << "++leyo un "<< valorEnMatriz<<endl;
            if(valorEnMatriz==1){
                if(v_1->at(j)==nullptr){ 
                    //* Caso 0 arriba
                    if (j==0 || (j>0 && v_2->at(j-1)==nullptr)){ 
                        // Caso - 1 o Caso 0 1: Aumento mi etiqueta. Es una nueva componente
                        etiqDisp++;
                        compConex++; 
                        //cout<< "--Estoy en la " << (i+1) << " fila y hay un 0 1 o - 1. Creo una nueva" << endl;
                        asignoComponenteConEtiqueta(v_2, j, etiqDisp);
                    } else { 
                        // Caso 1 1: Apunto a la misma componente que el de la izquierda
                        //cout<< "--Estoy en la " << (i+1) << " fila y hay un 1 1. Copio la de la izquierda" << endl;
                        apuntoAComponenteDeIzq(v_2, j);
                    }
                } else { 
                    //* Caso 1 arriba 
                    int etiquetaArriba = v_1->at(j)->etiqueta;
                    if (j>0 && v_2->at(j-1)!=nullptr){ 
                        // Caso 1 1: Son todas la misma componente que arriba
                        //cout<< "--Estoy en la " << (i+1) << " fila y hay 1 1 y un 1 arriba. Copio la de la izquierda "<< endl;
                        apuntoAComponenteDeIzq(v_2, j);
                        //cout << "--Comparo etiqueta izq: "<<v_2->at(j-1)->etiqueta<<" con arriba: "<<etiquetaArriba<<endl;
                        if(v_2->at(j-1)->etiqueta != etiquetaArriba){
                            //Si la etiqueta de la izquierda es distinta a la de arriba, descuento una componente y pongo la misma etiqueta de arriba
                            compConex--;
                            //cout<< "--Tenian distinta etiqueta, se la asigno a la de la izquierda" << endl;
                            v_2->at(j)->etiqueta = etiquetaArriba;
                            //unificoComponenteConIzq(v_2, j);
                        } 
                    } else {
                        // Caso - 1 o Caso 0 1: Ya tomo la componente de arriba
                        // Creo una componente conexa nueva y le copio la etiqueta del de arriba (para no depender de CC de filas anteriores)
                        //cout<< "--Estoy en la " << (i+1) << " fila y hay un 1 arriba. Creo una con esa etiqueta" << endl;
                        asignoComponenteConEtiqueta(v_2, j, etiquetaArriba);
                    }
                }   
            }else{
                v_2->at(j) = nullptr;
            }
            //cout<<"--VALOR EN V_2: "<<v_2->at(j)<<endl;
        }
        
        //**Borro las componentes de la fila a borrar
        borroComponentes(v_1);

        //** El vector de abajo pasa a ser el de arriba
        for(int i = 0; i < CANT_COLS; i++){
            v_1->at(i) = v_2->at(i);
        }
    }
}

int main(int argc, char *argv[]){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    //*** Leo la primera fila
    cin >> CANT_FILAS >> CANT_COLS;
    
    //*** Caso base
    if(CANT_FILAS == 0 || CANT_COLS == 0){cout<<0<<endl; return 0;}

    //*** Creo mis dos vectores
    vector<componenteConexa*> v_1(CANT_COLS, nullptr);
    vector<componenteConexa*> v_2(CANT_COLS, nullptr);
    etiqDisp = 0;
    compConex = 0;

    cargoPrimeraFila(&v_1);
    cargoRestoFilas(&v_1, &v_2);
    borroComponentes(&v_1);
    
    cout<<compConex<<endl;
    return 0;
}
