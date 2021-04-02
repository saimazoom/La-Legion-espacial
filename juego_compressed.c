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
// #define SPANISH
#define ENGLISH

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
// CÛdigo local
// Si necesitamos cÛdigo en p·ginas de memoria hay que compilarlas como .bin y aÒadirlas aquÌ como extern
// Se llaman desde el cÛdigo usando: setRAMpage (n) y llamando a la funciÛn, al terminar hay que volver siempre a la p·gina 0

char respuestas();
char respuestas_post();
char proceso1();
char proceso1_post();
char proceso2();
char proceso2_post();

// Variables que necesitamos del parser...
// Se pueden declarar m·s tablas de flags para el juego pero el parser
// sÛlo trabaja con esta. 
extern unsigned char flags[255]; // Flags 60...250 Disponibles para el usuario
extern unsigned char playerInput[80];
extern unsigned char playerWord[25];
extern BYTE gWord_number; // Marker for current word, 1st word is 1
extern BYTE gChar_number; // Marker for current char, 1st char is 0

// Tabla de im·genes del juego
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

// ˙ltima localidad como ID 0 

#ifdef SPANISH 
loc_t localidades_t [] =
{
	{"PuóeÅm∑»","Loü¥ƒrumó›Å≈ÃgÓi&£ilum¥∑ÖpuóeÅm∑»«EnÖext•i≥Âu≈ùrmóaÅhi¡¢’ßba™∞ob≠Ñsup•fÔieÅEuœ—«",lPuente, FALSE, 0x00000000},
	{"Nod¢cëa∫","Loüm&dul›Ål†≈Ã¶ƒ#náp§umbπ«E∫‹d¢cë√Éec”ÉÖpuóeÅm∑»,Ñ®clus†a∫o®™ yÑbo©g†√∞ur«",lNodo, FALSE, 0x00000000},
	{"Esclusa","Se¶scucÒÉ ¥t§·d“Ñt≥mó†golpe∑»ÉtπÖfu’ºje«Lûs€brûc≠a£f≥mûs¥i®tπsá‡ütπj®Åexpl≥Ói&n«",lEsclusa, FALSE, 0x00000000},
	{"Bo©gaÅc±ga","L†z≤aÅc±g†ti§e¶s—ci¢sufÔióe∂±†◊§d•∂eqÀ+›òv%oüëe∂±tÔul±®«EnÑs€brûÒ÷v±Ûü—qÀtôqÀ¶sp•a£su ëega«", lBodega, FALSE, 0x00000000},
	{"Exterior","Meòvu¡Ã u≈ùrmóaÅnieÃ y´ƒ√®Åhi¡¢qÀ¿e∆mpiñv•òÑdiƒ∑cia«A∫o®™∞e¨iƒ¥gÀ u£ËifÔi¢qÀ∂odr%†s•Ñë“aìlßl⁄c$n.",lExterior, FALSE, 0x00000000},
    {"Eªπd†√ßl⁄c$n","Un†moﬂÅﬁt√∞eòcuëaòcºv“aòÑsup•fÔie ÆºdaÅEuœ—«",lAlmacen, FALSE, 0x00000000},
    {"Z≤†A1","Lûm≤&t≤û®t∑t•%û≠pﬂt…Åc≤t§Ë≥ôbl∑∏üc≠a£Ï†◊m&sf•†imp•s≤√«A∫o®™ u£›cur¢p…ill¢d†Óc®¢†Ï†s√†œja.",lZonaA1, FALSE, 0x00000000},
    {"Z≤†A2","El∂…il‡°•m¥aáÏ†s√†aboÃd“†ilum¥“aáœjo«Lûm≤&t≤û®t∑t•%ûpœ·gÀ£su´ursoÉ¿#sÉt§Ë≥ôbl∑∏üp•fec”móe ≥d§a»s.",lZonaA2, FALSE, 0x00000000},
    {"","",0, FALSE, 0x00000000}
};
#endif 

#ifdef ENGLISH
loc_t localidades_t [] =
{
	{"Bridge", "ãbdgeàdimly∆llum¥a™–b÷Ä≈vig◊Û£p∑¡«OÎ·©,ß£i‰∞t≥màπgâov• Äsurfa‰éEuœpe«",lPuente, FALSE, 0x00000000},
	{"Cëa∫‹ñ", "ãship'ümodulôa≠ ¥°wilight«ãcëa∫‹©ÉnectsÇÄ∏mm∑–bdgeÂÄair‡ckÇÄw®tßŒ Äc±goÇÄs‘Ø«",lNodo, FALSE, 0x00000000},
	{"Airlock", "ãƒ≥m´a£be Æ±d∂‘Œâ¥t§s¡yßga¥sæÄw√ls«ãpo≥¬ightâtπcôs¥iƒ•∞Òpôi£Äexpl≥◊Û£su‚s«",lEsclusa, FALSE, 0x00000000},
	{"C±g¢hold", "ãc±g¢a≠†h…ò‘gh∞—‰Çh∑dﬂ∞m√l∞hipmós«I£ÄsÒ»wsí•eß≠∞ev•√∂Ókagôawa‚â©liv•y«", lBodega, FALSE, 0x00000000},
	{"Outside", "Ißmògulfe–b÷†ƒ≥més‹wßŒ∆‰´ryƒ√üp≠vóâﬁÌœm∞eeâi£Ädiƒ∑‰«T¢Äw®æI´a£⁄keΩuæ†buildâØ◊ïul–be Äë∑‰ÇÄwa≠h‘’.",lExterior, FALSE, 0x00000000},
    {"Wa≠h‘’ ë∑‰", "A¿…séﬁt√∞‚ün®tﬂdΩ£Äfœze£surfa‰éEuœpe«",lAlmacen, FALSE, 0x00000000},
    {"Z≤e A1", "ãm≤ot≤‘üsÆlvôfilﬂ–wiØÁhi™É”¥•üc≠a™ß£imp•s≤√ßtm›ph•e«T¢Äw®æ†d±kïrd≥¬e“sÇ†≠–œ€.",lZonaA1, FALSE, 0x00000000},
    {"Z≤e A2", "Thärd≥òdüi£†vaul™–œ€¬iæi£≠d«ãm≤ot≤‘üsÆlv®Ét¥Àíeirïur’ÁiØ¿o≠Õe◊lyßrr∑ge–whi™É”¥•s.",lZonaA2, FALSE, 0x00000000},
	{"","",0, FALSE, 0x00000000}
};   
#endif 

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

#ifdef SPANISH 

