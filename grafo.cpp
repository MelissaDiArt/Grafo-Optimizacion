
#include "grafo.hpp"


/******************************************************/

GRAFO::~GRAFO(){    // Destructor
  
  LS.clear();
  LP.clear();
}

/******************************************************/

void GRAFO:: actualizar (char nombrefichero[100], int &errorapertura){    // Actualizar ( Llamada al destructor y al constructor)
   
  LS.clear();
  LP.clear();
  
  ElementoLista  dummy;  // Crear un struct con el nombre dummy
  ifstream textfile;
  textfile.open(nombrefichero); // Abrir fichero
  if (textfile.is_open()) { // Se hará si el fichero esta abierto correctamente
   
    unsigned i, j, k;
    int cost;
    textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;       // Leer el numero de nodos,arcos y el atributo
    // los nodos internamente se numeran desde 0 a n-1
    LS.resize(n);            // creamos las n listas de sucesores 
    for (k=0;k<m;k++){               // leemos los m arcos y creamos las listas de sucesores LS
       textfile>> (unsigned &) i >> (unsigned &) j >> (int &) cost;  // Almacenar sucesores 
       dummy.c=cost;
       dummy.j=j-1;  // Almacenar los sucesores
       LS[i-1].push_back(dummy);  // Crea un nuevo espacio con el struct   
       if(dirigido==0){  // Almacenar la adyacencia 
	 dummy.j=i-1;   // Almacenar predecesores
	 LS[j-1].push_back(dummy);  // Crea un nuevo espacio con el struct 
      }
      
    }
    textfile.close();
    if (dirigido == 1){    // Crear lista de predecedores
		  
      ListaPredecesores();
    };
    errorapertura = 0;
    
  } else {
    errorapertura = 1;
    
  }
}

/******************************************************/

void GRAFO::Info_Grafo(){     // Mostrar informacion del grafo
  
  if(Es_dirigido()==1){
    cout << "Grafo dirigido | nodos " << n << " | arcos " << m << endl;
  } else {
    cout << "Grafo no dirigido | nodos "  << n << " | aristas " << m << endl;
  }
  
}

/******************************************************/

unsigned GRAFO::Es_dirigido(){          // Comprobar si es dirigido o no
  
	return dirigido;
}

/******************************************************/

void Mostrar_Lista(vector<LA_nodo> L)   // Mostrar lista
{
  for(int i=0; i<L.size(); i++){
    cout<<"["<<i+1<<"] :";
    for(int k=0; k<L[i].size(); k++){
      if(k>0){
	cout<<"|";
      }
      cout<<" "<<L[i][k].j+1<<" ";
    }
    if(L[i].size()==0){
      cout<<" null";
    }
    cout<<endl;
  }
  
};


/******************************************************/

void GRAFO :: Mostrar_Listas (int l){   // Acceder a la funcion mostrar lista 
  
  if(l==0){
    Mostrar_Lista(LS);   // Llamada a la lista sucesores
    
  } else {
    Mostrar_Lista(LP);  // Llamada a la lista predecesores
  }
  
};


/******************************************************/

void GRAFO::ListaPredecesores() {      // Crear la lista de predecesores

  ElementoLista dummy;
  LP.resize(n);    // Redimencionar con el numero de nodos
  for(int i=0; i<n; i++){		
    for(int k=0; k<LS[i].size(); k++){
      dummy.j=i;
      LP[LS[i][k].j].push_back(dummy);   // Crea la lista de predecesores a partir de los sucesores
    }
  }
}


/******************************************************/

