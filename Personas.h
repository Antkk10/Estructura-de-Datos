
#ifndef _PERSONAS_H_
#define _PERSONAS_H_

#include "Personaje.h"
#include <iostream>
#include <list>
#include <cstring>

using namespace std;
/**
  * @brief T.D.A Personas
  * Esta clase representa al conjunto de personajes que hay disponibles en el tablero
  * para poder jugar al who is who. Su representación es una lista de tipo Personaje con todos
  * los personajes almacenados en esta lista. A traves de esta clase se crearán los personajes para el juego
  *
  * En la función de abstracción, si r es u objeto de tipo Personas:
  *  f(r) ={r.milista[0], r.milista[1],....,r.milista[total_personajes-1]}
  *
  * En el invariante de la representación
  * r.milista.size >= 0
  * r.milista[0], r.milista[1],... r.milista[n-1] debe tener almacenados objetos de tipo Personaje
  * la validez de representación de un personaje viene detallada en la clase Personaje.
  */
class Personas{
private:
	list<Personaje> milista; ///< contiene el total de personajes del juego
public:
	/**
	  * @brief constructor por defecto
	  */
	Personas(){}
	/**
	  * @brief constructor de copia en el cual guarda los mismo valores de los atributos contenidos en un objeto
	  * de tipo Personas.
	  * @pre que el objeto de tipo Personas tenga contenido y cumpla con el invariante de la representación detallada
	  * en la parte superior de este fichero.
	  */
	Personas(const Personas& personas);
	/**
	  * @brief operador = que a diferencia del constructor de copia elimina antes el contenido almacenado en 
	  * el atributo privado milista.
	  * @pre que el objeto de tipo Personas tenga contenido y cumpla con el invariante de la representación detallada
	  * en la parte superior de este fichero.
	  */
	Personas& operator=(const Personas& copia);
	/**
	  * @brief getCantidad método que devuelve la cantidad de personajes almacenados en la lista.
	  */
	int getCantidad(){
		return milista.size();
	}
	/**
	  * @brief eliminarPersonaje método que eliminar un personaje de la lista. El personaje a eliminar viene 
	  * identificado por un entero.
	  * @param pos es la posición que ocupa el personaje dentro de la lista.
	  * @pre que sea una posición válida dentro de la lista.
	  */
	void eliminarPersonaje(int pos);
	/**
	  * @brief clear método que elimina todo el contenido de la lista
	  */
	void clear();

	/**
	  * @brief método amigo de la clase Personas que recibe un archivo y un objeto de tipo Personas en el cual
	  * desde el fichero se leeran los valores de personajes y se irán almacenando en el objeto persona que ha sido
	  * recibido por referencia.
	  * @param archivo es el archivo con los personajes a almacenar.
	  * @param persona es el objeto donde se irán almacenando los personajes
	  * @pre que el archivo esté abierto.
	  */
	friend ifstream& operator>>(ifstream& archivo, Personas& persona);
	/**
	  * @brief método que utiliza el flujo de salida para mostrar por pantalla la cantidad
	  * de personajes almacenados en el objeto de tipo Personas.
	  * @param out para el flujo de salida
	  * @param personajes el objeto que contiene los personajes
	  * @pre que el objeto personajes esté debidamente inicializado.
	  */
	friend ostream& operator<<(ostream& out, Personas& personajes);
	/**
	  * @brief iterator
	  * clase que está definida dentro de la clase Personas y que es utilizada para iterar sobre la lista de
	  * personajes almacenada en la clase Personas.
	  *
	  * Función de abstracción, si r es un objeto de tipo iterator
	  * f(r) = r.(*it)
	  *
	  * Invariante de la representación:
	  * r.(*it) apunta a un elemento de la lista. Esta lista va desde milista.begin() hasta milista.end()
	  */
	class iterator{
	private:
		list<Personaje>::iterator it; ///< iterador 
	public:
		/**
		  * @brief constructor sin parámetros
		  */
		iterator(){}
		/**
		  * @brief operator++ método que hace avanzar al iterador dentro de la lista a la que apunta
		  * @pre que haya elementos a los que apuntar dentro de la lista y que el iterador esté inicializado.
		  * @return el contenido de this
		  */
		iterator& operator++(){
			++it;
			return *this; 
		}
		/**
		  * @brief operator-- método que hace retroceder al iterador dentro de la lista a la que apunta
		  * @pre que haya elementos a los que apuntar dentro de la lista y que el iterador esté inicializado.
		  * @return el contenido de this
		  */
		iterator& operator--(){
			--it;
			return *this;
		}

		/**
		  * @brief operator* método que devuelve un objeto de tipo Personaje apuntado por el iterador dentro de la lista
		  * @pre que el iterador apunte a un Personaje con contenido.
		  */
		Personaje& operator*(){
			return *it;
		}
		/**
		  * @brief operator!= método que devuelve true cuando dos iterador apuntan a objetos disntitos
		  * @pre los dos iteradores deben de estar inicializados antes de llamar a esta función.
		  */
		bool operator!=(const iterator& i){

			return it!=i.it;
		}
		/**
		  * @brief operator== método que devuelve true cuando dos iterador apuntan a objetos iguales
		  * @pre los dos iteradores deben de estar inicializados antes de llamar a esta función.
		  */
		bool operator==(const iterator& i){

			return it==i.it;
		}
		/**
		  * @brief este iterador es amigo de la clase Personas
		  */
		friend class Personas;
	};

	/**
	  * @brief método que devuelve el Personaje por referencia que ocupa
	  * dentro de la lista
	  * @param pos identifica la posición del personaje dentro de la lista.
	  * @pre que pos esté dentro del intervalo 0 <= pos <= milista.size()-1
	  */
	Personaje& GetPersona(int pos);

	/**
	  * @brief begin método que inicializa un iterador apuntando a la primera posición de milista.
	  * @return devuelve el iterador creado
	  */
	iterator begin(){
		iterator it;
		it.it=milista.begin();
		return it;
	}
	/**
	  * @brief end método que crea un iterador y lo inicializa llamando a la función end de milista
	  * end es una función implementada en list
	  * @return devuelve el iterador creado en el método.
	  */
	iterator end(){
		iterator it;
		it.it=milista.end();
		return it;
	}

};

#endif