token_t mensajes_t [] =
{
	{"ZHL^ Eª≠gamoüsu∂aqÀ™á24h«^ (c) 2016Â2019Â2021 KMBR«R¡e…e 5.",1},
	{"N¢Ã¢≈daáp±tÔul±.",2},
	{"ZHL„÷KMBR",3},
	{"D®ci§©£a∫‹d¢cë√.",4},
	{"Asci§©£√∂uóeÅm∑».",5},
	{"E∫m&dul¢p±aÜ∑d±Ñ≈Ã.",6},
	{"L†v%†l#c™aánu®Ÿ¢c…o.",7},
	{"LaÉsoºÅ≈ÃgÓi&nÅl†≈Ã«Eüu£mo©l¢baƒ∑™ÕÀvo,Ö≥d§“≥Åab≥d¢’òc±gaÅl†≈ÃgÓi&£yù»ül›Ü∑»ü’ ≠√iza£p≥ voz«E£®™¿€óoÑp∑t√ºÅºÉsol†®t#ánegœ.",8},
	{"-FÏci≤am›ámo»ÅbajoÉsumo«LaÉsoºìbe∂•m∑ec•ß—g“†-r®p≤©Ö≥d§“≥.",9},
	{"Pœvi§eÅºÉsoºÅm∑»s«LaÉsol†®t#ámo»ÅbajoÉsumo«",10},
	{"NieÃ ÷hi¡¢†150 C¡·uübaj¢c•o.",11},
	{"El∞ ™m†t$rmÔ¢ap§ûpÀñev‚±Ñf≥⁄ci&nÅcƒ√®òÖext•i≥ìl∂±abr ….",12},
	{"SeÌ≥m∑á‡ügπdióôt$rmi∏ål∂±abr …Ål†≈Ã.",13},
	{"L†≈ÃÅ≠p±öd≤ñÒgoÑru”«Eüu£mo©l¢¥duƒ√Éƒrui»É¿&du‡ü®t#Œ±«Ha‰∞u°πbaj¢yÕ¢’ßv•%aìm…i“ûÃc®.",14},
	{"-C≤tœºÑ™mp•◊uπòÖ¥t•i≥ yá‡ü¥ƒrumóoüp±†ev‚±∞uìt•i≥¢-¥f≥⁄Ö≥d§“≥.",15},
	{"Eüu‹Å‡ü»ütπj®Åsup•viv§ci†nec®±i¢p±†≠√iz± EVA«El°πje¶sÜpﬂ”móeßuøm#tÔ¢y°i§e Ï†aÎ≤€%aÅoch¢h≥…«",16},
	{"PaqÀtô†ëeg±∂≥Ös ™m†sol±.",17},
	{"Eƒ#ß—g“a.",18},
	{"N¢sob≠vivir$áEuœp†s¥Ötπje∂œ™ct≥.",19},
	{"-P±†ev‚±É”m¥Ói&nìjaÖtπjeßª®Åp…±ß∫‹d¢cëa∫-™ ≠cu•daÖ≥d§“≥.",20},
	{"L†®clus†·rÃ∂±†igu√±Ñpr®i&£ëeÖext•i≥ yÖ¥t•i≥Ål†≈Ã«SeÉtœºÉÖb&ø£œj¢p±†c•r± yÖbot&£v•ñp±†abr«",21},
	{"Eƒ#´•πda.",22},
	{"Eƒ#ßbi•”.",23},
	{"-L†®clus†’ßb≠É¬›Étœlôm∑u√ô-¥f≥⁄Ö≥d§“≥.",24}, 
	{"-L†®clus†’´i•πÉ¬›Étœlôm∑u√ô-¥f≥⁄Ö≥d§“≥«",25},
	{"Puls±∂±†abrÑ®cluÚ«^ADVERTENCIA: ANTES DE ABRIR USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"Puls±∂±†c•r±Ñ®cluÚ.",27},
	{"-L†®clus†y†®t#ßbi•”.",28},
	{"-Ab§»Üpu•t†ext•i≥ yß l∑»Ö¥t•i≥ -di‰Ö≥d§“≥«LaÜpu•t†ext•i≥∞eßb≠É u£s e¢miëû’∆gu√∑úüpr®i≤®.",29},
	{"-C•r∑»Üpu•t†ext•i≥- ≠pi™Ö≥d§“≥",30},
	{"Un†ÃzÑçu•t†ext•i≥∞eÊ†c•π»Âu‹üch≥œsÅai≠ †pr®i&£surg§Ålû—≠dôp±†¡im¥±¬›É”m¥∑tôe∆gu√±ÅnÀvoÑpr®i&n.",30},
	{"U£p∑õ’ßb≠ y∂•mi™ÖÓc®¢a∫¥t•i≥Ål†≈Ã.",31},
	{"-L†®clus†y†®t#´•πd†-≠p≥”Ö≥d§“≥Åab≥».",32},
	{"Ap§ûu‹ümil%ﬁtœsÅpl#ƒÔ¢y¿et√°e∞ep±∑ìl¶xt•i≥.",33},
	{"Fr%¢√°Óø.",34},
	{"C€oáÏ†‹cÆΩscur†s√v¢p≥Öbll¢®quivoÅ‡ütœz›Åhi¡¢qÀ¶ƒ#£Íy§».",35},
	{"L†≈Ã¿odul±¶ƒ#Œ±ÅZHL«P¥t“aÅam±ill¢yÉÖ‡goÅºÜ—+%aágr∑dôﬂŸûœj….",36},
	{"ZHL 24h",37},
	{"Co£difÔult“¨iƒ¥goÖp•filÅu£ËifÔÛÅﬁt√òÑt≥móa«",38},
	{"E£Ïút•√Ål†ë“†bll†Ï°ecºd¢num$∏.",39},
	{"P≥ Ï†ab•tur†’ìsliz†u£Í+&£l#s• qÀ°eßpuªa: TECLEE EL C&DIGO DE ACCESO«TIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"U£Í+&nÅ…pecöp¡igœs¢·gÀ¿iümovimió›.",41},
	{"Tod¢so£Íjûbl∑c…Å”⁄+¢·mil±«Lûm#ügr∑dô’òcuë∑á‡ü®t∑tôm#übaj›.",42},
	{"A‡j∑ìc§…ÅpeqÀ+›Ét§Ë≥ôbl∑∏s.",43},
	{"Tod¢fÏci≤√«El¶s—ci¢sufÔióe∂±†m∑t§•úsÉdÔi≤ônec®±iûp±†pr®•v±¿◊•i√ôbÛl&gi∏s.",44},
	{"Un†¡ev“†b&Ãd†f≥⁄Ö™choÅ®t†Úº.",45},
	{"U£—qÀ™ßzulÉ u£gπ£¥dÔ“≥Åp¡igr¢bÛl&gi∏òÖfr≤t√«",46},
	{"-Es™¶sÖ—qÀ™ -susurπÖ≥d§“≥átuΩ%».",47},
	{"-N¢pÀ»,úüdi≠ctiv…Ål†empr®†ﬁ¬¢impid§«",48},
	{"P¡igr¢bÛl&gi∏«C≤s•v± †m§›Å15´¡·uübaj¢c•o«N¢m∑ipul±∞i£pœ™cci&n«N¢abr«N¢golpe±«M◊•ia∫fr#gil.",49},
	// Textos relativos al ordenador
	{"-Co≥d¥où»ü‡üs ™m…Ål†≈Ã«P±†Òbl±Émig¢empﬂa: ≥d§“≥Ü∑»«AlgÏûsug•§ci…Å∏m∑»üs≤: ≥d§“≥ßyudaÂ≥d§“≥Õ€b≠Â≥d§“≥¿ i&n..«-™ÿ®p≤ñs•vÔi√Ö≥d§“≥Å≈ÃgÓi&n.",50},
	{"-OhÂvayaÜ¢n¢p§s$áﬂ•¶s¢-di‰Ö≥d§“≥ÉÌ√s†“miπci&n.",51},
	{" ",52},
	{"N¢‹ö≈daáp±tÔul±.",53},
	{"N“†qÀìƒÓ±.",54},
	{"N¢ô®peci√móe ¥t•®∑™.",55},
	{"N¢su‰ñ≈d†¥®p•a».",56},
	{"Elßulli»ì∫vió¢r®u§aòÖfu’ºje.",57},
	{"-Bu§°πbaj¢-aprÀbaÑvoz∞◊ fecÒì∫≥d§“≥« ",58},
	{"-Ah≥†ôm€óoÅp≤•ÿumb¢†M±™«Baj†aÑbo©gaÅc±g†miëû≠¥Ôi¢‡üs ™m…Ål†≈Ã -di‰Ö≥d§“≥É∂≠muπ«",59},
	{"D®ci§d¢‡ü®c√≤ôaÑbo©g†yìp›iøÖ—qÀ™ jÏö†‡åm#üp§dió®Åëega«A∫≠gr®±ìscubr¢qÀÑs√†’Ê†c•π».",60},
	{"-N¢ô≈d†p•s≤√∂•¢ôm€óoÅ≠cÔl± -di‰Ñvozì∫≥d§“≥-¿iëû™Ì√l∑úüpi•nû÷golpe…ÉÑÍbezaÉtπÖsu¡o.",61}, 
	{"-L¢m#üdur¢ôt§• qÀ ≠cÔl±∞uüpiezûp±aÑ·guióe¿ i&n«Lﬂga£†c≠•’Êum∑›«E£f¥..«-suspiπÖ≥d§“≥¿iëû≠∏ge¬oür®øsÅtu´u•poÉ Ï†œbof≠g≤a.",62},
	{"-Cë√,ßqu% To–C≤n≥ -di‰Ñvoz- VolÃmoü†M±™ÉÖ—qÀ™«RepiövolÃm›ÉÖ—qÀ™«",63},
	{"Hay¨oübot≤®: œj¢÷v•©«Se Îiliza£p±†c•r± yßbrÑ®clus†√¶xt•i≥«",172},
	{"Loü·guióô—qÀtôp±†ëeg±.",173},
	{"N¢ôm€óoÅjug±ß∫Sokob∑.",174},
	{"-Vooº≠...ΩohΩooh -™ìvu¡Ã´ru¡Öe∏Ål†≈Ã.",175},
	{"-C∑”≠,ΩohΩooh -¥tóûó≤± ^ -Nõblu¨ip¥ödi„lu...",176},
	{"S&l¢®cuch¢®t#tiÍ«Laùrmó†¥t•fi•eáºsÜÏiÍci≤®.",177},
	{"EsøyòÑc±†ocul”,Õ¢Ã¢J'p‚•.",178},
	{"S◊$li™ Æºd¢e ¥h&spiø.",179}, 
	{"L†ë“†√ßl⁄c$n«",180},
	{"FÏci≤aÉÜ∑»sÅvozß∫≥d§“≥: ≥d§“≥Ü∑».",181}, 
	{"Eüu≈Éƒrucci&£ﬁt#lÔ†÷≠ct∑gul± qÀ∞e ¥t•n†bajo°i•π.",182}, 
	{"(§Ö™cº»)",183},
	{"L†pu•”ìlßl⁄c$£y†®t#ßbi•”.",184},
	{"El°ecºd¢’∆lum¥aáœjo«CLAVE INCORRECTA.",185}, 
	{"El°ecºd¢’∆lum¥aáv•©«CLAVE CORRECTA«El´a+&£l#s•∞e ≠pliegaásuÜp±timóo.",186}, 
	{"El´a+&£l#s•Üi§z††c√ó±’.",187},
	{"El´a+&£l#s•∞e∂≠p±††d p±±«",188},
	{"El´a+&£l#s•¨ p±a«",189},
	{"P•¢≈d†su‰©«Un†volu”Åhum¢yßlgÏûch pûsurg§ìl´a+&n.",190},
	{"S≤Ét§Ë≥®ÅŸ∑sp≥™.",191}, 
	{"(∏gi§d¢∑t®Ötπje)",192},
	{"-Loüs ™mûy†®t#námo»ÅbajoÉsumm¢-™ ≠cu•daÖ≥d§“≥.",193},
	{"-S&l¢nec®iöu£—qÀ™ßzul«",194},
	{"L†sup•fÔie ôl a,∞&l¢’ßctivaÉÖ™cº».", 195},
	{"E U R O P A",196},
};
#endif 

#ifdef ENGLISH

token_t mensajes_t [] =
{
	{"ZHL^ Weìliv•èµp±cõwiØi£24h«^ (c) 2016Â2019Â2021 KMBR«R¡e…e 5.",1},
	{"I¨≤'t∞eeßnyØâi£p±tÔul±.",2},
	{"ZHL„÷KMBR",3},
	{"TÆyìsc§dÇÄcëa∫‹©.",4},
	{"TÆyßsc§dÇÄ∏mm∑–bdge.",5},
	{"ãmoduﬂÇ∏mm∑–Äship.",6},
	{"ãMilk÷Way∆£‘r´…e.",7},
	{"ãship'ü≈vig◊i≤Ésoﬂ«Ità†fairlyÕew¿o©lÂÄ≤-bo±dÜpÎ•ài£ch±geé≈vig◊Û£∑dßllÜm∑düa≠¿añb÷voi‰«AæÄm€ó Äc≤soﬂ∞c≠§àbºck.",8},
	{"'Weß≠Ωp•◊âi£‡w∂ow•¿o©«TÆÉsoﬂ¿usæ≠⁄i£off'Â≠pliôÄçÎ•.",9},
	{"ItÜôfœm Äc≤tœlÉsoﬂ«TÆÉsoﬂài£‡w∂ow•¿o©«",10},
	{"S‹wßŒ∆‰ßæm¥uü150 C¡·us.",11},
	{"ãîrm√∞ys™m´a£h±dly∂≠vó Äf≥m◊i≤égºsüo£Ä‘t·©éÄw¥dsc≠§.",12},
	{"TÆ÷f≥mΩ£Äîr⁄∫gπdióséÄship'üw¥dsc≠§",13},
	{"ã©liv•y∞Æ–wh•e I¨¢Äœu™«Itàa£¥duƒa∫modõbuilæwiØ∞t∑d±d¿odul®«It¨oô‚üjobßŒ¨o®n'æb≠ak¨ownù¢oft§.",14},
	{"'ItÉtœlüÄ™mp•◊u≠ ¥·ñ∑d∆£Ä¥ƒrumósÇavoidíeirìt•i≥◊i≤,' ≠p≥tüÄçÎ•",15},
	{"Ità≤eéÄtw¢surviv√∞u‚ü≠qui≠dÇp•f≥m EVA«ãsu‚àfullyßuøm◊ÔßŒÊûa£aÎ≤€yéeighæh‘rs«",16},
	{"PÓkag®Çbeìliv•Ëíœugh‘æÄsol±∞ys™m.",17},
	{"It'üoff.",18},
	{"IÁ≤'t∞urviÃ∆£EuœpeÁiØ‘æÄpœ™ctiÃ∞u‚.",19},
	{"'T¢avoidÉ”m¥◊i≤,¬eaÃ Äsuiæbeh¥–befo≠∂…sâÄcëa∫‹©,'  ÄçÎ• ≠m¥dsè.",20},
	{"ãair‡ckàu’dÇequ√ e Äpr®su≠„etwee£Ä‘t·ñ∑–¥·©éÄship«Iæ Étœlﬂ–b÷Ä≠–bÎt≤Çc‡’ßŒ Äg≠e£bÎt≤Çop§«",21},
	{"Itàc‡’d.",22},
	{"Itàop§.",23},
	{"'ãair‡ckàop§e–wiØ Äm∑u√Étœls,' ≠p≥tüÄçÎ•",24},
	 {"'ãair‡ckàop§e–wiØ Äm∑u√Étœls,' ≠p≥tüÄçÎ•",24}, 
	{"'ãair‡ckàc‡’–wiØ Äm∑u√Étœls,'ÜpÎ• ≠p≥ts«",25},
	{"Pr®sÇope£Äair‡ck«WARNING: WEAR SURVIVAL SUIT IN HOSTILE ENVIRONMENT BEFORE OPENING.",26},
	{"Pr®sÇc‡’ Äair‡ck.",27},
	{"ãair‡ckà‹wΩp§.",28},
	{"'Op§â‘t•ßir‡ckßŒ∆soºtâÄ¥t•i≥,'∞ayüÄçÎ•«ã‘t•ßir‡ckΩp§üwiØ †h üûÄpr®surôequ√ e.",29},
	{"'Cl›â‘t•Ê◊ch,' ≠pe◊üÄçÎ•",30},
	{"On‰ Ä‘t•Ê◊chÊûc‡’dÂjetsépr®sur ËßiµburƒΩÎéÄw√lsÇ≠moÃÉ”m¥∑tü∑d¶qu√ e Äpr®su≠ßga¥.",30}, 
	{"A∂∑õop§ü∑dßl‡wüÓc®sÇÄ¥t•i≥éÄs—‰cπft.",31},
	{"'ãair‡ckà‹w´‡’d,' ≠p≥tüÄ≤-bo±dÜpÎ•.",32},
	{"Jusæ†few¿illiﬁŸ®épºƒÔßŒ¿e”∫ oº™èÌœm Ä‘t·©.",33},
	{"ColdÇÄøuch.",34},
	{"Aüi£†d±kÕight¶x‰pæf≥ Ä¡u·Ã g‡wéf√lâi‰´hÏks.",35},
	{"ãƒ∑d±–ZHL¿odul±∞hip«Pa¥™–y¡‡wßŒÁiØ Äç∑y¬og¢i£big ≠d¬ett•s.",36},
	{"ZHL 24h",37},
	{"WiØ¨iffÔult÷I´a£⁄keΩuæÄ‘tl¥eé†ﬁ”∫buildâi£Äƒ≥m«",38},
	{"O£Ä·©éÄë∑‰∞h¥ô†num•Ô key—d",39},
	{"Aús•´∑‹£slid®íœughß£op§â∑d∂o¥tü◊è: TYPE IN THE ACCESS CODE«YOU HAVE ONE CHANCE BEFORE DESINTEGRATION.",40},
	{"A¨∑g•‘s-‡okâc∑‹£fol‡wümy¿oÃmós.",41},
	{"Allß≠Áhi™„ox®é·mil±∞ize«ãl±g®tß≠Ω£Ä‡w®t∞Ælv®.",42},
	{"TÆ÷h‘’¨oz§sésm√∫whi™É”¥•s.",43},
	{"Ba≠¿¥imum«Juƒò‘gh∞—‰Ç⁄¥”i£Äc≤d‚i≤ünee©dÇpr®•Ã„Û‡giÍ∫m◊•i√s.",44},
	{"AÊigh vaulæf≥müÄ‰ilâofíiüœ€.",45},
	{"A„lÀ∂ÓkageÁiØßúrge„ÛÒz±–¥dÔ◊≥Ω£Äfr≤t«",46},
	{"'Th àÄ—ckage,' ÄçÎ•Áh p•ü¥èr¶±.",47},
	{"I´∑'tÂÄç∑y'üdi≠ctivôp≠vó¿eÌœm¨oâso«",48},
	{"BÛÒz±d«Sø≠„¡ow¿¥uü15 C¡·us«D¢‹æh∑dﬂÁiØ‘t∂œ™cti≤«D¢‹tΩp§«D¢‹æh∑dﬂ Ïpœ™c™d«Fπgiﬂ¿◊•i√.",49},
	// Computer-related texts
	{"'I¿∑ageßll∞—‰cπft'üsys™ms«To°√kÇﬁ u’:ÜpÎ•Üm∑d«S€e∞ugg®ti≤üofÜm∑düa≠:ÜpÎ• Ælp,ÜpÎ• ≈ﬁ,ÜpÎ•¿ ·≤..' Ä≈vig◊i≤ÜpÎ•ÿ®p≤düÆlpfullyÇy‘.",50},
	{"'OhÂI¨idn'tí¥k I'–≠“í◊,'∞ayüÄçÎ•ÁiØÌ√’ßdmiπti≤.",51},
	{" ",52},
	{"I¨≤'æ‹ti‰ßnyØâi£p±tÔul±.",53},
	{"NoØ¥gÇhighlight.",54},
	{"It'ü‹t∂±tÔul±l÷¥t•®t¥g.",55},
	{"NoØâÏexpec™–Òpp§s.",56},
	{"ãhowléÄw¥d¶choôi£Äfu’ºge.",57},
	{"'Goo–job,'ßppœvôÄs◊ fie–voi‰éÄçÎ•.",58},
	{"'Now∆t'ütiﬁÇ’tïur’Ì≥ M±s«G¢»wnÇÄc±g¢hol–whiﬂ I ≠booæÄship'üsys™ms,' ÄçÎ•∞ayüÒƒily.",59},
	{"Iìsc§–Äs™psÇÄc¡l±ßŒìp›iæÄ—ckageÁiØ Äoîrüawa‚â©liv•y«WÆ£I ≠tur£I¨ ∏v•íaæÄœ€Êûc‡’d.",60},
	{"'It'ü‹Øâp•s≤a∫buæ‚'ütiﬁÇ≠cycﬂ,'∞ayüÄçÎ• voi‰,ßsèµﬂgügiÃΩÎßŒè„∑gèµÆ“Ω£Äf‡≥",61}, 
	{"'ãh±d®tí¥gàÒv¥gÇ≠cycﬂíeiµp±tüf≥ Änexæm ·≤«TÆyÜeÇØ¥kéîms¡vôûhum∑«Anyway...'∞ighüÄçÎ• û‚∞∏opüup Ä≠⁄¥séy‘µbod÷wiØ †œbo-scrubb•.",62},
	{"'Cë√,í àTo–C≤n≥,'∞ayüÄvoi‰Â'I'm ≠turn¥gÇM±üwiØ Ä—ckage«I ≠peaæI'm ≠turnâwiØ Ä—ckage.' ",63},
	{"Th•eß≠°w¢bÎt≤s: ≠dßŒ g≠§«TÆyß≠ u’dÇc‡’ßŒΩpe£Äair‡ckÇÄ‘t·©«",172},
	{"Next∂Ókag®Çbeìliv•Ë.",173},
	{"Th à‹°iﬁÇpº÷Sokob∑.",174},
	{"'Vooº≠...ΩohΩooh'è geæ†cruõech¢bÓkÌœm Äship.",175}, 
	{"'C∑”≠,ΩohΩooh 'y‘°ryÇ¥t≤e ^ 'Nõblu¨ip¥ödi„lu...'",176},
	{"I Æ± ≤ly∞”tÔ«ãƒ≥mà¥t•f•âwiØÜmÏÔ◊i≤s.",177},
	{"I'mΩ£Äd±k∞i©ÂI´∑'t∞ee Jup‚•",178},
	{"IcyÂ¥h›pi”bﬂ∞a™lli™.",179}, 
	{"ãë∑‰ÇÄwa≠h‘’«",180},
	{"Iæw≥küwiØ voi‰Üm∑dsÇÄçÎ•:ÜpÎ•Üm∑d.",181}, 
	{"Ità†≠ct∑gul±¿et√Éƒructi≤íaægoôuŒ•gœuŒ.",182}, 
	{"(o£Äkeybo±d)",183},
	{"ãwa≠h‘’¨o≥à√≠“yΩp§.",184},
	{"ãkey—dàillum¥a™–≠d«INCORRECT KEY.",185}, 
	{"ãkey—dàillum¥a™–g≠§«CORRECT KEY«ãºs•´∑‹£≠tπctü¥ö‚sÜp±tmó.",186}, 
	{"L…•´∑‹£beg¥sÇÆaæup.",187},
	{"ãºs•´∑‹£p≠p±®Çfi≠«",188},
	{"L…•´∑‹£fir®«",189},
	{"Buæ‹ØâÒpp§s«A∂uffésmokeßŒ †few∞p±küem•geÌœm Äc∑n≤.",190},
	{"TÆy'≠∞hipp¥gÉ”¥•s.",191}, 
	{"(pÔkâup Äsuiæfirƒ)",192},
	{"-ãsys™müa≠ßl≠“y∆£‡w∂ow•¿oñ- ÄçÎ• ≠m¥dsè.",193},
	{"-I jusænee–†blÀ∂Óket«",194},
	{"ãsurfa‰àsmooØÂ≤lyßctiva™–wiØ Äkeybo±d.", 195},
	{"E U R O P A",196},
};
#endif 

#ifdef SPANISH
token_t mensajesSistema_t [] =
{
	{"N¢pÀd¢v• ≈da,¶ƒ#¿uyΩscuœ.^",0},
	{"Tambi$£Ò÷",1},
	{"Escbe°uü&rd§ôaqu%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&mo? P≥Ìav≥∂rÀbaÉΩŸû—ºbπs.^",6},
	{"N¢pÀd¢irá®†di≠cci&n.^",7},
	{"øPerdÛn?^",8},
	{"Lﬂv¢",9},
	{"(puesto)",10},
	{"n¥g'£objeø.",11},
	{"/Seguœ? ",12},
	{"/JÀg…ÅnÀvo? ",13},
	{"AdiÛs...",14},
	{"OK^",15},
	{"[...]",16},
	{"Hû≠√iz“¢",17},
	{"°ur‹",18},
	{"s",19},
	{".^ ",20},
	{"L†puªuÓi&£®Å",21},
	{"∂uªo",22},
	{"N¢lﬂv¢pu®ö®o.^",23},
	{"N¢pÀ»Ây†lﬂv¢®¢pu®ø.^",24},
	{"Y†t§g¢",25},
	{"N¢Ã¢®¢p≥ßqu%.^",26},
	{"N¢pÀd¢lﬂv±¿#sïs….^",27},
	{"No°§g¢®o.^",28},
	{"P•¢· y†lﬂv¢pu®ø",29},
	{"S",30},
	{"N",31},
	{"M·s...",32},
	{"> ",33},
	{"",34},
	{"El°iemp¢p…a...^",35},
	{"Ah≥†t§g¢",36},
	{"Me∂≤g¢",37},
	{"Me quiö",38},
	{"Dej¢",39},
	{"N¢pÀd¢p≤•ﬁ ",40},
	{"N¢pÀd¢qu‚±ﬁ ",41},
	{"<T§goìm…i“…ïs…álûm∑›!",42},
	{"D®gπci“amóe∂®aìm…ia».",43},
	{"Meto",44},
	{"Ah≥†n¢®t#á",45},
	{",",46},
	{" ÷",47},
	{".",48},
	{"No°§g¢",49},
	{"N¢lﬂv¢pu®ö",50},
	{"",51},
	{"Es¢n¢®t#á",52},
	{"n¥g'£objeø",53},
	{"FÔh•¢‹òc≤tπ».^",54},
	{"FÔh•oïrrupø.^",55},
	{"Err≥ÅE/S«FÔh•¢n¢gπba».^",56},
	{"Di≠ct≥i¢ll§o.^",57},
	{"D c¢ll§o.",58},
	{"N€b≠ÅfÔh•¢n¢v#li».^",59},
	{"N€b≠ì∫fÔh•o: ",60},
	{"",61},
	{"/P•d&n? P≥Ìav≥∂rÀbaÉΩŸû—ºbπs.^",62},
	{"Aqu% ",SYSMESS_NPCLISTSTART},
	{"®t# ",SYSMESS_NPCLISTCONTINUE},
	{"est·n",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"Dë¢Ò÷",SYSMESS_INSIDE_YOUCANSEE},
    {"Encim†Ò÷",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"N¢ô√g¢qÀ∂Àd†qu‚±ﬁ.^",69},
	{"P≤g¢",SYSMESS_YOUPUTOBJECTON },
    {"N¢ô√g¢qÀ∂Àdaïg•’.^",SYSMESS_YOUCANNOTTAKE},
	{"N¢—≠‰ qÀ∂Àd†mov•’.^", SYSMESS_CANNOTMOVE},
	{"Lﬂvoúüm∑oüvÓ%….^", SYSMESS_CARRYNOTHING},
	{"S√idûv ibl®:",SYSMESS_EXISTLIST},
	{"",0}	
};
#endif 

#ifdef ENGLISH 
token_t mensajesSistema_t [] =
{
	{"It'sù¢d±kÇ’eßnyØ¥g.^",0},
	{"Y‘´a£’e ",1},
	{"Wh◊¨oèÁ∑æﬁÇd¢‹w?",2},
	{"",3},
	{"",4},
	{"",5},
	{"S≥ry? Pﬂ…e°ryΩîµw≥ds.^",6},
	{"I´∑'æg¢¥í◊¨i≠cti≤.^",7},
	{"P±»£ﬁ?^",8},
	{"Ißm´±ry¥g: ",9},
	{"(worn)",10},
	{"‹Øâ◊ßll.",11},
	{"A≠è∞u≠? ",12},
	{"DoèÁ∑tÇpºyßga¥? ",13},
	{"Goodbye...",14},
	{"OK^",15},
	{"[...]",16},
	{"Y‘ÊaÃ°ype–",17},
	{"°urn",18},
	{"s",19},
	{".^ ",20},
	{"Y‘r∞∏≠à",21},
	{"∂o¥t",22},
	{"I'mÕoæwe±âØ◊.^",23},
	{"I´∑‹tÂI'mßl≠“÷we±âØ◊.^",24},
	{"Ißl≠“÷ÒÃ ",25},
	{"I´∑‹t∞eeí◊ßœuŒ.^",26},
	{"I´∑‹t´±ryßnymo≠.^",27},
	{"I¨≤'æÒÃí◊.^",28},
	{"I'mßl≠“÷we±â",29},
	{"Y",30},
	{"N",31},
	{"More...",32},
	{"> ",33},
	{"",34},
	{"Tiﬁ∂…sô...^",35},
	{"I'Ã°ake£",36},
	{"IÁe± ",37},
	{"I ≠moÃ ",38},
	{"I¨œp ",39},
	{"I´∑‹æwe±  ",40},
	{"I´∑‹æ≠moÃ ",41},
	{"M÷h∑düa≠Ìull!",42},
	{"It'sù¢Æavy.",43},
	{"I∂uæ",44},
	{"Ità‹æi£",45},
	{",",46},
	{"ßŒ ",47},
	{".",48},
	{"I¨≤'æÒÃ ",49},
	{"I'mÕoæwe±â",50},
	{"",51},
	{"Th◊à‹æi£",52},
	{"‹Øâ◊ßll",53},
	{"FiﬂÕoæf‘Œ.^",54},
	{"C≥rup™–fiﬂ.^",55},
	{"I/O •r≥«FiﬂÕot∞aÃd.^",56},
	{"Di≠ct≥÷full.^",57},
	{"D càfull.",58},
	{"Inv√id∞aÃgaﬁ ≈ﬁ«Pﬂ…e´Æck Ä≈ﬁè ó•Ëàc≥≠ct,ßŒ¿ake∞u≠èß≠°ry¥gÇ‡a–ÄgaﬁÌœm ÄÚﬁÌiﬂè∞aÃd.^",59},
	{"Pﬂ…e ó•∞aÃgaﬁ ≈ﬁ«Reﬁmb•Ç‹™¨ow£Ä≈ﬁè´hoo’Âûiæwil∫be ≠qu®™d∆£≥d•Çr®ø≠ Ägaﬁ∞”tus.",60},
	{"",61},
	{"S≥ry? Pﬂ…e°ryΩîµw≥ds.^",62},
	{"H•e ",SYSMESS_NPCLISTSTART},
	{"I´a£’e ",SYSMESS_NPCLISTCONTINUE},
	{"I´a£’e ",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"In·ñI∞ee ",SYSMESS_INSIDE_YOUCANSEE},
    {"Onùp I∞ee ",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"Ità‹t∞€eØâI´a£≠moÃ.^",69},
	{"I∂uæ",SYSMESS_YOUPUTOBJECTON },
    {"Ità‹t∞€eØâI´∑°ake.^",SYSMESS_YOUCANNOTTAKE},
	{"It´∑‹æbe¿oÃd.^", SYSMESS_CANNOTMOVE},
	{"M÷h∑düa≠¶mpty.^", SYSMESS_CARRYNOTHING},
	{"Exists:",SYSMESS_EXISTLIST},
	{"",0}	
};

#endif 
// Tablas de vocabulario
// Nombre propios, sustantivos...
// ˙ltimo elemento debe ser 0
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

#ifdef SPANISH 
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

#endif 

#ifdef ENGLISH
token_t nombres_t [] =
{
    {"north",           nNorte},  //0
	{"n",               nNorte},
	{"south",             nSur},    //2
	{"s",               nSur},
	{"east",            nEste},   //4
	{"e",               nEste},
	{"west",           nOeste},  //6
	{"o",               nOeste},
	{"northeast",         nNoreste}, //8
	{"w",               nOeste},
	{"northwest",        nNorOeste}, //10
	{"ne",              nNoreste},
	{"southest",         nSurEste},	 //12
	{"se",              nSurEste},
	{"southwest",        nSurOeste},  // 14
    {"sw",           nSurOeste},
    {"up",          nArriba},   // 16
	{"nw",              nNorOeste},
	{"down",           nAbajo},   // 18
	{"enter",			nEntrar}, // 20
	{"exit",			nSalir}, // 22
	{"leave",			nSalir}, // 22
	{"up",	nArriba},
	{"down",  	nAbajo},
	{"desce",	nAbajo},
	{"i",               nInventario},
    {"inven",           nInventario},
	{"inv",         nInventario },
	{"score",       nPuntos},
	{"points",       nPuntos},
	{"turns",       nTurnos},    
	// Names < 20 can be used as verbs
	// Nombres para el Vocabulario del juego,
	{"all",        nTodo},
	{"door", nPuerta},
	{"button", nBoton},
	{"stair", nEscalera},
	{"wall", nPared},
	{"floor", nSuelo},
	{"ceill", nTecho},
	{"light", nLuz},
	{"beam", nLuz},
	{"winds", 	nParabrisas},
	{"box",	nCaja},
	{"parcel",	nPaquete},
	{"conta",	nContenedor},
	{"sky",	nCielo},
	{"space", 	nNave},
	{"ship",	nNave},
	{"fusel",	nNave},
	{"node",	nNodo},
	{"bridg",	nPuente},
	{"storm",	nTormenta},
	{"europ",	nEuropa},
	{"moon",	nLuna},
	{"moons",	nLuna},
	{"satel",	nSatelite},
	{"jupit",	nJupiter},
	{"jovia",	nJoviano},
	{"face",	nCara},
	{"side",	nLado},
    {"inter", 	nInterior},
	{"wareh",	nAlmacen},
	{"mass",	nMole},
	{"build",	nEdificio},
	{"compu", 	nOrdenador},
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
	{"bridge", 	nConsola},
	{"instr",	nSistema},
	{"airlo", 	nEsclusa},
	{"hatch",	nEsclusa},
	{"gate", 	nEsclusa},
	{"suit",	nTraje},
	{"cargo", nBodega},
	{"hold", nBoveda},
	{"shelv",	nEstanteria},
	{"camera",	nCamara},
	{"canno",	nCanon},
	{"32768",	n32768},
	{"key",	nTeclas},
	{"keypad", nTeclas},
	{"keybo", nTeclas},
	{"exter",	nExterior},
	{"outsi",	nFuera},
	{"label",	nEtiqueta},
	{"indic",	nIndicador},
	{"scree", nPantalla},
	{"instr", nPantalla},
	{"contr", nControles},
	{"panel", nPantalla},
	{"shado", nSombra},
	{"",0}
};

#endif 

// Verbos
// VOCABULARIO
// Verbos < 20 son iguales a nombres < 20

#ifdef SPANISH 

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
	{"ENSE—", 	36},
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
	{"VERTI",	86},  // TÈrmino errÛneo, pero ampliamente extendido
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
#endif 

#ifdef ENGLISH
token_t verbos_t [] =
{
    {"take",	vCoger},
    {"pick",	vCoger},
    {"drop",	vDejar},
    {"remove",	vQuitar},
    {"remove",	vSacar},
    {"remove",	vQuitar},
    {"l",		vMirar},
    {"look",	vMirar},
    {"r",		vMirar},
    {"redes",	vMirar},
    {"quit",	vFin},
    {"save",	vSave},
    {"salva",	vSave},
	{"load",	vLoad},
	{"ramsa",	vRamsave},
	{"ramlo",	vRamload},
	{"carga",	vLoad},
	{"x",       vExaminar},
	{"exami",	vExaminar},
	{"ex",		vExaminar},
	{"regis",	vExaminar},
	{"say", 	vDecir},
	{"talk",		vDecir},
	{"answer", 	vDecir},
	{"order",  	vDecir},
	{"throw",	vLanzar},
	{"push",	vEmpujar},
	{"press",	vEmpujar},	
	{"press",	vPulsar},
	{"turn",  	vGirar},
	{"rotat",	vGirar},
	{"listen", 	vEscuchar},
	{"hear",		vEscuchar},
	{"touch",	vTocar},
	{"pat",	vTocar},
	{"smell",	vOler},
	{"sniff",	vOler},
	{"wait",	vEsperar},
	{"z",		vEsperar},
	{"sing",	vCantar},
	{"jump", 	vSaltar},
	{"attac",	vAtacar},
	{"kill",	vAtacar},
	{"fight",	vAtacar},
	{"punch",	vAtacar},
	{"kick",	vAtacar},
	{"pee",	vAtacar},
	{"open",	vAbrir},
	{"close",	vCerrar},
	{"activ",	vEncender},
	{"deact",	vApagar},
	{"break",	vRomper},
	{"destroy",	vRomper},
	{"put",		vPoner},
	{"wear", vPoner},
	{"wear",	vVestir},
	{"put",	vVestir},
	{"give",		vDar},
	{"put",	vMeter},
	{"insert", 	vMeter},
	{"go",		vIr},
	{"walk",		vIr},
	{"run",	vIr},
	{"read",		vLeer},
	{"move",	vEmpujar},
	{"type", vTeclear},
	{"write", vEscribir},
	{"point", vPuntos},
	{"score", vPuntos},
	{"turns", vTurnos},
	{"use", vUsar},
	{"activ", vUsar},
    {"",0}
};
#endif 

#ifdef SPANISH
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
#endif 

#ifdef ENGLISH
token_t adjetivos_t [] =
{
	{"small", aPequeno},
	{"big", aGrande},
	{"old", aViejo},
	{"new", aNuevo},
	{"hard", aDuro},
	{"soft", aBlando},
	{"short", aCorto},
	{"long", aLargo},
	{"blue", aAzul},
	{"green", aVerde},
	{"black", aNegro},
	{"red", aRojo},
	{"yellow", aAmarillo},
	{"therm", aTermico},
	{"cold", aFrio},
	{"hot", aCaliente},
	{"",0}
};
#endif

// Tabla de objetos
// No existe la limitaciÛn de PAWS donde el objeto 1 siemmpre es la fuente de luz 
// La luz en ngpaws se calcula en funciÛn del atributo de los objetos presentes en la localidad, puestos y llevados.
// Localidades de sistema: LOCATION_WORN,LOCATION_CARRIED, LOCATION_NONCREATED, LOCATION_HERE, CARRIED, HERE, NONCREATED, WORN

// Atributos con OR: aLight, aWear, aContainer, aNPC, aConcealed, aEdible, aDrinkable, aEnterable, aFemale, aLockable, aLocked, aMale, aNeuter, aOpenable, aOpen, aPluralName, aTransparent, aScenary, aSupporter, aSwitchable, aOn, aStatic, aExamined, aTaken, aDropped, aVisited, aTalked, aWore, aEaten, aPropio, aDeterminado

#ifdef SPANISH
obj_t objetos_t[]=
{
    // ID, LOC, NOMBRE, NOMBREID, ADJID, PESO, ATRIBUTOS
    {oCaja, lZonaA2,"—qÀ™ßzul",     nPaquete, aAzul,   1, aMale_hex | aDeterminado_hex},  
    {oTraje, lEsclusa,"tπje∂r®uza»",     nTraje, EMPTY_WORD,   1, aWear_hex| aMale_hex | aDeterminado_hex},  
	{oEsclusa, lEsclusa,"çu•”Ål†®cluÚ", nEsclusa, EMPTY_WORD,   1, aStatic_hex | aFemale_hex | aDeterminado_hex},  
	{oPuerta, lEntrada,"pu•”Åﬁt√",     nPuerta, EMPTY_WORD,   1, aStatic_hex | aFemale_hex},  
	{obotonrojo, lEsclusa,"bot&£œjo",     nBoton, aRojo,   1, aStatic_hex | aConcealed_hex | aMale_hex},  
	{obotonverde, lEsclusa,"bot&£v•©",     nBoton, aVerde,   1, aStatic_hex | aConcealed_hex | aMale_hex},  
	{oCanon, NONCREATED,"Í+&nÅvigil∑cia",     nCanon, EMPTY_WORD,   1, aStatic_hex | aMale_hex},  
	{oTeclado, NONCREATED,"teclado",     nTeclado, EMPTY_WORD,   1, aStatic_hex | aMale_hex},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x00000000}
}; // Tabla de objetos de la aventura
#endif 

#ifdef ENGLISH 
obj_t objetos_t[]=
{
    // ID, LOC, NOMBRE, NOMBREID, ADJID, PESO, ATRIBUTOS
    {oCaja, lZonaA2,"blÀ∂±c¡",     nPaquete, aAzul,   1, aMale_hex | aDeterminado_hex},  
    {oTraje, lEsclusa,"pr®uzË∞u‚",     nTraje, EMPTY_WORD,   1, aWear_hex| aMale_hex | aDeterminado_hex},  
	{oEsclusa, lEsclusa,"air‡ck ga™", nEsclusa, EMPTY_WORD,   1, aStatic_hex | aFemale_hex | aDeterminado_hex},  
	{oPuerta, lEntrada,"»≥¿et√",     nPuerta, EMPTY_WORD,   1, aStatic_hex | aFemale_hex},  
	{obotonrojo, lEsclusa,"≠–bÎt≤",     nBoton, aRojo,   1, aStatic_hex | aConcealed_hex | aMale_hex},  
	{obotonverde, lEsclusa,"g≠e£bÎt≤",     nBoton, aVerde,   1, aStatic_hex | aConcealed_hex | aMale_hex},  
	{oCanon, NONCREATED,"surÃill∑‰´∑n≤",     nCanon, EMPTY_WORD,   1, aStatic_hex | aMale_hex},  
	{oTeclado, NONCREATED,"keypad",     nTeclado, EMPTY_WORD,   1, aStatic_hex | aMale_hex},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x00000000}
}; // Tabla de objetos de la aventura
#endif

