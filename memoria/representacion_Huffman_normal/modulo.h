#ifndef ARREGLO_H
#define ARREGLO_H
#define csv "huffman_normal.csv"
#include <chrono>

struct node {
        int diff;
        float freq;
        bool interior;
        short height;
        struct node* left;
        struct node* right;
        };

struct Compare {
    bool operator()(node *const& n1, node *const& n2)
    {
        return n1->freq > n2->freq;
    }
};

struct simbolo {
        int num;
        float freq;
        };

long* crear_arreglo(int tamano, int d);

long* crear_gap(int tamano, long* arreglo);

long* crearsample(int tamano, int b ,long* arreglo);

double sacar_entropia(long* array, int tamaño);

long getMemoryUsage(pid_t pid);

node* crear_arbol(int tamaño, long* gap_coded);

void liberarArbol(node* root);

#endif
