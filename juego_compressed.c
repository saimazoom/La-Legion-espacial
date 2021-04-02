// ZHL. Escrita por KMBR.
// 2016-2019 KMBR
// This code is licensed under a Attribution-NonCommercial-NoDerivatives 4.0 International (CC BY-NC-ND 4.0) 
// https://creativecommons.org/licenses/by-nc-nd/4.0/
// Use ISO 8819-15 Encoding 

//#include <stdio.h>
#include <string.h>
//#include <spectrum.h>
#include "parser_defs.h"
#include "parser.h"
// Flags del Juego
#include "juego_flags.h"

#define GRAPHICS 

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
extern unsigned char playerInput[80];
extern unsigned char playerWord[25];
extern BYTE gWord_number; // Marker for current word, 1st word is 1
extern BYTE gChar_number; // Marker for current char, 1st char is 0

// Tabla de im�genes del juego
extern unsigned char *L01_img;
extern unsigned char *L02_img;
extern unsigned char *L03_img;
extern unsigned char *L04_img;
extern unsigned char *L05_img;
extern unsigned char *L06_img;
extern unsigned char *L07_img;
extern unsigned char *Europa_img;

#ifdef GRAPHICS
	#asm
	_L01_img:
	BINARY "./res/lPuente07.scr.rcs.zx7"
	_L02_img:
	BINARY "./res/lnode1.scr.rcs.zx7"
	_L03_img:
	BINARY "./res/lEsclusa.scr.rcs.zx7"
	_L04_img:
	BINARY "./res/lBodega01.scr.rcs.zx7"
	_L05_img:
	BINARY "./res/lExterior03.scr.rcs.zx7"
	_L06_img:
	BINARY "./res/lEntrada03.scr.rcs.zx7"
	_L07_img:
	BINARY "./res/lzonaA1.scr.rcs.zx7"
	_Europa_img:
	BINARY "./res/Europa.scr.rcs.zx7"
	#endasm

// id, page, memory pointer
img_t imagenes_t [] = {
    { 1,0, L01_img},   
    { 2,0, L02_img},   
    { 3,0, L03_img},   
 	{ 4,0, L04_img},   
    { 5,0, L05_img},   
    { 6,0, L06_img},   
    { 7,0, L07_img},   
    { 8,0, L07_img},   
	{ 9,0, Europa_img},
    { 0,0,0}
    };
#else 
img_t imagenes_t [] = {
    { 0,0,0}
    };
