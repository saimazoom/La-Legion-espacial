/*
 ZMiniIF para ordenadores de 8bit
 Basado en PAWS y NGPAWS-Beta 9 (Uto/Carlos Sanchez) http://www.ngpaws.com
 (c) 2016. Written by KMBR.
 v0.1

 License
-----------------------------------------------------------------------------------
 Released under the the GPL v2 or later license.
-----------------------------------------------------------------------------------

El mapa de memoria en Spectrum consiste en:

40KB de RAM disponibles 
0x - 0x
Los 16KB más altos se pueden paginar. Aquí es donde conmutamos gráficos y tablas de respuestas. Un juego pensado para 128Kb debe estar fragmentado de forma que cada bloque de código no supere 16Kb. Por cada bloque se genera un .bin que luego es paginado y cargado al comienzo. 

0x - 0x
Los 24Kb más bajos son dedicados al parser y a las definiciones del juego. El parser ocupa 16Kb, eso deja 8Kb disponibles para definiciones y tablas de procesos y respuestas. 

En un juego de 48Kb no nos preocuparemos de la paginación y todo el código puede distribuirse libremente por la memoria. 
Tampoco es un problema en Spectrum paginar para pintar un gráfico y luego paginar de nuevo para ejecutar código. 

----------------------------------
Comandos de depuración
----------------------------------
;testme : Lanza una sequencia de test pre-definida
;xlista":
;goto":
;gonear:
;flag:
;setflag:
;place:
;attr:
;sattr:
;cattr:
;help:
;where:

 Use ISO 8819-15 Encoding 

*/

//#define DEBUG       // DEBUG=1 incluye funciones y mensajes de depuración
//#define GRAPHICS    // GRAPHICS=1 Incluye gráficos
//#define SPANISH
#define ENGLISH

#include <string.h>

#include "symbol_list.h"
#include "parser_defs.h"
#include "juego_flags.h"
#include "parser.h"
#include "zx7.h"
#include ".\libgfx\libgfx.h"

// Funciones externas
//extern void scrollArriba2 (BYTE linea_inicial, BYTE num, BYTE step);
extern void clearchar (BYTE x, BYTE y, BYTE color);

unsigned char flags[255];
unsigned char *playerPrompt = "> ";
extern struct fzx_state fzx;   // active fzx state defined in libgfx

// Global variables exposed to the author for the parsing of the player input
unsigned char playerInput[MAX_INPUT_LENGTH]; // Máximo una fila
unsigned char playerWord[MAX_INPUT_WORD];
BYTE gWord_number; // Marker for current word, 1st word is 1
BYTE gChar_number; // Marker for current char, 1st char is 0

// Windows declaration 
textwin_t TextWindow;
textwin_t GraphWindow;

// ------------------------------
// Arrays defined at juego.c
// ------------------------------
extern loc_t localidades_t[];
extern img_t imagenes_t[];
extern token_t mensajes_t[];
extern cnx_t conexiones_t[];
extern obj_t objetos_t[]; // Tabla de objetos de la aventura
extern token_t nombres_t []; // Tabla de nombres...
extern token_t verbos_t []; // Tabla de verbos...
extern token_t adjetivos_t[]; // Tabla de adjetivos

// Parser FLAGS (Internal), not available for the game creator
BYTE gNUM_OBJECTS;
BYTE gNUM_LOC;
BYTE gLAST_OBJECT_NUMBER;
BYTE gNUM_IMG;
BYTE gDEBUGGER=FALSE;

// Settings
unsigned char gGRAPHICSON = TRUE;
unsigned char gSOUNDSON = TRUE;
unsigned char gINTERRUPTDISABLED = TRUE;
unsigned char gSHOWWARNINGS = TRUE;
BYTE ginEND=FALSE;
BYTE ginQUIT=FALSE;

// Status flags
unsigned char gDONE_FLAG;
unsigned char gDESCRIBE_LOCATION_FLAG;
unsigned char gIN_RESPONSE;
unsigned char gSUCCESS;

// doall control
unsigned char gDOALL_FLAG;
unsigned char gPROCESS_IN_DOALL;
unsigned char gENTRY_FOR_DOALL	= 0;
unsigned char gCURRENT_PROCESS;

// Parsing

//---------------------------------
// Tablas de parser
//---------------------------------

/*
Some notes about vocabulary:

Words with same number but different type are not considered synomyms.
Nouns under number 20 are considered "convertible", what means they can be converted to verbs if a verb is missing (so "north" does the same than "go north").
Verbs undernumber 14 are considered "direction verbs", so if you have not added a specific response for a player order like "north" then ngPAWS will try to go in that direction. That doesn't happen with verbs 14 and above.
You can leave gaps when adding vocabulary, that is, is not required that vocabulary numbers are consecutive.

*/
#define d_testme 1
#define d_xlista 2
#define d_goto 3
#define d_gonear 4
#define d_flag 5
#define d_setflag 6
#define d_move 7
#define d_attr 8
#define d_setattr 9
#define d_clearattr 10
#define d_help 11
#define d_where 12

token_t verbos_debug_t [] =
{
    {";testme", d_testme},
    {";xlista", d_xlista},
    {";goto", d_goto},
    {";gonear", d_gonear},
    {";flag",   d_flag},
    {";setflag", d_setflag},
    {";place", d_move},
    {";attr", d_attr},
    {";sattr", d_setattr},
    {";cattr", d_clearattr},
    {";help", d_help},
    {";where", d_where},
    {"",0}
};

token_t adverbios_t [] =
{
    {"rapid",    2},
    {"lenta",    3},
    {"silen",    4},
    {"ruido",    5},
    {"cuida",    6},
    {"tranq",    6},
    {"",0}
};

token_t preposiciones_t [] =
{
    {"a",             2},
    {"al",            2},
    {"de",            3},
    {"del",           3},
    {"en",            4},
    {"dentr",        4},
    {"desde",         5},
    {"hacia",         6},
    {"tras",          7},
    {"detra",        7},
    {"bajo",          8},
    {"debaj",        8},
    {"con",           9},
    {"para",          10},
    {"por",           11},
    {"excep",       12},
    {"fuera",         13},
    {"afuer",        13},
    {"delan",       14},
    {"entre",         15},
    {"encim",        16},
    {"",0}
};

token_t pronombres_t [] =
{
   	{"lo",            2},
   	{"los",           2},
   	{"selo",          2},
   	{"selos",         2},
   	{"la",            2},
   	{"las",           2},
   	{"sela",          2},
   	{"selas",         2},
   	{"le",            2},
   	{"les",           2},
    {"",0}
};

token_t conjunciones_t [] =
{
    {"y",    2},
    {"enton",2},
    {"despu",2},
    {"luego",2},
    {".",2},
    {",",2},
    {";",2},
    {"",0}
};

// Tabla de Mensajes
/* Símbolos en el juego de caracteres de tc.py (Text Compressor):
    # Sustituye las ñ y los caracteres acentuados por los nuevos símbolos
    content = [w.replace('á', '#') for w in content]
    content = [w.replace('é', '$') for w in content]
    content = [w.replace('í', '%') for w in content]
    content = [w.replace('ó', '&') for w in content]
    content = [w.replace('ú', '\'') for w in content]
    content = [w.replace('ñ', '+') for w in content]
    content = [w.replace('¿', '/') for w in content]
    content = [w.replace('¡', '<') for w in content]
*/

extern token_t mensajesSistema_t [];

//---------------------------------
// Fin de tablas de parser
//---------------------------------
void  initParser (void) // 212bytes
{
    // Menú principal
    // Inicializa el array de FLAGS
    memset(flags,0,255);

	// Inicializa variables por defecto
	flags[flocation] = 0;
	flags[fobjects_carried_count]=0;
	flags[fscore]=0;
	flags[fturns_low] = 0;
	flags[fturns_high] = 0;
	flags[fsalidas] = 1; // Se listan por defecto...
	flags[flight]=0;
	gDESCRIBE_LOCATION_FLAG=TRUE;
    ginEND=FALSE;

	// Inicializa vocabulario
	flags[fverb] = EMPTY_WORD;
	flags[fnoun1] = EMPTY_WORD;
	flags[fnoun2] = EMPTY_WORD;
	flags[fadject1] = EMPTY_WORD;
	flags[fadject2] = EMPTY_WORD;
	flags[fadverb] = EMPTY_WORD;
	flags[fprep] = EMPTY_WORD;

	// Cuenta los objetos...
	gNUM_OBJECTS=0;
	while (objetos_t[gNUM_OBJECTS].id!=0)
    {
        gNUM_OBJECTS++;
        gLAST_OBJECT_NUMBER = objetos_t[gNUM_OBJECTS].id;
        if (objetos_t[gNUM_OBJECTS].locid==LOCATION_CARRIED ||
            objetos_t[gNUM_OBJECTS].locid==LOCATION_WORN) flags[fobjects_carried_count]++; // Inicializa el contador de objetos llevados...
    }

    // Cuenta las localidades
	gNUM_LOC=0;
	while (localidades_t[gNUM_LOC].id!=0)
    {
        gNUM_LOC++;
        localidades_t[gNUM_LOC].visited=FALSE;
    }
    // Cuenta las imágenes
	gNUM_IMG=0;
	while (imagenes_t[gNUM_IMG].id!=0)
    {
        gNUM_IMG++;
    }
    // Inicializa la pantalla
    //fzx.font = ff_utz_Handpress;
    fzx.y=0;
    fzx.x=0;
}

