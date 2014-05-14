#include <iostream>
using namespace std;
#include <stdint.h>

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


#define HN 0xF0 //HighNeedle
#define LN 0x0F //LowNidles

#define PAL 0xF0 //Part alta
#define NUM 0x0F //Part baixa

#define COPES 0x10   // 0001
#define BASTUS 0x20  // 0010
#define ESPASES 0x40 // 0100
#define ORUS 0x80    // 1000

#define COMODI 0x0F  // 15 decimal

uint8_t baralla1[50]; //Unsigned int de 8
uint8_t baralla2[50];
uint8_t baralla3[50];

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

void mostra_baralla(uint8_t *pila)
{
  uint8_t i;
  cout << pila[i];
  while(i<10)
  {
    cout << pila[i];
    i++;
  }
}

int main()
{
  uint8_t pila_main;
  init_baralla(pila_main);
  mostra_baralla(pila_main);
}
//Tros de codi

//Mirar Pal -> (pila[x] & PAL)== COPES...
//Mirar num -> (pila[x] & NUM) == 1 ,2 ..12
