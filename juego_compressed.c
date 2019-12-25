
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
// Se pueden declarar m�s tablas de flags para el juego pero el parser
// s�lo trabaja con esta. 
extern unsigned char flags[255]; // Flags 60...250 Disponibles para el usuario

// Tabla de im�genes del juego
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

// �ltima localidad como ID 0 

loc_t localidades_t [] =
{
	{"Pu���Ƹ","En�ext�i� ���v�s��at�u�ȱm�� hi�o�E��d�c�a�ߖcu�a baj�d�u�t�m��c����",lPuente, FALSE, 0x00000000},
	{"Nod�c�a�","La �v�ha�id�di�+�� f�ʿodu�r�E��d�c����Á𜎿Ƹ���cluѳ�o�t�y�bo��sur�U�ȣu�iluڵ�&�p�vi��d�s�c��a��𜎬mƸ�",lNodo, FALSE, 0x00000000},
	{"Esclusa","L�clus���s�m� i���mbi��r�i&��e�ext�i� y�zo� h�i�bl����.",lEsclusa, FALSE, 0x00000000},
	{"Bo�g����","La z������i�e��ΡsufiΜe�a�t��r�eq�+��v%��e�t�u�r��Ha�v�i��q�t���p�a�su �e��", lBodega, FALSE, 0x00000000},
	{"Exterior","E�ζo�ԧb�r&��n�v�y��½e� hi�o�Laȱm�a��ti�sup�fi�e��zo� �cur� Eu���La �v�f�ó�oc�c�%�tĄ�sup�fi�e�ge���A�o�t�s�di��gu�u��ol��eì��dr%a���������c$n.",lExterior, FALSE, 0x00000000},
    {"E��ҳ���c$n","U��ol��eìߖcu�a�c�v�a��sup�fiΟhe�d� Eu���",lAlmacen, FALSE, 0x00000000},
    {"Zo� A1","L��a��%��p�Ä�t�ed��b�nc�c�a�u��tm&sf�a imp�so�l�U�p�ill��gr�a�o�t�ҳcc��a�t�������c$n.",lZonaA1, FALSE, 0x00000000},
    {"Zo� A2","E���c$�t�ڵ�u��a��o�d�a�i��� b�n��A�% hay�u�m#s�t�ed��b�nc�p�f��m���d�a�s��ô�%�.",lZonaA2, FALSE, 0x00000000},
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
	{"ZHL^ E���m�su�aq���24h�^ (c) 2016�2019 KMBR�R�e��4.",1},
	{"N�С�҂p�t�u�r.",2},
	{"ZHL b�KMBR",3},
	{"D�Σd����d�c��.",4},
	{"AsΣd���𜎿Ƹ.",5},
	{"E�m&du܍a�m�d����.",6},
	{"La v%a�#c�a�nu�ɡc�o.",7},
	{"La�sol��Ƹ�����E�u��l�b�ô�n�vo,��d��� ���d�ߖc�g������&�y�od�l��m�d�s���iza�p� voz�En���m�o�Ŵ�l��c�so��#��g�.",8},
	{"-F��o�m���d� bajo�su��La�sol�b�p�m�ᨳ�g�a -r�p����d���.",9},
	{"P�vi���c�sol��Ƹs�La�so��#��d� bajo�su��",10},
	{"N�v��hi��a 150 C��u�baj�c�o.",11},
	{"E��s���$r�c�ap��p��evit��f���&��c�½���ext�i� �l���s�.",12},
	{"S�f�mƂl�g�di��t$rں�l���ф���.",13},
	{"La �v� �p�t��n�hٛtu�u��",14},
	{"-Co�Ī��mp�atu���i��i� y�l���rum����vit��u �t�i��-�f�ʁ�d���.",15},
	{"E�̡��d�t�je��up�viv��a�᥯�a ��iz� EVA�E�t�je��mp��m��au�m#t�y�i��u��ut�om%��ch�ho�s�",16},
	{"Paq�t�a �eg���Ti��.",17},
	{"E�#��g�a.",18},
	{"-N�sob�vivir$�Eu�žӁt�j�pĩct�.",19},
	{"-Debid�a���aڵ�&��ja�t�j�Ʃ�������d�c�a�-t��cu�ҁ�d���.",20},
	{"L�cluѾirЍa igua�r�pr�i&��e�ext�i� y�i��i� �����Se�tĪ��b&է�jo�a����y�bot&�v���a�b�r�",21},
	{"E�#����.",22},
	{"E�#�bi��.",23},
	{"-L�cluѾ�������t�l�m�u��-�f�ʁ�d���.",24}, 
	{"-L�cluѾ�Ψ�����t�l�m�u��-�f�ʁ�d����",25},
	{"Puls��a�b�r��clu��^ADVERTENCIA: ANTES DE ABRIR USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"Puls��a���r��clu�.",27},
	{"-L�clu� ya�#�bi��.",28},
	{"-Abף��m�t�xt�i� y��n��i��i� -diⁱd����La�m�t�xt�i������ԧ�ߡڊ�s�igua�n��pr�i��.",29},
	{"-C��n��m�t�xt�i�- �pi���d���",30},
	{"U� �z��m�t�xt�i���ha�����̞ch�Ą�ir�a�r�i&�surg���s�e�s�a�imӯ����ڵ���igua���n�vo�pr�i�.",30},
	{"U��n�s��r�y��ک��c��a�i��i� ����.",31},
	{"-L�clu� ya�#���� -�p�Á�m�t�� ����.",32},
	{"Ap��̞�l%�tĄ�l#��y�eìt�ߑn��ext�i�.",33},
	{"-Fr%�a��c�.",34},
	{"Toì�cu�d���v�p��b�lܕ�iv���t�zo� hi����t#��y��.",35},
	{"La �v��du�r�#� �ZHL�Pi����m�ill�y���g���m�+%a�g����ə�j�.",36},
	{"ZHL 24h",37},
	{"C��if�ult��i��gu��p�fi��̠difi΋�eì�c�ø�t��ζo�",38},
	{"E�̔t�a�����aԧ�c�d�num$�c�iluڵ�e�m�e��cu�d�.",39},
	{"P�Ե�b�tu���slizaԧ�+&�l#s� �t�a�a: TECLEE EL C&DIGO DE ACCESO�TIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"U��+&���p�t�p�igr���gu�tu��viڜ�.",41},
	{"Tod�so��j�b�n� ��+��ڪr�L�m#�g���ߖcu�Ƃl��a��m#�baj�.",42},
	{"A�ja��c�a��eq�+��t�ed��b�n�s.",43},
	{"Tod�f��o�l�El��ΡsufiΜe�a�a����s�diι�n᥯i��a�r��v��at�i��b�l&gi�s.",44},
	{"U� b&��ˡmuy�l� f�ʁ�ch��a�a�.",45},
	{"U��q�t�azul�ԧg���d��� �p�igr�b�l&gi���fĴ��",46},
	{"-Es����q�t�-susur���d����tu�%�.",47},
	{"-N�p��,��di�ctiva��empr�a��l�impid��",48},
	{"P�igr�b�l&gi��C�s�v����o� 100���u�baj�c�o�N�m�i�ۧpĩc���N���r�N�gol��Mat�ia�fr#gil.",49},
	// Textos relativos al ordenador
	{"-Co�dӡ�d�l��s�ʄ����P�h��r��go�mp�a: �d����a�b�����Alg̙sug���a��a�br�c�v�s�: �d����yu��d����omb��d����i��..�-t�r�p��s�viν��d��� ������.",50},
	{"-Oh�vaya�m�n�p�s$�֨��-di⁺m�t��� f�ѳdګ��.",51},
	{" ",52},
	{"N��t��҂p�t�u�r.",53},
	{"N�a ���ٯ.",54},
	{"No���νm��i���Ʃ.",55},
	{"N�su⒵� ӥp�a�.",56},
	{"E�aullid��vi��r�u�a��fuߪje.",57},
	{"-Bu�ȫbaj�-apr�ba�voz�at�f�h���d���� ",58},
	{"-Ah���om������umb�a M���Baja��bo�g����i����iΡl��s�ʄ��v�-diⁱd�����mu��",59},
	{"D�Σd�l��c���a�bo�� �p�iՁ�q�t�ju��a�o�m#�p�di�e� �e��A��gr�� �scubć�їs�ha����.",60},
	{"-No� �ҭ�so��p�o��om�� ��c��-di�voz���d���-�i��u�g���Ҁbo�� y�a��u�p�f�d�s�+o.",61}, 
	{"L�m#�duĕȣ� ���c��su�p�z��a��gui������L��a���s�hum���E�f�..�-suspi���d����i����g�l�r�Մ�u�u��Ե �bof�go�.",62},
	{"-C��,��% Tod C�n� -di�voz- Vol�m�a M�����q���Repit�vol�m����q���",63},
	{"Hay��bot��: �j��v���S�utilizƍa����y�b�r��cluѳl�xt�i��",172},
	{"L��gui���q�t��a �eg�.",173},
	{"No��om�� jug���Sokob�.",174},
	{"-Voo��..�ooh�ooh -t�v�lv�cr�l�ዀ��.",175},
	{"-Ca��e,�oh�ooh -i����t�� ^ -N�blu�ipi��di blu...",176},
	{"S&ܕcucho�#ti��Laȱm�a i��fi�e��s�m�i�ι�.",177},
	{"E�oy��c�ocul�,ˡСJ'pit�.",178},
	{"Sat$lit�he�d���h&spi�.",179}, 
	{"La ��a����c$n�",180},
	{"F��o���mƸ� voz���d���: �d������.",181}, 
	{"E�u�b܅�t#l졻c�ngu���s�i��� baj�ti��.",182}, 
	{"(���c��)",183},
	{"La�u�t����c$�ya�#�bi��.",184},
	{"E��c�d�s�iluڵ��jo�CODIGO INCORRECTO.",185}, 
	{"E��c�d�s�iluڵ�v���CODIGO CORRECTO�E��+&�l#s����pl��su�mp�tim�o.",186}, 
	{"E��+&�l#s��ڣza������.",187},
	{"E��+&�l#s���p�p�a��r�",188},
	{"E��+&�l#s����",189},
	{"P���Ҿu��U� volut� hum�y�lg̙ch�p�surg����+�.",190},
	{"S��t�ed�e�ȫnsp��.",191}, 
	{"(�gi�d�a���t�je)",192},
	{"-E��c���d�%�a�o�s��t�lug� �h&spit�-t��cu�ҁ�d���.",193},
	{"-S&l�n�it�u��q�t�azul�",194},
	{"La�up�fi�e��i�,�&l�s��tiva���c��.", 195},
	{"E U R O P A",196},
};

token_t mensajesSistema_t [] =
{
	{"N�p�d�v� ��,�#�u��cu�.^",0},
	{"Tambi$�ha�",1},
	{"Esc�b�tu�&a�%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&�? P� fav��r�ba��əŪb�s.^",6},
	{"N�p�d�ir��a�i�c��.^",7},
	{"�Perd�n?^",8},
	{"L�v�",9},
	{"(puesto)",10},
	{"n�g'�obje�.",11},
	{"/Segu�? ",12},
	{"/J��˲vo? ",13},
	{"Adi�s...",14},
	{"OK^",15},
	{"[...]",16},
	{"H���iz��",17},
	{"�ur�",18},
	{"s",19},
	{".^ ",20},
	{"La�u�ua�㠄 ",21},
	{"�u�o",22},
	{"N�l�v��Օo.^",23},
	{"N�p���ya��vo����.^",24},
	{"Yaȣg�",25},
	{"N��o��p���%.^",26},
	{"N�p�d�l�v��#s�s�.^",27},
	{"N�t�go�o.^",28},
	{"P��� ya��v���",29},
	{"S",30},
	{"N",31},
	{"M�s...",32},
	{"> ",33},
	{"",34},
	{"E�t�mp�p�a...^",35},
	{"Aho�ȣg�",36},
	{"M�p�g�",37},
	{"M��it�",38},
	{"Dej�",39},
	{"N�p�d�p��m�",40},
	{"N�p�d��it�m�",41},
	{"<T�g�m�i���s��l�m��!",42},
	{"D�g���am��p��m�ia�.",43},
	{"Meto",44},
	{"Aho��o�#�",45},
	{",",46},
	{" �",47},
	{".",48},
	{"N�t�g�",49},
	{"N�l�v��t�",50},
	{"",51},
	{"Es�݌#�",52},
	{"n�g'�obje�",53},
	{"F�h��ݖ����.^",54},
	{"F�h�o�rrup�.^",55},
	{"Err� �E/S�F�h��n�g�ba�.^",56},
	{"Di�ct�i�ll�o.^",57},
	{"D�c�ll�o.",58},
	{"Nombr� f�h��n�v#li�.^",59},
	{"Nombr��f�h�o: ",60},
	{"",61},
	{"/P�d�? P� fav��r�ba��əŪb�s.^",62},
	{"A�% ",SYSMESS_NPCLISTSTART},
	{"�t# ",SYSMESS_NPCLISTCONTINUE},
	{"est�n",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"D��ha�",SYSMESS_INSIDE_YOUCANSEE},
    {"En�� ha�",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"No��lg��p�� �it��.^",69},
	{"P�g�",SYSMESS_YOUPUTOBJECTON },
    {"No��lg��p�Ҙg��.^",SYSMESS_YOUCANNOTTAKE},
	{"No�ៅp�ҿov��.^", SYSMESS_CANNOTMOVE},
	{"L�vo��mƞv�%�.^", SYSMESS_CARRYNOTHING},
	{"",0}	
};

// Tablas de vocabulario
// Nombre propios, sustantivos...
// �ltimo elemento debe ser 0
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
	{"ENSE�", 	36},
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
// No existe la limitaci�n de PAWS donde el objeto 1 siemmpre es la fuente de luz 
// La luz en ngpaws se calcula en funci�n del atributo de los objetos presentes en la localidad, puestos y llevados.
// Localidades de sistema: LOCATION_WORN,LOCATION_CARRIED, LOCATION_NONCREATED, LOCATION_HERE, CARRIED, HERE, NONCREATED, WORN

// Atributos con OR: aLight, aWear, aContainer, aNPC, aConcealed, aEdible, aDrinkable, aEnterable, aFemale, aLockable, aLocked, aMale, aNeuter, aOpenable, aOpen, aPluralName, aTransparent, aScenary, aSupporter, aSwitchable, aOn, aStatic, aExamined, aTaken, aDropped, aVisited, aTalked, aWore, aEaten, aPropio, aDeterminado

obj_t objetos_t[]=
{
    // ID, LOC, NOMBRE, NOMBREID, ADJID, PESO, ATRIBUTOS
    {oCaja, lZonaA2,"�q�t�azul",     nPaquete, aAzul,   1,0x0000 | aMale | aDeterminado},  
    {oTraje, lEsclusa,"t�j�pr�u�za�",     nTraje, EMPTY_WORD,   1,0x0000 | aWear| aMale | aDeterminado},  
	{oEsclusa, lEsclusa,"�m�t���clu�", nEsclusa, EMPTY_WORD,   1,0x0000 | aStatic | aFemale | aDeterminado},  
	{oPuerta, lEntrada,"�t��et�",     nPuerta, EMPTY_WORD,   1,0x0000 | aStatic | aFemale},  
	{obotonrojo, lEsclusa,"bot&��jo",     nBoton, aRojo,   1,0x0000 | aStatic | aConcealed | aMale},  
	{obotonverde, lEsclusa,"bot&�v��",     nBoton, aVerde,   1,0x0000 | aStatic | aConcealed | aMale},  
	{oCanon, NONCREATED,"�+&��vigi�n�a",     nCanon, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
	{oTeclado, NONCREATED,"teclado",     nTeclado, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x0000}
}; // Tabla de objetos de la aventura

// Una tabla para hablar con el ordenador, se puede usar la misma t�cnica para definir listas de atrezzo y ahorrarse cientos de 'examinar objeto'.

// Tabla de conversaci�n con el ordenador 
tema_t ordenador_t[]= 
{
	{"Hola","-Ho�,�oy��d��� �����&�-r�p��u� voz�et#li�."},
	{"Adios","-H�íĴo."},
	{"trabajo","-Soy��s�m� ����&������"},
	{"yo/piloto/conductor/transportista","-Er�Tod C�n�,�pi�t�����"},
	{"tormenta/parabrisas", "-Laȱm���o����N�b�%a��ԧp�b�ʍa�c�r����c$�usƸ�t�j��ĩc��."},
	{"Europa/luna",	"-E�am����t$lit�Jovi�o�-r�p����d���."},
	{"Joviano/Jupiter",	"-Eu�p�ԧ�t$lit� Jupit��En�c�iluڵҭ� J'pit���p�t#cuܕ�ob�b��P� �sg��a�u�tĖc�go���c�ocul��"},
	{"cara/lado", "-Eu���i��u���s�mpr��i��a ha�a J'pit�."},
	{"donde", "-E�#�u���c$n,��ext�i��T�dr#��s�ir��aȱm�a�"},
	{"Mision","-T�em����g�ԧ�q���Eu�� �eg�܂M�t�Ʃ� 24h -r�p��."},
	{"nombre",	"-Mi�omb�� TOD�Si��p�fi��,��d�us����mbr�a�h��r��go� "},
	{"modelo/ordenador", "-Soyԧ�l�Cyb�dӟ1997� Mi��g�m�� �igi��f��Dr�Guill�m�Ha���Me� C��ti��Me��+&��a��Ե�����/�i��o%r�?"},
	{"mega/megacorp/corporacion/ciberdine/cyberdine","-L�mpr�aޥp��bl� �t' �yo�em��v�sƸ�Eu��."},
	{"aventuras/conversacionales","-Me��Ɣ�av�u�s�v���o�l�."},
	{"if/fi/ficcion/interactiva","-D�c�oz���t$rm�o�/t��fi��a�s�v���o�l�?"},
	{"graficas","-No�#�m�,���n�c���p�d�jug��Ե�i���duc�."},
	{"transilvania","-No�#��,��o�ԧ꺘rÍa�i gu�o�P�fi��'��ch�m#s�r�'�du� ̙12h �j�g���mp���."},
	{"isla",	"-P��bu�o�<ەa���t�mӯ�!�R�u�d��̡��aut��,ԧìUTO��hiz�u� vi�ó�p�g�m�� �t�m�& çʬ���ruy�o��d�u�b܅�ofiεs�P�o���t� hi±ia."},
	{"uto",	"-Re�m��n�t�g�m#��t�sob��a��so��SӦud��Ե���ʥt����p���i��gi�r�."},
	{"kmbr","-U��¨�,��rum�ea ��aԧ����j�mu�n��"},
	{"kno",	"-U�c�eb�d�aut� �c&�c �vivi&�#���Μ�a+��T�%aԧc�ܖ��d�ç�s�mu���fi�lm��mu�&�p����p� $l�E�u�cl#ۺ�b�%�֨�oҾu�b� v�i��c�."},
	{"dela/dla","-Un�c�b���gl�XV�g�Ιa $�t�em�d�p�ibl�ʫvil�s�m�'CuƸ�m%�s��g�'�f�nc$s."},
	{"frances/ingles/italiano/aleman",	"-L�gu�mu�t��hoy�d%a�o���iv�s�h헩c�l��."},
	{"tecnollano/castellano/espanol/mexicano", "-La��gua f�nc��u�ɞd%�."},
	{"comic", "-A��cu��a�muy�o�r� fi�ք��gl�XX�"},
	{"daniel/danixi", "-E�r�p��bl����r�ti�."},
	{"obra", "-H��鄚l�cu�d�t�mӛtu�i��."},
	{"av�u� fav�i�", "-E�dif%�l�egir,��volvi�o���m����r�a �%z ��p�lif�a�&���s�ʄ �����au�m&vil��b�c��v���ν��"},
	{"jug��v�u�", "-T�busc�$Ե ��m��i���a��u� �zȨmӥ����."},
	{"cancion/oir/canta/tararea", "-Da�y..�-Coڣza��t���i��m�i�a f�tu�."},
	{"guillermo", "-E��g�i��r�p��bl��i��faz humƆ���s�ʄ ����&���Me�r�ti�"},
	{"interfa",	"-L��us��a h��r��go."},
	{"viajar", "-P�m��ha�g���q��,��g�p�dr$�umb�a M���-t��cu�ҁ�d���."},
	{"entrada", "-La ��a�# ha�fu�a�E�p�ibl��n�it��g'�c&dig��cc�o�a ��."},
	{"codigo", "-N�t�g�n�g'n�aՖ��d� ��c�a�٨c��c&digo."},
	{"central", "-La��a��ZEUR�#��Ti��."},
	{"ZEUR", "-Es�empr�� �p�t��aq�t��24h �n���s�ld�y��p�z��a�egui��c�ף��Univ�so."},
	{"Tierra", "-S�vo�l�z��pĩgid�s�ha�v�ti��̃g�m����e�-urb��U��ti�p�igr�o,���ll���p�t�iҤs." },
	{"almacen", "-Hem�at��z��c�c����a�Deb�s�ir�l�xt�i�犯����c$��volv����q���a �p�d�t�mӯ�����"},
	{"temperatura", "-E�t�n�a 150�C baj�c�o��ext�i��T���ڣd��l�v��t�j��up�vivi��a."},
	{"consola", "-La�sol���d�mu�t���t����v�y���t�l�m�u���Actu�m�e�# ��ctiv�a�a�h��r��g%a�"},
	{"�tiv��so�", "-E��j��p����mp�t������E�am���d� bajo�su�."},
	{"��ctiv��so�", "-Ya�# ��ctiv�a�"},
	{"memoria", "-E�n�ʬ�n��cu�d�much���ڣz�Ե�i���P��n�t�p�ocu򄕡aho��s�$� ̙j��҄ ��x�od�volv�#��n�m�id�."},
	{ "relax/jornadas/vacaciones","-D��$���t�baj��dr#�p�� ̞d%a� ��x�M��."},
	{"marte","-Ya���,�p��� �jo�Bu�o,���nj��s��d�ڣzo�t��f����."},
	{"venus/saturno/pluton/lunas/urano/neptuno/mercurio","-E��j� �n�s�irs���m������-r�p��"},
	{"terraformacion","-Hٟ̞a+��m�z���ext�c�&��mӨ��,�bרo�v�i�mәy�m�z�o�l�t�bajo�Ȩ�f����."},
	{"minas","-D��$����gid�bem��eg���q���E�T�ed��Un����y��ڵ� Hi�r��N%͓d�S�� So�r."},
	{"Tenedor","-Tambi$�s�փo��T�ed���di���E�u��i� gob��ҭ��s�di�t��if����Ө%� M���"},
	{"Hierro/Niquel","-E�u��ì��Ҵ�p��muy���a��L�dif%�l��uȫnsp��,�u���uy��s�y�u�� b�ô�dӨo�xt��l��atm&sf�a��Ti���"},
	{"sindicato","-Gobi��n��ơdu���p��o� v�a y���u����um�i�r��"},
	{"humanidad","-S�h�xt�did�p���xia�P��l�t�$i�b�ô�a�g�a��s�� So�r�s�ʴi�e��c���od���op�aι�."},
	{"operaciones","-Ya��sum�i�r�,�aq�t�%a,��o..."},
	{"ocio", "-A�% �d���o�ha�t�mӯ�t�bajo."},
	{"paqueteria", "-Nu�ɡt�bajo�ZEUR� �eg����q�t��24h"},
	{"suministros", "-S�ha��i�t�v�i�ڵs�M����objetiv��ba�t��p�΋����lg̙�t�i�p�m������o."},
	{"paquete", "-Seg'n��sc�p�㦓m��j�s�t�t�ԧ�q�t� 27cm x 29cm x 30cm �p�a 10Kg�"},
	{"recoger/recogida", "-Hem�at��za���������c$n�Sugi���s�g�ah% fu�a,��m�a��� j���q��."},
	{"nave", "-Vo�m��u� �v� �p�t��ip�T���Es�mp��m�e�$c�i�,�s% �ڊ�t��m�u��r��c��od�m��c�g���bat�%�."},
	{"estrellas", "-La�#�c�cƐ Sol."},
	{"Sol", "-Es��ɶ�pr��Ŭ����s���"},
	{"S�� So�r", "-Es��s�ʳ��p�t��e�Ti���"},
	{"sistemas", "-Tod�l��s�m���d��Op�am���d� bajo�su�."},
	{"ayuda", "-P��o�oy��%,�a�yud���Alg̙Ūbr�c�v��p�d�us���:�i���J'pit�,�omb�,�o��,���je..."},
	{"mensaje/comanda/encargo/entrega"	"Te�: Env%�urg��a�T�ed� �M���Co��i�: Re�gi҂��c$n���d����Eu���Us����: 32768�Imp��n�: Ma���� �mp�atu� baj�c�o�"},
	{"clave", "-Quiz# haya�lgo��m��j�l�c�go."},
	{"radiacion", "-No�ԧp�b�ʃ�t�j��up�viv��a�SӚ��dia�� �n�ev�a �n�vivir%�m#� ̦%a�"},
	{"airlock/esclusa/boton/botones", "-L�cluѾ�op�a��u�m�e�E�bot&�v��Ψ���clu� y��jo���� A�g'�t���v��t�j��up�viv��a�u���"},
	{"comunicaciones", "-Debid�a�fu�t��dia�&�nu�t�s�m�i�ι�s&l�f��o�n�����No��$�tig�ah% fu�a�"},
	{"eva", "-S����g���ctivid��xt�-�h�u�r�E�cu�d�s�����&�fu������"},
	{"traje/superviviencia/proteccion"	"-Lo����r#s���cluѰi�o�a�u�so�R�u��ˡs�i����v�ۧl�v�l���."},
	{"mierda/tacos/culo/joder/hija/puta/puton/hijo/comemierda", "-Eѳ�p�&�n�f�ʍt��i b���at��-r�p����d�����eg��a�"},
	{"siglas", "-Ya���,�a�c�t��a�b��m�ia��rg��"},
	{"calla", "-Si�p�b�m��yaˡë��m��-r�p��u��c��li�."},
	{"bodega", "-D����c�am�l��q�t��a�u�i��bu��."},
	{"temperatura/frigo/congelador/frigorifico/enfriar", "-T�em�u�f�g�%f�d���a��tip��aq�t��-r�p�d�s�$�ԧb�v��l��o"},
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

// A�adir funciones de inyecci�n de comandos en modo DEBUG

//; S�lo podemos hablar con el ordenador en la nave
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
// Descripciones com�nes para la nave
if (fverbo==vExaminar)  {
	if (fnombre1==nNave)	
	{
		if (CNDatlt (lExterior)) { ACCmessage (14); return TRUE; }
		if (CNDatlt (lAlmacen)) { ACCmessage(36); return TRUE;}
		// Si estamos dentro del almac�n no vemos la nave...
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
			if (fnombre1==nBodega) { ACCwriteln ("A�sur."); DONE;}
			if (fnombre1==nEsclusa) { ACCwriteln ("A�o��."); DONE;}
			if (fnombre1==nEscaleras || fnombre1==nPuente) 
			{
				ACCmessage(5);
				DONE;
			}
			if (fnombre1==nLuz) { ACCwriteln ("P�vi���𜎿Ƹ."); DONE; }
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
	// Sin�nimos...
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
		// Salir con �xito 
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
// Entrada al almac�n
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
	// Entrar al almac�n...
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
			writeText ("E��c�d�n�r�p���La�u�� ya�#�bi��.^");
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
			// Si ya est� abierta...
			if (CNDpresent(oTeclado) && CNDonotzero(oPuerta, aOpen))
			{
				ACCmessage(184);
				DONE;
			}
			if (fnombre1==n32768 && CNDpresent(oTeclado))
			{
				// No est� abierta...
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
				// Ha excedido el n�mero de intentos
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

// ================= LIBRER�A BASE FINAL=======================================

}

// ----------------------------------------------------------
// Tabla de respuestas-post
// Se llama despu�s de ejecutar el proceso de respuestas
// ----------------------------------------------------------

char respuestas_post()
{
 //setRAMPage(0);
 // respuestas_post_pagina0();

// ------------------- LIBRER�A BASE -----------------------------------
 // Comandos de direcci�n...
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
            writeText ("Deb�%��g���a��.^");
        else
			writeText ("N�v���p���%.^");
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

    // Si es un nombre/verbo de conexi�n...
	
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
	
    // Comandos t�picos...
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
	// Si ninguna acci�n es v�lida...
    ACCsysmess(SYSMESS_IDONTUNDERSTAND);
    newLine();
}

char proceso1() // Antes de la descripci�n de la localidad...
{
 // Muestra la pantalla...
 ACCpicture(flags[flocation]);
 //setRAMPage(0);
 //proceso1_pagina0();
 //setRAMPage(1);
 //proceso1_pagina1();
 //setRAMPage(0);

// C�lculo de luz
// En ZHL todas las localidades tienen luz
flags[flight]=1; // No est� oscuro

// Incrementa el contador de turnos
if (flags[fturns_low]==255) {
	flags[fturns_high]++;
	flags[fturns_low]=0;	
	} else flags[fturns_low]++;
}

char proceso1_post() // Despu�s de la descripci�n
{
 //setRAMPage(0);
 // Usar proceso en otras p�ginas require compilar c�digo por separado
 //proceso1_post_pagina0();
}

char proceso2() // Despu�s de cada turno, haya tenido o no �xito la entrada en la tabla de respuestas
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
    defineTextWindow (0,11,32,14); // Pantalla reducida en 128Kb, Gr�ficos + Texto
    flags[LOCATION_MAX] = 8; // N�mero m�s alto de localidad
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

// Funci�n para buscar en tablas a partir de una palabra clave
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



