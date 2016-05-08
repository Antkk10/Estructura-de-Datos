
#include "Preguntas.h"
#include <cstring>
#include <cassert>
#include <list>
#include <iostream>
#include "QuitaComentarios.h"
#include <cstdlib>


using namespace std;

Preguntas::Preguntas(const Preguntas& v){
	preguntas.assign(v.preguntas.begin(),v.preguntas.end()); // Copiamos todo el vector
}

Preguntas& Preguntas::operator=(const Preguntas& copia){
	if(this!=&copia){
		borrar();
		preguntas.assign(copia.preguntas.begin(),copia.preguntas.end());
	}

	return *this;
}


string Preguntas::getPregunta(int pos) const{
	//assert(pos>=0 && pos < preguntas.size());
	list<string>::const_iterator it=preguntas.begin();
	for(int i=0;i<pos;++i,++it);
	
	return *it;
}

void Preguntas::setPregunta(string preg){
	preguntas.push_back(preg);
}

ifstream& operator>>(ifstream& archivo, Preguntas& original){

	int nump=0;// Entero para el número de preguntas
	char numero[200];
	archivo.getline(numero,200); // Obtenemos el número de preguntas
	if(isdigit(numero[0]))
		nump = atoi(numero);
	QuitaComentarios(archivo);
	string preg; // Auxiliar para obtener las preguntas del archivo
	int i=0;
	while(i<nump){
		getline(archivo,preg); // Obtenemos una linea del fichero.
		
			original.preguntas.push_back(preg); // Guardamos la pregunta en el vector.
			++i;
	}

	return archivo;
}


ostream& operator<<(ostream& out, const Preguntas& original){

	list<string>::const_iterator it=original.preguntas.begin();
	int i=1;
	for(it;it!=original.preguntas.end();++it,++i)
		cout << i << ".- "<< *it << endl;
		

	return out;
}

typename Preguntas::iterator& Preguntas::iterator::operator++(){
	++it;
	return *this;
}

string& Preguntas::iterator::operator*(){
	return *it;
}

typename Preguntas::iterator& Preguntas::iterator::operator--(){
	--it;
	return *this;
}
bool Preguntas::iterator::operator==(const typename Preguntas::iterator& otro)const{
	return it == otro.it;
}

bool Preguntas::iterator::operator!=(const typename Preguntas::iterator& otro)const{
	return it != otro.it;
	
}

typename Preguntas::iterator Preguntas::begin(){
	iterator i;
	i.it=preguntas.begin();
	return i;
}

typename Preguntas::iterator Preguntas::end(){
	iterator i;
	i.it=preguntas.end();
	return i;
}
