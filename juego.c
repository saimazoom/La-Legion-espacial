
//
// ZHL. Escrita por KMBR.
// 2016-2019 KMBR
// ZHL is licensed under a Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)  license.
// http://creativecommons.org/licenses/by-nc-sa/4.0/

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

// C�digo local
// Si necesitamos c�digo en p�ginas de memoria hay que compilarlas como .bin y a�adirlas aqu� como extern
// Se llaman desde el c�digo usando: setRAMpage (n) y llamando a la funci�n, al terminar hay que volver siempre a la p�gina 0

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

// Tabla de im�genes del juego
img_t imagenes_t [] =
    {   
    { 0,0,0}
    };

// Tabla de localidades de la aventura
// 250 to 255 reservadas
// Regiones del juego...
// unsigned char *name;
//	unsigned char *descripcion;
//	unsigned char id;
//  unsigned char visitado
//	unsigned long int atributos; // 32bit

// �ltima localidad como ID 0 
loc_t localidades_t [] =
{
	{"Puente de mando","El interior de la nave est� iluminado d�bilmente por la consola de mando. Una luz ambarina ti�e los instrumentos de un color c�lido mientras en el exterior se abate una tormenta de hielo. El nodo central de la nave se encuentra bajando un tramo de escaleras al sur. ",l_puente, FALSE, 0x00000000},
	{"Nodo central ","La nave ha sido dise�ada de forma modular. El nodo central conecta el puente de mando con la esclusa al exterior al oeste, y la bodega al sur. Una tenue iluminaci�n proviene de las escaleras del puente del mando. ",l_nodo, FALSE, 0x00000000},
	{"Esclusa","La esclusa es el sistema de intercambio de presi�n entre el exterior y la zona habitable de la nave.",l_esclusa, FALSE, 0x00000000},
	{"Exterior","El cielo es un borr�n de nieve y cristales de hielo. La tormenta castiga la superficie en la zona oscura de Europa. La nave flota a pocos cent�metros de la superficie congelada. Al oeste se distingue una mole de metal que podr�a ser la entrada del almac�n.",l_exterior, FALSE, 0x00000000},
    {"Entrada al almac�n","Una mole de metal se encuentra enclavada en la superficie helada de Europa. ",l_almacen, FALSE, 0x00000000},
    {"Zona A1","Las estanter�as repletas de contenedores blancos crean una atm�sfera opresiva. Un pasillo negro al oeste da acceso a otra sala del almac�n.",l_zonaA1, FALSE, 0x00000000},
    {"Zona A2","El almac�n termina en una sala abovedada pintada de blanco. Aqu� hay aun m�s contenedores perfectamente ordenados en estanter�as.",l_zonaA2, FALSE, 0x00000000},
    {"","",0, FALSE, 0x00000000}
};

// Localidades para contenedores

// Tabla de conexiones...
// Se usan los ID de localidad para idenfiticar las conexiones

cnx_t conexiones_t [] =
{
// LOC | AL_N | AL_S | AL_E | AL_O | AL_NE | AL_NO | AL_SE | AL_SO | ARRIB | ABAJO
	{l_puente,{	0,		l_nodo,		0,		0,		0,		0,		0,		0,		0,		l_nodo}},
	{l_nodo,{l_puente,		l_bodega,		0,		l_esclusa,		0,		0,		0,		0,		l_puente,		0}},
	{l_esclusa,{0,		0,		l_nodo,		0,		0,		0,		0,		0,		0,		0}},
	{l_bodega,{l_nodo,		0,		0,		0,		0,		0,		0,		0,		l_nodo,		0}},
	{l_exterior,{0,		0,		l_esclusa,		0,		0,		0,		0,		0,		0,		0}},
	{l_entrada,{0,		0,		l_exterior,		0,		0,		0,		0,		0,		0,		0}},
	{l_zonaA1,{0,		0,		l_entrada,		l_zonaA2,		0,		0,		0,		0,		0,		0}},
	{l_zonaA2,{0,		0,		l_zonaA1,		0,		0,		0,		0,		0,		0,		0}},
	{0,{	0,		0,		0,		0,		0,		0,		0,		0,		0,		0}}
	};

