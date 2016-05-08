
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "ArbolGeneral.h"
#include "Personas.h"
#include "QuitaComentarios.h"
#include "Preguntas.h"
#include <cstring>

using namespace std;


int main(int argc,char *argv[]){
    
  if ((argc!=2)){
      cout<<"Dime el nombre del fichero de configuracion"<<endl;
  
      return 0;
  }
  ifstream f(argv[1],ios::in);
  QuitaComentarios(f);
  
  Preguntas ask;
  f>>ask;

  Personas People;
  f>>People;

  QuitaComentarios(f);
  string str;
  //Leemos el fichero con el arbol
  
  f>>str;
  
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
  

  cout << endl << endl;



  Personas copia(People);

  Personas::iterator it, oit;


  for(it=People.begin();it!=People.end();++it){

    cout << "Comprobación para saber con quien no cumple la suficiencia el personaje: " << (*it).GetNombre() << endl;
    for(oit=copia.begin();oit!=copia.end();++oit){
      if((*oit).GetNombre().compare((*it).GetNombre()) != 0 && (*oit).getCodigo().compare((*it).getCodigo()) == 0){
        cout << "Las respuestas son las mismas para los personajes " << (*it).GetNombre() << " y " << (*oit).GetNombre() << endl;
      }
    }
  }


  cout << endl << endl << endl;
  cout << "Comprobación para ver si quitando una pregunta el conjunto es minimal o no. " << endl;
 

  for(int i=0;i<ask.NumPreguntas();++i){
    it=People.begin();
    bool minimal=false;
    string aux = (*it).getCodigo();
    
    for(it=People.begin();it!=People.end() && !minimal;++it){
      string codigo_comparar = (*it).getCodigo();
      if(aux[i] != codigo_comparar[i]){

        minimal=true;
      }
    }

    if(!minimal)
      cout << "No es minimal ya que la pregunta " << ask.getPregunta(i) << " no discrimina a los personajes. " << endl;

  }
}
