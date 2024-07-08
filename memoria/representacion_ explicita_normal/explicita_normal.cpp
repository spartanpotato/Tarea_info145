#include <iostream>
#include "modulo.h"
#include <fstream>   // libreria para escribir datos sobre csv
#include <algorithm> // libreria para usar funcion binary search
#include <chrono>    // libreria para medir el tiempo del algoritmo
#include <cmath>     // libreria para usar pow
#include <random>    // libreria con herramientas para crear arreglo de distribucion normal
#include <sys/resource.h>
#include <unistd.h>
using namespace std;

int main() {
    // N: numero de veces que se realiza la busqueda binaria sobre el array 
    // d: representa la desviacion estandar de la distribucion normal
    // pid: identificador del programa
    int N, d, tamano; 
    long teorico, memoria;
    pid_t pid = getpid();

    // Direccion del csv donde se guardan los resultados
    string csv = "explicita_normal.csv";

    //Se usa para que las funciones al azar sean diferentes cada ejecucion
    srand(time(nullptr));

    // Se pide al usuario los argumentos
    cout << "ingresa un numero N que representa las veces que se ejecutara el algoritmo " << endl;
    cin >> N;
    cout << "ingresa numero que representa tamano del array" << endl;
    cin >> tamano;
    cout << "ingrese un numero d que representa la desviacion estandar" << endl;
    cin >> d;

    teorico = sizeof(long) * tamano;

    // N veces crea el array, guarda la memoria, elimina el array y sube la info al csv
    for (int i = 0; i < N; i++) {
        long* array_explicito = crear_arreglo(tamano, d); 

        memoria = getMemoryUsage(pid);

        delete[] array_explicito;

        ofstream file(csv, std::ios::app);
        if (file.is_open()) {
            file << d << "," << tamano << "," << teorico  << "," << memoria << ",2" << ",1" << endl;
            file.close();
        } 
        else {
            cout << "No se encontro el archivo " << csv << endl;
        }
    }
    return 0;
}
