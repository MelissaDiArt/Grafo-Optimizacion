#include "grafo.hpp"
using namespace std;

void dirigido (void)
{
  cout << endl;
  cout << "*********************************************************" << endl;
  cout << "Actividad I, Optimizacion: carga basica de un grafo" << endl;
  cout << "c. [C]argar grafo desde fichero" << endl;
  cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
  cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
  cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
  cout << "d. Caminos minimos: [D]ijkstra" << endl;
  cout << "b. Caminos minimos: [B]ellman-ford-moore" << endl;
  cout << "q. Finalizar el programa" << endl;
  cout << "*********************************************************" << endl;
}


void nodirigido (void)
{
  cout<<endl;
  cout << "*********************************************************" << endl;
  cout << "Actividad I, Optimizacion: carga basica de un grafo" << endl;
  cout << "c. [C]argar grafo desde fichero" << endl;
  cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
  cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
  cout << "o. Mostrar las c[o]mponentes conexas del grafo" << endl;
  cout << "q. Finalizar el programa" << endl;
  cout << "*********************************************************" << endl;
}


int main (void) {
  
  char fichero[100];
  int error;
  char opcion='u';
  
  cout<<"Introduce el nombre del fichero; ";
  cin >> fichero;
  cin.get();
  GRAFO grafo(fichero, error);
  
  if(error==1){
    
    cout<<" ---- Error en la apertura del fichero ---- "<<endl;
  }else{
    while(opcion!='q')
    {
      if (grafo.Es_dirigido()==1){
	
	dirigido();
	cout << " Intoduzca una opcion; ";
	cin.get(opcion);		  	
	cin.get();
	
	switch (opcion){
	  
	   case 'c':
	    cout << "Introduce el nombre del fichero; ";
	    cin >> fichero;
	    cin.get();
	    grafo.actualizar(fichero, error);
	    if(error==0){
	      
	      cout << "******Fichero cargado correctamente******" << endl;
	      break;
	    } else {
	      cout << "---- Error en la apertura del fichero ----" << endl;
	      opcion='q';
	    }
	  case 'q':
	    cout << "---- Fin del programa ----" << endl;
	    break;
	  case 'i':
	    cout << "**** Grafo cargado correctamente ****" << endl;
	    grafo.Info_Grafo();
	    break;
	  case 's':
	    cout << endl;
	    grafo.Mostrar_Listas(0);
	    break; 
	  case 'p':
	    cout << endl;
	    grafo.Mostrar_Listas(1);
	    break;
	    
	  case 'd':
	  	grafo.Dijkstra();
	    break;
	    
	  case 'b': 
	  	grafo.Bellmanandmoore();
	  	break;
	  	
	  default: 
	    cout << "---- No existe esa opción ----" << endl;
	    break;
	  
	}
	
      } else {
	
	nodirigido();
        cout << "Introduce una opcion; ";
        cin.get(opcion);
        cin.get();
	
	switch(opcion){
	  
	  case 'c':
	    cout<<"Introduce el nombre del fichero; ";
	    cin >> fichero;
	    cin.get();
	    grafo.actualizar(fichero, error);
	    if(error==0){
	      cout << "****** Fichero cargado correctamente ******" << endl;
	      break;
	    } else {
	      cout << "---- Error en la apertura del fichero ----" << endl;
	      opcion='q';
	      
	    }
	  case 'q':
	    cout << "---- Fin del programa ----" << endl;
	    break;
	  case 'i':
	    cout << "**** Grafo cargado correctamente **** " << endl;
	    grafo.Info_Grafo();
	    break;
	  case 'a':
	    cout << endl;
	    grafo.Mostrar_Listas(0);
	    break;
	  case 'o' :
	    grafo.ComponentesConexas();
	    break;
	  default: 
	    cout << "---- No existe esa opción ----" << endl;
	    break; 
	}
      }
      
      if ((grafo.Es_dirigido()!=0)&&(grafo.Es_dirigido()!=1)){
	   
	cout << " ---- No se reconoce el tipo de grafo ---- " << endl;
	opcion = 'q';
      }
    }
  }
}
