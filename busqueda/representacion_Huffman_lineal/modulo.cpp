#include "modulo.h"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

// Devuelve el array explicito con distribucion lineal
long* crear_arreglo(int tamano,int e){
    srand(time(nullptr));
    int incremento;
    static long* arreglo = new long[tamano];
    arreglo[0] = rand();
    for(int i=1 ; i<tamano ; i++){
        incremento = rand() % e;
        arreglo[i] = arreglo[i-1] + incremento;
    }
    return arreglo;
}

// Devuelve el array gap_coded creado a partir del explicito
long* crear_gap(int tamano, long* arreglo){
    static long* gap = new long[tamano];
    gap[0] = arreglo[0];
    for (int i = 1; i < tamano; i++) {
        gap[i] = arreglo[i] - arreglo[i-1];
    }
    return gap;
}

// Devuelve el sample creado a partir del array explicito
long* crearsample(int tamano, int b, long* arreglo){
    static long* sample = new long[tamano];
    for (int i = 0; i < tamano; i++) {
       sample[i] = arreglo[i*b];
    }
    return sample;
}

// Crea el arbol de huffman a partir del array gap_coded
node* crear_arbol(int tamaño, long* gap_coded){
    bool presente_vector;
    vector<node*> nodos;
    // Se guardan las frecuencias de las diferencias y el primer elemento
    for (int i = 1; i < tamaño; i++){
        presente_vector = false;
        for (node* nodo : nodos) {
            if (nodo->diff == gap_coded[i]) {
                nodo->freq++;
                presente_vector = true;
                break;
            }
        }
        if(presente_vector == false){
            node *nuevo_nodo = new node();
            nuevo_nodo->diff = gap_coded[i];
            nuevo_nodo->freq = 1;
            nuevo_nodo->interior = false;
            nuevo_nodo->height = 0;
            nodos.push_back(nuevo_nodo);
        }
    }

    // Se crea un min-heap usando priority queue con el vector de frecuencias
    priority_queue<node*, vector<node*>, Compare> Q;
    for (int i = 0; i < nodos.size(); i++){
        nodos.at(i)->freq = nodos.at(i)->freq / tamaño;
        Q.push(nodos.at(i));
    }

    // Se crea el arbol de Huffman
    while(Q.size() >= 2){
        node *z = new node();
        node *x = Q.top();
        Q.pop();
        node *y = Q.top();
        Q.pop();
        z->left = x;
        z->right = y;
        z->freq = x->freq + y->freq;
        z->interior = true;
        z->height = max(x->height+1, y->height+1);
        Q.push(z);
    }

    //puntero al arbol
    node *root = Q.top(); 
    Q.pop();

    return root;
}

// Inicializa ProcessDiff
int CodeDiff(node* root, int diff){
    int left = ProcessDiff(root->left, diff, 0, root->height-1);
    if(left != -1){
        return left;
    }
    else{
        int right = ProcessDiff(root->right, diff, 1, root->height-1);
        if (right != -1){
            return right;
        }
    }
    return -1;
}

// Funcion recursiva que devuelve la codificacion de un numero en base al arbol de huffman entregado
int ProcessDiff(node* root, int diff, int binnary, int treeHeight){
    if(root == nullptr){
        return -1;
    }
    if(!root->interior){
        if (root->diff == diff){
            return binnary * pow(2,treeHeight);
        }
        else{
            return -1;
        }
    }
    else{
        int left = ProcessDiff(root->left, diff, 0, treeHeight - 1);
        if(left != -1){
            return (left + binnary * pow(2, treeHeight));
        }
        int right = ProcessDiff(root->right, diff, 1, treeHeight - 1);
        if (right != -1) {
            return (right + binnary * pow(2, treeHeight)); 
        }

        return -1;
    }

}

// Devuelve la decodificacion de un numero en base al arbol de huffman entregado
int DecodeDiff(node* root, int codedDiff, int treeHeight){
    vector<int> representacion_binaria(treeHeight);
    int bin;
    int copia = codedDiff;
    node *aux = root;

    for(int i = treeHeight-1; i >= 0; i--){
        bin = codedDiff % 2;
        codedDiff = codedDiff / 2;
        representacion_binaria.at(i) = bin;
    }

    for(int i = 0; i < representacion_binaria.size(); i++){
        if(!aux->interior){
            return aux->diff;
        }
        if (representacion_binaria.at(i) == 0){
            aux = aux->left;
        }
        else{
            aux = aux->right;
        }
    }
    
    return aux->diff;
}

