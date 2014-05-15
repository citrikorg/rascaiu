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

/* TODO
 * 1) Crear pila per referencia
 * 2) Barrejar baralla/pila per referencia
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
  int i = 0;
  while(i<50)
  {
    cout << "[" << i << "]" <<(int)pila[i] << endl;
    i++;
  }
}

void mostra_pila(uint8_t *pila)
{
  int i = 0;
  while(i<150)
  {
    cout << "[" << i << "]" <<(int)pila[i] << endl;
    i++;
  }
}

void crear_pila(uint8_t *pila, uint8_t *baralla1, uint8_t *baralla2, uint8_t *baralla3)
{ //Aqui hem d ajuntar les baralles a la pila, com a adresses, 
  //De moment ho fem per valor
  
  int i = 0,z = 0;	
  
  while(i<150)
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

int main()
{
  init_baralla(baralla1);
  init_baralla(baralla2);
  init_baralla(baralla3);
  //mostra_baralla(baralla1);
  //mostra_baralla(baralla2);
  //mostra_baralla(baralla2);
  crear_pila(pila, baralla1, baralla2, baralla3);
  mostra_pila(pila);

}
//Mirar Pal -> (pila[x] & PAL)== COPES...
//Mirar num -> (pila[x] & NUM) == 1 ,2 ..12