void ParserLoop (void) // 664 bytes
{
	BYTE loc_temp;
	BYTE i;
    BYTE j;

	// Bucle principal
    while (!ginEND)
    {
		// Inicializa vocabulario al comienzo de cada turno...
		flags[fverb] = EMPTY_WORD;
		flags[fnoun1] = EMPTY_WORD;
		flags[fnoun2] = EMPTY_WORD;
		flags[fadject1] = EMPTY_WORD;
		flags[fadject2] = EMPTY_WORD;
		flags[fadverb] = EMPTY_WORD;
		flags[fprep] = EMPTY_WORD;

        // Si el jugador ha llegado y hay luz, describe localidad
		if (gDESCRIBE_LOCATION_FLAG==TRUE)
		{
		    ACCcls(INK_YELLOW|PAPER_BLACK);
            proceso1(); // Antes de describir la localidad...
            //flags[flight]=0; // REMOVE!

		    if (flags[flight]==1)
            {
                fzx.x=TextWindow.x;
                fzx.y=TextWindow.y;
                loc_temp = get_loc_pos (flags[flocation]); // La posición en el array no tiene por que coincidir con su id

                //fontStyle(TITLE);
                //writeText (localidades_t[loc_temp].name);
                //newLine();

                fontStyle(NORMAL);
                writeText (localidades_t[loc_temp].descripcion);
                newLine();
                // Proceso 1 Post, después de describir la localidad...
                proceso1_post();
                // Si está activo, lista los objetos
                if (TRUE)
                {
                  ACClistobj();
                }

                // Si está activo, lista los PNJ

                // Si están activas, describe las salidas
                if (flags[fsalidas])
                {
                    writeSysMessage (SYSMESS_EXITSLIST);
                    for (i=0;i<10;++i)
                    {
                        j = conexiones_t[loc_temp].con[i];
                        if (j<NO_EXIT && j>0)
                        {
                            writeText (" ");
                            writeText (nombres_t[i<<1].word);
                        }
                    }                    
                    newLine();
                }
                localidades_t[loc_temp].visited=TRUE;
                gDESCRIBE_LOCATION_FLAG=FALSE; // To avoid describing the location each turn
            }
            else writeSysMessage(SYSMESS_ISDARK);
		}

		// Espera el input del jugador
        fontStyle (PLAYER);
		//writeText (playerPrompt);
		getInput ();
		newLine();
		parse(); // Extrae los tokens...
        fontStyle (NORMAL);
#ifdef DEBUG
        if (gDEBUGGER==FALSE)
        {
#endif
           if (respuestas()==FALSE) // Calls reply post function if not successful
                respuestas_post();
            proceso2(); // Calls the process after the responses tables
        	// Increments the turns counter
        	incr16bit (&flags[fturns_low]); 
#ifdef DEBUG
        }
        else
            debugger();
#endif
    }
}

// ACCNextWord
// Input: Global playerInput array.
// Output: gWord_number is updated with the word number that was processed (1 first word)
//          gChar_number is updated with the character number that ws processed (1 first char)
// Description: Retrieves the next word from playerinput array.
BYTE ACCNextWord ()
{
    BYTE salir=0;
    BYTE i=0;
    BYTE caracter=0;
    //writeText ("NextWord:");
    while (salir==0 && i<25)
    {
        caracter = playerInput[gChar_number];
        playerWord[i]=caracter;
        // word terminators...
        if (caracter==' ' || caracter==13 || caracter==',' || caracter=='.' || caracter==0)
        {            
            salir = 1;      
        }
        else {
            ++i;
        }        
       gChar_number++;
    }   
    gWord_number++;
    playerWord[i] = 0; // Terminator to help C functions
    if (i==0) return FALSE; // Nothing was extracted...
        else return TRUE;
    //writeText(playerWord);    
} 

// ACCGetWord
// Input: 
//      wordnum: Requested word from the playerInput array (1 is first word)
// Description: Retrieves in playerWord array the request word. Return 1 if succeed, 0 if failure.
BYTE ACCGetWord (BYTE wordnum)
{    
    // From the beginning...
    gChar_number = 0;
    gWord_number = 0;
    ACCNextWord();
    while (gWord_number!=wordnum && playerWord[0]!=0) ACCNextWord();    
}


void parse() // 145bytes
{
// Input: Cadena de texto -> playerInput
// Output: tokens -> verbo, nombre1, nombre2, adjetivo1, adjetivo2
// Una frase tiene: sólo un verbo, un máximo de dos nombres, un máximo de dos adjetivos, un adverbio
// Inicializa los flags de vocabulario...
    flags[fverb]=EMPTY_WORD;
    flags[fnoun1]=EMPTY_WORD;
    flags[fnoun2]=EMPTY_WORD;
    flags[fadject1]=EMPTY_WORD;
    flags[fadject2]=EMPTY_WORD;
    flags[fadverb]=EMPTY_WORD;
    gDEBUGGER=FALSE;
    // Procesa palabra por palabra
    gChar_number = 0;
    gWord_number = 0; 
    playerWord[0]=255; // Initialize...
    //writeText ("Parse");

    while (playerWord[0]!=0) 
    {
        ACCNextWord();
       //  writeText (playerWord);
        //writeValue (playerWord[0]);
        #ifdef DEBUG 
            if (flags[fverb]==EMPTY_WORD && buscador(verbos_debug_t, playerWord, &flags[fverb])!=EMPTY_WORD){
                gDEBUGGER=TRUE;
            } else if (gDEBUGGER==TRUE && flags[fnoun1]==EMPTY_WORD){
                 flags[fnoun1]= atoi (playerWord);
            }  else if (gDEBUGGER==TRUE && flags[fnoun2]==EMPTY_WORD)
                {
                   flags[fnoun2]= atoi (playerWord);
                } 
        #endif

        if (flags[fverb]==EMPTY_WORD && buscador(verbos_t, playerWord, &flags[fverb])!=EMPTY_WORD){
            #ifdef DEBUG 
                if (flags[fverb]>EMPTY_WORD) 
                {
                    writeText ("V");
                    writeValue (flags[fverb]);
                }
            #endif                        
        } else if ( flags[fnoun1]==EMPTY_WORD && buscador(nombres_t, playerWord, &flags[fnoun1])!=EMPTY_WORD)
        {
            #ifdef DEBUG 
                if (flags[fverb]>EMPTY_WORD) 
                {
                    writeText ("N1_");
                    writeValue (flags[fnoun1]);
                }
            #endif                        
        } else if (flags[fnoun2]==EMPTY_WORD && buscador(nombres_t, playerWord, &flags[fnoun2])!=EMPTY_WORD)
        {
            #ifdef DEBUG 
                if (flags[fnoun2]>EMPTY_WORD) 
                {
                    writeText ("N2_");
                    writeValue (flags[fnoun2]);
                }
            #endif                        
        } else if (flags[fadject1]==EMPTY_WORD && buscador(adjetivos_t, playerWord, &flags[fadject1])!=EMPTY_WORD)
        {
            #ifdef DEBUG 
                if (flags[fadject1]>EMPTY_WORD) 
                {
                    writeText ("A1_");
                    writeValue (flags[fadject1]);
                }
            #endif                        
        } else if (flags[fadject2]==EMPTY_WORD && buscador(adjetivos_t, playerWord, &flags[fadject2])!=EMPTY_WORD)
        {
                #ifdef DEBUG 
                if (flags[fadject2]>EMPTY_WORD) 
                {
                    writeText ("A2_");
                    writeValue (flags[fadject2]);
                }
            #endif                        
        }        
 
    if (flags[fnoun1]<NUM_CONVERTIBLE_NOUNS && flags[fverb]==EMPTY_WORD)
        {
            flags[fverb] = flags[fnoun1];
            flags[fnoun1] = EMPTY_WORD;
        }
 
    }     
}
 

#ifdef DEBUG
void debugger ()
{
/* Inputs:
      flags[fverb]
      flags[fnoun1]
      flags[fnoun2]

#define d_testme 1
#define d_xlista 2
#define d_goto 3
#define d_gonear 4
#define d_flag 5
#define d_setflag 6
#define d_move 7
#define d_attr 8
#define d_setattr 9
#define d_where 10
*/

switch (flags[fverb])
    {
    case d_testme:
        break;
    case d_xlista:
        ACClistat(flags[fnoun1], 0);
        break;
    case d_goto:
        ACCgoto (flags[fnoun1]);
        break;
    case d_gonear:
        ACCgoto (objetos_t[get_obj_pos(flags[fnoun1])].locid);
        break;
    case d_flag:
        playerInput[0]=0;
        utoa(flags[flags[fnoun1]],playerInput,10);
        writeText (playerInput);
        writeText ("^");
        break;
    case d_setflag:
        flags[flags[fnoun1]]=flags[fnoun2];
        break;
    case d_move:
        ACCplace(flags[fnoun1],flags[fnoun2]);
        break;
    case d_attr:
        if (CNDozero(flags[fnoun1],flags[fnoun2]))
            writeText (">>>>> 0");
        else
            writeText (">>>>> 1");
        break;
    case d_setattr:
        ACCoset(flags[fnoun1],flags[fnoun2]);
        break;
    case d_clearattr:
        ACCoclear(flags[fnoun1], flags[fnoun2]);
        break;
    case d_where:
        playerInput[0]=0;
        writeValue(objetos_t[get_obj_pos(flags[fnoun1])].locid);
       // writeText (playerInput);
        writeText ("^");
        break;
    case d_help:
        writeText (";testme seqid ");
        writeText (";xlista locid ");
        writeText (";goto locid ");
        writeText (";gonear objid ");
        writeText (";flag flag ");
        writeText (";setflag flag num ");
        writeText (";place objid locid ");
        writeText (";attr objid attrid ");
        writeText (";sattr objid attrid ");
        writeText (";cattr objid attrid ");
        writeText (";where objid");
        writeText (";help ^");
        break;
    
    }

}
#endif

void writeValue (unsigned int value)
{
        unsigned char *valor[6];
        utoa(value,valor,10);
        writeText (&valor);
}

BYTE buscador (token_t *tabla, unsigned char *word, unsigned char *result) // 180bytes
{
    // Input: Cadena de texto
    unsigned char fin=0;
    unsigned char counter=0;
    //writeText ("Buscando:");
    //writeText (word);
    //writeText (" ");

    while (fin==0)
    {
		//writeText ("%s-%s ",tabla[counter].word,playerWord);
        if (tabla[counter].id==0) fin=1; // Fin de la tabla...
    //    writeText (tabla[counter].word);
    //    writeText (" ");
        if (strncmp(word,tabla[counter].word,MAX_WORD_LENGHT)==0)
        {
            // flags[ftemp]=tabla[counter].id;
            //writeText (" Found ");
      //      writeValue (tabla[counter].id);
            //return tabla[counter].id;
            *result = tabla[counter].id;
            return TRUE;
        }
        ++counter;
    }
    //writeText ("NOT FOUND^");
    *result = EMPTY_WORD;
    return EMPTY_WORD;
}

