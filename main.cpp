#include "tabla.hpp"
#include "celda.hpp"
#include "dni.hpp"
#include <time.h>

int main(void)
{
  system("clear");
  unsigned nCeldas, nBloques;
  unsigned h = 5;
  unsigned g = 5;
  
//********************(1)********************
  
  cout << "******PARAMETROS PARA LA INICIALIZACION DE LA TABLA HASH******" << endl;	//Pedimos la información para crear la tabla.
  cout << "\nNúmero de celdas->"; cin >> nCeldas;						//Numero de celdas de la tabla
  cout << "Tamaño del bloque->"; cin >> nBloques;					//El tamaño de los bloques por cada celda
  
  while(h>2)										//El tipo de función de dispersión utilizado
  {
    cout << "Funciones de dispersión: " << endl;
    cout << "·Suma[0]." << endl;
    cout << "·Módulo[1]." << endl;
    cout << "·Pseudo-aleatoria[2]." << endl;
    cout << "--Eliga una opción->"; cin >> h;
    
    if(h>2) cout << "OPCION INCORRERCTA, VUELVA A INTRODUCIR." << endl;
  }
  
  while(g>3)										//El tipo de función de exploración utilizado
  {
    cout << "Funciones de exploración: " << endl;
    cout << "·Lineal[0]." << endl;
    cout << "·Cuadrática[1]." << endl;
    cout << "·Dispersión doble[2]." << endl;
    cout << "·Re-dispersión[3]." << endl;
    cout << "--Eliga una opción->"; cin >> g;
    
    if(g>2) cout << "OPCION INCORRERCTA, VUELVA A INTRODUCIR." << endl;
  }
  
  Tabla<DNI> HASH(nCeldas, nBloques, g, h);						//Instanciación de la tabla hash
  
//********************(2)********************
  
  cout << "\n******PARAMETROS DEL EXPERIMENTO******" << endl;	//Pedimos la información para el experimento.
  
  double factor;
  cout << "\nFactor de carga(entre 0 y 1)->"; cin >> factor;
  unsigned nPruebas;
  cout << "Número de pruebas->"; cin >> nPruebas;
  
//********************(3)********************
  
  unsigned N;
  N = (unsigned) (2*(factor*nCeldas*nBloques));	//le asignamos el valor al tamaño del vector
  vector<DNI> banco(N,0);			//creamos un vector de tamaño N repleto de 0
  
  srand(time(NULL));
  
  for(unsigned i=0;i<N;i++) banco[i] = rand() % 30000000+50000000;	//Creamos numeros aleatorios entre 80.000.000 y 30.000.000 y los incertamos en el vector
  
  //for(unsigned k=0;k<N/2;k++) cout << banco[k] << " "; cout << endl;
  
  
//********************(4)********************
  unsigned intento = 0;
  
  
  for(unsigned j=0;j<(N/2);j++)			//Buce para recorrer el banco de pruebas
  {
	
	while(!HASH[HASH.exploracion(banco[j], intento)].insertar(banco[j]))	//Bucle para insertar el elemento.
	{
	  intento++;								//Vamos aumentando intento
	}
	intento = 0;								//Cuando ya se ha insertado reiniciamos el contador
  }
  
  //cout << HASH;
  //cout << endl;
  
  
//********************(5)********************
  unsigned maxB=0; unsigned minB=999999999;		//Variables para almacenar numeros maximos y minimos de intentos
  vector<double> B(nPruebas);				//Vector que lamacenará el número de intentos para luego hacer la media
  double acuB = 0.0;					//Variable para almacenar la media

  srand(time(NULL));					//ponemos la semilla por medio del reloj
  
  intento=0;
  for(unsigned l=0;l<nPruebas;l++)
  {
    unsigned x = rand()%(N/2);							//creamos numeros aleatorios entre los N/2 primeros
    
    while(!HASH[HASH.exploracion(banco[x], intento)].buscar(banco[x]))		//Buscamos en el numero de celda que nos devuelve la función de exploración el valor
    {
      intento ++;								//Vamos aumentando el contador intento.
    }
    
    if(intento+1<minB) minB=intento+1;						//Vamos mirando si es el menor
    
    if(intento+1>maxB) maxB=intento+1;						//O si es el mayor
    
    B[l] = intento+1;								//se guarda ne el vector para luego hacer la media
    
    //cout << banco[x] << " se ha encontrado en " << HASH.exploracion(banco[x], intento) << " en el intento " << intento+1 << endl;
    
    intento = 0;								//le volvemos a dar el valor 0 a intento, ya que ha acabado la busqueda del elemento
  }
  
  double aux = 0.0;
  
  for(unsigned y=0;y<nPruebas;y++) aux+=B[y];					//Calculamos la media
  
  acuB = aux/nPruebas;
  
  //cout << "Valor mínimo: " << minB << "\nValor máximo: " << maxB << "\nValor medio: " << setprecision(3) << acuB << endl;
  
//********************(6)********************
  
  unsigned maxI=0; unsigned minI=999999999;			//Variables para almacenar numeros maximos y minimos de intentos
  vector<double> C(nPruebas);					//Vector que lamacenará el número de intentos para luego hacer la media
  double acuI = 0.0;						//Variable para almacenar la media
  
  srand(time(NULL));
  
  intento=0;
  for(unsigned m=0; m<nPruebas;m++)
  {
    unsigned z = rand()%((N/2)+1)+(N/2);
    
    while(!HASH[HASH.exploracion(banco[z], intento)].buscar(banco[z]))
    {
      intento ++;
      
      if(!HASH[HASH.exploracion(banco[z], intento)].full()) break;		//si no se encuentra y la celda no está llena significa que no está en la tabla
    }
    
    if(intento+1<minI) minI=intento+1;						//Vamos mirando si es el menor
    
    if(intento+1>maxI) maxI=intento+1;						//O si es el mayor
    
    C[m] = intento+1;								//se guarda ne el vector para luego hacer la media
    
    //cout << banco[x] << " se ha encontrado en " << HASH.exploracion(banco[x], intento) << " en el intento " << intento+1 << endl;
    
    intento = 0;								//le volvemos a dar el valor 0 a intento, ya que ha acabado la busqueda del elemento
    
  }
  
  
  double aux2 = 0.0;
  
  for(unsigned v=0;v<nPruebas;v++) aux2+=C[v];					//Calculamos la media
  
  acuI = aux2/nPruebas;
  
  
//********************(FIN)********************
  
  
  cout << "\n\n";
  cout << "Celdas"; cout << setw(12) << "Bloques";cout << setw(25) << "Exploración";
  cout << "Carga"; cout << setw(12) << "Pruebas" << endl;
  
  cout << setw(12) << nCeldas; cout << setw(12) << nBloques;
  
  switch(g)
  {
    case 0:
      
      cout << setw(25) << "Lineal";
      break;
      
    case 1:
      
      cout << setw(25) << "Cuadrática";
      break;
      
    case 2:
      
      cout << setw(25) << "Dispersión Dobe";
      break;
      
    case 3:
      
      cout << setw(25) << "Re-dispersión";
      break;
  }
  
  cout << setw(12) << factor; cout << setw(12) << nPruebas << endl;
  cout << "\n\n";
  
  cout << setw(40) << "Número de comparaciones" << endl;
  cout << " " <<  setw(24) << "Mínimo"; cout << setw(15) << "Medio"; cout << " " << setw(15) << "Máximo" << endl;
  cout << "Búsquedas" << setw(15) << minB; cout << setw(15) << acuB; cout << setw(15) << maxB << endl;
  cout << "Inserción" << setw(15) << minI; cout << setw(15) << acuI; cout << setw(15) << maxI << endl;
  
  cout << endl;
  
  return 0;

}