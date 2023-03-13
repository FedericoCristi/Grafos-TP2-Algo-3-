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
 * solo guardar las aristas y chequear que el grafo sea conexo, asi que es basicamente una lista de aristas con una
 * cantidad de nodos. las aristas surgen de forma aleatoria y para aumentar los tipos de grafos que puedan aparecer
 * la probabilidad de que dados 2 nodos tengan una arista es un valor aleatorio generado entre 10% y 60% (me di cuenta
 * que entre estos 2 valores pasas rapidamente de tener un arbol a un grafo muy conexo)
 * Existe el extra de que tiene que ser conexo por lo que uso la idea de kruskal de etiquetar los
 * conjuntos conexos y despues solo queda unir de forma ALEATORIA el problema con esto es que para elegir aleatoriamente
 * entre 2 conjuntos conexos no se me ocurrio de otra que explicitarlos en una lista de listas y luego elegir 2 nodos
 * al azar uno de cada arista para unirlos30
 *TODO: lo que queda por hacer que simplemente no se hacerlo bien es que el codigo corra muchas veces y lo guarde en txt
 */
using namespace std;

int Tnodos; //total de los nodos
int cantAristas = 0; //total de las aristas
vector<vector<int>> aristaS(0); //lista de aristas
int probabilidadDeArista; //probabilidad de que haya una arista entre 2 nodos

struct UF { //esto lo saque del codigo que dieron en la practica de kruskal es basicamente lo de las etiquetas
    //Vector con los parents y vector con tamaños
    vector<int> p, s;

    UF(int n) : p(n, -1), s(n, 1) {}

    //Hace la unión y devuelve el tamaño del resultante
    int unite(int v, int w) {
        v = find(v);
        w = find(w);
        if (v == w) return s[v];
        if (s[v] < s[w]) swap(v, w);
        p[w] = v; //El árbol de mayor tamaño queda como padre
        return s[v] += s[w];
    }

    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]); //Recursión para path compression
    }

};

void crearArista(int i, int j) {
    cantAristas++;
    vector<int> arista(2);
    arista[0] = i;
    arista[1] = j;
    aristaS.push_back(arista);
}

void creoGrafoNoConexo() {              // esto genera las primeras aristas de un grafo de Tnodos despues hay que
    for (int i = 0; i < Tnodos; ++i) { // agregar para que sea conexo
        for (int j = i + 1; j < Tnodos; ++j) {
            //srand(time(NULL));
            int random = rand() % 100;
            if (random < probabilidadDeArista) { //aca se puede jugar con la probabilidad de que aparezcan aristas
                crearArista(i, j);       //y que este cerca de estar conexo
            }
        }
    }
}

void unirVectors(vector<int> &prim, vector<int> &fin) {
    for (int i = 0; i < fin.size(); ++i) {
        prim.push_back(fin[i]);
    }
}

void unirVecindarios(vector<vector<int>> &vecindarios) {//esta funcion agarra 2 subgrafos conexos y los une tomando
    while (vecindarios.size() > 1) {                       // al azar un nodo de cada subgrafo
        //srand(time(NULL));
        int prim = rand() % (vecindarios.front()).size();
        //srand(time(NULL));
        int fin = rand() % (vecindarios.back()).size();
        /* COMENTARIO DE DEBUG
        cout << "el nodo elegido es: " << prim << " y " << fin
        << "el largo de fin es" << (vecindarios.back()).size() << std::endl;*/
        crearArista(vecindarios.front()[prim], vecindarios.back()[fin]);
        unirVectors(vecindarios.front(), vecindarios.back());
        vecindarios.pop_back();
    }
}

int main() {
    srand(time(NULL));
    Tnodos = rand() % 100 + 10;
    probabilidadDeArista = rand() % 60 + 10;
    creoGrafoNoConexo();
    /* COMENTARIO DE DEBUG
    for (int i = 0; i < aristaS.size(); ++i) {
        cout << i << ":" << aristaS[i][0] << " " << aristaS[i][1] << std::endl;
    }*/

    UF componentes(Tnodos);
    for (int k = 0; k < aristaS.size(); ++k) { //veo cuales son las componentes conexas
        componentes.unite(aristaS[k][0], aristaS[k][1]);
    }

    vector<vector<int>> vecindarios(0);//explicito las componentes conexas
    vecindarios.push_back(vector<int>(1, 0));
    for (int l = 1; l < Tnodos; ++l) {
        bool nuevovecindario = true;
        for (int h = 0; h < vecindarios.size() && nuevovecindario; ++h) {
            if (componentes.find(vecindarios[h].front()) == componentes.find(l)) {
                vecindarios[h].push_back(l);
                nuevovecindario = false;
            }
        }
        if (nuevovecindario) {
            vecindarios.push_back(vector<int>(1, l));
        }
    }
    /*COMENTARIO DE DEBUG
     for (int i = 0; i < vecindarios.size(); ++i) {
        cout << i << ":" << std::endl;
        for (int j = 0; j < vecindarios[i].size(); ++j) {
            cout << vecindarios[i][j] << std::endl;
        }
    }*/

    unirVecindarios(vecindarios);//ahora que estan explicitados puedo crear puentes para unir a los subgrafos

    cout << "p edge " << Tnodos << " " << cantAristas << std::endl;
    for (int i = 0; i < Tnodos - 1; ++i) {
        cout << "n " << i + 1 << " " << i + 2 << std::endl;
    }
    cout << "n " << Tnodos << " " << 1 << std::endl;
    for (int j = 0; j < aristaS.size(); ++j) {
        cout << "e " << aristaS[j][0] + 1 << " " << aristaS[j][1] + 1 << std::endl;
    }
    return 0;
}



