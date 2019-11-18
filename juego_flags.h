/*
 ZMiniIF para ordenadores de 8bit
 Basado en PAWS y NGPAWS-Beta 9 (Uto/Carlos Sanchez) http://www.ngpaws.com
 (c) 2016. Written by KMBR.
 v1.0

 License
-------
 Released under the the GPL v2 or later license.
*/

#define fherramientas 60 		// Se incrementa al buscar herrramientas

#define l_AccesoALaTrampa 	1

// Si es un objeto (por ejemplo una mochila), debemos dejar libre la localidad que corresponde con el identificador del n�mero del objeto
#define l_mesa 34	// La mesa no es un algo que lleve el jugador pero es un objeto de tipo contenedor.


// Definiciones de vocabulario
// Nombres de 1 a 20 reservados
#define nNorte  1
#define nSur 	2
#define nEste	3
#define nOeste  4
#define nNoreste 5
#define nNorOeste 6
#define nSurEste 7
#define nSurOeste 8
#define nArriba 9
#define nAbajo 10
#define nInventario 14
#define nPuntos 15
#define nTurnos 16
#define nTodo 20

// Nombres de 21 a 255 disponibles
#define n_linterna 21

// Verbos que funcionan como nombres
#define vSubir 10
#define vBajar 11
#define vEntrar 12
#define vSalir 13

// Verbos
// Some notes about vocabulary:
//    Words with same number but different type are not considered synomyms.
//    Nouns under number 20 are considered "convertible", what means they can be converted to verbs if a verb is missing (so "north" does the same than "go north").
//    Verbs undernumber 14 are considered "direction verbs", so if you have not added a specific response for a player order like "north" then ngPAWS will try to go in that direction. That doesn't happen with verbs 14 and above.
//    You can leave gaps when adding vocabulary, that is, is not required that vocabulary numbers are consecutive.

#define vCoger 20
#define vDejar 21
#define vSacar 22
#define vQuitar 22
#define vMeter 74
#define vMirar 24
#define vFin 25
#define vMirar 24
#define vExaminar 30
#define vDecir 31
#define	vHablarCon 31
#define vTirar  32
#define vLanzar 32
#define vEmpujar 33
#define vAtacar 46
#define vAgitar 49
#define vAtar 	54
#define vAbrir 64
#define vCerrar 65
#define vEncender 66
#define vApagar 67
#define vRomper 69
#define vPoner 71
#define vDesatar 98
#define vLeer 109
#define vMover 110
#define vAsustar 120
#define vMojar 121
#define vIr     90

#define o_linterna 1

#define a_rapidamente 2
#define a_lentamente 3
#define a_silenciosamente 4
#define a_ruidosamente 5
#define a_cuidadosamente 6
#define a_tranquilamente 7

#define p_a 2
#define p_de 3
#define p_dentro 4
#define p_desde 5
#define p_hacia 6
#define p_tras 7
#define p_bajo 8
#define p_con 9
#define p_para 10
#define p_por 11
#define p_excepto 12
#define p_fuera 13
#define p_delante 14
#define p_entre 15
#define p_encima 16

