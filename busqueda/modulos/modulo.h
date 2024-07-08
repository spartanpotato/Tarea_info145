#ifndef ARREGLO_H
#define ARREGLO_H
#include <chrono>

int* crear_arreglo(int tamano, int e);

void devolvervalores(int* arreglo, int buscado, int tamano, bool &presente, std::chrono::duration<double> &duration);

#endif
