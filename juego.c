
//#include <stdio.h>
#include <string.h>
//#include <spectrum.h>
#include "parser_defs.h"
#include "parser.h"

/* Allocate space for the stack */

#pragma output STACKPTR=24200
#pragma -reqpag=0
#pragma -no-expandz88
#pragma output CRT_ENABLE_CLOSE = 0    // do not close open files on exit (at this time this has no effect)
#pragma output CLIB_EXIT_STACK_SIZE = 0   // get rid of the exit stack (no functions can be registered with atexit() )
#pragma output CLIB_MALLOC_HEAP_SIZE = 0  // malloc's heap will not exist
#pragma output CLIB_STDIO_HEAP_SIZE = 0  // stdio's heap will not exist (you will not be able to open files)
#pragma output CLIB_FOPEN_MAX = -1  // don't even create the open files list
#pragma output CRT_ENABLE_RESTART = 1

// Código local
char respuestas();
char respuestas_post();
char proceso1();
char proceso1_post();
char proceso2();
char proceso2_post();

// Variables que necesitamos del parser...
extern unsigned char flags[255]; // Flags 60...250 Disponibles para el usuario

// Flags del Juego
#include "juego_flags.h"

// Tabla de imágenes del juego
img_t imagenes_t [] =
    {   
    { 0,0,0}
    };

// Tabla de localidades de la aventura

// Regiones del juego...

loc_t localidades_t [] =
{
	// L1     
	{"","",1}, 
    {"","",0}
};

// Localidades para contenedores

// Tabla de conexiones...
// Se usan los ID de localidad para idenfiticar las conexiones

cnx_t conexiones_t [] =
{
// LOC | AL_N | AL_S | AL_E | AL_O | AL_NE | AL_NO | AL_SE | AL_SO | ARRIB | ABAJO
	{1,{	0,		0,		0,		0,		0,		0,		0,		0,		0,		0}},
	{0,{	0,		0,		0,		0,		0,		0,		0,		0,		0,		0}}
	};

// Tabla de mensajes de la aventura

token_t mensajes_t [] =
{
	{"No puedo ver nada, está muy oscuro.",0}
};

token_t mensajesSistema_t [] =
{
	{"No puedo ver nada, está muy oscuro.^",0},
	{"También hay ",1},
	{"Escribe tus órdenes aquí",2},
	{"",3},
	{"",4},
	{"",5},
	{"¿Cómo? Por favor prueba con otras palabras.^",6},
	{"No puedo ir en esa dirección.^",7},
	{"¿Perdón?^",8},
	{"Llevo ",9},
	{"(puesto)",10},
	{"ningún objeto.",11},
	{"¿Seguro? ",12},
	{"¿Juegas de nuevo? ",13},
	{"Adiós...",14},
	{"OK^",15},
	{"[...]",16},
	{"Has realizado ",17},
	{" turno",18},
	{"s",19},
	{".^ ",20},
	{"La puntuación es de ",21},
	{" punto",22},
	{"No llevo puesto eso.^",23},
	{"No puedo, ya llevo eso puesto.^",24},
	{"Ya tengo ",25},
	{"No veo eso por aquí.^",26},
	{"No puedo llevar más cosas.^",27},
	{"No tengo eso.^",28},
	{"Pero si ya llevo puesto",29},
	{"S",30},
	{"N",31},
	{"Más...",32},
	{"> ",33},
	{"",34},
	{"El tiempo pasa...^",35},
	{"He cogido ",36},
	{"Me pongo ",37},
	{"Me quito ",38},
	{"Dejo ",39},
	{"No puedo ponerme ",40},
	{"No puedo quitarme ",41},
	{"¡Tengo demasiadas cosas en las manos!",42},
	{"Desgraciadamente pesa demasiado",43},
	{"Meto ",44},
	{"Ahora no está en ",45},
	{",",46},
	{" y ",47},
	{".",48},
	{"No tengo ",49},
	{"No llevo puesto ",50},
	{"",51},
	{"Eso no está en ",52},
	{"ningún objeto",53},
	{"Fichero no encontrado.^",54},
	{"Fichero corrupto.^",55},
	{"Error de E/S. Fichero no grabado.^",56},
	{"Directorio lleno.^",57},
	{"Disco lleno.",58},
	{"Nombre de fichero no válido.^",59},
	{"Nombre del fichero: ",60},
	{"",61},
	{"¿Perdón? Por favor prueba con otras palabras.^",62},
	{"Aquí ",63},
	{"está ",64},
	{"están",65},
    {"Dentro hay ",66},
    {"Encima hay ",67},
    {"",68},
	{"No es algo que pueda quitarme.^",69},
	{"Pongo ",70},
    {"",0}
};

