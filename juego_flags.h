/*
 ZMiniIF para ordenadores de 8bit
 Basado en PAWS y NGPAWS-Beta 9 (Uto/Carlos Sanchez) http://www.ngpaws.com
 (c) 2016. Written by KMBR.
 v1.0

 License
-------
 Released under the the GPL v2 or later license.
*/

/*
 ZHL. Escrita por KMBR.
 2016-2019 KMBR
 ZHL is licensed under a Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)  license.
 http://creativecommons.org/licenses/by-nc-sa/4.0/

*/

// Flags de juego 

#define fmensaje 64
#define fEsclusa 65
#define fPuerta 66
#define fCanon 66
#define fTemp 67
#define fTemp2 68
#define fTestStep 69
#define fTesting 70
#define fCasifin 71

// Define para las localidades
// Localidades
#define l_puente 1
#define l_nodo 2
#define l_esclusa 3
#define l_bodega 4
#define l_exterior 5
#define l_almacen 6
#define l_entrada 6
#define l_zonaA1 7
#define l_zonaA2 8


// Si es un objeto (por ejemplo una mochila), debemos dejar libre la localidad que corresponde con el identificador del n�mero del objeto
//#define l_mesa 34	// La mesa no es un algo que lleve el jugador pero es un objeto de tipo contenedor.


// Define para los objetos, o_
//; Objetos
#define o_Caja 0
#define o_Traje 1
#define o_Esclusa 2
#define o_Puerta 3
#define o_botonrojo 4
#define o_botonverde 5
#define o_Canon 6
#define o_Teclado 7
// -------------------------------------------------------------------------------------------
// ----------------------------------- VOCABULARIO ------------------------------------------- 
// -------------------------------------------------------------------------------------------
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
// Nombres < 20 se pueden usar como verbos
// Nombres por debajo de 50 como nombre propio, no admite lo,las...

// ------------------------------------------------
// Nombres de 21 a 255 disponibles
// ------------------------------------------------
#define n_ordenador 21      
#define n_computador    21      
#define n_ia      21      
#define n_dot     21      
#define n_navi    21      
#define n_gps     21      
#define n_galileo 21      
#define n_tom     21      
#define n_tomtom  21      
#define n_puerta   52      
#define n_boton   54      
#define n_escal   55      
#define n_plane   57      
#define n_pared   58      
#define n_suelo   59      
#define n_techo   60      
#define n_luz     61      
#define n_haz     61      
#define n_coman   63      
#define n_instr   63      
#define n_parab   64      
#define n_paquete 65
#define n_caja 65
#define n_contenedor 65
#define n_cielo 66
#define n_nave 67
#define n_airlock     132 
#define n_esclusa     132 
#define n_traje 135
#define n_pantalla    170 
#define n_crist       171 
#define n_nodo        172 
#define n_zona        173 
#define n_A1          174 
#define n_A2          175 
#define n_pasillo     176 
#define n_boveda      177 
#define n_estanteria  178 
#define n_camara      179 
#define n_canon       179 
#define n_32768       180 
#define n_teclas      181 
#define n_teclado 181
#define n_exterior    182 
#define n_fuera       182 
#define n_afuera      182 
#define n_controles   183 
#define n_etiqueta 184 
#define n_indicador 184 


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

// Adverbios
#define vaRapidamente 2
#define vaLentamente 3
#define vaSilenciosamente 4
#define vaRuidosamente 5
#define vaCuidadosamente 6
#define vaTranquilamente 7

#define pA 2
#define pDe 3
#define pDentro 4
#define pDesde 5
#define pHacia 6
#define pTras 7
#define pBajo 8
#define pCon 9
#define pPara 10
#define pPor 11
#define pExcepto 12
#define pFuera 13
#define pDelante 14
#define pEntre 15
#define pEncima 16

// Adjetivos

#define aPequeño 2
#define aGrande  3
#define aViejo   4
#define aVieja   4
#define aNuevo   5
#define aNueva   5
#define aDuro   6
#define aDura    6
#define aBlando  7
#define aCorto   8
#define aCorta   8
#define aLargo   9
#define aLarga   9
#define aAzul    10    
#define aBlanco  11    
#define aRojo    12    
#define aVerde   13    
#define aNegro   14    
#define aTermico 15    
#define aFrio    16    
#define aCaliente 16   
#define aCalor   16    
#define aAmarillo 17   
 