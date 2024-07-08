#include "modulo.h"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

// Devuelve el array explcitio con distribucion normal
long* crear_arreglo(int tamano, int d){

    srand(time(nullptr));
    static long* arreglo = new long[tamano];
    int media = rand();
    
    default_random_engine generator(rand());
    normal_distribution<double> distribution(media, d);

    for (int i = 0; i < tamano; i++) {
        arreglo[i] = round(distribution(generator));
    }
    
    sort(arreglo,arreglo+tamano);
    return arreglo;
}

// Guarda el tiempo que tarda terminar una busqueda binaria del elemento buscado en el arreglo
void devolvervalores(long* arreglo, long buscado, int tamano, bool &presente, chrono::nanoseconds &duration){
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