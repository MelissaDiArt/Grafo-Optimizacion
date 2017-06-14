
#ifndef _GRAPH_H
#define _GRAPH_H


#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

const unsigned UERROR = 65000;
const int maxint = 1000000;

// definicion de un elemento de la lista de adyacencia

typedef struct
{
	unsigned j; // nodo
	int      c; // atributo para expresar el peso, la longitud, el coste, la inversion, etc...

} ElementoLista;

// definicion del tipo de una lista de adyacencia de un nodo

typedef vector<ElementoLista> LA_nodo;


class GRAFO
 {
	unsigned            n;         // numero de nodos //
	unsigned            m;         // numero de arcos //
	unsigned   	    dirigido;  //0 si el grafo es no dirigido y 1 si es dirigido
	vector<LA_nodo>     LS;        // Lista de sucesores: es una matriz donde cada fila posiblemente es de distinto tamaño
	vector<LA_nodo>     LP;        // Lista de predecesores: es una matriz donde cada fila posiblemente es de distinto tamaño
 public:
     GRAFO(char nombrefichero[], int &errorapertura);  // Constructor
     void actualizar (char nombrefichero[], int &errorapertura);   // Actualizar valores, borrar y cargar denuevo
     unsigned Es_dirigido();  //devuelve 0 si el grafo es no dirigido y 1 si es dirigido
     void Info_Grafo();  // Mostrar informacion básica del grafo
     void Mostrar_Listas(int l); // Mostrar lista
     void ListaPredecesores();  // Crear lista de predecesores (si es dirigido)
     ~GRAFO();   // Destructor
     void dfs(unsigned i, vector<bool> &visitado); // Visitar todos los nodos de un grafo no dirigido
     void ComponentesConexas(); // Comprobar si las componentes son conexas
     void Dijkstra();  // Funcion que calcula los caminos minimos
     void Bellmanandmoore();  // Funcion que calcula los caminos minimos
    
};


#endif
