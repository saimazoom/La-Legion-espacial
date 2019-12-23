
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
img_t imagenes_t [] =
    {   
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
	{"Pu›Ÿ’mÉ¹","Uµ¯uz²mb°iµÈi+ŸlžÒÂrum›o„¸l±®#lid¡ÚŠ¼—ext¨i±¾ŸíatŸuµÈ±m›… hi¶oÇE¬Ýd¡cŠa¬¤€µvŸß—cuŠa bajÉ¹t«mŒ”c½¨¼Ç",lPuente, FALSE, 0x00000000},
	{"Nod¡cŠa¬","La µvŸha¾id¡diß+À… f±Ì¿oduªrÇE¬Ýd¡cŠ½ƒàÃó›Ÿ’mÉ¹ƒ€¥cluÑ²l xt¨i±²¬o¥©æy€bo¤ð²¬surÇUµÈ£uŸiluÚµÍ&§pÅvi£Ÿd†s”c½¨a„¬ó›Ÿd–mÉ¹Ç",lNodo, FALSE, 0x00000000},
	{"Esclusa","LclusÛs©m… i´¨ámbiŒ­r¥i&§Šeext¨i± y€zoµ híiÃblŸ¤€µÏ.",lEsclusa, FALSE, 0x00000000},
	{"Bo¤g…®°ð","La zº…®°g…€µvŸjuÂifiá€exiÂ£Í…‹a µÏÇTi£e”ÆÍ¡sufiÍ›eŽa²t£¤r¯žt%pi¸s—v%žŠeŽtêuªr¥‚u§Ûs©ÌÇHaîv°ižÆq³tšˆ¥p¨a§su ŠeðÇ", lBodega, FALSE, 0x00000000},
	{"Exterior","E¬Í¶o”b±r&§’nÐvŸy®×Â½e„ hi¶oÇLaÈ±m›a®¼tið€sup¨fiÍe—€zoµ Ácur… EuÅÆÇLa µvŸfØÃ²­ocžc›%åÄo„€sup¨fiÍeƒgeªÓÇA¬o¥tŸsŸdiÂÒguŸuµ¿olŸ’åÃ¬ˆédr%a¾¨€ŠÀ…¬½Ìc$n.",lExterior, FALSE, 0x00000000},
    {"E´«Ó²¬½Ìc$n","Uµ¿olŸ’åÃ¬ß—cuŠa—cªvÀa—€sup¨fiÍŸheªd… EuÅÆÇ",lAlmacen, FALSE, 0x00000000},
    {"Zoµ A1","L¼‹a´¨%™»pÖÃ„ƒt£ed±šbªncžc»a§uµ²tm&sf¨aÙpr¥ivaÇU§p¼ill¡ìgr¡a¬o¥tŸÓ²cc¥¡aÙt«¾½…¬½Ìc$n.",lZonaA1, FALSE, 0x00000000},
    {"Zoµ A2","E¬½Ìc$§t¨Úµ‚uµ¾a•íoÏdÀa­i´À… bªn¸ÇAÎ% hay²u§m#sƒt£ed±šp¨fàÃm›Ÿ±d£a¹s‚¥Ã´¨%¼.",lZonaA2, FALSE, 0x00000000},
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
	{"ZHL^ E´»ðmžsu­aq³©‚24hÇ^ (c) 2016æ2019 KMBRÇR¶e¼Ÿ4.",1},
	{"N¡Ï¡µÓ‚p°têuªr.",2},
	{"ZHL bîKMBR",3},
	{"D¥Í£d£²¬Ýd¡cŠ½.",4},
	{"AsÍ£d£²¬ó›Ÿ’mÉ¹.",5},
	{"E¬m&duØŽa˜mÉd°€µÏ.",6},
	{"La v%a¯#c©a‚nu¥Ä¡c¼o.",7},
	{"Laƒsol…¿É¹„€µÏÇEsë¤l¡b¼Ã´Ÿn³vo,±d£À± ’í±d¡ß—c°g…€µÏðÍ&§yÈodžlÁ˜mÉdžsŸ»½iza§p± vozÇEn‹Ÿëm›o€Æ´½l…€¸nsoª‹#‚ìgÅ.",8},
	{"-FËÍoµmÁ‚ëdŒ bajoƒsuëÇLaƒsol…bŸp¨mÉà¨²ÆgÀa -r¥pº¤±d£À±.",9},
	{"PÅvi£Ÿ¤€¸nsol…¿É¹sÇLaƒsoª‹#‚ëdŒ bajoƒsuëÇ",10},
	{"NÐvŸîhi¶¡a 150 C¶Ûu¢baj¡c¨o.",11},
	{"E¬Ûs©ÌÈ$rÚc¡ap£™p³’evit°€f±ÌÍ&§’c×Â½¥—ext¨i± ¤lŽí×s¼.",12},
	{"SŸf±mÉ‚lžg«di›št$rÚ¸„lŽí×Ñ„€µÏ.",13},
	{"La µvŸ’»p°t¡¹n’»c±r¥€ðªxiaÇ",14},
	{"-Co´Åª€©mp¨atu«—i´¨i± y‚lžÒÂrum›ÁŽvit°¾u ¤t¨i±¡-Òf±Ì±d£À±.",15},
	{"E¢Ë¡‡ždžt«je„¾up¨viv£ÍaÊà¥°âŽa »½iz° EVAÇE¬t«je”˜mpÖÃm›ŸauÕm#tê¡yÈi£Ÿuµ²utºom%…Ùch¡ho«sÇ",16},
	{"Paq³tša Šeg°—€Ti¨«.",17},
	{"EÂ#²ÆgÀa.",18},
	{"-N¡sob»vivir$‚EuÅÆ¾Òt«jŸpÅ©ct±.",19},
	{"-Debid¡a€¸´aÚµÍ&§¤jat«jŸÉ©„­¼°²¬Ýd¡cŠa¬-tŸ»cu¨Ó±d£À±.",20},
	{"LcluÑ¾irÏŽa iguaªr€pr¥i&§Šeext¨i± yi´¨i± ¤€µÏÇSeƒÄoªƒb&Õ§ÅjoŽa®¨«·ybot&§v¨¤Ža²b×rÇ",21},
	{"EÂ#®¨«Ó.",22},
	{"EÂ#²bi¨Ã.",23},
	{"-LcluÑ¾Ÿí»ƒ¯ÁƒÄolšmÉu½e„€¥cluÑ -Òf±Ì±d£À±.",24}, 
	{"-LcluÑ¾ŸÍ¨«ƒ¯ÁƒÄolšmÉu½e„€¥cluÑ -Òf±Ì±d£À±Ç",25},
	{"Puls°Ža²b×r€¥cluÑÇADVERTENCIA: USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"Puls°Ža®¨«r€¥cluÑ.",27},
	{"-LcluÑ ya‹#²bi¨Ã.",28},
	{"-Ab×£¹˜mó¨txt¨i± y²èªn¹i´¨i± -diç±d£À±ÇLa˜mó¨txt¨i±¾Ÿí»ƒÛß¡ÚŠ™sŸiguaªn“¢pr¥iº¥.",29},
	{"-C¨«n¹˜mó¨txt¨i±- »pi©±d£À±",30},
	{"Uµ Ïz€¸mó¨txt¨i±¾Ÿha®¨«¹æËžch±Å„²irŸa­r¥i&§surg£¦†sŽe¤sŽaœimÒ°¯ÁƒÃÚµ´šŸiguaª·’n³vo€pr¥iä.",30},
	{"U§Æn–sŸírŸy­¨Ú©Üc¥¡a¬i´¨i± ¤€µÏ.",31},
	{"-LcluÑ ya‹#®¨«Ó -»p±Ã¸mótÀ± ’í±¹.",32},
	{"Ap£™ËžÚl%åÄo„­l#Âê¡y¿eÃ¬tŸß‘n¦–ext¨i±.",33},
	{"-Fr%¡a¬ÃcÕ.",34},
	{"ToÃ¬Ácu×dÀ¾½v¡p±b×lØ”Îiv¡‡žÄozo„ hi¶¡ˆ¥t#§áy£¹.",35},
	{"La µvŸëduªr‹#ã° ’ZHLÇPi´À…²m°ill¡yƒØgŒ€¸mÆ+%a‚g«ãšÖÄ™Åj¼.",36},
	{"ZHL 24h",37},
	{"Cº¦ifêultÀ¦iÂÒgu¥p¨fi¬¤edifiÍŒ¿eÃ¬»c±Ã¹ƒt«Í¶oÇ",38},
	{"Enªt¨a¬¤€ŠÀa©cªd¡num$×c¡iluÚµ¯eÏm›e€Ácu×dÀ.",39},
	{"P±Ôµ²b¨tu«¾Ÿ¤slizaá+&§l#s¨ ˆtŸaó´a: TECLEE EL C&DIGO DE ACCESOÇTIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"U§á+&§’¼pàt¡p¶igrÁ¡ÛguŸtu¢ëviÚ›Á.",41},
	{"Tod¡so§áj™bªná„ ÃÌ+¡ÛÚªrÇL™m#¢g«ãšß—cuŠÉ‚lÁ‹a´šm#¢bajÁ.",42},
	{"AØja§¤c£a„­eq³+Áƒt£ed±šbªn¸s.",43},
	{"Tod¡fËÍoµlÇEl”ÆÍ¡sufiÍ›eŽa¿a´£¨“sƒdiÍºšnà¥°i¼Ža­r¥¨v°¿at¨i½šbâl&gi¸s.",44},
	{"Uµ b&ÏÓÊ¡muy²lÃ f±Ì©chŒ‹a¾aª.",45},
	{"U§Æq³tŸazulƒg«§ÒdêÀ± ’p¶igr¡bâl&gi¸—fÅ´½Ç",46},
	{"-Es©”Æq³tŸ-susur«±d£À±‚tuÙ%¹.",47},
	{"-N¡p³¹,“¢di»ctiva„€ñpr¥a¿Ÿl¡impid£Ç",48},
	{"P¶igr¡bâl&gi¸ÇCºs¨v°²¿£o„ 100®¶Ûu¢baj¡c¨oÇN¡mÉióª·Û§pÅ©cÍäÇN¡í×rÇN¡golpe°ÇMat¨ia¬fr#gil.",49},
	// Textos relativos al ordenador
	{"-Co±dÒ¡ÕdžlžÛs©Ì„€µÏÇPhíªrƒÚgo mpÖa: ±d£À±­aªb«®ªÏÇAlgË™sug¨£Ía„­aªbr™cªvŸsº: ±d£À±²yuÓæ±d£À±Êomb»æ±d£À±¿iÛä..Ç-tŸr¥pº’s¨viÍ½±d£À± ’µÏðÍä.",50},
	{"-Ohævaya˜m¡n¡p£s$‚Ö¨”¡-diç¸mótÀ±ƒ f½Ñ²dÚ«Íä.",51},
	{" ",52},
	{"N¡Ýt¡µÓ‚p°têuªr.",53},
	{"NÀa ˆ¤ÂÜ°.",54},
	{"No””peÍ½m›Ÿi´¨¥É©.",55},
	{"N¡suç’µÓ Ò¥p¨a¹.",56},
	{"E¬aullidŒ¬vi›¡sŸÒfilt«­±fußªje.",57},
	{"-Bu£È«baj¡-apr³ba€voz¾atèfàh…¬±d£À±Ç ",58},
	{"-Ah±¿om›Œ­º¨Þumb¡a M°©ÇBaja²€bo¤g…®°ð¿iŠ™»ÒiÍ¡lžÛs©Ì„€µvŸ-diç±d£À±­»mu«Ç",59},
	{"D¥Í£d¡lÁ”c½ºša€bo¤ð î¤pÁiÕÆq³tŸju´¡a¯o„m#¢p£di›e„ ŠeðÇA¬»gr¥° ¤scubÅ‰€Ñ•sŸha®¨«¹.",60},
	{"-No” µÓ­¨soµ¬p¨o”¿om›Œ »Ícª·-diç€voz¦–±d£À±-¿iŠ¼g™ÒËÓ€bo¤ð y®a¥‚u§pÅfËd¡s³+o.",61}, 
	{"L¡m#¢duÅ”È£¨ ˆ»Ícª·su¢pÐz¼Ža€Ûgui›ŸÚÛäÇLÖð§a®»¨sŸhumÉÁÇE§fÒ..Ç-suspi«±d£À±¿iŠ™»¸gŸlžr¥Õ„Èu®u¨éƒÔµ Åbof»goµ.",62},
	{"-CŠ½,²Î% Tod Cºn± -diç€voz- VolÏmža M°©ƒÆq³©ÇRepit¡volÏmÁƒÆq³©Ç",63},
	{"Hay¦žbotº¥: Åj¡îv¨¤ÇSŸutilizÉŽa®¨«·y²b×r€¥cluÑ²l xt¨i±Ç",172},
	{"LžÛgui›šÆq³t¥Ža Šeg°.",173},
	{"No”¿om›Œ jug°²¬SokobÉ.",174},
	{"-Vooª»..ÇoohÙooh -tŸ¤v³lvŸcr³làŒ€µÏ.",175},
	{"-Ca´°e,ÙohÙooh -i´›¼—tº° ^ -N–blu¦ipi´¡di blu...",176},
	{"S&Ø”cucho‹#tiáÇLaÈ±m›a i´¨fi¨e‚ªs˜mËiáÍº¥.",177},
	{"EÂoy—€coculÃ,Ê¡Ï¡J'pit¨.",178},
	{"Sat$litŸheªd¡ŸÒh&spiÕ.",179}, 
	{"La ŠÀa²¬½Ìc$nÇ",180},
	{"FËÍoµƒ˜mÉ¹„ voz²¬±d£À±: ±d£À±®ªÏ.",181}, 
	{"EsbØˆåt#lê¡»cÃnguª·ˆsŸi´¨µ baj¡ti¨«.",182}, 
	{"(£©cª¹)",183},
	{"La­u¨t…¬½Ìc$§ya‹#²bi¨Ã.",184},
	{"E¬©cªd¡sŸiluÚµ‚ÅjoÇCODIGO INCORRECTO.",185}, 
	{"E¬©cªd¡sŸiluÚµ‚v¨¤ÇCODIGO CORRECTOÇE¬á+&§l#s¨¾Ÿ»plÐð‚su˜mp°tim›o.",186}, 
	{"E¬á+&§l#s¨˜Ú£za²®½›°ß.",187},
	{"E¬á+&§l#s¨¾Ÿp»pa¦è‘rÇ",188},
	{"E¬á+&§l#s¨¦è‘Ç",189},
	{"P¨¡µÓ¾uç¤ÇUµ volut… hum¡y²lgË™chèp™surg£¦–á+ä.",190},
	{"Sºƒt£ed±e„È«nsp±©.",191}, 
	{"(¸gi£d¡a´¥t«je)",192},
	{"-E´ºcš©‰d°%™a¾oªs‚¥tŸlug° Òh&spit¡-tŸ»cu¨Ó±d£À±.",193},
	{"-S&l¡nà¥iÕÆq³tŸazulÇ",194},
	{"La¾up¨fiÍe”¯iÑ,¾&l¡sŸÜtivaƒ©cª¹.", 195},
	{"E U R O P A",196},
};

token_t mensajesSistema_t [] =
{
	{"N¡p³d¡v¨ µÓ,‹#¿uîÁcuÅ.^",0},
	{"Tambi$§haî",1},
	{"Esc×bŸtu¢&ï£šaÎ%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&ë? P± fav±­r³baƒÙÄ™Æªb«s.^",6},
	{"N¡p³d¡ir‚¥a¦i»cÍä.^",7},
	{"¿Perdón?^",8},
	{"LÖv¡",9},
	{"(puesto)",10},
	{"nÒg'§objeÕ.",11},
	{"/SeguÅ? ",12},
	{"/J³ð„Ê³vo? ",13},
	{"Adiós...",14},
	{"OK^",15},
	{"[...]",16},
	{"H™»½izÀ¡",17},
	{"ÈurÝ",18},
	{"s",19},
	{".^ ",20},
	{"La­u´uaÍä „ ",21},
	{"­u´o",22},
	{"N¡lÖv¡ó¥Õ”o.^",23},
	{"N¡p³¹æya¯Övo”¡ó¥Õ.^",24},
	{"YaÈ£g¡",25},
	{"N¡Ïo”¡p±²Î%.^",26},
	{"N¡p³d¡lÖv°¿#s˜s¼.^",27},
	{"N¡t£go”o.^",28},
	{"P¨¡Û ya¯Öv¡ó¥Õ",29},
	{"S",30},
	{"N",31},
	{"Más...",32},
	{"> ",33},
	{"",34},
	{"E¬tÐmp¡p¼a...^",35},
	{"He˜gid¡",36},
	{"MŸpºg¡",37},
	{"MŸÎit¡",38},
	{"Dej¡",39},
	{"N¡p³d¡pº¨mŸ",40},
	{"N¡p³d¡Îit°mŸ",41},
	{"<T£gŒm¼iÀ¼˜s¼‚l™mÉÁ!",42},
	{"D¥g«ÍÀam›Ÿp¥…m¼ia¹",43},
	{"Met¡",44},
	{"Aho«Êo‹#‚",45},
	{",",46},
	{" î",47},
	{".",48},
	{"N¡t£g¡",49},
	{"N¡lÖv¡ó¥t¡",50},
	{"",51},
	{"Es¡Ý‹#‚",52},
	{"nÒg'§objeÕ",53},
	{"Fêh¨¡Ý—¸´«¹.^",54},
	{"Fêh¨o˜rrupÕ.^",55},
	{"Err± ’E/SÇFêh¨¡n¡g«ba¹.^",56},
	{"Di»ct±i¡ll£o.^",57},
	{"Dèc¡ll£o.",58},
	{"NombrŸ’fêh¨¡n¡v#li¹.^",59},
	{"NombrŸd–fêh¨o: ",60},
	{"",61},
	{"/P¨dä? P± fav±­r³baƒÙÄ™Æªb«s.^",62},
	{"AÎ% ",SYSMESS_NPCLISTSTART},
	{"¥t# ",SYSMESS_NPCLISTCONTINUE},
	{"están",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"DŠ¡haî",SYSMESS_INSIDE_YOUCANSEE},
    {"EnÍÌ haî",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"No”²lg¡ˆp³Ó Îit°å.^",69},
	{"Pºg¡",SYSMESS_YOUPUTOBJECTON },
    {"No”²lg¡ˆp³Ó˜g¨ß.^",SYSMESS_YOUCANNOTTAKE},
	{"NoŽàŸˆp³Ó¿ov¨ß.^", SYSMESS_CANNOTMOVE},
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
    {oCaja, lZonaA2,"Æq³tŸazul",     nPaquete, aAzul,   1,0x0000 | aMale | aDeterminado},  
    {oTraje, lEsclusa,"t«jŸpr¥u×za¹",     nTraje, EMPTY_WORD,   1,0x0000 | aWear| aMale | aDeterminado},  
	{oEsclusa, lEsclusa,"¸mó¨t…€¥cluÑ", nEsclusa, EMPTY_WORD,   1,0x0000 | aStatic | aFemale | aDeterminado},  
	{oPuerta, lEntrada,"ó¨t…¿et½",     nPuerta, EMPTY_WORD,   1,0x0000 | aStatic | aFemale},  
	{obotonrojo, lEsclusa,"bot&§Åjo",     nBoton, aRojo,   1,0x0000 | aStatic | aConcealed | aMale},  
	{obotonverde, lEsclusa,"bot&§v¨¤",     nBoton, aVerde,   1,0x0000 | aStatic | aConcealed | aMale},  
	{oCanon, NONCREATED,"á+&§’vigiªnÍa",     nCanon, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
	{oTeclado, NONCREATED,"teclado",     nTeclado, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x0000}
}; // Tabla de objetos de la aventura

// Una tabla para hablar con el ordenador, se puede usar la misma técnica para definir listas de atrezzo y ahorrarse cientos de 'examinar objeto'.

// Tabla de conversación con el ordenador 
tema_t ordenador_t[]= 
{
	{"Hola","-Hoª,¾oy±d£À± ’µÏðÍ&§-r¥pº’uµ voz¿et#liá."},
	{"Adios","-H¼Ã­Å´o."},
	{"trabajo","-SoyÛs©m… µÏðÍ&§¤€µÏÇ"},
	{"yo/piloto/conductor/transportista","-EršTod Cºn±,piØtŒ€µÏÇ"},
	{"tormenta/parabrisas", "-LaÈ±m›¿o¤«ÓÇNŒb¨%a¾¨pÅbÖÌŽa²cç¤r²¬½Ìc$§usÉ¹t«jŸ’pÅ©cÍä."},
	{"Europa/luna",	"-EÂamÁ—Ñt$litŸJoviÉoÇ-r¥pº¤±d£À±."},
	{"Joviano/Jupiter",	"-EuÅpÑt$litŸ’Jupit¨ÇEn€ciluÚµÓ­± J'pit¨¥pàt#cuØ”¾ob¨bâÇP± ¤sg«ÍaÊu¥Äo—c°go”—€coculÃÇ"},
	{"cara/lado", "-EuÅÆÈi£Ÿuµ®sÐmprŸ±i›Àa haÍa J'pit¨."},
	{"donde", "-EÂ#‚u§½Ìc$n,—ext¨i±ÇT£dr#¢ˆs½irƒ‹aÈ±m›aÇ"},
	{"Mision","-T£ñžˆ»¸g¨Æq³©‚EuÅÆ îŠeg°Ø‚M°tŸÉ©„ 24h -r¥pº¤."},
	{"nombre",	"-MiÊomb»” TODÇSi¯¡p»fi¨¥,­³dšus°‹ŸÝmbrŸa¬híªrƒÚgoÇ "},
	{"modelo/ordenador", "-Soyë¤l¡Cyb¨dÒŸ1997Ç Mi­Åg«mÀ± ±igiµ¬f³DrÇGuill¨m¡Ha§¤€Með C±é«tiºÇMe—ß+&²®a´°Ôµ®ÉÍäæ/Îi¨šo%rª?"},
	{"mega/megacorp/corporacion/ciberdine/cyberdine","-Lmpr¥aÞ¥pºÑblŸ’ˆt' îyo‹ñÁƒv¨sÉ¹‚EuÅÆ."},
	{"aventuras/conversacionales","-Me—á´É“¢av›u«sƒv¨ÑÍoµl¥."},
	{"if/fi/ficcion/interactiva","-D¥¸Ýz¸”Ÿt$rmÒoæ/tŸ»fi¨ša“sƒv¨ÑÍoµl¥?"},
	{"graficas","-No‹#§m½,­¨¡n¡c»¡ˆp³d™jug°²Ôµ¿iŠ¼ƒduc¥."},
	{"transilvania","-No‹#¿½,­¨o”é¸˜rÃŽa¿i guÂoÇP»fi¨¡'•ÝchŸm#s“rð'æˆdu« Ë™12h ’j³gŒÈÐmp¡»½."},
	{"isla",	"-P¨¡bu£oæ<Û”aÊËá€t¨mÒ°º!ÇRàu¨d¡ˆË¡‡žaut±¥,Ã¬UTO¯Ÿhiz¡uµ viÛÃ²¬pÅg«mÀ± ˆt¨mÒ& Ã§Ì¬ˆ¤Âruy¨o§Õ¹bØˆ’ofiÍµsÇP¨o”Ùt« hiÂ±ia."},
	{"uto",	"-Re½m›Ÿn¡t£g¡m#¢Ótžsob»‹a­¨soµÇSÒ¦ud«Ôµ¿›ŸÌ¥t«Žáp°²¿i¢»giÂrÁ."},
	{"kmbr","-U§ÚÂ¨â,¾Ÿrum±ea ˆ¨a°£ˆÅj¡muÃn©Ç"},
	{"kno",	"-U§c¶eb«d¡aut± ’c&Úc ˆvivi&¿#„¦ÁÍ›ža+ÁÇT£%ac½Ø—¤d¡Ã§¤s¸muµ¬ˆfiµlm›Ÿmu×&²pªÂÀ¡p± $lÇEscl#Û¸æ¤b¨%™Ö¨ÈoÓ¾uÙb« v°i™Ïc¥."},
	{"dela/dla","-Un”c×b…¬Ûgl¡XVæg«Í™a $¬t£ñždèpºiblšÌ«vilªs˜m¡'CuÉ¹˜m%‰s¡ìgÅ'‚f«nc$s."},
	{"frances/ingles/italiano/aleman",	"-L£gu™mu¨t¼æhoy‚d%aÈo¹Ëiv¨s¡hí•©cÝlªÝ."},
	{"tecnollano/castellano/espanol/mexicano", "-La¯£gua f«nc…Êu¥Äžd%¼."},
	{"comic", "-AòŸßcu£Ía¬muy­oóªr² fiµÖ„¬Ûgl¡XXÇ"},
	{"daniel/danixi", "-E¬r¥pºÑblŸ¤€åð˜ré«tiº."},
	{"obra", "-HíÖë„œl¡cuÉd¡t¨mÒštu¿iÛä."},
	{"av›u« fav±iÃ", "-E¢dif%Ílœegir,¾Ÿvolvi¨o§»½m›Ÿéóªrša «%z ¤€pÅlif¨aÍ&§’Ûs©Ì„ µÏðÍä‚auÕm&vil¥æb°cžîµv¥”ÆÍ½¥Ç"},
	{"jug°²v›u«", "-TŸbusc°$Ôµ »½m›Ÿi´¨¥a´Ÿuµ ÏzÈ¨mÒ¥€ÚÛä."},
	{"cancion/oir/canta/tararea", "-Daèy..Ç-CoÚ£za²—tº°¾i§¤m¼iÀa f±tuµ."},
	{"guillermo", "-E¬Òg£i¨¡r¥pºÑblŸ¤€i´¨faz humÉ…¯žÛs©Ì„ µÏðÍ&§¤€Með˜ré«tiº"},
	{"interfa",	"-L¡ˆus¼Ža híªrƒÚgo."},
	{"viajar", "-P×m¨¡haîˆ»¸g¨Æq³©,¯³g¡pºdr$Þumb¡a M°©Ç-tŸ»cu¨Ó±d£À±."},
	{"entrada", "-La ŠÀa‹# haîfu¨aÇE¢pÁiblŸˆnà¥itš½g'§c&digŒ²cc¥oŽa Š°."},
	{"codigo", "-N¡t£g¡nÒg'n¦aÕ—€±d£ ¤€cŠa¬Ü¨c…¬c&digo."},
	{"central", "-La®Ša¬’ZEUR‹#—€Ti¨«."},
	{"ZEUR", "-Es€ñpr¥… »p°tŒ­aq³t¥‚24h ˆnžÆðs³ld¡y“¢pÐz¼Ža¾egui·»c±×£¹Univ¨so."},
	{"Tierra", "-S½vo‚l™zº™pÅ©gid™sŸhaƒv¨ti¹‚ËƒgØm¨ÀŒ¿eð-urb¥ÇU§Ûti¡p¶igrÁo,­¨¡ll£ŒÙp±tËiÓ¤s." },
	{"almacen", "-Hñžat¨×zÀ¡c¨c…€ŠÀaÇDebšs½ir²l xt¨i±æŠ°—½Ìc$§îvolv¨ƒÆq³©Ža ˆp³d™t¨mÒ°€ÚÛäÇ"},
	{"temperatura", "-E§t±n¡a 150ºC baj¡c¨o—ext¨i±ÇTŸ»¸Ú£d¡ˆlÖv¥t«jŸ’sup¨vivi£Ía."},
	{"consola", "-Laƒsol…¿Éd¡mu¥t«¥tÀŒ€µvŸy¯ÁƒÄolšmÉu½¥ÇActu½m›e‹# ¤ÑctivÀaŽa²h±«r—¨g%aÇ"},
	{"Ütiv°ƒsoª", "-E¢åj±”p¨°²˜mpÖt°€ÚÛäÇEÂamÁ‚ëdŒ bajoƒsuë."},
	{"¤Ñctiv°ƒsoª", "-Ya‹# ¤ÑctivÀaÇ"},
	{"memoria", "-E¢n±Ì¬ˆn¡»cu¨dšmuch¡½˜Ú£zŒÔµ¿iÛäÇP¨¡n¡tŸp»ocupe„”¡aho«æ¤só$„ Ë™j±µÓ„ »ªxÈod¡volv¨#²€n±m½idÀ."},
	{ "relax/jornadas/vacaciones","-D¥ó$„‹Ÿt«baj¡édr#¢p¼° Ëžd%a„ »ªx‚M°©."},
	{"marte","-Ya¾í¥,pªìÃ ÅjoÇBu£o,²µ«njÀŒs’ˆdâ˜Ú£zo€t¨«f±ÌÍä."},
	{"venus/saturno/pluton/lunas/urano/neptuno/mercurio","-E¢åj± ˆn¡s½irsŸd–©m…€ÚÛäÇ-r¥pº¤"},
	{"terraformacion","-HÜŸËža+Á˜m£z°º€ext«cÍ&§’mÒ¨½¥,²b×¨o§v°i™mÒ™y˜m£z°o§lžt«bajo„È¨«f±ÌÍä."},
	{"minas","-D¥ó$„€»¸gid…bñžŠeg°Æq³©‚E¬T£ed±ÇUn…“¢Ìy±šÚµ„ Hi¨r¡îN%Î–d–Sè©Ì Soªr."},
	{"Tenedor","-Tambi$§sŸÖƒoç˜ëT£ed±¦–diíØÇE¢uµ¿iµ gob¨µÓ­±sÒdiát¡ËifêÀŒ¿Ò¨%… M°©Ç"},
	{"Hierro/Niquel","-EsåÃ¬íËÓ´Ÿp¨¡muy­»Ía¹ÇL¡dif%Íl”¾uÈ«nsp±©,­u¥”¿uy¦£s¡y®u¥Ã b¼Ã´ŸdÒ¨o xt«¨lŒ€atm&sf¨a—€Ti¨«Ç"},
	{"sindicato","-Gobi¨µnƒ¿É¡du«¯žp»Ío„ v›a y¯žÜu¨¹„¾umÒiÂrÁÇ"},
	{"humanidad","-SŸhxt£did¡p±€ðªxiaÇP¨¡lŸt£$i¢b¼Ã´Ÿapeg¡a¬Ûs©Ì SoªræˆsŸÌ´i£e˜ëcŠŒÈod¼“¢op¨aÍº¥."},
	{"operaciones","-Ya¾íšsumÒiÂrÁ,­aq³t¨%a,ÙÍo..."},
	{"ocio", "-AÎ% µd…ÙÍoæhaîˆt¨mÒ°t«bajo."},
	{"paqueteria", "-Nu¥Ä¡t«bajo‚ZEUR” Šeg°¯žÆq³t¥‚24h"},
	{"suministros", "-SŸha§íi¨t¡v°i™Úµs‚M°©ƒobjetivŒ²ba«t°p»ÍŒ­º¨²lgË™Ìt¨i™p×m¼—¥ÆÍo."},
	{"paquete", "-Seg'n€¤sc×pÍä¦–m£ÑjŸsŸt«t…Æq³tŸ’27cm x 29cm x 30cm ˆp¥a 10KgÇ"},
	{"recoger/recogida", "-Hñžat¨×za¹—€ŠÀ…¬½Ìc$nÇSugi¨¡ˆs½g™ah% fu¨a,¯ªmša€ó¨Ã î»¸j¼Æq³©."},
	{"nave", "-VoªmÁ‚uµ µvŸ’»p°tŒÈip¡T¥ªÇEs˜mpÖÃm›eœ$cÄiá,²s% ˆÚŠ™t£ðmžuµ‹r¶•c¨á­od»mž»c°g°“¢bat¨%¼."},
	{"estrellas", "-La¿#¢c¨cÉ Sol."},
	{"Sol", "-Es€¥Ä¶•prÒÍÆ¬¤‹ŸÛs©ÌÇ"},
	{"Sè©Ì Soªr", "-EsÛs©Ì²¬ˆp¨t£àe€Ti¨«Ç"},
	{"sistemas", "-TodžlžÛs©m¼‚±d£ÇOp¨amÁ‚ëdŒ bajoƒsuë."},
	{"ayuda", "-P°o‹oy²Î%,Ža²yud°©ÇAlgË™Æªbr™cªvŸˆp³dšus°¾º:¿iÛäæJ'pit¨,Êomb»,¿o¤Ø,¿£Ñje..."},
	{"mensaje/comanda/encargo/entrega"	"TeÌ: Env%¡urg›Ÿa¬T£ed± ’M°©ÇCo´£i¹: Re¸giÓ‚½Ìc$n‚¸±d£À¼‚EuÅÆÇUs°®ªÏ: 32768ÇImp±Ãn©: Ma´£¨² ©mp¨atu« baj¡c¨oÇ"},
	{"clave", "-Quiz# haya²lgo—m£ÑjŸd–£c°go."},
	{"radiacion", "-No”pÅbÖÌƒt«jŸ’sup¨viv£ÍaÇSÒœ€«diaÍä” ÃnœevÀa ˆn¡vivir%™m#„d%aÇ"},
	{"airlock/esclusa/boton/botones", "-LcluÑ¾Ÿop¨a¿Éu½m›eÇE¬bot&§v¨’Í¨«€¥cluÑ yÅjo€í»Ç Aßg'«tŸ‡Öv°t«jŸ’sup¨viv£Ía­u¥ÕÇ"},
	{"comunicaciones", "-Debid¡a€fu¨tŸ«diaÍ&§nu¥t«s˜mËiáÍºšs&l¡fËÍoµn—€µÏÇNo‹°$ƒtig¡ah% fu¨aÇ"},
	{"eva", "-Sº“¢Ûgª„²ctividÀ xt«-ÏhêuªrÇE¢cuÉd¡s½¥‚ÚÛ&§fu¨…€µÏÇ"},
	{"traje/superviviencia/proteccion"	"-Lo—¸´«r#s—€¥cluÑ¯iÂoŽa¾uÔsoÇRàu¨ÓÊ¡s½i·¤€µvŸÛ§lÖv°l¡ó¥Õ."},
	{"mierda/tacos/culo/joder/hija/puta/puton/hijo/comemierda", "-EÑ²çpÍ&§n¡f±ÌŽtŸ’Ú b¼Ÿ’ÓtÁÇ-r¥pº¤±d£À±ƒœegÉÍaÇ"},
	{"siglas", "-Ya¾í¥,Ža²c±t°­aªb«„m¼ia¹“rg¼Ç"},
	{"calla", "-Si§pÅbÖm¼æyaÊ¡Ã«»¡m¼Ç-r¥pº¤éc¡¹li¹."},
	{"bodega", "-Dº’½Ìc£amžlžÆq³t¥Ža¾u¦iÂ×buÍä."},
	{"temperatura/frigo/congelador/frigorifico/enfriar", "-T£ñÁf×g±%fêŒdêÀ¡a‹ŸtipŒ­aq³t¥Ç-r¥pº’¤só$„b»vŸÛl£Ío"},
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
		if (fnombre2==nEsclusa)
		{
			ACCmessage (132); DONE;
		}
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
			if (fnombre1==nEscaleras) 
			{
				ACCmessage(5);
				DONE;
			}
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
			writeText ("E¬©cªd¡n¡r¥pº¤ÇLa­u¨Ã ya‹#²bi¨Ã.^");
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
    if (flags[fverb]==vExaminar)
    {
        if (findMatchingObject(get_loc_pos(loc_here()))!=EMPTY_OBJECT)
            writeText ("Deb¨%¼˜g¨”¡a´¥.^");
        else
			writeText ("N¡v¥”¡p±²Î%.^");
		DONE;
    }

    if(flags[fverb]==nInventario)
    {
        ACCinven();
        ACCnewline();
        DONE;
    }

    if (flags[fverb]==vCoger)  { ACCautog(); DONE; }

    if (flags[fverb]==vDejar) { ACCautod(); DONE; }

    if (flags[fverb]==vMeter) { DONE; }

    if (flags[fverb]==vSacar) { DONE; }

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
    if (flags[fverb]==vMirar)
    {
        ACCgoto( flags[flocation]);
        DONE;
    }
	if (flags[fverb]==vEmpujar || flags[fverb]==vTirar)
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
 //ACCpicture(flags[flocation]);
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
    defineTextWindow (0,0,32,23); // Pantalla reducida en 128Kb, Gráficos + Texto
    ACCgoto(lPuente); // Localidad inicial, en el puente de mando
    flags[LOCATION_MAX] = 8; // Número más alto de localidad
    ACCability(10,20); // 10 objetos, 20 piedras

	ParserLoop (); // Pone en marcha el bucle principal
}

// Funciones propias del juego

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



