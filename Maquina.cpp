
#include "Personaje.h"
#include "Preguntas.h"
#include <stdlib.h>    // incluye "rand" y "srand"
#include "Personas.h"
#include <cstring>
#include <cctype>
#include <cassert>
#include <math.h>
#include "Maquina.h"


Maquina::Maquina(int opc, const Personaje& pers,const Personas& total, const Preguntas& preg){
	personaje=pers;
	total_personajes=total;
	preguntas=preg;
	opcion=opc;
	if(opc==1)
		this->nombre="maquina lista";
	else
		this->nombre="maquina tonta";
}

string Maquina::getNombre(){
	return nombre;
}

string Maquina::getNombrePersonaje(){
	return personaje.GetNombre();
}

int Maquina::getEleccionAleatoria(){
	
	int numero = rand()%(preguntas.NumPreguntas()-1);
	return numero;
}

bool Maquina::comprobarPersonaje(string nom_personaje){
	if(personaje.GetNombre().compare(nom_personaje)==0)
		return true;
	else
		return false;
}

void Maquina::descartarPersonaje(string nombre_per){
	int i=0;
	bool encontrado = false;
	while(i < total_personajes.getCantidad() && !encontrado){
		if(nombre_per.compare(total_personajes.GetPersona(i).GetNombre())==0){
			encontrado=true;
			total_personajes.eliminarPersonaje(i);
		}
		i++;
	}
}


void Maquina::descartarPregunta(int pos){
	preg_realizadas.push_back(pos);
}

int Maquina::realizarPregunta(){
	int eleccion;
	if(total_personajes.getCantidad() == 1)
		return 18;
	if(opcion==1) // Máquina inteligente
		eleccion = this->calcularEntropia();
	else // Máquina tonta
		eleccion = this->getEleccionAleatoria();

	preg_realizadas.push_back(eleccion);

	return eleccion;
}

bool Maquina::getRespuesta(int pos){

	string cod_personaje = personaje.getCodigo();
	int i=0;
	for(i;i<pos;i++);


	if(cod_personaje[i]=='1')
		return true;
	else
		return false;
}

void Maquina::obtenerRespuesta(char respuesta, string preg){

	int i=0;
	bool continuar = true;
	while(i<preguntas.NumPreguntas()-2 && continuar){

		if(preg.compare(preguntas.getPregunta(i))==0){
			continuar = false;
		}
		else
			i++;
	}

	respuesta= toupper(respuesta);
	char comparador;
	if(respuesta=='S')
		comparador='1';
	else
		comparador='0';

	vector<string> aux;

	for(int j=0;j<total_personajes.getCantidad();++j){
		string cod_personaje = total_personajes.GetPersona(j).getCodigo();

		if(comparador != cod_personaje[i]){
			aux.push_back(total_personajes.GetPersona(j).GetNombre());
		}
	}


	for(int j=0;j<aux.size();++j){
		descartarPersonaje(aux[j]);
	}

	descartarPregunta(i);

}

int Maquina::calcularEntropia(){
	int eleccion=getEleccionAleatoria(); // Por defecto

	if(total_personajes.getCantidad() != 1){


		int personajes_no, personajes_si;

		double entropia=0;
		double aux_entropia;
		// -1 se debe a que no va a calcular la de elegir un personaje
		// -2 por qué no contamos la pregunta 18
		for(int i=0; i<preguntas.NumPreguntas()-2;i++){

			bool calculo=true; // true cuando comprueba que no se ha relizado la pregunta

			for(int j=0;j<preg_realizadas.size() && calculo;++j){
				if(preg_realizadas[j]==i)
					calculo=false;
			}

			if(calculo){
				personajes_si = personajes_no = 0;
				for(int j=0;j<total_personajes.getCantidad();j++){
					string cod_personaje = total_personajes.GetPersona(j).getCodigo();
					if(cod_personaje[i]=='0')
						personajes_no++;
					else
						personajes_si++;
				}
				double cod_no, cod_si;
				if(personajes_no == 0)
					cod_no=0;
				else
				    cod_no = (1.0*personajes_no/total_personajes.getCantidad())*log2(personajes_no/(total_personajes.getCantidad()*1.0));
				if(personajes_si == 0)
					cod_si =0;
				else
					cod_si =  (personajes_si*1.0/total_personajes.getCantidad())*log2(personajes_si/(total_personajes.getCantidad()*1.0));
				
				aux_entropia=-1.0*(cod_si+cod_no);
				if(aux_entropia > entropia){
					eleccion = i;
					entropia=aux_entropia;
				}
			}

		}
	}
	else
		eleccion=18;

	return eleccion;

}

string Maquina::respuestaFinal(){
	cout << total_personajes.GetPersona(0).GetNombre() << endl;
	return total_personajes.GetPersona(0).GetNombre();
}
