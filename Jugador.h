
#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include <iostream>
#include "Personaje.h"
#include <vector>
#include "Preguntas.h"
#include "Personas.h"


using namespace std;
/**
  * @brief T.D.A. Jugador
  *
  * Esta clase representa el estado de un Jugador que está jugando al who is who.
  * En esta clase tendremos almacenados el nombre de tipo string, el Personaje que
  * le ha tocado al jugador.
  *
  * El estado del jugador sería válido con una cadena de caracteres y que personaje sea
  * un personaje valido. ¿Qué quiere decir un personaje válido? que el personaje haya sido
  * almacenado en la clase Personas que está debidamente descrita en la documentación de su clase.
  * El personaje sirve para que la máquina intente adivinar a traves de preguntas el personaje que
  * tenemos almacenado.
  */
class Jugador{
private:
	string nombre; ///< nombre del jugador
	Personaje personaje; ///< Para guardar el personaje oculto
	
public:

	/**
	  * @brief constructor de la clase Jugador que da valor al atributo privado nombre y al
	  * atributo privado personaje.
	  * @pre El personaje debe ser un personaje válido y creado y almacenado previamente en el conjunto
	  *      de personajes de la clase Personas.
	  */
	Jugador(string nom, const Personaje& personaje);
	/**
	  * @brief método que devuelve el nombre del atributo privado personaje.
	  */
	string getNombrePersonaje();
	/**
	  * @brief método que devuelve el valor del atributo privado nombre de tipo string.
	  */
	string getNombre();

};

#endif
