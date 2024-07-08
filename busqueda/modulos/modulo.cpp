#include "modulo.h"
#include <chrono>
#include <algorithm>
#include <tuple>
#include <iostream>
using namespace std;

int* crear_arreglo(int tamano,int e){
    srand(time(nullptr));
    int incremento;
    static int* arreglo = new int[tamano];
    arreglo[0] = rand();
    for(int i=1 ; i<tamano ; i++){
        incremento = rand() % e;
        arreglo[i] = arreglo[i-1] + incremento;
    }
    return arreglo;
}

void devolvervalores(int* arreglo, int buscado, int tamano, bool &presente, std::chrono::duration<double> &duration){
    auto start = chrono::high_resolution_clock::now();
    presente = binary_search(arreglo, arreglo + tamano ,buscado);
    auto end = std::chrono::high_resolution_clock::now();
    duration = end - start;
}