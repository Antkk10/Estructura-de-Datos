


/* Métodos Privados! */
template <class Tbase>
void ArbolGeneral<Tbase>::destruir(nodo *&n){
    
    if(n!=0){ // Comprobamos si n es un nodo
    	destruir(n->izqda); // Llamada recursiva para destruir hijo izquierda
    	destruir(n->drcha); // Llamada recursiva para destruir hijo derecha
    	delete n; // Borramos el nodo
    	n=0; // Para saber que el nodo es nulo

    }
}


template <class Tbase>
void ArbolGeneral<Tbase>::copiar(nodo *& dest, nodo *orig){

	if(orig ==0) // Origen no es nodo
		dest=0; 
	else{
		if(laraiz==0){ // árbol sin nodos
			AsignaRaiz(orig->etiqueta); // Creamos la raiz
			copiar(dest->izqda,orig->izqda); // Copiamos hijo izquierda
			copiar(dest->drcha,orig->drcha); // Copiamos hermano derecha
		}
		else{

			dest = new nodo; // Reservamos memoria nodo
			dest->etiqueta=orig->etiqueta; // Copiamos el valor
			dest->padre=0; // sin padre
			dest->izqda=0; // sin hijo
			dest->drcha=0; // sin hermano derecha
			copiar(dest->izqda,orig->izqda); // Copiamos hijo
			copiar(dest->drcha,orig->drcha); // Copiamos hermano derecha



		}
		if(dest->izqda!=0){ // Si tiene hijo
			dest->izqda->padre=dest; // El hijo apunta a su padre
			nodo *aux =dest->izqda; // auxiliar
			while(aux->drcha!=0){
				aux->drcha->padre=dest; // Los hermanos del hijo apunta al mismo padre
				aux=aux->drcha;
			}
		}
	}
}

template <class Tbase>
int ArbolGeneral<Tbase>::contar(const nodo *n) const{
	if(n==0) // Sin nodo
		return 0; // El nodo no se cuenta
	else{
		nodo *aux; // Variable auxiliar
		int cnt=0; // Contador de nodos
		for(aux=n->izqda;aux!=0;aux=aux->drcha)
			cnt +=contar(aux); // Acumulamos cuantos nodos tenemos
		return 1 + cnt; // Contador + raiz
	}
}

template <class Tbase>
bool ArbolGeneral<Tbase>::soniguales(const nodo *n1, const nodo *n2) const{
	if(n1 == 0 && n2 == 0) // Ninguno es nodo
		return true;
	if(n1==0 || n2 == 0) // Uno de los dos es nodo vacio
		return false;
	else{
		if(n1->etiqueta != n2->etiqueta) // Etiquetas distintas
			return false;
		else{
			bool idem=true; // idénticos
			nodo *aux1, *aux2; // auxiliares.
			for(aux1=n1->izqda,aux2=n2->izqda;aux1!=0 && idem && aux2!=0;
				aux1=aux1->drcha, aux2=aux2->drcha){
				idem=soniguales(aux1,aux2);
			}
			return idem && aux1==0 && aux2 == 0;
		}
	}

}

template <class Tbase>
int ArbolGeneral<Tbase>::Altura(nodo *n) const {
	if(n==0)
		return -1;
	else{
		int max=-1;
		nodo *aux;
		for(aux=n->izqda;aux!=0;aux=aux->drcha){
			if(Altura(aux) > max)
				max=Altura(max);
		}
		return 1+max;
	}
}

template <class Tbase>
void ArbolGeneral<Tbase>::escribe_arbol(std::ostream& out, nodo *nod) const{

	if(nod!=0){
		out << "n"<< nod->etiqueta;

		nodo *aux;
		for(aux=nod->izqda;aux!=0;aux=aux->drcha)
			escribe_arbol(out,aux);
		cout << "x";
	}
	else
		cout << "x";

}