// Crea el array codificado de char e inicializa la busqueda binaria para este array
void CasoChar(node* root, long* array_explicito, int N, int e, int b, int tamaño, int tamaño_sample, long* gap_coded, long* sample){
    unsigned char* array_codificado = new unsigned char[tamaño-1];
    for(int i = 0; i < tamaño-1; i++){
        array_codificado[i] = CodeDiff(root, gap_coded[i+1]);
    }
   BusquedaBinariaChar(array_explicito, N, tamaño_sample, sample, e, tamaño, b, root, array_codificado, gap_coded);
}

// Crea el array codificado de short e inicializa la busqueda binaria para este array
void CasoShort(node* root, long* array_explicito, int N, int e, int b, int tamaño, int tamaño_sample, long* gap_coded, long* sample){
    unsigned short* array_codificado = new unsigned short[tamaño-1];
    for(int i = 0; i < tamaño-1; i++){
        array_codificado[i] = CodeDiff(root, gap_coded[i+1]);
    }
    BusquedaBinariaShort(array_explicito, N, tamaño_sample, sample, e, tamaño, b, root, array_codificado, gap_coded);
}

// Crea el array codificado de int e inicializa la busqueda binaria para este array
void CasoInt(node* root, long* array_explicito, int N, int e, int b, int tamaño, int tamaño_sample, long* gap_coded, long* sample){
    unsigned int* array_codificado = new unsigned int[tamaño-1];
    for(int i = 0; i < tamaño-1; i++){
        array_codificado[i] = CodeDiff(root, gap_coded[i+1]);
    }
    BusquedaBinariaInt(array_explicito, N, tamaño_sample, sample, e, tamaño, b, root, array_codificado, gap_coded);
}

// Realiza busqueda de un numero al azar para un array de char
void BusquedaBinariaChar(long* array_explicito, int N, int tamaño_sample, long* sample, int e, int tamaño, int b, node* root, unsigned char* array_codificado, long* gap_coded){
    // N veces 
    // Se genera un numero entre el primer y ultimo numero del array
    // Se busca el numero y se guarda el tiempo en un csv
    int random_num_presente;
    bool presente1;

    double entropia = sacar_entropia(gap_coded, tamaño);

    for (int i = 0; i < N; i++) {
        random_num_presente = (rand()%(array_explicito[tamaño-1]-array_explicito[0])) + array_explicito[0];


        // Busqueda y medicion de tiempo de numero al azar entre el primer y ultimo del arreglo
        // Se usa lower_bound que usa busqueda binaria para encontrar al primer elemento mayor o igual que el que se busca
        auto start = chrono::high_resolution_clock::now();
        long *indice1 = lower_bound(sample, sample+tamaño_sample, random_num_presente);
        presente1 = false;
        // Si lower_bound encuentra el numero, se guarda true en un booleano y se termina
        if(*indice1 == random_num_presente){
            presente1 = true;
        }
        // Si no se busca en el arreglo de gap-coding
        else{
            // Se usa distance para obtener el indice anterior al encontrado por lower_bound y se multiplica por b
            // para encontrar indice equivalente en arreglo gap-coding
            int index_start = b * (distance(sample, indice1) - 1);
            // Se guarda el indice menor entre el ultimo del array gap-coding y el guardado anteriormente mas b, 
            // con tal de no pasarse de rango
            int index_end = min(index_start + b, tamaño-1);
            // Se guarda el valor anterior al encontrado por lower_bound
            long valor_actual = *(indice1 - 1);
            index_start++;
            // Se va a buscar el numero en el array codificado hasta que termine el intervalo de busqueda o se encuentre
            // Para buscarlo se toma el valor guardado de en valor_actual, y se le van sumando las diferencias luego de decodificarlas
            while (index_start < index_end && valor_actual <= random_num_presente){
                valor_actual = valor_actual + DecodeDiff(root, array_codificado[index_start-1], root->height);
                if(valor_actual == random_num_presente){
                    presente1 = true;
                    break;
                }
                index_start++;
            } 
        }
        auto end = std::chrono::high_resolution_clock::now();
        chrono::nanoseconds duration = end - start;

        // En el csv se guarda:
        // el epsilon con que se genero el arreglo
        // el tamaño del arreglo usado
        // el tamaño de gap usado
        // la altura del arbol generado
        // si el numero generado al azar estaba presente
        // lo que se tardo la busqueda binaria para el numero al azar
        // la entropia
        // un id que representa la distribucion del arreglo usado
        // un id que representa el metodo de representacion usado
        ofstream file(csv, std::ios::app);
        if (file.is_open()) {
            file << e << "," << tamaño << "," << b << "," << root->height << "," << presente1 << "," << duration.count() << "," << entropia << ",1" << ",3" << endl;
            file.close();
        } 
        else {
            cout << "No se encontro el archivo " << csv << endl;
        }
    }
}