// Para no usar las tablas de nombres y mensajes podemos aÒadir una a medida
// para las conversaciones con PNJs. 

// Tabla de conversaciÛn con el ordenador 
// El link entre la tabla de temas y los mensajes es el ID. 
#ifdef SPANISH
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
#endif 

#ifdef ENGLISH
token_t ordenador_topics_t[] = 
{
	{"hi",1},
	{"bye",2},
	{"job",3},
	{"me",4},
	{"I",4},
	{"pilot",4},
	{"drive",4},
	{"trans",4},
	{"storm", 5},
	{"winds", 5},
	{"europ",7},
	{"moon",7},
	{"moons",7},	
	{"jovia",8},
	{"jupit",8},
	{"face",9},
	{"side",9},
	{"where", 10},
	{"missi", 11},
	{"name",12},
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
	{"graph",19},
	{"transi",20},
	{"isla", 21},
	{"uto", 22},
	{"csg",22},
	{"kmbr",23},
	{"kmbrkat",23},
	{"kno",24},
	{"dla",25},
	{"dela",25},
	{"frenc",26},
	{"engli",26},
	{"itali",26},
	{"germa",26},
	{"spani",26},
	{"tecno",27},
	{"comic",28},
	{"daniel",29},
	{"danixi", 29},
	{"game",30},
	{"please",31},
	{"play",32},
	{"song", 33},
	{"listen", 33},
	{"hummi", 33},
	{"sing",33},
	{"guille",34},
	{"inter",35},
	{"trave",36},
	{"enter",37},
	{"code",38},
	{"centr",39},
	{"headq", 39},
	{"hq",39},
	{"zeur", 40},
	{"zhl", 40},
	{"earth",41},
	{"wareh",42},
	{"storm",43},
	{"conso",44},
	{"remem", 45},
	{"memory", 45},
	{"relax", 46},
	{"rest", 46},
	{"holyd", 46},
	{"mars", 47},
	{"venus", 48},
	{"satur", 48},
	{"pluto", 48},
	{"neptu", 48},
	{"mercu", 48},
	{"mines", 50},
	{"fork", 51},
	{"ddevil", 51},
	{"iron", 52},
	{"nickel", 52},
	{"sindi", 53},
	{"human", 54},
	{"opera", 55},
	{"leisu", 56},
	{"parcel", 57},
	{"sumin", 58},
	{"paquet", 59},
	{"pickup", 60},
	{"ship", 61},
	{"space",61},
	{"deliv", 62},
	{"sun", 63},
	{"solar", 64},
	{"systm", 65},
	{"help", 66},
	{"messa", 67},
	{"email", 67},
	{"item", 67},
	{"deliv", 67},
	{"order", 70},
	{"code", 70},
	{"pass", 70},
	{"passk", 70},
	{"key", 70},
	{"passw", 70},
	{"radia", 71},
	{"hatch", 72},
	{"button", 72},
	{"airlo", 72},
	{"commu", 68},
	{"eva", 73},
	{"suit", 74},
	{"super", 75},
	{"prote", 76},
	{"acron", 77},
	{"shit", 78},
	{"ass", 78},
	{"asssh", 78},
	{"bitch", 78},
	{"fuck", 78},
	{"shutup", 79},
	{"cargo", 80},
	{"froze", 81},
	{"fridge", 81},
	{"freez", 81},
	{"",0}
};
#endif 

