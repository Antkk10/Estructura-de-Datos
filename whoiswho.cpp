
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "ArbolGeneral.h"
#include "Personas.h"
#include "QuitaComentarios.h"
#include "Preguntas.h"
#include <stdlib.h>    // incluye "rand" y "srand"
#include "Jugador.h"
#include <cctype>
#include "Maquina.h"

using namespace std;


int main(int argc,char *argv[]){
    
  if ((argc!=3)){
      cout<<"Dime el nombre del fichero de configuracion y h para máquina vs humano o m para máquina lista vs máquina totan "<<endl;
  
      return 0;
  }
  ifstream f(argv[1],ios::in);
  QuitaComentarios(f);
  
  Preguntas ask;
  f>>ask;

  Personas People;
  f>>People;
  cout << People << endl;
  QuitaComentarios(f);
  string str;
  //Leemos el fichero con el arbol
  
  f>>str;
  cout << str << endl;
  
  //Abrimos el fichero con el arbol
  ifstream farbol(str.c_str());
  if (!farbol){
      cout<<"No puedo abrir el fichero "<<str<<endl;
  }
  ArbolGeneral<int> ab;
  farbol>>ab;
  cout<<"Leido el arbol con las descripciones de los personajes"<<endl;
 
  //recorremos en postorden el arbol
  ArbolGeneral<int>::iter_preorden it_tree=ab.begin();
  while (it_tree!=ab.end()){
    if (it_tree.Hoja() && (*it_tree)!=-1){
      ArbolGeneral<int>::Nodo nod = it_tree.GetNodo();
      cout<<"***************\nPersonaje: "<<People.GetPersona(*it_tree).GetNombre()<<endl;
      cout<<"Preguntas y contestaciones son:"<<endl;
      Preguntas::iterator itask=ask.end(); --itask;
      
      Preguntas::iterator itask_prev=ask.end();
      string codigo(ask.NumPreguntas(),'0');
      int pos = ask.NumPreguntas()-1;
      do{
	     cout<<(*itask);
	     if (nod==ab.hijomasizquierda(ab.padre(nod))){
	       cout<<"Si"<<endl;
	       codigo[pos]='1';
	     }  
	     else{ 
	       cout<<"No"<<endl;
	       codigo[pos]='0';
	  
	     } 
	     itask_prev=itask;
       --itask;	
        pos--;
	       nod=ab.padre(nod);
      }while (itask_prev!=ask.begin());
      cout<<"Codigo asociado "<<codigo<<endl;
      //Le ponemos al personaje el codigo
      People.GetPersona(*it_tree).SetCodigoRespuestas(codigo);
      
      
    }
    
    ++it_tree;
  }

  ask.setPregunta("Digo ya el personaje. ");
  string nombre1;
  char opcion = *argv[2];

  if(toupper(opcion) == 'H'){
  	cout << "Partida entre humano y máquina. " << endl;
	  cout << "Nombre jugador 1: ";
	  cin >> nombre1;
	  cin.ignore();
	  
	  

	  // Se obtiene dos personajes al azar
	  srand(time(0));
	  // Obtiene un número al azar entre 0 y n-1 personajes
	  int numero = rand()%People.getCantidad();

	  
	  // Se crea el primer jugador
	  Jugador j1(nombre1,People.GetPersona(numero));
	  // Aleatorio para personaje 2
	  numero = rand()%People.getCantidad();
	  // Crea el jugador 2
	  Maquina j2(1,People.GetPersona(numero),People,ask);

	  bool fin = false;
	  int toca=0;
	  char respuesta; // Para las respuestas
	  cout << endl << endl << endl << endl;
	  while(!fin){
	  	bool correcto=false; // Para salir cuando la opción sea correcta
	  	int opcion; // Para elegir el número de la pregunta
	  	char aux_opcion[50];// auxiliar para transformar a entero
	  	if(toca%2==0){
	  		while(!correcto){
		  		cout << "Turno de jugador " << j1.getNombre() << endl;
		  		cout << "Tu personaje es " << j1.getNombrePersonaje() << endl;
		  		cout << "Elige una de las siguientes preguntas: " << endl;
		  		cout << ask;
		  		cout << "Opción: ";
		  		cin >> aux_opcion;
		  		if(isdigit(aux_opcion[0])){
		  			opcion = atoi(aux_opcion);

			  		if(opcion > 0 && opcion < 19){
			  			if(opcion == 18){
			  				while(!correcto){
				  				cout << "Elige un personaje: " << endl;
				  				cout << People << endl;
				  				cout << "*********************************************************************" << endl;
				  				cout << "Opción: " << endl;
			  					cin >> aux_opcion;
			  					if(isdigit(aux_opcion[0])){
			  						opcion = atoi(aux_opcion);

				  					if(opcion > 0 && opcion <= People.getCantidad()){
				  						correcto=true;
				  						if(j2.comprobarPersonaje(People.GetPersona(opcion-1).GetNombre())){
				  							cout << "Has ganado el juego " << j1.getNombre() << endl;
				  							fin=true;
				  						}
				  						else
				  							cout << "Ese no es el jugador. " << endl;
				  					}
				  					else
				  						cout << "Introduce una opción válida. " << endl;
				  				}
				  				else
				  					cout << "Introduce una opción válida. " << endl;
			  				}
			  			}
			  			else{
			  				correcto=true;
			  				cout << "Jugador 1: "<< ask.getPregunta(opcion-1);
			  				cout << "Respuesta jugador 2: ";
			  				if(j2.getRespuesta(opcion-1))  				
			  					cout << "Si." << endl;
			  				else
			  					cout << "No." << endl;

			  			}
			  		}
			  		else
			  			cout << "Introduce una opción válida. " << endl;
			  	}
			  	else
			  			cout << "Introduce una opción válida. " << endl;
		  	}

	  	}
	  	else{
		  		cout << "Turno de jugador " << j2.getNombre() << endl;
		  		cout << "Tu personaje es " << j2.getNombrePersonaje() << endl;
		  		cout << "Elige una de las siguientes preguntas: " << endl;
		  		cout << ask;
		  		cout << "Opción: ";
		  		opcion = j2.realizarPregunta();
		  		cout << ask.getPregunta(opcion-1);
		  		cout << endl;
		  		if(opcion == 18){
			  						  				
			  			if(j2.respuestaFinal().compare(j1.getNombrePersonaje())==0){
			  				cout << "Si. Has ganado el juego " << j2.getNombre() << endl;
			  				fin=true;
			  			}
			  			else
			  				cout << "Ese no es el jugador. " << endl;
			  			
			  			
		  				
		  		}
		  		else{
		  		
		  			cout << "Respuesta jugador 1: " << endl;
		  			string aux;
		  			cin >> aux;
		  			respuesta = aux[0];
		  			cin.ignore(256,'\n');
		  			j2.obtenerRespuesta(respuesta,ask.getPregunta(opcion-1)) ;			

		  		}
		}
		  
		  
		  cout << endl << "****************************************************************" << endl;
		  toca++;
	  }
	}
	else{
		cout << "Partida entre máquina lista vs máquina tonta. " << endl;

	  // Se obtiene dos personajes al azar
	  srand(time(0));
	  // Obtiene un número al azar entre 0 y n-1 personajes
	  int numero = rand()%People.getCantidad();

	  Maquina j1(1,People.GetPersona(numero),People,ask);

	  numero = rand()%People.getCantidad();

	  Maquina j2(0,People.GetPersona(numero),People,ask);

	  bool fin = false;
	  int toca=0;
	  char respuesta; // Para las respuestas
	  cout << "*************************************************************************" << endl;
	  cout << "*************************************************************************" << endl;
	  cout << "*************************************************************************" << endl;
	  cout << "*************************************************************************" << endl;
	  while(!fin){
		int opcion; // Para elegir el número de la pregunta
	  	if(toca%2==0){
	  			cout << "Turno de jugador " << j1.getNombre() << endl;
		  		cout << "Tu personaje es " << j1.getNombrePersonaje() << endl;
		  		cout << "Elige una de las siguientes preguntas: " << endl;
		  		cout << ask;
		  		cout << "Opción: ";
		  		opcion = j1.realizarPregunta();
		  		cout << ask.getPregunta(opcion-1);
		  		cout << endl;
		  		if(opcion == 18){
			  						  				
			  			if(j1.respuestaFinal().compare(j2.getNombrePersonaje())==0){
			  				cout << "Si. Has ganado el juego " << j1.getNombre() << endl;
			  				fin=true;
			  			}
			  			else
			  				cout << "Ese no es el jugador. " << endl;
			  			
			  			
		  				
		  		}
		  		else{
		  		
		  			cout << "Respuesta jugador 2: " << endl;
		  			if(j2.getRespuesta(opcion-1)){			
		  					cout << "Si." << endl;
		  					respuesta='S';
		  			}
		  			else{
		  					cout << "No." << endl;
		  					respuesta='N';
		  			}
		  			j1.obtenerRespuesta(respuesta,ask.getPregunta(opcion-1)) ;			

		  		}
		}
		else{
			  	cout << "Turno de jugador " << j2.getNombre() << endl;
		  		cout << "Tu personaje es " << j2.getNombrePersonaje() << endl;
		  		cout << "Elige una de las siguientes preguntas: " << endl;
		  		cout << ask;
		  		cout << "Opción: ";
		  		opcion = j2.realizarPregunta();
		  		cout << ask.getPregunta(opcion-1);
		  		cout << endl;
		  		if(opcion == 18){
			  						  				
			  			if(j2.respuestaFinal().compare(j1.getNombrePersonaje())==0){
			  				cout << "Si. Has ganado el juego " << j2.getNombre() << endl;
			  				fin=true;
			  			}
			  			else
			  				cout << "Ese no es el jugador. " << endl;
			  			
			  			
		  				
		  		}
		  		else{
		  		
		  			cout << "Respuesta jugador 1: " << endl;
		  			if(j1.getRespuesta(opcion-1)){			
		  					cout << "Si." << endl;
		  					respuesta='S';
		  			}
		  			else{
		  					cout << "No." << endl;
		  					respuesta='N';
		  			}
		  			j2.obtenerRespuesta(respuesta,ask.getPregunta(opcion-1)) ;			

		  		}
		}
		  
		  
		  cout << endl << "****************************************************************" << endl;
		  toca++;
	  }
	
	}
  
  
}
    
    
