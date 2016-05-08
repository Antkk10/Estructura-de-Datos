
#include "QuitaComentarios.h"

void QuitaComentarios(ifstream& f){

  while(f.peek()=='#' || f.peek() == '\n'){
    string linea;
    getline(f,linea); // Quita toda la linea
  }
}