// Topic and mensaje linked by ID 
// N:1 relationship
#ifdef SPANISH 
token_t mensajes_ordenador_t[]= 
{
	{"-Hoº,∞oyÖ≥d§“≥Å≈ÃgÓi&£-r®p≤ñÏ†voz¿et#liÍ.",1},
	{"-Haƒ†pr≤ø.",2},
	{"-SoyÖs ™⁄Å≈ÃgÓi&nÅl†≈Ã«",3},
	{"-ErôTo–C≤n≥,Öpi‡øÅl†≈Ã«",4},
	{"-Laùrmó†ômod•“a«Noìb•%†s• u£pœbﬂm†p±†Ó‰d•ßlßl⁄c$£us∑»ÖtπjeÅpœ™cci&n.",5},
	{"-Eƒam›òÖs◊$li™ Jovi∑o«-r®p≤©Ö≥d§“≥.",7},
	{"-Euœp†ôu£s◊$li™ÅJup‚•«EnÑc±†ilum¥“†p≥ J'p‚•Ö®pect#cul¢ôsob•bÛ«P≥ìsgπci†nu®tœòc±g¢®òÑc±†ocul”«",8},
	{"-Euœp†ti§e Ï†c±†·emp≠ ≥ió“†hÓi†J'p‚•.",9},
	{"-Eƒ#áu£√⁄c$n,òÖext•i≥«T§dr#üqÀ∞√irÉ¶ƒaùrmóa«",10},
	{"-Ti§ôqÀ ≠∏g• u£—qÀ™áEuœp†÷ëeg±‡áM±™ßª®Å24h -r®p≤©.",11},
	{"-MiÕ€b≠ ôDOT«Si¬¢p≠fi•®,∂Àdôus±¶s™Õ€b≠ß∫Òbl±Émigo« ",12},
	{"-So÷u£mo©l¢Cyb•d¥e 1997« Mi∂œgπm“≥ ≥ig¥a∫fÀÖDr«Guill•m¢H∑Ål†MegaC≥p(tm)«Meò’+& †c∑t± Ï†c∑ci&nÂ/qui•ôo%rº?",13},
	{"-L†empr®†r®p≤ÚbﬂÅqÀ°' ÷y¢®™m›Év•s∑»áEuœ—.",14},
	{"-Meòc∑t∑úüavóuπsÉv•sÓi≤√®.",17},
	{"-D®c≤ozc¢®e°$rm¥oÂ/™ ≠fi•ôaúsÉv•sÓi≤√®?",18},
	{"-N¢®t#£m√,∂•¢n¢c≠¢qÀ∂Àdûjug± †Ï†mië…Éduc®.",19},
	{"-N¢®t#¿√,∂•¢ôu£po∏ïrt†p±†mi gusø«P≠fi•¢'l†‹cÆ¿#súrga'ÂqÀ¨ur†Ïû12hÅjÀgoÅtiemp¢≠√.",20},
	{"-P•¢bu§oÂ<·¶s†nÏÍÑt•m¥±≤!«Recu•d¢qÀ u‹Å‡üaÎ≥®ÂÏ°a∫UTO¬eÊiz¢Ï†v ‚†√∂œgπm“≥ qÀ°•m¥&°a£⁄∫qÀìƒruy•≤ùd¢u£b‡qÀÅofÔ¥…«P•¢®†ôoŸ†hiƒ≥ia.",21},
	{"-Re√móeÕo°§g¢m#üdaøüsob≠¶ƒ†p•s≤a«Si£dud†•†Ï†móe¿a®Ÿ†p±†®Íp± †miü≠giƒœs.",22},
	{"-U£miƒ•Û,∞eÿumo≠†qÀ •†u£±§qÀ œj¢mÎ∑™«",23},
	{"-U£c¡ebπd¢aÎ≥Åc&mÔ qÀ vivi&¿#sÅ»scióoüa+›«T§%†u£c√‡òÖ©»°∑ìs∏mu≈∫qÀÌ¥√móe¿u&ßpºƒ“¢p≥ $l«Eüu£cl#·∏,ìb•%ûﬂ•ùd†suΩbr†v±iûÃc®.",24},
	{"-U£®cbaìl∞igl¢XVÂgπciû†$l°§emoüd p≤iblôm±avilºsÜ¢'Cu∑»Ü% qu®¢negœ'áfr∑c$s.",25},
	{"-L§guûmu•t…Âhoyád%aù»ÖÏiv•s¢Òbl†™c‹ll∑o.",26},
	{"-L†l§gu†fr∑ÍÅnu®tœüd%….",27},
	{"-Ar™∞ecu§cia∫muy∂opul± †f¥√eål∞igl¢XX«",28},
	{"-E∫r®p≤ÚbﬂÅl†ﬁgaïrp≥◊i≤.",29},
	{ "-Habﬂm›Å¡l¢cu∑»°•m¥ôtu¿ i&n.",30},
	{"-Eüdif%cil¶ﬂgir,úüavóuπsÅ™xö’ volvi•o£≠√móe∂opul±ô†π%zÅl†pœlif•Ói&nÅs ™m…Å≈ÃgÓi&náauøm&vil®,„±∏ü÷≈vô®—ci√®«",31},
	{ "-Te„usc±$ Ï†≠√móe ¥t•®∑™ Ï†Ãz°•m¥®Ñm i&n.",32},
	{"-Da y..«-C€i§z††ó≤±∞¥ìm…i“†f≥tu≈.",33},
	{"-E∫¥g§i•¢r®p≤ÚbﬂÅl†¥t•fazÊum∑aÅ‡üs ™m…Å≈ÃgÓi&nÅl†MegÓ≥p(tm)",34},
	{"-L¢qÀ usûp±aÜÏÔ±™Émigo.",35},
	{"-Pm•¢Ò÷qÀ ≠∏g•Ö—qÀ™,¬Àg¢p≤dr$ÿumb¢†M±™«-™ ≠cu•daÖ≥d§“≥.",36},
	{"-L†ë“†®t#Êa÷fu•a«Eüp›ibﬂ qÀÕec®‚ô√g'£c&digoÅÓc®¢p±†ë±.",37},
	{"-No°§g¢n¥g'£daøòÑ≥d§Ål†cë√ßc•Íìl´&digo.",38},
	{"-L†cë√ÅZHL¶ƒ#òÑLu≈.",39},
	{"-EsÑempr®aÅ≠p±øÅ—qÀt®á24h qÀÕoü—gaÖsu¡d¢yúüpiezûp±†’guiµ≠c≥§»ÖUniv•so.",40},
	{"-L†Ti•r†fÀìvaƒ“aìspu$sÅv±Ûüapoc√ips «De¿€ó¢v†tir∑».",41 },
	{"-Hemoü◊•z“¢c•ÍÅl†ë“a«Debôs√irßl¶xt•i≥Âë±òÖ√⁄c$£÷volv•ÉÖ—qÀ™∂±†qÀ∂Àdût•m¥±Ñm i&n«",42},
	{"-Enùrn¢†150∫C„aj¢c•oòÖext•i≥«Te ≠∏mi§d¢qÀ¬ﬂv®ÖtπjeÅsup•vivi§cia.",43},
	{"-LaÉsoºÅm∑d¢mu®tπÖ®”»Ål†≈Ã y¬›Étœlôm∑u√®«Actu√móe¶ƒ#ìsÓtiv“†p±†ah≥r±ò•g%a«",44},
	{"-Eün≥⁄∫qÀÕ¢≠cu•dômuch¢√Üi§zoÅÏ†m i&n«P•¢‹°e∂≠ocup®Å®¢ah≥a,ìspu$sÅÏûj≥≈d…Å≠ºxùd¢volv•#ßÑn≥m√id“.",45},
	{ "-D®pu$sÅ®™°πbaj¢podr#üp…± u‹üd%…Å≠ºxáM±™.",46},
	{"-Y†Úb®,Öpl∑et†œjo«Bu§o,ßn±∑ja»ìsñqÀÜ§z&Ñt•πf≥⁄ci&n.",47},
	{"-Eüﬁj≥Õ¢s√ir’ìl°e⁄Ål†m i&n«-r®p≤©",48},
	{"-D®pu$sÅl†≠∏gidaìbemoüëeg±Ö—qÀ™òÖt§Ë≥ìl¨iab‡«U≈Ålû⁄y≥ôm¥…ÅHi•r¢÷N%qu¡ì∫S ™m†Sol±.",50},
	{"-Tambi$£’¬eÉo‰ÜoÖt§Ë≥ìl¨iab‡«EüÏ†m¥†gob•≈d†p≥Ös¥diÍöÏifiÍ»Åm¥•%aÅM±™«",51},
	{"-Eüu£ﬁt√ßbuŒ∑™∂•¢muy∂≠cia»«L¢dif%ci∫ôsu°r∑sp≥™,∂uôômuyìns¢y´u®t†baƒ∑™¨¥•¢extπ•‡Ål†◊m&sf•aòÑTi•π«",52},
	{"-Gobi•n∑É¿∑¢dur†‡üp≠ci›Åvó†y¬oüÓu•»sÅsum¥iƒœs«",53},
	{"-S≤°iempoüdif%cil®«L†hum∑id“°uv¢qÀßb∑d≤±ÑTi•πìbid¢†v±iûgu•rûnucﬂ±ôy¨ em¥±’∂≥Ös ™m†sol±«",54},
	{"-Y†Úbôsum¥iƒœs,∂aqÀt•%a,ΩcÛ...",55},
	{"-Aqu% ≈daÅocÛÂÒ÷qÀ°•m¥±Ötπbajo.",56},
	{"-Nu®tœ°πbajoáZHL ôëeg±¬oü—qÀt®á24h.",57},
	{"-SeÊa£abi•öv±iûm¥…áM±™.",58},
	{"-Seg'nÑd®cpci&nì∫m§Úje∞e°π”Åu£—qÀ™Å27cm x 29cm x 30cm qÀ∂®†10Kg«",59},
	{"-Hemoü◊•za»òÑë“aìlßl⁄c$n«Sugi•¢qÀ∞√gûah%Ìu•a,¬ºmôaÑpu•t†÷≠∏j…Ö—qÀ™.",60},
	{"-Voºm›áÏ†≈ÃÅ≠p±øÅtip¢T®º«EsÜpﬂ”móe¶l$cŸÔ†s√voÖmot≥∂r¥cip√.",61},
	{"-L†m#üc•c∑†ôSol.",62},
	{"-EsÑ®t≠ll†pr¥cip√Å®™∞ ™⁄«",63},
	{ "-EsÖs ™m†a∫qÀ∂•t§e‰ÑTi•π«",64},
	{"-To»ü‡üs ™m…á≥d§«Op•am›ámo»ÅbajoÉsumo.",65},
	{"-P±†®¢®øyßqu%,∂±†ayud±™«Algu‹sÜ∑»üqÀ∂Àdôus±∞≤:¿ i&nÂJ'p‚•,Õ€b≠,¿o©‡,¿§Úje...",66},
	{"Te⁄: Env%¢urgóeß∫T§Ë≥ÅM±™«C≤t§i»: Re∏gidaá√⁄c$ná∏≥d§“…áEuœ—«Us±´ºÃ: 32768«Imp≥t∑™: M∑t§• †™mp•◊ur†baj¢c•o«",67},
	{ "-Quiz#Êay†√goòÖm§Újeìlòc±go.",70},
	{"-N¢ôu£pœbﬂ⁄ÉÖtπjeÅsup•viv§cia«Si£$lÑπdiÓi&£ô”£¡ev“†qÀÕ¢vivir%ûm#sÅu£d%a«",71},
	{"-L†®clus†’Ωp•†m∑u√móe«E∫bot&£v•ñci•πÑ®clus†yÖœjoÑab≠« A’g'π™Ålﬂv±ÖtπjeÅsup•viv§ci†pu®ø«",72},
	{"-Debid¢aÑfu•™ πdiÓi&£nu®tπsÜÏiÍci≤ôs&l¢fÏci≤∑òÑ≈Ã«N¢®t±$Étig¢ah%Ìu•a«",68},
	{ "-S≤úü·gºsÅÓtivid“¶xtπ-ÃhÔul±«Eücu∑d¢s√®ám i&£fu•aÅl†≈Ã«",73},
	{"-Loòc≤Ÿ±#sòÑ®clus†l öp±†su uso«Recu•d†n¢s√irÅl†≈Ã∞i£lﬂv±l¢pu®ø.",74},
	{ "-Es†a‰pci&£n¢f≥m†p±™Åmi„…eÅdaøs«-r®p≤©Ö≥d§“≥É¶ﬂg∑cia«",78},
	{"-Y†Úb®,∂±†Ó≥t±∂aºbπåm…ia»úrg…«",77},
	{"-Si£pœbﬂm…Ây†‹°±a≠¢m…«-r®p≤ñu£poc¢»li».",79},
	{"-D≤ñ√⁄c§amoü‡ü—qÀtôp±†su¨iƒbuci&n.",80},
	{ "-T§emoüu£fg≥%fi∏ìdÔ“¢†®™°ipoÅ—qÀt®«-r®p≤©ìspu$sÅu£b≠Ã∞il§cÛ",81},
	{0,0}
};
#endif 