// --------------------------------------------
// Librería de condactos
// --------------------------------------------

void ACCdesc(void)
{
	gDESCRIBE_LOCATION_FLAG = TRUE;
	ACCbreak(); // Cancel doall loop
}

void  ACCdone(void)
{
	gDONE_FLAG = TRUE;
}

void  ACCbreak(void)
{
	gDOALL_FLAG = FALSE;
	gENTRY_FOR_DOALL = 0;
}


unsigned char CNDat(BYTE locid)
{
 if (locid == flags[flocation]) return TRUE;
    else return FALSE;
}

unsigned char CNDnotat(BYTE locid)
{
	 return (!CNDat(locid));
}

unsigned char CNDatgt(BYTE locid)
{
 if (flags[flocation] > locid) return TRUE;
    else return FALSE;
}

unsigned char CNDatlt(BYTE locid)
{
   // writeValue (locid);
   // writeValue (flags[flocation]);
    if (flags[flocation] < locid) return TRUE;
        else return FALSE;
}

BYTE  CNDpresent(BYTE objid)
{
    BYTE objnum = get_obj_pos(objid);
	BYTE locid = objetos_t[objnum].locid;
    BYTE obj2num = get_obj_pos(locid); // Si está dentro de un contenedor, el locid coincide con el objid del contenedor
    //writeText ("Present...");
    //writeValue (objid);
    //writeText (", ");
    //writeValue (locid);
	if (locid  == loc_here()) return TRUE;
	if (locid == LOCATION_WORN) return TRUE;
	if (locid == LOCATION_CARRIED) return TRUE;

	if ( (objectIsContainer(obj2num) || objectIsSupporter(obj2num)) && (CNDpresent(objetos_t[obj2num].id)) )  // Extended context and object in another object that is present
	{
		if ( objectIsSupporter(obj2num)) return TRUE;  // On supporter
		if ( objectIsContainer(obj2num) && objectIsAttr(obj2num, aOpenable) && objectIsAttr(obj2num, aOpen)) return TRUE; // In a openable & open container
		if ( objectIsContainer(obj2num) && (!objectIsAttr(obj2num, aOpenable)) ) return FALSE; // In a not openable container
	}
	return FALSE;
}

BYTE CNDabsent(BYTE objid)
{
	if (CNDpresent(objid)==TRUE) return FALSE;
        else return TRUE;
}

BYTE CNDworn(BYTE objid)
{
    if (getObjectLocation( get_obj_pos(objid)) == LOCATION_WORN) return TRUE;
    #ifdef DEBUG
        writeText ("(Not worn)");
    #endif
    return FALSE;
	// return (getObjectLocation( get_obj_pos(objid)) == LOCATION_WORN);
}

BYTE  CNDnotworn(BYTE objid)
{
    if (CNDworn(objid)==TRUE) return FALSE;
        else return TRUE;
	//return !CNDworn(objid);
}


BYTE  CNDnotcarr(BYTE objid)
{
    if (CNDcarried(objid)==TRUE) return FALSE;
        else return TRUE;
	//return !CNDcarried(objid);
}

BYTE  CNDchance(BYTE percent)
{
	 //var val = Math.floor((Math.random()*101));
	 //return (val<=percent);
}
/*
BYTE CNDzero(BYTE flagno)
{
	return (getFlag(flagno) == 0);
}

BYTE CNDnotzero(BYTE flagno)
{
	 return !CNDzero(flagno);
}

BYTE CNDeq(BYTE flagno, BYTE value)
{
	return (getFlag(flagno) == value);
}

BYTE CNDnoteq(BYTE flagno,BYTE value)
{
	return !CNDeq(flagno, value);
}

BYTE CNDgt(BYTE flagno, BYTE value)
{
	return (getFlag(flagno) > value);
}

BYTE CNDlt(BYTE flagno, BYTE value)
{
	return (getFlag(flagno) < value);
}

BYTE CNDadject1(BYTE wordno)
{
	return (getFlag(fadject1) == wordno);
}

BYTE CNDadverb(BYTE wordno)
{
	return (getFlag(fadverb) == wordno);
}

BYTE CNDadj2(BYTE adjid)
{
    return (flags[fadject2]==adjid);
}

BYTE CNDadj1(BYTE adjid)
{
    return (flags[fadject1]==adjid);
}

BYTE CNDnoun2(BYTE nounid)
{
    return (flags[fnoun2]==nounid);
}

BYTE CNDnoun1(BYTE nounid)
{
    return (flags[fnoun1]==nounid);
}

BYTE CNDverb(BYTE verbid)
{
    return (flags[fverb]==verbid);
}
*/
BYTE  CNDtimeout()
{
	// return bittest(getFlag(FLAG_TIMEOUT_SETTINGS),7);
}

BYTE CNDisat(BYTE objid, BYTE locid)
{
if (objetos_t[get_obj_pos(objid)].locid==locid)
    return TRUE;
else
    return FALSE;
}

BYTE CNDisnotat(BYTE objid, BYTE locid)
{
	return !CNDisat(objid, locid);
}

BYTE  CNDprep(BYTE wordno)
{
	return (getFlag(fprep) == wordno);
}

BYTE CNDsame(BYTE flagno1,BYTE flagno2)
{
	return (getFlag(flagno1) == getFlag(flagno2));
}

BYTE CNDnotsame(BYTE flagno1,BYTE flagno2)
{
	return (getFlag(flagno1) != getFlag(flagno2));
}

BYTE  CNDweight () // Devuelve el peso total de los objetos llevados por el jugador
{

}

void ACCinven()
{
	BYTE i;
	BYTE count = 0;
    BYTE objscount =  getObjectCountAt(LOCATION_CARRIED)+getObjectCountAt(LOCATION_WORN);

    if (!flags[fobjects_carried_count]) 
    {
        writeSysMessage (SYSMESS_CARRYNOTHING);
        return;
    }

	writeSysMessage(SYSMESS_YOUARECARRYING);

    
	for (i=0;i<gNUM_OBJECTS;++i)
	{
		if ((getObjectLocation(i)) == LOCATION_CARRIED)
		{
            writeObject(i);
            if ((objectIsAttr(i,aSupporter))  || (  (objectIsAttr(i,aTransparent))  && (objectIsAttr(i,aContainer))))  ACClistat(i, i);
            // ACCnewline();
            count++;
		}

		if (getObjectLocation(i) == LOCATION_WORN)
		{
			writeObject(i);
			writeSysMessage(SYSMESS_WORN);
			count++;
			// ACCnewline();
		}
        if (getObjectLocation(i)==LOCATION_WORN || getObjectLocation(i)==LOCATION_CARRIED)
        {
            if (count<(objscount-1)) writeSysMessage (SYSMESS_LISTSEPARATOR); // , 
            if (count==(objscount-1)) writeSysMessage (SYSMESS_LISTLASTSEPARATOR); // y
        }
	}
    
    writeSysMessage (SYSMESS_LISTEND); //.
    writeText ("^");

	gDONE_FLAG = TRUE;
}

void  ACCquit()
{
	ginQUIT = TRUE;
	writeSysMessage(SYSMESS_AREYOUSURE);
}

void  ACCend()
{
	ginEND = TRUE;
}

void  ACCok()
{
	writeSysMessage(SYSMESS_OK);
	gDONE_FLAG = TRUE;
}

void  ACCramsave()
{
    /*
	ramsave_value = getSaveGameObject();
	var savegame_object = getSaveGameObject();
	savegame =   JSON.stringify(savegame_object);
	localStorage.setItem('ngpaws_savegame_' + STR_RAMSAVE_FILENAME, savegame);
    */
}

void  ACCramload()
{
    /*
	if (ramsave_value==null)
	{
		var json_str = localStorage.getItem('ngpaws_savegame_' + STR_RAMSAVE_FILENAME);
		if (json_str)
		{
			savegame_object = JSON.parse(json_str.trim());
			restoreSaveGameObject(savegame_object);
			ACCdesc();
			focusInput();
			return;
		}
		else
		{
			writeText (STR_RAMLOAD_ERROR);
			gDONE_FLAG = true;
			return;
		}
	}
	restoreSaveGameObject(ramsave_value);
	ACCdesc();
	*/
}

void  ACCsave()
{
    // We just need to store the FLAGS array in a file

    /*
	var savegame_object = getSaveGameObject();
	savegame =   JSON.stringify(savegame_object);
	filename = prompt(getSysMessageText(SYSMESS_SAVEFILE),'').toUpperCase();;
	localStorage.setItem('ngpaws_savegame_' + filename.toUpperCase(), savegame);
	ACCok();
	*/
}

void  ACCload()
{
    // Restore the FLAGS array in memory 
    // Continue with the game...
    /*
	var json_str;
	filename = prompt(getSysMessageText(SYSMESS_LOADFILE),'').toUpperCase();;
	json_str = localStorage.getItem('ngpaws_savegame_' + filename.toUpperCase());
	if (json_str)
	{
		savegame_object = JSON.parse(json_str.trim());
		restoreSaveGameObject(savegame_object);
	}
	else
	{
		writeSysMessage(SYSMESS_FILENOTFOUND);
		gDONE_FLAG = true; return;
	}
	ACCdesc();
	focusInput();
    */
}

void  ACCturns()
{
    unsigned int turns = (unsigned int)(flags[fturns_high]*256)+flags[fturns_low];
	writeSysMessage(SYSMESS_TURNS_START);
    writeValue(turns);
	writeSysMessage(SYSMESS_TURNS_CONTINUE);
	if (turns != 1) writeSysMessage(SYSMESS_TURNS_PLURAL);
	writeSysMessage(SYSMESS_TURNS_END);
}

void  ACCscore()
{
    unsigned int score = flags[fscore];
	writeSysMessage(SYSMESS_SCORE_START);
    writeValue(flags[fscore]);
  	writeSysMessage(SYSMESS_SCORE_END);
    if (score != 1) writeSysMessage(SYSMESS_TURNS_PLURAL);
	writeSysMessage(SYSMESS_TURNS_END);
}

void  ACCcls()
{
	clear_screen (INK_YELLOW|PAPER_BLACK);
	fzx.x = TextWindow.x;
	fzx.y = TextWindow.y;
}