#define SYSMESS_NONSENSE_SENTENCE 62
#define SYSMESS_NPCLISTSTART 63
#define SYSMESS_NPCLISTCONTINUE 64
#define SYSMESS_NPCLISTCONTINUE_PLURAL 65
#define SYSMESS_INSIDE_YOUCANSEE 66
#define SYSMESS_OVER_YOUCANSEE 67
#define SYSMESS_YOUCANTTAKEOBJECTFROM 69
#define SYSMESS_YOUPUTOBJECTON 70


// Tablas de vocabulario
// Nombre propios, sustantivos...

token_t nombres_t [] =
{
    {"norte",           nNorte},  //0
	{"n",               nNorte},
	{"sur",             nSur},    //2
	{"s",               nSur},
	{"este",            nEste},   //4
	{"e",               nEste},
	{"oeste",           nOeste},  //6
	{"o",               nOeste},
	{"noreste",         nNoreste}, //8
	{"w",               nOeste},
	{"noroeste",        nNorOeste}, //10
	{"ne",              nNoreste},
	{"sureste",         nSurEste},	 //12
	{"se",              nSurEste},
	{"suroeste",        nSurOeste},  // 14
    {"suroe",           nSurOeste},
    {"arriba",          nArriba},   // 16
	{"nw",              nNorOeste},
	{"abajo",           nAbajo},   // 18
	{"no",              nNorOeste},
	{"sudes",           nSurEste},
	{"suroe",           nSurOeste},
	{"sw",              nSurOeste},
	{"so",              nSurOeste},
	{"u",               nArriba},
	{"up",              nArriba},
	{"d",               nAbajo},
	{"down",            nAbajo},
    {"i",               14},
    {"inven",           14},
	{"inv",         14 },
	{"punto",       15},
	{"puntu",       15},
	{"conta",       15},
	{"turno",       16},
    {"todo",        20},
    {"",0}
};

