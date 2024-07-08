#include <iostream>
#include "modulo.h"
#include <fstream>   // libreria para escribir datos sobre csv
#include <algorithm> // libreria para usar funcion binary search
#include <chrono>    // libreria para medir el tiempo del algoritmo
#include <cmath>     // libreria para usar pow
#include <random>    // libreria con herramientas para crear arreglo de distribucion normal
using namespace std;

int main() {
    // N: numero de veces que se realiza la busqueda binaria sobre el array 
    // d: representa la desviacion estandar de la distribucion normal
    int N, d, b, tamano, tamano_sample; 
    long primer_num, ultimo_num, random_num_presente;
    bool presente1 = false;
    chrono::nanoseconds duration;

    // Direccion del csv donde se guardan los resultados
    string csv = "gap_coded_normal.csv";

    //Se usa para que las funciones al azar sean diferentes cada ejecucion
    srand(time(nullptr));

    // Se piden argumentos al usuario
    cout << "ingresa un numero N que representa las veces que se ejecutara el algoritmo " << endl;
    cin >> N;
    cout << "ingresa numero que representa tamaño del array" << endl;
    cin >> tamano;
    cout << "ingrese un numero d que representa la desviacion estandar" << endl;
    cin >> d;
    cout << "ingrese un numero b que representa los gaps del sample" << endl;
    cin >> b;

    // Creacion del array 
    long* array_explicito = crear_arreglo(tamano,d);

    //creacion del array con gap-coding
    long* gap_coded = crear_gap(tamano,array_explicito);
 
    // Se crea en sample con el b dado por el usuario
    tamano_sample = tamano / b;
    long* sample = crearsample(tamano_sample,b,array_explicito);

    // variables para facilitar la generacion de numeros a buscar
    primer_num = array_explicito[0];
    ultimo_num = array_explicito[tamano-1];

    double entropia = sacar_entropia(gap_coded, tamano);

    // N veces 
    // Se genera un numero entre el primer y ultimo numero del array
    // Se busca el numero y se guarda el tiempo en un csv
    for (int i = 0; i < N; i++) {
        random_num_presente = (rand()%(ultimo_num-primer_num)) + primer_num;

        // Busqueda y medicion de tiempo de numero al azar entre el primer y ultimo del arreglo
        devolvervalores(sample,gap_coded,random_num_presente,tamano_sample,b,presente1,duration);


        // En el csv se guarda:
        // la desviacion estandar con que se genero el arreglo
        // el tamaño del arreglo usado
        // el tamaño de los gaps
        // si el numero generado al azar estaba presente
        // lo que se tardo la busqueda binaria para el numero al azar
        // la entropia
        // un id que representa la distribucion del arreglo usado
        // un id que representa el metodo de representacion usado
        ofstream file(csv, std::ios::app);
        if (file.is_open()) {
            file << d << "," << tamano << "," << b << "," << presente1 << "," << duration.count() << "," << entropia << ",2" << ",2" << endl;
            file.close();
        } 
        else {
            cout << "No se encontro el archivo " << csv << endl;
        }
    }
    //se libera memoria
    delete[] array_explicito;
    delete[] gap_coded;
    delete[] sample;
    return 0;
}
