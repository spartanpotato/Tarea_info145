#ifndef ARREGLO_H
#define ARREGLO_H
#include <chrono>

struct simbolo {
        int num;
        float freq;
        };

long* crear_arreglo(int tamano, int d);

long* crear_gap(int tamano, long* arreglo);

long* crearsample(int tamano,int b ,long* arreglo);

long getMemoryUsage(pid_t pid); 

double sacar_entropia(long* array, int tamaño);


#endif