void  ACCautog()
{
    BYTE objid;
    //  flags[ftemp] = ACCgetReferredObject(flags[fnoun1]);
    objid = ACCgetReferredObject(flags[fnoun1]);
    if (objid != EMPTY_OBJECT)
    {
        if (CNDonotzero(objid, aScenery) || CNDonotzero(objid, aStatic))
            {
                //writeText("(");
                //writeObject (get_obj_pos(objid));
                //writeText(")");
                writeSysMessage (SYSMESS_YOUCANNOTTAKE);
                DONE;
            }
        ACCget (objid);
        return TRUE;
    }

	writeSysMessage(SYSMESS_CANTSEETHAT);
	ACCnewline();
	ACCdone();
}


void ACCautod()
{
    BYTE objno;
	objno =findMatchingObject(LOCATION_CARRIED);
	if (objno != EMPTY_OBJECT) { ACCdrop(objetos_t[objno].id); return; };

	objno =findMatchingObject(LOCATION_WORN);
	if (objno != EMPTY_OBJECT) { ACCdrop(objetos_t[objno].id); return; };

	//objno =findMatchingObject(get_loc_pos(loc_here()));
	//if (objno != EMPTY_OBJECT) { ACCdrop(objetos_t[objno].id); return; };
	writeSysMessage(SYSMESS_YOUDONTHAVETHAT);
	ACCnewline();
	ACCdone();
}


void  ACCpause(BYTE value)
{
 /*
 if (value == 0) value = 256;
 pauseRemainingTime = Math.floor(value /50 * 1000);
 inPause = true;
 $('.block_layer').css('display','none');
 $('.block_text').html('');
 $('.block_graphics').html('');
 $('.block_layer').css('background','transparent');
 $('.block_layer').css('display','block');
 */
}

void  ACCgoto(BYTE locid)
{
 	flags[flocation]=locid; // Flags de usuario trabajan siempre con ID
 	gDESCRIBE_LOCATION_FLAG=TRUE; // Triggers the location description
}


void ACCclearexit(BYTE locid, BYTE value)
{
	if ((value > NUM_CONNECTION_VERBS) || (value< 0 )) return;
	setConnection(locid,value, NO_EXIT);
}

BYTE ACCgetexit(BYTE locid, BYTE value)
{
    BYTE locno;
    if (value < NUM_CONNECTION_VERBS)
    {
        locno =  getConnection(get_loc_pos(locid),value);
        if (locno>0 && locno<NO_EXIT) return localidades_t[locno].id;
    }
    return NO_EXIT;
}

BYTE ACCsetexit(BYTE loc_orig, BYTE value, BYTE loc_dest)
{
	if (value < NUM_CONNECTION_VERBS) setConnection(get_loc_pos(loc_orig), value, get_loc_pos(loc_dest));
}

// 
void  ACCmessage(BYTE mesid)
{
	writeMessage(get_msg_pos(mesid));
	ACCnewline();
}

BYTE trytoGet(BYTE objno)  // auxiliaty function for ACCget
{
    BYTE weight;
    if (flags[fobjects_carried_count] >= flags[fmaxobjects_carried])
    {
        writeSysMessage(SYSMESS_CANTCARRYANYMORE);
        writeText("^");
        return FALSE;
    }

    weight = getLocationObjectsWeight( get_loc_pos (objetos_t[objno].id)  ); // El ID del contenedor se usa como ID de localidad
	weight += getObjectWeight(objno);
	weight +=  getLocationObjectsWeight(LOCATION_CARRIED);
	weight +=  getLocationObjectsWeight(LOCATION_WORN);
	if (weight > flags[fmaxweight_carried])
	{
		writeSysMessage(SYSMESS_WEIGHSTOOMUCH);
		writeText ("^");
		return FALSE;
	}

    setObjectLocation(objno, LOCATION_CARRIED);
    flags[fobjects_carried_count]++;            // Incrementa el contador de objetos llevados
    writeSysMessage (SYSMESS_YOUTAKEOBJECT);
    writeObject(objno);
    ACCnewline();
    return TRUE;
}

BYTE ACCget(BYTE objid)
 {

    BYTE locpos = getObjectLocation(get_obj_pos(objid));
    BYTE objpos = get_obj_pos (objid);

    if (locpos==LOCATION_CARRIED || locpos==LOCATION_WORN)
    {
		writeSysMessage(SYSMESS_YOUALREADYHAVEOBJECT);
		writeObject(objpos);
        ACCnewline();
        return TRUE;
    }

    if (locpos==get_loc_pos(loc_here()))
    {
        if (trytoGet(objpos)) return TRUE;
            else return FALSE;
    }

    // If it's not here, carried or worn but is present, thus you can get objects from present containers supporters
    if (objid!=EMPTY_OBJECT && CNDpresent(objid))
        {
        if (trytoGet(objpos)) return TRUE;
            else return FALSE;
        }
        else
        {
            writeText ("ACCget");
            writeSysMessage(SYSMESS_CANTSEETHAT);
            writeObject(objpos);
            ACCnewline();
            return FALSE;
        }
    return FALSE;
    }

BYTE ACCdrop(BYTE objid)
{
    // BYTE success = false;
	//setFlag(FLAG_REFERRED_OBJECT, objno);
	//setReferredObject(objno);
    BYTE objpos;
    objpos = get_obj_pos(objid);
	if (objetos_t[objpos].locid == LOCATION_WORN)
    {
			writeSysMessage(SYSMESS_YOUAREALREADYWEARINGTHAT);
            //            writeObject(objpos);
			ACCnewline();
			ACCdone();
			return FALSE;
    }

    if (objetos_t[objpos].locid == loc_here())
    {
			writeSysMessage(SYSMESS_YOUDONTHAVEOBJECT);
			//writeObject(objpos);
            ACCnewline();
			//ACCdone();
			return FALSE;

    }
    if (objetos_t[objpos].locid == LOCATION_CARRIED)
    {
        	setObjectLocation(objpos, get_loc_pos(loc_here()));
        	flags[fobjects_carried_count]--;
			writeSysMessage(SYSMESS_YOUDROPOBJECT);
			writeObject(objpos);
			writeText(". ^");
			ACCdone();
			return TRUE;
	}
    return FALSE;
}



void  ACCdestroy(BYTE objid)
{
	setObjectLocation(get_loc_pos(objid), LOCATION_NONCREATED);
}


void  ACCcreate(BYTE objid)
{
    //writeText ("ACCCREATE: %u",objno);
	setObjectLocation( get_obj_pos(objid), get_loc_pos(loc_here()) );
}


void ACCswap(BYTE objid1, BYTE objid2)
{
	BYTE locno1 = getObjectLocation (get_loc_pos(objid1));
	BYTE locno2 = getObjectLocation (get_loc_pos(objid2));
	ACCplace (objid1,locno2);
	ACCplace (objid2,locno1);
	//setReferredObject(objno2);
}

// Place the object OBJID in the location LOCID. 
// Input: OBJID (1-255)
//        LOCID (1-255)
// Output: None
void ACCplace(BYTE objid, BYTE locid) 
{
    if (locid==LOCATION_CARRIED || locid==LOCATION_WORN || locid == LOCATION_NONCREATED || locid == LOCATION_HERE)
    {
        setObjectLocation(get_obj_pos(objid), locid);
    } else setObjectLocation (get_obj_pos(objid), get_loc_pos(locid));
}

//void ACCset(BYTE flagno)
//{
//	setFlag(flagno, SET_VALUE);
//}

//void ACCclear(BYTE flagno)
//{
//	setFlag(flagno,0);
//}

//void ACClet(BYTE flagno,BYTE value)
//{
//	setFlag(flagno,value);
//}

void ACCnewline()
{
    newLine();
}

// ACCwriteText
// Input: Flag number indicating the message to be printed
// Outpput: Outputs message into screen.
// Description: Prints the message pointed by flagno.

void  ACCwriteText(BYTE flagno)
{
   writeMessage(get_msg_pos(flags[flagno]));
}

void ACCwrite (unsigned char *texto)
{
    writeText (texto);
}

void ACCwriteln (unsigned char *texto)
{
    writeText (texto);
    newLine();
}


void  ACCsysmess(BYTE sysno)
{
	writeSysMessage(sysno);
}

void ACCcopyof(BYTE objno,BYTE flagno)
{
	// setFlag(flagno, getObjectLocation(objno))
}

void ACCcopyoo(BYTE objno1, BYTE objno2)
{
	//setObjectLocation(objno2,getObjectLocation(objno1));
	//setReferredObject(objno2);
}

void ACCcopyfo(BYTE flagno,BYTE objno)
{
	// setObjectLocation(objno, getFlag(flagno));
}

void ACCcopyff(BYTE flagno1, BYTE flagno2)
{
	// setFlag(flagno2, getFlag(flagno1));
}

void ACClistat(BYTE locid, BYTE container_id)   // objno is a container/supporter id, used to list contents of objects
{
  BYTE listingContainer = FALSE;
  BYTE i=0;
  BYTE j=0;
  BYTE locno = get_loc_pos(locid);
  BYTE objscount =  getObjectCountAt( locno);
  BYTE concealed_objcount = getObjectCountAtWithAttr(locno, aConcealed);
  BYTE scenery_objcount = getObjectCountAtWithAttr(locno, aScenery);
  BYTE progresscount=0;

  objscount = objscount - concealed_objcount - scenery_objcount;
  if (container_id > 0) listingContainer = TRUE;

  // writeText ("Num Obj: %u",objscount);

  for (i=0;i<gNUM_OBJECTS;++i)
  {
    //j = objetos_t[i].id;
  	if (objetos_t[i].locid == locid)
    {
  		if  (!objectIsNPC(i) && !objectIsAttr(i,aConcealed) && !objectIsAttr(i,aScenery)) // if not an NPC and object is not concealed nor scenery
  		  {
            writeObject (i);
            progresscount++;
            // Formato de lista contínua
            if (objscount>1 && (progresscount <= objscount - 2))
            {
                //writeText("  ");
                writeSysMessage(SYSMESS_LISTSEPARATOR);
            }
  			if (progresscount == objscount - 1) writeSysMessage(SYSMESS_LISTLASTSEPARATOR);
  			if (!listingContainer && progresscount == objscount )
            {
                writeSysMessage(SYSMESS_LISTEND);
                //ACCnewline();
            }
  		  }
    }
  }

}