#endif 

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
	{"Pu���÷","L���rum�o� ��ga�&�iluڲn��÷�En�ext�i�,ղįm�� hi��s�abat�sob��sup�fi̎ Eu���",lPuente, FALSE, 0x00000000},
	{"Nod�c�a�","L�m&duׄ��Ӊ#n�p�umb��E��d�c����ǃ��÷,��cluҶ�o�t�y�bo�ga��sur�",lNodo, FALSE, 0x00000000},
	{"Esclusa","En��cluҼe�cucha� i���d��t�m�a golpe÷�t��fu߫je�L�s�br�c�a�f�m�s�i�t�s�l�t�je��xpת���",lEsclusa, FALSE, 0x00000000},
	{"Bo�g���ga","La z����ga�i�e��̡sufi̞�p�at��r�eq�+��v%��e�t�u�r��En�s�br�ha�v�i��q�t���p�a�su �ega�", lBodega, FALSE, 0x00000000},
	{"Exterior","Me�v�lv�u�įm����v�y��¾e� hi���m�impi�v���di���a�A�o�t�s�di��gu�Πdifi̡��dr%a���������c$n.",lExterior, FALSE, 0x00000000},
    {"E��Զ���c$n","U��ol��eǬߔcu�a�c�v�a��sup�fi̟he�d� Eu���",lAlmacen, FALSE, 0x00000000},
    {"Zo� A1","L�m�&вs�a��%��p�Ǆ�t�ed��b�nc�c�a�u��tm&sf�a imp�so�l�A�o�t�u��cur�p�ill�Զcc��aղ�a��ja.",lZonaA1, FALSE, 0x00000000},
    {"Zo� A2","E�p�ill�t�ڲ�u��a�abo�d�a iluڲԂ�jo�L�m�&вs�a��%�pr�igu��u�urso��#s�t�ed��b�nc�p�f��m��o�a�s.",lZonaA2, FALSE, 0x00000000},
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
	{"ZHL^ E��gam�su�aq���24h�^ (c) 2016�2019 KMBR�R�e��4.",1},
	{"N�ӡ�Ԃp�t�u�r.",2},
	{"ZHL b�KMBR",3},
	{"D�̣d����d�c��.",4},
	{"Aṣd����÷.",5},
	{"E�m&dul�p��m�d����.",6},
	{"La v%a�#c�a�nu�ȡc�o.",7},
	{"La�sol� ��ga�&������E�u��l�b�ǵ�n�vo,�o��� �ab�d�ߔc�g����ga�&�y�od�l��m�d�s���iza�p� voz�En���m�o�ŵ�l���nso��#��g�.",8},
	{"-F��o�m���d��bajo�su��La�sol�b�p�m�ਸ਼�g�a -r�p���o���.",9},
	{"P�vi����nsol��÷s�La�so��#��d��bajo�su��",10},
	{"N�v��hi��a 150 C��u�baj�c�o.",11},
	{"E��s���$r�c�ap��p��evit��f���&��c�¾���ext�i� �l�ab�s�.",12},
	{"S�f�mÂl�g�di��t$rڹ�l�ab�҄���.",13},
	{"La �v� �p�t��n�hago�ru��E�u��l��du�۾��rui���&dul��#ݮ�H�suĪbaj�yʡs�av�%�m�i���c�.",14},
	{"-Co�ɫ��mp�atu���i��i� y�l���rum��p�evit��u �t�i��-�f�ˁo���.",15},
	{"E�Ρ��d�t�je��up�viv��a�८i�p���iz� EVA�E�t�je��mp��m��au�m#t�y�i��u��ut��%��ch�ho�s�",16},
	{"Paq�t�a �eg�����s�˼o�r.",17},
	{"E�#��g�a.",18},
	{"N�sob�vivir$�Eu�żсt�j�pɩct�.",19},
	{"-P�evit���ڲ�&��ja�t�j�é�������d�c�a�-t��cu�ԁo���.",20},
	{"La�cluҼirv�p�igua�r�pr�i&��e�ext�i� y�i��i� �����Se��o���b&Ч�j�p�c���y�bot&�v��p�ab�r�",21},
	{"E�#����.",22},
	{"E�#�bi��.",23},
	{"-La�cluҼ�ab������ol�m�u��-�f�ˁo���.",24}, 
	{"-La�cluҼ�̨������ol�m�u��-�f�ˁo����",25},
	{"Puls���ab�r��clu��^ADVERTENCIA: ANTES DE ABRIR USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"Puls���c��r��clu�.",27},
	{"-La�clu� ya�#�bi��.",28},
	{"-Abۣ��m�t�xt�i� y��n��i��i� -d�e�o����La�m�t�xt�i���ab��է�ߡڑ�s�igua�n��pr�i��.",29},
	{"-C��n��m�t�xt�i�- �pi��o���",30},
	{"U� �z��m�t�xt�i���ha�����Νch�Ʉ�ir�a�r�i&�surg� ���ed�p��imѮ����ڲ���igua���n�vo�pr�i�.",30},
	{"U�pÓs�abr�y��ک��c��a�i��i� ����.",31},
	{"-La�clu� ya�#���� -�p�ǁo��� �ab��.",32},
	{"Ap��Ν�l%��o��l#��y�eǬt�ߐn��ext�i�.",33},
	{"-Fr%�a��c�.",34},
	{"Co�u��och��cu���v�p��b�lז�iv����ozo� hi����t#��y��.",35},
	{"La �v��du�r�#ݮ �ZHL�Pi����m�ill�y���g����m�+%a�g�ݜ�ș�j�.",36},
	{"ZHL 24h",37},
	{"C��if�ult��i��o�p�fi��Πdifi̡��t���t�m�a�",38},
	{"E�Εt�a�����a b�l�u��c�d�num$۹.",39},
	{"P�ղ�b�tu���slizaէ�+&�l#s� �t�a�a: TECLEE EL C&DIGO DE ACCESO�TIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"U��+&���p�t�p�igr���gu�ڢ�viڞ�.",41},
	{"Tod�so��j�b�n��a�+��ګr�L�m#�g�ݜߔcu�Âl��a��m#�baj�.",42},
	{"A�ja��c�a��eq�+��t�ed��b�n�s.",43},
	{"Tod�f��o�l�El��̡sufi̞�p�˵���s�di̺�n८i�p�pr��v��at�i��b�l&gi�s.",44},
	{"U��ev�a b&�� f�ˁ�ch���a�a�.",45},
	{"U��q�t�azul�էg���d㿯 �p�igr�b�l&gi���fɵ��",46},
	{"-Es����q�t�-susur��o����tu�%�.",47},
	{"-N�p��,��di�ctiva���pr�a��l�impid��",48},
	{"P�igr�b�l&gi��C�s�v����o� 15���u�baj�c�o�N�m�i֧pɩc���N�ab�r�N�golpe��Mat�ia�fr#gil.",49},
	// Textos relativos al ordenador
	{"-Co�dѡ�d�l��s�˄����P�hab�r��go�mp�a:؍���m÷�AlgΙsug���a��m�d�s�:؍���yu�,؍����b�,؍���i��..�-t�r�p��s�vi̾�o��� ���ga��.",50},
	{"-Oh�vaya�m�n�p�s$�٨��-d�e�o���� f�Ҷdڪ��.",51},
	{" ",52},
	{"N��t��Ԃp�t�u�r.",53},
	{"N�a ����.",54},
	{"No��pe̾m��i���é.",55},
	{"N�su蒲� ѥp�a�.",56},
	{"E�aullid�d�vi��r�u�a��fu߫je.",57},
	{"-Bu�Ībaj�-apr�ba�voz�at�f�h��o���� ",58},
	{"-Aho���힡�p���umb�a M���Baja��bo�g���ga�i����i̡l��s�˄��v�-d�e�o������mu��",59},
	{"D�̣d�l��c���a�bo�ga �p�iЁ�q�t�ju��a�o�m#�p�di�e� �ega�A��gr�� �scubɇ�җs�ha����.",60},
	{"-No� �ԭ�so��p�o��힡���c��-d�e�voz��o���-�i��t�f��n��pi�n��golpe����beza�t��s��.",61}, 
	{"-L�m#�duɖģ� ���c��su�p�z��a��gui������L�ga�a���s�hum���E�f�..�-suspi��o����i����g�l�r�Є�u�u��ղ �bof�go�.",62},
	{"-C��,��% Tod C�n� -d�e�voz- Vol�m�a M�����q���Repit�vol�m����q���",63},
	{"Hay��bot��: �j��v���S�utiliza�p�c���y�b�r��cluҶl�xt�i��",172},
	{"L��gui���q�t�p��eg�.",173},
	{"No��힡�jug���Sokob�.",174},
	{"-Voo��..�ooh�ooh -t�v�lv�cr�l�ࡤ���.",175},
	{"-Ca��e,�oh�ooh -i����t�� ^ -N�blu�ipi��di blu...",176},
	{"S&זcucho�#t�a�Laįm�a i��fi�e��s�m��a̺�.",177},
	{"E�oy��c�ocul�,ʡӡJ'pit�.",178},
	{"Sat$lit�he�d���h&spi�.",179}, 
	{"La ��a����c$n�",180},
	{"F��o���m÷� voz��o���:؍���m÷.",181}, 
	{"E�u���ruc�&��t#l�a �ct�gu���s�i��� baj�ti��.",182}, 
	{"(���c��)",183},
	{"La�u�t����c$�ya�#�bi��.",184},
	{"E��c�d�s�iluڲ��jo�CLAVE INCORRECTA.",185}, 
	{"E��c�d�s�iluڲ�v���CLAVE CORRECTA�E��+&�l#s����pl�ga�su�mp�tim�o.",186}, 
	{"E��+&�l#s��ڣza������.",187},
	{"E��+&�l#s���p�p�a��r�",188},
	{"E��+&�l#s����",189},
	{"P���Լu��U� volut� hum�y�lgΙch�p�surg����+�.",190},
	{"S��t�ed�e�Īnsp��.",191}, 
	{"(�gi�d�a���t�je)",192},
	{"-L��s�m�ya�#n��d��bajo�summ�-t��cu�ԁo���.",193},
	{"-S&l�n�it�u��q�t�azul�",194},
	{"La�up�fi�e��i�,�&l�s��tiva���c��.", 195},
	{"E U R O P A",196},
};

token_t mensajesSistema_t [] =
{
	{"N�p�d�v� ��,�#�u��cu�.^",0},
	{"Tambi$�ha�",1},
	{"Esc�b�tu�&��a�%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&�? P� fav��r�ba��șūb�s.^",6},
	{"N�p�d�ir��a�i�c��.^",7},
	{"�Perd�n?^",8},
	{"L�v�",9},
	{"(puesto)",10},
	{"n�g'�obje�.",11},
	{"/Segu�? ",12},
	{"/J�ga�ʳvo? ",13},
	{"Adi�s...",14},
	{"OK^",15},
	{"[...]",16},
	{"H���iz��",17},
	{"�ur�",18},
	{"s",19},
	{".^ ",20},
	{"La�u�ua�⠄ ",21},
	{"�u�o",22},
	{"N�l�v��Жo.^",23},
	{"N�p���ya��vo����.^",24},
	{"Yaģg�",25},
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
	{"Aho�ģg�",36},
	{"M�p�g�",37},
	{"M��it�",38},
	{"Dej�",39},
	{"N�p�d�p��m�",40},
	{"N�p�d��it�m�",41},
	{"<T�g��m�i���s��l�m��!",42},
	{"D�g�̿am��p��m�ia�.",43},
	{"Meto",44},
	{"Aho��o�#�",45},
	{",",46},
	{" �",47},
	{".",48},
	{"N�t�g�",49},
	{"N�l�v��t�",50},
	{"",51},
	{"Es�܉#�",52},
	{"n�g'�obje�",53},
	{"F�h��ܔ����.^",54},
	{"F�h�o�rrup�.^",55},
	{"Err� �E/S�F�h��n�g�ba�.^",56},
	{"Di�ct�i�ll�o.^",57},
	{"D�c�ll�o.",58},
	{"N�br� f�h��n�v#li�.^",59},
	{"N�br��f�h�o: ",60},
	{"",61},
	{"/P�d�? P� fav��r�ba��șūb�s.^",62},
	{"A�% ",SYSMESS_NPCLISTSTART},
	{"�t# ",SYSMESS_NPCLISTCONTINUE},
	{"est�n",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"D��ha�",SYSMESS_INSIDE_YOUCANSEE},
    {"En�� ha�",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"No��lg��p�� �it��.^",69},
	{"P�g�",SYSMESS_YOUPUTOBJECTON },
    {"No��lg��p�Ԙg��.^",SYSMESS_YOUCANNOTTAKE},
	{"No����p���ov��.^", SYSMESS_CANNOTMOVE},
	{"L�vo��mÝv�%�.^", SYSMESS_CARRYNOTHING},
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
	{"fusel",	nNave},
	{"nodo",	nNodo},
	{"puent",	nPuente},
	{"torme",	nTormenta},
	{"europ",	nEuropa},
	{"luna",	nLuna},
	{"lunas",	nLuna},
	{"satel",	nSatelite},
	{"jupit",	nJupiter},
	{"jovia",	nJoviano},
	{"cara",	nCara},
	{"lado",	nLado},
    {"inter", 	nInterior},
	{"almac",	nAlmacen},
	{"mole",	nMole},
	{"edifi",	nEdificio},
	{"orden", 	nOrdenador},
//	{"compu", 	nOrdenador},
	{"ia", 		nOrdenador},
	{"dot", 	nOrdenador},
	{"tod",		nOrdenador},	
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
	{"compu",	nEsclusa},
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
	{"panel", nPantalla},
	{"sombr", nSombra},
	{"",0}
};

// Verbos
// VOCABULARIO
// Verbos < 20 son iguales a nombres < 20
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
    {"quit",	vFin},
    {"fin",		vFin},
    {"save",	vSave},
    {"graba",	vSave},
    {"salva",	vSave},
	{"guard",	vSave},
	{"load",	vLoad},
	{"carga",	vLoad},
	{"ramsa",	vRamsave},
	{"graba",	vSave},
	{"ramlo",	vRamload},
	{"carga",	vLoad},
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
	*/
	{"tocar",	vTocar},
	{"toca",	vTocar},
	{"acari",	vTocar},
	{"palpa",	vTocar},
	/*
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
	{"punto", vPuntos},
	{"score", vPuntos},
	{"turno", vTurnos},
	{"usa", vUsar},
	{"usar", vUsar},
	{"activ", vUsar},
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
    {oCaja, lZonaA2,"�q�t�azul",     nPaquete, aAzul,   1, aMale_hex | aDeterminado_hex},  
    {oTraje, lEsclusa,"t�j�pr�u�za�",     nTraje, EMPTY_WORD,   1, aWear_hex| aMale_hex | aDeterminado_hex},  
	{oEsclusa, lEsclusa,"�m�t���clu�", nEsclusa, EMPTY_WORD,   1, aStatic_hex | aFemale_hex | aDeterminado_hex},  
	{oPuerta, lEntrada,"�t��et�",     nPuerta, EMPTY_WORD,   1, aStatic_hex | aFemale_hex},  
	{obotonrojo, lEsclusa,"bot&��jo",     nBoton, aRojo,   1, aStatic_hex | aConcealed_hex | aMale_hex},  
	{obotonverde, lEsclusa,"bot&�v��",     nBoton, aVerde,   1, aStatic_hex | aConcealed_hex | aMale_hex},  
	{oCanon, NONCREATED,"�+&��vigi�n�a",     nCanon, EMPTY_WORD,   1, aStatic_hex | aMale_hex},  
	{oTeclado, NONCREATED,"teclado",     nTeclado, EMPTY_WORD,   1, aStatic_hex | aMale_hex},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x00000000}
}; // Tabla de objetos de la aventura

// Para no usar las tablas de nombres y mensajes podemos a�adir una a medida
// para las conversaciones con PNJs. 

// Tabla de conversaci�n con el ordenador 
// El link entre la tabla de temas y los mensajes es el ID. 
token_t ordenador_topics_t[] = 
{
	{"hola",1},
	{"adios",2},
	{"traba",3},
	{"yo",4},
	{"pilot",4},
	{"condu",4},
	{"trans",4},
	{"torme", 5},
	{"parab", 5},
	{"europ",7},
	{"luna",7},
	{"jovia",8},
	{"jupit",8},
	{"cara",9},
	{"lado",9},
	{"donde", 10},
	{"misio", 11},
	{"nombr",12},
	{"model",13},
	{"mega",14},
	{"megac",14},
	{"corpo",14},
	{"ciber",14},
	{"cyber",14},
	{"ac",17},
	{"avent",17},
	{"conve",17},
	{"if", 18},
	{"fi",18},
	{"ficci",18},
	{"inter",18},
	{"grafi",19},
	{"transi",20},
	{"isla", 21},
	{"uto", 22},
	{"csg",22},
	{"kmbr",23},
	{"kmbrkat",23},
	{"kno",24},
	{"dla",25},
	{"dela",25},
	{"franc",26},
	{"ingle",26},
	{"itali",26},
	{"alema",26},
	{"caste",26},
	{"tecno",27},
	{"comic",28},
	{"daniel",29},
	{"danixi", 29},
	{"obra",30},
	{"favor",31},
	{"jugar",32},
	{"canci", 33},
	{"oir", 33},
	{"tarar", 33},
	{"canta",33},
	{"guille",34},
	{"inter",35},
	{"viaja",36},
	{"entra",37},
	{"codig",38},
	{"centr",39},
	{"zeur", 40},
	{"zhl", 40},
	{"tierr",41},
	{"almac",42},
	{"tempe",43},
	{"conso",44},
	{"memoria", 45},
	{"relax", 46},
	{"jorna", 46},
	{"vacac", 46},
	{"marte", 47},
	{"venus", 48},
	{"satur", 48},
	{"pluto", 48},
	{"neptu", 48},
	{"mercu", 48},
	{"minas", 50},
	{"tened", 51},
	{"diabl", 51},
	{"hierr", 52},
	{"nique", 52},
	{"sindi", 53},
	{"human", 54},
	{"opera", 55},
	{"ocio", 56},
	{"paque", 57},
	{"sumin", 58},
	{"paquet", 59},
	{"recog", 60},
	{"nave", 61},
	{"estre", 62},
	{"sol", 63},
	{"solar", 64},
	{"sistm", 65},
	{"ayuda", 66},
	{"mensa", 67},
	{"coman", 67},
	{"encar", 67},
	{"entre", 67},
	{"clave", 70},
	{"contr", 70},
	{"passw", 70},
	{"codig", 70},
	{"radia", 71},
	{"esclu", 72},
	{"boton", 72},
	{"airlo", 72},
	{"comun", 68},
	{"eva", 73},
	{"traje", 74},
	{"super", 75},
	{"prote", 76},
	{"sigla", 77},
	{"mierd", 78},
	{"culo", 78},
	{"joder", 78},
	{"puta", 78},
	{"puton", 78},
	{"calla", 79},
	{"bodeg", 80},
	{"enfri", 81},
	{"frigo", 81},
	{"conge", 81},
	{"",0}
};

// Topic and mensaje linked by ID 
// N:1 relationship
token_t mensajes_ordenador_t[]= 
{
	{"-Ho�,�oy�o��� ���ga�&�-r�p��u� voz�et#l�a.",1},
	{"-H�ǭɵo.",2},
	{"-Soy��s�m� ��ga�&������",3},
	{"-Er�Tod C�n�,�pi�t������",4},
	{"-Laįm�a��o����N��b�%a��էp�b�˭���r����c$�us÷�t�j��ɩc��.",5},
	{"-E�am����t$lit�Jovi�o�-r�p���o���.",7},
	{"-Eu�Ŗէ�t$lit� Jupit��En�c�iluڲԭ� J'pit���p�t#cuז�ob�b��P� �sg��a�u��o�c�go���c�ocul��",8},
	{"-Eu���i��u���s�mpr��i��a ha�a J'pit�.",9},
	{"-E�#�u���c$n,��ext�i��T�dr#��s�ir��aįm�a�",10},
	{"-Ti�����g�է�q���Eu�� �eg�ׂM�t�é� 24h -r�p��.",11},
	{"-Mi��b�� DOT�Si��p�fi��,��d�us����mbr�a�hab�r��go� ",12},
	{"-Soyէ�l�Cyb�dџ1997� Mi��g�m�� �igi��f��Dr�Guill�m�Ha���MegaC�p(tm)�Me��+&��a��ղ�����/�i��o%r�?",13},
	{"-L�mpr�aޥp��bl� �t' �yo����v�s÷�Eu��.",14},
	{"-Me��Õ�av�u�s�v���o�l�.",17},
	{"-D���z���t$rm�o�/t��fi��a�s�v���o�l�?",18},
	{"-No�#�m�,���n�c���p�d�jug��ղ�i���duc�.",19},
	{"-No�#��,��o�է鹘rǭ�� gu�o�P�fi��'��ch�m#s�rga'�du� Ι12h �j�g��t�mp���.",20},
	{"-P��bu�o�<֖a���t�mѮ�!�R�u�d��Ρ��aut��,էǬUTO��hiz�u� vi�Ƕ�p�g�m�� �t�m�&�a�ˬ���ruy�o��d�u�bׅ�ofi̲s�P�o�a��t� hi¯ia.",21},
	{"-Re�m��n�t�g�m#��t�sob��a��so��SѦud��ղ���˥t�����p���i��gi�r�.",22},
	{"-U��¨�,��rum�ea ��aէ����j�muté�",23},
	{"-U�c�eb�d�aut� �c&�c �vivi&�#���̞�a+��T�%aէc�ה��d�ǧ�s�mu���fi�lm��mu�&�p�¿�p� $l�E�u�cl#ֹ�b�%�٨�oԼu�b� v�i��c�.",24},
	{"-Un�c�b���gl�XV�g�̙a $�t��d�p�ibl�˪vil�s�m�'Cu÷�m%�s��g�'�f�nc$s.",25},
	{"-L�gu�mu�t��hoy�d%a�o���iv�s�hab��c�l��.",26},
	{"-La��gua f�nc��u�ȝd%�.",27},
	{"-A��cu��a�muy�o�r� fi�ل��gl�XX�",28},
	{"-E�r�p��bl���ga�r�ti�.",29},
	{ "-Hab�섚l�cu�d�t�mќtu�i��.",30},
	{"-E�dif%�l�egir,��av�u�� �xt�s�volvi�o���m����r�a �%z ��p�lif�a�&���s�˄ ��ga��au�m&vil��b�c��v���̾��",31},
	{ "-T�busc�$ղ ��m��i���a��u� �zĨmѥ����.",32},
	{"-Da�y..�-Coڣza��t���i��m�i�a f�tu�.",33},
	{"-E��g�i��r�p��bl��i��faz humÆ���s�˄ ��ga�&���Meg�p(tm)",34},
	{"-L��us�p��m�㮩��go.",35},
	{"-P�m��haꅻ�g���q��,��g�p�dr$�umb�a M���-t��cu�ԁo���.",36},
	{"-La ��a�# ha�fu�a�E�p�ibl��n�it��g'�c&dig���c��p���.",37},
	{"-N�t�g�n�g'n�aД�o� ��c�a��c��c&digo.",38},
	{"-La��a��ZHL�#��Ti��.",39},
	{"-Es��pr�� �p�t���q�t��24h �n��ga�s�ld�y��p�z�p��gui��c�ۣ��Univ�so.",40},
	{"-La Ti�� fu�v�t��s�$� v�i�a�c�ip�s�Aho��էlug���vaje,��igr���ѹm��a�.",41 },
	{"-H�at��z��c�c����a�Deb�s�ir�l�xt�i�瑮����c$��volv����q�t�p��p�d�t�mѮ�����",42},
	{"-E�t�n�a 150�C baj�c�o��ext�i��T���ڣd��l�v��t�j��up�vivi��a.",43},
	{"-La�sol���d�mu�t���t�����v�y����ol�m�u���Actu�m�e�# ��ctiv�a��ah��r��g%a�",44},
	{"-E�n�ˬ�n��cu�d�much���ڣz��u��i���P��n�t�p�ocupe���aho��s�$� Ιj��Ԅ ��x�od�volv�#��n�m�id�.",45},
	{ "-D��$���t�baj��dr#�p�� Νd%a� ��x�M��.",46},
	{"-Ya�ab�,�p��� �jo�Bu�o,���nj���s���m�z&�t��f����.",47},
	{"-E��j� �n�s�irs���m������-r�p��",48},
	{"-D��$����gid�b�eg���q����t�ed���diab��Un����y��ڲ� Hi�r��N%͓d�S�� So�r.",50},
	{"-Tambi$�s�كo��t�ed���diab��E�u��i� gob��ԭ��s�d�at��if㿡�mѨ%� M���",51},
	{"-E�u��Ǭab�Ե�p��muy���a��L�dif%�l��uĪnsp��,�u���uy��s�y�u�� b�ǵ�dѨo�xt��l���atm&sf�a��Ti���",52},
	{"-Gobi��n��ádu���p��o� v�a y���u����um�i�r��",53},
	{"-So�t�mp�dif%�l��La hum�id��uv��ab÷n��Ti�r�bid�a v�i�gu�r�nucٮ�y�i�mѮs�p���s�˼o�r�",54},
	{"-Ya�ab�sum�i�r�,�aq�t�%a,��o...",55},
	{"-A�% �d���o�ha�t�mѮ�t�bajo.",56},
	{"-Nu�ȡt�bajo�ZHL� �eg����q�t��24h.",57},
	{"-S�ha�abi�t�v�i�ڲs�M��.",58},
	{"-Seg'n��sc�p�⦓m��j�s�t�t�է�q�t� 27cm x 29cm x 30cm �p�a 10Kg�",59},
	{"-H�at��za���������c$n�Sugi���s�g�ah% fu�a,��m�a��� 껹j���q��.",60},
	{"-Vo�m��u� �v� �p�t��tip�T���Es�mp��m�e�$c��a��vo��t��r��p�.",61},
	{"-La�#�c�䲖 Sol.",62},
	{"-Es��ȴ�pr��Ŭ����s���",63},
	{ "-Es��s�˶��p�t��e�Ti���",64},
	{"-Tod�l��s�m��o��Op�am���d��bajo�su�.",65},
	{"-P��o�oy��%,��ayud���Alg���m�d��p�d�us���:�i���J'pit�,��b�,�o��,���je...",66},
	{"Te�: Env%�urg��a�T�ed� �M���Co��i�: Re�giԂ��c$n��o����Eu���Us����: 32768�Imp�té: Ma���� �mp�atu� baj�c�o�",67},
	{ "-Quiz# haya�lgo��m��j�l�c�go.",70},
	{"-No�էp�b�˃�t�j��up�viv��a�Si�$l��dia���Úev�a �n�vivir%�m#� Φ%a�",71},
	{"-La�cluҼ�op�a��u�m�e�E�bot&�v��̨���clu� y��jo�ab�� A�g'�t���v��t�j��up�viv��a�u���",72},
	{"-Debid�a�fu�t��dia�&�nu�t�s�m��a̺�s&l�f��o�n�����No��$�tig�ah% fu�a�",68},
	{ "-S����g���ctivid��xt�-�h�u�r�E�cu�d�s�����&�fu������",73},
	{"-Lo����r#s���cluұi¡p�su�so�R�u��ʡs�i����v�֧l�v�l���.",74},
	{ "-EҶ�p�&�n�f�ˌt��i b���at��-r�p���o�����eg��a�",78},
	{"-Ya�ab�,���t��a�b��m�ia��rg��",77},
	{"-Si�p�b�m��yaʡǪ��m��-r�p��u��c��li�.",79},
	{"-D����c�am�l��q�t�p�su�i��bu��.",80},
	{ "-T��u�f�g�%f㡤d㿡a��tip���q�t��-r�p�d�s�$�էb�v��l��o",81},
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
	if (fverbo==vAbrir && fnombre2==nEsclusa) { ACCmessage (24); DONE;}
	if (fverbo==vCerrar && fnombre2==nEsclusa) { ACCmessage (25); DONE;}
	
	if (fverbo==vApagar) { ACCmessage (193); DONE; }
	if (fverbo==vEncender && (fnombre1==nPantalla || fnombre2==nConsola)) { ACCmessage (9); DONE; }
	// Preguntas al ordenador
	// Parsea el input del jugador...
	// From the beginning...
    gChar_number = 0;
    gWord_number = 0;
	while (ACCNextWord())
	{
		//writeText (playerWord);
		// S�lo admite una palabra clave
		if (buscador (ordenador_topics_t, playerWord, &flags[fTemp])!=EMPTY_WORD)
		{
			// El ID del topic es el mismo que el mensaje
			ACCwriteln (mensajes_ordenador_t[get_table_pos(mensajes_ordenador_t, flags[fTemp])].word);
			//ACCmessage (flags[fTemp])
			DONE;
		}			
	}
	//if (aux=buscador_tema(ordenador_t, nombres_t[fnombre2]))
	//{
	//	writeText (ordenador_t[aux].respuesta);
	//	DONE;
	//}	

	// Si no encaja con ning�n tema...
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

	if (fnombre1==nEuropa) { ACCmessage (179); DONE; }
	if (fnombre1==nTormenta) { ACCmessage (11); DONE; }
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
			if (fnombre1==nPantalla) { ACCmessage(18); DONE; }
			if (fnombre1==nInterior || fnombre1==nConsola || fnombre1==nControles) 
			{
				ACCmessage (8); DONE;
			}	
			if (fnombre1==nLuz) { ACCmessage (10); DONE; }		
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
			if (fnombre1==nLuz) { ACCwriteln ("P�vi����÷."); DONE; }
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
	// Descripciones 
	if (fverbo==vExaminar)
	{
		if (fnombre1==nSombra) { writeText ("R�ult�����br�iluڲ�─���N�����p�ocup��.^ "); DONE; }
	}
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
			if (fnombre1==nEsclusa || fnombre1==nCompu || fnombre1==nControles)
			{
				ACCmes(21);
				// Aparecen listados...
				ACCoclear (obotonrojo,aConcealed);
				ACCoclear (obotonverde,aConcealed);
				if (CNDonotzero(oEsclusa, aOpen)) { ACCmessage(23); DONE; }
					else { ACCmessage(22); DONE; }
			}
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
// Localidad exterior 
// --------------------------------------------------
if (fverbo==vExaminar)
{
	if (flocalidad==lExterior || flocalidad==lAlmacen)
	{
		if (fnombre1==nCielo) { ACCmessage (7); DONE; }
		if (fnombre1==nJupiter) { ACCmessage (178); DONE; }
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
				DONE;
			}	
			if (fnombre1==nAlmacen || fnombre1==nMole || fnombre1==nEdificio)
			{
				ACCgoto (lAlmacen);
				DONE;
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
			if (CNDonotzero(oPuerta, aOpen)) writeText ("E��c�d�n�r�p���La�u�� ya�#�bi��.^");
			 else ACCmessage(39);
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
	
	if (fverbo==vUsar && fnombre1==nTeclado) { ACCwriteln ("Deb��cٮ�c�Әr�cǔ��c��."); DONE; }

	if (fverbo==vTeclear) fverbo=vEscribir;
	if (fverbo==vEscribir)
	{
		if (fnombre2==EMPTY_WORD && CNDpresent(oTeclado)) { fnombre2=nTeclado; ACCmes(183); }
		if (fnombre2==nTeclado && CNDpresent(oTeclado))
		{
			if (CNDabsent(oCanon) && CNDozero (oPuerta, aOpen)) 
			{
				ACCplace(oCanon, lEntrada);
				ACCmessage(40);
				DONE;
			}

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
					ACCanykey();
					ACCdesc();
					DONE;
				}	
			}

			if (CNDpresent(oTeclado) && CNDpresent(oCanon)) 
			{
				ACCmes (185);
				flags[fCanon]++;
				if (flags[fCanon]<3)
				{
					ACCmessage (186+flags[fCanon]);
					DONE;
				} 
				if (flags[fCanon]==3)
				{
					ACCmessage (189);
					ACCanykey();
					ACCmessage (190);
					flags[fCanon]=0;
					DONE;
				} 
				
				// Ha excedido el n�mero de intentos
				ACCmessage(41);			
				DONE;	
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

	if (fverbo==vFin) { ACCend(); DONE; }

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

	if (fverbo==vSave || fverbo==vRamsave || fverbo==vLoad || fverbo==vRamload)
	{
		//ACCsave();
		ACCwriteln ("N�n�it�c�g� �s�v���t�viaj�-d�e�o���");
		DONE;
	}

	if (fverbo==vPuntos) { ACCscore(); DONE; }
	if (fverbo==vTurnos) { ACCturns(); DONE; }
	if (fverbo==vEsperar) { writeSysMessage (35); DONE; }
	if (fverbo==vTocar || fverbo==vOler) { ACCmessage (56); DONE; }
	// Si ninguna acci�n es v�lida...
    ACCsysmess(SYSMESS_IDONTUNDERSTAND);
    newLine();
}

char proceso1() // Antes de la descripci�n de la localidad...
{
	// Oculta el dibujado
	defineTextWindow (1,1,30,10); 
	clearTextWindow(INK_BLACK | PAPER_BLACK , FALSE);

	// Muestra la pantalla..
	#ifdef GRAPHICS
		ACCpicture(flags[flocation]);
	#endif 

	if (CNDat(lZonaA2)) 
	{
		clearTextWindow(INK_BLACK | PAPER_RED | BRIGHT, FALSE);
		defineTextWindow (15,4,3,3); 
		clearTextWindow(INK_BLACK | PAPER_RED | BRIGHT, TRUE);
	}
	#ifdef GRAPHICS
		defineTextWindow (0,11,32,14); 
	#else 
		defineTextWindow (0,11,32,14); 
	#endif 
	// C�lculo de luz
	// En ZHL todas las localidades tienen luz
	flags[flight]=1; // No est� oscuro

}

char proceso1_post() // Despu�s de la descripci�n
{
	if (CNDat (lPuente) && !localidades_t[0].visited)
		ACCwriteln ("E�o��� ���ga��#�a���d�u�����.");

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
	// Inicializar variables

	clear_screen(INK_BLACK | PAPER_BLACK);

	// Inicializa objetos
	ACCplace(oCaja, lZonaA2);
	ACCplace(oTraje, lEsclusa);
	
	ACCplace (oEsclusa, lEsclusa);
	ACCoclear (oEsclusa, aOpen);
	
	ACCplace (oPuerta, lEntrada);
	ACCoclear (oPuerta, aOpen);

	ACCplace (obotonrojo, lEsclusa);
	ACCoset (obotonrojo, aConcealed);
	ACCplace (obotonverde,lEsclusa);
	ACCplace (obotonverde, aConcealed);

	ACCplace (oCanon, NONCREATED);
	ACCplace (oTeclado, NONCREATED);

	initParser ();                // Inicializa el parser y la pantalla

	#ifdef GRAPHICS 
 		defineTextWindow (0,11,32,14); // Pantalla reducida en 128Kb, Gr�ficos + Texto
	#else 
		defineTextWindow (0,0,32,24); // S�lo Texto
	#endif 

	#ifdef GRAPHICS 
		ACCpicture(9);
	#endif 

// A�adir men� de juego
     clearTextWindow(INK_GREEN | PAPER_BLACK  | BRIGHT, TRUE);
	 gotoxy (13,12);
     writeText (" Z H L ");
     gotoxy (12,14);
     writeText ("1 Jug�");
     //gotoxy (100,80);
     //writeText ("(J) Cargar Partida");
     //gotoxy (100,96);
     //writeText ("1 Tutorial");
     gotoxy (12,15);
     writeText ("2 Cr$dit�");
     //fontStyle (NORMAL);

     gotoxy (9,20);
     writeText ("(C) 2019,2021 KMBR ");

while (1) 
{
	switch (getKey())
		{
			//case 'j': // Cargar Partida
			//break;
			case '2': // Cr�ditos
				clearTextWindow(INK_YELLOW | PAPER_BLACK, TRUE);
				gotoxy(0,13);
				writeTextln ("Z H L");
				writeTextln ("C��a�� KMBR");
				writeTextln ("R�e��5 ^");
				writeTextln ("Ag���ڞ�a�a@zdk.�g �C�l�S#nchez (UTO)");
				writeTextln ("C�pr�i&��gr#fi�s� ZX7�� EѮ Sauk�");
				writeTextln ("Rey�ld�fo� b�DaڣG");
				waitForAnyKey();
				main();
				break;
			//case 't': // Jugar en modo Tutorial...
			//     flags[fTutorial]=1;
			case '1': // Jugar...
				clear_screen(INK_YELLOW | PAPER_BLACK, TRUE);
				flags[LOCATION_MAX] = 8; // N�mero m�s alto de localidad
				ACCability(10,20); // 10 objetos, 20 piedras
				ACCgoto(lPuente); // Localidad inicial, en el puente de mando
				ParserLoop (); // Pone en marcha el bucle principal
				// Parser gets out of the parserloop when the player ENDS the game 	
				// The player wants to abandon the game
				writeSysMessage(SYSMESS_PLAYAGAIN);
				flags[fTemp] = getKey();
				// Restart
				if (flags[fTemp]=='y' || flags[fTemp]=='s' || flags[fTemp]=='S' || flags[fTemp]=='Y')
				{
				
					// Regresa al comienzo 
					main();
				}
				// To the void...
				#asm 
					jp 0
				#endasm 
				break;
		}
	}
}

// ------------------------------------------------------------
// Funciones propias del juego
// ------------------------------------------------------------
