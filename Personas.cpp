
#include "Personas.h"
#include "Personaje.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include "QuitaComentarios.h"
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;

Personas::Personas(const Personas& personas){
	milista.assign(personas.milista.begin(),personas.milista.end());
}

Personas& Personas::operator=(const Personas& copia){
	if(this!=&copia){
		this->clear();
		milista.assign(copia.milista.begin(),copia.milista.end());
	}

	return *this;
}

void Personas::eliminarPersonaje(int pos){
	assert(pos >= 0 && pos < milista.size());

	list<Personaje>::iterator it;
	it = milista.begin();

	for(int i=0;i<pos;++i,++it);

	milista.erase(it);

}

Personaje& Personas::GetPersona(int pos){
	assert(0<=pos && pos < milista.size());
	list<Personaje>::iterator it=milista.begin();
	for(int i=0;i<pos;i++)
		++it;
	return *it;
}

void Personas::clear(){
	milista.clear(); // Borramos todos los personajes
}

ifstream& operator>>(ifstream& archivo, Personas& persona){
	QuitaComentarios(archivo);
	int nump=0;// Entero para el número de personajes
	char numero[200];
	archivo.getline(numero,200); // Obtenemos el número de preguntas
	nump = atoi(numero);
	string aux;
	
	string nombre; // Para el nombre del personaje
	int i=0;
	while(i<nump){
		QuitaComentarios(archivo);
		getline(archivo,nombre); // Lee una linea
			
		string fichero; // Para guardar la linea del fichero
		getline(archivo,fichero); // Lee la linea para el fichero
		// Por si tiene algún comentario a continuación
		for(int j=0;j<fichero.length() && fichero[j]!='#';j++)
			aux.push_back(fichero[j]);
		

		Personaje personaje(nombre,aux); // Creamos el personaje
		persona.milista.push_back(personaje); // Lo guardamos en la lista
		++i;
		aux.clear();
	
	}

	return archivo;
}

ostream& operator<<(ostream& out, Personas& personajes){
	
	Personas::iterator it;
	int i=1;
	for(it=personajes.begin();it!=personajes.end();++it,++i)
		out << i << ".- "<< (*it).GetNombre() << " " << (*it).getCodigo() << endl;

	return out;
}