#ifdef ENGLISH
token_t mensajes_ordenador_t[]= 
{
	{"'H¡‡,í àÄ≈vig◊i≤ÜpÎ•,' ≠pliô†ﬁt√lÔ voi‰.",1},
	{"'Seeè∞o≤'",2},
	{"'Ißm Äship'ü≈vig◊Û£sys™m' ",3},
	{"'Y‘ß≠ To–C≤n≥ÂÄs—‰cπft'üdv•' ",4},
	{"'ãƒ≥màmod•a™«It∞h‘ldn'æbe †pœbﬂmÇÓc®üÄwa≠h‘’Áe±âÄpœ™ctiÃ∞u‚'",5},
	{"'Weß≠Ω£ÄJovia£Ú™lli™,' ≠pliôÄçÎ•.",7},
	{"'Euœpeà†Ú™lli™éJup‚•«O£Ä·ñillum¥a™–b÷Jup‚• Äspec”cﬂàg≠◊«Unf≥tu≈™lyΩurßs·gnmóào£Ähid©£·©' ",8},
	{"'EuœpeÊû†·ñ√wayü≥ióËùw±düJup‚•'",9},
	{"'It'üi£†wa≠h‘’,ΩÎ·©«Y‘'l∫ÒÃÇg¢‘æ¥íiüƒ≥m' ",10},
	{"'Y‘ÊaÃÇpÔk up †—ckageΩ£EuœpeßŒìliv•∆tÇM±üwiØi£24h,'∆æ≠pli®.",11},
	{"'M÷≈ﬁàDOT«Ifè∂≠f•,è´a£u’íiü≈ﬁÁh§°√k¥gÇﬁ'  ",12},
	{"'Ißm †1997 Cyb•d¥e¿o©l« M÷≥ig¥√∂œgπmm•ÁûDr«Guill•m¢H∑éMegaC≥p(tm)«He°aughæﬁÇsâ†s≤g,¨oèÁ∑tÇÆ±∆t?'",13},
	{"'TÆÜp∑÷r®p≤·bﬂÌ≥èßŒ¿eÊavâØ Év•s◊Û£i£Euœpe'",14},
	{"'I¬oÃÜm∑dl¥eßdvóur®'",17},
	{"'I¨≤'æk‹wí◊°•m,è¿ea£Ä∏mm∑d¬¥e ≤®?'",18},
	{"'Noæb“,„uæI¨≤'tí¥kè´a£pº÷≤eÁhiﬂ¨v¥g'",19}, 
	{"'Noæb“,„uæ‚'ü†l‚tﬂ∞h≥æf≥¿y°…™«I∂≠f• 'Äl≤g®ænight'ÂwhÔhúƒüab‘æ12hé≠√°iﬁ gaﬁpºy'",20},
	{"'W¡l,íeyÕev•Ì¥ Ædíaæ≤e«I ≠ﬁmb•íaæ≤eéÄauØ≥sÂ†c•”i£UTO,∂ai–†v ‚ÇÄpœgπmm•í◊ò©d∞¢b“lyí◊íeyìƒœye–†whoﬂ„‡ckéoffÔ®«BÎí◊'ü∑oîr∞t≥y'",21},
	{"'I ≠√ly¨≤'æÒÃßny¿o≠¨◊†≤íiüp•s≤«N¢»ubæÆÁû†⁄ƒ•m¥dÇ®Ípe¿÷≠c≥ds'",22},
	{"'A¿yƒ•y,ÿum≥ÊûiæÆÁû†mÎ∑æ≠–h•r¥g' ",23},
	{"'A´¡ebπ™dÜÔßuØ≥Áh¢liÃdÇbeΩv•°w¢huŒ≠–ye±üold«HeÊa–†c√luüo£hiüf¥g•∞¢gig∑tÔíaæÆÁûevóu√ly´rusÆdÇ©aØ„y∆t«Heà†cult´ºs·c,è∞h‘l–≠“ßl∫hiüw≥k∞ev•√°im®'",24},
	{"'AÌif™óh´óury∞cbe,í∑ksÇhimÁeÊaÃ∞uchÁ≤d•üû'WÆ£Iß™„ºck´Æ®e'ßvaiºbﬂ∆£Fr§ch'",25},
	{"'De“úÈuag®,Õow“ayüÄwhoﬂ Ïiv•’∞peaküTech‹l¥gu√.",26}, 
	{"'ãl¥gu†fr∑Íé‘r¨ays'",27},
	{"'Sequói√ßrtÂv•y∂opul±ßæÄ§déÄ20Ø´óury'",28},
	{"'ã⁄£r®p≤·bﬂÌ≥ Äﬁgaïrp≥◊i≤'",29},
	{"'Let'üt√kßb‘æiæwh§èÌ¥ hèµm ·≤'",30},
	{"'It'üh±dÇchoo’Âvoi‰ßdvóurôbeÍﬁ ≠√ly∂opul±∆£ÄwakeéÄpœlif•◊i≤é≈vig◊Û£sys™müi£c±s,∞hipü∑d∞—‰cπfts' ",31},
	{"'I'l∫f¥dè †≠√l÷¥t•®tâ≤e ≤‰èÌ¥ h Äm ·≤'",32},
	{"'Da y...,' ÄçÎ•∞t±tüs¥gâwiØ‘æmuchÌ≥tÏe.",33},
	{"'ã§g¥e•ÿ®p≤·bﬂÌ≥ Ähu⁄£¥t•fa‰éÄMegÓ≥p(tm)'ü≈vig◊Û£sys™ms'",34}, 
	{"'Wh◊è u’Ç∏mmÏiÍ™ÁiØ¿e'",35},
	{"'FirsæweÊaÃÇpÔk up Ä—ckage,íe£I'll∞etïur’Ì≥ M±sÂ' ÄçÎ• ≠m¥dsè.",36},
	{"'ãë∑‰à‘t·©«Y‘¿ayÕeË∞€eßcc®sï©Çgeæ¥'",37},
	{"'I¨≤'æÒÃßny¨◊†i£Ä≥d•Ìœm Äcë√∞”tÛ£ab‘æÄ∏©'",38},
	{"'ZHL'üÆ“qu±t•sào£E±Ø'üMo≤'",39},
	{"'It'üÄ24h∂Ókageìliv•yÜp∑yí◊∂ayü‘r∞√±yßŒ Äp±tsÇc≤t¥ÀùurâÄSol±∞ys™m'",40},
	{"'E±ØÁaåvaƒa™dßft•∞ev•√ßpoc√yps®«Nowà»âjusæf¥e.'",41 },
	{"'WeÊaÃún©dÕe± Äë∑‰«Y‘¿usæg¢‘t·©Âó• Äwa≠h‘’ßŒ ≠tur£wiØ Ä—ckage∞oè´a£f¥ h Äm ·≤' ",42},
	{"'Ab‘æ150∞C„¡ow z•¢‘t·©«I ≠∏mm§dèÁe± Äsurviv√∞u‚'",43},
	{"'TÆÜm∑dÉsoﬂ¨ pºyüship∞”tuü∑d¿∑u√Étœls«Itàcurróly¨ abﬂdÇÚÃ∂ow•'",44},
	{"'It'ün≥m√í◊è¨≤'æ≠ﬁmb•¿uchßæÄbeg¥nâof †m ·≤«BÎ¨≤'æw≥ryßb‘tíaæ‹w,ßft• †few¨aysé≠ºx◊Û£ev•yØâwil∫be„ÓkÇn≥m√'",45}, 
	{"'Aft•íiüw≥kèÁil∫beßbﬂÇsp§–†few¨ayü≠ºxâo£M±s'",46},
	{"'Y‘ k‹wÂÄ≠d∂l∑et«W¡lÂ≥∑ge∞¥‰°•πf≥mâbeg∑'",47},
	{"'It'übett•ÕotÇgetΩff ÄsubjectéÄm ·≤«'",48},
	{"'Aft• ÄpÔkupÁe¿uƒìliv• Ä—ckageÇÄ©vil'üf≥k«OneéÄl±g®æIœ£∑–NÔkõm¥ôi£ÄSol± Sys™m'",50},
	{"'Ità√s¢k‹w£ûÄ©vil'üf≥k«Ità†m¥e gov•ne–b÷ÄÏifiË¿¥âsyŒiÍ™éM±s' ",51},
	{"'Itàa£abuŒ∑æbuæv•y∂≠ci‘üﬁt√«Wh◊àdiffÔultà‚üŸ∑sp≥”ti≤Âf≥∆tàv•yìn’ßŒïƒüqui™ †‡tém≤eyÇextπcæiæfœm E±Ø' ",52},
	{"'TÆ÷gov•£wiØ∆œ£f æÄs¡lâprÔô∑–Äsupplyßg≠emós' ",53},
	{"'Th®eß≠Ê±d°im®«M∑k¥–h“ÇﬂaÃ ÄE±Ø¨ÀÇpolÎÛ£∑d∞p≠“íœugh‘æÄsol±∞ys™m' ",54},
	{"'Y‘ k‹w∞uppli®,∂±c¡s,¬e u≠...'",55},
	{"'N¢fÏà√‡wËÂweÊaÃÇf¥ h Äjob'",56},
	{"'OuµjobßæZHL∆sÇ©liv•∂±c¡üwiØi£24h'",57},
	{"'Sev•a∫m¥ôÒÃ„ee£exÍva™dΩ£M±s'",58},
	{"'Acc≥d¥gÇÄm®ÚgeìscptÛ£‚à†27cm x 29cm x 30cm∂ÓkageÁeighâ10Kg'",59},
	{"'WeÊaÃún©dßæÄwa≠h‘’ ë∑‰«I∞ugg®tè g¢‘tí•e,Ωpe£Ä»≥ßŒ∂Ôk up Ä—ckage'",60},
	{"'We'≠Ìlyâi£†T®º-typeìliv•y∞hip«It'ü√l¶ﬂcŸÔ¶x‰pæf≥ Ä⁄¥òg¥e'",61},
	{"'ãne±®æ≤eàÄSÏ'.",62},
	{"'ItàÄ⁄i£ƒ±éØiüsys™m' ",63},
	{"'ItàÄsys™mÇwhÔh ÄE±Ø„¡≤gs' ",64},
	{"'All∞ys™müi£≥d•«WeΩp•a™∆£‡w∂ow•¿o©'",65},
	{"'Th◊'üwh÷I'mÊ•e,ÇÆlpè«S€eÜm∑dsè´a£u’ß≠:¿ ·≤ÂJup‚•Â≈ﬁ,¿o©l,¿®Úge...'",66},
	{"'Subject: Urgó∞hipmóÇM±üF≥k«C≤tó: PÔk up∆£wa≠h‘’ßtï≥d¥◊ôi£Euœpe«U’ key: 32768«Imp≥t∑t: Keepßt∞ubz•o°emp•◊u≠.' ",67},
	{"'Maybeí•e'üs€eØâi£Ä≥d•¿®Úge'",70},
	{"'It'ü‹æ†pœbﬂmÁiØ Äsurviv√∞u‚«WiØ‘æiæÄπdi◊i≤às¢highèÁ‘ldn'æliÃ¿o≠ía£†day' ",71},
	{"'ãair‡ckàop•a™d¿∑u√ly«ãg≠e£bÎø£cl›ôÄair‡ckßŒ Ä≠–bÎø£op§ü‚« Make∞u≠èÊaÃèr∞urviv√∞uiæ≤' ",72},
	{"'DÀÇÄƒr≤g πdi◊Û£‘rÜmÏÔ◊i≤ü≤l÷w≥kΩ£Äship«IÁ≤'æbeÁiØèΩÎí•e' ",68},
	{"'Th◊∞t∑düf≥¶xtπ-ÃhÔul±ßctiv‚y«It'üwh§è g¢o£†m ·o£‘t·ñÄship' ",73},
	{"'Y‘'l∫f¥d∆æi£Äair‡ck ≠“÷f≥ u’«Reﬁmb•ÕotÇﬂaÃ ÄshipÁiØ‘æwe±â‚'",74},
	{"'TÒæﬁ∑¥gà‹t∂±témy¨a”b…e,'ÿ®p≤düÄçÎ• gπ‰fully«",78},
	{"'Y‘ k‹w,Çsh≥™£w≥dsí◊ß≠ù¢l≤g' ",77},
	{"'N¢pœbﬂmÂI¨≤'æhumßnymo≠,'ÿ®p≤dü†l‚tﬂÊurt.",79},
	{"'Wh•eÁe∞ø≠ Ä—ckagôf≥¨iƒbÎi≤'",80},
	{"'WeÊaÃ †≠fg•◊≥ìdiÍ™dÇØiütypeé—ckag®,'ßnsw•üaft• †bef∞il§‰.",81},
	{0,0}
};
#endif 
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