// Realiza busqueda de un numero al azar para un array de short
void BusquedaBinariaShort(long* array_explicito, int N, int tamaño_sample, long* sample, int e, int tamaño, int b, node* root, unsigned short* array_codificado, long* gap_coded){
    // N veces 
    // Se genera un numero entre el primer y ultimo numero del array
    // Se busca el numero y se guarda el tiempo en un csv
    int random_num_presente;
    bool presente1;

    double entropia = sacar_entropia(gap_coded, tamaño);

    for (int i = 0; i < N; i++) {
        random_num_presente = (rand()%(array_explicito[tamaño-1]-array_explicito[0])) + array_explicito[0];


        // Busqueda y medicion de tiempo de numero al azar entre el primer y ultimo del arreglo
        // Se usa lower_bound que usa busqueda binaria para encontrar al primer elemento mayor o igual que el que se busca
        auto start = chrono::high_resolution_clock::now();
        long *indice1 = lower_bound(sample, sample+tamaño_sample, random_num_presente);
        presente1 = false;
        // Si lower_bound encuentra el numero, se guarda true en un booleano y se termina
        if(*indice1 == random_num_presente){
            presente1 = true;
        }
        // Si no se busca en el arreglo de gap-coding
        else{
            // Se usa distance para obtener el indice anterior al encontrado por lower_bound y se multiplica por b
            // para encontrar indice equivalente en arreglo gap-coding
            int index_start = b * (distance(sample, indice1) - 1);
            // Se guarda el indice menor entre el ultimo del array gap-coding y el guardado anteriormente mas b, 
            // con tal de no pasarse de rango
            int index_end = min(index_start + b, tamaño-1);
            // Se guarda el valor anterior al encontrado por lower_bound
            long valor_actual = *(indice1 - 1);
            index_start++;
            // Se va a buscar el numero en el array codificado hasta que termine el intervalo de busqueda o se encuentre
            // Para buscarlo se toma el valor guardado de en valor_actual, y se le van sumando las diferencias luego de decodificarlas
            while (index_start < index_end && valor_actual <= random_num_presente){
                valor_actual = valor_actual + DecodeDiff(root, array_codificado[index_start-1], root->height);
                if(valor_actual == random_num_presente){
                    presente1 = true;
                    break;
                }
                index_start++;
            } 
        }
        auto end = std::chrono::high_resolution_clock::now();
        chrono::nanoseconds duration = end - start;

        // En el csv se guarda:
        // el epsilon con que se genero el arreglo
        // el tamaño del arreglo usado
        // el tamaño de gap usado
        // la altura del arbol generado
        // si el numero generado al azar estaba presente
        // lo que se tardo la busqueda binaria para el numero al azar
        // la entropia
        // un id que representa la distribucion del arreglo usado
        // un id que representa el metodo de representacion usado
        ofstream file(csv, std::ios::app);
        if (file.is_open()) {
            file << e << "," << tamaño << "," << b << "," << root->height << "," << presente1 << "," << duration.count() << "," << entropia << ",1" << ",3" << endl;
            file.close();
        } 
        else {
            cout << "No se encontro el archivo " << csv << endl;
        }
    }
}

