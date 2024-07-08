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

void devolvervalores(long* sample, long* gap, long buscado, int tamano_sample,int b, 
                        bool &presente, std::chrono::nanoseconds &duration);

double sacar_entropia(long* array, int tamaño);


#endif
