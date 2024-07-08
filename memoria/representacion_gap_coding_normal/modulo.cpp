#include "modulo.h"
#include <chrono>
#include <algorithm>
#include <random>
#include <iostream>
#include <sys/resource.h>
#include <unistd.h>
#include <fstream> 
using namespace std;

// Devuelve el array explicito con distribucion normal
long* crear_arreglo(int tamano, int d){

    srand(time(nullptr));
    long* arreglo = new long[tamano];
    
    int media = rand();
    
    default_random_engine generator(rand());
    normal_distribution<double> distribution(media, d);

    for (int i = 0; i < tamano; i++) {
        arreglo[i] = round(distribution(generator));
    }
    
    sort(arreglo,arreglo+tamano);
    return arreglo;
}

// Devuelve el array gap_coded creado a partir del explicito
long* crear_gap(int tamano, long* arreglo){
    long* gap = new long[tamano];
    gap[0] = arreglo[0];
    for (int i = 1; i < tamano; i++) {
        gap[i] = arreglo[i] - arreglo[i-1];
    }
    return gap;
}

// Devuelve el sample creado a partir del array explicito
long* crearsample(int tamano,int b,long* arreglo){
    long* sample = new long[tamano];
    for (int i = 0; i < tamano; i++) {
       sample[i] = arreglo[i*b];
    }
    return sample;
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

//Funcion que retorna la memoria usada en cierto momento de la ejecución
long getMemoryUsage(pid_t pid) {
    // Se abre el archivo en el que se encuentra el estado del programa
    ifstream statusFile("/proc/" + to_string(pid) + "/status");
    string line;
    long memBytes;

    // Mientras sigan habiendo lineas por leer
    while (getline(statusFile, line)) {
        // Si se encuentra 'VmRRS' en la línea
        if (line.find("VmRSS:") != string::npos) {
            // Encuentra la posición donde empieza el valor de los kB
            size_t pos = line.find_first_of("0123456789");
            if (pos != string::npos) {
                // Se extraen los kB en un string
                string memStr = line.substr(pos);
                // Convierte a long
                long memKb = stol(memStr);
                // Convierte a bytes para futura comparación
                memBytes = memKb * 1024;
            }
            break;
        }
    }
    return memBytes;
}