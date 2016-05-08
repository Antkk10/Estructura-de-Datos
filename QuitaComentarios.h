
#ifndef _QUITAR_COMENTARIOS_H_
#define _QUITAR_COMENTARIOS_H_

#include <fstream>
#include <string>

using namespace std;

/**
  * @brief método que quita los comentarios del flujo de entrada f de tipo ifstream.
  * Para saber cuando es comentario, el inicio de la linea comienza por el caracter #
  * @pre que el archivo esté ya abierto.
  */
void QuitaComentarios(ifstream& f);

#endif