// Realiza busqueda de un numero al azar para un array de int
void BusquedaBinariaInt(long* array_explicito, int N, int tamaño_sample, long* sample, int e, int tamaño, int b, node* root, unsigned int* array_codificado, long* gap_coded){
    // N veces 
    // Se genera un numero entre el primer y ultimo numero del array
    // Se busca el numero y se guarda el tiempo en un csv
    long random_num_presente;
    bool presente1;

    double entropia = sacar_entropia(gap_coded, tamaño);

    for (int i = 0; i < N; i++) {
        random_num_presente = (rand()%(array_explicito[tamaño-1]-array_explicito[0])) + array_explicito[0];

        // Busqueda y medicion de tiempo de numero al azar entre el primer y ultimo del arreglo
        // Se usa lower_bound que usa busqueda binaria para encontrar al primer elemento mayor o igual que el que se busca
        auto start = chrono::high_resolution_clock::now();
        long *indice1 = lower_bound(sample, sample+tamaño_sample, random_num_presente);
        presente1 = false;
        // Si lower_bound encuentra el numero, se guarda true en un booleano y se termina
        if(*indice1 == random_num_presente){
            presente1 = true;
        }
        // Si no se busca en el arreglo de gap-coding
        else{
            // Se usa distance para obtener el indice anterior al encontrado por lower_bound y se multiplica por b
            // para encontrar indice equivalente en arreglo gap-coding
            int index_start = b * (distance(sample, indice1) - 1);
            // Se guarda el indice menor entre el ultimo del array gap-coding y el guardado anteriormente mas b, 
            // con tal de no pasarse de rango
            int index_end = min(index_start + b, tamaño-1);
            // Se guarda el valor anterior al encontrado por lower_bound
            long valor_actual = *(indice1 - 1);
            index_start++;
            // Se va a buscar el numero en el array codificado hasta que termine el intervalo de busqueda o se encuentre
            // Para buscarlo se toma el valor guardado de en valor_actual, y se le van sumando las diferencias luego de decodificarlas
            while (index_start < index_end && valor_actual <= random_num_presente){
                valor_actual = valor_actual + DecodeDiff(root, array_codificado[index_start-1], root->height);
                if(valor_actual == random_num_presente){
                    presente1 = true;
                    break;
                }
                index_start++;
            } 
        }
        auto end = std::chrono::high_resolution_clock::now();
        chrono::nanoseconds duration = end - start;


        // En el csv se guarda:
        // el epsilon con que se genero el arreglo
        // el tamaño del arreglo usado
        // el tamaño de gap usado
        // la altura del arbol generado
        // si el numero generado al azar estaba presente
        // lo que se tardo la busqueda binaria para el numero al azar
        // la entropia
        // un id que representa la distribucion del arreglo usado
        // un id que representa el metodo de representacion usado
        ofstream file(csv, std::ios::app);
        if (file.is_open()) {
            file << e << "," << tamaño << "," << b << "," << root->height << "," << presente1 << "," << duration.count() << "," << entropia << ",1" << ",3" << endl;
            file.close();
        } 
        else {
            cout << "No se encontro el archivo " << csv << endl;
        }
    }
}

// Obtiene entropia media del array
double sacar_entropia(long* array, int tamaño){
    double entropia = 0;
    double aux;
    vector<simbolo*> temp;

    simbolo* nuevo = new simbolo();
    nuevo->num = array[0];
    nuevo->freq = 1;
    temp.push_back(nuevo);

    for (int i = 1; i < tamaño; i++){
        for (int j = 0; j < temp.size(); j++){
            if (temp.at(j)->num == array[i]){
                temp.at(j)->freq++;
                break;
            }
        }
        simbolo* nuevo = new simbolo();
        nuevo->num = array[i];
        nuevo->freq = 1;
        temp.push_back(nuevo);
    }

    for (int i = 0; i < temp.size(); i++){
        aux = (temp.at(i)->freq/tamaño) * (log2(tamaño/temp.at(i)->freq));
        entropia = entropia + aux;
    }

    return entropia;
}   