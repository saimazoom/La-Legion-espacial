
//
// ZHL. Escrita por KMBR.
// 2016-2019 KMBR
// This code is licensed under a Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)  license.
// http://creativecommons.org/licenses/by-nc-sa/4.0/

//#include <stdio.h>
#include <string.h>
//#include <spectrum.h>
#include "parser_defs.h"
#include "parser.h"
// Flags del Juego
#include "juego_flags.h"

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

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Código local
// Si necesitamos código en páginas de memoria hay que compilarlas como .bin y añadirlas aquí como extern
// Se llaman desde el código usando: setRAMpage (n) y llamando a la función, al terminar hay que volver siempre a la página 0

char respuestas();
char respuestas_post();
char proceso1();
char proceso1_post();
char proceso2();
char proceso2_post();


// Variables que necesitamos del parser...
// Se pueden declarar más tablas de flags para el juego pero el parser
// sólo trabaja con esta. 
extern unsigned char flags[255]; // Flags 60...250 Disponibles para el usuario

// Tabla de imágenes del juego
extern unsigned char *L05_img;
#asm
_L05_img:
BINARY "./res/lExterior.scr.rcs.zx7"
#endasm

// id, page, memory pointer
img_t imagenes_t [] = {
    { 1,0, L05_img},   
    { 2,0, L05_img},   
    { 3,0, L05_img},   
 	{ 4,0, L05_img},   
    { 5,0, L05_img},   
    { 6,0, L05_img},   
    { 7,0, L05_img},   
    { 8,0, L05_img},   
    { 0,0,0}
    };

// Tabla de regiones
// Regiones del juego...
//unsigned char region_exterior [] = { 4,6,7,0 };
//unsigned char region_entrada [] = { 13,10,17,14,9,0 };
//unsigned char region_superior [] = { 3,8,23,26,27,0 };
//unsigned char region_inferior [] = { 12,15,19,2,5,11,21,16,19,18,27,28,25,24,30,1,31,20,0 };

// Tabla de localidades de la aventura
// 250 to 255 reservadas
// Regiones del juego...
// unsigned char *name;
//	unsigned char *descripcion;
//	unsigned char id;
//  unsigned char visitado
//	unsigned long int atributos; // 32bit

// última localidad como ID 0 

loc_t localidades_t [] =
{
	{"Puente de mando","En el exterior de la nave se abate una tormenta de hielo. El nodo central se encuentra bajando un tramo de escaleras. ",lPuente, FALSE, 0x00000000},
	{"Nodo central ","La nave ha sido diseñada de forma modular. El nodo central conecta el puente de mando con la esclusa al oeste y la bodega al sur. Una tenue iluminación proviene de las escaleras del puente del mando. ",lNodo, FALSE, 0x00000000},
	{"Esclusa","La esclusa es el sistema de intercambio de presión entre el exterior y la zona habitable de la nave.",lEsclusa, FALSE, 0x00000000},
	{"Bodega de carga","La zona de carga tiene espacio suficiente para atender pequeños envíos entre particulares. Hay varios paquetes que esperan su entrega. ", lBodega, FALSE, 0x00000000},
	{"Exterior","El cielo es un borrón de nieve y cristales de hielo. La tormenta castiga la superficie en la zona oscura de Europa. La nave flota a pocos centímetros de la superficie congelada. Al oeste se distingue una mole de metal que podría ser la entrada del almacén.",lExterior, FALSE, 0x00000000},
    {"Entrada al almacén","Una mole de metal se encuentra enclavada en la superficie helada de Europa. ",lAlmacen, FALSE, 0x00000000},
    {"Zona A1","Las estanterías repletas de contenedores blancos crean una atmósfera impersonal. Un pasillo negro al oeste da acceso a otra sala del almacén.",lZonaA1, FALSE, 0x00000000},
    {"Zona A2","El almacén termina en una sala abovedada pintada de blanco. Aquí hay aun más contenedores blancos perfectamente ordenados en estanterías.",lZonaA2, FALSE, 0x00000000},
    {"","",0, FALSE, 0x00000000}
};

// Localidades para contenedores

// Tabla de conexiones...
// Se usan los ID de localidad para idenfiticar las conexiones
cnx_t conexiones_t [] =
{
// LOC | AL_N | AL_S | AL_E | AL_O | AL_NE | AL_NO | AL_SE | AL_SO | ARRIB | ABAJO | ENTRAR | SALIR 
	{lPuente,{	0,		lNodo,		0,		0,		0,		0,		0,		0,		0,		lNodo,	0,	0}},
	{lNodo,{lPuente,		lBodega,		0,		lEsclusa,		0,		0,		0,		0,		lPuente,		0,0,0}},
	{lEsclusa,{0,		0,		lNodo,		0,		0,		0,		0,		0,		0,		0,0,0}},
	{lBodega,{lNodo,		0,		0,		0,		0,		0,		0,		0,		lNodo,		0,0,0}},
	{lExterior,{0,		0,		lEsclusa,		lEntrada,		0,		0,		0,		0,		0,		0,0,0}},
	{lEntrada,{0,		0,		lExterior,		0,		0,		0,		0,		0,		0,		0,0,0}},
	{lZonaA1,{0,		0,		lEntrada,		lZonaA2,		0,		0,		0,		0,		0,		0,0,lEntrada}},
	{lZonaA2,{0,		0,		lZonaA1,		0,		0,		0,		0,		0,		0,		0,0,0}},
	{0,{	0,		0,		0,		0,		0,		0,		0,		0,		0,		0,0,0}}
	};

// Tabla de mensajes de la aventura
// 1 to 255
// Text, message_id (0 t0 255)
// Messages can be printed directly in the code just calling the function writeText (unsigned char *string)
// More than one message table can be defined

