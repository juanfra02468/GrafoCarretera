//============================================================================
// Name        : GrafosCarretera.cpp
// Author      : Juanfra
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

#include "Grafo.h"
#include "Cola.h"


#define FICHERO_ENT "datos.in"
#define FICHERO_SAL "datos2.out"

using namespace std;

//Metood para cargar los datos en el grafo
//y guardar los caminos a resolver.
bool cargarDatos(Grafo* grafo, Cola* cola){
	bool cargado;
	int numNodos, numAristas, numCaminos;
    string linea, ciudadInicio, ciudadFin;
    ifstream entradaDatos;
	

	entradaDatos.open(FICHERO_ENT, ios::in);
	
    if(entradaDatos.is_open()){
        
        //Leer numero de nodos.
        getline(entradaDatos, linea, '\n');
        numNodos = stoi(linea);

        //Leer nombre de nodos e insertarlos.
        for(int i = 0; i < numNodos; i++){

			getline(entradaDatos, linea, '\n');
			
			//Eliminamos el retorno de carro.
			//Evitando problemas entre Linux y Windows.
			if(linea[linea.size() - 1] == '\r'){
				linea.erase(linea.size() - 1);
			}

            grafo -> insertarVertice(linea);
        }

        //Leer salto de linea entre los nodos y los arcos.
        getline(entradaDatos, linea, '\n');
        
        //Leer numero de aristas.
        getline(entradaDatos, linea, '\n');
        numAristas = stoi(linea);

        //Leer las aristas e insertarlas en el grafo.
        for(int i = 0; i < numAristas; i++){
            getline(entradaDatos, ciudadInicio, ' ');
            getline(entradaDatos, ciudadFin, ' ');
            getline(entradaDatos, linea, '\n');
			
			
            if(!grafo -> insertarArco(ciudadInicio, ciudadFin, stof(linea))){
				cout << "No inserta: " << ciudadInicio << " -- " <<ciudadFin << "." << endl;
			} 
        }

		//Leer salto de linea entre los arcos y los caminos.
        getline(entradaDatos, linea, '\n');
        
        //Leer numero de caminos a resolver.
        getline(entradaDatos, linea, '\n');
        numCaminos = stoi(linea);

		//Guardamos los datos de los caminos a resolver.
        for(int i = 0; i < numCaminos; i++){
			//Coger primera palabra de la linea.
        	getline(entradaDatos, ciudadInicio, ' ');
        	
			//Coger segunda palabra de la linea 
			getline(entradaDatos, ciudadFin, '\n');
			
			//Eliminamos el retorno de carro.
			//Evitando problemas entre Linux y Windows.
			if(ciudadFin[ciudadFin.size() - 1] == '\r'){
				ciudadFin.erase(ciudadFin.size() - 1);
			}

			//Insertamos los datos del fichero en una cola
			//para su procesamineto posterior.
			cola -> insertarNodo(ciudadInicio);
			cola -> insertarNodo(ciudadFin);
        }
		
        entradaDatos.close();
		cargado = true;	

    } else{
        cout << "Error: Fichero no encontrado.";
		cargado = false;
    }

	return cargado;
}


void ejecutar(Grafo* grafo, Grafo* mst, Cola* cola){
	string ciudadInicio, ciudadFin;
	ofstream salidaDatos;
	Cola* aux = new Cola();

	salidaDatos.open(FICHERO_SAL);

	grafo -> floyd();
	while(!cola -> estaVacia()){
		ciudadInicio = cola -> primero();
		aux -> insertarNodo(ciudadInicio);
		cola -> desencolar();

		ciudadFin = cola -> primero();
		aux -> insertarNodo(ciudadFin);
		cola -> desencolar();

		salidaDatos << grafo -> caminoFloyd(ciudadInicio, ciudadFin) << " ";
		salidaDatos << grafo -> getDistancia(ciudadInicio, ciudadFin) << endl;
	}

	salidaDatos << endl;
	mst = grafo -> prim();
	mst -> floyd();
	salidaDatos << mst -> sumaMatriz() << endl;

	while(!aux -> estaVacia()){
		ciudadInicio = aux -> primero();
		aux -> desencolar();

		ciudadFin = aux -> primero();
		aux -> desencolar();

		salidaDatos << mst -> caminoFloyd(ciudadInicio, ciudadFin) << " ";
		salidaDatos << mst -> getDistancia(ciudadInicio, ciudadFin) << endl;
	}

	salidaDatos.close();
}

int main(){

	//ejecutar();
	//Grafo* g = new Grafo();
	//g -> prueba();
	//g -> verVertices();
	//delete g;

	/*Cola* cola = new Cola();

	cola -> insertarNodo("Badajoz");
	cola -> insertarNodo("Caceres");
	cola -> insertarNodo("Sevilla");

	cola -> mostrar();

	cola -> desencolar();
	cola -> desencolar(); 
	cola -> desencolar();

	cola -> mostrar(); */
////////////////////////////////////

	Grafo* grafo = new Grafo();
	Grafo* mst;
	Cola* cola = new Cola();

	if(cargarDatos(grafo, cola)){
		ejecutar(grafo, mst, cola);
	}

	return 0;
}