GRAFO::GRAFO(char nombrefichero[100], int &errorapertura){     // Lee el fichero y guarda los datos
  
	ElementoLista  dummy;  // Crear un struct con el nombre dummy
	ifstream textfile;
	textfile.open(nombrefichero); // 
	if (textfile.is_open()) { // Se hará si el fichero esta abierto correctamente
   
		unsigned i, j, k;
		int cost;
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;       // Leer el numero de nodos,arcos y el atributo
		// los nodos internamente se numeran desde 0 a n-1
		LS.resize(n);            // creamos las n listas de sucesores 
		for (k=0;k<m;k++){               // leemos los m arcos y creamos las listas de sucesores LS
       
			textfile>> (unsigned &) i >> (unsigned &) j >> (int &) cost;  // leer sucesores 
			dummy.c=cost;
			dummy.j=j-1;  // Almacenar los sucesores
			LS[i-1].push_back(dummy);  // Crea un nuevo espacio con el struct   
			if(dirigido==0){  // Almacenar la adyacencia 
			
				dummy.j=i-1;   // Almacenar predecesores
				LS[j-1].push_back(dummy);  // Crea un nuevo espacio con el struct 
			}

		}
		textfile.close(); // Cerrar fichero
		if (dirigido == 1){
		  
           	    ListaPredecesores();
	      };
	      
	      errorapertura = 0;
    } else {
      errorapertura = 1;
     
    }
    
}
    
/**********************************************************/

  void GRAFO::dfs(unsigned i, vector<bool> &visitado) {  // Recorre todos los nodos de la lista de adyacencia
    
      visitado[i] = 1;
      cout << i+1 << ", ";
      for ( int j=0; j<LS[i].size(); j++ ) { 
	      if (visitado[LS[i][j].j] == 0) {
	       dfs(LS[i][j].j, visitado);
	      }
      }
  }
    

/**********************************************************/

    void GRAFO::ComponentesConexas(void) {         // Comprobar si el grafo es conexo o no
      
      vector<bool> visitado;  // Marca los nodos visitados
      visitado.resize(n);   // Redimensiona el vector dependiendo de el numero de nodos
      int contador = 0;
      
      for ( int i=0; i<n; i++ ) {
        
        if ( visitado[i] == 0) {  // Comprobar si el nodo esta visitado o no
          
          contador++;
          cout << "Componente conexa "<< contador << ": { ";
          dfs( i,visitado );
          cout << " }" << endl;
        }
      }
          
      if (contador == 1) {    // Existe un unico camino que une todos los nodos
        cout << " El grafo es conexo " << endl;
        
      } else {
        
        cout << " El grafo no es conexo " << endl;
      }
    }
    

/***************************************************************************************************/
      
  void MostrarCamino (unsigned s, unsigned i, vector<unsigned> pred) {  // Funcion que muestra del final al comienzo
	  if(i!=s) {
		  MostrarCamino(s,pred[i],pred); //llama recursivamente con el predecesor del nodo i
		  cout<<pred[i]+1<<" -> "; //al terminar las llamadas recursivas muestra los nodos en orden de predecesores invertido
		  }
  }


/***************************************************************************************************/
      
    void GRAFO::Dijkstra(void) {

      vector<bool> PermanentementeEtiquetado;
      vector<int> d;
      vector<unsigned> pred;
      int min=0;
      unsigned s, candidato;
	
	
      PermanentementeEtiquetado.resize(n,false); // Redimenciona y pone todo a false
      d.resize(n,maxint);   // Redimenciona y pone inf en los costes
      pred.resize(n,UERROR); // poner el predecesor que no existe(NULL)
	
      cout<<endl;
      cout<<"Caminos mínimos: Dijkstra"<<endl; // Pide un nodo
      cout<<"¿Nodo de partida? [1-"<<n<<"]: ";
      cin>>(unsigned &) s;  // s nodo de partida
      cin.get();
      s--;  
      if(s<n){
      	  
	    	d[s]=0;   // Coste de primer nodo
	    	pred[s]=s; // Pred de s es s
	    	
	    	do {
	    	  
		    	min=maxint;  // Resetea el min a inf
	        candidato=-1; 
	    		for(int i=0; i<n; i++) {
				      if(PermanentementeEtiquetado[i]==false) {       // Si el nodo no esta etiquetado
		
					        if(d[i]<min) { // Si coste del nodo < min, dicho nodo es candidato por lo tanto machaca el min (Coger el nodo de menor coste)
					
					        	candidato=i;
					        	min=d[i];
					        }
				      }
	    		}
			
	    		
			     if(candidato!=-1) {  // Si tenemos un candidato
			
			    	  PermanentementeEtiquetado[candidato]=true; //Lo marcamos de modo permanente
				      for(int i=0; i<LS[candidato].size(); i++) {//Recorremos los nodos mirando sus sucesores
			
					        if((d[candidato]+LS[candidato][i].c<d[LS[candidato][i].j])&&(PermanentementeEtiquetado[LS[candidato][i].j]==false)) { // Si mejora y no esta etiquetado
					         //Si existe un atajo en los sucesores al candidato y no esta etiquetados, se actualiza el coste y el pred
						        d[LS[candidato][i].j]=d[candidato]+LS[candidato][i].c; //Nuevo coste
					      	  pred[LS[candidato][i].j]=candidato; //Nuevo pred
					        }
				      }
			     }
			     
	    	} while (min < maxint); //Mientras min < maxint
		
		    cout<<"Soluciones: "<<endl; //Muestra las soluciones
		    for(unsigned i=0; i<n; i++)	{
			      if(i!=s) { //Si el nodo es diferente al nodo de partida elegido
		
				      if(PermanentementeEtiquetado[i]==true) { //Y si esta marcado hay camino de s a i
				
					      cout<<"El camino desde "<<s+1<<" al nodo "<<i+1<<" es : "; //Muestra el camino de s a i
					      MostrarCamino(s,i,pred); //Llama a la funcion de muestra
					      cout<<i+1<<" de longitud "<<d[i]; 
				      } else {
					      cout<<"No hay camino desde "<<s+1<<" al nodo "<<i+1;
				      }
				  cout<<endl;
			      }
		    }
      } else {
        
		      cout<<"El número introducido no está en el rango [1-"<<n<<"] introduzca un número del rango permitido."<<endl;
      }
    }
    
