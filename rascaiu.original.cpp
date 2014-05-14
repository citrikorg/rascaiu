#include <stdint.h>

#define HN 0xF0
#define LN 0x0F

#define PAL 0xF0
#define NUM 0x0F

#define COPES 0x10
#define BASTUS 0x20
#define ESPASES 0x40
#define ORUS 0x80

#define COMODI 0x0F

uint8_t baralla1[50];
uint8_t baralla2[50];
uint8_t baralla3[50];

uint8_t Pila[150];

void init_baralla(uint8_t *pila)
{
  uint8_t i;

  for(i=0;i<12;i++)     { pila[i] = COPES; }
  for(i=12;i<24;i++)   { pila[i] = BASTUS ; } 
  for(i=24;i<36;i++)   { pila[i] = ESPASES ; } 
  for(i=36;i<48;i++)   { pila[i] = ORUS ; } 

  for(i=0;i<48;i++)
  { 
    pila[i] += (i%12)+1;  
  }//Posem numero

  pila[48] = COMODI;
  pila[49] = COMODI;
}

int main(){}