//; SÛlo podemos hablar con el ordenador en la nave
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
		// SÛlo admite una palabra clave
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

	// Si no encaja con ning˙n tema...
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
// Descripciones com˙nes para la nave
if (fverbo==vExaminar)  {
	if (fnombre1==nNave)	
	{
		if (CNDatlt (lExterior)) { ACCmessage (14); return TRUE; }
		if (CNDatlt (lAlmacen)) { ACCmessage(36); return TRUE;}
		// Si estamos dentro del almacÈn no vemos la nave...
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
			#ifdef SPANISH
			if (fnombre1==nBodega) { ACCwriteln ("Al∞ur."); DONE;}
			if (fnombre1==nEsclusa) { ACCwriteln ("A∫o®™."); DONE;}
			#endif 

			#ifdef ENGLISH
			if (fnombre1==nBodega) { ACCwriteln ("At∞‘Ø."); DONE;}
			if (fnombre1==nEsclusa) { ACCwriteln ("Aæw®t."); DONE;}			
			#endif
			
			if (fnombre1==nEscaleras || fnombre1==nPuente) 
			{
				ACCmessage(5);
				DONE;
			}
			#ifdef SPANISH
			if (fnombre1==nLuz) { ACCwriteln ("Pœvi§eìl∂uóeÅm∑»."); DONE; }
			#endif 
			#ifdef ENGLISH
				if (fnombre1==nLuz) { ACCwriteln ("ItÜôfœm Äbdge."); DONE; }
			#endif
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
		#ifdef SPANISH 
		if (fnombre1==nSombra) { writeText ("R®ul”»Ål†pob≠∆lum¥Ói&nòÑ≈Ã«N“aÅl¢qÀ∂≠ocup±’.^ "); DONE; }
		#endif 

		#ifdef ENGLISH 
		if (fnombre1==nSombra) { writeText ("DÀÇpo≥¬ightâi£Äship«NoØ¥gÇw≥ryßb‘t.^ "); DONE; }
		#endif 

	}
	// SinÛnimos...
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
		// Salir con Èxito 
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
// Entrada al almacÈn
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
	// Entrar al almacÈn...
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
			#ifdef SPANISH 
			if (CNDonotzero(oPuerta, aOpen)) writeText ("El°ecºd¢n¢r®p≤©«L†pu•t†y†®t#ßbi•”.^");
			#endif
			#ifdef ENGLISH 
			if (CNDonotzero(oPuerta, aOpen)) writeText ("ãkey—d¨oô‹æw≥k«ãwa≠h‘’'ü»≥à√≠“yΩp§.^");
			#endif			
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
	
	
	if (fverbo==vUsar && fnombre1==nTeclado) 
		{ 
			#ifdef SPANISH
			ACCwriteln ("Debo°ecﬂ±Ñcºvär≠c”òÖ™cº»."); 
			#endif 
			#ifdef ENGLISH
			ACCwriteln ("IÊaÃÇtype Äc≥≠ctïño£Äkeybo±d."); 
			#endif
			DONE; 
		}

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

			// Si ya est· abierta...
			if (CNDpresent(oTeclado) && CNDonotzero(oPuerta, aOpen))
			{
				ACCmessage(184);
				DONE;
			}
			if (fnombre1==n32768 && CNDpresent(oTeclado))
			{
				// No est· abierta...
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
				
				// Ha excedido el n˙mero de intentos
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

// ================= LIBRERÌA BASE FINAL=======================================

}

// ----------------------------------------------------------
// Tabla de respuestas-post
// Se llama despuÈs de ejecutar el proceso de respuestas
// ----------------------------------------------------------

char respuestas_post()
{
 //setRAMPage(0);
 // respuestas_post_pagina0();

// ------------------- LIBRERÕA BASE -----------------------------------
 // Comandos de direcciÛn...
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
		#ifdef SPANISH
            writeText ("Deb•%aïg•¶s¢∑t®.^");
		#endif 
		#ifdef ENGLISH 
		    writeText ("IÊaÃÇ”keíaæfirƒ.^");
		#endif
        else
		#ifdef SPANISH
			writeText ("N¢Ã¢®¢p≥ßqu%.^");
		#endif
		#ifdef ENGLISH 
			writeText ("I¨¢‹t∞eeí◊ßœuŒÊ•e.^");
		#endif
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

    // Si es un nombre/verbo de conexiÛn...
	
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
	
    // Comandos tÌpicos...
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
		#ifdef SPANISH
		ACCwriteln ("N¢nec®‚ûc±g± ¢s√v±á®™ viaje -di‰Ö≥d§“≥");
		#endif 
		#ifdef ENGLISH 
		ACCwriteln ("'Y‘¨≤'æneËÇ‡a–≥∞aÃ ≤íiüŸip,'∞ayüÄçÎ•.");
		#endif 
		DONE;
	}

	if (fverbo==vPuntos) { ACCscore(); DONE; }
	if (fverbo==vTurnos) { ACCturns(); DONE; }
	if (fverbo==vEsperar) { writeSysMessage (35); DONE; }
	if (fverbo==vTocar || fverbo==vOler) { ACCmessage (56); DONE; }
	// Si ninguna acciÛn es v·lida...
    ACCsysmess(SYSMESS_IDONTUNDERSTAND);
    newLine();
}

