

#include "Jugador.h"
#include "Personaje.h"
#include "Preguntas.h"
#include <stdlib.h>    // incluye "rand" y "srand"
#include "Personas.h"
#include <cstring>
#include <cctype>
#include <cassert>
#include <math.h>

Jugador::Jugador(string nombre, const Personaje& personaje){
	this->nombre=nombre;
	this->personaje=personaje;
	

}

string Jugador::getNombrePersonaje(){
	return personaje.GetNombre();
}

string Jugador::getNombre(){
	return nombre;
}
