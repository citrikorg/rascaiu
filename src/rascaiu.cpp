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
 * 2) Hauriem de crear una mena d index per a cartes aparellades?
*/

#define HN 0xF0 	//HighNeedle
#define LN 0x0F 	//LowNidles

#define PAL 0xF0 	//Part alta
#define NUM 0x0F 	//Part baixa

#define COPES 0x10   	// 0001
#define BASTUS 0x20  	// 0010
#define ESPASES 0x40 	// 0100
#define ORUS 0x80    	// 1000

#define COMODI 0x0F  	// 15 decimal

#define MAX_PILA 150
#define MAX_BARALLA 50
#define MAX_JUGADOR 11

uint8_t baralla1[MAX_BARALLA];
uint8_t baralla2[MAX_BARALLA];
uint8_t baralla3[MAX_BARALLA];

uint8_t pila[MAX_PILA];

uint8_t jugador1[MAX_JUGADOR];
uint8_t jugador2[MAX_JUGADOR];
uint8_t jugador3[MAX_JUGADOR];
uint8_t jugador4[MAX_JUGADOR];


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
  uint8_t indx;
  
  for(indx=0;indx<MAX_BARALLA;indx++)
  {
    cout << "[" << indx << "]" <<(int)brll[indx] << endl;
  }
}

void mostra_pila(uint8_t *pl)
{
  uint8_t in;
  for(in=0;in<MAX_PILA;in++)
  {
    cout << "[" << in << "]" <<(int)pila[in] << endl;
  }
}

void crear_pila(uint8_t *py, uint8_t *br1, uint8_t *br2, uint8_t *br3)
{ //Proven de fer-ho per adresses?
  
  int ind = 0, znd = 0;	
  
  while(ind<MAX_PILA)
  {	
    if(ind<=50){ 
      py[ind] = br1[znd];
      znd++;
      ind++;
    }
    if( ind == 50) znd = 0;
    if(ind>49 && ind<103) 
    {
      py[ind] = br2[znd];
      znd++;
      ind++;
    }
    if( ind == 100) znd = 0;
    if(ind>=100 && ind<151){ 
      py[ind] = br3[znd];
      ind++;
      znd++;
    }
  }
}

void barreja_pila(uint8_t *pl, int passades)
{
  uint8_t carta;
  uint8_t ix = 0;
  uint8_t pos_extreu = 0;
  uint8_t pos_posa = 0;
	
  srand(time(NULL));
  
  while(passades>0)
  {
    for(ix=0;ix<MAX_PILA;ix++)
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
  uint8_t iz = 0;
  uint8_t suma = 0;

  for(iz=0;iz<MAX_PILA;iz++) suma += (int)pla[iz];

  return suma;
}

void repartir_pila(uint8_t *pila_partida, uint8_t *jug1, uint8_t *jug2, uint8_t *jug3, uint8_t *jug4)//, int num_jug)
{
  uint8_t ij = 0, ip = 0;
  //Repartim 40 cartes entre els jugadors de la pila, de dos ens dos
  //ij de dos a dos i ip de 8 en 8
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
  uint8_t cartes = 0;
  uint8_t car = 0x00;

  while(cartes<10)
  {
    if(jugador[cartes] & COPES) {
      car += (jugador[cartes] ^ COPES); //Treiem part alta, funciona? Sembla que si
      cout << (int)car << "c"; 
      car = 0x00;
    }
    if(jugador[cartes] & BASTUS){
      car += (jugador[cartes] ^ BASTUS);
      cout << (int)car << "b";
      car = 0x00;
    }
    if(jugador[cartes] & ESPASES){
      car += (jugador[cartes] ^ ESPASES);
      cout << (int)car << "e";
      car = 0x00;
    }
    if(jugador[cartes] & ORUS){
      car += (jugador[cartes] ^ ORUS);
      cout << (int)car << "o";
      car = 0x00;
    }
    if(jugador[cartes] == COMODI) cout << "K"; 
    cartes++;
  }
  cout << endl;
}

void ordena_cartes_jug(uint8_t *juga) //IA Power!
{
  //Ordenar cartes pel mateix nombre, ho podem fer per bits
  //Ordenem per numero dec de carta, ordenacio per seleccio:
  uint8_t max = 0;
  uint8_t index = 1;
  uint8_t temp = 0x00;
  uint8_t mida = 10;

  //Ordenar per numero i per pal, FET, treure NUM

  while(mida>0)
  {
    max = 0;
    for(index=1;index<mida;index++)
      if((juga[index]&NUM) > (juga[max]&NUM)) max = index; //Compara nomes numero!FET
    temp = juga[mida-1];
    juga[mida-1] = juga[max];
    juga[max] = temp;
    mida--;
  }
  //Mirar si tres o mes numeros iguals
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
  //mostra_pila(pila);
  barreja_pila(pila,10);
  //mostra_pila(pila);
  repartir_pila(pila, jugador1, jugador2, jugador3, jugador4);
  cout << "Cartes jugador1:" << endl;
  veure_cartes_jug(jugador1);
  cout << "Cartes jugador2:" << endl;
  veure_cartes_jug(jugador2);
  cout << "Cartes jugador3:" << endl;
  veure_cartes_jug(jugador3);
  cout << "Cartes jugador4:" << endl;
  veure_cartes_jug(jugador4);
  ordena_cartes_jug(jugador2);
  cout << "Cartes ordenades:" << endl;
  veure_cartes_jug(jugador2);
  //mostra_pila(pila);
}

//Mirar Pal -> (pila[x] & PAL)== COPES...
//Mirar num -> (pila[x] & NUM) == 1 ,2 ..12, No funciona per comparar??? ordenar