template <class Tbase>
void ArbolGeneral<Tbase>::lee_arbol(std::istream& in, nodo *& nod){


	char c; // Carácter para leer
	in.get(c);
		switch(c){
			case 'x':
				nod=0;
				break;
			case 'n':
				Tbase et;
				in >> et;
				nod = new nodo;
				nod->etiqueta=et;
				nod->padre=0;
				nod->izqda=0;
				nod->drcha=0;
				lee_arbol(in,nod->izqda);
				lee_arbol(in,nod->drcha);
				if(nod->izqda!=0){
					nod->izqda->padre=nod;
					nodo *aux =nod->izqda;
					while(aux->drcha!=0){
						aux->drcha->padre=nod;
						aux=aux->drcha;
					}
				}
				break;
		}
	
}


/* Métodos públicos. */


template <class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral(){
	laraiz = 0;  //El constructor por defecto crea un árbol vacío
}

template <class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral(const ArbolGeneral<Tbase>& v){
	laraiz=0;
	copiar(laraiz,v.laraiz);
}

template <class Tbase>
ArbolGeneral<Tbase>::ArbolGeneral(const Tbase& e)
{
	laraiz=0;
	AsignaRaiz(e);
}

template <class Tbase>
ArbolGeneral<Tbase>::~ArbolGeneral(){
	destruir(laraiz); // Llamada para destruir la raiz
}

template <class Tbase>
ArbolGeneral<Tbase>& ArbolGeneral<Tbase>::operator=(const ArbolGeneral<Tbase>& v){

	if(this!=&v){

		destruir(laraiz);
		copiar(laraiz,v.laraiz);

	}

	return *this;
}
template <class Tbase>
void ArbolGeneral<Tbase>::AsignaRaiz(const Tbase& e){
	destruir(laraiz);
	laraiz = new nodo; // Creamos el nodo raiz
	laraiz->padre =0; // No tiene padre
	laraiz->izqda =0; // No tiene hijo a la izquierda
	laraiz->drcha = 0; // No tiene hijo a la derecha     
	laraiz->etiqueta = e; // Asignamos su etiqueta 
}

template <class Tbase>
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::raiz() const{
	return laraiz; // Devuelve la raiz del árbol
}


template <class Tbase>
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::hijomasizquierda(const typename ArbolGeneral<Tbase>::Nodo n) const{
	return n->izqda; // Devuelve el hijo a la izquierda.
}

template <class Tbase>
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::hermanoderecha(const ArbolGeneral<Tbase>::Nodo n) const{
	return n->drcha;
}

template <class Tbase>
typename ArbolGeneral<Tbase>::Nodo ArbolGeneral<Tbase>::padre(const typename ArbolGeneral<Tbase>::Nodo n) const{
	return n->padre;
}

template <class Tbase>
Tbase& ArbolGeneral<Tbase>::etiqueta(const typename ArbolGeneral<Tbase>::Nodo n){
	return n->etiqueta;
}

template <class Tbase>
const Tbase& ArbolGeneral<Tbase>::etiqueta(const typename ArbolGeneral<Tbase>::Nodo n) const{
	return n->etiqueta;
}

template <class Tbase>
void ArbolGeneral<Tbase>::asignar_subarbol(const ArbolGeneral<Tbase>& orig, const typename ArbolGeneral<Tbase>::Nodo nod){
	destruir(laraiz); // Borramos todo el contenido del árbol actual
	copiar(laraiz,nod); // Copiamos el subárbol en el árbol receptor
	if(laraiz!=0){ // Si la raiz no es vacia
		laraiz->padre=0; // Actualizamos su padre.
		destruir(laraiz->drcha); // Si en la raiz se han copiado hermanos, los borra.
	}
}

template <class Tbase>
void ArbolGeneral<Tbase>::podar_hermanoderecha(typename ArbolGeneral<Tbase>::Nodo n, ArbolGeneral<Tbase>& dest){
	
	if(n->drcha!=0){ // Tiene hermano a la derecha

		dest.laraiz=n->drcha; // la raiz del árbol destino apunta al nodo hermano derecha que se quiere podar.
		n->drcha=n->drcha->drcha; // Actualizalos el hermano a la derecha que apunta al siguiente hermano a la derehca o es nul
		dest.laraiz->padre=0; // El nodo podado no tiene padre
		dest.laraiz->drcha=0; // Tampoco tiene hermano
	}
}