void  ACClistnpc(BYTE locno)
{
/*
  var npccount =  getNPCCountAt(locno);
  setFlag(FLAG_OBJECT_LIST_FORMAT, bitclear(getFlag(FLAG_OBJECT_LIST_FORMAT),5));
  if (!npccount) return;
  setFlag(FLAG_OBJECT_LIST_FORMAT, bitset(getFlag(FLAG_OBJECT_LIST_FORMAT),5));
  continouslisting = bittest(getFlag(FLAG_OBJECT_LIST_FORMAT),6);
  writeSysMessage(SYSMESS_NPCLISTSTART);
  if (!continouslisting) ACCnewline();
  if (npccount==1)  writeSysMessage(SYSMESS_NPCLISTCONTINUE); else writeSysMessage(SYSMESS_NPCLISTCONTINUE_PLURAL);
  var progresscount = 0;
  var i;
  for (i=0;i<gNUM_OBJECTS;i++)
  {
  	if (getObjectLocation(i) == locno)
  		if ( (objectIsNPC(i)) && (!objectIsAttr(i,ATTR_CONCEALED)) ) // only NPCs not concealed
  		  {
  		     writeText(getObjectText(i));
  		     progresscount++
  		     if (continouslisting)
  		     {
		  	 	if (progresscount <= npccount - 2) writeSysMessage(SYSMESS_LISTSEPARATOR);
  			 	if (progresscount == npccount - 1) writeSysMessage(SYSMESS_LISTLASTSEPARATOR);
  			 	if (progresscount == npccount ) writeSysMessage(SYSMESS_LISTEND);
  			 } else ACCnewline();
  		  };
  }
  */
}


void  ACClistobj()
{
  BYTE locno = get_loc_pos(flags[flocation]);
  BYTE objscount =  getObjectCountAt(locno);
  BYTE concealed_objcount = getObjectCountAtWithAttr(locno, aConcealed);
  BYTE scenery_objcount = getObjectCountAtWithAttr(locno, aScenery);
  objscount = objscount - concealed_objcount - scenery_objcount;
  if (objscount)
  {
	  writeSysMessage(SYSMESS_YOUCANSEE);
      ACClistat(flags[flocation],0);
      newLine();
  }
}

BYTE ACCobjat (BYTE locid)
{
  return getObjectCountAt(get_loc_pos(locid));
}

/*
void ACCprocess(BYTE procno)
{

	if (procno > last_process)
	{
		writeText(STR_WRONG_PROCESS);
		ACCnewtext();
		ACCdone();
	}
	callProcess(procno);

}
*/

void  ACCmes(BYTE mesid)
{
   	writeMessage(get_msg_pos(mesid));
}

/*
void ACCmode(BYTE mode)
{
	// setFlag(FLAG_MODE, mode);
}

void ACCtime(BYTE length, BYTE settings)
{
	//setFlag(FLAG_TIMEOUT_LENGTH, length);
	//setFlag(FLAG_TIMEOUT_SETTINGS, settings);
}
*/
/*
BYTE ACCdoall(BYTE locno)
{
    /*
	doall_flag = true;
	if (locno == LOCATION_HERE) locno = loc_here();
	// Each object will be considered for doall loop if is at locno and it's not the object specified by the NOUN2/ADJECT2 pair and it's not a NPC (or setting to consider NPCs as objects is set)
	setFlag(FLAG_DOALL_LOC, locno);
	var doall_obj;
	doall_loop:
	for (doall_obj=0;(doall_obj<gNUM_OBJECTS) && (doall_flag);doall_obj++)
	{
		if (getObjectLocation(doall_obj) == locno)
			if ((!objectIsNPC(doall_obj)) || (!bittest(getFlag(FLAG_PARSER_SETTINGS),3)))
 			 if (!objectIsAttr(doall_obj, ATTR_CONCEALED))
 			  if (!objectIsAttr(doall_obj, ATTR_SCENERY))
				if (!( (objectsNoun[doall_obj]==getFlag(FLAG_NOUN2))  &&    ((objectsAdjective[doall_obj]==getFlag(FLAG_ADJECT2)) || (objectsAdjective[doall_obj]==EMPTY_WORD)) ) ) // implements "TAKE ALL EXCEPT BIG SWORD"
				{
					setFlag(FLAG_NOUN1, objectsNoun[doall_obj]);
					setFlag(FLAG_ADJECT1, objectsAdjective[doall_obj]);
					setReferredObject(doall_obj);
					callProcess(process_in_doall);
					if (gDESCRIBE_LOCATION_FLAG)
						{
							doall_flag = false;
							entry_for_doall = '';
							break doall_loop;
						}
				}
	}
	doall_flag = false;
	entry_for_doall = '';
	if (gDESCRIBE_LOCATION_FLAG) descriptionLoop();

}
*/

void ACCweigh(BYTE objno, BYTE flagno)
{
	BYTE weight = getObjectWeight(objno);
	setFlag(flagno, weight);
}


void  ACCability(BYTE maxObjectsCarried, BYTE maxWeightCarried)
{
    flags[fmaxobjects_carried] = maxObjectsCarried;
    flags[fmaxweight_carried] = maxWeightCarried;
	//setFlag(FLAG_MAXOBJECTS_CARRIED, maxObjectsCarried);
	//setFlag(FLAG_MAXWEIGHT_CARRIED, maxWeightCarried);
}

void  ACCweight(BYTE flagno)
{

	BYTE weight_carried = getLocationObjectsWeight(LOCATION_CARRIED);
	BYTE weight_worn = getLocationObjectsWeight(LOCATION_WORN);
	BYTE total_weight = weight_worn + weight_carried;

	flags[flagno] = total_weight;
}


void  ACCrandom(BYTE flagno)
{
	// setFlag(flagno, 1 + Math.floor((Math.random()*100)));
}

void  ACCwhato()
{
	//var whatofound = getReferredObject();
	//if (whatofound != EMPTY_OBJECT) setReferredObject(whatofound);
}

void  ACCputo(BYTE locno)
{
	// setObjectLocation(getFlag(FLAG_REFERRED_OBJECT), locno);
}

void  ACCnotdone()
{
	gDONE_FLAG = TRUE;
}

void  ACCautop() // Auto putin, PUT OBJID INTO OBJ2ID
{
    /*
    BYTE objno;

    objno = findMatchingObject (LOCATION_CARRIED);
    if (objno != EMPTY_OBJECT)
    {
        ACCputin(objid, obj2id);
        return TRUE;
    }

    objno = findMatchingObject (LOCATION_WORN);
    if (objno != EMPTY_OBJECT)
    {
        ACCputin(objid, obj2id);
        return TRUE;
    }
    objno = findMatchingObject (loc_here());
    if (objno != EMPTY_OBJECT)
    {
        ACCputin(objid, obj2id);
        return TRUE;
    }

	writeSysMessage(SYSMESS_CANTDOTHAT);
	ACCnewline();
	ACCdone();
	*/
}


void  ACCautot() // Auto take out...
{
    /*
    BYTE objno;
    objno = findMatchingObject (get_loc_pos(obj2id));
    if (objno != EMPTY_OBJECT)
    {
        ACCtakeout(objid, obj2id);
        return TRUE;
    }

    objno = findMatchingObject (LOCATION_CARRIED);
    if (objno != EMPTY_OBJECT)
    {
        ACCtakeout(objid, obj2id);
        return TRUE;
    }

    objno = findMatchingObject (LOCATION_WORN);
    if (objno != EMPTY_OBJECT)
    {
        ACCtakeout(objid, obj2id);
        return TRUE;
    }
    objno = findMatchingObject (loc_here());
    if (objno != EMPTY_OBJECT)
    {
        ACCtakeout(objid, obj2id);
        return TRUE;
    }

	writeSysMessage(SYSMESS_CANTDOTHAT);
	ACCnewline();
	ACCdone();
	*/
}

BYTE CNDmove(BYTE flagno)
{

	BYTE locno = flags[flagno];
	BYTE dirno = flags[fverb];
/*
	var destination = getConnection( locno,  dirno);
	if (destination != -1)
		{
			 flags[flagno]=destination;
			 return TRUE;
		}
*/
	return FALSE;
}

// ACCpicture
// Input: Picture id declared in imagenes_t structure
// Output: Direct decompress using zx7 to screen.
// Pagination is disabled in 48K for Page 0.

void  ACCpicture(BYTE picid)
{
	BYTE picpos;
	picpos = get_img_pos(picid);
    if (imagenes_t[picpos].page!=0) setRAMPage (imagenes_t[picpos].page);
    dzx7AgileRCS(imagenes_t[picpos].paddr, ((unsigned char*) 16384));
    //dzx7SmartRCS(imagenes_t[picpos].paddr, ((unsigned char*) 16384));
    if (imagenes_t[picpos].page!=0) setRAMBack();
}

void  ACCgraphic(BYTE option)
{
	gGRAPHICSON = (option==1);
	if (!gGRAPHICSON) hideGraphicsWindow();
}

void  ACCbeep(BYTE sfxno, BYTE channelno, BYTE times)
{
    /*
	if ((channelno <1) || (channelno >MAX_CHANNELS)) return;  //SFX channels from 1 to MAX_CHANNELS, channel 0 is for location music and can't be used here
	sfxplay(sfxno, channelno, times, 'play');
    */
}

void  ACCsound(BYTE value)
{
    /*
	soundsON = (value==1);
	if (!soundsON) sfxstopall();
    */
}

BYTE CNDozero(BYTE objid, unsigned char attrno)
{
    
    if (objectIsAttr(get_obj_pos(objid), attrno)) return FALSE;
    return TRUE;
    }

BYTE CNDonotzero(BYTE objid, unsigned char attrno)
{
 if (CNDozero(objid,attrno)==TRUE) return FALSE;
    else return TRUE;
}

void ACCoset(BYTE objid, BYTE attrno)
{
    objetos_t[get_obj_pos(objid)].atributos|=(unsigned long int)1<<(unsigned long int)attrno;
}