// Tabla de mensajes de la aventura
// 1 to 255
// Text, message_id (0 t0 255)
// Messages can be printed directly in the code just calling the function writeText (unsigned char *string)
// More than one message table can be defined

token_t mensajes_t [] =
{
	{"E U R O P A",0},
	{"ZHL \n Entregamos su paquete en 24h. \n (c) 2016, 2019 KMBR. Release 4."},
	{"No veo nada en particular.",2},
	{"ZHL by KMBR",3},
	{"Descienden al nodo central.",4},
	{"Ascienden al puente de mando.",5},
	{"El m�dulo para comandar la nave.",6},
	{"La v�a l�ctea en nuestro caso.",7},
	{"La consola de mandos de la nave. Es un modelo bastante nuevo, el ordenador de abordo se encarga de la navegaci�n y todos los comandos se realizan por voz. En este momento la pantalla de la consola est� en negro.",8},
	{"-Funcionamos en modo de bajo consumo. La consola debe permanecer apagada -responde el ordenador.",9},
	{"Proviene de la consola de mandos. La consola est� en modo de bajo consumo. ",10},
	{"Nieve y hielo a 150 Celsius bajo cero.",11},
	{"El sistema t�rmico apenas puede evitar la formaci�n de cristales en el exterior del parabrisas.",12},
	{"Se forman en los gradientes t�rmicos del parabrisas de la nave.",13},
	{"La nave de reparto donde recorres la galaxia. ",14},
	{"-Controla la temperatura en el interior y en los instrumentos para evitar su deterioro -informa el ordenador.",15},
	{"Es uno de los dos trajes de supervivencia necesario para realizar EVA. El traje es completamente autom�tico y tiene una autonom�a de ocho horas. ",16},
	{"Paquetes a entregar en la Tierra.",17},
	{"Est� apagada.",18},
	{"-No sobrevivir� en Europa sin el traje protector.",19},
	{"-Debido a la contaminaci�n deja el traje antes de pasar al nodo central -te recuerda el ordenador.",20},
	{"La esclusa sirve para igualar la presi�n entre el exterior y el interior de la nave. ",21},
	{"Est� cerrada.",22},
	{"Est� abierta.",23},
	{"-La esclusa se abre con los controles manuales de la esclusa -informa el ordenador.",24}, 
	{"-La esclusa se cierra con los controles manuales de la esclusa -informa el ordenador. ",25},
	{"Pulsar para abrir la esclusa. ADVERTENCIA: USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"Pulsar para cerrar la esclusa.",27},
	{"-La esclusa ya est� abierta.",28},
	{"-Abriendo compuerta exterior y aislando el interior -dice el ordenador. La compuerta exterior se abre con un siseo mientras se igualan las presiones.",29},
	{"-Cerrando compuerta exterior- repite el ordenador",30},
	{"Una vez la compuerta exterior se ha cerrado, unos chorros de aire a presi�n surgen de las paredes para eliminar los contaminantes e igualar de nuevo la presi�n.",30},
	{"Un panel se abre y permite el acceso al interior de la nave.",31},
	{"-La esclusa ya est� cerrada -reporta el computador de abordo.",32},
	{"Apenas unos mil�metros de pl�stico y metal te separan del exterior.",33},
	{"-Fr�o al tacto.",34},
	{"Total oscuridad salvo por el brillo esquivo de los trozos de hielo que est�n cayendo.",35},
	{"La nave modular est�ndar de ZHL. Pintada de amarillo y con el logo de la compa��a en grandes letras rojas.",36},
	{"ZHL 24h",37},
	{"Con dificultad distingues el perfil de un edificio de metal recortado contra el cielo. ",38},
	{"En un lateral de la entrada un teclado num�rico ilumina levemente la oscuridad.",39},
	{"Por una abertura se desliza un ca��n l�ser que te apunta: TECLEE EL C�DIGO DE ACCESO. TIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"Un ca��n de aspecto peligroso sigue tus movimientos.",41},
	{"Todo son cajas blancas de tama�o similar. Las m�s grandes se encuentran en los estantes m�s bajos.",42},
	{"Alojan decenas de peque�os contenedores blancos.",43},
	{"Todo funcional. El espacio suficiente para mantener las condiciones necesarias para preservar materiales biol�gicos.",44},
	{"Una b�veda no muy alta forma el techo de esta sala.",45},
	{"Un paquete azul con un gran indicador de peligro biol�gico en el frontal. ",46},
	{"-Este es el paquete -susurra el ordenador en tu o�do.",47},
	{"-No puedo, las directivas de la empresa me lo impiden. ",48},
	{"Peligro biol�gico. Conservar a menos de 100 celsius bajo cero. No manipular sin protecci�n. No abrir. No golpear. Material fr�gil.",49},
	// Textos relativos al ordenador
	{"-Coordino todos los sistemas de la nave. Para hablar conmigo emplea: ordenador palabra clave. Algunas sugerencias de palabras clave son: ordenador ayuda, ordenador nombre, ordenador misi�n... -te responde servicial el ordenador de navegaci�n.",50},
	{"-Oh, vaya como no pens� en leer eso -dice el computador con falsa admiraci�n.",51},
	{" ",52},
	{"No noto nada en particular.",53},
	{"Nada que destacar.",54},
	{"No es especialmente interesante.",55},
	{"No sucede nada inesperado.",56},
	{"El aullido del viento se infiltra por el fuselaje.",57},
	{"-Buen trabajo -aprueba la voz satisfecha del ordenador.  ",58},
	{"-Ahora es momento de poner rumbo a Marte. Baja a la bodega de carga mientras reinicio los sistemas de la nave -dice el ordenador premura. ",59},
	{"Desciendo los escalones a la bodega y deposito el paquete junto a los dem�s pendientes de entrega. Al regresar descubro que la sala se ha cerrado.",60},
	{"-No es nada personal pero es momento de reciclar -dice la voz del ordenador- mientras un gas inunda la bodega y caes en un profundo sue�o.",61}, 
	{"Lo m�s duro es tener que reciclar sus piezas para la siguiente misi�n. Llegan a creerse humanos. En fin... -suspira el ordenador mientras recoge los restos de tu cuerpo con una robofregona.",62},
	{"-Central, aqu� Tod Connor -dice la voz- Volvemos a Marte con el paquete. Repito volvemos con el paquete. ",63},
	{"Hay dos botones: rojo y verde. Se utilizan para cerrar y abrir la esclusa al exterior. ",172},
	{"Paquetes que esperan su entrega.",173},
	{"No es momento de jugar al Sokoban.",174},
	{"-Voolare... ooh oooh -te devuelve cruel el eco de la nave.",175},
	{"-Cantare, ooh oooh -intentas entonar \n -Nel blu dipinto di blu...",176},
	{"S�lo escucho est�tica. La tormenta interfiere en las comunicaciones.",177},
	{"Estoy en la cara oculta, no veo J�piter.",178},
	{"Sat�lite helado e inh�spito.",179}, 
	{"La entrada al almac�n. ",180},
	{"Funciona con comandos de voz al ordenador: ordenador clave.",181}, 
	{"Es un bloque met�lico rectangular que se interna bajo tierra.",182}, 
	{"(en el teclado)",183},
	{"La puerta del almac�n ya est� abierta.",184},
	{"El teclado se ilumina en rojo. CODIGO INCORRECTO.",185}, 
	{"El teclado se ilumina en verde. CODIGO CORRECTO. El ca��n l�ser se repliega en su compartimento.",186}, 
	{"El ca��n l�ser comienza a calentarse.",187},
	{"El ca��n l�ser se prepara a disparar. ",188},
	{"El ca��n l�ser dispara. ",189},
	{"Pero nada sucede. Una voluta de humo y algunas chispas surgen del ca��n.",190},
	{"Son contenedores de transporte.",191}, 
	{"(cogiendo antes el traje)",192},
	{"-Entonces te quedar�as a solas en este lugar inh�spito -te recuerda el ordenador.",193},
	{"-Busco un paquete azul. ",194}
};

token_t mensajesSistema_t [] =
{
	{"No puedo ver nada, est� muy oscuro.^",0},
	{"Tambi�n hay ",1},
	{"Escribe tus �rdenes aqu�",2},
	{"",3},
	{"",4},
	{"",5},
	{"�C�mo? Por favor prueba con otras palabras.^",6},
	{"No puedo ir en esa direcci�n.^",7},
	{"�Perd�n?^",8},
	{"Llevo ",9},
	{"(puesto)",10},
	{"ning�n objeto.",11},
	{"�Seguro? ",12},
	{"�Juegas de nuevo? ",13},
	{"Adi�s...",14},
	{"OK^",15},
	{"[...]",16},
	{"Has realizado ",17},
	{" turno",18},
	{"s",19},
	{".^ ",20},
	{"La puntuaci�n es de ",21},
	{" punto",22},
	{"No llevo puesto eso.^",23},
	{"No puedo, ya llevo eso puesto.^",24},
	{"Ya tengo ",25},
	{"No veo eso por aqu�.^",26},
	{"No puedo llevar m�s cosas.^",27},
	{"No tengo eso.^",28},
	{"Pero si ya llevo puesto",29},
	{"S",30},
	{"N",31},
	{"M�s...",32},
	{"> ",33},
	{"",34},
	{"El tiempo pasa...^",35},
	{"He cogido ",36},
	{"Me pongo ",37},
	{"Me quito ",38},
	{"Dejo ",39},
	{"No puedo ponerme ",40},
	{"No puedo quitarme ",41},
	{"�Tengo demasiadas cosas en las manos!",42},
	{"Desgraciadamente pesa demasiado",43},
	{"Meto ",44},
	{"Ahora no est� en ",45},
	{",",46},
	{" y ",47},
	{".",48},
	{"No tengo ",49},
	{"No llevo puesto ",50},
	{"",51},
	{"Eso no est� en ",52},
	{"ning�n objeto",53},
	{"Fichero no encontrado.^",54},
	{"Fichero corrupto.^",55},
	{"Error de E/S. Fichero no grabado.^",56},
	{"Directorio lleno.^",57},
	{"Disco lleno.",58},
	{"Nombre de fichero no v�lido.^",59},
	{"Nombre del fichero: ",60},
	{"",61},
	{"�Perd�n? Por favor prueba con otras palabras.^",62},
	{"Aqu� ",63},
	{"est� ",64},
	{"est�n",65},
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
// �ltimo elemento debe ser 0

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
	// Nombres para el Vocabulario del juego,
    {"orden", n_ordenador},
	{"compu", n_ordenador},
	{"ia", n_ordenador},
	{"dot", n_ordenador},
	{"navi", n_ordenador}, 
	{"gps", n_ordenador},  
	{"galileo", n_ordenador},
	{"tom", n_ordenador},    
	{"tomtom", n_ordenador}, 
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
	{"ENSE�", 	36},
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
	{"VERTI",	86},  // T�rmino err�neo, pero ampliamente extendido
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
// No existe la limitaci�n de PAWS donde el objeto 1 siemmpre es la fuente de luz 
// La luz en ngpaws se calcula en funci�n del atributo de los objetos presentes en la localidad, puestos y llevados.
// Localidades de sistema: LOCATION_WORN,LOCATION_CARRIED, LOCATION_NONCREATED, LOCATION_HERE, CARRIED, HERE, NONCREATED, WORN

// Atributos con OR: aLight, aWear, aContainer, aNPC, aConcealed, aEdible, aDrinkable, aEnterable, aFemale, aLockable, aLocked, aMale, aNeuter, aOpenable, aOpen, aPluralName, aTransparent, aScenary, aSupporter, aSwitchable, aOn, aStatic, aExamined, aTaken, aDropped, aVisited, aTalked, aWore, aEaten, aPropio, aDeterminado

obj_t objetos_t[]=
{
    // ID, LOC, NOMBRE, NOMBREID, ADJID, PESO, ATRIBUTOS
    {o_Caja, l_zonaA2,"un paquete azul",     n_paquete, aAzul,   1,0x0000 },  
    {o_Traje, l_esclusa,"un traje presurizado",     n_traje, EMPTY_WORD,   1,0x0000 | aWear },  
	{o_Esclusa, l_esclusa,"la compuerta de la esclusa",     n_esclusa, EMPTY_WORD,   1,0x0000 | aStatic },  
	{o_Puerta, l_esclusa,"una puerta de metal",     n_puerta, EMPTY_WORD,   1,0x0000 | aStatic},  
	{o_Puerta, l_esclusa,"un bot�n rojo",     n_boton, aRojo,   1,0x0000 | aStatic | aConcealed},  
	{o_Puerta, l_esclusa,"un bot�n verde",     n_boton, aVerde,   1,0x0000 | aStatic | aConcealed},  
	{o_Puerta, NONCREATED,"un ca��n de vigilancia",     n_canon, EMPTY_WORD,   1,0x0000 | aStatic },  
	{o_Puerta, NONCREATED,"un teclado",     n_teclado, EMPTY_WORD,   1,0x0000 | aStatic},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x0000}
}; // Tabla de objetos de la aventura


typedef struct {
	BYTE *topic;
	BYTE *respuesta;
} tema_t;

// Tabla de conversaci�n con el ordenador 
tema_t ordenador_t[]= 
{
	{"Hola","-Hola, soy el ordenador de navegaci�n -responde una voz met�lica."},
	{"Adios","-Hasta pronto."},
	{"trabajo","-Soy el sistema de navegaci�n de la nave. "},
	{"yo/piloto/conductor/transportista","-Eres Tod Connor, el piloto de la nave. "},
	{"tormenta/parabrisas", "-La tormenta es moderada. No deber�a ser un problema para acceder al almac�n usando el traje de protecci�n."},
	{"Europa/luna",	"-Estamos en el sat�lite Joviano. -responde el ordenador."},
	{"Joviano/Jupiter",	"-Europa es un sat�lite de Jupiter. En la cara iluminada por J�piter el espect�culo es soberbio. Por desgracia nuestro encargo es en la cara oculta. "},
	{"cara/lado", "-Europa tiene una cara siempre orientada hacia J�piter."},
	{"donde", "-Est� en un almac�n, en el exterior. Tendr�s que salir con esta tormenta. "},
	{"Mision","-Tenemos que recoger un paquete en Europa y entregarlo en Marte antes de 24h -responde."},
	{"nombre",	"-Mi nombre es TOD. Si lo prefieres, puedes usar este nombre al hablar conmigo.  "},
	{"modelo/ordenador", "-Soy un modelo Cyberdine 1997.  Mi programador original fue el Dr. Guillermo Han de la Mega Corporation. Me ense�� a cantar una canci�n, �quieres o�rla?"},
	{"mega/megacorp/corporacion/ciberdine/cyberdine","-La empresa responsable de que t� y yo estemos conversando en Europa."},
	{"aventuras/conversacionales","-Me encantan las aventuras conversacionales."},
	{"if/fi/ficcion/interactiva","-Desconozco ese t�rmino, �te refieres a las conversacionales?"},
	{"graficas","-No est�n mal, pero no creo que puedas jugar a una mientras conduces."},
	{"transilvania","-No est� mal, pero es un poco corta para mi gusto. Prefiero 'la noche m�s larga', que dura unas 12h de juego de tiempo real."},
	{"isla",	"-Pero bueno, �si esa nunca la terminaron!. Recuerdo que uno de los autores, un tal UTO le hizo una visita al programador que termin� tan mal que destruyeron todo un bloque de oficinas. Pero esa es otra historia."},
	{"uto",	"-Realmente no tengo m�s datos sobre esta persona. Sin duda era una mente maestra para escapar a mis registros."},
	{"kmbr","-Un misterio, se rumorea que era un arenque rojo mutante. "},
	{"kno",	"-Un celebrado autor de c�mic que vivi� m�s de doscientos a�os. Ten�a un callo en el dedo tan descomunal que finalmente muri� aplastado por �l. Es un cl�sico, deber�as leer toda su obra varias veces."},
	{"dela/dla","-Un escriba del siglo XV, gracias a �l tenemos disponibles maravillas como 'Cuando com� queso negro' en franc�s."},
	{"frances/ingles/italiano/aleman",	"-Lenguas muertas, hoy en d�a todo el universo habla tecnollano."},
	{"tecnollano/castellano/espanol/mexicano", "-La lengua franca de nuestros d�as."},
	{"comic", "-Arte secuencial muy popular a finales del siglo XX. "},
	{"daniel/danixi", "-El responsable de la mega corporation."},
	{"obra", "-Hablemos de ello cuando termines tu misi�n."},
	{"aventura favorita", "-Es dif�cil elegir, se volvieron realmente populares a ra�z de la proliferaci�n de sistemas de navegaci�n en autom�viles, barcos y naves espaciales. "},
	{"jugar aventura", "-Te buscar� una realmente interesante una vez termines la misi�n."},
	{"cancion/oir/canta/tararea", "-Daisy... -Comienza a entonar sin demasiada fortuna."},
	{"guillermo", "-El ingeniero responsable de la interfaz humana de los sistemas de navegaci�n de la Mega corporation"},
	{"interfa",	"-Lo que usas para hablar conmigo."},
	{"viajar", "-Primero hay que recoger el paquete, luego pondr� rumbo a Marte. -te recuerda el ordenador."},
	{"entrada", "-La entrada est� hay fuera. Es posible que necesites alg�n c�digo de acceso para entrar."},
	{"codigo", "-No tengo ning�n dato en la orden de la central acerca del c�digo."},
	{"central", "-La central de ZEUR est� en la Tierra."},
	{"ZEUR", "-Es la empresa de reparto de paquetes en 24h que nos paga el sueldo y las piezas para seguir recorriendo
	el Universo."},
	{"Tierra", "-Salvo en las zonas protegidas se ha convertido en un conglomerado de mega-urbes. Un sitio peligroso, pero lleno de oportunidades." },
	{"almacen", "-Hemos aterrizado cerca de la entrada. Debes salir al exterior, entrar en el almac�n y volver con el paquete para que puedas terminar la misi�n. "},
	{"temperatura", "-En torno a 150�C bajo cero en el exterior. Te recomiendo que lleves el traje de superviviencia."},
	{"consola", "-La consola de mando muestra el estado de la nave y los controles manuales. Actualmente est� desactivada para ahorrar energ�a. "},
	{"activar consola", "-Es mejor esperar a completar la misi�n. Estamos en modo de bajo consumo."},
	{"desactivar consola", "-Ya est� desactivada. "},
	{"memoria", "-Es normal que no recuerdes mucho al comienzo de una misi�n. Pero no te preocupes de eso ahora, despu�s de unas jornadas de relax todo volver� a la normalidad."},
	{ "relax/jornadas/vacaciones","-Despu�s de este trabajo podr�s pasar unos d�as de relax en Marte."},
	{"marte","-Ya sabes, el planeta rojo. Bueno, anaranjado desde que dio comienzo la terraformaci�n."},
	{"venus/saturno/pluton/lunas/urano/neptuno/mercurio","-Es mejor que no salirse del tema de la misi�n. -responde"},
	{"terraformacion","-Hace unos a�os comenzaron la extracci�n de minerales, abrieron varias minas y comenzaron los trabajos de terraformaci�n."},
	{"minas","-Despu�s de la recogida debemos entregar el paquete en El Tenedor. Una de las mayores minas de Hierro y N�quel del Sistema Solar."},
	{"Tenedor","-Tambi�n se le conoce como el Tenedor del diablo. Es una mina gobernada por el sindicato unificado de miner�a de Marte. "},
	{"Hierro/Niquel","-Es un metal abundante pero muy preciado. Lo dif�cil es su transporte, pues es muy denso y cuesta bastante dinero extraerlo de la atm�sfera en la Tierra. "},
	{"sindicato","-Gobiernan con mano dura los precios de venta y los acuerdos de suministros. "},
	{"humanidad","-Se ha extendido por la galaxia. Pero le ten�is bastante apego al sistema Solar, que se mantiene como el centro de todas las operaciones."},
	{"operaciones","-Ya sabes suministros, paqueter�a, ocio..."},
	{"ocio", "-Aqu� nada de ocio, hay que terminar el trabajo."},
	{"paqueteria", "-Nuestro trabajo en ZEUR es entregar los paquetes en 24h"},
	{"suministros", "-Se han abierto varias minas en Marte con el objetivo de abaratar el precio de poner algunas materias primas en el espacio."},
	{"paquete", "-Seg�n la descripci�n del mensaje se trata de un paquete de 27cm x 29cm x 30cm que pesa 10Kg. "},
	{"recoger/recogida", "-Hemos aterrizado en la entrada del almac�n. Sugiero que salgas ah� fuera, llames a la puerta y recojas el paquete."},
	{"nave", "-Volamos en una nave de reparto de tipo Tesla. Es completamente el�ctrica, as� que mientras tengamos una estrella cerca podremos recargar las bater�as."},
	{"estrellas", "-La m�s cercana es Sol."},
	{"Sol", "-Es la estrella principal de este sistema. "},
	{"Sistema Solar", "-Es el sistema al que pertenece la Tierra. "},
	{"sistemas", "-Todos los sistemas en orden. Operamos en modo de bajo consumo."},
	{"ayuda", "-Para eso estoy aqu�, para ayudarte. Algunas palabras clave que puedes usar son: misi�n, J�piter, nombre, modelo, mensaje..."},
	{"mensaje/comanda/encargo/entrega"	"Tema: Env�o urgente al Tenedor de Marte. Contenido: Recogida en almac�n en coordenadas en Europa. Usar clave: 32768. Importante: Mantener a temperatura bajo cero. "},
	{"clave", "-Quiz� haya algo en el mensaje del encargo."},
	{"radiacion", "-No es un problema con el traje de supervivencia. Sin el la radiaci�n es tan elevada que no vivir�as m�s de un d�a. "},
	{"airlock/esclusa/boton/botones", "-La esclusa se opera manualmente. El bot�n verde cierra la esclusa y el rojo la abre.  Aseg�rate de llevar el traje de supervivencia puesto. "},
	{"comunicaciones", "-Debido a la fuerte radiaci�n nuestras comunicaciones s�lo funcionan en la nave. No estar� contigo ah� fuera. "},
	{"eva", "-Son las siglas de actividad extra-vehicular. Es cuando sales en misi�n fuera de la nave. "},
	{"traje/superviviencia/proteccion"	"-Lo encontrar�s en la esclusa listo para su uso. Recuerda no salir de la nave sin llevarlo puesto."},
	{"mierda/tacos/culo/joder/hija/puta/puton/hijo/comemierda", "-Esa acepci�n no forma parte de mi base de datos. -responde el ordenador con elegancia. "},
	{"siglas", "-Ya sabes, para acortar frases demasiado largas. "},
	{"calla", "-Sin problemas, ya no tarareo mas. -responde un poco dolido."},
	{"bodega", "-Donde almacenamos los paquetes para su distribuci�n."},
	{"temperatura/frigo/congelador/frigorifico/enfriar", "-Tenemos un frigor�fico dedicado a este tipo de paquetes. -responde despu�s de un breve silencio"},
	{0,0}
};

// ----------------------------------------------------------------
// Tabla de respuestas
// ----------------------------------------------------------------
char respuestas()
{
 //setRAMPage(0);
 //if (respuestas_pagina0()==FALSE)
  //  {
   // setRAMPage(1);
   // if (respuestas_pagina1()==TRUE) return TRUE;
   // }
   // else return TRUE;

// A�adir funciones de inyecci�n de comandos en modo DEBUG

// ordenador encender consola -> encender ordenador consola -> encender consola
if (fverbo==n_ordenador) {
	// Llamar al procesado de la tabla por tema...
	}

// Cosas que se pueden hacer con los objetos...
if (fverb== vExaminar && fnoun1== n_contenedor && fadj1 == aAzul && CNDpresent (o_Caja)) 
	{
		ACCmessage (46);
		return TRUE;
	}
// ---------------------------------------------------------------
// Descripciones com�nes para la nave
if (fverb==vAbrir && fnoun1== n_contenedor) 
	{
		ACCmessage(48);
		return TRUE;
	}

if (fverb==vExaminar && fnoun1==n_nave)	
	{
		if (CNDatlt (l_exterior)) { ACCmessage (14); return TRUE; }
		if (CNDatlt (l_almacen)) { ACCmessage(36); return TRUE;}
		// Si estamos dentro del almac�n no vemos la nave...
	}



// ---------------------------------------------------------------
// Cosas que hacer en las localidades...

// Puente de mando
if (flocation==l_puente)
	{


	}
// Nodo central 
if (flocation == l_nodo) 	
	{

	}
// Esclusa 
if (flocation == l_esclusa) 
	{

	}
// Bodega 
if (flocation==l_bodega)
	{

	}
// Exterior 
if (flocation==l_exterior)
	{

	}
// Entrada al almac�n
if (flocation==l_entrada)
	{

	}
// Zona A1
if (flocation==l_zonaA1)
	{

	}
// Zona A2
if (flocation==l_zonaA2)
	{

	}

 return FALSE;
}

// ----------------------------------------------------------
// Tabla de respuestas-post
// Se llama despu�s de ejecutar con �xito una entrada de la tabla de respuestas
// ----------------------------------------------------------

char respuestas_post()
{
 //setRAMPage(0);
 // respuestas_post_pagina0();
}

char proceso1() // Antes de la descripci�n de la localidad...
{
 // Muestra la pantalla...
 //ACCpicture(flags[flocation]);
 //setRAMPage(0);
 //proceso1_pagina0();
 //setRAMPage(1);
 //proceso1_pagina1();
 //setRAMPage(0);
}

char proceso1_post() // Despu�s de la descripci�n
{
 //setRAMPage(0);
 // Usar proceso en otras p�ginas require compilar c�digo por separado
 //proceso1_post_pagina0();
}

char proceso2() // Despu�s de cada turno, haya tenido o no la entrada en la tabla de respuestas
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
// A�adir men� de juego

// Inicializar variables
    initParser ();                // Inicializa el parser y la pantalla
    defineTextWindow (0,0,32,23); // Pantalla reducida en 128Kb, Gr�ficos + Texto
    ACCgoto(l_puente); // Localidad inicial, en el puente de mando
    flags[LOCATION_MAX] = 8; // N�mero m�s alto de localidad
    ACCability(10,20); // 10 objetos, 20 piedras

	ParserLoop (); // Pone en marcha el bucle principal
}
