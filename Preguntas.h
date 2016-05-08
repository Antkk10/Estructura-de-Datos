
#ifndef _PREGUNTAS_H_
#define _PREGUNTAS_H_

#include <list>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

/** 
  * @brief T.D.A. Preguntas
  * clase que representa un conjunto de preguntas y que serán utilizadas por los jugadores del quien es quien para 
  * saber los atributos de un personaje buscado.
  * En esta clase contiene una lista de tipo string con el contenido de todas las preguntas del juego.
  *
  * Función de abstracción, si r es un objeto de tipo Preguntas
  * f(r) = r.preguntas y que utilizará la funcionalidad típica de list como push_back, size, insert, assign, erase, pop_back,
  * pop_front, push_front,... para más información visitar la página cplusplus
  *
  * Invariante de la representación:
  * r.preguntas.size >= 0
  * r.preguntas.push_back(string)
  */
class Preguntas{
private:
	list<string> preguntas; ///< lista con la cantidad de preguntas
public:
	/**
	  * @brief constructor sin parámetros
	  */
	Preguntas(){}
	/**
	  * @brief constructor de copia en el cual almacena el contenido de v.preguntas en this.preguntas
	  * @pre que v tenga 0 ó más elementos dentro de su lista.
	  */
	Preguntas(const Preguntas& v);
	/**
	  * @brief borrar método que borra el contenido de la lista preguntas
	  */
	void borrar(){
		preguntas.clear();
	}

	/**
	  * @brief operator= método con la misma funcionalidad que el constructor de copia con la diferencia
	  * que el contenido almacenado en preguntas se elimina antes de copiar copia.preguntas
	  * @param copia de tipo Preguntas que contiene las preguntas a copiar
	  */
	Preguntas& operator=(const Preguntas& copia);
	/**
	  * @brief getPregunta método que devuelve una pregunta concreta almacenada en la lista preguntas.
	  * @param pos contiene la posición que ocupa la pregunta a devolver
	  * @return el contenido de la pregunta buscada.
	  * @pre que la posición este entre el intervalo 0 y preguntas.size()
	  */
	string getPregunta(int pos)const;
	/**
	  * @brief setPregunta método que almacena una pregunta en la lista preguntas
	  */
	void setPregunta(string preg);
	/**
	  * @brief NumPreguntas método que devuelve la cantidad de preguntas almacenadas en la lista preguntas
	  */
	int NumPreguntas()const{
		return preguntas.size();
	}

	/**
	  * @brief iguales método que compara si dos string son iguales.
	  * @param primero string a comparar
	  * @param segundo string a comparar
	  * @return true cuando los dos string son iguales, false en caso contrario
	  */
	bool iguales(string primero,string segundo){
		if(primero.compare(segundo)==0)
			return true;
		else
			return false;
	}

	/**
	  * @brief operator>> función amiga de la clase Preguntas en la cual lee unas preguntas del fichero y las almacena en un objeto llamado
	  * original de tipo Preguntas.
	  * @param archivo es donde están almacenadas las preguntas a obtener.
	  * @param original objeto de tipo Pregutas que almacenará las preguntas que se leen del fichero
	  * @return archivo
	  */
	friend ifstream& operator>>(ifstream& archivo, Preguntas& original);

	/**
	  * @brief operator << es una función amiga de la clase Preguntas en la cual muestra por pantalla las preguntas almacenadas en un objeto
	  * @param out flujo de salida
	  * @param original objeto que contiene las preguntas a mostrar por pantalla.
	  * @pre que original esté inicializado
	  * @return out para que desde donde fue invocado el método se pueda seguir utilizando el flujo de salida
	  */
	friend ostream& operator<<(ostream& out, const Preguntas& original);

	/**
	  * T.D.A iterator
	  * clase que se utiliza para iterar sobre una lista<string>
	  * Concretamente esta clase está escrita en la clase Preguntas con lo cual este iterador se utilizará normalmente
	  * para iterar sobre la lista pregutas.
	  *
	  * Función de abstracción, si r es un objeto de tipo iterator
	  * f(r) = r.(*it)
	  *
	  * Invariante de la representación:
	  * r.(*it) apunta a un elemento de la lista. Esta lista va desde preguntas.begin() hasta preguntas.end()
	  */
	class iterator{
	private:
		list<string>::iterator it; ///< iterador

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
		iterator& operator++();
		/**
		  * @brief operator* método que devuelve un objeto de tipo Personaje apuntado por el iterador dentro de la lista
		  * @pre que el iterador apunte a un Personaje con contenido.
		  */
		string& operator*();
		/**
		  * @brief operator-- método que hace retroceder al iterador dentro de la lista a la que apunta
		  * @pre que haya elementos a los que apuntar dentro de la lista y que el iterador esté inicializado.
		  * @return el contenido de this
		  */
		iterator& operator--();
		/**
		  * @brief operator== método que devuelve true cuando dos iterador apuntan a objetos iguales
		  * @pre los dos iteradores deben de estar inicializados antes de llamar a esta función.
		  */
		bool operator==(const iterator& otro)const;
		/**
		  * @brief operator!= método que devuelve true cuando dos iterador apuntan a objetos disntitos
		  * @pre los dos iteradores deben de estar inicializados antes de llamar a esta función.
		  */
		bool operator!=(const iterator& otro) const;

		/**
		  * @brief el iterator es amigo de la clase Preguntas.
		  */
		friend class Preguntas;
	};
	/**
	  * @brief begin método que inicializa un iterador apuntando a la primera posición de preguntas.
	  * @return devuelve el iterador creado
	  */
	iterator begin();
	/**
	  * @brief end método que crea un iterador y lo inicializa llamando a la función end de preguntas
	  * end es una función implementada en list
	  * @return devuelve el iterador creado en el método.
	  */
	iterator end();
};


#endif
