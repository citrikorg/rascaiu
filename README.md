Joc de cartes rascaiu
=====================

El joc Rascaiu és un joc de cartes per a jugar entre 3 jugador fins a buit. Consta de les següents caracterísitiques:
* Es juga amb tres baralles espanyoles com a mínim.
* Cada jugador juga amb 10 cartes a la mà.
* Guanya el jugador que no arribar als cent punts (S'ha d'anotar en un paper cada ronda quants punts té cadascú).
* Les puntacions funcionen de la següent manre: Per a no puntuar les cartes has de tenir com a mínim 3 cartes lligades:
 * Cartes del mateix nombre i/o diferent pal. Per exemple tres 2 del pal que siguin.
 * Escala de pal: Tres o més cartes del mateix pal i correlatives: 1, 2 i 3 de copes o 11, 12 i 1 de bastus.
 * El comodí pot servir per lligar cartes on ens faltariu una carta: 11, 12 i Comodí (pot servir com a 1 o com a 10).
 * Escala complerta: Si el lliga tota la mà de cartes amb una escala del mateix pal es guanya la partida.

Procediment del joc
-------------------

* Es reparteixen les cartes de dues en dues a tots els jugador fins a tenir 10 cartes cadascú.
* Comença el jugador de la dreta del que ha barrejar i repartit.
* S'aixeca una carta de la baralla pel jugador que comença. Si la carta li va bé l'agafa, sinó obre una altre de la pila de cartes.
* En aquest moment el jugador té 11 cartes i n'ha de descartar una que posa sobre la taula, que ofereix al següent jugador.
* El següent jugador, si li agrada la carta, l'agafa i sinó n'agafa una de la pila de cartes.
* Així es va rotand amb el sentit contrari a les agulles del rellotge.
* Per a fer que que s'anomena Zero, un ha de tenir TOTES les cartes lligades, per exemple: 1o2b3b 3o3e3b 12e1eComodí3e. En el seu torn rescarta la carta sobrant ficant-la girada sobre el tauler i dit Zero!
* En aquest moment cada jugador ha de sumar el numero de totes les cartes que no té lligades, aquesta serà la puntuació de la ronda.
* Quan un jugador arriba a 100 queda eliminat de la partida.


Funcions
========

Inicialitza baralla, genera les cartes de la pila per referencia de mida MAX_PILA:

.. code:: C

 void init_baralla(uint8_t *pl)

Mostra per pantalla la baralla espesificada per referencia:

void mostra_baralla(uint8_t *brll)

Mostra per pantalla la pila que es passa per referencia:

void mostra_pila(uint8_t *pl)

Crea pila de MAX_PILA amb la referencia de tres baralles ja creades:

void crear_pila(uint8_t *py, uint8_t *br1, uint8_t *br2, uint8_t *br3)

Utilitza srand(time(NULL)) per a barrejar una pila passada per referencia tantes passades com s indica:

void barreja_pila(uint8_t *pl, int passades)

Suma la puntuacio d una pila:

int suma_pila(uint8_t *pla)

Reparteix la pila a 4 jugadors, es reparteix dues cartes a cadascu fins a 10:

void repartir_pila(uint8_t *pila_partida, uint8_t *jug1, uint8_t *jug2, uint8_t *jug3, uint8_t *jug4)

Mostra per pantalla les cartes d'un jugador:

void veure_cartes_jug(uint8_t *jugador)

Ordena cartes d'un jugador segons algoritme determinat (AFER):

void ordena_cartes_jug(uint8_t *juga) //IA Power!

Retorna per pantall la puntacio d'un jgador. Guardem la puntuacio dins jugador NO FUNCIONA:

void punts_ma(uint8_t *jugad) 

Xtrem Programming
=================

Definim Xtrem Programming com la programació extrema, extrema en el sentit que els programes s'han de poder executar el sistemes amb recursos limitats.
D'aquesta manera s'intenta fer un ús de la memòria (variables i funcions) per a ser utilitzats de forma de fer un mínim ús dels recurssos de l'ordinador (RAM i CPU)
S'utilitza el tipus uint8_t de C on es fa servir un byte per a la variable, és el tipus que hem trobat més petit i universal en l'entorn C/C++.

EOF
