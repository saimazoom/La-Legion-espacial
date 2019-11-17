/*
 ZMiniIF para ordenadores de 8bit
 Basado en PAWS y NGPAWS-Beta 9 (Uto/Carlos Sanchez) http://www.ngpaws.com
 (c) 2016. Written by KMBR.
 v1.0

 License
-------
 Released under the the GPL v2 or later license.


*/

#define DEBUG       // DEBUG=1 incluye funciones y mensajes de depuraci�n
#define GRAPHICS    // GRAPHICS=1 Incluye gr�ficos

#include <string.h>

#include "fzx.h"
#include "fzxfonts_utz.h"

#include "symbol_list.h"
#include "parser_defs.h"
#include "juego_flags.h"
#include "parser.h"
#include "zx7.h"
#include ".\libgfx\libgfx.h"

// Funciones externas
//extern void scrollArriba2 (BYTE linea_inicial, BYTE num, BYTE step);
//extern void clearchar (BYTE x, BYTE y, BYTE color);

// Variables globales
unsigned char flags[255];
unsigned char playerInput[80];
unsigned char playerWord[25];
unsigned char *playerPrompt = "> ";

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


token_t adjetivos_t [] =
{
    {"peque",       2},
    {"grand",        3},
    {"viejo",         4},
    {"vieja",         4},
    {"nuevo",         5},
    {"nueva",         5},
    {"duro",          6},
    {"dura",          6},
    {"suave",         7},
    {"largo",         9},
    {"larga",         9},
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
/* S�mbolos en el juego de caracteres de tc.py (Text Compressor):
    # Sustituye las � y los caracteres acentuados por los nuevos s�mbolos
    content = [w.replace('�', '#') for w in content]
    content = [w.replace('�', '$') for w in content]
    content = [w.replace('�', '%') for w in content]
    content = [w.replace('�', '&') for w in content]
    content = [w.replace('�', '\'') for w in content]
    content = [w.replace('�', '+') for w in content]
    content = [w.replace('�', '/') for w in content]
    content = [w.replace('�', '<') for w in content]
*/

extern token_t mensajesSistema_t [];

//---------------------------------
// Fin de tablas de parser
//---------------------------------
void  initParser (void) // 212bytes
{
    // Men� principal
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
    // Cuenta las im�genes
	gNUM_IMG=0;
	while (imagenes_t[gNUM_IMG].id!=0)
    {
        gNUM_IMG++;
    }
    // Inicializa la pantalla
    fzx.font = ff_utz_Handpress;
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
                fzx.x=TextWindow.x*8;
                fzx.y=TextWindow.y*8;
                loc_temp = get_loc_pos (flags[flocation]); // La posici�n en el array no tiene por que coincidir con su id

                //fontStyle(TITLE);
                //writeText (localidades_t[loc_temp].name);
                //newLine();

                fontStyle(NORMAL);
                writeText (localidades_t[loc_temp].descripcion);
                newLine();
                // Proceso 1 Post, despu�s de describir la localidad...
                proceso1_post();
                // Si est� activo, lista los objetos
                if (TRUE)
                {
                  ACClistobj();
                }

                // Si est� activo, lista los PNJ

                // Si est�n activas, describe las salidas
                if (flags[fsalidas])
                {
                    writeText ("Salidas visibles: ");
                    for (i=0;i<10;i++)
                    {
                        j = conexiones_t[loc_temp].con[i];
                            if (j<NO_EXIT && j>0)
                                {
                                    writeText (" ");
                                    writeText (nombres_t[i<<1].word);
                            }
                    }
                    /*
                    800bytes!
                    if (conexiones_t[loc_temp].con[nNorte]>0 && conexiones_t[loc_temp].con[nNorte]<NO_EXIT ) writeText ("norte ");
                    if (conexiones_t[loc_temp].con[nSur]>0 && conexiones_t[loc_temp].con[nSur]<NO_EXIT) writeText ("sur ");
                    if (conexiones_t[loc_temp].con[nEste]>0 && conexiones_t[loc_temp].con[nEste]<NO_EXIT) writeText ("este ");
                    if (conexiones_t[loc_temp].con[nOeste]>0 && conexiones_t[loc_temp].con[nOeste]<NO_EXIT) writeText ("oeste ");
                    if (conexiones_t[loc_temp].con[nNoreste]>0 && conexiones_t[loc_temp].con[nNoreste]<NO_EXIT) writeText ("noreste ");
                    if (conexiones_t[loc_temp].con[nNorOeste]>0 && conexiones_t[loc_temp].con[nNorOeste]<NO_EXIT) writeText ("noroeste ");
                    if (conexiones_t[loc_temp].con[nSurEste]>0 && conexiones_t[loc_temp].con[nSurEste]<NO_EXIT) writeText ("sureste ");
                    if (conexiones_t[loc_temp].con[nSurOeste]>0 && conexiones_t[loc_temp].con[nSurOeste]<NO_EXIT) writeText ("suroeste ");
                    if (conexiones_t[loc_temp].con[nArriba]>0 && conexiones_t[loc_temp].con[nArriba]<NO_EXIT) writeText ("arriba ");
                    if (conexiones_t[loc_temp].con[nAbajo]>0 && conexiones_t[loc_temp].con[nAbajo]<NO_EXIT) writeText ("abajo ");
                    */
                    // Si hemos estado en la localidad a�ade su nombre...
                    newLine();
                }
                localidades_t[loc_temp].visited=TRUE;
                gDESCRIBE_LOCATION_FLAG=FALSE; // Evita describir la localidad en cada turno
            }
            else writeSysMessage(SYSMESS_ISDARK);

		}

		// Espera el input del jugador
        fontStyle (PLAYER);
		writeText (playerPrompt);
		getInput ();
		newLine();
		parse(); // Extrae los tokens...
        fontStyle (NORMAL);

        if (gDEBUGGER==FALSE)
        {
           if (respuestas()==FALSE)
                respuestas_post();
           proceso2(); // Tabla de proceso despu�s de dar respuesta al jugador
        }