// Verbos
// VOCABULARIO
token_t verbos_t [] =
{
	{"subir",	10},
	{"ascen",	10},
	{"ascie",	10},
	{"subet",	10},
	{"sube",   	10},
	{"bajar",  	11},
	{"baja",    11},
	{"desce",	11},
	{"desci",  	11},
	{"bajat",  	11},
	{"entra",	12},
	{"enter",	12},
	{"intro",	12},
	{"adent",   12},
	{"dentr",   12},
	{"inter",	12},
	{"salir",	13},
	{"sal",		13},
	{"exit",	13},
	{"fuera",   13},
	{"afuer",   13},
    {"coger",	20},
    {"coge",	20},
    {"tomar",	20},
    {"toma",	20},
    {"take",	20},
    {"dejar",	21},
    {"deja",	21},
    {"solta",	21},
    {"suelt",	21},
    {"drop",	21},
    {"quita",	22},
    {"sacat",	22},
    {"sacar",	22},
    {"desvi",	22},
    {"desve",	22},
//    {"SENTA",	23},
//    {"SENTA",	23},
//    {"SENTA",	23},
//    {"SIENT",	23},
    {"l",		24},
    {"look",	24},
    {"m",		24},
    {"mirar",	24},
    {"mira",	24},
    {"quit",	25},
    {"fin",		25},
    {"save",	26},
    {"graba",	26},
    {"salva",	26},
	{"guard",	26},
	{"load",	27},
	{"carga",	27},
	{"ramsa",	28},
	{"graba",	28},
	{"ramlo",	29},
	{"carga",	29},
	{"x",       30},
	{"exami",	30},
	{"ex",		30},
	{"inspe",	30},
	{"obser",	30},
	{"decir", 	31},
	{"di",		31},
	{"habla", 	31},
	{"respo",  	31},
	{"lanza",	32},
	{"tirar",	32},
	{"arroj",	32},
	{"empuj",	33},
	/*
	{"AYUDA",	34},
	{"HELP",	34},
	*/
	{"girar",  	35},
	{"gira",    35},
	{"rota",	35},
	{"rotar",	35},
	/*
	{"VOLTE",	35},
	{"MOSTR",	36},
	{"MUEST",	36},
	{"ENSEÑ", 	36},
	{"ESCUC", 	37},
	{"OIR",		37},
	{"OYE",		37},
	{"COMER",	38},
	{"COME",	38},
	{"COMET",	38},
	{"TRAGA",	38},
	{"INGIE",	38},
	{"INGER",	38},
	{"MASTI",	38},
	{"BEBER",	39},
	{"BEBE",	39},
	{"BEBET",	39},
	{"BEBER",	39},
	{"TOCAR",	40},
	{"TOCA",	40},
	{"ACARI",	40},
	{"PALPA",	40},
	{"SALID",	41},
	{"EXITS",   41},
	{"X",		41},
	*/
	{"oler",	42},
	{"huele",	42},
	{"olfat",	42},
	{"husme", 	42},
	{"esper",	43},
	{"z",		43},
/*
	{"CANTA",	44},
	{"SALTA", 	45},
	{"BRINC",	45},
*/
	{"ataca",	46},
	{"agred",	46},
	{"matar",	46},
	{"mata",	46},
	{"asesi",	46},
	{"estra",	46},
	{"patea",	46},
	{"pisot",	46},
	{"tortu",	46},
	{"noque",	46},
	{"lucha",	46},
/*
	{"ORINA",	47},
	{"MEAR",	47},
	{"MEA",		47},
	{"MEATE",	47},
	{"MEARS",	47},
	{"MEART",	47},
	{"DEFEC",	47},
	{"CAGAR",	47},
	{"ERUCT",	47},
	{"VOMIT",	47},
	{"ESCUP",	48},
*/
	{"agita",	49},
	{"menea",	49},
	{"sacud",	49},
	{"remov",	49},
	{"remue",	49},
	{"balan",	49},
/*
	{"COLUM",	50},
	{"EXCAV",	51},
	{"CAVAR",	51},
	{"CAVA",	51},
	{"DESEN",	51},
	{"ENTER",	51},
	{"ENTIE",	51},
	{"CORTA",	52},
	{"RASGA",	52},
	{"LEVAN",	53},
	*/
	{"atar",	54},
	{"ata",		54},
	{"enlaz",	54},
	{"anuda",	54},
	/*
	{"LLENA",	55},
	{"RELLE",	55},
	{"NADAR",	56},
	{"NADA",	56},
	{"TREPA",	57},
	{"ESCAL",	57},
	{"RETOR",	58},
	{"RETUE",	58},
	{"TORCE",	58},
	{"TUERC",	58},
	{"REZAR",	59},
	{"REZA",	59},
	{"ORAR",	59},
	{"ORA",		59},
	{"PENSA",	60},
	{"PIENS",	60},
	{"DORMI",	61},
	{"DUERM",	61},
	{"DORMI",	61},
	{"DESCA",	61},
	{"RONCA",	61},
	{"ECHAT",	61},
	{"ECHAR",	61},
	{"BESAR",	62},
	{"BESA",	62},
	{"CHUPA",	63},
	{"LAMER",	63},
	{"LAME",	63},
	{"PROBA",	63},
	{"PRUEB",	63},
	{"PALAD",	63},
	{"SABOR",	63},
	*/
	{"abri",	64},
	{"abre",	64},
    {"abrir",   64},
	{"open",	64},
	{"cerrar",	65},
	{"cierra",	65},
	{"close",	65},
	{"quema",	66},
	{"encen",	66},
	{"encie",	66},
	{"incen",	66},
	{"prend",	66},
	{"apaga",	67},
	{"extin",	67},
	{"sofoc",	67},
	{"trans",	68},
	{"rompe",	69},
	{"parti",	69},
	{"parte",	69},
	{"quebr",	69},
	{"quieb",	69},
	{"destr",	69},
	{"versi",	70},
	{"poner",	71},
	{"pon",		71},
	{"ponte",	71},
	{"ponse",	71},
	{"poner",	71},
	{"viste",	71},
	{"vesti",	71},
	{"golpe",	72},
	{"dar",		73},
	{"da",		73},
	{"dase",	73},
	{"darse",	73},
	{"darte",	73},
	{"dale",	73},
	{"darle",	73},
	{"ofrec",	73},
	{"regal",	73},
	{"meter",	74},
	{"mete", 	74},
	{"intro",	74},
	{"inser",	74},
	{"echa",	74},
	{"echar",	74},
/*
	{"LLAMA",	76},
	{"GRITA",	77},
	{"CHILL",	77},
	{"REGIS",	78},
	{"REBUS",	78},
	{"ARRAN",	79},
	{"ESTIR",	79},
	{"USAR",	80},
	{"USA",		80},
	{"UTILI",	80},
	{"MATAT",	81},
	{"MATAR",	81},
	{"SUICI",	81},
	{"XYZZY",	82},
	{"ARRAS",	83},
	{"REGIS",	84},
	{"MIRAT",	85},
	{"MIRAR",	85},
	{"EXAMI",	85},
	{"VACIA",	86},
	{"VERTE",	86},
	{"VERTI",	86},  // Término erróneo, pero ampliamente extendido
	{"VIERT",	86},
	{"DESPI",	87},
	{"DESPE",	87},
	{"ESPAB",	87},
	{"LAVAT",	88},
	{"LAVAR",	88},
	{"LAVAR",	88},
	{"LIMPI",	88},
	{"INSUL",	89},
	{"INCRE",	89},
	*/
	{"ir",		90},
	{"ve",		90},
	{"vete",	90},
	{"irte",	90},
	{"irse",	90},
	{"camin",	90},
	{"anda",	90},
	{"andar",	90},
	{"corre",	90},
	{"huir",	90},
	{"huye",	90},
	{"dirig",	90},
	/*
	{"ESCON",	91},
	{"OCULT",	91},
	{"ESCON",	91},
	{"OCULTA",	91},
	{"ESCON",	92},
	{"OCULT",	92},
	{"LLORA",	93},
	{"LLORI",	93},
	{"SOLLO",	93},
	{"RECOR",	94},
	{"ACORD",	94},
	{"ACUER",	94},
	{"SOPLA",	95},
	{"DOBLA",	96},
	{"DESDO",	97},
	*/
	{"desat",	98},
	/*
	{"UNIR",	99},
	{"UNE",		99},
	{"JUNTA",	99},
	{"ACERC",	99},
	{"ARRIM",	99},
	{"APROX",	99},
	{"REUNE",	99},
	{"REUNI",	99},
	{"SEPAR",	100},
	{"LIMPI",	101},
	{"FROTA",	101},
	{"LAVAR",	101},
	{"LAVA",	101},
	{"PULE",	101},
	{"PULIR",	101},
	{"FREGA",	101},
	{"FRIEG",	101},
	{"RASCA",	102},
	{"RASPA",	102},
	{"CONEC",	103},
	{"ACTIV",	103},
	{"DESCO",	104},
	{"DESAC",	104},
	{"ABRAZ",	105},
	{"COMPRA",	106},	{"ADQUI",	106},
	{"CONSU",	107},
	{"PREGU",	108},
	*/
	{"lee",		109},
	{"leer",	109},
	{"leers",	109},
	{"leert",	109},
	{"leete",	109},
	{"mover",	110},
	{"mueve",	110},
	{"despl",	110},
	/*
	{"APRET",	111},
	{"APRIE",	111},
	{"ESTRU",	111},
	{"BAILA",	112},
	{"DANZA",	112},
	{"SALUD",	113},
	{"LEVAN",	114},
	{"ESPAN",	115},
	{"SECA",	116},
	{"SECAR",	116},
	{"COLOC",	117},
	{"MACHA",	118},
	*/
	{"asust", 120},
	{"moja",121},
	{"mojar",121},
	{"empap",121},
	{"impre",121},
    {"",0}
};

