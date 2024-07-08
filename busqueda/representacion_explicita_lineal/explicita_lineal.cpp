#include "modulo.h"
#include <iostream>
#include <fstream>   // libreria para escribir datos sobre csv
#include <algorithm> // libreria para usar funcion binary search
#include <chrono>    // libreria para medir el tiempo del algoritmo
#include <cmath>     // libreria para usar pow
using namespace std;


int main() {
    // N: numero de veces que se realiza la busqueda binaria sobre el array 
    // e: epsilon que afecta la generacion del array X[i] = X[i-1] + rand() % e, proporcional a la variabilidad del arreglo
    int N, e, tamano; 
    long primer_num, ultimo_num, random_num_presente;
    bool presente1;
    chrono::nanoseconds duration;

    // Direccion del csv donde se guardan los resultados
    string csv = "explicita_lineal.csv";

    //Se usa para que las funciones al azar sean diferentes cada ejecucion
    srand(time(nullptr));

    // Se piden argumentos al usuario
    cout << "ingresa un numero N que representa las veces que se ejecutara el algoritmo " << endl;
    cin >> N;
    cout << "ingresa numero que representa tamano del array" << endl;
    cin >> tamano;
    cout << "ingrese un numero e que afecta la creacion del array X[i] = X[i-1] + rand() '%' e" << endl;
    cin >> e;

    // Creacion del array 
    long* array_explicito = crear_arreglo(tamano,e);

    // Variables para facilitar la generacion de numeros a buscar
    primer_num = array_explicito[0];
    ultimo_num = array_explicito[tamano-1];

    // Se obtiene la entropia del array
    double entropia = sacar_entropia(array_explicito, tamano);

    // N veces 
    // Se genera un numero entre el primer y ultimo numero del array
    // Se busca el numero y se guarda el tiempo en un csv
    for (int i = 0; i < N; i++) {
        random_num_presente = (rand()%(ultimo_num-primer_num)) + primer_num;

        // Busqueda y medicion de tiempo de numero al azar entre el primer y ultimo del arreglo
        devolvervalores(array_explicito,random_num_presente,tamano,presente1,duration);

        // En el csv se guarda:
        // el epsilon con que se genero el arreglo
        // el tamano del arreglo usado
        // si el numero generado al azar estaba presente
        // lo que se tardo la busqueda binaria para el numero al azar
        // la entropia
        // un id que representa la distribucion del arreglo usado
        // un id que representa el metodo de representacion usado
        ofstream file(csv, std::ios::app);
        if (file.is_open()) {
            file << e << ", " << tamano << ", " << presente1 << ", " << duration.count() << "," << entropia << ",1 " << ",1" << endl;
            file.close();
        } 
        else {
            cout << "No se encontro el archivo " << csv << endl;
        }
    }
    // Se libera memoria
    delete[] array_explicito;
    return 0;
}



