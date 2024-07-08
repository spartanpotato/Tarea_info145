#include "modulo.h"
#include <chrono>
#include <algorithm>
#include <iostream>
using namespace std;

// Devuelve el array explicito con distribucion lineal
long* crear_arreglo(int tamano,int e){
    srand(time(nullptr));
    int incremento;
    static long* arreglo = new long[tamano];
    arreglo[0] = rand();
    for(int i=1 ; i<tamano ; i++){
        incremento = rand() % e;
        arreglo[i] = arreglo[i-1] + incremento;
    }
    return arreglo;
}

// Devuelve el array gap_coded creado a partir del explicito
long* crear_gap(int tamano, long* arreglo){
    static long* gap = new long[tamano];
    gap[0] = arreglo[0];
    for (int i = 1; i < tamano; i++) {
        gap[i] = arreglo[i] - arreglo[i-1];
    }
    return gap;
}

// Devuelve el sample creado a partir del array explicito
long* crearsample(int tamano, int b, long* arreglo){
    static long* sample = new long[tamano];
    for (int i = 0; i < tamano; i++) {
       sample[i] = arreglo[i*b];
    }
    return sample;
}

// Guarda el tiempo que tarda terminar una busqueda binaria del elemento buscado en el arreglo
void devolvervalores(long* sample, long* gap, long buscado, int tamano_sample,int b, 
                        bool &presente, std::chrono::nanoseconds &duration){
    auto start = chrono::high_resolution_clock::now();
    int tamano = tamano_sample*b;
    // Se usa lower_bound que usa busqueda binaria para encontrar al
    // primer elemento mayor o igual que el que se busca
    long *indice1 = lower_bound(sample, sample+tamano_sample, buscado);
    // Si lower_bound encuentra el numero, se guarda true en un booleano y se termina
    if(*indice1 == buscado){
        presente = true;
    }
    // Si no se busca en el arreglo de gap-coding
    else{
        // Se usa distance para obtener el indice anterior al encontrado por lower_bound
        // y se multiplica por b para encontrar indice equivalente en arreglo gap-coding
        int index_start = b * (distance(sample, indice1) - 1);
        // Se guarda el indice menor entre el ultimo del array gap-coding 
        // y el guardado anteriormente mas b, con tal de no pasarse de rango
        int index_end = min(index_start + b, tamano-1);
        // Se guarda el valor anterior al encontrado por lower_bound
        long valor_actual = *(indice1 - 1);
        index_start++;
        // Se va a buscar el numero en el array gap-coding hasta que termine el 
        // intervalo de busqueda o se encuentre
        // Para buscarlo se toma el valor guardado de en valor_actual y se le 
        // suman las diferencias del array gap-coding
        while (index_start < index_end && valor_actual <= buscado){
            valor_actual = valor_actual + gap[index_start];
            if(valor_actual == buscado){
                presente = true;
                break;
            }
            index_start++;
        } 
    }
    auto end = std::chrono::high_resolution_clock::now();
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