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

node* crear_arbol(int tamaño, long* gap_coded);

void CasoChar(node* root, long* array_explicito, int N, int d, int b, int tamaño, int tamaño_sample, long* gap_coded, long* sample);

void CasoShort(node* root, long* array_explicito, int N, int d, int b, int tamaño, int tamaño_sample, long* gap_coded, long* sample);

void CasoInt(node* root, long* array_explicito, int N, int d, int b, int tamaño, int tamaño_sample, long* gap_coded, long* sample);

void BusquedaBinariaChar(long* array_explicito, int N, int tamaño_sample, long* sample, int d, int tamaño, int b, node* root, char* array_codificado, long* gap_coded);

void BusquedaBinariaShort(long* array_explicito, int N, int tamaño_sample, long* sample, int d, int tamaño, int b, node* root, short* array_codificado, long* gap_coded);

void BusquedaBinariaInt(long* array_explicito, int N, int tamaño_sample, long* sample, int d, int tamaño, int b, node* root, int* array_codificado, long* gap_coded);

void devolvervalores(long* sample, long* gap, long buscado, int tamano_sample,int b, 
                        bool &presente, std::chrono::nanoseconds &duration);

int CodeDiff(node* root, int diff);

int ProcessDiff(node* root, int diff, int binnary, int treeHeight);

int DecodeDiff(node* root, int codedDiff, int treeHeight);

double sacar_entropia(long* array, int tamaño);

#endif
