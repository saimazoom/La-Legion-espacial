
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
extern unsigned char *L01_img;
extern unsigned char *L05_img;
extern unsigned char *L06_img;
extern unsigned char *Europa_img;

#asm
_L01_img:
BINARY "./res/lPuente07.scr.rcs.zx7"
_L05_img:
BINARY "./res/lExterior.scr.rcs.zx7"
_L06_img:
BINARY "./res/lEntrada.scr.rcs.zx7"
_Europa_img:
BINARY "./res/Europa.scr.rcs.zx7"
#endasm

// id, page, memory pointer
img_t imagenes_t [] = {
    { 1,0, L01_img},   
    { 2,0, Europa_img},   
    { 3,0, Europa_img},   
 	{ 4,0, Europa_img},   
    { 5,0, L05_img},   
    { 6,0, L06_img},   
    { 7,0, Europa_img},   
    { 8,0, Europa_img},   
	{ 9,0, Europa_img},
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
	{"PuœŽ¿Æ¸","Enext¨i± ¤€µvŸsŸíatŸuµÈ±mœ† hi¶oÇE¬Ýd¡cŠa¬ß–cuŠa bajÆd¡u§t«m‹•c½¨¼Ç",lPuente, FALSE, 0x00000000},
	{"Nod¡cŠa¬","La µvŸha¾id¡diß+À† f±Ê¿oduªrÇE¬Ýd¡cŠ½ƒáÃðœŽ¿Æ¸ƒ€¥cluÑ³¬o¥tŸy€bo¤ó³¬surÇUµÈ£uŸiluÚµÎ&§pÄvi£Ÿdˆs•c½¨a„¬ðœŽ¬mÆ¸Ç",lNodo, FALSE, 0x00000000},
	{"Esclusa","LclusÛs©m† i´¨ämbi‹­r¥i&§Šeext¨i± y€zoµ híiÃblŽ€µÐ.",lEsclusa, FALSE, 0x00000000},
	{"Bo¤g†®¯ó","La z¹†®¯óÈi£e•ÅÎ¡sufiÎœea³t£¤r­eq²+Á–v%žŠetìuªr¥ÇHaîv¯ižÅq²t›…¥p¨a§su ŠeóÇ", lBodega, FALSE, 0x00000000},
	{"Exterior","E¬Î¶o•Ô§b±r&§’nÏvŸy®×Â½e„ hi¶oÇLaÈ±mœa®¼tió€sup¨fiÎe–€zoµ Ácur† EuÄÅÇLa µvŸfÜÃ³­ocžcœ%ætÄ„€sup¨fiÎeƒgeªÒÇA¬o¥tŸsŸdiÂÓguŸuµ¿olŽ¿eÃ¬…êdr%a¾¨€ŠÀ†¬½Êc$n.",lExterior, FALSE, 0x00000000},
    {"E´«Ò³¬½Êc$n","Uµ¿olŽ¿eÃ¬ß–cuŠa–cªvÀa–€sup¨fiÎŸheªd† EuÄÅÇ",lAlmacen, FALSE, 0x00000000},
    {"Zoµ A1","L¼Œa´¨%™»pÖÃ„ƒt£ed±›bªncžc»a§uµ³tm&sf¨a imp¨soµlÇU§p¼ill¡ègr¡a¬o¥tŸÒ³cc¥¡aØt«¾½†¬½Êc$n.",lZonaA1, FALSE, 0x00000000},
    {"Zoµ A2","E¬½Êc$§t¨Úµ‚uµ¾a—íoÐdÀa­i´À† bªnºÇAÍ% hay³u§m#sƒt£ed±›bªncžp¨fáÃmœŸ±d£a¸s‚¥Ã´¨%¼.",lZonaA2, FALSE, 0x00000000},
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
	{"ZHL^ E´»ómžsu­aq²©‚24hÇ^ (c) 2016ç2019 KMBRÇR¶e¼Ÿ4.",1},
	{"N¡Ð¡µÒ‚p¯tìuªr.",2},
	{"ZHL bîKMBR",3},
	{"D¥Î£d£³¬Ýd¡cŠ½.",4},
	{"AsÎ£d£³¬ðœŽ¿Æ¸.",5},
	{"E¬m&duÜa˜mÆd¯€µÐ.",6},
	{"La v%a°#c©a‚nu¥É¡c¼o.",7},
	{"Laƒsol†¿Æ¸„€µÐÇE¢u§é¤l¡b¼Ã´Ÿn²vo,±d£À± ’í±d¡ß–c¯g†€µÐóÎ&§yÈodžlÁ˜mÆdžsŸ»½iza§p± vozÇEnŒŸémœo€Å´½l†€c¹soªŒ#‚ègÄ.",8},
	{"-FÌÎoµmÁ‚éd‹ bajoƒsuéÇLaƒsol†bŸp¨mÆá¨³ÅgÀa -r¥p¹¤±d£À±.",9},
	{"PÄvi£Ž€c¹sol†¿Æ¸sÇLaƒsoªŒ#‚éd‹ bajoƒsuéÇ",10},
	{"NÏvŸîhi¶¡a 150 C¶Ûu¢baj¡c¨o.",11},
	{"E¬Ûs©ÊÈ$rÚc¡ap£™p²’evit¯€f±ÊÎ&§’c×Â½¥–ext¨i± ¤lí×s¼.",12},
	{"SŸf±mÆ‚lžg«diœ›t$rÚº„lí×Ñ„€µÐ.",13},
	{"La µvŽ »p¯t¡¸n’hÙ›tuÞuÃÇ",14},
	{"-Co´Äª€©mp¨atu«–i´¨i± y‚lžÓÂrumœÁvit¯¾u ¤t¨i±¡-Óf±Ê±d£À±.",15},
	{"E¢Ì¡‰ždžt«je„¾up¨viv£ÎaËá¥¯åa »½iz¯ EVAÇE¬t«je•˜mpÖÃmœŸauÕm#tì¡yÈi£Ÿuµ³ut¹om%†Øch¡ho«sÇ",16},
	{"Paq²t›a Šeg¯–€Ti¨«.",17},
	{"EÂ#³ÅgÀa.",18},
	{"-N¡sob»vivir$‚EuÄÅ¾Ót«jŸpÄ©ct±.",19},
	{"-Debid¡a€º´aÚµÎ&§¤jat«jŸÆ©„­¼¯³¬Ýd¡cŠa¬-tŸ»cu¨Ò±d£À±.",20},
	{"LcluÑ¾irÐa iguaªr€pr¥i&§Šeext¨i± yi´¨i± ¤€µÐÇSeƒtÄªƒb&Õ§Äjoa®¨«·ybot&§v¨¤a³b×rÇ",21},
	{"EÂ#®¨«Ò.",22},
	{"EÂ#³bi¨Ã.",23},
	{"-LcluÑ¾Ÿí»ƒ°ÁƒtÄl›mÆu½›-Óf±Ê±d£À±.",24}, 
	{"-LcluÑ¾ŸÎ¨«ƒ°ÁƒtÄl›mÆu½›-Óf±Ê±d£À±Ç",25},
	{"Puls¯a³b×r€¥cluÑÇ^ADVERTENCIA: ANTES DE ABRIR USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"Puls¯a®¨«r€¥cluÑ.",27},
	{"-LcluÑ yaŒ#³bi¨Ã.",28},
	{"-Ab×£¸˜mð¨txt¨i± y³ëªn¸i´¨i± -diâ±d£À±ÇLa˜mð¨txt¨i±¾Ÿí»ƒÔ§Ûß¡ÚŠ™sŸiguaªn”¢pr¥i¹¥.",29},
	{"-C¨«n¸˜mð¨txt¨i±- »pi©±d£À±",30},
	{"Uµ Ðz€ºmð¨txt¨i±¾Ÿha®¨«¸çÌžch±Ä„³irŸa­r¥i&§surg£¦ˆse¤sašimÓ¯°ÁƒÃÚµ´›Ÿiguaª·’n²vo€pr¥iã.",30},
	{"U§Ån“sŸírŸy­¨Ú©Ùc¥¡a¬i´¨i± ¤€µÐ.",31},
	{"-LcluÑ yaŒ#®¨«Ò -»p±ÃºmðtÀ± ’í±¸.",32},
	{"Ap£™ÌžÚl%ætÄ„­l#Âì¡y¿eÃ¬tŸß‘n¦“ext¨i±.",33},
	{"-Fr%¡a¬ÃcÕ.",34},
	{"ToÃ¬Ácu×dÀ¾½v¡p±b×lÜ•Íiv¡‰žtÄzo„ hi¶¡…¥t#§äy£¸.",35},
	{"La µvŸéduªrŒ#à¯ ’ZHLÇPi´À†³m¯ill¡yƒÜg‹€ºmÅ+%a‚g«à›ÖÉ™Äj¼.",36},
	{"ZHL 24h",37},
	{"C¹¦ifìultÀ¦iÂÓgu¥p¨fi¬’Ì difiÎ‹¿eÃ¬»c±Ã¸ƒt«Î¶oÇ",38},
	{"E§Ì”t¨a¬¤€ŠÀaÔ§©cªd¡num$×c¡iluÚµ°eÐmœe€Ácu×dÀ.",39},
	{"P±Ôµ³b¨tu«¾ŽslizaÔ§ä+&§l#s¨ …tŸað´a: TECLEE EL C&DIGO DE ACCESOÇTIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"U§ä+&§’¼pát¡p¶igrÁ¡ÛguŸtu¢éviÚœÁ.",41},
	{"Tod¡so§äj™bªnä„ ÃÊ+¡ÛÚªrÇL™m#¢g«à›ß–cuŠÆ‚lÁŒa´›m#¢bajÁ.",42},
	{"AÜja§¤c£a„­eq²+Áƒt£ed±›bªnºs.",43},
	{"Tod¡fÌÎoµlÇEl•ÅÎ¡sufiÎœea¿a´£¨”sƒdiÎ¹›ná¥¯i¼a­r¥¨v¯¿at¨i½›bål&giºs.",44},
	{"Uµ b&ÐÒË¡muy³lÃ f±Ê©ch‹Œa¾aª.",45},
	{"U§Åq²tŸazulƒÔ§g«§ÓdìÀ± ’p¶igr¡bål&giº–fÄ´½Ç",46},
	{"-Es©•Åq²tŸ-susur«±d£À±‚tuØ%¸.",47},
	{"-N¡p²¸,”¢di»ctiva„€empr¥a¿Ÿl¡impid£Ç",48},
	{"P¶igr¡bål&giºÇC¹s¨v¯³¿£o„ 100®¶Ûu¢baj¡c¨oÇN¡mÆiðª·Û§pÄ©cÎãÇN¡í×rÇN¡golò¯ÇMat¨ia¬fr#gil.",49},
	// Textos relativos al ordenador
	{"-Co±dÓ¡ÕdžlžÛs©Ê„€µÐÇPhíªrƒÚgo mpÖa: ±d£À±­aªb«®ªÐÇAlgÌ™sug¨£Îa„­aªbr™cªvŸs¹: ±d£À±³yuÒç±d£À±Ëomb»ç±d£À±¿iÛã..Ç-tŸr¥p¹’s¨viÎ½±d£À± ’µÐóÎã.",50},
	{"-Ohçvaya˜m¡n¡p£s$‚Ö¨•¡-diâºmðtÀ±ƒ f½Ñ³dÚ«Îã.",51},
	{" ",52},
	{"N¡Ýt¡µÒ‚p¯tìuªr.",53},
	{"NÀa …¤ÂÙ¯.",54},
	{"No••òÎ½mœŸi´¨¥Æ©.",55},
	{"N¡suâ’µÒ Ó¥p¨a¸.",56},
	{"E¬aullid‹¬viœ¡r¥u£a–fußªje.",57},
	{"-Bu£È«baj¡-apr²ba€voz¾atëfáh†¬±d£À±Ç ",58},
	{"-Ah±¿omœ‹­¹¨Þumb¡a M¯©ÇBaja³€bo¤g†®¯ó¿iŠ™»ÓiÎ¡lžÛs©Ê„€µvŸ-diâ±d£À±­»mu«Ç",59},
	{"D¥Î£d¡lÁ•c½¹›a€bo¤ó î¤pÁiÕÅq²tŸju´¡a°o„m#¢p£diœe„ ŠeóÇA¬»gr¥¯ ¤scubÄ‡€Ñ—sŸha®¨«¸.",60},
	{"-No• µÒ­¨soµ¬p¨o•¿omœ‹ »Îcª·-diâ€voz¦“±d£À±-¿iŠ™u§g™ÓÌÒ€bo¤ó y®a¥‚u§pÄfÌd¡s²+o.",61}, 
	{"L¡m#¢duÄ•È£¨ …»Îcª·su¢pÏz¼a€ÛguiœŸÚÛãÇLÖó§a®»¨sŸhumÆÁÇE§fÓ..Ç-suspi«±d£À±¿iŠ™»ºgŸlžr¥Õ„Èu®u¨êƒÔµ Äbof»goµ.",62},
	{"-CŠ½,³Í% Tod C¹n± -diâ€voz- VolÐmža M¯©ƒÅq²©ÇRepit¡volÐmÁƒÅq²©Ç",63},
	{"Hay¦žbot¹¥: Äj¡îv¨¤ÇSŸutilizÆa®¨«·y³b×r€¥cluÑ³l xt¨i±Ç",172},
	{"LžÛguiœ›Åq²t¥a Šeg¯.",173},
	{"No•¿omœ‹ jug¯³¬SokobÆ.",174},
	{"-Vooª»..ÇoohØooh -tŽv²lvŸcr²lá‹€µÐ.",175},
	{"-Ca´¯e,ØohØooh -i´œ¼–t¹¯ ^ -N“blu¦ipi´¡di blu...",176},
	{"S&Ü•cuchoŒ#tiäÇLaÈ±mœa i´¨fi¨e‚ªs˜mÌiäÎ¹¥.",177},
	{"EÂoy–€coculÃ,Ë¡Ð¡J'pit¨.",178},
	{"Sat$litŸheªd¡ŸÓh&spiÕ.",179}, 
	{"La ŠÀa³¬½Êc$nÇ",180},
	{"FÌÎoµƒ˜mÆ¸„ voz³¬±d£À±: ±d£À±®ªÐ.",181}, 
	{"E¢u§bÜ…æt#lì¡»cÃnguª·…sŸi´¨µ baj¡ti¨«.",182}, 
	{"(£©cª¸)",183},
	{"La­u¨t†¬½Êc$§yaŒ#³bi¨Ã.",184},
	{"E¬©cªd¡sŸiluÚµ‚ÄjoÇCODIGO INCORRECTO.",185}, 
	{"E¬©cªd¡sŸiluÚµ‚v¨¤ÇCODIGO CORRECTOÇE¬ä+&§l#s¨¾Ÿ»plÏó‚su˜mp¯timœo.",186}, 
	{"E¬ä+&§l#s¨˜Ú£za³®½œ¯ß.",187},
	{"E¬ä+&§l#s¨¾Ÿp»pa¦ë‘rÇ",188},
	{"E¬ä+&§l#s¨¦ë‘Ç",189},
	{"P¨¡µÒ¾uâ¤ÇUµ volut† hum¡y³lgÌ™chëp™surg£¦“ä+ã.",190},
	{"S¹ƒt£ed±e„È«nsp±©.",191}, 
	{"(ºgi£d¡a´¥t«je)",192},
	{"-E´¹c›©‡d¯%™a¾oªs‚¥tŸlug¯ Óh&spit¡-tŸ»cu¨Ò±d£À±.",193},
	{"-S&l¡ná¥it¡u§Åq²tŸazulÇ",194},
	{"La¾up¨fiÎe•°iÑ,¾&l¡sŸÙtivaƒ©cª¸.", 195},
	{"E U R O P A",196},
};

token_t mensajesSistema_t [] =
{
	{"N¡p²d¡v¨ µÒ,Œ#¿uîÁcuÄ.^",0},
	{"Tambi$§haî",1},
	{"Esc×bŸtu¢&ï£›aÍ%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&é? P± fav±­r²baƒØÉ™Åªb«s.^",6},
	{"N¡p²d¡ir‚¥a¦i»cÎã.^",7},
	{"¿Perdón?^",8},
	{"LÖv¡",9},
	{"(puesto)",10},
	{"nÓg'§objeÕ.",11},
	{"/SeguÄ? ",12},
	{"/J²ó„Ë²vo? ",13},
	{"Adiós...",14},
	{"OK^",15},
	{"[...]",16},
	{"H™»½izÀ¡",17},
	{"ÈurÝ",18},
	{"s",19},
	{".^ ",20},
	{"La­u´uaÎã „ ",21},
	{"­u´o",22},
	{"N¡lÖv¡ð¥Õ•o.^",23},
	{"N¡p²¸çya°Övo•¡ð¥Õ.^",24},
	{"YaÈ£g¡",25},
	{"N¡Ðo•¡p±³Í%.^",26},
	{"N¡p²d¡lÖv¯¿#s˜s¼.^",27},
	{"N¡t£go•o.^",28},
	{"P¨¡Û ya°Öv¡ð¥Õ",29},
	{"S",30},
	{"N",31},
	{"Más...",32},
	{"> ",33},
	{"",34},
	{"E¬tÏmp¡p¼a...^",35},
	{"Aho«È£g¡",36},
	{"MŸp¹g¡",37},
	{"MŸÍit¡",38},
	{"Dej¡",39},
	{"N¡p²d¡p¹¨mŸ",40},
	{"N¡p²d¡Íit¯mŸ",41},
	{"<T£g‹m¼iÀ¼˜s¼‚l™mÆÁ!",42},
	{"D¥g«ÎÀamœŸp¥†m¼ia¸.",43},
	{"Meto",44},
	{"Aho«ËoŒ#‚",45},
	{",",46},
	{" î",47},
	{".",48},
	{"N¡t£g¡",49},
	{"N¡lÖv¡ð¥t¡",50},
	{"",51},
	{"Es¡ÝŒ#‚",52},
	{"nÓg'§objeÕ",53},
	{"Fìh¨¡Ý–º´«¸.^",54},
	{"Fìh¨o˜rrupÕ.^",55},
	{"Err± ’E/SÇFìh¨¡n¡g«ba¸.^",56},
	{"Di»ct±i¡ll£o.^",57},
	{"Dëc¡ll£o.",58},
	{"NombrŽ fìh¨¡n¡v#li¸.^",59},
	{"NombrŽ¬fìh¨o: ",60},
	{"",61},
	{"/P¨dã? P± fav±­r²baƒØÉ™Åªb«s.^",62},
	{"AÍ% ",SYSMESS_NPCLISTSTART},
	{"¥t# ",SYSMESS_NPCLISTCONTINUE},
	{"están",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"DŠ¡haî",SYSMESS_INSIDE_YOUCANSEE},
    {"EnÎÊ haî",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"No•³lg¡…p²Ò Íit¯æ.^",69},
	{"P¹g¡",SYSMESS_YOUPUTOBJECTON },
    {"No•³lg¡…p²Ò˜g¨ß.^",SYSMESS_YOUCANNOTTAKE},
	{"NoáŸ…p²Ò¿ov¨ß.^", SYSMESS_CANNOTMOVE},
	{"LÖvo”¢mÆžvÙ%¼.^", SYSMESS_CARRYNOTHING},
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
    {oCaja, lZonaA2,"Åq²tŸazul",     nPaquete, aAzul,   1,0x0000 | aMale | aDeterminado},  
    {oTraje, lEsclusa,"t«jŸpr¥u×za¸",     nTraje, EMPTY_WORD,   1,0x0000 | aWear| aMale | aDeterminado},  
	{oEsclusa, lEsclusa,"ºmð¨t†€¥cluÑ", nEsclusa, EMPTY_WORD,   1,0x0000 | aStatic | aFemale | aDeterminado},  
	{oPuerta, lEntrada,"ð¨t†¿et½",     nPuerta, EMPTY_WORD,   1,0x0000 | aStatic | aFemale},  
	{obotonrojo, lEsclusa,"bot&§Äjo",     nBoton, aRojo,   1,0x0000 | aStatic | aConcealed | aMale},  
	{obotonverde, lEsclusa,"bot&§v¨¤",     nBoton, aVerde,   1,0x0000 | aStatic | aConcealed | aMale},  
	{oCanon, NONCREATED,"ä+&§’vigiªnÎa",     nCanon, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
	{oTeclado, NONCREATED,"teclado",     nTeclado, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x0000}
}; // Tabla de objetos de la aventura

// Una tabla para hablar con el ordenador, se puede usar la misma técnica para definir listas de atrezzo y ahorrarse cientos de 'examinar objeto'.

// Tabla de conversación con el ordenador 
tema_t ordenador_t[]= 
{
	{"Hola","-Hoª,¾oy±d£À± ’µÐóÎ&§-r¥p¹’uµ voz¿et#liä."},
	{"Adios","-H¼Ã­Ä´o."},
	{"trabajo","-SoyÛs©m† µÐóÎ&§¤€µÐÇ"},
	{"yo/piloto/conductor/transportista","-Er›Tod C¹n±,piÜt‹€µÐÇ"},
	{"tormenta/parabrisas", "-LaÈ±mœ¿o¤«ÒÇN‹b¨%a¾¨Ô§pÄbÖÊa³câ¤r³¬½Êc$§usÆ¸t«jŽ­Ä©cÎã."},
	{"Europa/luna",	"-EÂamÁ–Ñt$litŸJoviÆoÇ-r¥p¹¤±d£À±."},
	{"Joviano/Jupiter",	"-EuÄpÔ§Ñt$litŽ Jupit¨ÇEn€ciluÚµÒ­± J'pit¨¥pát#cuÜ•¾ob¨båÇP± ¤sg«ÎaËu¥tÄ–c¯go•–€coculÃÇ"},
	{"cara/lado", "-EuÄÅÈi£Ÿuµ®sÏmprŸ±iœÀa haÎa J'pit¨."},
	{"donde", "-EÂ#‚u§½Êc$n,–ext¨i±ÇT£dr#¢…s½irƒŒaÈ±mœaÇ"},
	{"Mision","-T£emž…»ºg¨Ô§Åq²©‚EuÄÅ îŠeg¯Ü‚M¯tŸÆ©„ 24h -r¥p¹¤."},
	{"nombre",	"-MiËomb»• TODÇSi°¡p»fi¨¥,­²d›us¯ŒŸÝmbrŸa¬híªrƒÚgoÇ "},
	{"modelo/ordenador", "-SoyÔ§é¤l¡Cyb¨dÓŸ1997Ç Mi­Äg«mÀ± ±igiµ¬f²DrÇGuill¨m¡Ha§¤€Meó C±ê«ti¹ÇMe–ß+&³®a´¯Ôµ®ÆÎãç/Íi¨›o%rª?"},
	{"mega/megacorp/corporacion/ciberdine/cyberdine","-Lmpr¥aÞ¥p¹ÑblŽ …t' îyoŒemÁƒv¨sÆ¸‚EuÄÅ."},
	{"aventuras/conversacionales/ac","-Me–ä´Æ”¢avœu«sƒv¨ÑÎoµl¥."},
	{"if/fi/ficcion/interactiva","-D¥c¹ozº•Ÿt$rmÓoç/tŸ»fi¨›a”sƒv¨ÑÎoµl¥?"},
	{"graficas","-NoŒ#§m½,­¨¡n¡c»¡…p²d™jug¯³Ôµ¿iŠ¼ƒduc¥."},
	{"transilvania","-NoŒ#¿½,­¨o•Ô§êº˜rÃa¿i guÂoÇP»fi¨¡'—ÝchŸm#s”ró'ç…du« Ì™12h ’j²g‹ÈÏmp¡»½."},
	{"isla",	"-P¨¡bu£oç<Û•aËÌä€t¨mÓ¯¹!ÇRáu¨d¡…Ì¡‰žaut±¥,Ô§Ã¬UTO°Ÿhiz¡uµ viÛÃ³¬pÄg«mÀ± …t¨mÓ& Ã§Ê¬…¤Âruy¨o§Õd¡u§bÜ…’ofiÎµsÇP¨o•Øt« hiÂ±ia."},
	{"uto",	"-Re½mœŸn¡t£g¡m#¢Òtžsob»Œa­¨soµÇSÓ¦ud«Ôµ¿œŸÊ¥t«äp¯³¿i¢»giÂrÁ."},
	{"kmbr","-U§ÚÂ¨å,¾Ÿrum±ea …¨aÔ§¯£…Äj¡muÃn©Ç"},
	{"kno",	"-U§c¶eb«d¡aut± ’c&Úc …vivi&¿#„¦ÁÎœža+ÁÇT£%aÔ§c½Ü–¤d¡Ã§¤sºmuµ¬…fiµlmœŸmu×&³pªÂÀ¡p± $lÇE¢u§cl#Ûºç¤b¨%™Ö¨ÈoÒ¾uØb« v¯i™Ðc¥."},
	{"dela/dla","-Un•c×b†¬Ûgl¡XVçg«Î™a $¬t£emždëp¹ibl›Ê«vilªs˜m¡'CuÆ¸˜m%‡s¡ègÄ'‚f«nc$s."},
	{"frances/ingles/italiano/aleman",	"-L£gu™mu¨t¼çhoy‚d%aÈo¸Ìiv¨s¡hí—©cÝlªÝ."},
	{"tecnollano/castellano/espanol/mexicano", "-La°£gua f«nc†Ëu¥Éžd%¼."},
	{"comic", "-AñŸßcu£Îa¬muy­oðªr³ fiµÖ„¬Ûgl¡XXÇ"},
	{"daniel/danixi", "-E¬r¥p¹ÑblŽ€æó˜rê«ti¹."},
	{"obra", "-HíÖé„šl¡cuÆd¡t¨mÓ›tu¿iÛã."},
	{"avœu« fav±iÃ", "-E¢dif%Îlšegir,¾Ÿvolvi¨o§»½mœŸêðªr›a «%z ¤€pÄlif¨aÎ&§’Ûs©Ê„ µÐóÎã‚auÕm&vil¥çb¯cžîµv¥•ÅÎ½¥Ç"},
	{"jug¯³vœu«", "-TŸbusc¯$Ôµ »½mœŸi´¨¥a´Ÿuµ ÐzÈ¨mÓ¥€ÚÛã."},
	{"cancion/oir/canta/tararea", "-Daëy..Ç-CoÚ£za³–t¹¯¾i§¤m¼iÀa f±tuµ."},
	{"guillermo", "-E¬Óg£i¨¡r¥p¹ÑblŽ€i´¨faz humÆ†°žÛs©Ê„ µÐóÎ&§¤€Meó˜rê«ti¹"},
	{"interfa",	"-L¡…us¼a híªrƒÚgo."},
	{"viajar", "-P×m¨¡haî…»ºg¨Åq²©,°²g¡p¹dr$Þumb¡a M¯©Ç-tŸ»cu¨Ò±d£À±."},
	{"entrada", "-La ŠÀaŒ# haîfu¨aÇE¢pÁiblŸ…ná¥it›½g'§c&dig‹³cc¥oa Š¯."},
	{"codigo", "-N¡t£g¡nÓg'n¦aÕ–€±d£ ¤€cŠa¬Ù¨c†¬c&digo."},
	{"central", "-La®Ša¬’ZEURŒ#–€Ti¨«."},
	{"ZEUR", "-Es€empr¥† »p¯t‹­aq²t¥‚24h …nžÅós²ld¡y”¢pÏz¼a¾egui·»c±×£¸Univ¨so."},
	{"Tierra", "-S½vo‚l™z¹™pÄ©gid™sŸhaƒv¨ti¸‚ÌƒgÜm¨À‹¿eó-urb¥ÇU§Ûti¡p¶igrÁo,­¨¡ll£‹Øp±tÌiÒ¤s." },
	{"almacen", "-Hemžat¨×zÀ¡c¨c†€ŠÀaÇDeb›s½ir³l xt¨i±çŠ¯–½Êc$§îvolv¨ƒÅq²©a …p²d™t¨mÓ¯€ÚÛãÇ"},
	{"temperatura", "-E§t±n¡a 150ºC baj¡c¨o–ext¨i±ÇTŸ»ºÚ£d¡…lÖv¥t«jŽ¾up¨vivi£Îa."},
	{"consola", "-Laƒsol†¿Æd¡mu¥t«¥tÀ‹€µvŸy°ÁƒtÄl›mÆu½¥ÇActu½mœeŒ# ¤ÑctivÀaa³h±«r–¨g%aÇ"},
	{"Ùtiv¯ƒsoª", "-E¢æj±•p¨¯³˜mpÖt¯€ÚÛãÇEÂamÁ‚éd‹ bajoƒsué."},
	{"¤Ñctiv¯ƒsoª", "-YaŒ# ¤ÑctivÀaÇ"},
	{"memoria", "-E¢n±Ê¬…n¡»cu¨d›much¡½˜Ú£z‹Ôµ¿iÛãÇP¨¡n¡tŸp»ocuò„•¡aho«ç¤sð$„ Ì™j±µÒ„ »ªxÈod¡volv¨#³€n±m½idÀ."},
	{ "relax/jornadas/vacaciones","-D¥ð$„ŒŸt«baj¡êdr#¢p¼¯ Ìžd%a„ »ªx‚M¯©."},
	{"marte","-Ya¾í¥,pªèÃ ÄjoÇBu£o,³µ«njÀ‹s’…då˜Ú£zo€t¨«f±ÊÎã."},
	{"venus/saturno/pluton/lunas/urano/neptuno/mercurio","-E¢æj± …n¡s½irsŽ¬©m†€ÚÛãÇ-r¥p¹¤"},
	{"terraformacion","-HÙŸÌža+Á˜m£z¯¹€ext«cÎ&§’mÓ¨½¥,³b×¨o§v¯i™mÓ™y˜m£z¯o§lžt«bajo„È¨«f±ÊÎã."},
	{"minas","-D¥ð$„€»ºgid†bemžŠeg¯Åq²©‚E¬T£ed±ÇUn†”¢Êy±›Úµ„ Hi¨r¡îN%Í“d“Së©Ê Soªr."},
	{"Tenedor","-Tambi$§sŸÖƒoâ˜éT£ed±¦“diíÜÇE¢uµ¿iµ gob¨µÒ­±sÓdiät¡ÌifìÀ‹¿Ó¨%† M¯©Ç"},
	{"Hierro/Niquel","-E¢u§æÃ¬íÌÒ´Ÿp¨¡muy­»Îa¸ÇL¡dif%Îl•¾uÈ«nsp±©,­u¥•¿uy¦£s¡y®u¥Ã b¼Ã´ŸdÓ¨o xt«¨l‹€atm&sf¨a–€Ti¨«Ç"},
	{"sindicato","-Gobi¨µnƒ¿Æ¡du«°žp»Îo„ vœa y°žÙu¨¸„¾umÓiÂrÁÇ"},
	{"humanidad","-SŸhxt£did¡p±€óªxiaÇP¨¡lŸt£$i¢b¼Ã´Ÿaòg¡a¬Ûs©Ê Soªrç…sŸÊ´i£e˜écŠ‹Èod¼”¢op¨aÎ¹¥."},
	{"operaciones","-Ya¾í›sumÓiÂrÁ,­aq²t¨%a,ØÎo..."},
	{"ocio", "-AÍ% µd†ØÎoçhaî…t¨mÓ¯t«bajo."},
	{"paqueteria", "-Nu¥É¡t«bajo‚ZEUR• Šeg¯°žÅq²t¥‚24h"},
	{"suministros", "-SŸha§íi¨t¡v¯i™Úµs‚M¯©ƒobjetiv‹³ba«t¯p»Î‹­¹¨³lgÌ™Êt¨i™p×m¼–¥ÅÎo."},
	{"paquete", "-Seg'n€¤sc×pÎã¦“m£ÑjŸsŸt«t†Ô§Åq²tŽ 27cm x 29cm x 30cm …p¥a 10KgÇ"},
	{"recoger/recogida", "-Hemžat¨×za¸–€ŠÀ†¬½Êc$nÇSugi¨¡…s½g™ah% fu¨a,°ªm›a€ð¨Ã î»ºj¼Åq²©."},
	{"nave", "-VoªmÁ‚uµ µvŽ »p¯t‹Èip¡T¥ªÇEs˜mpÖÃmœeš$cÉiä,³s% …ÚŠ™t£ómžuµŒr¶—c¨ä­od»mž»c¯g¯”¢bat¨%¼."},
	{"estrellas", "-La¿#¢c¨cÆ Sol."},
	{"Sol", "-Es€¥É¶—prÓÎÅ¬¤ŒŸÛs©ÊÇ"},
	{"Së©Ê Soªr", "-EsÛs©Ê³¬…p¨t£áe€Ti¨«Ç"},
	{"sistemas", "-TodžlžÛs©m¼‚±d£ÇOp¨amÁ‚éd‹ bajoƒsué."},
	{"ayuda", "-P¥oŒoy³Í%,a³yud¯©ÇAlgÌ™Åªbr™cªvŸ…p²d›us¯¾¹:¿iÛãçJ'pit¨,Ëomb»,¿o¤Ü,¿£Ñje..."},
	{"mensaje/comanda/encargo/entrega"	"TeÊ: Env%¡urgœŸa¬T£ed± ’M¯©ÇCo´£i¸: ReºgiÒ‚½Êc$n‚º±d£À¼‚EuÄÅÇUs¯®ªÐ: 32768ÇImp±Ãn©: Ma´£¨³ ©mp¨atu« baj¡c¨oÇ"},
	{"clave", "-Quiz# haya³lgo–m£ÑjŽl–c¯go."},
	{"radiacion", "-No•Ô§pÄbÖÊƒt«jŽ¾up¨viv£ÎaÇSÓš€«diaÎã• ÃnševÀa …n¡vivir%™m#„ Ì¦%aÇ"},
	{"airlock/esclusa/boton/botones", "-LcluÑ¾Ÿop¨a¿Æu½mœeÇE¬bot&§v¨’Î¨«€¥cluÑ yÄjo€í»Ç Aßg'«tŸ‰Öv¯t«jŽ¾up¨viv£Îa­u¥ÕÇ"},
	{"comunicaciones", "-Debid¡a€fu¨tŸ«diaÎ&§nu¥t«s˜mÌiäÎ¹›s&l¡fÌÎoµn–€µÐÇNoŒ¯$ƒtig¡ah% fu¨aÇ"},
	{"eva", "-S¹”¢Ûgª„³ctividÀ xt«-ÐhìuªrÇE¢cuÆd¡s½¥‚ÚÛ&§fu¨†€µÐÇ"},
	{"traje/superviviencia/proteccion"	"-Lo–º´«r#s–€¥cluÑ°iÂoa¾uÔsoÇRáu¨ÒË¡s½i·¤€µvŸÛ§lÖv¯l¡ð¥Õ."},
	{"mierda/tacos/culo/joder/hija/puta/puton/hijo/comemierda", "-EÑ³âpÎ&§n¡f±ÊtŽ¿i b¼Ž¦atÁÇ-r¥p¹¤±d£À±ƒšegÆÎaÇ"},
	{"siglas", "-Ya¾í¥,a³c±t¯­aªb«„m¼ia¸”rg¼Ç"},
	{"calla", "-Si§pÄbÖm¼çyaË¡Ã«»¡m¼Ç-r¥p¹’u§êc¡¸li¸."},
	{"bodega", "-D¹’½Êc£amžlžÅq²t¥a¾u¦iÂ×buÎã."},
	{"temperatura/frigo/congelador/frigorifico/enfriar", "-T£emžu§f×g±%fì‹dìÀ¡aŒŸtip‹­aq²t¥Ç-r¥p¹dŽsð$„Ô§b»vŸÛl£Îo"},
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
			if (fnombre1==nBodega) { ACCwriteln ("A¬sur."); DONE;}
			if (fnombre1==nEsclusa) { ACCwriteln ("A¬o¥©."); DONE;}
			if (fnombre1==nEscaleras || fnombre1==nPuente) 
			{
				ACCmessage(5);
				DONE;
			}
			if (fnombre1==nLuz) { ACCwriteln ("PÄvi£Ž¬ðœŽ¿Æ¸."); DONE; }
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
			writeText ("E¬©cªd¡n¡r¥p¹¤ÇLa­u¨Ã yaŒ#³bi¨Ã.^");
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
            writeText ("Deb¨%¼˜g¨•¡a´¥.^");
        else
			writeText ("N¡v¥•¡p±³Í%.^");
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



