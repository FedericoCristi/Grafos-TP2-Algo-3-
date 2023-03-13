#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <iostream>
#include <time.h>
/*
 * bueno la idea del codigo es generar un conjunto de nodos de forma aleatoria con el formato de las intancias del tp
 * pasado en principio con un tamanio entre 10 y 100
 * TODO: se podria agregar un valor que el codigo tome de entrada para determinar el tamanio de los nodos
 * en cuanto a la estructura de los datos es extremadamente minimalista porque no se necesitan hacer muchas operaciones
 * solo guardar las aristas, asi que es basicamente una lista de aristas con peso con una cantidad de nodos.
 * las aristas surgen de forma aleatoria y para aumentar los tipos de grafos que puedan aparecer la probabilidad de que
 * dados 2 nodos tengan una arista es un valor aleatorio generado entre 10% y 60% (me di cuenta que entre estos 2
 * valores pasas rapidamente de tener casi no aristas a un digrafo muy conexo)
 *TODO: lo que queda por hacer que simplemente no se hacerlo bien es que el codigo corra muchas veces y lo guarde en txt
 */
using namespace std;

int Tnodos; //total de los nodos
int cantAristas = 0; //total de las aristas
int probabilidadDeArista; //probabilidad de que haya una arista entre 2 nodos
vector<vector<int>> aristaSPesadas(0); //lista de aristas con sus pesos
int pesoMaximo;
int probabilidadPesoNegativo;

void crearArista(int i, int j) {
    cantAristas++;
    vector<int> arista(3);
    arista[0] = i;
    arista[1] = j;
    int peso = rand() % pesoMaximo;
    int esNegativa = rand() % 20;
    if(probabilidadPesoNegativo > esNegativa){peso = peso * -1;}
    arista[2] = peso;
    aristaSPesadas.push_back(arista);
}

void creoDigrafoPesado() {              // esto genera las primeras aristas de un grafo de Tnodos despues hay que
    for (int i = 0; i < Tnodos; ++i) { // agregar para que sea conexo
        for (int j = 0; j < Tnodos; ++j) {
            if (i != j){
                int random = rand() % 100;
                if (random < probabilidadDeArista) { //aca se puede jugar con la probabilidad de que aparezcan aristas
                    crearArista(i, j);
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));
    Tnodos = rand() % 100 + 10;
    probabilidadDeArista = rand() % 60 + 10;
    pesoMaximo = rand() % 100 + 10;
    probabilidadPesoNegativo = rand() % 10;
    creoDigrafoPesado();

    /* COMENTARIO DE DEBUG
    for (int i = 0; i < aristaS.size(); ++i) {
        cout << i << ":" << aristaS[i][0] << " " << aristaS[i][1] << std::endl;
    }*/

    cout << "p edge " << Tnodos << " " << cantAristas << std::endl;
    for (int i = 0; i < Tnodos - 1; ++i) {
        cout << "n " << i + 1 << " " << i + 2 << std::endl;
    }
    cout << "n " << Tnodos << " " << 1 << std::endl;
    for (int j = 0; j < aristaSPesadas.size(); ++j) {
        cout << "e " << aristaSPesadas[j][0] + 1 << " " << aristaSPesadas[j][1] + 1 //nodos de la arista
        << " " << aristaSPesadas[j][2] <<std::endl; //peso de la arista
    }
    return 0;
}
