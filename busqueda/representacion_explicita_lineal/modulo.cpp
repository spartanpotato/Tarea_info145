#include "modulo.h"
#include <chrono>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <cmath>
using namespace std;

// Devuelve el array explicito con distribucion lineal
long* crear_arreglo(int tamano,int e){
    srand(time(nullptr));
    int incremento;
    static long* arreglo = new long[tamano];
    arreglo[0] = 0;
    for(int i=1 ; i<tamano ; i++){
        incremento = rand() % e;
        arreglo[i] = arreglo[i-1] + incremento;
    }
    return arreglo;
}

// Guarda el tiempo que tarda terminar una busqueda binaria del elemento buscado en el arreglo
void devolvervalores(long* arreglo, long buscado, int tamano, bool &presente, std::chrono::nanoseconds &duration){
    auto start = chrono::high_resolution_clock::now();
    presente = binary_search(arreglo, arreglo + tamano ,buscado);
    auto end = chrono::high_resolution_clock::now();
    duration = end - start;
}

// Obtiene entropia media del array
double sacar_entropia(long* array, int tamaño){
    double entropia = 0;
    double aux;
    vector<simbolo*> temp;

    simbolo* nuevo = new simbolo();
    nuevo->num = array[0];
    nuevo->freq = 1;
    temp.push_back(nuevo);

    for (int i = 1; i < tamaño; i++){
        for (int j = 0; j < temp.size(); j++){
            if (temp.at(j)->num == array[i]){
                temp.at(j)->freq++;
                break;
            }
        }
        simbolo* nuevo = new simbolo();
        nuevo->num = array[i];
        nuevo->freq = 1;
        temp.push_back(nuevo);
    }

    for (int i = 0; i < temp.size(); i++){
        aux = (temp.at(i)->freq/tamaño) * (log2(tamaño/temp.at(i)->freq));
        entropia = entropia + aux;
    }

    return entropia;
}   