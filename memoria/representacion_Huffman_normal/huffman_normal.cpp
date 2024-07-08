#include <iostream>
#include <fstream>   // libreria para escribir datos sobre csv
#include <algorithm> // libreria para usar funcion binary search
#include <chrono>    // libreria para medir el tiempo del algoritmo
#include <cmath>     // libreria para usar pow
#include <random>    // libreria con herramientas para crear arreglo de distribucion normal
#include <queue>
#include <vector>
#include <unistd.h>
#include <sys/resource.h>
#include "modulo.h"
#define COUNT 10
#define csv "huffman_normal.csv"
using namespace std;

int main() {
    // N: numero de veces que se realiza la busqueda binaria sobre el array 
    // e: epsilon que afecta la generacion del array X[i] = X[i-1] + rand() % e, proporcional a la variabilidad del arreglo
    // pid: identificador del programa

    int N, d, b, tamano, tamano_sample; 
    long empirico, teorico;
    bool presente_vector;
    vector<node*> nodos;
    pid_t pid = getpid();

    //Se usa para que las funciones al azar sean diferentes cada ejecucion
    srand(time(nullptr));

    // Se pide al usuario los argumentos
    cout << "ingresa un numero N que representa las veces que se ejecutara el algoritmo " << endl;
    cin >> N;
    
    cout << "ingresa numero que representa tamaño del array" << endl;
    cin >> tamano;
    
    tamano = 10000000;
    N = 1;

    cout << "ingrese un numero d que representa la desviacion estandar" << endl;
    cin >> d;

    cout << "ingrese un numero b que representa los gaps del sample" << endl;
    cin >> b;

    teorico = (tamano * 8);


    for(int i = 0; i < N; i++){
        //creacion del array 
        long* array_explicito =  crear_arreglo(tamano, d);

        //creacion del array con gap-coding
        long* gap_coded = crear_gap(tamano, array_explicito);
        tamano_sample = tamano / b;
    
        // Se crea en sample con el b dado por el usuario
        long* sample = crearsample(tamano_sample, b, array_explicito);

        //puntero al arbol
        node *root = crear_arbol(tamano, gap_coded);

        delete[] array_explicito;
        delete[] gap_coded;

        if(root->height <= 7){
            char* array_codificado = new char[tamano-1]();
            empirico = getMemoryUsage(pid);
            delete[] array_codificado;
        } 
        else{
            if(root->height <= 15){
                short* array_codificado = new short[tamano-1]();
                empirico = getMemoryUsage(pid);
                delete[] array_codificado;
            }
            else{
                int* array_codificado = new int[tamano-1]();
                empirico = getMemoryUsage(pid);
                delete[] array_codificado;
            }
        }
   
        ofstream file(csv, std::ios::app);
        if (file.is_open()) {
            file << d << "," << tamano << "," << b << "," << root->height << "," << teorico <<  "," << empirico << ",1" << ",3" << endl;
            file.close();
        } 
        else {
            cout << "No se encontro el archivo " << csv << endl;
        }

        delete[] sample;
        liberarArbol(root);

    }
    return 0;
}