void ACCoclear(BYTE objid, BYTE attrno)
{
 unsigned long int mask=0xFFFFFFFF;
 mask^=(unsigned long int)1<<(unsigned long int)attrno;
 objetos_t[get_obj_pos(objid)].atributos&=mask;
}

BYTE CNDislight()
{
	//if (!isDarkHere()) return TRUE;
	//return lightObjectsPresent();
}

BYTE  CNDisnotlight()
{
	return ! CNDislight();
}

void  ACCversion()
{
	// writeText(STR_RUNTIME_VERSION);
}

void  ACCrestart()
{
  // process_restart = true;
}


void  ACCtranscript()
{
	//$('#transcript_area').html(transcript);
	//$('.transcript_layer').show();
	//inTranscript = true;
}

void  ACCanykey()
{
	writeSysMessage(SYSMESS_PRESSANYKEY);
    waitForAnyKey();
}

void  ACCgetkey(BYTE flagno)
{
	//getkey_return_flag = flagno;
	//inGetkey = TRUE;
}

BYTE CNDobjfound(BYTE attrno, BYTE locid)
{
/*
	for (var i=0;i<gNUM_OBJECTS;i++)
		if ((getObjectLocation(i) == locno) && (CNDonotzero(i,attrno))) {setFlag(FLAG_ESCAPE, i); return true; }
	setFlag(FLAG_ESCAPE, EMPTY_OBJECT);
	return false;
	*/
}

BYTE CNDobjnotfound(BYTE attrno, BYTE locid)
{
	/*
	for (var i=0;i<gNUM_OBJECTS;i++)
		if ((getObjectLocation(i) == locno) && (CNDonotzero(i,attrno))) {setFlag(FLAG_ESCAPE, i); return false; }

	setFlag(FLAG_ESCAPE, EMPTY_OBJECT);

	return true;
	*/
}

BYTE  CNDcarried(BYTE objid)
{
	if (getObjectLocation(get_obj_pos(objid)) == LOCATION_WORN) return TRUE;
	if (getObjectLocation(get_obj_pos(objid)) == LOCATION_CARRIED) return TRUE;
#ifdef DEBUG
    writeText ("(Not carried)");
#endif
	return FALSE;
}

void ACConeg(BYTE objid, BYTE attrno)
{
	// objetos_t[get_obj_pos(objid)].atributos^=attrno;
}


// -------------------------------------
// Funciones auxiliares del parser
// -------------------------------------
BYTE findMatchingObject(BYTE locno)
{
    BYTE i,j=0;

	for (i=0;i<gNUM_OBJECTS;++i) // Recorre el array de objetos
    {
        if (locno==-1 || getObjectLocation(i) == locno)
        {
		 if (objetos_t[i].vnombre == flags[fnoun1] &&
            (objetos_t[i].vadj1 == EMPTY_WORD || objetos_t[i].vadj1 ==flags[fadject1]))
            {
                return i;
            }
        }
    }
	return EMPTY_OBJECT;
}

BYTE  isAccesibleContainer(BYTE objno)
{
	if (objectIsSupporter(objno)) return TRUE;   // supporter
	if ( objectIsContainer(objno) && !objectIsAttr(objno, aOpenable) ) return TRUE;  // No openable container
	if ( objectIsContainer(objno) && objectIsAttr(objno, aOpenable) && objectIsAttr(objno, aOpen)  )  return TRUE;  // No openable & open container
	return FALSE;
}

BYTE ACCgetReferredObject(BYTE num_noun)
{
	BYTE objectfound = EMPTY_OBJECT;
	BYTE temp = flags[fnoun1];
    BYTE i;

    if (num_noun==EMPTY_WORD) return objectfound;

	flags[fnoun1] = num_noun; // Para que funcione findMatchingObject...

    // writeText ("RO ");
    //writeValue (num_noun);

    objectfound = findMatchingObject(LOCATION_CARRIED);
    if (objectfound != EMPTY_OBJECT)
        {
          //  writeText ("OC");
            flags[fnoun1] = temp;
            return objetos_t[objectfound].id;
        }

    objectfound = findMatchingObject(LOCATION_WORN);
    if (objectfound != EMPTY_OBJECT)
        {
          // writeText ("OW");
            flags[fnoun1] = temp;
            return objetos_t[objectfound].id;
        }

    objectfound = findMatchingObject(get_loc_pos(loc_here()));
    if (objectfound != EMPTY_OBJECT)
        {
         //   writeText ("OH");
            flags[fnoun1] = temp;
            return objetos_t[objectfound].id;
        }

   	for (i=0; i<gNUM_OBJECTS;++i) // Try to find it in present containers/supporters
	{
		if (CNDpresent(objetos_t[i].id) && (isAccesibleContainer(i) || objectIsAttr(i, aSupporter)) )  // If there is another object present that is an accesible container or a supporter
		{
			objectfound =findMatchingObject(get_loc_pos(objetos_t[i].id)); // Busca un objeto en la localidad que encaje con el input del jugador. El id del contenedor es el id de la loc.
			if (objectfound != EMPTY_OBJECT)
                {
                flags[fnoun1]=temp;
                return objetos_t[objectfound].id;
                }
		}
	}
	return objectfound;
}

/*
function getReferredObject()
{
	var objectfound = EMPTY_OBJECT;
	refobject_search:
	{
		object_id = findMatchingObject(LOCATION_CARRIED);
		if (object_id != EMPTY_OBJECT)	{objectfound = object_id; break refobject_search;}

		object_id = findMatchingObject(LOCATION_WORN);
		if (object_id != EMPTY_OBJECT)	{objectfound = object_id; break refobject_search;}

		object_id = findMatchingObject(loc_here());
		if (object_id != EMPTY_OBJECT)	{objectfound = object_id; break refobject_search;}

		object_id = findMatchingObject(-1);
		if (object_id != EMPTY_OBJECT)	{objectfound = object_id; break refobject_search;}
	}
	return objectfound;
}
*/
/*
// Sets all flags associated to  referred object by current LS
function setReferredObject(objno)
{
	if (objno == EMPTY_OBJECT)
	{
		setFlag(FLAG_REFERRED_OBJECT, EMPTY_OBJECT);
		setFlag(FLAG_REFERRED_OBJECT_LOCATION, LOCATION_NONCREATED);
		setFlag(FLAG_REFERRED_OBJECT_WEIGHT, 0);
		setFlag(FLAG_REFERRED_OBJECT_LOW_ATTRIBUTES, 0);
		setFlag(FLAG_REFERRED_OBJECT_HIGH_ATTRIBUTES, 0);
		return;
	}
	setFlag(FLAG_REFERRED_OBJECT, objno);
	setFlag(FLAG_REFERRED_OBJECT_LOCATION, getObjectLocation(objno));
	setFlag(FLAG_REFERRED_OBJECT_WEIGHT, getObjectWeight(objno));
	setFlag(FLAG_REFERRED_OBJECT_LOW_ATTRIBUTES, getObjectLowAttributes(objno));
	setFlag(FLAG_REFERRED_OBJECT_HIGH_ATTRIBUTES, getObjectHighAttributes(objno));

}

*/

BYTE  getFlag (BYTE flagno)
{
    return flags[flagno];
}

void setFlag (BYTE flagno, BYTE valor)
{
    flags[flagno]=valor;
}

void dropall()
{
	// Done in two different loops cause PAW did it like that, just a question of retro compatibility
	BYTE i;
	for (i=0;i<gNUM_OBJECTS;++i)	if (getObjectLocation(i) == LOCATION_CARRIED)setObjectLocation(i, flags[flocation]);
	for (i=0;i<gNUM_OBJECTS;++i)	if (getObjectLocation(i) == LOCATION_WORN)setObjectLocation(i, flags[flocation]);
}

void  done()
{
	gDONE_FLAG = TRUE;
}

void  desc()
{
	gDESCRIBE_LOCATION_FLAG = TRUE;
}

// loc_here
// Returns the current location ID
BYTE  loc_here ()
{
    return flags[flocation]; // flocation contiene el ID de la localidad
}

// Searchs the Loc ID in the localidades_t array and returns the position of the element 
// Input: Location ID
// Output: Position within the location array

BYTE get_loc_pos (BYTE locid)
{
	BYTE i=0;
	while (i<gNUM_LOC)
	{
		if (localidades_t[i].id==locid) return i;
        i++;
	}
	return FALSE;
}
// Input: Object ID 
// Output: Position within the object array 
BYTE get_obj_pos (BYTE objid)
{
	BYTE i=0;
	if (objid==EMPTY_OBJECT) return EMPTY_OBJECT;
	while (i<gNUM_OBJECTS)
	{
		if (objetos_t[i].id==objid) return i;
        i++;
	}
	return FALSE;
}
BYTE get_img_pos (BYTE imgid)
{
	BYTE i=0;
	while (i<gNUM_IMG)
	{
		if (imagenes_t[i].id==imgid) return i;
        i++;
	}
	return FALSE;
}

BYTE get_msg_pos (BYTE mesid)
{
    return get_table_pos (mensajes_t, mesid);
}

BYTE  get_table_pos (token_t *tabla, BYTE noun_id)
{
    unsigned char counter=0;
    while (tabla[counter].id!=0)
    {
        if (tabla[counter].id==noun_id) return counter;
        counter++;
    }
    return FALSE;
}

BYTE  getObjectLocation (BYTE objpos) // Devuelve el número de localidad en el array
{
    if (objetos_t[objpos].locid == LOCATION_CARRIED || objetos_t[objpos].locid==LOCATION_WORN)
        return objetos_t[objpos].locid;
    else
        return get_loc_pos ( objetos_t[objpos].locid) ;
}

BYTE setObjectLocation(BYTE objno, BYTE location)
{
    if (location == LOCATION_CARRIED || location == LOCATION_WORN || location == LOCATION_NONCREATED || location == LOCATION_HERE)
    {
        objetos_t[objno].locid = location;
    } else	objetos_t[objno].locid = localidades_t[location].id;
}

unsigned char objectIsSupporter (unsigned char objno)
{
    //writeText ("Supporter? ");
    //writeValue (objno);
    //writeValue (objetos_t[objno].atributos&aSupporter);
    if (objno == EMPTY_OBJECT) return FALSE;
	//if (objno > gLAST_OBJECT_NUMBER) return FALSE;
    //if ((objetos_t[objno].atributos&aSupporter)>0)
    if (objectIsAttr(objno, aSupporter)) return TRUE;
    return FALSE;
}