char proceso1() // Antes de la descripciÛn de la localidad...
{
	
	// Muestra la pantalla..
	#ifdef GRAPHICS
		// Oculta el dibujado
		defineTextWindow (1,1,30,10); 
		clearTextWindow(INK_BLACK | PAPER_BLACK , FALSE);
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
		defineTextWindow (0,0,32,14); 
	#endif 
	// C·lculo de luz
	// En ZHL todas las localidades tienen luz
	flags[flight]=1; // No est· oscuro

}

char proceso1_post() // DespuÈs de la descripciÛn
{
	if (CNDat (lPuente) && !localidades_t[0].visited)
	#ifdef SPANISH
		ACCwriteln ("E∫≥d§“≥Å≈ÃgÓi&n°±a≠†Ï†c∑ci&n.");
	#endif
	#ifdef ENGLISH 
		ACCwriteln ("ã≈vig◊i≤ÜpÎ•Êumü†tÏe.");
	#endif 

 //setRAMPage(0);
 // Usar proceso en otras p·ginas require compilar cÛdigo por separado
 //proceso1_post_pagina0();
}

char proceso2() // DespuÈs de cada turno, haya tenido o no Èxito la entrada en la tabla de respuestas
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
	ACCplace(oCaja, lPuente);	
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
 		defineTextWindow (0,11,32,14); // Pantalla reducida en 128Kb, Gr·ficos + Texto
	#else 
		defineTextWindow (0,0,32,24); // SÛlo Texto
	#endif 

	#ifdef GRAPHICS 
		ACCpicture(9);
	#endif 

