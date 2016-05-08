
#ifndef _PERSONAJE_H_
#define _PERSONAJE_H_

#include <iostream>
#include <cstring>


using namespace std;

/**
  * @brief T.D.A Personaje
  * Esta clase representa a un personaje que existe en el juego y en el cual almacena los atributos
  * que lo identifican. Estos atributos son nombre (tipo:string) que representa el nombre del personaje
  * fichero (tipo:string) que representa la localización de la imagen de este personaje y codigo (tipo:string) 
  * que cada posición del personaje representa la contestación a una pregunta concreta. En el código
  * el 0 significará negación y el 1 afirmación. Para que esta respuesta sea válida con la pregunta que la identifica,
  * en la creación del juego el código debe ser generado una vez que las posiciones de las preguntas estén ya almacenadas
  * y que estas preguntas tengan una posición constante para que cuando se compruebe la respuesta del personaje a una pregunta
  * pueda ser correcta la respuesta a esta pregunta.
  *
  * En la función de abstracción si r es un objeto de tipo Personaje:
  * f(r) = {r.nombre, r.fichero, r.codigo}
  *
  * Invariante de la representacón:
  * nombre = cadena de caracteres
  * fichero = carpeta existente dentro de memoria
  * codigo = Lo ya mencionado anteriormente, y además que no haya más 0/1 que preguntas totales.
  */
class Personaje{
private:
	string nombre; ///< representa el nombre del personaje
	string fichero; ///< Donde está su imagen
	string codigo; ///< código de respuesta a las preguntas
public:
	/**
	  * @brief constructor sin parámetros.
      */
	Personaje(){}
	/**
	  * @brief constructor con parámetros que almacena el nombre y la dirección del fichero.
	  * @param nom string con el nombre del jugador.
	  * @param fich string con la dirección del fichero donde se encuentra la foto del personaje
	  */
	Personaje(string nom, string fich);
	/**
	  * @brief operador= que sirve para copiar los atributos de un personaje en this.
	  * @pre que el personaje esté ya almacenado dentro de un objeto de la clase Personas.
	  */
	Personaje& operator=(const Personaje& personaje);
	/**
	  * @brief método que almacena un código en el atributo privado codigo.
	  * @param cod contiene el código a almacenar.
	  * @pre que el código sea válido cumpliendo las restricciónes ya mencionadas en TDA Personaje.
	  */
	void SetCodigoRespuestas(string cod);
	/**
	  * @brief GetNombre devuelve el nombre del personaje
	  */
	string GetNombre();
	/**
	  * @brief getFichero devuelve el contenido del atributo privado fichero
	  */
	string getFichero();
	/**
	  * @brief getCodigo método que devuelve el código del personaje
	  * @pre que exista ya el codigo almacenado.
	  */
	string getCodigo();

};

#endif