unsigned char objectIsContainer (unsigned char objno)
{
   // writeText ("Container? ");
   // writeValue (objno);
    //writeValue (objetos_t[objno].atributos&aContainer);
	if (objno == EMPTY_OBJECT) return FALSE;
    //if ((objetos_t[objno].atributos&aContainer)>0)
    if (objectIsAttr(objno, aContainer)) return TRUE;
        else return FALSE;
   // return (objetos_t[objno].atributos&aContainer)>0?1:0;
    return FALSE;
}

unsigned char objectIsAttr (BYTE objno, BYTE att)
{
   if ((objetos_t[objno].atributos&((unsigned long int)1<<(unsigned long int)att))>0) return 1;
    else return 0;
}

BYTE  getObjectWeight(BYTE objno)
{
	BYTE weight = objetos_t[objno].peso;
	if ( ((objectIsContainer(objno)) || (objectIsSupporter(objno))) && (weight!=0)) // Container with zero weigth are magic boxes, anything you put inside weigths zero
  		weight = weight + getLocationObjectsWeight(objno);
	return weight;
}

BYTE getLocationObjectsWeight(BYTE locno)
{
	BYTE weight = 0;
	BYTE i=0;
	BYTE j=0;
	BYTE objweight;
    BYTE locid=0;

    if (locno==LOCATION_CARRIED || locno==LOCATION_WORN)
    {
        locid = locno;
    } else locid = localidades_t[locno].id;

	for (i=0;i<gNUM_OBJECTS;++i)
	{
		if (objetos_t[i].locid == locid)
		{
			objweight = objetos_t[i].peso;
			weight += objweight;
			if (objweight > 0)
			{
				if ((objectIsContainer(i)) || (objectIsSupporter(i)) )
				{
					weight += getLocationObjectsWeight( get_loc_pos (objetos_t[i].locid) );
				}
			}
		}
	}
	return weight;
}

BYTE  getObjectCountAt(BYTE locno)
{
	BYTE count = 0;
	BYTE i=0;
	BYTE locid;

	if (locno==LOCATION_CARRIED || locno==LOCATION_WORN)
    {   locid = locno;
    } else locid = localidades_t[locno].id;

	for (i=0;i<gNUM_OBJECTS;++i)
	{
		if (objetos_t[i].locid== locid)
		{
		    /*
			attr = getObjectLowAttributes(i);
			if (!bittest(getFlag(FLAG_PARSER_SETTINGS),3)) count ++;  // Parser settings say we should include NPCs as objects
			 else if (!objectIsNPC(i)) count++;     // or object is not an NPC
            */
            if (!objectIsNPC(i)) count++;
		}
	}


	return count;
}

BYTE getObjectCountAtWithAttr(BYTE locno, unsigned long int attrno)
{
	BYTE count = 0;
	BYTE i=0;
	for (i=0;i<gNUM_OBJECTS;++i)
		if (   (objetos_t[i].locid == localidades_t[locno].id)  && (objectIsAttr(i, attrno))) count++;
	return count;
}

BYTE  getNPCCountAt(BYTE locno)
{
	BYTE count = 0;
	BYTE i=0;
	for (i=0;i<gNUM_OBJECTS;++i)
		if ((objetos_t[i].locid  == localidades_t[locno].id) &&  (objectIsNPC(i))) count++;
	return count;
}

BYTE  objectIsNPC(BYTE objno)
{
	if (objno > gLAST_OBJECT_NUMBER) return FALSE;
	if (objetos_t[objno].atributos&aNPC)
        return TRUE;
    else
        return FALSE;
	//return (objetos_t[objno].atributos&aNPC)>0?1:0;
}

void writeObject(BYTE objno)
{
    BYTE isPlural = objectIsAttr(objno, aPluralName);
    BYTE isFemale = objectIsAttr(objno, aFemale);
 	BYTE isMale = objectIsAttr(objno, aMale);
 	BYTE isPropio = objectIsAttr(objno, aPropio);
 	BYTE isDeterminado = objectIsAttr(objno, aDeterminado);

    // Si es Propio no se imprime artículo. Pej: Javier (alguien)
    // Si no es Propio
    // Si es determinado: el la los las. El pergamino (uno en especial)
    // Si es indeterminado: un uno unos unas. Un pergamino (no lo conozco)

//    writeText ("%u %u %u",objno,j,isMale);
    if (objno==EMPTY_OBJECT)
    {
        #ifdef SPANISH
        writeText ("ninguno");
        #endif 
        #ifdef ENGLISH 
        writeText ("nothing");
        #endif 
        return;
    }
    if (!isPropio)
    {
        if (isDeterminado) // Determinado
        {
            if (!isPlural) // Singular
            {
                //if (isMale) writeText ("el ");
             #ifdef SPANISH
                if (isFemale) writeText ("la ");
                    else writeText ("el ");
             #endif
            #ifdef ENGLISH 
                writeText ("the ");
            #endif
            }
            else
            {
                #ifdef SPANISH
                if (isFemale) writeText ("las ");
                 else writeText ("los ");
                #endif 
                #ifdef ENGLISH 
                    writeText ("the ");
                #endif
            }
        }
        else // Indeterminado
        {
            if (!isPlural) // Singular
            {
                #ifdef SPANISH
                if (isFemale) writeText ("una ");
                 else writeText ("un ");
                #endif 

                #ifdef ENGLISH
                    writeText ("a ");
                #endif
            }
            else // Plural
            {
                #ifdef SPANISH 
                 if (isFemale) writeText ("unas ");
                 else writeText ("unos ");
                #endif 
                #ifdef ENGLISH 
                    writeText ("a ");
                #endif
            }
        }
    }
    //writeText (" ");
    writeText (objetos_t[objno].nombre_corto);
}

// -------------------------------------------------------------------------------
void newLine ()
{
   // a = fzx.font->height+1;
    //writeText("+");
    //fzx_putc('X');

    //writeValue(fzx.y);
    // Spectrum: 256 x 192 
    fzx.x = TextWindow.x;
    fzx.y+=1; // Coordenada estimada para la siguiente línea
    if ( (fzx.y)>(TextWindow.y+TextWindow.height-2)) // Si hemos llegado al final de la ventana de texto...
    {
       scrollVTextWindow (1); // Scroll Vertical de la ventana de texto
       fzx.y-=1;
    }
    //writeValue(fzx.y);
}

void  scrollVTextWindow (BYTE lineas) // Líneas de scroll en píxel, las fuentes usadas son proporcionales
{
    //fzx_putc('V');
    scrollArriba(TextWindow.y, TextWindow.x);
}

void  CaptionBox (BYTE *texto)
{
    // Calcula el tamaño en píxel
    writeText(texto);
}

void  writeTextCenter (BYTE *texto)
{
    // Calcula el tamaño en píxel
    //fzx.x = (256 - fzx_sExtent(texto)) / 2;
    // fzx.y = (192 - (fzx.font->height)) / 2;
    //writeText(texto);
    //newLine();
}

// writeText
// Description: Prints a long string splitting the string in words and creating new lines when needed. It adds a blank space at the end of each word.
/*
 The python compressor performs the following replacements:
    content = [w.replace('á', '#') for w in content]
    content = [w.replace('é', '$') for w in content]
    content = [w.replace('í', '%') for w in content]
    content = [w.replace('ó', '&') for w in content]
    content = [w.replace('ú', '\'') for w in content]
    content = [w.replace('ñ', '+') for w in content]
    content = [w.replace('¿', '/') for w in content]
    content = [w.replace('¡', '<') for w in content]
*/
void writeTextln (BYTE *texto)
{
    writeText (texto);
    writeText ("^");
}
void  writeText (BYTE *texto) 
{
    BYTE texto_buffer[256];
    BYTE buffer[20]; // Buffer de palabras
    BYTE counter=0;
    BYTE texto_counter=0;
    BYTE caracter=0;
    BYTE simbol_counter=0;
    BYTE salir=0;
 
   // 1. Descomprime la cadena
   memset(texto_buffer,0,256);
   caracter = texto[0];
   while (caracter!=0 && counter<255)
   {
       caracter = texto[texto_counter];
       if (caracter>127) // Código comprimido
       {
           simbol_counter=0;
           while (symbol_list[caracter-128][simbol_counter] && counter<255)
           {
               texto_buffer[counter]=symbol_list[caracter-128][simbol_counter];
               counter++;
               simbol_counter++;
           }
       }
       else
       {
           texto_buffer[counter]=caracter;
           counter++;
       }
       texto_counter++;
    }

   // 2. Imprime la cadena palabra a palabra
   counter=0;
   //caracter = texto_buffer[0];
   texto_counter=0;

    while (salir==0)
    {
        caracter = texto_buffer[texto_counter];
        buffer[counter] = caracter;

        // word terminators
        if (caracter==' ' || caracter=='.' || caracter=='^' || !caracter)
        {
            if (caracter==0) salir = 1;
            counter++;
            if (caracter!='.') counter--; // Steps backs over the escape char           
            
            buffer[counter]=0; // String terminator
            // New Line...
            // Each character fixed at 8pixel
            if (caracter=='^' || (fzx.x+counter)>(TextWindow.width+TextWindow.x))
            {
                newLine();
            }
            fzx_puts(buffer);
            if (caracter==' ') counter++;
            fzx.x+=counter;            
            counter=0;
        }  
        else 
        {
            counter++;
        }

        texto_counter++;
       }
}

void  writeSysMessage (BYTE messno)
{
   writeText (mensajesSistema_t[messno].word);
}

// Prints a message based on its position in the array 
void  writeMessage (BYTE messno)
{
   writeText (mensajes_t[messno].word);
}

// Parámetros en caracteres. 80x25
void defineGraphWindow (BYTE x, BYTE y, BYTE width, BYTE height)
{
    /*
    GraphWindow.x = x;
    GraphWindow.y = y;
    GraphWindow.width=width;
    GraphWindow.height=height;
    */
}