template <class Tbase>
void ArbolGeneral<Tbase>::podar_hijomasizquierda(typename ArbolGeneral<Tbase>::Nodo n, ArbolGeneral<Tbase>& dest){

	if(n->izqda!=0){ // Tiene hijo a la izquierda
		dest.laraiz=n->izqda; // El nuevo ábol contiene el hijo a la izquierda
		n->izqda=n->izqda->drcha; // El hijo a la izqd del árbol receptor apunta al hermano del anterior hijo
		dest.laraiz->drcha=0; // La raiz del nuevo árbol no tiene hermano a la derecha
		dest.laraiz->padre=0; // Tampoco tiene nodo padre
	}
}

template <class Tbase>
void ArbolGeneral<Tbase>::insertar_hijomasizquierda(Nodo n, ArbolGeneral<Tbase>& rama){

	if(!rama.empty()){ // Comprobamos que la rama tiene nodos
		Nodo aux; // Nodo auxiliar
		aux=n->izqda; // Guardamos el nodo hijo actual
		copiar(n->izqda,rama.raiz()); // Copiamos el contenido y creamos un nuevo hijo más izquierda
		n->izqda->drcha=aux; // El hermano derecho del hijo izquierda actual es el hijo izquierdo anterior
		n->izqda->padre=n; // Le asignamos su padre
		rama.clear(); // Borramos los nodos de la rama.
	}
}

template <class Tbase>
void ArbolGeneral<Tbase>::insertar_hermanoderecha(Nodo n, ArbolGeneral<Tbase>& rama){
	assert(n->padre!=0); // Para que la raiz no tenga hermano a la derecha
	if(!rama.empty()){ // Comprobamos que la rama no esté vacia
		Nodo aux; // Nodo auxiliar
		aux=n->drcha; // aux contiene el hermano a la derecha actual
		copiar(n->drcha,rama.raiz()); // Copiamos la rama en el hermano a la derecha de n
		n->drcha->drcha=aux; // Su hermano a la derecha de nodo apunta al hermano a la derecha anterior
		n->drcha->padre=n->padre; // Su padre es el mismo que el de sus hermanos
		rama.clear();

	}
}

template <class Tbase>
void ArbolGeneral<Tbase>::clear(){
	destruir(laraiz); // Llamada para borrar todos los nodos del árbol
	laraiz=0; // a 0 para que no tenga contenido basura.
}

template <class Tbase>
int ArbolGeneral<Tbase>::size() const{
	
	return contar(laraiz); // Devuelve el número de nodos del árbol
}

template <class Tbase>
bool ArbolGeneral<Tbase>::empty() const{
	if(laraiz!=0)
		return false;
	else
		return true;
}

template <class Tbase>
bool ArbolGeneral<Tbase>::operator==(const ArbolGeneral<Tbase>& v) const{
	return soniguales(laraiz,v.laraiz);
}

template <class Tbase>
bool ArbolGeneral<Tbase>::operator!=(const ArbolGeneral<Tbase>& v) const{
	return !soniguales(laraiz,v.laraiz); // son iguales negado
}



template<class T>
std::istream& operator>>(std::istream& in, ArbolGeneral<T>& v){
	v.lee_arbol(in,v.laraiz);
	return in;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const ArbolGeneral<T>& v){
	v.escribe_arbol(out,v.laraiz);
	return out;
}

template <class Tbase>
ArbolGeneral<Tbase>::iter_preorden::iter_preorden(){
	it = 0;
	raiz=it;
	level=-1;
}

template <class Tbase>
Tbase& ArbolGeneral<Tbase>::iter_preorden::operator*(){
	return it->etiqueta;
}

template <class Tbase>
int ArbolGeneral<Tbase>::iter_preorden::getlevel()const{
	return level;
}