// AÒadir men˙ de juego
     clearTextWindow(INK_GREEN | PAPER_BLACK  | BRIGHT, TRUE);
	 gotoxy (13,12);
     writeText (" Z H L ");
     gotoxy (12,14);
	 #ifdef SPANISH
     writeText ("1 Jug±");
	 #endif 
	 #ifdef ENGLISH
	 writeText ("1 St±t");
	 #endif
     //gotoxy (100,80);
     //writeText ("(J) Cargar Partida");
     //gotoxy (100,96);
     //writeText ("1 Tutorial");
     gotoxy (12,15);
	 #ifdef SPANISH
     writeText ("2 Cr$diøs");
	 #endif 
	 #ifdef ENGLISH 
	 writeText ("2 C≠d‚s");
	 #endif
     //fontStyle (NORMAL);

     gotoxy (9,20);
     writeText ("(C) 2019,2021 KMBR ");

while (1) 
{
	switch (getKey())
		{
			//case 'j': // Cargar Partida
			//break;
			case '2': // CrÈditos
				clearTextWindow(INK_YELLOW | PAPER_BLACK, TRUE);
				gotoxy(0,13);
				writeTextln ("Z H L");
				#ifdef SPANISH
				writeTextln ("C≠“†p≥ KMBR");
				writeTextln ("R¡e…e 5 ^");
				writeTextln ("Agπ©cimióoü†aa@zdk.≥g ÷C±‡üS#ncÆz (UTO)");
				writeTextln ("C€pr®i&nÅgr#fi∏sÉ ZX7∂≥ E¥± Sauk…");
				#endif 
				#ifdef ENGLISH
				writeTextln ("Wr‚™£b÷KMBR");
				writeTextln ("R¡e…e 5 ^");
				writeTextln ("Ack‹wﬂdgmósÇaa@zdk.≥gßŒ C±‡üS#ncÆz (UTO)");
				writeTextln ("ZX7 gπphÔÜpr®·o£b÷E¥± Sauk…");
				#endif
				writeTextln ("Rey‹ldüf≤æb÷Dami§G");
				waitForAnyKey();
				main();
				break;
			//case 't': // Jugar en modo Tutorial...
			//     flags[fTutorial]=1;
			case '1': // Jugar...
				clear_screen(INK_YELLOW | PAPER_BLACK, TRUE);
				flags[LOCATION_MAX] = 8; // N˙mero m·s alto de localidad
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
