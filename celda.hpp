#pragma once
#include <vector>
#include "tabla.hpp"

using namespace std;


template <class Clave>
class Celda 
{
private:
  
  unsigned int tam;		//número de bloques en la celda
  Clave* bloques;		//vector de bloques de tipo Clave
  
public:
  
  Celda(void);			//constructor por defecto
  Celda(unsigned int size);	//constructor de asignacion de tamaño
  Celda(const Celda &x);	//contructor de copia
  ~Celda(void);			//destructor
  
  unsigned tamanio(void);
  
  bool buscar(Clave x);		//elemento para buscar una clave
  bool insertar(Clave x);	//funcion para extraer una clave
  bool full(void);		//método que indica si la clave está llena
  
  void ajustar(unsigned int size);		//método para poder darle un tamaño al bloque en el constructor de la tabla
  Clave acceso(unsigned i);			//método para obtener un elemento de la clave
};

template <class Clave>
Celda<Clave>::Celda(void):
tam(0)
{}


template <class Clave>
Celda<Clave>::Celda(unsigned int size):
tam(size)
{
  bloques = new Clave[tam];
  
  for(unsigned int i=0;i<tam;i++)
  {
    bloques[i] = 0;				//lo uso para inicializar todos los elementos con un mismo valor
						//esto es de utilidad si también se implementara el método eliminar
  }

}

template <class Clave>
Celda<Clave>::Celda(const Celda &x)
{
  bloques = x.bloques;
  tam = x.tam;
}

template <class Clave>
Celda<Clave>::~Celda(void)
{}

template <class Clave>
unsigned Celda<Clave>::tamanio(void)
{
  return(tam);
}

template <class Clave>
void Celda<Clave>::ajustar(unsigned int size)
{
  tam=size;
  bloques = new Clave[tam];
  
  for(unsigned int i=0;i<tam;i++)
  {
    
    bloques[i] = 0;				//lo uso para inicializar todos los elementos con un mismo valor
							//esto es de utilidad si también se implementara el método eliminar
  }

}

template <class Clave>
bool Celda<Clave>::buscar(Clave x)
{
  for(unsigned int i=0;i<tam;i++)
  {
    if(x == bloques[i]) return true;		//si la Clave pasada coincide con algún elemento del bloque retornamos true
  }
  
  return false;					//si recorremos todo el bloque y no encontramos la clave devolvemos false
}

template <class Clave>
bool Celda<Clave>::insertar(Clave x)
{
  for(unsigned int i=0;i<tam;i++)
  {
    if(bloques[i] == 0)			//si no hay nada en esa posición del bloque
    {
      bloques[i] = x;			//le asignamos el valor x a esa posición
      return true;			//y retornamos true
    }
  }
  
  return false;				//si todos los bloques ya tienen un elemento retornamos false
}

template <class Clave>
bool Celda<Clave>::full(void)
{
  bool aux = true;
  
  for(unsigned int i=0;i<tam;i++)
  {
    if(bloques[i] == 0)	return false;		//si no hay nada en esa posición del bloque retornamos false porque no esta lleno
  }
  
  return true;				//si todos los bloques ya tienen un elemento retornamos true ya que está lleno
}

template <class Clave>
Clave Celda<Clave>::acceso(unsigned int i)
{
  return(bloques[i]);
}