#ifdef DEBUG
        else
            debugger();
#endif


    }
}

void parse() // 670bytes
{
// Input: Cadena de texto -> playerInput
// Output: tokens -> verbo, nombre1, nombre2, adjetivo1, adjetivo2
// Una frase tiene: s�lo un verbo, un m�ximo de dos nombres, un m�ximo de dos adjetivos, un adverbio
unsigned char counter=0;
unsigned char caracter = 0;
unsigned char ongoing=1;
unsigned char word_counter=0;
unsigned char i;
BYTE salir=0;

procesaString (); // Convierte todo a may�sculas, elimina acentos, s�mbolos y �

caracter = playerInput[0]; // Va a recorrer toda la cadena de entrada...

// Inicializa los flags de vocabulario...
flags[fverb]=EMPTY_WORD;
flags[fnoun1]=EMPTY_WORD;
flags[fnoun2]=EMPTY_WORD;
flags[fadject1]=EMPTY_WORD;
flags[fadject2]=EMPTY_WORD;
flags[fadverb]=EMPTY_WORD;
gDEBUGGER=FALSE;

while (salir==0) // Recorre la cadena hasta el final
	{
	    if (counter==0 && playerInput[counter]==';') gDEBUGGER=TRUE; // Es un comando de depuraci�n

        if ((caracter==' ' || caracter==13 || caracter==0 || caracter==10) && ongoing==1)  // Termina de extraer una palabra...
        {
            ongoing = 0;
            playerWord[word_counter] = 0; // Para ayudar a las funciones de C...
            word_counter = 0;

            if (gDEBUGGER==FALSE)
            {
                if (flags[fverb]==EMPTY_WORD && (i = buscador(verbos_t, playerWord))>0)
                {
                   #ifdef DEBUG
                   writeText ("V");
                   #endif
                   flags[fverb]=i;
                }
                else
                if ((flags[fnoun1]==EMPTY_WORD || flags[fnoun2]==EMPTY_WORD) && (i = buscador(nombres_t, playerWord))>0) // Busca si es un nombre...
                {
                    #ifdef DEBUG
                    writeText ("N");
                    #endif
                    if (i<NUM_CONVERTIBLE_NOUNS && flags[fverb]==EMPTY_WORD) flags[fverb]=i; // Si es un nombre < 20 tambi�n vale como verbo
                        else
                            if (flags[fnoun1]==EMPTY_WORD)
                            {
                                    #ifdef DEBUG
                                    writeText ("1");
                                    #endif
                                    flags[fnoun1]=i;
                            }
                            else
                            {
                                #ifdef DEBUG
                                writeText("2");
                                #endif
                                flags[fnoun2]=i;
                            }
                }
                else
                if (flags[fadject1]==EMPTY_WORD && (i = buscador(adjetivos_t, playerWord))>0) // Adjetivo...?
                {
                    #ifdef DEBUG
                    writeText ("A");
                    #endif
                    if (flags[fadject1]==0) flags[fadject1]=i;
                        else flags[fadject2]=i;
                }
                else
                if (flags[fadverb]==EMPTY_WORD && (i = buscador(adverbios_t, playerWord))>0) // Adverbio?
                {
                    #ifdef DEBUG
                    writeText ("B");
                    #endif
                    flags[fadverb]=i;
                }
                else
                if (flags[fprep]==EMPTY_WORD && (i = buscador(preposiciones_t, playerWord))>0) // Adverbio?
                {
                    #ifdef DEBUG
                    writeText ("P");
                    #endif
                    flags[fprep]=i;
                }
            }
            #ifdef DEBUG
            else // Comando de depuraci�n
            {
                if (flags[fverb]==EMPTY_WORD && (i = buscador (verbos_debug_t, playerWord)))
                {
                    writeText ("D");
                    flags[fverb]=i;
                }
                else
                if (flags[fnoun1]==EMPTY_WORD)
                {
                   writeText ("V");
                   flags[fnoun1]= atoi (playerWord);
                }
                else
                if (flags[fnoun2]==EMPTY_WORD)
                {
                   writeText ("V");
                   flags[fnoun2]= atoi (playerWord);
                }
            }
            #endif
        }
        if (ongoing==0 && caracter!=' ') ongoing=1;
        if (ongoing==1)
        {
            playerWord[word_counter] = caracter;
            if (word_counter<MAX_WORD_LENGHT) word_counter++; // Limitamos el parsing a 5 caracteres...
        }

        if (caracter==0 || caracter==13) salir=1;
        counter++;
        caracter = playerInput[counter];
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
*/

switch (flags[fverb])
    {
    case d_testme:
        break;
    case d_xlista:
        ACClistat(flags[fnoun1], 0);
        break;
    case d_goto:
        ACCgoto(flags[fnoun1]);
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
        if (CNDozero(flags[fnoun1],(unsigned long int)1<<flags[fnoun2]))
            writeText ("0^");
        else
            writeText ("1^");
        break;
    case d_setattr:
        ACCoset(flags[fnoun1], (unsigned long int)1<<flags[fnoun2]);
        break;
    case d_clearattr:
        ACCoclear(flags[fnoun1], (unsigned long int)1<<flags[fnoun2]);
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
        writeText (";help ^");

        break;
    case d_where:
        playerInput[0]=0;
        writeValue(objetos_t[get_obj_pos(flags[fnoun1])].locid);
        writeText (playerInput);
        writeText ("^");
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

unsigned char buscador (token_t *tabla, unsigned char *word) // 180bytes
{
    // Input: Cadena de texto
    unsigned char fin=0;
    unsigned char counter=0;
    //writeText ("Buscando...%s\n",word);
    while (fin==0)
    {
		//writeText ("%s-%s ",tabla[counter].word,playerWord);
        if (tabla[counter].id==0) fin=1; // Fin de la tabla...
        if (strncmp(word,tabla[counter].word,MAX_WORD_LENGHT)==0)
        {
            // flags[ftemp]=tabla[counter].id;
            //writeText ("found %u", flags[ftemp]);
            return tabla[counter].id;
        }
        counter++;
    }
    return EMPTY_WORD;
}

void procesaString ()
{
//    strupr(playerInput);
}

// --------------------------------------------
// Librer�a de condactos
// --------------------------------------------

void  ACCdesc(void)
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

unsigned char  CNDnotat(BYTE locid)
{
	 return (!CNDat(locid));
}

unsigned char  CNDatgt(BYTE locid)
{
 if (locid >= flags[flocation]) return TRUE;
    else return FALSE;
}

unsigned char  CNDatlt(BYTE locid)
{
 if (locid <= flags[flocation]) return TRUE;
    else return FALSE;
}

BYTE  CNDpresent(BYTE objid)
{
    BYTE objnum = get_obj_pos(objid);
	BYTE locid = objetos_t[objnum].locid;
    BYTE obj2num = get_obj_pos(locid); // Si est� dentro de un contenedor, el locid coincide con el objid del contenedor
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
	return (getObjectLocation( get_obj_pos(objid)) == LOCATION_WORN);
}

BYTE  CNDnotworn(BYTE objid)
{
    if (CNDworn(objid)==TRUE) return FALSE;
        else return TRUE;
	//return !CNDworn(objid);
}


BYTE  CNDnotcarr(BYTE objid)
{
    if (CNDcarried(objid)==TRUE)return FALSE;
        else return FALSE;
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
*/

BYTE  CNDtimeout()
{
	// return bittest(getFlag(FLAG_TIMEOUT_SETTINGS),7);
}

BYTE CNDisat(BYTE objid, BYTE locid)
{
//	return (objetos_t[get_obj_pos(objid)].locid == locid);
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

BYTE  CNDnoun2(BYTE wordno)
{
	return (getFlag(fnoun2) == wordno);
}

BYTE  CNDadject2(BYTE wordno)
{
	return (getFlag(fadject2) == wordno);
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

	writeSysMessage(SYSMESS_YOUARECARRYING);
	for (i=0;i<gNUM_OBJECTS;i++)
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
            if (count<(objscount-1)) writeText(", ");
            if (count==(objscount-1)) writeText (" y ");
        }
	}

	if (!count)
	{
		 writeSysMessage(SYSMESS_CARRYING_NOTHING);
		 writeText("^");
		 // ACCnewline();
	} else writeText (".^");

	gDONE_FLAG = TRUE;
}

void  ACCquit()
{
	ginQUIT = TRUE;
	writeSysMessage(SYSMESS_AREYOUSURE);
}

void  ACCend()
{
	//$('.input').hide();
	ginEND = TRUE;
	writeSysMessage(SYSMESS_PLAYAGAIN);
	gDONE_FLAG = TRUE;
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
	fzx.x = TextWindow.x*8;
	fzx.y = TextWindow.y*8;
}


void  ACCautog()
{
    BYTE objid;
    //  flags[ftemp] = ACCgetReferredObject(flags[fnoun1]);
    objid = ACCgetReferredObject(flags[fnoun1]);
    if (objid != EMPTY_OBJECT)
    {
        ACCget (objid);
        return TRUE;
    }

	writeSysMessage(SYSMESS_CANTSEETHAT);
	ACCnewline();
	ACCdone();
}


void  ACCautod()
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

void  ACCmessage(BYTE mesno)
{
	writeMessage(mesno);
	// ACCnewline();
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

void ACCplace(BYTE objid, BYTE locid) // Aqu� locno puede ser otro n�mero de objeto.
{
    if (locid==LOCATION_CARRIED || locid==LOCATION_WORN)
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

void  ACCnewline()
{
    newLine();
}

void  ACCwriteText(BYTE flagno)
{
   writeMessage(flags[flagno]);
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

  for (i=0;i<gNUM_OBJECTS;i++)
  {
    //j = objetos_t[i].id;
  	if (objetos_t[i].locid == locid)
    {
  		if  (!objectIsNPC(i) && !objectIsAttr(i,aConcealed) && !objectIsAttr(i,aScenery)) // if not an NPC and object is not concealed nor scenery
  		  {
            writeObject (i);
            progresscount++;
            // Formato de lista cont�nua
            if (objscount>1 && (progresscount <= objscount - 2))
            {
                writeText("  ");
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

void  ACCmes(BYTE mesno)
{
	writeMessage(mesno);
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


/*
void ACCnewtext()
{
	// parser_order_buffer = '';
}
*/

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

void  ACCpicture(BYTE picid)
{
	BYTE picpos;
	picpos = get_img_pos(picid);
    setRAMPage (imagenes_t[picpos].page);
    dzx7AgileRCS(imagenes_t[picpos].paddr, ((unsigned char*) 16384));
    setRAMBack();
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

BYTE CNDozero(BYTE objid, unsigned long int attrno)
{
    if (objectIsAttr(get_obj_pos(objid), attrno)) return FALSE;
    return TRUE;
    }

BYTE CNDonotzero(BYTE objid, unsigned long int attrno)
{
 if (CNDozero(objid,attrno)==TRUE) return FALSE;
    else return TRUE;
}

void ACCoset(BYTE objid, unsigned long int attrno)
{
    objetos_t[get_obj_pos(objid)].atributos|=attrno;
    /*
	if (attrno > 63) return;
	if (attrno <= 31)
	{
		attrs = getObjectLowAttributes(objno);
		var attrs = bitset(attrs, attrno);
		setObjectLowAttributes(objno, attrs);
		return;
	}
	var attrs = getObjectHighAttributes(objno);
	attrno = attrno - 32;
	attrs = bitset(attrs, attrno);
	setObjectHighAttributes(objno, attrs);
    */
}

void ACCoclear(BYTE objid, unsigned long int attrno)
{
    objetos_t[get_obj_pos(objid)].atributos&=!attrno;
    /*
	if (attrno > 63) return;
	if (attrno <= 31)
	{
		var attrs = getObjectLowAttributes(objno);
		attrs = bitclear(attrs, attrno);
		setObjectLowAttributes(objno, attrs);
		return;
	}
	var attrs = getObjectHighAttributes(objno);
	attrno = attrno - 32;
	attrs = bitclear(attrs, attrno);
	setObjectHighAttributes(objno, attrs);
    */
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

void  ACCwrite(BYTE writeno)
{
	writeMessage(writeno);
}

void  ACCwriteln(BYTE writeno)
{
	writeMessage(writeno);
	ACCnewline();
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
	return FALSE;
}

void ACConeg(BYTE objid, unsigned long int attrno)
{
	/*
	if (attrno > 63) return;
	if (attrno <= 31)
	{
		var attrs = getObjectLowAttributes(objno);
		attrs = bitneg(attrs, attrno);
		setObjectLowAttributes(objno, attrs);
		return;
	}
	var attrs = getObjectHighAttributes(objno);
	attrno = attrno - 32;
	attrs = bitneg(attrs, attrno);
	setObjectHighAttributes(objno, attrs);
	*/
	objetos_t[get_obj_pos(objid)].atributos^=attrno;
}


// -------------------------------------
// Funciones auxiliares del parser
// -------------------------------------
BYTE findMatchingObject(BYTE locno)
{
    BYTE i,j=0;

	for (i=0;i<gNUM_OBJECTS;i++) // Recorre el array de objetos
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

   	for (i=0; i<gNUM_OBJECTS;i++) // Try to find it in present containers/supporters
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
	for (i=0;i<gNUM_OBJECTS;i++)	if (getObjectLocation(i) == LOCATION_CARRIED)setObjectLocation(i, flags[flocation]);
	for (i=0;i<gNUM_OBJECTS;i++)	if (getObjectLocation(i) == LOCATION_WORN)setObjectLocation(i, flags[flocation]);
}

void  done()
{
	gDONE_FLAG = TRUE;
}

void  desc()
{
	gDESCRIBE_LOCATION_FLAG = TRUE;
}


BYTE  loc_here ()
{
    return flags[flocation]; // flocation contiene el ID de la localidad
}

// Input: ID de localidad
// Output: Posici�n dentro del array de localidades.

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

BYTE  get_table_num (token_t *tabla, BYTE noun_id)
{
    unsigned char fin=0;
    unsigned char counter=0;
    while (fin==0)
    {
        if (tabla[counter].id==0) fin=1; // Fin de la tabla...
        if (tabla[counter].id==noun_id) return counter;
        counter++;
    }
    return 0;
}

BYTE  getObjectLocation (BYTE objpos) // Devuelve el n�mero de localidad en el array
{
    if (objetos_t[objpos].locid == LOCATION_CARRIED || objetos_t[objpos].locid==LOCATION_WORN)
        return objetos_t[objpos].locid;
    else
        return get_loc_pos ( objetos_t[objpos].locid) ;
}

BYTE setObjectLocation(BYTE objno, BYTE location)
{
    if (location == LOCATION_CARRIED || location == LOCATION_WORN )
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

unsigned char objectIsAttr (unsigned char objno, unsigned long int att)
{
	return (objetos_t[objno].atributos&att)>0?1:0;
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

	for (i=0;i<gNUM_OBJECTS;i++)
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

	for (i=0;i<gNUM_OBJECTS;i++)
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
	for (i=0;i<gNUM_OBJECTS;i++)
		if (   (objetos_t[i].locid == localidades_t[locno].id)  && (objectIsAttr(i, attrno))) count++;
	return count;
}

BYTE  getNPCCountAt(BYTE locno)
{
	BYTE count = 0;
	BYTE i=0;
	for (i=0;i<gNUM_OBJECTS;i++)
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

    // Si es Propio no se imprime art�culo. Pej: Javier (alguien)
    // Si no es Propio
    // Si es determinado: el la los las. El pergamino (uno en especial)
    // Si es indeterminado: un uno unos unas. Un pergamino (no lo conozco)

//    writeText ("%u %u %u",objno,j,isMale);
    if (objno==EMPTY_OBJECT)
    {
        writeText ("ninguno ");
        return;
    }
    if (!isPropio)
    {
        if (isDeterminado) // Determinado
        {
            if (!isPlural) // Singular
            {
                if (isMale) writeText ("el ");
                 else writeText ("la ");
            }
            else
            {
                if (isMale) writeText ("los ");
                 else writeText ("las ");
            }
        }
        else // Indeterminado
        {
            if (!isPlural) // Singular
            {
                if (isMale) writeText ("un ");
                 else writeText ("una ");

            }
            else // Plural
            {
                 if (isMale) writeText ("unos ");
                 else writeText ("unas ");
            }
        }
    }
    writeText (objetos_t[objno].nombre_corto);
}

// -------------------------------------------------------------------------------
void newLine ()
{
   // a = fzx.font->height+1;
    //writeText("+");
    //fzx_putc('X');

    //writeValue(fzx.y);

    fzx.x = TextWindow.x*8;
    fzx.y+=9; // Coordenada estimada para la siguiente l�nea
    if ( (fzx.y)>179) // Si hemos llegado al final de la ventana de texto...
    {
       scrollVTextWindow (1); // Scroll Vertical de la ventana de texto
       fzx.y=174;
    }

    //writeValue(fzx.y);
}

void  scrollVTextWindow (BYTE lineas) // L�neas de scroll en p�xel, las fuentes usadas son proporcionales
{
    //fzx_putc('V');
    scrollArriba(TextWindow.y, TextWindow.x);
}

void  CaptionBox (BYTE *texto)
{
    // Calcula el tama�o en p�xel
    writeText(texto);
}

void  writeTextCenter (BYTE *texto)
{
    // Calcula el tama�o en p�xel
    //fzx.x = (256 - fzx_sExtent(texto)) / 2;
    // fzx.y = (192 - (fzx.font->height)) / 2;
    //writeText(texto);
    //newLine();
}

void  writeText (BYTE *texto) //694bytes
{
    BYTE counter=0;
    BYTE texto_counter=0;
    BYTE caracter=0;
    BYTE ongoing=0;
    BYTE texto_buffer[256];
    BYTE buffer[20]; // Buffer de palabras
    BYTE simbol_counter=0;
    BYTE salir=0;
    fcounter=0;
    fcaracter=0;

   // 1. Descomprime la cadena
   memset(texto_buffer,0,256);
   caracter = texto[0];
   while (caracter!=0 && counter<255)
   {
       caracter = texto[texto_counter];
       if (caracter>127) // C�digo comprimido
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
   caracter = texto_buffer[0];
   texto_counter=0;

   while (salir==0)
   {
       if (ongoing==1)
           {
               if (caracter==' ' || caracter=='.' || caracter=='^' || caracter==0) // Fin de una palabra
               {
                   ongoing=0;
                   if (caracter!='^')  // No imprime c�digos de escape
                    {
                        counter++;
                        buffer[counter]=caracter;
                    }
                   buffer[counter+1]=0;
                   // Calcula el tama�o de la palabra en p�xel y crea una nueva l�nea si es necesario
                   if ((fzx.x+counter*7)>=8*(TextWindow.width+TextWindow.x))
                        {
                        //fzx_putc('L');
                        newLine();
                        }
                   else if (fzx.y>179)
                   {
                  //   scrollVTextWindow(1);
                  //   fzx.y=178; // Fuerza a no salir de la pantalla
                   }

                   fzx_puts(buffer);
                   counter=0;
                   if (caracter==0) salir=1; // Fin de cadena
               }
               else
               {
                   counter++;
                   buffer[counter]=caracter;
               }
           }
           else if (caracter!='.' && caracter!='^') // Comienzo de palabra
            {
                ongoing=1;
                counter=0;
                buffer[counter]=caracter;
            }

       if (caracter=='^')
        newLine();

       texto_counter++;
       caracter = texto_buffer[texto_counter];
   }

}

void  writeSysMessage (BYTE messno)
{
   writeText (mensajesSistema_t[messno].word);
}

void  writeMessage (BYTE messno)
{
   writeText (mensajes_t[messno].word);
}

// Par�metros en caracteres. 80x25
void defineGraphWindow (BYTE x, BYTE y, BYTE width, BYTE height)
{
    /*
    GraphWindow.x = x;
    GraphWindow.y = y;
    GraphWindow.width=width;
    GraphWindow.height=height;
    */
}

// Par�metros en caracteres. 80x25 (0 to 79, 0 to 24)
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

    // Borra la ventana de gr�ficos en pantalla.
    for (a=GraphWindow.x;a<GraphWindow.width;a++)
    {
        for (b=GraphWindow.y;b<GraphWindow.height;b++)
        {
            clearchar (a,b,color);
        }
    }
    */
}

void  clearTextWindow (BYTE color)
{
    unsigned char a,b;
    // Posiciona el cursor en la esquina superior-izquierda
    fzx.x = TextWindow.x*8;
    fzx.y = TextWindow.y*8;

    // Borra la ventana de texto en pantalla.
    for (b=TextWindow.y;b<TextWindow.height;b++)
    {
        for (a=TextWindow.x;a<TextWindow.width;a++)
        {
            clearchar (a,b,color);
        }
    }
}


void clearTextLine (BYTE x, BYTE y, BYTE color)
{
    BYTE a;
    for (a=31;a>x;a--)
        clearchar (a, y, color);
}

void gotoxy (BYTE x, BYTE y)
{
    fzx.x = x;
    fzx.y = y;
}

void getInput ()
{
   BYTE contador=0;
   BYTE caracter=0;
   //fcontador=0;
   //fcaracter=0;
 //   BYTE ancho=0;
  // fzx_font *puntero;
// Espera a que el jugador presione enter...
   memset(playerInput,0,80); // Limpia el buffer
   gotoxy(TextWindow.x+8,fzx.y);  // Borra la pantalla...
   while (caracter!=13)
   {
        caracter = getKey();
        if (caracter!=4) { // C�digo devuelto al borrar
            playerInput[contador]=caracter;
            contador++;
            if (caracter!=13) fzx_putc(caracter);
        }
        else  // Borrar
            {
            if (contador>0) contador--;
            // Retrocede el �ltimo caracter...

            gotoxy(TextWindow.x+8,fzx.y);
            writeText(playerInput);
            playerInput[contador]=0;
            gotoxy(TextWindow.x+8,fzx.y);
            writeText(playerInput);
            }
        waitForNoKey();
   }
   playerInput[contador-1]=' ';
   playerInput[contador]='0';
   //playerInput[contador+1]=0;
}

void fontStyle (BYTE style)
{
    switch (style)
    {
        case NORMAL:
        fzx.font = ff_utz_Handpress;
        break;
        case TITLE:
        fzx.font = ff_utz_ShadowFlower;
        break;
        case PLAYER:
        fzx.font = ff_utz_ShadowFlower;
        break;
    }
}

void hideGraphicsWindow()
{
    // Toma el tama�o completo de la pantalla...
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
