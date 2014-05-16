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
 * 1) La pila no l hauriem de definir com a fifo?
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

uint8_t jugador1[11];
uint8_t jugador2[11];
uint8_t jugador3[11];
uint8_t jugador4[11];


void init_baralla(uint8_t *pl) //Podem unificar en un recorregut
{
  uint8_t i;

  for(i=0;i<12;i++)    { pl[i] = COPES; } //define
  for(i=12;i<24;i++)   { pl[i] = BASTUS ; } 
  for(i=24;i<36;i++)   { pl[i] = ESPASES ; } 
  for(i=36;i<48;i++)   { pl[i] = ORUS ; } 

  for(i=0;i<48;i++)
  { 
    pl[i] += (i%12)+1;  
  } //resta div ent

  pl[48] = COMODI;
  pl[49] = COMODI;
}

void mostra_baralla(uint8_t *brll)
{
  int i;
  
  for(i=0;i<MAX_BARALLA;i++)
  {
    cout << "[" << i << "]" <<(int)brll[i] << endl;
  }
}

void mostra_pila(uint8_t *pl)
{
  int i;
  for(i=0;i<MAX_PILA;i++)
  {
    cout << "[" << i << "]" <<(int)pila[i] << endl;
  }
}

void crear_pila(uint8_t *py, uint8_t *br1, uint8_t *br2, uint8_t *br3)
{ //Proven de fer-ho per adresses?
  
  int i = 0,z = 0;	
  
  while(i<MAX_PILA)
  {	
    if(i<=50){ 
      py[i] = br1[z];
      z++;
      i++;
    }
    if( i == 50) z = 0;
    if(i>49 && i<103) 
    {
      py[i] = br2[z];
      z++;
      i++;
    }
    if( i == 100) z = 0;
    if(i>=100 && i<151){ 
      py[i] = br3[z];
      i++;
      z++;
    }
  }
}

void barreja_pila(uint8_t *pl, int passades)
{
  //Reescriure, falten cartes.  Cartes repetides?
  uint8_t carta;
  int i = 0;
  int pos_extreu = 0;
  int pos_posa = 0;
	
  srand(time(NULL));
  
  while(passades>0)
  {
    for(i=0;i<MAX_PILA;i++)
    {
        pos_extreu = rand()%(MAX_PILA);
        pos_posa = rand()%(MAX_PILA);

        if(pos_extreu != pos_posa)
        {
          carta = pl[pos_extreu]; 	  //Extreu A, guardem a carta
          pl[pos_extreu] = pl[pos_posa];//Posem a pos_extre pos_posa
          pl[pos_posa] = carta;		  // posem a pos_posa carta
        }
    }
    passades--;
  }
}

int suma_pila(uint8_t *pla)
{
  int i = 0;
  int suma = 0;

  for(i=0;i<MAX_PILA;i++) suma += (int)pla[i];

  return suma;
}

void repartir_pila(uint8_t *pila_partida, uint8_t *jug1, uint8_t *jug2, uint8_t *jug3, uint8_t *jug4)//, int num_jug)
{
  int ij = 0, ip = 0;
  //Repartim 40 cartes entre els jugadors de la pila, de dos ens dos
  //ij de dos a dos i ip de 8 en 8
  //REVISAR, TOT CORRECTE?
  for(ij = 0, ip = 0; ip<40; ij+=2,ip+=8)
  {
    jug1[ij] = pila_partida[ip];
    pila_partida[ip] = 0xFF;
    jug1[ij+1] = pila_partida[ip+1];
    pila_partida[ip+1] = 0xFF;
    jug2[ij] = pila_partida[ip+2];
    pila_partida[ip+2] = 0xFF;
    jug2[ij+1] = pila_partida[ip+3];
    pila_partida[ip+3] = 0xFF;
    jug3[ij] = pila_partida[ip+4];
    pila_partida[ip+4] = 0xFF;
    jug3[ij+1] = pila_partida[ip+5];
    pila_partida[ip+5] = 0xFF;
    jug4[ij] = pila_partida[ip+6];
    pila_partida[ip+6] = 0xFF;
    jug4[ij+1] = pila_partida[ip+7];
    pila_partida[ip+7] = 0xFF;
  }
}

void veure_cartes_jug(uint8_t *jugador)
{
  int cartes = 0;
  while(cartes<10)
  {
    //cout << "Carta: " << (int)jugador[cartes] << endl;
    if(jugador[cartes] & COPES) cout << "C"; //NUM!!!
    if(jugador[cartes] & BASTUS) cout << "B";
    if(jugador[cartes] & ESPASES) cout << "E";
    if(jugador[cartes] & ORUS) cout << "O";
    if(jugador[cartes] == COMODI) cout << "K"; //Falla, hem de trobar OP correcte
    cartes++;
  }
  cout << endl;
}

void ordena_cartes_jug(uint8_t *juga)
{
  //Primera passada, numeros, ordenament per seleccio https://es.wikipedia.org/wiki/Ordenamiento_por_selecci%C3%B3n
  int indexc = 0;
  for(indexc = 0; indexc<10; indexc++) //Ordenar per pal i nombre
  {

  }
}

//I

int main()
{
  init_baralla(baralla1);
  init_baralla(baralla2);
  init_baralla(baralla3);
  //mostra_baralla(baralla1);
  //mostra_baralla(baralla2);
  //mostra_baralla(baralla2);
  crear_pila(pila, baralla1, baralla2, baralla3);
  //mostra_pila(pila);
  barreja_pila(pila,10);
  //mostra_pila(pila);
  repartir_pila(pila, jugador1, jugador2, jugador3, jugador4);
  cout << "Cartes jugador1" << endl;
  veure_cartes_jug(jugador1);
  cout << "Cartes jugador2" << endl;
  veure_cartes_jug(jugador2);
  cout << "Cartes jugador3" << endl;
  veure_cartes_jug(jugador3);
  cout << "Cartes jugador4" << endl;
  veure_cartes_jug(jugador4);
  //mostra_pila(pila);
}

//Jugador, 10 cartes cadau

//Mirar Pal -> (pila[x] & PAL)== COPES...
//Mirar num -> (pila[x] & NUM) == 1 ,2 ..12
