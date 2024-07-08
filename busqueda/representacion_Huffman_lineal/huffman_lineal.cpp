#include <iostream>
#include <fstream>   // libreria para escribir datos sobre csv
#include <algorithm> // libreria para usar funcion binary search
#include <chrono>    // libreria para medir el tiempo del algoritmo
#include <cmath>     // libreria para usar pow
#include <queue>     // se usa como minheap
#include <vector>
#include "modulo.h"
#define COUNT 10
#define csv "huffman_lineal.csv"
using namespace std;


int main() {
    // N: numero de veces que se realiza la busqueda binaria sobre el array 
    // e: epsilon que afecta la generacion del array X[i] = X[i-1] + rand() % e, proporcional a la variabilidad del arreglo
    int N, e, b, tamaño, tamaño_sample; 

    //Se usa para que las funciones al azar sean diferentes cada ejecucion
    srand(time(nullptr));

    // Se piden argumentos al usuario
    cout << "ingresa un numero N que representa las veces que se ejecutara el algoritmo " << endl;
    cin >> N;
    cout << "ingresa numero que representa tamaño del array" << endl;
    cin >> tamaño;
    cout << "ingrese un numero e que afecta la creacion del array X[i] = X[i-1] + rand() '%' e" << endl;
    cin >> e;
    cout << "ingrese un numero b que representa los gaps del sample" << endl;
    cin >> b;

    //creacion del array 
    long* array_explicito =  crear_arreglo(tamaño, e);

    //creacion del array con gap-coding
    long* gap_coded = crear_gap(tamaño, array_explicito);
    tamaño_sample = tamaño / b;
 
    // Se crea en sample con el b dado por el usuario
    long* sample = crearsample(tamaño_sample, b, array_explicito);

    
    // Se crea el arbol de huffman a partir del array gap_coded
    node *root = crear_arbol(tamaño, gap_coded); 

    //Dependiendo de la altura del arbol se creara un array codificado de distinto tipo
    if(root->height <= 7){
        // Sea crea y realiza la busqueda sobre un array codificado de char
        CasoChar(root, array_explicito, N, e, b, tamaño, tamaño_sample, gap_coded, sample);
    } 
    else{
        if(root->height <= 15){
            // Sea crea y realiza la busqueda sobre un array codificado de short
            CasoShort(root, array_explicito, N, e, b, tamaño, tamaño_sample, gap_coded, sample);
        }
        else{
            // Sea crea y realiza la busqueda sobre un array codificado de int
            CasoInt(root, array_explicito, N, e, b, tamaño, tamaño_sample, gap_coded, sample);
        }
    }


    //se libera memoria
    delete[] array_explicito;
    delete[] gap_coded;
    delete[] sample;
    return 0;
}