token_t mensajes_t [] =
{
	{"ZHL^ Entregamos su paquete en 24h. ^ (c) 2016, 2019 KMBR. Release 4.",1},
	{"No veo nada en particular.",2},
	{"ZHL by KMBR",3},
	{"Descienden al nodo central.",4},
	{"Ascienden al puente de mando.",5},
	{"El módulo para comandar la nave.",6},
	{"La vía láctea en nuestro caso.",7},
	{"La consola de mandos de la nave. Es un modelo bastante nuevo, el ordenador de abordo se encarga de la navegación y todos los comandos se realizan por voz. En este momento la pantalla de la consola está en negro.",8},
	{"-Funcionamos en modo de bajo consumo. La consola debe permanecer apagada -responde el ordenador.",9},
	{"Proviene de la consola de mandos. La consola está en modo de bajo consumo. ",10},
	{"Nieve y hielo a 150 Celsius bajo cero.",11},
	{"El sistema térmico apenas puede evitar la formación de cristales en el exterior del parabrisas.",12},
	{"Se forman en los gradientes térmicos del parabrisas de la nave.",13},
	{"La nave de reparto donde haces tu ruta. ",14},
	{"-Controla la temperatura en el interior y en los instrumentos para evitar su deterioro -informa el ordenador.",15},
	{"Es uno de los dos trajes de supervivencia necesario para realizar EVA. El traje es completamente automático y tiene una autonomía de ocho horas. ",16},
	{"Paquetes a entregar en la Tierra.",17},
	{"Está apagada.",18},
	{"-No sobreviviré en Europa sin el traje protector.",19},
	{"-Debido a la contaminación deja el traje antes de pasar al nodo central -te recuerda el ordenador.",20},
	{"La esclusa sirve para igualar la presión entre el exterior y el interior de la nave. Se controla con el bóton rojo para cerrar y el botón verde para abrir. ",21},
	{"Está cerrada.",22},
	{"Está abierta.",23},
	{"-La esclusa se abre con los controles manuales -informa el ordenador.",24}, 
	{"-La esclusa se cierra con los controles manuales -informa el ordenador. ",25},
	{"Pulsar para abrir la esclusa. ^ADVERTENCIA: ANTES DE ABRIR USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"Pulsar para cerrar la esclusa.",27},
	{"-La esclusa ya está abierta.",28},
	{"-Abriendo compuerta exterior y aislando el interior -dice el ordenador. La compuerta exterior se abre con un siseo mientras se igualan las presiones.",29},
	{"-Cerrando compuerta exterior- repite el ordenador",30},
	{"Una vez la compuerta exterior se ha cerrado, unos chorros de aire a presión surgen de las paredes para eliminar los contaminantes e igualar de nuevo la presión.",30},
	{"Un panel se abre y permite el acceso al interior de la nave.",31},
	{"-La esclusa ya está cerrada -reporta el computador de abordo.",32},
	{"Apenas unos milímetros de plástico y metal te separan del exterior.",33},
	{"-Frío al tacto.",34},
	{"Total oscuridad salvo por el brillo esquivo de los trozos de hielo que están cayendo.",35},
	{"La nave modular estándar de ZHL. Pintada de amarillo y con el logo de la compañía en grandes letras rojas.",36},
	{"ZHL 24h",37},
	{"Con dificultad distingues el perfil de un edificio de metal recortado contra el cielo. ",38},
	{"En un lateral de la entrada un teclado numérico ilumina levemente la oscuridad.",39},
	{"Por una abertura se desliza un cañón láser que te apunta: TECLEE EL CóDIGO DE ACCESO. TIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"Un cañón de aspecto peligroso sigue tus movimientos.",41},
	{"Todo son cajas blancas de tamaño similar. Las más grandes se encuentran en los estantes más bajos.",42},
	{"Alojan decenas de pequeños contenedores blancos.",43},
	{"Todo funcional. El espacio suficiente para mantener las condiciones necesarias para preservar materiales biológicos.",44},
	{"Una bóveda no muy alta forma el techo de esta sala.",45},
	{"Un paquete azul con un gran indicador de peligro biológico en el frontal. ",46},
	{"-Este es el paquete -susurra el ordenador en tu oído.",47},
	{"-No puedo, las directivas de la empresa me lo impiden. ",48},
	{"Peligro biológico. Conservar a menos de 100 celsius bajo cero. No manipular sin protección. No abrir. No golpear. Material frágil.",49},
	// Textos relativos al ordenador
	{"-Coordino todos los sistemas de la nave. Para hablar conmigo emplea: ordenador palabra clave. Algunas sugerencias de palabras clave son: ordenador ayuda, ordenador nombre, ordenador misión... -te responde servicial el ordenador de navegación.",50},
	{"-Oh, vaya como no pensé en leer eso -dice el computador con falsa admiración.",51},
	{" ",52},
	{"No noto nada en particular.",53},
	{"Nada que destacar.",54},
	{"No es especialmente interesante.",55},
	{"No sucede nada inesperado.",56},
	{"El aullido del viento resuena en el fuselaje.",57},
	{"-Buen trabajo -aprueba la voz satisfecha del ordenador.  ",58},
	{"-Ahora es momento de poner rumbo a Marte. Baja a la bodega de carga mientras reinicio los sistemas de la nave -dice el ordenador premura. ",59},
	{"Desciendo los escalones a la bodega y deposito el paquete junto a los demás pendientes de entrega. Al regresar descubro que la sala se ha cerrado.",60},
	{"-No es nada personal pero es momento de reciclar -dice la voz del ordenador- mientras un gas inunda la bodega y caes en un profundo sueño.",61}, 
	{"Lo más duro es tener que reciclar sus piezas para la siguiente misión. Llegan a creerse humanos. En fin... -suspira el ordenador mientras recoge los restos de tu cuerpo con una robofregona.",62},
	{"-Central, aquí Tod Connor -dice la voz- Volvemos a Marte con el paquete. Repito volvemos con el paquete. ",63},
	{"Hay dos botones: rojo y verde. Se utilizan para cerrar y abrir la esclusa al exterior. ",172},
	{"Los siguientes paquetes para entregar.",173},
	{"No es momento de jugar al Sokoban.",174},
	{"-Voolare... ooh oooh -te devuelve cruel el eco de la nave.",175},
	{"-Cantare, ooh oooh -intentas entonar ^ -Nel blu dipinto di blu...",176},
	{"Sólo escucho estática. La tormenta interfiere en las comunicaciones.",177},
	{"Estoy en la cara oculta, no veo Júpiter.",178},
	{"Satélite helado e inhóspito.",179}, 
	{"La entrada al almacén. ",180},
	{"Funciona con comandos de voz al ordenador: ordenador clave.",181}, 
	{"Es un bloque metálico rectangular que se interna bajo tierra.",182}, 
	{"(en el teclado)",183},
	{"La puerta del almacén ya está abierta.",184},
	{"El teclado se ilumina en rojo. CODIGO INCORRECTO.",185}, 
	{"El teclado se ilumina en verde. CODIGO CORRECTO. El cañón láser se repliega en su compartimento.",186}, 
	{"El cañón láser comienza a calentarse.",187},
	{"El cañón láser se prepara a disparar. ",188},
	{"El cañón láser dispara. ",189},
	{"Pero nada sucede. Una voluta de humo y algunas chispas surgen del cañón.",190},
	{"Son contenedores de transporte.",191}, 
	{"(cogiendo antes el traje)",192},
	{"-Entonces te quedarías a solas en este lugar inhóspito -te recuerda el ordenador.",193},
	{"-Sólo necesito un paquete azul. ",194},
	{"La superficie es lisa, sólo se activa con el teclado.", 195},
	{"E U R O P A",196},
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
	{"Ahora tengo ",36},
	{"Me pongo ",37},
	{"Me quito ",38},
	{"Dejo ",39},
	{"No puedo ponerme ",40},
	{"No puedo quitarme ",41},
	{"¡Tengo demasiadas cosas en las manos!",42},
	{"Desgraciadamente pesa demasiado.",43},
	{"Meto",44},
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
	{"Aquí ",SYSMESS_NPCLISTSTART},
	{"está ",SYSMESS_NPCLISTCONTINUE},
	{"están",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"Dentro hay ",SYSMESS_INSIDE_YOUCANSEE},
    {"Encima hay ",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"No es algo que pueda quitarme.^",69},
	{"Pongo ",SYSMESS_YOUPUTOBJECTON },
    {"No es algo que pueda cogerse.^",SYSMESS_YOUCANNOTTAKE},
	{"No parece que pueda moverse.^", SYSMESS_CANNOTMOVE},
	{"Llevo las manos vacías.^", SYSMESS_CARRYNOTHING},
	{"",0}	
};

// Tablas de vocabulario
// Nombre propios, sustantivos...
// último elemento debe ser 0
#define nNorte  1
#define nSur 	2
#define nEste	3
#define nOeste  4
#define nNoreste 5
#define nNorOeste 6
#define nSurEste 7
#define nSurOeste 8
#define nArriba 9
#define nSubir 9
#define nAbajo 10
#define nBajar 10
#define nEntrar 11
#define nEntra 11
#define nAdentro 11
#define nDentro 11
#define nSalir 12
#define nSal 12 


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
	{"up",              nNorOeste},
	{"abajo",           nAbajo},   // 18
	{"no",              nNorOeste},
	{"entrar",			nEntrar}, // 20
	{"entra",			nEntrar},
	{"salir",			nSalir}, // 22
	{"sal",				nSalir},
	{"ascie",	nArriba},
	{"subet",	nArriba},
	{"sube",   	nArriba},
	{"bajar",  	nAbajo},
	{"baja",    nAbajo},
	{"desce",	nAbajo},
	{"desci",  	nAbajo},
	{"bajat",  	nAbajo},
	{"entra",	nEntrar},
	{"enter",	nEntrar},
	{"intro",	nEntrar},
	{"adent",   nEntrar},
	{"dentr",   nEntrar},
	{"inter",	nEntrar},
	{"salir",	nSalir},
	{"sal",		nSalir},
	{"exit",	nSalir},
	{"fuera",   nSalir},
	{"afuer",   nSalir},
    {"i",               nInventario},
    {"inven",           nInventario},
	{"inv",         nInventario },
	{"punto",       nPuntos},
	{"puntu",       nPuntos},
	{"conta",       nPuntos},
	{"turno",       nTurnos},    
	// Names < 20 can be used as verbs
	// Nombres para el Vocabulario del juego,
	{"todo",        nTodo},
	{"puerta", nPuerta},
	{"boton", nBoton},
	{"escal", nEscalera},
	{"pared", nPared},
	{"suelo", nSuelo},
	{"techo", nTecho},
	{"luz", nLuz},
	{"haz", nLuz},
	{"parab", 	nParabrisas},
	{"caja",	nCaja},
	{"paque",	nPaquete},
	{"conte",	nContenedor},
	{"cielo",	nCielo},
	{"nave",	nNave},
	{"nodo",	nNodo},
	{"puent",	nPuente},
	{"torme",	nTormenta},
	{"Europ",	nEuropa},
	{"Luna",	nLuna},
	{"Lunas",	nLuna},
	{"Satel",	nSatelite},
	{"Jupit",	nJupiter},
	{"Jovia",	nJoviano},
	{"Cara",	nCara},
	{"Lado",	nLado},
    {"inter", 	nInterior},
	{"almac",	nAlmacen},
	{"mole",	nMole},
	{"edifi",	nEdificio},
	{"orden", 	nOrdenador},
	{"compu", 	nOrdenador},
	{"ia", 		nOrdenador},
	{"dot", 	nOrdenador},
	{"navi", 	nOrdenador}, 
	{"gps", 	nOrdenador},  
	{"galileo", nOrdenador},
	{"tom", 	nOrdenador},    
	{"tomtom", 	nOrdenador}, 
	{"inter", 	nInterior},
	{"conso", 	nConsola},
	{"puent", 	nConsola},
	{"mando",	 nConsola},
	{"siste",	nSistema},
	{"esclu", 	nEsclusa},
	{"airlo", 	nEsclusa},
	{"traje",	nTraje},
	{"bodega", nBodega},
	{"boveda", nBoveda},
	{"estant",	nEstanteria},
	{"camara",	nCamara},
	{"canon",	nCanon},
	{"32768",	n32768},
	{"tecla",	nTeclas},
	{"exter",	nExterior},
	{"fuera",	nFuera},
	{"afuer",	nFuera},
	{"etiqu",	nEtiqueta},
	{"indic",	nIndicador},
	{"panta", nPantalla},
	{"instr", nPantalla},
	{"contr", nControles},
	{"",0}
};

// Verbos
// VOCABULARIO
token_t verbos_t [] =
{
    {"coger",	vCoger},
    {"coge",	vCoger},
    {"tomar",	vCoger},
    {"toma",	vCoger},
    {"take",	vCoger},
    {"dejar",	vDejar},
    {"deja",	vDejar},
    {"solta",	vDejar},
    {"suelt",	vDejar},
    {"drop",	vDejar},
    {"quita",	vQuitar},
    {"sacat",	vQuitar},
    {"sacar",	vSacar},
    {"desvi",	vQuitar},
    {"desve",	vQuitar},
//    {"SENTA",	23},
//    {"SENTA",	23},
//    {"SENTA",	23},
//    {"SIENT",	23},
    {"l",		vMirar},
    {"look",	vMirar},
    {"m",		vMirar},
    {"mirar",	vMirar},
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
	{"x",       vExaminar},
	{"exami",	vExaminar},
	{"ex",		vExaminar},
	{"inspe",	vExaminar},
	{"obser",	vExaminar},
	{"decir", 	vDecir},
	{"di",		vDecir},
	{"habla", 	vDecir},
	{"respo",  	vDecir},
	{"manda",	vDecir},
	{"lanza",	vLanzar},
	{"tira", 	vLanzar},
	{"tirar",	vLanzar},
	{"arroj",	vLanzar},
	{"empuj",	vEmpujar},
	{"apret",	vEmpujar},
	{"pulsa",	vPulsar},
	/*
	{"AYUDA",	34},
	{"HELP",	34},
	*/
	{"girar",  	vGirar},
	{"gira",    vGirar},
	{"rota",	vGirar},
	{"rotar",	vGirar},
	/*
	{"VOLTE",	35},
	{"MOSTR",	36},
	{"MUEST",	36},
	{"ENSEÑ", 	36},
	*/
	{"escuc", 	vEscuchar},
	{"oir",		vEscuchar},
	{"oye",		vEscuchar},
	/*
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
	{"oler",	vOler},
	{"huele",	vOler},
	{"olfat",	vOler},
	{"husme", 	vOler},
	{"esper",	vEsperar},
	{"z",		vEsperar},
	{"canta",	vCantar},
	{"salta", 	vSaltar},
	{"brinc",	vSaltar},
	{"ataca",	vAtacar},
	{"agred",	vAtacar},
	{"matar",	vAtacar},
	{"mata",	vAtacar},
	{"asesi",	vAtacar},
	{"estra",	vAtacar},
	{"patea",	vAtacar},
	{"pisot",	vAtacar},
	{"tortu",	vAtacar},
	{"noque",	vAtacar},
	{"lucha",	vAtacar},
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
	{"agita",	49},
	{"menea",	49},
	{"sacud",	49},
	{"remov",	49},
	{"remue",	49},
	{"balan",	49},
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
	{"atar",	54},
	{"ata",		54},
	{"enlaz",	54},
	{"anuda",	54},
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
	{"abri",	vAbrir},
	{"abre",	vAbrir},
    {"abrir",   vAbrir},
	{"cerrar",	vCerrar},
	{"cierra",	vCerrar},
//	{"quema",	66},
	{"encen",	vEncender},
	{"encie",	vEncender},
	{"incen",	vEncender},
	{"prend",	vEncender},
	{"apaga",	vApagar},
	{"extin",	vApagar},
	{"sofoc",	vApagar},
//	{"trans",	68},
	{"rompe",	vRomper},
	{"parti",	vRomper},
	{"parte",	vRomper},
	{"quebr",	vRomper},
	{"quieb",	vRomper},
	{"destr",	vRomper},
//	{"versi",	70},
	{"poner",	vPoner},
	{"pon",		vPoner},
	{"ponte",	vPoner},
	{"ponse",	vPoner},
	{"pone",	vPoner},
	{"viste",	vVestir},
	{"vesti",	vVestir},
	{"golpe",	vAtacar},
	{"dar",		vDar},
	{"da",		vDar},
	{"dase",	vDar},
	{"darse",	vDar},
	{"darte",	vDar},
	{"dale",	vDar},
	{"darle",	vDar},
	{"ofrec",	vDar},
//	{"regal",	73},
	{"meter",	vMeter},
	{"mete", 	vMeter},
	{"intro",	vMeter},
	{"inser",	vMeter},
	{"echa",	vMeter},
	{"echar",	vMeter},
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
	{"ir",		vIr},
	{"ve",		vIr},
	{"vete",	vIr},
	{"irte",	vIr},
	{"irse",	vIr},
	{"camin",	vIr},
	{"anda",	vIr},
	{"andar",	vIr},
	{"corre",	vIr},
	{"huir",	vIr},
	{"huye",	vIr},
	{"dirig",	vIr},
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
	{"desat",	98},
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
	{"lee",		vLeer},
	{"leer",	vLeer},
	{"leers",	vLeer},
	{"leert",	vLeer},
	{"leete",	vLeer},
	{"mover",	vEmpujar},
	{"mueve",	vEmpujar},
	{"despl",	vEmpujar},
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
	{"asust", 120},
	{"moja",121},
	{"mojar",121},
	{"empap",121},
	{"impre",121},
*/
	{"tecle", vTeclear},
	{"escri", vEscribir},
    {"",0}
};

// Tabla de adjetivos
token_t adjetivos_t [] =
{
	{"peque", aPequeno},
	{"grand", aGrande},
	{"viejo", aViejo},
	{"vieja", aVieja},
	{"nuevo", aNuevo},
	{"nueva", aNueva},
	{"duro", aDuro},
	{"dura", aDura},
	{"bland", aBlando},
	{"corto", aCorto},
	{"corta", aCorta},
	{"largo", aLargo},
	{"larga", aLarga},
	{"azul", aAzul},
	{"verde", aVerde},
	{"negro", aNegro},
	{"rojo", aRojo},
	{"verde", aVerde},
	{"amari", aAmarillo},
	{"termi", aTermico},
	{"frio", aFrio},
	{"calie", aCaliente},
	{"",0}
};


// Tabla de objetos
// No existe la limitación de PAWS donde el objeto 1 siemmpre es la fuente de luz 
// La luz en ngpaws se calcula en función del atributo de los objetos presentes en la localidad, puestos y llevados.
// Localidades de sistema: LOCATION_WORN,LOCATION_CARRIED, LOCATION_NONCREATED, LOCATION_HERE, CARRIED, HERE, NONCREATED, WORN

// Atributos con OR: aLight, aWear, aContainer, aNPC, aConcealed, aEdible, aDrinkable, aEnterable, aFemale, aLockable, aLocked, aMale, aNeuter, aOpenable, aOpen, aPluralName, aTransparent, aScenary, aSupporter, aSwitchable, aOn, aStatic, aExamined, aTaken, aDropped, aVisited, aTalked, aWore, aEaten, aPropio, aDeterminado

obj_t objetos_t[]=
{
    // ID, LOC, NOMBRE, NOMBREID, ADJID, PESO, ATRIBUTOS
    {oCaja, lZonaA2,"paquete azul",     nPaquete, aAzul,   1,0x0000 | aMale | aDeterminado},  
    {oTraje, lEsclusa,"traje presurizado",     nTraje, EMPTY_WORD,   1,0x0000 | aWear| aMale | aDeterminado},  
	{oEsclusa, lEsclusa,"compuerta de la esclusa", nEsclusa, EMPTY_WORD,   1,0x0000 | aStatic | aFemale | aDeterminado},  
	{oPuerta, lEntrada,"puerta de metal",     nPuerta, EMPTY_WORD,   1,0x0000 | aStatic | aFemale},  
	{obotonrojo, lEsclusa,"botón rojo",     nBoton, aRojo,   1,0x0000 | aStatic | aConcealed | aMale},  
	{obotonverde, lEsclusa,"botón verde",     nBoton, aVerde,   1,0x0000 | aStatic | aConcealed | aMale},  
	{oCanon, NONCREATED,"cañón de vigilancia",     nCanon, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
	{oTeclado, NONCREATED,"teclado",     nTeclado, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x0000}
}; // Tabla de objetos de la aventura

// Una tabla para hablar con el ordenador, se puede usar la misma técnica para definir listas de atrezzo y ahorrarse cientos de 'examinar objeto'.

// Tabla de conversación con el ordenador 
tema_t ordenador_t[]= 
{
	{"Hola","-Hola, soy el ordenador de navegación -responde una voz metálica."},
	{"Adios","-Hasta pronto."},
	{"trabajo","-Soy el sistema de navegación de la nave. "},
	{"yo/piloto/conductor/transportista","-Eres Tod Connor, el piloto de la nave. "},
	{"tormenta/parabrisas", "-La tormenta es moderada. No debería ser un problema para acceder al almacén usando el traje de protección."},
	{"Europa/luna",	"-Estamos en el satélite Joviano. -responde el ordenador."},
	{"Joviano/Jupiter",	"-Europa es un satélite de Jupiter. En la cara iluminada por Júpiter el espectáculo es soberbio. Por desgracia nuestro encargo es en la cara oculta. "},
	{"cara/lado", "-Europa tiene una cara siempre orientada hacia Júpiter."},
	{"donde", "-Está en un almacén, en el exterior. Tendrás que salir con esta tormenta. "},
	{"Mision","-Tenemos que recoger un paquete en Europa y entregarlo en Marte antes de 24h -responde."},
	{"nombre",	"-Mi nombre es TOD. Si lo prefieres, puedes usar este nombre al hablar conmigo.  "},
	{"modelo/ordenador", "-Soy un modelo Cyberdine 1997.  Mi programador original fue el Dr. Guillermo Han de la Mega Corporation. Me enseñó a cantar una canción, ¿quieres oírla?"},
	{"mega/megacorp/corporacion/ciberdine/cyberdine","-La empresa responsable de que tú y yo estemos conversando en Europa."},
	{"aventuras/conversacionales","-Me encantan las aventuras conversacionales."},
	{"if/fi/ficcion/interactiva","-Desconozco ese término, ¿te refieres a las conversacionales?"},
	{"graficas","-No están mal, pero no creo que puedas jugar a una mientras conduces."},
	{"transilvania","-No está mal, pero es un poco corta para mi gusto. Prefiero 'la noche más larga', que dura unas 12h de juego de tiempo real."},
	{"isla",	"-Pero bueno, ¡si esa nunca la terminaron!. Recuerdo que uno de los autores, un tal UTO le hizo una visita al programador que terminó tan mal que destruyeron todo un bloque de oficinas. Pero esa es otra historia."},
	{"uto",	"-Realmente no tengo más datos sobre esta persona. Sin duda era una mente maestra para escapar a mis registros."},
	{"kmbr","-Un misterio, se rumorea que era un arenque rojo mutante. "},
	{"kno",	"-Un celebrado autor de cómic que vivió más de doscientos años. Tenía un callo en el dedo tan descomunal que finalmente murió aplastado por él. Es un clásico, deberías leer toda su obra varias veces."},
	{"dela/dla","-Un escriba del siglo XV, gracias a él tenemos disponibles maravillas como 'Cuando comí queso negro' en francés."},
	{"frances/ingles/italiano/aleman",	"-Lenguas muertas, hoy en día todo el universo habla tecnollano."},
	{"tecnollano/castellano/espanol/mexicano", "-La lengua franca de nuestros días."},
	{"comic", "-Arte secuencial muy popular a finales del siglo XX. "},
	{"daniel/danixi", "-El responsable de la mega corporation."},
	{"obra", "-Hablemos de ello cuando termines tu misión."},
	{"aventura favorita", "-Es difícil elegir, se volvieron realmente populares a raíz de la proliferación de sistemas de navegación en automóviles, barcos y naves espaciales. "},
	{"jugar aventura", "-Te buscaré una realmente interesante una vez termines la misión."},
	{"cancion/oir/canta/tararea", "-Daisy... -Comienza a entonar sin demasiada fortuna."},
	{"guillermo", "-El ingeniero responsable de la interfaz humana de los sistemas de navegación de la Mega corporation"},
	{"interfa",	"-Lo que usas para hablar conmigo."},
	{"viajar", "-Primero hay que recoger el paquete, luego pondré rumbo a Marte. -te recuerda el ordenador."},
	{"entrada", "-La entrada está hay fuera. Es posible que necesites algún código de acceso para entrar."},
	{"codigo", "-No tengo ningún dato en la orden de la central acerca del código."},
	{"central", "-La central de ZEUR está en la Tierra."},
	{"ZEUR", "-Es la empresa de reparto de paquetes en 24h que nos paga el sueldo y las piezas para seguir recorriendo el Universo."},
	{"Tierra", "-Salvo en las zonas protegidas se ha convertido en un conglomerado de mega-urbes. Un sitio peligroso, pero lleno de oportunidades." },
	{"almacen", "-Hemos aterrizado cerca de la entrada. Debes salir al exterior, entrar en el almacén y volver con el paquete para que puedas terminar la misión. "},
	{"temperatura", "-En torno a 150ºC bajo cero en el exterior. Te recomiendo que lleves el traje de superviviencia."},
	{"consola", "-La consola de mando muestra el estado de la nave y los controles manuales. Actualmente está desactivada para ahorrar energía. "},
	{"activar consola", "-Es mejor esperar a completar la misión. Estamos en modo de bajo consumo."},
	{"desactivar consola", "-Ya está desactivada. "},
	{"memoria", "-Es normal que no recuerdes mucho al comienzo de una misión. Pero no te preocupes de eso ahora, después de unas jornadas de relax todo volverá a la normalidad."},
	{ "relax/jornadas/vacaciones","-Después de este trabajo podrás pasar unos días de relax en Marte."},
	{"marte","-Ya sabes, el planeta rojo. Bueno, anaranjado desde que dio comienzo la terraformación."},
	{"venus/saturno/pluton/lunas/urano/neptuno/mercurio","-Es mejor que no salirse del tema de la misión. -responde"},
	{"terraformacion","-Hace unos años comenzaron la extracción de minerales, abrieron varias minas y comenzaron los trabajos de terraformación."},
	{"minas","-Después de la recogida debemos entregar el paquete en El Tenedor. Una de las mayores minas de Hierro y Níquel del Sistema Solar."},
	{"Tenedor","-También se le conoce como el Tenedor del diablo. Es una mina gobernada por el sindicato unificado de minería de Marte. "},
	{"Hierro/Niquel","-Es un metal abundante pero muy preciado. Lo difícil es su transporte, pues es muy denso y cuesta bastante dinero extraerlo de la atmósfera en la Tierra. "},
	{"sindicato","-Gobiernan con mano dura los precios de venta y los acuerdos de suministros. "},
	{"humanidad","-Se ha extendido por la galaxia. Pero le tenéis bastante apego al sistema Solar, que se mantiene como el centro de todas las operaciones."},
	{"operaciones","-Ya sabes suministros, paquetería, ocio..."},
	{"ocio", "-Aquí nada de ocio, hay que terminar el trabajo."},
	{"paqueteria", "-Nuestro trabajo en ZEUR es entregar los paquetes en 24h"},
	{"suministros", "-Se han abierto varias minas en Marte con el objetivo de abaratar el precio de poner algunas materias primas en el espacio."},
	{"paquete", "-Según la descripción del mensaje se trata de un paquete de 27cm x 29cm x 30cm que pesa 10Kg. "},
	{"recoger/recogida", "-Hemos aterrizado en la entrada del almacén. Sugiero que salgas ahí fuera, llames a la puerta y recojas el paquete."},
	{"nave", "-Volamos en una nave de reparto de tipo Tesla. Es completamente eléctrica, así que mientras tengamos una estrella cerca podremos recargar las baterías."},
	{"estrellas", "-La más cercana es Sol."},
	{"Sol", "-Es la estrella principal de este sistema. "},
	{"Sistema Solar", "-Es el sistema al que pertenece la Tierra. "},
	{"sistemas", "-Todos los sistemas en orden. Operamos en modo de bajo consumo."},
	{"ayuda", "-Para eso estoy aquí, para ayudarte. Algunas palabras clave que puedes usar son: misión, Júpiter, nombre, modelo, mensaje..."},
	{"mensaje/comanda/encargo/entrega"	"Tema: Envío urgente al Tenedor de Marte. Contenido: Recogida en almacén en coordenadas en Europa. Usar clave: 32768. Importante: Mantener a temperatura bajo cero. "},
	{"clave", "-Quizá haya algo en el mensaje del encargo."},
	{"radiacion", "-No es un problema con el traje de supervivencia. Sin el la radiación es tan elevada que no vivirías más de un día. "},
	{"airlock/esclusa/boton/botones", "-La esclusa se opera manualmente. El botón verde cierra la esclusa y el rojo la abre.  Asegúrate de llevar el traje de supervivencia puesto. "},
	{"comunicaciones", "-Debido a la fuerte radiación nuestras comunicaciones sólo funcionan en la nave. No estaré contigo ahí fuera. "},
	{"eva", "-Son las siglas de actividad extra-vehicular. Es cuando sales en misión fuera de la nave. "},
	{"traje/superviviencia/proteccion"	"-Lo encontrarás en la esclusa listo para su uso. Recuerda no salir de la nave sin llevarlo puesto."},
	{"mierda/tacos/culo/joder/hija/puta/puton/hijo/comemierda", "-Esa acepción no forma parte de mi base de datos. -responde el ordenador con elegancia. "},
	{"siglas", "-Ya sabes, para acortar palabras demasiado largas. "},
	{"calla", "-Sin problemas, ya no tarareo mas. -responde un poco dolido."},
	{"bodega", "-Donde almacenamos los paquetes para su distribución."},
	{"temperatura/frigo/congelador/frigorifico/enfriar", "-Tenemos un frigorífico dedicado a este tipo de paquetes. -responde después de un breve silencio"},
	{0,0}
};

// ----------------------------------------------------------------
// Tabla de respuestas
// ----------------------------------------------------------------
char respuestas()
{
 BYTE aux;
 //setRAMPage(0);
 //if (respuestas_pagina0()==FALSE)
  //  {
   // setRAMPage(1);
   // if (respuestas_pagina1()==TRUE) return TRUE;
   // }
   // else return TRUE;

// Añadir funciones de inyección de comandos en modo DEBUG

//; Sólo podemos hablar con el ordenador en la nave
//; ORDENADOR, palabra_clave

// ordenador encender consola -> encender ordenador consola -> encender consola
if (fnombre1==nOrdenador) {
	// Llamar al procesado de la tabla por tema...
	// ordenador encender consola -> encender ordenador consola -> encender consola
	// ordenador palabra_clave
	// Fuera del alcance...
	if (CNDatgt (lBodega)) { ACCmessage (177); DONE; }
	// Comandos al ordenador
	if (fverbo==vAbrir)
	{
		if (fnombre2==nEsclusa) { ACCmessage (132); DONE;}
	}

	if (fverbo==vApagar) { ACCmessage (192); DONE; }
	if (fverbo==vEncender && fnombre2==nConsola) { ACCmessage (105); DONE; }
	if (fverbo==vCerrar)
	{

	}
	// Preguntas al ordenador
	//if (aux=buscador_tema(ordenador_t, nombres_t[fnombre2]))
	//{
	//	writeText (ordenador_t[aux].respuesta);
	//	DONE;
	//}	
	ACCmessage (50);
	DONE;
	}

//-------------------------------------------------------------
// Cosas que se pueden hacer con los objetos...

if (fverbo== vExaminar) 
	{
		if (fnombre1== nContenedor  && CNDpresent (oCaja)) 
		{
			ACCmessage (46);
			DONE;
		}
		if (fnombre1==nIndicador && CNDpresent(oCaja)) 
		{
			ACCmessage (49);
			DONE;
		}
		if (fnombre1==nTraje && CNDpresent(oTraje)) { ACCmessage (16); DONE; }
	}

if (fverbo==vPoner && fnombre1==nTraje && CNDpresent(oTraje))
	{
		if (CNDnotcarr(oTraje) && CNDnotworn(oTraje))
		{
			ACCmessage (192);
			ACCget (oTraje);
		}
	}

// Quitar el traje...
if (fverbo==vQuitar && fnombre1==nTraje && CNDworn(oTraje))
{
	if (CNDatgt(lBodega)) { ACCmessage(19); DONE; }
}

if (fverbo==vAbrir && fnombre1== nContenedor) 
	{
		ACCmessage(48);
		DONE;
	}

// ---------------------------------------------------------------
// Descripciones comúnes para la nave
if (fverbo==vExaminar)  {
	if (fnombre1==nNave)	
	{
		if (CNDatlt (lExterior)) { ACCmessage (14); return TRUE; }
		if (CNDatlt (lAlmacen)) { ACCmessage(36); return TRUE;}
		// Si estamos dentro del almacén no vemos la nave...
	}

	if (fnombre1==nPared || fnombre1==nSuelo) 
	{
		if (CNDatlt(lExterior)) { ACCmessage (33); DONE; }
			else { ACCmessage (179); DONE; }
	}

	if (fnombre1==nTecho || fnombre1==nCielo) {
		if (CNDatlt(lExterior)) { ACCmessage (33); DONE;}
			else { ACCmessage(178); DONE; }
	}

}

if (fverbo==vSaltar) { ACCmessage(56); DONE; }
if (fverbo==vEscuchar) 
{
	if (CNDatlt (lExterior)) { ACCmessage (57); DONE; }
	ACCmessage(56);
	DONE;
}

if (fverbo==vCantar) 
{
	if (CNDatlt(lExterior)) { ACCmessage (175); DONE;}
		else { ACCmessage (176); DONE; }
}

// ---------------------------------------------------------------
// Cosas que hacer en las localidades...
// --------------------------------------------------
// Puente de mando
// --------------------------------------------------

if (flocalidad==lPuente)
	{
		if (fverbo==vTeclear) { ACCmessage (181); DONE; }
		// Atrezzo 
		if (fverbo==vExaminar) 
		{
			if (fnombre1==nSistema && fadjetivo1==aTermico ) 
			{
				ACCmessage(15); DONE;
			}

			if (fnombre1==nParabrisas)
			{
				ACCmessage (12); DONE;
			}

			if (fnombre1==nCristales) { ACCmessage (13); DONE; }
			if (fnombre1==nEscaleras) { ACCmessage (4); DONE; }
			if (fnombre1==nPantalla || fnombre1==nInterior || fnombre1==nConsola || fnombre1==nControles) 
			{
				ACCmessage (8); DONE;
			}	
			if (fnombre1==nLuz) { ACCmessage (10); DONE; }		
			if (fnombre1==nTormenta) { ACCmessage (11); DONE; }
		}

		if (fverbo==vEncender && (fnombre1==nPantalla || fnombre1==nConsola)) { ACCmessage (9); DONE; }
		if (fverbo==vIr && fnombre1==nNodo) { ACCgoto(lNodo); DONE;	}
	}
// --------------------------------------------------
// Nodo central 
// --------------------------------------------------

if (flocalidad == lNodo) 	
	{
		if (fverbo==vExaminar) 
		{
			if (fnombre1==nBodega) { ACCwriteln ("Al sur."); DONE;}
			if (fnombre1==nEsclusa) { ACCwriteln ("Al oeste."); DONE;}
			if (fnombre1==nEscaleras || fnombre1==nPuente) 
			{
				ACCmessage(5);
				DONE;
			}
			if (fnombre1==nLuz) { ACCwriteln ("Proviene del puente de mando."); DONE; }
		}
		if (fverbo==vIr) 
		{			
			if (fnombre1==nPuente) 
				{
				ACCgoto (lPuente);
				DONE;
				}
			if (fnombre1==nEsclusa)
			{
				ACCgoto (lEsclusa);
				DONE;				
			}
			if (fnombre1==nBodega)
			{
				ACCgoto(lBodega);
				DONE;
			}
		}

	// Escena de casi-final...
	if (CNDcarried(oCaja) && flags[fCasifin]==0)
		{
			ACCmessage (58);
			flags[fCasifin]=1;
			ACCanykey();
			ACCmessage (59);
			DONE;
		}

	}

// --------------------------------------------------
// Esclusa 
// --------------------------------------------------
if (flocalidad == lEsclusa) 
	{
	// Sinónimos...
	if (fverbo==vIr && fnombre1==nExterior) { fverbo = vSalir; }
	if (fverbo==nOeste) { fverbo = vSalir; }
	if (fverbo==nEste) { fverbo = vIr; fnombre1=nNodo; }
	// Puzzle de la esclusa y ponerse el traje
	// No podemos quitarnos el traje con la esclusa abierta...
	if (fverbo==vQuitar && fnombre1==nTraje  && CNDcarried(oTraje))
		{
			if (CNDonotzero(oEsclusa, aOpen)) { ACCmessage (19); DONE; }
		}

	if (fverbo==vSalir)
		{
		// Salir, compuerta cerrada...
		if (CNDozero (oEsclusa, aOpen)) { ACCmes(24); ACCmessage(22); DONE; }
		// Salir, Pero no lleva el traje
		if (CNDnotworn (oTraje)) { ACCmessage (19); DONE;}
		// Salir con éxito 
		if (CNDonotzero(oEsclusa, aOpen) && CNDworn(oTraje)) { ACCgoto (lExterior); DONE; }
		}
	
	// Regresa al nodo pero lleva puesto el traje...
	if (fverbo==vIr && fnombre1==nNodo)
		{
			if (CNDworn(oTraje) || CNDcarried(oTraje)) { ACCmessage (20); DONE; }
				else { ACCgoto (lNodo); DONE; }
		}

	// Puzzle de abrir la compuerta
	if (fnombre1==nPuerta || fnombre1==nCompuerta) fnombre1=nEsclusa;
	if (fverbo==vAbrir && fnombre1==nEsclusa ) { ACCmessage(24); DONE; }
	if (fverbo==vCerrar && fnombre1==nEsclusa) { ACCmessage(25); DONE; }
	if (fverbo==vExaminar)
		{			
			if (fnombre1==nEsclusa || fnombre1==nCompu)
			{
				ACCmes(21);
				// Aparecen listados...
				ACCoclear (obotonrojo,aConcealed);
				ACCoclear (obotonverde,aConcealed);
				if (CNDonotzero(oEsclusa, aOpen)) { ACCmessage(23); DONE; }
					else { ACCmessage(22); DONE; }
			}
			if (fnombre1==nControles) { ACCmessage(24); DONE; }
			if (fnombre1==nBoton) 
			{
				if (fadjetivo1==aVerde) { ACCmessage (26); DONE; }
				if (fadjetivo1==aRojo) { ACCmessage(27); DONE; }	
				ACCmessage(172); 
				DONE; 
			} 
		}
	// Usar los botones...

	if (fverbo==vPulsar)
	{
		if (fnombre1==nBoton)
		{
			// Cerrar esclusa 
			if (fadjetivo1==aRojo)
			{
				if (CNDozero(oEsclusa,aOpen)) { ACCmessage(32); DONE; }
				else { ACCoclear (oEsclusa, aOpen); ACCmessage(30); DONE; }
			}
			// Abrir esclusa...
			if (fadjetivo1==aVerde)
			{
				if (CNDonotzero(oEsclusa,aOpen)) { ACCmessage(28); DONE; }
				else { 
					// Pero no tiene puesto el traje...
					if (CNDnotworn(oTraje)) { ACCmessage(19); DONE; }
					// Abre la compuerta
					ACCoset (oEsclusa, aOpen); ACCmessage(29); DONE; }
			}
		}	
	}
		
	}

// --------------------------------------------------
// Bodega 
// --------------------------------------------------

if (flocalidad==lBodega)
	{
	// Fin del juego
	if (CNDcarried(oCaja))
		{
			ACCmessage (60);
			ACCanykey();
			ACCmessage (61);
			ACCanykey();
			ACCmessage (62);
			ACCanykey();
			ACCmessage (63);
			ACCend();
			DONE;
		}
	if (fverbo==vExaminar)
		{
		if (fnombre1==nPaquetes) { ACCmessage (173); DONE; }
		}

	if ( (fverbo==vCoger || fverbo==vEmpujar) && fnombre1==nPaquetes)
		{
			ACCmessage (174);
			DONE;
		}
	}
// --------------------------------------------------
// Exterior 
// --------------------------------------------------
if (fverbo==vExaminar)
{
	if (flocalidad==lExterior || flocalidad==lAlmacen)
	{
		if (fnombre1==nCielo) { ACCmessage (7); DONE; }
		if (fnombre1==nJupiter) { ACCmessage (178); DONE; }
		if (fnombre1==nEuropa) { ACCmessage (179); DONE; }
		if (fnombre1==nCristales) { ACCmessage (11); DONE; }	
	}
}


if (flocalidad==lExterior)
	{
		if (fverbo==vIr)
		{
			if (fnombre1==nNave) 
			{
				ACCgoto (lEsclusa);
			}	
			if (fnombre1==nAlmacen || fnombre1==nMole || fnombre1==nEdificio)
			{
				ACCgoto (lAlmacen);
			}
		}

		if (fverbo==vExaminar)
		{
			if (fnombre1==nNave) 
			{
				ACCmessage (36);
				DONE;	
			}
			if (fnombre1==nMole) 
			{
				ACCmessage (38);
				DONE;
			}
		}
	}

// --------------------------------------------------
// Entrada al almacén
// --------------------------------------------------
if (flocalidad==lEntrada)
{		
	if (fverbo==vIr) 
	{
		if (fnombre1==nNave) { ACCgoto (lExterior); DONE; }	
	}
	
	
	if (fverbo==nEste) { fverbo==vIr; fnombre1==nNave; }
	if (fverbo==vIr && fnombre1==nNave) { ACCgoto(lExterior); DONE; }
	if (fverbo==nOeste || fnombre1==nOeste) { fverbo==vEntrar; }
	// Entrar al almacén...
	if (fverbo==vEntrar) 
	{
		if (CNDozero(oPuerta, aOpen)) { ACCmessage(22); DONE; }
		ACCgoto(lZonaA1);
		DONE;
	}

	if (fverbo==vExaminar)
	{
		if (fnombre1==nEdificio) { ACCmessage(182); DONE; }	

		if (fnombre1==nPuerta) 
		{
			ACCmes(180);
			if (!CNDisat(oTeclado,lEntrada))
			{
				ACCmes (39);
				ACCplace (oTeclado,lEntrada);			
			}	
			if (CNDonotzero(oPuerta, aOpen)) { ACCmessage(23); DONE;}
				else { ACCmessage(22); DONE; }
			DONE;
		}

		if (fnombre1==nCanon && CNDpresent(oCanon)) { ACCmessage(41); DONE; }
		if (fnombre1==nTeclado && CNDpresent(oTeclado)) 
		{
			if (CNDabsent(oCanon) && CNDozero (oPuerta, aOpen)) 
			{
				ACCplace(oCanon, lEntrada);
				ACCmessage(40);
				DONE;
			}
			writeText ("El teclado no responde. La puerta ya está abierta.^");
			DONE;
		}
	}

	if ( (fverbo==vAbrir||fverbo==vCerrar) && fnombre1==nPuerta)
	{
		ACCmessage (195);
		if (!CNDisat(oTeclado,lEntrada))
		{
			ACCmes (39);
			ACCplace (oTeclado,lEntrada);			
		}	
		DONE;
	}
		
	if (fverbo==vTeclear) fverbo=vEscribir;
	if (fverbo==vEscribir)
	{
		if (fnombre2==EMPTY_WORD) { fnombre2=nTeclado; ACCmes(183); }
		if (fnombre2==nTeclado)
		{
			// Si ya está abierta...
			if (CNDpresent(oTeclado) && CNDonotzero(oPuerta, aOpen))
			{
				ACCmessage(184);
				DONE;
			}
			if (fnombre1==n32768 && CNDpresent(oTeclado))
			{
				// No está abierta...
				if (CNDozero(oPuerta, aOpen))
				{
					ACCmessage(186);
					ACCoset (oPuerta, aOpen);
					ACCplace (oCanon, LOCATION_NOTCREATED);
					ACCsetexit (lEntrada, nOeste, lZonaA1);
					ACCsetexit (lEntrada, nEntrar, lZonaA1);
					ACCdesc();
					DONE;
				}	
			}

			// Clave incorrecta...
			if (CNDpresent(oTeclado) && CNDpresent(oCanon)) 
			{
				ACCmes (185);
				flags[fCanon]++;
				if (flags[fCanon]<3)
				{
					ACCmessage (186+flags[fCanon]);
					DONE;
				} 
				// Ha excedido el número de intentos
				ACCmessage(41);				
			}
		}
	}
}
// --------------------------------------------------
// Zona A1
// --------------------------------------------------

if (flocalidad==lZonaA1)
{
	if (fverbo==vExaminar) 
	{
		if (fnombre1==nEstanterias) { ACCmessage (43); DONE;}			
		if (fnombre1==nTecho || fnombre1==nSuelo || fnombre1==nParedes || fnombre1==nPasillo) 
		{
			ACCmessage (44); DONE;
		}
		if (fnombre1==nContenedores) 
		{
			ACCmessage (191);
			DONE;
		}
	}
}

// --------------------------------------------------
// Zona A2
// --------------------------------------------------
if (fverbo==vCoger) 
{
	if (fnombre1==nPaquete)
	{
		if (fadjetivo1==aAzul) 
		{
			ACCautog(); DONE; 
		} 
				
		if (flocalidad==lZonaA2 || flocalidad==lZonaA1) { ACCmessage (194);DONE;}
		
	}
}
if (flocalidad==lZonaA2)
{
	 
	if (fverbo==vExaminar)
	{
		if (fnombre1==nBoveda) 
		{
			ACCmessage (45);
			DONE;
		}	
		if (fnombre1==nPasillo) 
		{
			ACCmessage (44);
			DONE;
		}
		if (fnombre1==nEstanterias)
		{
			ACCmessage (44);
			DONE;
		}
		if (fnombre1==nContenedores)
		{
			ACCmessage (191);
			DONE;
		}
	}

}
 NOTDONE;

// ================= LIBRERíA BASE FINAL=======================================

}

// ----------------------------------------------------------
// Tabla de respuestas-post
// Se llama después de ejecutar el proceso de respuestas
// ----------------------------------------------------------

char respuestas_post()
{
 //setRAMPage(0);
 // respuestas_post_pagina0();

// ------------------- LIBRERÍA BASE -----------------------------------
 // Comandos de dirección...
 // writeText ("Respuestas Post: %u %u^", flags[fverb], flags[fnoun1]);
 // Movimiento entre localidades...
    BYTE i;
    BYTE loc_temp;

	if (fverbo==vQuitar) {  ACCautor(); DONE; }
	if (fverbo==vPoner) { ACCautow(); DONE; }
	
	// En este punto el examinar no ha sido cubierto por las respuestas
    if (fverbo==vExaminar)
    {
        if (findMatchingObject(get_loc_pos(loc_here()))!=EMPTY_OBJECT)
            writeText ("Deberías coger eso antes.^");
        else
			writeText ("No ves eso por aquí.^");
		DONE;
    }

    if(fverbo==nInventario)
    {
        ACCinven();
        ACCnewline();
        DONE;
    }

    if (fverbo==vCoger)  { ACCautog(); DONE; }

    if (fverbo==vDejar) { ACCautod(); DONE; }

    if (fverbo==vMeter) { DONE; }

    if (fverbo==vSacar) { DONE; }

    // Si es un nombre/verbo de conexión...
	
    if (flags[fverb]>0 && flags[fverb]<NUM_CONNECTION_VERBS)
        {
            i=0;
            loc_temp = get_loc_pos (flags[flocation]); // La posicion en el array no tiene porque coincidir con su id
			i = conexiones_t[loc_temp].con[flags[fverb]-1];
	        if (i>0)
            {
                ACCgoto(i);
                DONE;
            }
            else {
                ACCsysmess(SYSMESS_WRONGDIRECTION);
                NOTDONE;
            }

        }
	
    // Comandos típicos...
    if (fverbo==vMirar)
    {
        ACCgoto( flags[flocation]);
        DONE;
    }
	if (fverbo==vEmpujar || fverbo==vTirar)
	{
		ACCsysmess (SYSMESS_CANNOTMOVE);
		DONE;
	}
	// Si ninguna acción es válida...
    ACCsysmess(SYSMESS_IDONTUNDERSTAND);
    newLine();
}

char proceso1() // Antes de la descripción de la localidad...
{
 // Muestra la pantalla...
 ACCpicture(flags[flocation]);
 //setRAMPage(0);
 //proceso1_pagina0();
 //setRAMPage(1);
 //proceso1_pagina1();
 //setRAMPage(0);

// Cálculo de luz
// En ZHL todas las localidades tienen luz
flags[flight]=1; // No está oscuro

// Incrementa el contador de turnos
if (flags[fturns_low]==255) {
	flags[fturns_high]++;
	flags[fturns_low]=0;	
	} else flags[fturns_low]++;
}

char proceso1_post() // Después de la descripción
{
 //setRAMPage(0);
 // Usar proceso en otras páginas require compilar código por separado
 //proceso1_post_pagina0();
}

char proceso2() // Después de cada turno, haya tenido o no éxito la entrada en la tabla de respuestas
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
    initParser ();                // Inicializa el parser y la pantalla
    defineTextWindow (0,11,32,14); // Pantalla reducida en 128Kb, Gráficos + Texto
    flags[LOCATION_MAX] = 8; // Número más alto de localidad
    ACCability(10,20); // 10 objetos, 20 piedras
    ACCgoto(lPuente); // Localidad inicial, en el puente de mando
	//ACCpicture(5);
	ParserLoop (); // Pone en marcha el bucle principal
	//ACCwrite ("Ahora tengo ");
	//ACCwrite("el traje presurizado");
	//while (1) {
	//}
}

// ------------------------------------------------------------
// Funciones propias del juego
// ------------------------------------------------------------

// Función para buscar en tablas a partir de una palabra clave
unsigned char buscador_tema (tema_t *tabla, unsigned char *word) 
{
    // Input: Cadena de texto
    unsigned char fin=0;
    unsigned char counter=0;
    //writeText ("Buscando...%s\n",word);
    while (fin==0)
    {
		//writeText ("%s-%s ",tabla[counter].word,playerWord);
        if (tabla[counter].topic==0) fin=1; // Fin de la tabla...
        if (strncmp(word,tabla[counter].topic,MAX_WORD_LENGHT)==0)
        {
            // flags[ftemp]=tabla[counter].id;
            //writeText ("found %u", flags[ftemp]);
            return counter;
        }
        counter++;
    }
    return EMPTY_WORD;
}



