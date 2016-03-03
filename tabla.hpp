#pragma once
#include "celda.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>

template <class Clave>
class Tabla
{
private:
  
  unsigned int tam;							//numero de celdas
  unsigned int paramD;							//indica el tipo de función de dispersión que se usará
  unsigned int paramE;							//indica el tipo de función de exploración que se usará
  vector<Celda<Clave> > celdas;						//vector de celdas
  
public:
  
  Tabla(unsigned int sizeC,unsigned int sizeB,unsigned int parametroE, unsigned int paramteroD);	//constructor que asigna el número de celdas(sizeC) y de bloques(sizeB)
  ~Tabla(void);								//destructor
  
  Celda<Clave> &operator[](unsigned i);			//operador para acceder a un elento de la lista
  template<class T>
  friend ostream& operator<<(ostream&, Tabla<T>&);	//operador de salida
  
  unsigned int dispersion(Clave x);			//función de dispersión
  unsigned int dispersion_suma(Clave x);		//función de dispersión suma(1)
  unsigned int dispersion_modulo(Clave x);		//función de dispersión modulo(2)
  unsigned int dispersion_aleatoria(Clave x);		//función de dispersión aleatoria(3)
  
  unsigned int exploracion(Clave x, unsigned int& intento);			//función de exploración
  unsigned int exploracion_lineal(Clave x, unsigned int& intento);		//función de exploración lineal
  unsigned int exploracion_cuadratica(Clave x, unsigned int& intento);		//función de exploración cuadrática
  unsigned int exploracion_doble(Clave x, unsigned int& intento);		//función de exploración dispersión doble
  unsigned int exploracion_redispersion(Clave x, unsigned int& intento);	//función de exploración re-dispersión
  
};

template <class Clave>
Tabla<Clave>::Tabla(unsigned int sizeC,unsigned int sizeB, unsigned int parametroE, unsigned int parametroD):	//Constructor
tam(sizeC),
paramD(parametroD),
paramE(parametroE)
{
  celdas.resize(sizeC);
  for(unsigned i =0;i<tam;i++) celdas[i].ajustar(sizeB);
  
}

template <class Clave>
Tabla<Clave>::~Tabla(void)
{
}

template <class Clave>
Celda<Clave> &Tabla<Clave>::operator[](unsigned i)
{
  return(celdas[i]);
}

template <class T2>
ostream& operator<<(ostream& os, Tabla<T2>& v) {

	for(int i = 0; i<v.celdas[i].tamanio();i++) {
	  
	  os << setfill('-');
	  os << setw(v.tam*13) << "-";
	  cout << endl;
	  os << setfill(' ');
	  os << "|";
	  
	  for(int j=0;j<v.tam;j++)
	  {
	    os << setw(10) << v.celdas[j].acceso(i) << " | ";
	  }
	  
	  cout << endl;
		
	}
	
  os << setfill('-');
  os << setw(v.tam*13) << "-";
  cout << endl;
  os << setfill('\0');

	return os;
}	


//**************************DISPERSIÓN***********************************

template <class Clave>
unsigned int Tabla<Clave>::dispersion(Clave x)			//Funcion de dispersión genérica
{
  switch(paramD)
  {
    case 0:
      
      return(dispersion_suma(x));
      break;
      
    case 1:
      
      return(dispersion_modulo(x));
      break;
      
    case 2:
      
      return(dispersion_aleatoria(x));
      break;
      
    default:
      
      cout << "Opción de dispersión invalida, se saldrá del programa" << endl;
      exit(1);
  }
}

template <class Clave>
unsigned int Tabla<Clave>::dispersion_suma(Clave x)					//función de dispersión suma(0)
{//función de dispersión suma(1)
  Clave d = 0;
  Clave y = 0;
  
  unsigned a = 10; 
  
  while(x > 0)
  {
    y = x%a;
    d = d + y;
    x = x/a;
  }
  
  
  unsigned int r = d%tam;
  return(r);
}

template <class Clave>
unsigned int Tabla<Clave>::dispersion_modulo(Clave x)					//función de dispersión módulo(1)
{
  unsigned int r =x%tam;
  return(r);
}

template <class Clave>
unsigned int Tabla<Clave>::dispersion_aleatoria(Clave x)				//función de dispersión pseudo-aleatoria(2)
{
  srand((unsigned int) x);
  return ((rand()%tam));
}

//****************************EXPLORACIÓN************************************

template <class Clave>
unsigned int Tabla<Clave>::exploracion(Clave x, unsigned int& intento)
{
  switch(paramE)
  {
    case 0:
      
      return(exploracion_lineal(x,intento));
      break;
      
    case 1:
      
      return(exploracion_cuadratica(x,intento));
      break;
      
    case 2:
      
      return(exploracion_doble(x,intento));
      break;
      
    case 3:
      
      return(exploracion_redispersion(x,intento));
      break;
      
    default:
      
      cout << "Opción de exploración invalida, se saldrá del programa" << endl;
      exit(1);
  }
}

template <class Clave>
unsigned int Tabla<Clave>::exploracion_lineal(Clave x, unsigned int& intento)
{
   return((dispersion(x)+intento)%tam);		//retornamos el numero de la celda
  
}

template <class Clave>
unsigned int Tabla<Clave>::exploracion_cuadratica(Clave x, unsigned int& intento)
{
  return((dispersion(x)+(intento*intento))%tam);		//Usamos la funcion cuadrática (i*i)%t, si la celda no está llena retornamos la posición
 
}

template <class Clave>
unsigned int Tabla<Clave>::exploracion_doble(Clave x, unsigned int& intento)
{
 return((dispersion(x)+intento*dispersion_aleatoria(x))%tam);	//Usamos la funcion de dispersión aleatoria, como amplitud de paso, por defecto
}

template <class Clave>
unsigned int Tabla<Clave>::exploracion_redispersion(Clave x, unsigned int& intento)
{
  srand((unsigned int) x);
  unsigned int y;
  
    y = rand()%3;
    switch(y)
    {
      case 0:
      
      return((dispersion(x)+intento)%tam);			//Exploración lineal
      break;
      
    case 1:
      
      return((dispersion(x)+(intento*intento))%tam);		//Exploración Cuadrática
      break;
      
    case 2:
      
      return((dispersion(x)+intento*dispersion_aleatoria(x))%tam);	//Exploración Dispersión Doble
      break;
      
    }
}


