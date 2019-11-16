
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
	{"N€†v¬²»a, ÒuyÄßu©.",0}
};

token_t mensajesSistema_t [] =
{
	{"N€†v¬²»a, ÒuyÄßu©.^",0},
	{"Taïi$¾îy ",1},
	{"Eßribªå¨&rd¤ àÁ%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&mã Po­fav¯Ÿr¡b«º¾oÔœpÞaÙ¦.^",6},
	{"N€†ó¢n•«diÉcÚâ.^",7},
	{"¿Perdón?^",8},
	{"Lˆ ",9},
	{"(puesto)",10},
	{"ni³'¾objç®",11},
	{"/Segu©? ",12},
	{"/J¡g¦›²¡¼? ",13},
	{"Adiós...",14},
	{"OK^",15},
	{"[...]",16},
	{"HœÉÞiza§ ",17},
	{"ÅÝ½",18},
	{"s",19},
	{".^ ",20},
	{"LaŸuÎuaÚâ•› ",21},
	{"Ÿunµ",22},
	{"£„v€–…®^",23},
	{"N€™, ya„v…€–®^",24},
	{"Y«t¤¿ ",25},
	{"“ò…’o­aÁ%.^",26},
	{"N€™„va­m#¨ºs¦.^",27},
	{"“t¤g…®^",28},
	{"PŠsi ya„v€–o",29},
	{"S",30},
	{"N",31},
	{"Más...",32},
	{"> ",33},
	{"",34},
	{"ElÅiæp’¦a...^",35},
	{"Hªºgi§ ",36},
	{"éŸo³o ",37},
	{"MªÁiµ ",38},
	{"Dejo ",39},
	{"N€†pÆ¬mª",40},
	{"N€†Áíaèª",41},
	{"<T¤¿›m¦i»œºsœ¤·œÖ½s!",42},
	{"D g¹Ú»am¤ÕŸ a›m¦ia§",43},
	{"éµ ",44},
	{"Ah¯«n…È¢¾",45},
	{",",46},
	{" y ",47},
	{".",48},
	{"“t¤¿ ",49},
	{"£„v€–o ",50},
	{"",51},
	{"EÏ²…È¢¾",52},
	{"ni³'¾objeµ",53},
	{"ì‹o‡¤ºÎ¹§.^",54},
	{"ìËŠc¯rupt®^",55},
	{"Er©r› E/S. ì‹o‡g¹ê§.^",56},
	{"DiÉct¯io„n®^",57},
	{"Disº„n®",58},
	{"£ïÉ›Ñi‹o‡v#li§.^",59},
	{"£ïÉ›lÑi‹o: ",60},
	{"",61},
	{"/P¬dâ? Po­fav¯Ÿr¡b«º¾oÔœpÞaÙ¦.^",62},
	{"AÁ% ",63},
	{" ",64},
	{"están",65},
    {"D¤tžîy ",66},
    {"EnÚm«îy ",67},
    {"",68},
	{"N… Þ¿×¡ «ÁíarÜ.^",69},
	{"Po³o ",70},
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
	{"arena",   n_arena},
	{"suelo",   n_arena},
	{"expla",   n_arena},
	{"desie",   n_arena},
	{"piram",   n_piramide},
	{"pies",    n_cuerpo},
	{"pie",     n_cuerpo},
    {"cabez",  n_cuerpo},
	{"cejas",   n_cuerpo},
	{"brazo",   n_cuerpo},
	{"piern",   n_cuerpo},
	{"zapat",   n_cuerpo},
	{"suela",   n_cuerpo},
	{"tramp",   n_trampa},
	{"pinch",   n_pinchos},
	{"cuchi",   n_pinchos},
	{"aguja",   n_pinchos},
	{"acces",   n_acceso},
	{"altar",   n_altar},
	{"vasij",   n_vasija},
	{"recip",   n_vasija},
	{"urna",    n_vasija},
	{"urnas",    n_vasija},
	{"llama",   n_llama},
	{"fuego",   n_fuego},
	{"aceit",   n_aceite},
	{"serpi",   n_serpiente},
	{"cobra",   n_serpiente},
	{"bicha",   n_serpiente},
	{"arana",   n_arana},
	{"pared",   n_pared},
	{"muro",    n_pared},
	{"muros",   n_pared},
	{"esqui",   n_esquina},
	{"brech",   n_brecha},
	{"luz",     n_luz},
	{"abert",   n_abertura},
	{"apert",   n_abertura},
	{"sol",     n_sol},
	{"cielo",   n_sol},
	{"feret",   n_sepulcro},
	{"sepul",   n_sepulcro},
	{"tumba",   n_sepulcro},
	{"templ",   n_piramide},
	{"monum",   n_piramide},
	{"cafax",   n_cafax},
	{"aceps",   n_aceps},
	{"recin",   n_sala},
	{"sala",    n_sala},
	{"salas",   n_sala},
	{"techo",   n_techo},
	{"suelo",   n_suelo},
    {"entra",   n_entrada},
    {"puert",   n_entrada},
	{"pilar",   n_columna},
	{"colum",   n_columna},
	{"escal",   n_escalera},
	{"nubes",   n_nubes},
	{"nube",    n_nubes},
	{"pasad",   n_pasillo},
	{"corre",   n_pasillo},
	{"pasil",   n_pasillo},
	{"detal",   n_arte},
	{"jerog",   n_arte},
	{"arte",    n_arte},
	{"muest",   n_arte},
	{"picto",   n_arte},
	{"pintu",   n_arte},
	{"image",   n_arte},
	{"graba",   n_arte},
	{"autor",   n_arte},
	{"simbo",   n_arte},
	{"grand",   n_arte},
	{"majes",   n_arte},
	{"ojos",    n_ojo},
	{"ojo",     n_ojo},
	{"oscur",   n_oscuridad},
	{"banca",   n_soporte},
	{"sopor",   n_soporte},
	{"puent",   n_puente},
	{"pasar",   n_puente},
	{"colga",   n_puente},
	{"sima",    n_sima},
	{"preci",   n_sima},
	{"vacio",   n_sima},
	{"caida",   n_sima},
	{"rampa",   n_rampa},
	{"pendi",   n_pendiente},
	{"objet",   n_objeto},
    {"hueco",   n_hueco},
    {"aguje",   n_hueco},
    {"orifi",   n_hueco},
    {"ranur",   n_ranura},
	{"lumin",   n_luminaria},
	{"brasa",   n_brasa},
	{"carbo",   n_carbon},
	{"momia",   n_momia},
	{"fiamb",   n_momia},
	{"ataud",   n_ataud},
	{"tumba",   n_ataud},
	{"sarco",   n_ataud},
	{"mesa",    n_mesa},
	{"polvo",   n_polvo},
	{"anima",   n_animales},
	{"semil",   n_semilla},
	{"maiz",    n_maiz},
	{"anubi",   n_anubis},
	{"vivos",   n_vivos},
	{"farao",   n_farao},
	{"vida",    n_vida},
	{"antes",   n_antes},
	{"muert",   n_muerte},
	{"charc",   n_charco},
	{"agua",    n_charco},
	{"cofre",   n_cofre},
	{"cerra",   n_cerradura},
	{"ranur",   n_cerradura},
	{"cerro",   n_cerradura},
	{"copa",    n_copa},
	{"anill",   n_anillo},
	{"espad",   n_espada},
	{"cabez",   n_cabeza},
	{"piedr",   n_piedra},
	{"mano",    n_mano},
	{"manos",   n_mano},
	{"dedo",    n_dedo},
	{"falan",   n_dedo},
	{"dedos",   n_dedo},
	{"hueso",   n_hueso},
	{"rey",     n_rey},
    {"farao",   n_rey},
    {"pozo",    n_pozo},
    {"herra",   n_herramientas},
    {"linte",   n_linterna},
    {"barra",   n_barra},
    {"cuerd",   n_cuerda},
    {"soga",    n_cuerda},
    {"cabo",    n_cuerda},
    {"antor",   n_antorcha},
    {"peder",   n_pedernal},
    {"sanda",   n_sandalia},
    {"carta",   n_carta},
    {"teleg",   n_carta},
    {"nota",    n_carta},
    {"papel",   n_carta},
    {"bruju",   n_brujula},
    {"roca",    n_roca},
    {"bloqu",   n_roca},
    {"tabla",   n_tabla},
    {"mader",   n_tabla},
	{"trigo",	n_trigo},
	{"llave",	n_llave},
	{"tapa",	n_tapa},
	{"losa",    n_losa},
	{"poste",	n_poste},
	{"papir",	n_papiro},
	{"carto",   n_papiro},
	{"valle",   n_valle},
	{"monta",   n_valle},
	{"expla",   n_suelo},
	{"polea",   n_polea},
	{"rueda",   n_polea},
	{"mecan",   n_polea},
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
}
