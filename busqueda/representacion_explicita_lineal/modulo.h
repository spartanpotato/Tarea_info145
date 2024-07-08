#ifndef ARREGLO_H
#define ARREGLO_H
#include <chrono>

struct simbolo {
        int num;
        float freq;
        };

long* crear_arreglo(int tamano, int e);

void devolvervalores(long* arreglo, long buscado, int tamano, bool &presente, std::chrono::nanoseconds &duration);

double sacar_entropia(long* array, int tamaño);

#endif