// Parámetros en caracteres. 80x25 (0 to 79, 0 to 24)
void defineTextWindow (BYTE x, BYTE y, BYTE width, BYTE height)
{
    TextWindow.x = x;
    TextWindow.y = y;
    TextWindow.width=width;
    TextWindow.height=height;
}

void  clearGraphWindow (BYTE color)
{
/*
    BYTE a,b;

    // Borra la ventana de gráficos en pantalla.
    for (a=GraphWindow.x;a<GraphWindow.width;a++)
    {
        for (b=GraphWindow.y;b<GraphWindow.height;b++)
        {
            clearchar (a,b,color);
        }
    }
    */
}

void  clearTextWindow (BYTE color, BYTE clear)
{
    unsigned char a,b;
    // Posiciona el cursor en la esquina superior-izquierda
    fzx.x = TextWindow.x;
    fzx.y = TextWindow.y;
    // Borra la ventana de texto en pantalla.
    for (b=TextWindow.y;b<(TextWindow.y+TextWindow.height-1);++b)
    {
        for (a=TextWindow.x;a<(TextWindow.x+TextWindow.width);++a)
        {
            if  (clear==TRUE) clearchar (a,b,color);
                else set_attr (a,b,color);
        }
    }
}

void clearTextLine (BYTE x, BYTE y, BYTE color)
{
    BYTE a;
    for (a=31;a>x;--a)
        clearchar (a, y, color);
}

// GOTOXY 
// Input: X = COLUMN (0-31)
//        Y = ROW (0-24)
// Description: Moves the cursor to the specified column and row 

void gotoxy (BYTE x, BYTE y)
{
    fzx_setat (x,y);
}

void getInput ()
{
   BYTE contador=0;
   BYTE caracter=0;
   // Iterates until the player press ENTER
   memset(playerInput,0,MAX_INPUT_LENGTH); // Limpia el buffer
   gotoxy(TextWindow.x,fzx.y);
   writeText (playerPrompt);

   //writeText("_");
   while (caracter!=13 && contador<MAX_INPUT_LENGTH)
   {
        caracter = getKey();
        if (caracter!=4) { // Código devuelto al borrar
            playerInput[contador]=caracter;
            contador++;
            print_char (TextWindow.x+contador, fzx.y,caracter);
        }
        else  // Borrar
            {
            playerInput[contador]=0;            
             print_char (TextWindow.x+contador, fzx.y,caracter);
            if (contador>0) contador--;
            }
        waitForNoKey();
   }
   
   //playerInput[contador-1]=' ';
   playerInput[contador]=0;
}

void fontStyle (BYTE style)
{
    switch (style)
    {
        case NORMAL:
       // fzx.font = ff_utz_Handpress;
        break;
        case TITLE:
       // fzx.font = ff_utz_ShadowFlower;
        break;
        case PLAYER:
       // fzx.font = ff_utz_ShadowFlower;
        break;
    }
}

void hideGraphicsWindow()
{
    // Toma el tamaño completo de la pantalla...
    defineTextWindow (0,0,32,24);
}

void setConnection (BYTE loc_orig, BYTE value, BYTE loc_dest)
{
    if (value < NUM_CONNECTION_VERBS)
    {
        conexiones_t[loc_orig].con[value-1]=localidades_t[loc_dest].id;
    }
}

BYTE getConnection (BYTE loc_orig, BYTE value)
{
    if (value>NUM_CONNECTION_VERBS) return NO_EXIT;
    return get_loc_pos(conexiones_t[loc_orig].con[value-1]);
}

void  ACCautow()
{
	BYTE objno;
	objno =findMatchingObject(LOCATION_CARRIED);
	if (objno != EMPTY_OBJECT) { ACCwear(objetos_t[objno].id); return; };
	objno =findMatchingObject(LOCATION_WORN);
	if (objno != EMPTY_OBJECT) { ACCwear(objetos_t[objno].id); return; };
	objno =findMatchingObject(loc_here());
	if (objno != EMPTY_OBJECT) { ACCwear(objetos_t[objno].id); return; };
	writeSysMessage(SYSMESS_YOUDONTHAVETHAT);
	ACCnewline();
	ACCdone();
}

void  ACCautor()
{
    BYTE objno;
    objno =findMatchingObject(LOCATION_WORN);
	if (objno != EMPTY_OBJECT) { ACCremove(objetos_t[objno].id); return; };
	objno =findMatchingObject(LOCATION_CARRIED);
	if (objno != EMPTY_OBJECT) { ACCremove(objetos_t[objno].id); return; };
	objno =findMatchingObject(loc_here());
	if (objno != EMPTY_OBJECT) { ACCremove(objetos_t[objno].id); return; };
	writeSysMessage(SYSMESS_YOURENOTWEARINGTHAT);
	ACCnewline();
	ACCdone();
}

BYTE ACCremove(BYTE objid)
{
    BYTE objpos;
    objpos = get_obj_pos(objid);
    if (objetos_t[objpos].locid == LOCATION_WORN)
    {
			writeSysMessage(SYSMESS_YOUREMOVEOBJECT);
            setObjectLocation(objpos, LOCATION_CARRIED);
            writeObject (objpos);
            writeText(". ^");
			ACCdone();
			return TRUE;
    }

    if (objetos_t[objpos].locid == loc_here())
    {
			writeSysMessage(SYSMESS_YOUDONTHAVEOBJECT);
            ACCnewline();
			return TRUE;

    }
    if (objetos_t[objpos].locid == LOCATION_CARRIED)
    {
        if (objectIsAttr(objpos, aWear))
        {
            writeSysMessage (SYSMESS_YOUARENOTWEARINGOBJECT);
            writeObject (objpos);
            writeText(". ^");
			ACCdone();
			return TRUE;
        }
        writeSysMessage (SYSMESS_YOUCANNOTREMOVEOBJECT);
        return TRUE;
	}
    return FALSE;

}

BYTE ACCwear(BYTE objid)
{
    BYTE objpos;
    objpos = get_obj_pos(objid);
    if (objetos_t[objpos].locid == LOCATION_WORN)
    {
			writeSysMessage(SYSMESS_YOUAREALREADYWEARINGTHAT);
			ACCnewline();
			ACCdone();
			return TRUE;
    }

    if (objetos_t[objpos].locid == loc_here())
    {
			writeSysMessage(SYSMESS_YOUDONTHAVEOBJECT);
            ACCnewline();
			return TRUE;

    }
    if (objetos_t[objpos].locid == LOCATION_CARRIED)
    {
        if (!objectIsAttr(objpos, aWear))
        {
            writeSysMessage (SYSMESS_YOUCANTWEAROBJECT);
            ACCnewline();
			ACCdone();
			return TRUE;
        }
        setObjectLocation(objpos, LOCATION_WORN);
        writeSysMessage (SYSMESS_YOUWEAROBJECT);
        writeObject(objpos);
        writeText (". ^");
        return TRUE;
	}
    return FALSE;
}

void ACCputin(BYTE objid, BYTE obj2id)
{
    // BYTE success = false;
	//setFlag(FLAG_REFERRED_OBJECT, objno);
	//setReferredObject(objno);
    BYTE objpos;
    BYTE obj2pos;
    objpos = get_obj_pos(objid);
    obj2pos = get_obj_pos(obj2id);

	if (objetos_t[objpos].locid == LOCATION_WORN)
    {
			writeSysMessage(SYSMESS_YOUAREALREADYWEARINGTHAT);
            writeObject(objpos);
            writeText (". ^");
			return FALSE;
    }

    if (objetos_t[objpos].locid == loc_here())
    {
			writeSysMessage(SYSMESS_YOUDONTHAVEOBJECT);
            ACCnewline();
			return FALSE;

    }
    if (objetos_t[objpos].locid == LOCATION_CARRIED)
    {
            // En contenedores: obj.id = loc.id
        	setObjectLocation (objpos, get_loc_pos(obj2id));
        	flags[fobjects_carried_count]--;
        	if (objectIsAttr(obj2pos,aSupporter))
            {
                writeSysMessage(SYSMESS_YOUPUTOBJECTON);
                writeObject(objpos);
                writeText (" sobre ");
            }
            else
            {
                writeSysMessage(SYSMESS_YOUPUTOBJECTIN);
                writeObject(objpos);
                writeText (" en ");
            }

            writeObject(obj2pos);
			writeSysMessage(SYSMESS_PUTINTAKEOUTTERMINATION);
            ACCnewline();
			//ACCdone();
			return TRUE;
	}
    return FALSE;
}


void ACCtakeout(BYTE objid, BYTE obj2id)
{
    // objid : Objeto a sacar
    // obj2id : Contenedor

    BYTE objpos;
    objpos = get_obj_pos(objid);
    if (objetos_t[objpos].locid == LOCATION_WORN || objetos_t[objpos].locid==LOCATION_CARRIED)
    {
			writeSysMessage(SYSMESS_YOUALREADYHAVEOBJECT);
			ACCnewline();
			ACCdone();
			return FALSE;
    }

    if (objetos_t[objpos].locid == loc_here())
    {
        // LocID = OBJID para contenedores
        if (objectIsAttr(get_obj_pos(obj2id),aSupporter))
            {
                writeSysMessage (SYSMESS_YOUCANTTAKEOBJECTFROM);
            } else
                writeSysMessage (SYSMESS_YOUCANTTAKEOBJECTOUTOF);
            ACCnewline();
			return FALSE;

    }

    if (getObjectWeight(objpos)+getLocationObjectsWeight(LOCATION_WORN)+getLocationObjectsWeight(LOCATION_CARRIED)> flags[fmaxweight_carried])
    {
        writeSysMessage(SYSMESS_WEIGHSTOOMUCH);
        ACCnewline();
        return FALSE;
    }

    if (flags[fobjects_carried_count]  > flags[fmaxobjects_carried])
    {
        writeSysMessage(SYSMESS_CANTCARRYANYMORE);
        ACCnewline();
        return FALSE;
    }


	setObjectLocation(objpos, LOCATION_CARRIED);
	writeSysMessage(SYSMESS_YOUTAKEOBJECT);
	ACCnewline();
    return TRUE;
}

void incr16bit (BYTE *pointer)
{
    if (pointer[0]==255)
    {
        pointer[0]=0;
        ++pointer[1];
        return;
    }
    ++pointer[0];
}