/***************************************************************************************************/

    void GRAFO::Bellmanandmoore(void) {
	    vector<int> d;
    	vector<unsigned> pred;
	    unsigned s, numeromejoras=0;
    	bool mejora;
	
	    d.resize(n,maxint);
	    pred.resize(n,UERROR);
	
    	cout<<endl;
    	cout<<"Caminos mínimos: Bellman - End - Moore" <<endl;
    	cout<<"¿Nodo de partida? [1-"<<n<<"] : ";
    	cin>> (unsigned &) s;
    	cin.get();
    	s--;
    	if(s<n) {
	    	d[s]=0;
	    	pred[s]=s;
	    	
		    do {
		      
		    	mejora=false;
		    	for(int i=0;i<n; i++) //Recorre nodos
			    	for(int j=0; j<LS[i].size(); j++) // Recorre arcos sucesores del nodo i
					    if(d[LS[i][j].j]>d[i]+LS[i][j].c)	{ // Si existe un atajo(no menor)
				
						    if(!(LS[i][j].c<0&&d[i]==maxint)) { //Y si el coste no es negativo y el coste no es igual a maxint (coste negativo y el coste del nodo al que va es inf)
						
						    	d[LS[i][j].j]=d[i]+LS[i][j].c;//Nuevo coste
						    	pred[LS[i][j].j]=i;//Nuevo predecesor
						    	mejora=true;//Marcamos como mejora
						    }
					    }
					    
			  if(mejora==true) // Si ha habido mejora
				  numeromejoras++; // +1 al contador de mejoras
		  } while((numeromejoras<n)&&(mejora==true)); //Mientas el numero de mejoras sea menor al numero de nodos y haya mejora (ciclo de coste negativo)
		
		if(mejora==false)	{ //Si salimos del bucle con mejora==false, hay solucion, en otro caso no
	
			cout<<"Soluciones: "<<endl;//Muestra de soluciones
			for(unsigned i=0; i<n; i++)	{//Rrecorrido de nodos
		
				if(i!=s) { //Si el nodo i es distinto al nodo seleccionado s
				
					if(pred[i]!=UERROR) {//Y si no hay error
					
						cout<<"El camino desde "<<s+1<<" al nodo "<<i+1<<" es : "; //Muestra el camino del nodo s al nodo i
						MostrarCamino(s,i,pred);
						cout<<i+1<<" de longitud "<<d[i];
					} else {
						  cout<<"No hay camino desde "<<s+1<<" al nodo "<<i+1;
					}
					cout<<endl;
				}
			}
		} else
			cout<<"No hay solucion posible al detectarse un ciclo de coste negativo en el grafo."<<endl;	
    	} else
		cout<<"El número introducido no está en el rango [1-"<<n<<"], introduzca un número del rango permitido."<<endl;
  }
  



