
#include "Personaje.h"
#include <iostream>
#include <cstring>

Personaje::Personaje(string nom, string fich){
	this->nombre=nom;
	this->fichero=fich;
}

Personaje& Personaje::operator=(const Personaje& personaje){
	if(this!=&personaje){
		this->nombre=personaje.nombre;
		this->fichero=personaje.fichero;
		this->codigo=personaje.codigo;
	}
}

void Personaje::SetCodigoRespuestas(string cod){
	
	this->codigo=cod;
}

string Personaje::GetNombre(){
	return this->nombre;
}

string Personaje::getFichero(){
	return this->fichero;
}

string Personaje::getCodigo(){
	return this->codigo;
}
