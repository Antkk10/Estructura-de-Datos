
#ifndef _MAQUINA_H_
#define _MAQUINA_H_

#include <vector>
#include "Preguntas.h"
#include "Personas.h"
#include <iostream>
#include "Personaje.h"

using namespace std;


/**
  * T.D.A Máquina
  *
  * La clase máquina representa el estado y la funcionalidad simulando a jugador para el juego
  * who is who. La máquina puede simular acciones como preguntar al contrincante por rasgos del personaje
  * a adivinar, eliminar preguntas ya hechas, eliminar personajes que no se correspondan con la respuesta 
  * obtenida, responder a preguntas realizadas por el contrincante y unas funciones privadas que dependiendo
  * de la "inteligencia" de la máquina con las cuales podrá hacer mejores preguntas para adivinar el personaje
  * del contrario. Hay dos tipos de máquina representados en esta clase por un entero con nombre opcion.
  * La opción número 1 representará a la máquina inteligente que utilizará un método denominado calcularEntropia.
  * La máquina tonta tendrá como opción el número 0 y realizará la pregunta de forma aleatoria entre todas las posibles 
  * preguntas.
  *
  * La máquina viene representada por un nombre (string), el personaje (tipo:Personaje) que tiene almacenado
  * y que debe adivinar el adversario, total_personajes (tipo:Personas) que son el total de personajes
  * que hay en el tablero, preguntas (tipo:Preguntas) que contiene el total de preguntas que puede realizar
  * la máquina y un vector de enteros llamado preg_realizadas para almacenar la posición que ocupa una pregunta
  * dentro del objeto preguntas y que se almacena en el vector para que no pueda repetir preguntas.
  *
  * En la función de abstracción, si r es un objeto de tipo Maquina:
  * f(r) = {r.nombre, r.personaje, r.total_personajes, r.preguntas, {r.preg_realizadas[0],...,
  * r.preg_realizadas[r.preguntas.size() - 1]}}
  */
class Maquina{
private:
	string nombre; ///< nombre de la máquina "máquina lista" o "máquina tonta"
	Personaje personaje; ///< personaje oculto de la máquina
	Personas total_personajes; ///< total de personajes en el tablero
	Preguntas preguntas; /// < total de preguntas que puede realizar la máquina
	vector<int> preg_realizadas; ///< vector con las posiciones de las preguntas ya realizadas
	int opcion; ///< Representa el tipo de máquina
	/**
	  * @brief Método que devuelve la posición de una pregunta a realizar.
	  *
	  */
	int getEleccionAleatoria();
	/**
	  * @brief método que devuelve la posición de una pregunta a realizar.
	  * La elección de esta pregunta se realizará con la siguiente fórmula:
	  *
	  * H(pregunta) = -(p(No)*log2(p(No))+ p(Si)*log2(p(Si)))
	  * con esta fórmula obtenemos la entropia.
	  *
	  * @return devuelve un entero que representa la posición que ocupa la pregunta
	  * dentro del objeto preguntas.
	  */
	int calcularEntropia();
	/**
	  * @brief descartarPersonaje
	  * método que llama a una función del objeto total_personajes pasandole como parámetro
	  * el string nombre_per. Sirve para eliminar un personaje del conjunto de personajes almacenados
	  * @param nombre_per es un string con el nombre del personaje a eliminar
	  */
	void descartarPersonaje(string nombre_per);
	/** @brief descartarPregunta
	  * método que almacena la posicíón que ocupa una pregunta en el vector de tipo int llamado
	  * preg_realizadas.
	  * @param pos un entero que representa la posición que ocupa una pregunta dentro del obtejo preguntas.
	  * @pre que sea una posición válida dentro del objeto preguntas.
	  */
	void descartarPregunta(int pos);
public:
	/**
	  * @brief Constructor.
	  * Le da valor a los atributos privados de la clase, como la opción de la máquina,
	  * el personaje oculto, el total de personajes del tablero y el total de preguntas que puede realizar la máquina.
	  * @param opc es el parámetro que indica la máquina seleccionada. 1 representa la máquina inteligente
	  * y cualquier otra opción introducida representa la máquina tonta.
	  * @param pers es un parámetro con el contenido del personaje oculto a almacenar.
	  * @param total es un parámetro de tipo Personas que contiene el total de personajes del juego.
	  * @param preg representa el total de preguntas que puede realizar la máquina al adversario.
	  */
	Maquina(int opc, const Personaje& pers, const Personas& total,
		const Preguntas& preg);
	/**
	  * @brief método que devuelve el nombre de la máquina.
	  */
	string getNombre();
	/**
	  * @brief método que devuelve el nombre del personaje oculto
	  */
	string getNombrePersonaje();
	/**
	  * @brief método que devuelve true si el string recibido como parámetro
	  * es el mismo que el nombre del personaje oculto.
	  * @param nom_personaje contiene el nombre del personaje a comparar.
	  * @return devueve true si el nombre recibido como parámetro es el mismo
	  * que el nombre del personaje oculto.
	  */
	bool comprobarPersonaje(string nom_personaje);
	/**
	  * @brief realizarPregunta método que devuelve un entero que identifica a una pregunta concreta.
	  * Este método conecta o bien con calcularEntropia o getEleccionAleatoria, dependiendo del tipo
	  * de máquina.
	  */
	int realizarPregunta();
	/**
	  * @brief método que devuelve true como afirmativa a una pregunta realizada por el adversario.
	  * Esta pregunta viene representada por un entero que se recibe como parámetro y que gracias a 
	  * este entero podemos identificar la pregunta dentro del objeto preguntas.
	  * @param pos un entero que identifica a la pregunta que realiza el adversario dentro del objeto
	  * preguntas.
	  * @return true cuando la respuesta es afirmativa a una pregunta, false en caso contrario.
	  */
	bool getRespuesta(int pos);
	/**
	  * @brief método que recibe la respuesta a una pregunta realizada. Con este método podemos
	  * eliminar la pregunta realizada y los personajes que no se corresponden con la respuesta.
	  * @param respuesta es un carácter que representa la afirmación o negación de una pregunta
	  * @param preg representa a la pregunta realizada.
	  */
	void obtenerRespuesta(char respuesta, string preg);
	/**
	  * @brief método que devuelve el nombre del personaje que "piensa" la máquina que es el personaje oculto
	  * del adversario. Este método solo se invoca cuando en el objeto total_personajes solo queda un personaje
	  * almacenado.
	  */
	string respuestaFinal();
	/**
	  * @brief Método que devuelve el total de personajes almacenados en el objeto total_personajes.
	  */
	Personas getPersonas(){
		return total_personajes;
	}
};

#endif
