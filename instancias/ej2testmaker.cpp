#include <stdio.h>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;
// OPCION CON 03: g++ -no-pie -c -m64 -O3 ej2.cpp -o ej2f.o && g++ -no-pie -O3 -o ./ej2 -m64 ej2f.o
// Compilacion tranqui: g++ -c ej2testmaker.cpp && g++ -o ej2testmaker.exe ej2testmaker.o
// Para correrlo: ./ej2testmaker.exe > nombreDelArchivo.txt

int CANT_FILAS = 1000;
int CANT_COLS = 1000;
static std::random_device rd; 
static std::mt19937_64 rng(rd()); // Mersennes' twister c/seed

int random_int(int initial, int last) {
    std::uniform_int_distribution<int> distribution(initial, last);
    return distribution(rng); 
}

int main(int argc, char *argv[]){    
    // *** Escribo la primera fila
    cout<<CANT_FILAS<<" "<<CANT_COLS<<endl;
    
    for (int i = 0; i < CANT_FILAS; ++i)
    {
        for (int j = 0; j < CANT_COLS; ++j){
            cout<<random_int(0,1)<< " ";
        }
        cout<<endl;
    }
    return 0;
}
