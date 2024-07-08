#ifndef ARREGLO_H
#define ARREGLO_H
#include <chrono>

struct simbolo {
        int num;
        float freq;
        };

long* crear_arreglo(int tamano, int d);

double sacar_entropia(long* array, int tamaño);

long getMemoryUsage(pid_t pid);

#endif
