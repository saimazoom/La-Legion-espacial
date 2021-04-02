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

loc_t localidades_t [] =
{
	{"Puûé¡√∑","Lù—¬rumûoÑ ≤”gaÃ&ßilu⁄≤nÅÓûé¡√∑∆EnÅext®iØ,’≤ƒØmûÜ hi¥°süabatüsobªÄsup®fiÃé Eu…≈∆",lPuente, FALSE, 0x00000000},
	{"Nod°cëa¨","Lùm&du◊ÑÄ≤”â#nÇp£umb™∆E¨‹d°cëæÉ‡«ÉÅÓûé¡√∑,Ä•clu“∂¨o•tüyÄbo§ga∂¨sur∆",lNodo, FALSE, 0x00000000},
	{"Esclusa","EnÄ•clu“ºeñcuchaÉ iµ£÷døÄtØmûa golpe√∑Ét™Åfuﬂ´je∆LôsÌbrôcªaßfØmôs—i•t™sÇlùt™jeÑ†xp◊™Ã‚∆",lEsclusa, FALSE, 0x00000000},
	{"Bo§gÜ∞Æga","La z∫Ü∞Ægaƒi£eñ≈Ã°sufiÃûüpãat£§r≠eq≥+¿îv%ùëeåt„u´r•∆EnÄsÌbrôhaÍvÆiù≈q≥túÖ•p®aßsu ëega∆", lBodega, FALSE, 0x00000000},
	{"Exterior","Meîv≥lvüu≤ƒØmûÜ œvüy∞€¬æeÑ hi¥°Ömüimpiív®îÄdi¬√Ãa∆A¨o•tüsüdi¬—guüŒ†difiÃ°ÖÈdr%aº®ÄëøÜ¨æÀc$n.",lExterior, FALSE, 0x00000000},
    {"Eµ™‘∂¨æÀc$n","U≤¡olé¡e«¨ﬂîcuëaîc´vøaîÄsup®fiÃühe´dÜ Eu…≈∆",lAlmacen, FALSE, 0x00000000},
    {"Zo≤ A1","Lôm∫&–≤sâaµ®%ôªpŸ«ÑÉt£edØúb´ncùcªaßu≤∂tm&sf®a imp®so≤l∆A¨o•tüuß¿cur°pΩill°‘∂cc•°a’≤ºaó…ja.",lZonaA1, FALSE, 0x00000000},
    {"Zo≤ A2","E¨pΩill°t®⁄≤Çu≤ºaóabo”døa ilu⁄≤‘Ç…jo∆Lôm∫&–≤sâaµ®%ôpr¿igu£ºu∞ursoÉ¡#sÉt£edØúb´ncùp®f‡«mûüoça∑s.",lZonaA2, FALSE, 0x00000000},
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
	{"ZHL^ Eµªgamùsu≠aq≥©Ç24h∆^ (c) 2016Á2019 KMBR∆R¥eΩü4.",1},
	{"N°”°≤‘ÇpÆt„u´r.",2},
	{"ZHL bÍKMBR",3},
	{"D•Ã£d£∂¨‹d°cëæ.",4},
	{"AsÃ£d£∂¨Óûé¡√∑.",5},
	{"E¨m&dul°pãπm√dÆÄ≤”.",6},
	{"La v%a±#c©aÇnu•»°cΩo.",7},
	{"LaÉsolÜ ≤”gaÃ&ß§Ä≤”∆E¢ußÏ§l°bΩ«µün≥vo,ÅoçøØ íabØd°ﬂîcÆgÜÄ≤”gaÃ&ßyƒodùl¿òm√dùsüªæizaßpØ voz∆EnâüÏmûoÄ≈µælÜÄπnso´â#ÇÔg….",8},
	{"-FŒÃo≤m¿ÇÏd°íbajoÉsuÏ∆LaÉsolÜbüp®m√‡®∂≈gøa -r•p∫§ÅoçøØ.",9},
	{"P…vi£éÄπnsolÜ¡√∑s∆LaÉso´â#ÇÏd°íbajoÉsuÏ∆",10},
	{"NœvüÍhi¥°a 150 C¥÷u¢baj°c®o.",11},
	{"E¨÷s©Àƒ$r⁄c°ap£ôp≥íevitÆÄfØÀÃ&ßíc€¬æ•îÅext®iØ §låab€sΩ.",12},
	{"SüfØm√Çlùg™diûút$r⁄πÑlåab€“ÑÄ≤”.",13},
	{"La ≤vé ªpÆt°∑níhagoÄru«∆E¢ußÏ§l°—du¬€æÉ¬rui∑É¡&dul¿â#›Æ∆H·üsuƒ™baj°y °süav®%ÜmΩiøô”c•.",14},
	{"-Coµ…´Ä©mp®atu™îÅiµ®iØ yÇlù—¬rumûùpãevitÆºu §t®iØ°-—fØÀÅoçøØ.",15},
	{"E¢Œ°àùdùt™jeÑºup®viv£Ãa ‡•Æi°pãªæizÆ EVA∆E¨t™jeñòmpŸ«mûüau–m#t„°yƒi£üu≤∂ut∫Ì%Üÿch°ho™s∆",16},
	{"Paq≥túa ëegÆ≠ØÅ÷s©Àºo´r.",17},
	{"E¬#∂≈gøa.",18},
	{"N°sobªvivir$ÇEu…≈º—Åt™jüp…©ctØ.",19},
	{"-PãevitÆÉ«⁄≤Ã&ß§jaÅt™jü√©Ñ≠ΩÆ∂¨‹d°cëa¨-tüªcu®‘ÅoçøØ.",20},
	{"Lañclu“ºirvüpãigua´rÄpr•i&ßëeÅext®iØ yÅiµ®iØ §Ä≤”∆SeÉ»o´ÉÅb&–ß…j°pãc®™∏yÅbot&ßv®ípãab€r∆",21},
	{"E¬#∞®™‘.",22},
	{"E¬#∂bi®«.",23},
	{"-Lañclu“ºüabªÉ±¿É»olúm√uæú-—fØÀÅoçøØ.",24}, 
	{"-Lañclu“ºüÃ®™É±¿É»olúm√uæú-—fØÀÅoçøØ∆",25},
	{"PulsÆ≠ãab€rÄ•clu“∆^ADVERTENCIA: ANTES DE ABRIR USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"PulsÆ≠ãc®™rÄ•clu“.",27},
	{"-Lañclu“ yaâ#∂bi®«.",28},
	{"-Ab€£∑òmÓ®tõxt®iØ y∂Ê´n∑Åiµ®iØ -d„eÅoçøØ∆LaòmÓ®tõxt®iØºüabªÉ’ß÷ﬂ°⁄ëôsüigua´nï¢pr•i∫•.",29},
	{"-C®™n∑òmÓ®tõxt®iØ- ªpi©ÅoçøØ",30},
	{"U≤ ”zÄπmÓ®tõxt®iØºüha∞®™∑ÁŒùchØ…Ñ∂irüa≠r•i&ßsurg£ àΩåedúpã¥im—Æ±¿É«⁄≤µúüigua´∏ín≥voÄpr•i‚.",30},
	{"Ußp√ìsüabrüy≠®⁄©Å·c•°a¨iµ®iØ §Ä≤”.",31},
	{"-Lañclu“ yaâ#∞®™‘ -ªpØ«ÅoçøØ íabØ∑.",32},
	{"Ap£ôŒù⁄l%Î»oÑ≠l#¬„°y¡e«¨tüﬂên¶ìext®iØ.",33},
	{"-Fr%°a¨«c–.",34},
	{"CoÏÇu≤ ochü¿cu™ºæv°pØÅb€l◊ñÕiv°àù»ozoÑ hi¥°Ö•t#ß‰y£∑.",35},
	{"La ≤vüÏdu´râ#›Æ íZHL∆PiµøÜ∂mÆill°yÉÅ◊g°§Äπm≈+%aÇg™›úŸ»ô…jΩ.",36},
	{"ZHL 24h",37},
	{"C∫¶if„ultø¶i¬—oÅp®fi¨íŒ†difiÃ°íÎtæîÄtØmûa∆",38},
	{"EßŒït®a¨§Äëøa b€lóuß©c´d°num$€π.",39},
	{"PØ’≤∂b®tu™ºésliza’ß‰+&ßl#s® ÖtüaÓµa: TECLEE EL C&DIGO DE ACCESO∆TIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"Uß‰+&ßíΩp‡t°p¥igr¿°÷guü⁄¢Ïvi⁄û¿.",41},
	{"Tod°soß‰jôb´n‰ÑƒaÀ+°÷⁄´r∆Lôm#¢g™›úﬂîcuë√Çl¿âaµúm#¢baj¿.",42},
	{"A◊jaß§c£aÑ≠eq≥+¿Ét£edØúb´nπs.",43},
	{"Tod°fŒÃo≤l∆Elñ≈Ã°sufiÃûüpãÀµ£®ïsÉdiÃ∫ún‡•Æiôpãpr•®vÆ¡at®iæúbÒl&giπs.",44},
	{"U≤öevøa b&”‘ fØÀÅ©ch°§âaºa´.",45},
	{"Uß≈q≥tüazulÉ’ßg™ß—d„øØ íp¥igr°bÒl&giπîÅf…µæ∆",46},
	{"-Es©ñÅ≈q≥tü-susur™ÅoçøØÇtuÿ%∑.",47},
	{"-N°p≥∑,ï¢diªctivaÑÄpr•a¡ül°impid£∆",48},
	{"P¥igr°bÒl&giπ∆C∫s®vÆ∂¡£oÑ 15∞¥÷u¢baj°c®o∆N°m√iÓ´∏÷ßp…©cÃ‚∆N°ab€r∆N°golpeÆ∆Mat®ia¨fr#gil.",49},
	// Textos relativos al ordenador
	{"-CoØd—°–dùlù÷s©ÀÑÄ≤”∆Pãhab´rÉ⁄go†mpŸa:ÿçøØòm√∑∆AlgŒôsug®£ÃaÑòm√dùs∫:ÿçøØ∂yu‘,ÿçøØ Ìbª,ÿçøØ¡i÷‚..∆-tür•p∫ís®viÃæÅoçøØ í≤”gaÃ‚.",50},
	{"-OhÁvayaòm°n°p£s$ÇŸ®ñ°-d„eÅoçøØÉ fæ“∂d⁄™Ã‚.",51},
	{" ",52},
	{"N°‹t°≤‘ÇpÆt„u´r.",53},
	{"Nøa Ö§¬·Æ.",54},
	{"NoññpeÃæmûüiµ®•√©.",55},
	{"N°suËí≤‘ —•p®a∑.",56},
	{"E¨aullid°dìviû°r•u£aîÅfuﬂ´je.",57},
	{"-Bu£ƒ™baj°-apr≥baÄvozºatÊf‡hÜ¨oçøØ∆ ",58},
	{"-Aho™ñ¡Ìû°íp∫®ﬁumb°a MÆ©∆Baja∂Äbo§gÜ∞Æga¡iëôª—iÃ°lù÷s©ÀÑÄ≤vü-d„eÅoçøØÉ≠ªmu™∆",59},
	{"D•Ã£d°l¿ñcæ∫úaÄbo§ga Í§p¿i–Å≈q≥tüjuµ°a±oÑm#¢p£diûeÑ ëega∆A¨ªgr•Æ §scub…áÄ“ósüha∞®™∑.",60},
	{"-Noñ ≤‘≠®so≤¨p®oñ¡Ìû°íªÃc´∏-d„eÄvoz¶ìoçøØ-¡iëôtüfæ´nï¢pi®nôÍgolpeΩÉÄ‰bezaÉt™Ås≥◊.",61}, 
	{"-L°m#¢du…ñƒ£® ÖªÃc´∏su¢pœzΩåaÄ÷guiûü⁄÷‚∆LŸgaßa∞ª®sühum√¿∆Eßf—..∆-suspi™ÅoçøØ¡iëôªπgülùr•–Ñƒu∞u®ÈÉ’≤ …bofªgo≤.",62},
	{"-Cëæ,∂Õ% Tod C∫nØ -d„eÄvoz- Vol”mùa MÆ©ÉÅ≈q≥©∆Repit°vol”m¿ÉÅ≈q≥©∆",63},
	{"Hay¶ùbot∫•: …j°Ív®§∆Süutilizaßpãc®™∏y∂b€rÄ•clu“∂l†xt®iØ∆",172},
	{"Lù÷guiûú≈q≥túpãëegÆ.",173},
	{"Noñ¡Ìû°íjugÆ∂¨Sokob√.",174},
	{"-Voo´ª..∆oohÿooh -tév≥lvücr≥lÅ‡°§Ä≤”.",175},
	{"-CaµÆe,ÿohÿooh -iµûΩît∫Æ ^ -Nìblu¶ipiµ°di blu...",176},
	{"S&◊ñcuchoâ#t„a∆LaƒØmûa iµ®fi®eÇ´sòmŒ„aÃ∫•.",177},
	{"E¬oyîÄcãocul«, °”°J'pit®.",178},
	{"Sat$litühe´d°ü—h&spi–.",179}, 
	{"La ëøa∂¨æÀc$n∆",180},
	{"FŒÃo≤Éòm√∑Ñ voz∂¨oçøØ:ÿçøØòm√∑.",181}, 
	{"E¢u≤É¬rucÃ&ßÎt#l„a Íªct√gu´∏Ösüiµ®≤ baj°ti®™.",182}, 
	{"(£Å©c´∑)",183},
	{"La≠u®tÜ¨æÀc$ßyaâ#∂bi®«.",184},
	{"E¨©c´d°süilu⁄≤Ç…jo∆CLAVE INCORRECTA.",185}, 
	{"E¨©c´d°süilu⁄≤Çv®§∆CLAVE CORRECTA∆E¨‰+&ßl#s®ºüªplœgaÇsuòmpÆtimûo.",186}, 
	{"E¨‰+&ßl#s®ò⁄£za∂∞æûÆﬂ.",187},
	{"E¨‰+&ßl#s®ºüpªpãa¶Êêr∆",188},
	{"E¨‰+&ßl#s®¶Êê∆",189},
	{"P®°≤‘ºuË§∆U≤ volutÜ hum°y∂lgŒôchÊpôsurg£¶ì‰+‚.",190},
	{"S∫Ét£edØeÑƒ™nspØ©.",191}, 
	{"(πgi£d°aµ•Åt™je)",192},
	{"-Lù÷s©môyaâ#nÇÏd°íbajoÉsumm°-tüªcu®‘ÅoçøØ.",193},
	{"-S&l°n‡•it°uß≈q≥tüazul∆",194},
	{"Laºup®fiÃeñ±i“,º&l°sü·tivaÉÅ©c´∑.", 195},
	{"E U R O P A",196},
};

token_t mensajesSistema_t [] =
{
	{"N°p≥d°v® ≤‘,â#¡uÍ¿cu….^",0},
	{"Tambi$ßhaÍ",1},
	{"Esc€bütu¢&çúaÕ%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&Ï? PØ favØ≠r≥baÉÿ»ô≈´b™s.^",6},
	{"N°p≥d°irÇ•a¶iªcÃ‚.^",7},
	{"øPerdÛn?^",8},
	{"LŸv°",9},
	{"(puesto)",10},
	{"n—g'ßobje–.",11},
	{"/Segu…? ",12},
	{"/J≥gaÑ ≥vo? ",13},
	{"AdiÛs...",14},
	{"OK^",15},
	{"[...]",16},
	{"Hôªæizø°",17},
	{"ƒur‹",18},
	{"s",19},
	{".^ ",20},
	{"La≠uµuaÃ‚†Ñ ",21},
	{"≠uµo",22},
	{"N°lŸv°Ó•–ño.^",23},
	{"N°p≥∑Áya±Ÿvoñ°Ó•–.^",24},
	{"Yaƒ£g°",25},
	{"N°”oñ°pØ∂Õ%.^",26},
	{"N°p≥d°lŸvÆ¡#sòsΩ.^",27},
	{"N°t£goño.^",28},
	{"P®°÷ ya±Ÿv°Ó•–",29},
	{"S",30},
	{"N",31},
	{"M·s...",32},
	{"> ",33},
	{"",34},
	{"E¨tœmp°pΩa...^",35},
	{"Aho™ƒ£g°",36},
	{"Müp∫g°",37},
	{"MüÕit°",38},
	{"Dej°",39},
	{"N°p≥d°p∫®mü",40},
	{"N°p≥d°ÕitÆmü",41},
	{"<T£g°§mΩiøΩòsΩÇlôm√¿!",42},
	{"D•g™Ãøamûüp•ÜmΩia∑.",43},
	{"Meto",44},
	{"Aho™ oâ#Ç",45},
	{",",46},
	{" Í",47},
	{".",48},
	{"N°t£g°",49},
	{"N°lŸv°Ó•t°",50},
	{"",51},
	{"Es°‹â#Ç",52},
	{"n—g'ßobje–",53},
	{"F„h®°‹îπµ™∑.^",54},
	{"F„h®oòrrup–.^",55},
	{"ErrØ íE/S∆F„h®°n°g™ba∑.^",56},
	{"DiªctØi°ll£o.^",57},
	{"DÊc°ll£o.",58},
	{"NÌbré f„h®°n°v#li∑.^",59},
	{"NÌbré¨f„h®o: ",60},
	{"",61},
	{"/P®d‚? PØ favØ≠r≥baÉÿ»ô≈´b™s.^",62},
	{"AÕ% ",SYSMESS_NPCLISTSTART},
	{"•t# ",SYSMESS_NPCLISTCONTINUE},
	{"est·n",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"Dë°haÍ",SYSMESS_INSIDE_YOUCANSEE},
    {"EnÃÀ haÍ",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"Noñ∂lg°Öp≥‘ ÕitÆÎ.^",69},
	{"P∫g°",SYSMESS_YOUPUTOBJECTON },
    {"Noñ∂lg°Öp≥‘òg®ﬂ.^",SYSMESS_YOUCANNOTTAKE},
	{"Noå‡üÖp≥‘¡ov®ﬂ.^", SYSMESS_CANNOTMOVE},
	{"LŸvoï¢m√ùv·%Ω.^", SYSMESS_CARRYNOTHING},
	{"",0}	
};

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
// No existe la limitaciÛn de PAWS donde el objeto 1 siemmpre es la fuente de luz 
// La luz en ngpaws se calcula en funciÛn del atributo de los objetos presentes en la localidad, puestos y llevados.
// Localidades de sistema: LOCATION_WORN,LOCATION_CARRIED, LOCATION_NONCREATED, LOCATION_HERE, CARRIED, HERE, NONCREATED, WORN

// Atributos con OR: aLight, aWear, aContainer, aNPC, aConcealed, aEdible, aDrinkable, aEnterable, aFemale, aLockable, aLocked, aMale, aNeuter, aOpenable, aOpen, aPluralName, aTransparent, aScenary, aSupporter, aSwitchable, aOn, aStatic, aExamined, aTaken, aDropped, aVisited, aTalked, aWore, aEaten, aPropio, aDeterminado

obj_t objetos_t[]=
{
    // ID, LOC, NOMBRE, NOMBREID, ADJID, PESO, ATRIBUTOS
    {oCaja, lZonaA2,"≈q≥tüazul",     nPaquete, aAzul,   1, aMale_hex | aDeterminado_hex},  
    {oTraje, lEsclusa,"t™jüpr•u€za∑",     nTraje, EMPTY_WORD,   1, aWear_hex| aMale_hex | aDeterminado_hex},  
	{oEsclusa, lEsclusa,"πmÓ®tÜÄ•clu“", nEsclusa, EMPTY_WORD,   1, aStatic_hex | aFemale_hex | aDeterminado_hex},  
	{oPuerta, lEntrada,"Ó®tÜ¡etæ",     nPuerta, EMPTY_WORD,   1, aStatic_hex | aFemale_hex},  
	{obotonrojo, lEsclusa,"bot&ß…jo",     nBoton, aRojo,   1, aStatic_hex | aConcealed_hex | aMale_hex},  
	{obotonverde, lEsclusa,"bot&ßv®§",     nBoton, aVerde,   1, aStatic_hex | aConcealed_hex | aMale_hex},  
	{oCanon, NONCREATED,"‰+&ßívigi´nÃa",     nCanon, EMPTY_WORD,   1, aStatic_hex | aMale_hex},  
	{oTeclado, NONCREATED,"teclado",     nTeclado, EMPTY_WORD,   1, aStatic_hex | aMale_hex},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x00000000}
}; // Tabla de objetos de la aventura

// Para no usar las tablas de nombres y mensajes podemos aÒadir una a medida
// para las conversaciones con PNJs. 

// Tabla de conversaciÛn con el ordenador 
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
	{"-Ho´,ºoyÅoçøØ í≤”gaÃ&ß-r•p∫íu≤ voz¡et#l„a.",1},
	{"-HΩ«≠…µo.",2},
	{"-SoyÅ÷s©mÜ ≤”gaÃ&ß§Ä≤”∆",3},
	{"-ErúTod C∫nØ,Åpi◊t°§Ä≤”∆",4},
	{"-LaƒØmûañ¡o§™‘∆N°§b®%aº®’ßp…bŸÀ≠ã·Ë§r∂¨æÀc$ßus√∑Åt™jé≠…©cÃ‚.",5},
	{"-E¬am¿îÅ“t$litüJovi√o∆-r•p∫§ÅoçøØ.",7},
	{"-Eu…≈ñ’ß“t$lité Jupit®∆EnÄcãilu⁄≤‘≠Ø J'pit®Å•p‡t#cu◊ñºob®bÒ∆PØ §sg™Ãa u•»oîcÆgoñîÄcãocul«∆",8},
	{"-Eu…≈ƒi£üu≤∞ãsœmprüØiûøa haÃa J'pit®.",9},
	{"-E¬#ÇußæÀc$n,îÅext®iØ∆T£dr#¢ÖsæirÉâaƒØmûa∆",10},
	{"-Ti£úÖªπg®’ß≈q≥©ÇEu…≈ ÍëegÆ◊ÇMÆtü√©Ñ 24h -r•p∫§.",11},
	{"-Mi Ìbªñ DOT∆Si±°pªfi®•,≠≥dúusÆâü‹mbrüa¨hab´rÉ⁄go∆ ",12},
	{"-Soy’ßÏ§l°Cyb®d—ü1997∆ Mi≠…g™møØ Øigi≤¨f≥ÅDr∆Guill®m°Haß§ÄMegaCØp(tm)∆Meîﬂ+&∂∞aµÆ’≤∞√Ã‚Á/Õi®úo%r´?",13},
	{"-Lõmpr•aﬁ•p∫“blé Öt' Íyoâ¿Év®s√∑ÇEu…≈.",14},
	{"-Meî‰µ√ï¢avûu™sÉv®“Ão≤l•.",17},
	{"-D•π‹zπñüt$rm—oÁ/tüªfi®úaïsÉv®“Ão≤l•?",18},
	{"-Noâ#ßmæ,≠®°n°cª°Öp≥dôjugÆ∂’≤¡iëΩÉduc•.",19},
	{"-Noâ#¡æ,≠®oñ’ßÈπòr«≠ã⁄ gu¬o∆Pªfi®°'ó‹chüm#sïrga'ÁÖdu™ Œô12h íj≥g°ítœmp°ªæ.",20},
	{"-P®°bu£oÁ<÷ña Œ‰Ät®m—Æ∫!∆R‡u®d°ÖŒ°àùautØ•,’ß«¨UTO±ühiz°u≤ vi÷«∂¨p…g™møØ Öt®m—&ƒaßÀ¨Ö§¬ruy®oß–d°ußb◊ÖíofiÃ≤s∆P®oñañÿt™ hi¬Øia.",21},
	{"-Reæmûün°t£g°m#¢‘tùsobªâa≠®so≤∆S—¶udõ™’≤¡ûüÀ•t™≠ã•‰pÆ∂¡i¢ªgi¬r¿.",22},
	{"-Uß⁄¬®Ò,ºürumØea Ö®a’ßÆ£Ö…j°mut√©∆",23},
	{"-Ußc¥eb™d°autØ íc&⁄c Övivi&¡#Ñ¶¿Ãûùa+¿∆T£%a’ßcæ◊îÅ§d°«ß§sπmu≤¨Öfi≤lmûümu€&∂p´¬ø°pØ $l∆E¢ußcl#÷πÁ§b®%ôŸ®ƒo‘ºuÿb™ vÆiô”c•.",24},
	{"-Unñc€bÜ¨÷gl°XVÁg™Ãôa $¨t£ùdÊp∫iblúÀ™vil´sòm°'Cu√∑òm%ás°Ôg…'Çf™nc$s.",25},
	{"-L£guômu®tΩÁhoyÇd%aƒo∑ÅŒiv®s°habó©c‹l´‹.",26},
	{"-La±£gua f™ncÜ u•»ùd%Ω.",27},
	{"-AÛüﬂcu£Ãa¨muy≠oÓ´r∂ fi≤ŸÑ¨÷gl°XX∆",28},
	{"-E¨r•p∫“bléÄÎgaòrÈ™ti∫.",29},
	{ "-HabŸÏÑöl°cu√d°t®m—útu¡i÷‚.",30},
	{"-E¢dif%Ãlöegir,ï¢avûu™Ñ ©xt°süvolvi®oßªæmûüÈÓ´rúa ™%z §Äp…lif®aÃ&ßí÷s©ÀÑ ≤”gaÃ‚Çau–m&vil•ÁbÆcùÍ≤v•ñ≈Ãæ•∆",31},
	{ "-TübuscÆ$’≤ ªæmûüiµ®•aµüu≤ ”zƒ®m—•Ä⁄÷‚.",32},
	{"-DaÊy..∆-Co⁄£za∂ît∫Æºiß§mΩiøa fØtu≤.",33},
	{"-E¨—g£i®°r•p∫“bléÄiµ®faz hum√Ü±ù÷s©ÀÑ ≤”gaÃ&ß§ÄMeg·Øp(tm)",34},
	{"-L°ÖusôpãπmŒ„Æ©É⁄go.",35},
	{"-P€m®°haÍÖªπg®Å≈q≥©,±≥g°p∫dr$ﬁumb°a MÆ©∆-tüªcu®‘ÅoçøØ.",36},
	{"-La ëøaâ# haÍfu®a∆E¢p¿iblüÖn‡•itúæg'ßc&dig°í·c•°pãëÆ.",37},
	{"-N°t£g°n—g'n¶a–îÄoç §Äcëa¨·®cÜ¨c&digo.",38},
	{"-La∞ëa¨íZHLâ#îÄTi®™.",39},
	{"-EsÄpr•Ü ªpÆt°í≈q≥t•Ç24h Önù≈gaÅs≥ld°yï¢pœzôpãﬂgui∏ªcØ€£∑ÅUniv®so.",40},
	{"-La Ti®™ fuévΩtøÜsÓ$Ñ vÆiùaÈcæip÷s∆Aho™ñ’ßlugÆºævaje,≠¥igr¿°ü—πmŒ„a∑.",41 },
	{"-Hùat®€zø°c®cÜÄëøa∆Debúsæir∂l†xt®iØÁëÆîÅæÀc$ßÍvolv®ÉÅ≈q≥tüpãÖp≥dôt®m—ÆÄ⁄÷‚∆",42},
	{"-EßtØn°a 150∫C baj°c®oîÅext®iØ∆Tüªπ⁄£d°ÖlŸv•Åt™jéºup®vivi£Ãa.",43},
	{"-LaÉsolÜ¡√d°mu•t™Å•tø°§Ä≤vüy±¿É»olúm√uæ•∆Actuæmûeâ# §“ctivøa≠ãahØ™rî®g%a∆",44},
	{"-E¢nØÀ¨Ön°ªcu®dúmuch°æò⁄£z°íu≤¡i÷‚∆P®°n°tüpªocupeÑñ°aho™Á§sÓ$Ñ ŒôjØ≤‘Ñ ª´xƒod°volv®#∂ÄnØmæidø.",45},
	{ "-D•Ó$Ñâüt™baj°Èdr#¢pΩÆ Œùd%aÑ ª´xÇMÆ©.",46},
	{"-Yaºab•,Åp´Ô« …jo∆Bu£o,∂≤™njø°§síÖπm£z&Ät®™fØÀÃ‚.",47},
	{"-E¢ÎjØ Ön°sæirsé¨©mÜÄ⁄÷‚∆-r•p∫§",48},
	{"-D•Ó$ÑÄªπgidÜbùëegÆÅ≈q≥©îÅt£edØ¶ìdiab◊∆UnÜï¢ÀyØú⁄≤Ñ Hi®r°ÍN%ÕìdìSÊ©À So´r.",50},
	{"-Tambi$ßsüŸÉoËòÏÅt£edØ¶ìdiab◊∆E¢u≤¡i≤ gob®≤‘≠ØÅs—d„at°Œif„ø°ím—®%Ü MÆ©∆",51},
	{"-E¢ußÎ«¨abŒ‘µüp®°muy≠ªÃa∑∆L°dif%Ãlñºuƒ™nspØ©,≠u•ñ¡uy¶£s°y∞u•« bΩ«µüd—®o†xt™®l°§Äatm&sf®aîÄTi®™∆",52},
	{"-Gobi®≤nÉ¡√°du™±ùpªÃoÑ vûa y±ù·u®∑Ñºum—i¬r¿∆",53},
	{"-Soßtœmpùdif%Ãl•∆La hum√idøƒuv°Öab√∑nÆÄTi®rÜbid°a vÆiôgu®rônucŸÆúy¶iﬂm—ÆsüpØÅ÷s©Àºo´r∆",54},
	{"-Yaºabúsum—i¬r¿,≠aq≥t®%a,ÿÃo...",55},
	{"-AÕ% ≤dÜÿÃoÁhaÍÖt®m—ÆÅt™bajo.",56},
	{"-Nu•»°t™bajoÇZHLñ ëegÆ±ù≈q≥t•Ç24h.",57},
	{"-Sühaßabi®t°vÆiô⁄≤sÇMÆ©.",58},
	{"-Seg'nÄ§sc€pÃ‚¶ìm£“jüsüt™tÜ’ß≈q≥té 27cm x 29cm x 30cm Öp•a 10Kg∆",59},
	{"-Hùat®€za∑îÄëøÜ¨æÀc$n∆Sugi®°Ösægôah% fu®a,±´múaÄÓ®« ÍªπjΩÅ≈q≥©.",60},
	{"-Vo´m¿Çu≤ ≤vé ªpÆt°ítip°T•´∆EsòmpŸ«mûeö$c»„aºævoÅÏtØ≠r—Ãpæ.",61},
	{"-La¡#¢c®‰≤ñ Sol.",62},
	{"-EsÄ•»¥ópr—Ã≈¨§âü÷s©À∆",63},
	{ "-EsÅ÷s©À∂¨Öp®t£‡eÄTi®™∆",64},
	{"-Todùlù÷s©mΩÇoç∆Op®am¿ÇÏd°íbajoÉsuÏ.",65},
	{"-Pã•oâoy∂Õ%,≠ãayudÆ©∆AlgŒ¿òm√dùÖp≥dúusÆº∫:¡i÷‚ÁJ'pit®, Ìbª,¡o§◊,¡£“je...",66},
	{"TeÀ: Env%°urgûüa¨T£edØ íMÆ©∆Coµ£i∑: Reπgi‘ÇæÀc$nÇπoçøΩÇEu…≈∆UsÆ∞´”: 32768∆ImpØt√©: Maµ£®∂ ©mp®atu™ baj°c®o∆",67},
	{ "-Quiz# haya∂lgoîÅm£“jélîcÆgo.",70},
	{"-Noñ’ßp…bŸÀÉÅt™jéºup®viv£Ãa∆Siß$lÄ™diaÃ‚ñƒ√öevøa Ön°vivir%ôm#Ñ Œ¶%a∆",71},
	{"-Lañclu“ºüop®a¡√uæmûe∆E¨bot&ßv®íÃ®™Ä•clu“ yÅ…joÄabª∆ Aﬂg'™tüàŸvÆÅt™jéºup®viv£Ãa≠u•–∆",72},
	{"-Debid°aÄfu®tü™diaÃ&ßnu•t™sòmŒ„aÃ∫ús&l°fŒÃo≤nîÄ≤”∆NoâÆ$Étig°ah% fu®a∆",68},
	{ "-S∫ï¢÷g´Ñ∂ctividø†xt™-”h„u´r∆E¢cu√d°sæ•Ç⁄÷&ßfu®ÜÄ≤”∆",73},
	{"-Loîπµ™r#sîÄ•clu“±i¬°pãsu’so∆R‡u®‘ °sæi∏§Ä≤vü÷ßlŸvÆl°Ó•–.",74},
	{ "-E“∂ËpÃ&ßn°fØÀåté¡i bΩé¶at¿∆-r•p∫§ÅoçøØÉöeg√Ãa∆",78},
	{"-Yaºab•,≠ã·ØtÆ≠a´b™ÑmΩia∑ïrgΩ∆",77},
	{"-Sißp…bŸmΩÁya °«™ª°mΩ∆-r•p∫íußÈc°∑li∑.",79},
	{"-D∫íæÀc£amùlù≈q≥túpãsu¶i¬€buÃ‚.",80},
	{ "-T£ùußf€gØ%f„°§d„ø°aâütip°í≈q≥t•∆-r•p∫désÓ$Ñ’ßbªvü÷l£Ão",81},
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
			if (fnombre1==nBodega) { ACCwriteln ("A¨sur."); DONE;}
			if (fnombre1==nEsclusa) { ACCwriteln ("A¨o•©."); DONE;}
			if (fnombre1==nEscaleras || fnombre1==nPuente) 
			{
				ACCmessage(5);
				DONE;
			}
			if (fnombre1==nLuz) { ACCwriteln ("P…vi£é¨Óûé¡√∑."); DONE; }
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
		if (fnombre1==nSombra) { writeText ("R•ultø°§ÄÈbrüilu⁄≤Ã‚îÄ≤”∆NøÜ±°ÖpªocupÆﬂ.^ "); DONE; }
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
			if (CNDonotzero(oPuerta, aOpen)) writeText ("E¨©c´d°n°r•p∫§∆La≠u®« yaâ#∂bi®«.^");
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
	
	if (fverbo==vUsar && fnombre1==nTeclado) { ACCwriteln ("Deb°©cŸÆÄc´”òrªc«îÅ©c´∑."); DONE; }

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
            writeText ("Deb®%Ωòg®ñ°aµ•.^");
        else
			writeText ("N°v•ñ°pØ∂Õ%.^");
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
		ACCwriteln ("N°n‡•itôcÆgÆ °sævÆÇ•tüviajü-d„eÅoçøØ");
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
	// C·lculo de luz
	// En ZHL todas las localidades tienen luz
	flags[flight]=1; // No est· oscuro

}

char proceso1_post() // DespuÈs de la descripciÛn
{
	if (CNDat (lPuente) && !localidades_t[0].visited)
		ACCwriteln ("E¨oçøØ í≤”gaÃ‚â#ƒa™ª√d°u≤∞√Ã‚.");

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
     writeText ("1 JugÆ");
     //gotoxy (100,80);
     //writeText ("(J) Cargar Partida");
     //gotoxy (100,96);
     //writeText ("1 Tutorial");
     gotoxy (12,15);
     writeText ("2 Cr$dit¿");
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
				writeTextln ("Cªøa≠Ø KMBR");
				writeTextln ("R¥eΩü5 ^");
				writeTextln ("Ag™§Ã⁄ûùa∂a@zdk.Øg ÍCÆlùS#nchez (UTO)");
				writeTextln ("CÌpr•i&ßígr#fiπsÉ ZX7≠Ø E—Æ SaukΩ");
				writeTextln ("Rey‹ld¢foµ bÍDa⁄£G");
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
