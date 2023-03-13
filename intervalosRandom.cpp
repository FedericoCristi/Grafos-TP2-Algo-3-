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
 * bueno la idea del codigo es generar un conjunto de intervalos cuya union de el intervalo [0, 2n) donde n es la
 * cantidad de intervalos, este numero se genera de forma aleatoria
 * TODO: se podria agregar un valor que el codigo tome de entrada para determinar n
 * una cosa importante que dice el enunciado es que todos juntos forman un intervalo como ya dije, ademas los bordes
 * tienen que ser enteros asi que se usan todos los numeros entre 0 y n-1
 * IMPORTANTE ESTOY ASUMIENDO QUE ES SOBRE LOS REALES EXEPTO POR EL ULTIMO TRAMO ES RARO
 * entonces es cuestion de tirar minimos y maximos cosa de que cuando unas to do no te queden 2 intervalos separados
 * osea que sea to do como una "cadena"
 * para hacer eso parto del primer minimo que es 0 y el maximo lo tomo al azar entre 2 y 2n - 1 cosa de dejar espacio
 * para otro minimo en el medio luego hay que avanzar cuidadosamente siempre dejando fijandose de que no pueda surgir un
 * intervalo disjunto a la union de los primeros.
 * como el maximo esta en un elemento al ezar por la lista uso list cosa de que sea mas facil de eliminar
 * en cuanto a la estructura de los datos es extremadamente minimalista porque solo importan los intervalos asi que es
 * un vector de pares de enteros
 *TODO: lo que queda por hacer que simplemente no se hacerlo bien es que el codigo corra muchas veces y lo guarde en txt
 */
using namespace std;

int Tintervalos; //total de los intervalos
vector<pair<int, int>> intervaloS(0); //lista de intervalos
//vector<int> tablaPosicioneslibres(0);


void creoIntervalos() {
    list<int> maximos; // lista de posibles valores para ser maximos
    int proximoMin = 0; // el primer minimo siempre es el 0
    for (int i = 1; i < Tintervalos * 2; ++i) {//construyo la lista maximo
        maximos.push_back(i);
    }
    int mayorMaximo = 1;
    while (maximos.size() > 0) {
        int minimo = proximoMin;
        int maximo;
        int posMax = 0;
        bool teniaEspacio = true;//flag para ver si puedo seguir enganchando el resto del conjunto
        if (maximos.size() > 1) {
            if (mayorMaximo < *(++maximos.begin())) {//si me quede con casi un intevalo sin agujeros tengo que prevenir
                proximoMin = maximos.front();//que se cierre tiene que ser el segundo porque si el segundo es mas
                maximos.pop_front();//grande que el mayor alcanzado significa que cuanto mucho 2 valores estan por
                teniaEspacio = false;//debajo de el ultimo maximo por lo que si elegimos el proximo maximo
            }//funciona
            posMax = rand() % maximos.size();
        } else {
            teniaEspacio = false;
        }

        for (list<int>::iterator K = maximos.begin(); K != maximos.end(); ++K) {
            if (posMax == 0) {
                maximo = *K;
                mayorMaximo = max(mayorMaximo, maximo);
                maximos.erase(K);
                break;
            } else {
                posMax--;
            }
        }
        if (teniaEspacio) { // es importante fijarse que haya que seguir la recursion y que no
            proximoMin = maximos.front();// me lo haya guardado ya
            maximos.pop_front();
        }
        intervaloS.push_back(pair<int, int>(minimo, maximo));
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    //Tintervalos = 10;//rand() % 100 + 10;

    std::cin >> Tintervalos;

    creoIntervalos();

    cout << Tintervalos << std::endl;
    for (int i = 0; i < intervaloS.size(); ++i) {
        cout << intervaloS[i].first << " " << intervaloS[i].second << std::endl;
    }

    return 0;
}