template <class Tbase>
bool ArbolGeneral<Tbase>::iter_preorden::operator==(const iter_preorden& i){
	if(it==0 && i.it==0) // Los dos iteradores apuntan a nodos vacios
		return true;
	if(it==0 || i.it==0) // Uno de los dos iteradores apuntan a nodo nulo
		return false;
	else
	return (it->etiqueta == i.it->etiqueta) && (raiz->etiqueta == i.raiz->etiqueta)
				&& (level == i.level);
}

template <class Tbase>
bool ArbolGeneral<Tbase>::iter_preorden::operator!=(const iter_preorden &i){
	if(it==0 && i.it==0) // Los dos iteradores apuntan a nodos vacios
		return false;
	if(it==0 || i.it==0) // Uno de los dos iteradores apuntan a nodo nulo
		return true;
	else
		return (it->etiqueta != i.it->etiqueta) || (raiz->etiqueta != i.raiz->etiqueta)
				|| (level != i.level);
}

template <class Tbase>
ArbolGeneral<Tbase>::const_iter_preorden::const_iter_preorden(){
	it = 0;
	raiz=it;
	level=-1;
}

template <class Tbase>
const Tbase& ArbolGeneral<Tbase>::const_iter_preorden::operator*(){
	return it->etiqueta;
}

template <class Tbase>
int ArbolGeneral<Tbase>::const_iter_preorden::getlevel()const{
	return level;
}

template <class Tbase>
typename ArbolGeneral<Tbase>::const_iter_preorden& ArbolGeneral<Tbase>::const_iter_preorden::operator++(){
	if (it->izqda!=0){
	      it= it->izqda;
	      level = level+1; 
	    } 
	    else{
		if (it->drcha!=0)
		  it=it->drcha;
		else{
		 if (it->padre!=0){
		   while  (it->padre!=0 && it->drcha==0){
		    it=it->padre;
		    level = level-1;
		   }
		   it=it->drcha;
		    
		 }
		 else{
		   it=0;
		   level = -1;
		 }
		}	 
	    }
	    return *this;
}

template <class Tbase>
bool ArbolGeneral<Tbase>::const_iter_preorden::operator==(const typename ArbolGeneral<Tbase>::const_iter_preorden& i){
	if(it==0 && i.it==0) // Los dos iteradores apuntan a nodos vacios
		return true;
	if(it==0 || i.it==0) // Uno de los dos iteradores apuntan a nodo nulo
		return false;
	else
	return (it->etiqueta == i.it->etiqueta) && (raiz->etiqueta == i.raiz->etiqueta)
				&& (level == i.level);
}

template <class Tbase>
bool ArbolGeneral<Tbase>::const_iter_preorden::operator!=(const typename ArbolGeneral<Tbase>::const_iter_preorden& i){
	if(it==0 && i.it==0) // Los dos iteradores apuntan a nodos vacios
		return false;
	if(it==0 || i.it==0) // Uno de los dos iteradores apuntan a nodo nulo
		return true;
	else
		return (it->etiqueta != i.it->etiqueta) || (raiz->etiqueta != i.raiz->etiqueta)
				|| (level != i.level);	
}

template <class Tbase>
typename ArbolGeneral<Tbase>::iter_preorden ArbolGeneral<Tbase>::begin(){
	ArbolGeneral<Tbase>::iter_preorden it;
	it.it=it.raiz=raiz();
	it.level=-1;
	return it;
}

template <class Tbase>
typename ArbolGeneral<Tbase>::const_iter_preorden ArbolGeneral<Tbase>::begin() const{
	ArbolGeneral<Tbase>::const_iter_preorden cit;
	cit.it=cit.raiz=raiz();
	cit.level=-1;
	return cit;
}

template <class Tbase>
typename ArbolGeneral<Tbase>::iter_preorden ArbolGeneral<Tbase>::end(){
	ArbolGeneral<Tbase>::iter_preorden it;

	it.raiz=raiz();
	it.it=0;
	it.level=-1;

	return it;
}

template <class Tbase>
typename ArbolGeneral<Tbase>::const_iter_preorden ArbolGeneral<Tbase>::end()const{
	ArbolGeneral<Tbase>::const_iter_preorden cit;

	cit.raiz=raiz();
	cit.it=0;
	cit.level=-1;

	return cit;
}