// Tabla de objetos
obj_t objetos_t[]=
{
    // ID, LOC, NOMBRE, NOMBREID, ADJID, PESO, ATRIBUTOS
    {1, LOCATION_NONCREATED,"linterna",     n_linterna,EMPTY_WORD,   1,0x0000 | aLight | aSwitchable | aFemale  },  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x0000}
}; // Tabla de objetos de la aventura

char respuestas()
{
 //setRAMPage(0);
 //if (respuestas_pagina0()==FALSE)
  //  {
   // setRAMPage(1);
   // if (respuestas_pagina1()==TRUE) return TRUE;
   // }
   // else return TRUE;

 return FALSE;
}

char respuestas_post()
{
 //setRAMPage(0);
 // respuestas_post_pagina0();
}

char proceso1() // Antes de la descripción de la localidad...
{
 // Muestra la pantalla...
 //ACCpicture(flags[flocation]);
 //setRAMPage(0);
 //proceso1_pagina0();
 //setRAMPage(1);
 //proceso1_pagina1();
 //setRAMPage(0);
}

char proceso1_post() // Después de la descripción
{
 //setRAMPage(0);
 //proceso1_post_pagina0();
}

char proceso2() // Después de cada turno
{
 //setRAMPage(0);
 //proceso2_pagina0();
 //setRAMPage(1);
 //proceso2_pagina1();
 //setRAMPage(0);
}

void main (void)
{
     clear_screen(INK_YELLOW | PAPER_BLACK);
// Añadir menú de juego

// Inicializar variables
    defineTextWindow (0,0,32,24); // Pantalla reducida en 128Kb, Gráficos + Texto
//    ACCgoto(l_Desierto); // Localidad inicial, en el desierto
	ParserLoop (); // Pone en marcha el bucle principal
}
