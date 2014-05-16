#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdint.h>

using namespace std;

/*

Les cartes s emmagatzemen en 1Bytes:
		 HN   LN
		 |    |
1Byte=8bits 1B = 0000 0000
		 to   to
		 FFFF FFFF
		 PAL  NUM (0-255) Tot i que nomes hauriem de fer servir valor fins a 12 (0000-1100b)
 		 (0-255) Nomes fer servir 4opc = (0000-0100b), podria ser 111b
*/

/* TODO
 * 1) Crear pila per referencia, FET
 * 2) Barrejar baralla/pila per referencia FET però falten cartes...
 * 3) Canviar variables dins funcio
 * 4) Diferents funcions per a baralles?
*/

#define HN 0xF0 //HighNeedle
#define LN 0x0F //LowNidles

#define PAL 0xF0 //Part alta
#define NUM 0x0F //Part baixa

#define COPES 0x10   // 0001
#define BASTUS 0x20  // 0010
#define ESPASES 0x40 // 0100
#define ORUS 0x80    // 1000

#define COMODI 0x0F  // 15 decimal

#define MAX_PILA 150
#define MAX_BARALLA 50

uint8_t baralla1[MAX_BARALLA]; //Unsigned int de 8
uint8_t baralla2[MAX_BARALLA];
uint8_t baralla3[MAX_BARALLA];

uint8_t pila[150];


void init_baralla(uint8_t *pila)
{
  uint8_t i;

  for(i=0;i<12;i++)    { pila[i] = COPES; } //define
  for(i=12;i<24;i++)   { pila[i] = BASTUS ; } 
  for(i=24;i<36;i++)   { pila[i] = ESPASES ; } 
  for(i=36;i<48;i++)   { pila[i] = ORUS ; } 

  for(i=0;i<48;i++)
  { 
    pila[i] += (i%12)+1;  
  } //resta div ent

  pila[48] = COMODI;
  pila[49] = COMODI;
}

void mostra_baralla(uint8_t *baralla1) //Mostra baralla1
{
  int i = 0;
  while(i<MAX_BARALLA)
  {
    cout << "[" << i << "]" <<(int)pila[i] << endl;
    i++;
  }
}

void mostra_pila(uint8_t *pila)
{
  int i = 0;
  while(i<MAX_PILA)
  {
    cout << "[" << i << "]" <<(int)pila[i] << endl;
    i++;
  }
}

void crear_pila(uint8_t *pila, uint8_t *baralla1, uint8_t *baralla2, uint8_t *baralla3)
{ //Aqui hem d ajuntar les baralles a la pila, com a adresses, 
  //De moment ho fem per valor
  
  int i = 0,z = 0;	
  
  while(i<MAX_PILA)
  {	
    if(i<=50){ 
      pila[i] = baralla1[z];
      z++;
      i++;
    }
    if( i == 50) z = 0;
    if(i>49 && i<103) 
    {
      pila[i] = baralla2[z];
      z++;
      i++;
    }
    if( i == 100) z = 0;
    if(i>=100 && i<151){ 
      pila[i] = baralla3[z];
      i++;
      z++;
    }
  }
}

void barreja_pila(uint8_t *pl)//int passades)
{
  //Reescriure, falten cartes!!!
  uint8_t carta = 0;
  int i = 0;
  int pos_extreu = 0;
  int pos_posa = 0;
	
  //Agafem una carta, on l hem agafat la posem a 0 (no hi es), ara no ho fem
  srand(time(NULL));
  while(i<MAX_PILA)
  {
      //Si declarem aixi els numeros sempre son mateixos
      //srand(time(NULL));

      //On agafem la fiquem a 0xFF

      int pos_extreu = rand()%MAX_PILA+1;
      int pos_posa = rand()%MAX_PILA+1;

      carta = pila[pos_extreu];
      pila[pos_extreu] = pila[pos_posa];
      pila[pos_posa] = carta;
      //Extrei A, guardem a cart
      //pil{pos_extreu] pila[pos_posa]
      //pila{pos_extr] 
      i++;
    }
}

int suma_pila(uint8_t *pl)
{
  int i = 0;
  int suma = 0;

  for(i=0;i<MAX_PILA;i++) suma += pl[i];

  return suma;
}

int main()
{
  init_baralla(baralla1);
  init_baralla(baralla2);
  init_baralla(baralla3);
  //mostra_baralla(baralla1);
  //mostra_baralla(baralla2);
  //mostra_baralla(baralla2);
  crear_pila(pila, baralla1, baralla2, baralla3);
  cout << suma_pila(pila) << endl;
  //mostra_pila(pila);
  barreja_pila(pila);
  //mostra_pila(pila);
  cout << suma_pila(pila) << endl;

}
//Comprovar pila fem suma
//Canviar while

//Mirar Pal -> (pila[x] & PAL)== COPES...
//Mirar num -> (pila[x] & NUM) == 1 ,2 ..12
