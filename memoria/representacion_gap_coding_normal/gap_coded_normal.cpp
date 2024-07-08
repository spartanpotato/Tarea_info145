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
    // e: epsilon que afecta la generacion del array X[i] = X[i-1] + rand() % e, proporcional a la variabilidad del arreglo
    // pid: identificador del programa
    int N, d, b, tamano, tamano_sample; 
    long empirico, teorico;
    pid_t pid = getpid();

    // Direccion del csv donde se guardan los resultados
    string csv = "gap_coded_normal.csv";

    //Se usa para que las funciones al azar sean diferentes cada ejecucion
    srand(time(nullptr));

    // Se pide al usuario los argumentos
    cout << "ingresa un numero N que representa las veces que se ejecutara el algoritmo " << endl;
    cin >> N;
    cout << "ingresa numero que representa tamaño del array" << endl;
    cin >> tamano;
    cout << "ingrese un numero b que representa los gaps del sample" << endl;
    cin >> b;
    cout << "ingrese un numero d que representa la desviacion estandar" << endl;
    cin >> d;
    
    teorico = (tamano * 8) + ((tamano / b) * 8);

    tamano_sample = tamano / b;

    // N veces crea el array, gap_coded, sample
    // se elimina el array explicito y se guarda la memoria
    // se eliminan el gap_coded y sample y guardan los datos en el csv
    for (int i = 0; i < N; i++) {
        
        long* array_explicito = crear_arreglo(tamano, d);

        long* gap_coded = crear_gap(tamano, array_explicito);

        long* sample = crearsample(tamano_sample, b, array_explicito);

        delete[] array_explicito;

        empirico = getMemoryUsage(pid);

        delete[] gap_coded;
        delete[] sample;

        ofstream file(csv, std::ios::app);
        if (file.is_open()) {
            file << d << "," << tamano << "," << b << "," << teorico << "," << empirico << ",2" << ",2" << endl;
            file.close();
        } 
        else {
            cout << "No se encontro el archivo " << csv << endl;
        }
    }
    return 0;
}
