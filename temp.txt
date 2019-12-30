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
extern unsigned char *L05_img;
extern unsigned char *L06_img;
extern unsigned char *L07_img;
extern unsigned char *Europa_img;

#asm
_L01_img:
BINARY "./res/lPuente07.scr.rcs.zx7"
_L05_img:
BINARY "./res/lExterior.scr.rcs.zx7"
_L06_img:
BINARY "./res/lEntrada.scr.rcs.zx7"
_L07_img:
BINARY "./res/lzonaA1.scr.rcs.zx7"
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
    { 7,0, L07_img},   
    { 8,0, L07_img},   
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

// ˙ltima localidad como ID 0 

loc_t localidades_t [] =
{
	{"Puùç¿√π","Lû”¡rumùoÑ ≥œgaÀ&ßilu€≥nÅÏùç¿√d°§Ä≥œ∆EnÅext®i∞,’≥≈∞mùÜ hiµ°süÓatüÛbΩÄsup®fiÀç Eu…ƒ∆",lPuente, FALSE, 0x00000000},
	{"Nod°cèa≠","Lûm&du◊ÑÄ≥œä#nÇp£umb™∆E≠›d°cèæÉ‡«ÉÅÏùç¿√π,Ä•clu“¥≠o•tüyÄbo§ga¥≠sur∆",lNodo, FALSE, 0x00000000},
	{"Esclusa","EnÄ•clu“ªeïcuchaÉ i∂£÷døÄt∞mùa golpe√πÉt™Åfuﬁ´je∆LòsÚbròcΩaßf∞mòs”i•t™sÇlût™jeÑ†xp◊™À„∆",lEsclusa, FALSE, 0x00000000},
	{"Bo§gÜØÆga","La z∏ÜØÆga≈i£eïƒÀ°sufiÀùüpãat£§r¨eq≤+¬îv%ûèeåt·u´r•∆EnÄsÚbròhaÍvÆiûƒq≤tõÖ•p®aßsu èega∆", lBodega, FALSE, 0x00000000},
	{"Exterior","Meîv≤lvüu≥≈∞mùÜ —vüyØ⁄¡æeÑ hiµ°Ömüimpiív®îÄdi¡√Àa∆A≠o•tüsüdi¡”guüŒ†difiÀ°ÖËdr%aª®ÄèøÜ≠æÃc$n.",lExterior, FALSE, 0x00000000},
    {"E∂™‘¥≠æÃc$n","U≥¿olç¿e«≠ﬁîcuèaîc´vøaîÄsup®fiÀühe´dÜ Eu…ƒ∆",lAlmacen, FALSE, 0x00000000},
    {"Zo≥ A1","Lòm∏&–≥säa∂®%òΩpÿ«ÑÉt£ed∞õb´ncûcΩaßu≥¥tm&sf®a imp®Û≥l∆A≠o•tüuß¬cur°pºill°‘¥cc•°a≠o•tü‘¥cc•°a’≥ªaó…ja.",lZonaA1, FALSE, 0x00000000},
    {"Zo≥ A2","El¨ºill°t®€≥Çu≥ªaóÓoœdøa ilu€≥‘Ç…jo∆Lòm∏&–≥säa∂®%òpr¬igu£ªuØurÛÉ¿#sÉt£ed∞õb´ncûp®f‡«mùüoëaπs.",lZonaA2, FALSE, 0x00000000},
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
	{"ZHL^ E∂Ωgamûsu¨aq≤©Ç24h∆^ (c) 2016Á2019 KMBR∆Rµeºü4.",1},
	{"N°œ°≥‘ÇpÆt·u´r.",2},
	{"ZHL bÍKMBR",3},
	{"D•À£d£¥≠›d°cèæ.",4},
	{"AsÀ£d£¥l¨uùç¿√π.",5},
	{"E≠m&dul°pã∫m√dÆÄ≥œ.",6},
	{"La v%a±#c©aÇnu•»°cºo.",7},
	{"LaÉÛlÜ ≥œgaÀ&ß§Ä≥œ∆E¢ußÌ§l°bº«∂ün≤vo,Åoëø∞ íÓ∞d°ﬁîcÆgÜÄ≥œgaÀ&ßy≈odûl¬ôm√dûsüΩæizaßp∞ voz∆EnäüÌmùoÄƒ∂ælÜÄc∏Û´ä#ÇÔg….",8},
	{"-FŒÀo≥m¬ÇÌd°íbajoÉsuÌ∆LaÉÛlÜbüp®m√‡®¥ƒgøa -r•p∏§Åoëø∞.",9},
	{"P…vi£çÄc∏ÛlÜ¿√πs∆LaÉÛ´ä#ÇÌd°íbajoÉsuÌ∆",10},
	{"N—vüÍhiµ°a 150 Cµ÷u¢baj°c®o.",11},
	{"E≠÷s©Ã≈$r€c°ap£òp≤íevitÆÄf∞ÃÀ&ßíc⁄¡æ•îÅext®i∞ §låÓ⁄sº.",12},
	{"Süf∞m√Çlûg™diùõt$r€∫ÑlåÓ⁄“ÑÄ≥œ.",13},
	{"La ≥vç ΩpÆt°d∏íhagoÄru«∆E¢ußÌ§l°”du¡⁄æÉ¡ruiπÉ¿&dul¬ä#‚Æ∆Hﬂüsu≈™baj°y °süav®%Ümºiøòœc•.",14},
	{"-Co∂…´Ä©mp®atu™îÅi∂®i∞ yÇlû”¡rumùûpãevitÆªu §t®i∞°-”f∞ÃÅoëø∞.",15},
	{"E¢Œ°âûdût™jeÑªup®viv£Àa ‡•Æi°pãΩæizÆ EVA∆E≠t™jeïômpÿ«mùüau–m#t·°y≈i£üu≥¥ut∏Ú%ÜŸch°ho™s∆",16},
	{"Paq≤tõa èegÆ¨∞Å÷s©Ãªo´r.",17},
	{"E¡#¥ƒgøa.",18},
	{"N°ÛbΩvivir$ÇEu…ƒª”Åt™jüp…©ct∞.",19},
	{"-PãevitÆÉ«€≥À&ß§jaÅt™jü√©Ñ¨ºÆ¥≠›d°cèa≠-tüΩcu®‘Åoëø∞.",20},
	{"Lêclu“ªirvüpãigua´rÄpr•i&ßèeÅext®i∞ yÅi∂®i∞ §Ä≥œ∆SeÉ»o´ÉÅb&–ß…j°pãc®™∑yÅbot&ßv®ípãÓ⁄r∆",21},
	{"E¡#Ø®™‘.",22},
	{"E¡#¥bi®«.",23},
	{"-Lêclu“ªüÓΩÉ±¬É»olõm√uæõ-”f∞ÃÅoëø∞.",24}, 
	{"-Lêclu“ªüÀ®™É±¬É»olõm√uæõ-”f∞ÃÅoëø∞∆",25},
	{"PulsÆ¨ãÓ⁄rÄ•clu“∆^ADVERTENCIA: ANTES DE ABRIR USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"PulsÆ¨ãc®™rÄ•clu“.",27},
	{"-Lêclu“ yaä#¥bi®«.",28},
	{"-Ab⁄£πômÏ®túxt®i∞ y¥Ê´nπÅi∂®i∞ -d·eÅoëø∞∆LaômÏ®túxt®i∞ªüÓΩÉ’ß÷ﬁ°€èòsüigua´nñ¢pr•i∏•.",29},
	{"-C®™nπômÏ®túxt®i∞- Ωpi©Åoëø∞",30},
	{"U≥ œzÄ∫mÏ®túxt®i∞ªühaØ®™πÁŒûch∞…Ñ¥irüa¨r•i&ßsurg£¶àsåedõpãµim”Æ±¬É«€≥∂õüigua´∑ín≤voÄpr•i„.",30},
	{"Ußp√ìsüÓrüy¨®€©Åﬂc•°a≠i∂®i∞ §Ä≥œ.",31},
	{"-Lêclu“ yaä#Ø®™‘ -Ωp∞«Å∫mÏtø∞ íÓ∞π.",32},
	{"Ap£òŒû€l%È»oÑ¨l#¡·°y¿e«≠tüﬁén¶ìext®i∞.",33},
	{"-Fr%°a≠«c–.",34},
	{"CoÌÇu≥ ochü¬cu™ªæv°p∞Åb⁄l◊ïÕiv°âû»ozoÑ hiµ°Ö•t#ß‰y£π.",35},
	{"La ≥vüÌdu´rä#‚Æ íZHL∆Pi∂øÜ¥mÆill°yÉÅ◊g°§Ä∫mƒ+%aÇg™‚õÿ»ò…jº.",36},
	{"ZHL 24h",37},
	{"C∏¶if·ultø¶i¡”oÅp®fi≠íŒ†difiÀ°íÈtæîÄt∞mùa∆",38},
	{"EßŒñt®a≠§Äèøa b⁄lóuß©c´d°num$⁄∫.",39},
	{"P∞’≥¥b®tu™ªçsliza’ß‰+&ßl#s® ÖtüaÏ∂a: TECLEE EL C&DIGO DE ACCESO∆TIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"Uß‰+&ßíºp‡t°pµigr¬°÷guü€¢Ìvi€ù¬.",41},
	{"Tod°Ûß‰jòb´n‰Ñ≈aÃ+°÷€´r∆Lòm#¢g™‚õﬁîcuè√Çl¬äa∂õm#¢baj¬.",42},
	{"A◊jaß§c£aÑ¨eq≤+¬Ét£ed∞õb´n∫s.",43},
	{"Tod°fŒÀo≥l∆ElïƒÀ°sufiÀùüpãÃ∂£®ñsÉdiÀ∏õn‡•Æiòpãpr•®vÆ¿at®iæõbÒl&gi∫s.",44},
	{"U≥öevøa b&œ‘ f∞ÃÅ©ch°§äaªa´.",45},
	{"Ußƒq≤tüazulÉ’ßg™ß”d·ø∞ ípµigr°bÒl&gi∫îÅf…∂æ∆",46},
	{"-Es©ïÅƒq≤tü-susur™Åoëø∞ÇtuŸ%π.",47},
	{"-N°p≤π,ñ¢diΩctivaÑÄpr•a¿ül°impid£∆",48},
	{"Pµigr°bÒl&gi∫∆C∏s®vÆ¥¿£oÑ 15Øµ÷u¢baj°c®o∆N°m√iÏ´∑÷ßp…©cÀ„∆N°Ó⁄r∆N°golpeÆ∆Mat®ia≠fr#gil.",49},
	// Textos relativos al ordenador
	{"-Co∞d”°–dûlû÷s©ÃÑÄ≥œ∆PãhÓ´rÉ€go†mpÿa:Ÿëø∞¨a´b™Ø´œ∆AlgŒòsug®£ÀaÑ¨a´bròc´vüs∏:Ÿëø∞¥yu‘,Ÿëø∞ ÚbΩ,Ÿëø∞¿i÷„..∆-tür•p∏ís®viÀæÅoëø∞ í≥œgaÀ„.",50},
	{"-OhÁvayaôm°n°p£s$Çÿ®ï°-d·eÅ∫mÏtø∞É fæ“¥d€™À„.",51},
	{" ",52},
	{"N°›t°≥‘ÇpÆt·u´r.",53},
	{"Nøa Ö§¡ﬂÆ.",54},
	{"NoïïpeÀæmùüi∂®•√©.",55},
	{"N°suÂí≥‘ ”•p®aπ.",56},
	{"E≠aullid°dìviù°r•u£aîÅfuﬁ´je.",57},
	{"-Bu£≈™baj°-apr≤baÄvozªatÊf‡hÜ≠oëø∞∆ ",58},
	{"-Ah∞ê¿Úù°íp∏®‹umb°a MÆ©∆Baja¥Äbo§gÜØÆga¿ièòΩ”iÀ°lû÷s©ÃÑÄ≥vü-d·eÅoëø∞É¨Ωmu™∆",59},
	{"D•À£d°l¬ïcæ∏õaÄbo§ga Í§p¬i–Åƒq≤tüju∂°a±oÑm#¢p£diùeÑ èega∆A≠Ωgr•Æ §scub…áÄ“ósühaØ®™π.",60},
	{"-Noï ≥‘¨®Û≥l¨®oï¿Úù°íΩÀc´∑-d·eÄvoz¶ìoëø∞-¿ièòtüfæ´nñ¢pi®nòÍgolpeºÉÄ‰bezaÉt™Ås≤◊.",61}, 
	{"-L°m#¢du…ï≈£® ÖΩÀc´∑su¢p—zºåaÄ÷guiùü€÷„∆LÿgaßaØΩ®sühum√¬∆Eßf”..∆-suspi™Åoëø∞¿ièòΩ∫gülûr•–Ñ≈uØu®ËÉ’≥ …bofΩgo≥.",62},
	{"-Cèæ,¥Õ% Tod C∏n∞ -d·eÄvoz- Volœmûa MÆ©ÉÅƒq≤©∆Repit°volœm¬ÉÅƒq≤©∆",63},
	{"Hay¶ûbot∏•: …j°Ív®§∆Süutilizaßpãc®™∑y¥b⁄rÄ•clu“¥l†xt®i∞∆",172},
	{"Lû÷guiùõƒq≤tõpãèegÆ.",173},
	{"Noï¿Úù°íjugÆ¥≠Sokob√.",174},
	{"-Voo´Ω..∆oohŸooh -tçv≤lvücr≤lÅ‡°§Ä≥œ.",175},
	{"-Ca∂Æe,ŸohŸooh -i∂ùºît∏Æ ^ -Nìblu¶ipi∂°di blu...",176},
	{"S&◊ïcuchoä#t·a∆La≈∞mùa i∂®fi®eÇlò∫mŒ·aÀ∏•.",177},
	{"E¡oyîÄcãocul«, °œ°J'pit®.",178},
	{"Sat$litühe´d°ü”h&spi–.",179}, 
	{"La èøa¥≠æÃc$n∆",180},
	{"FŒÀo≥Éôm√πÑ voz¥≠oëø∞:Ÿëø∞Ø´œ.",181}, 
	{"E¢u≥É¡rucÀ&ßÈt#l·a ÍΩct√gu´∑Ösüi∂®≥ baj°ti®™.",182}, 
	{"(£Å©c´π)",183},
	{"La¨u®tÜ≠æÃc$ßyaä#¥bi®«.",184},
	{"E≠©c´d°süilu€≥Ç…jo∆CODIGO INCORRECTO.",185}, 
	{"E≠©c´d°süilu€≥Çv®§∆CODIGO CORRECTO∆E≠‰+&ßl#s®ªüΩpl—gaÇsuômpÆtimùo.",186}, 
	{"E≠‰+&ßl#s®ô€£za¥ØæùÆﬁ.",187},
	{"E≠‰+&ßl#s®ªüpΩpãa¶Êér∆",188},
	{"E≠‰+&ßl#s®¶Êé∆",189},
	{"P®°≥‘ªuÂ§∆U≥ volutÜ hum°y¥lgŒòchÊpòsurg£¶ì‰+„.",190},
	{"S∏Ét£ed∞eÑ≈™nsp∞©.",191}, 
	{"(∫gi£d°a∂•Åt™je)",192},
	{"-Lû÷s©mòyaä#nÇÌd°íbajoÉsumm°-tüΩcu®‘Åoëø∞.",193},
	{"-S&l°n‡•it°ußƒq≤tüazul∆",194},
	{"Laªup®fiÀeï±i“,ª&l°süﬂtivaÉÅ©c´π.", 195},
	{"E U R O P A",196},
};

token_t mensajesSistema_t [] =
{
	{"N°p≤d°v® ≥‘,ä#¿uÍ¬cu….^",0},
	{"Tambi$ßhaÍ",1},
	{"Esc⁄bütu¢&ëõaÕ%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&Ì? P∞ fav∞¨r≤baÉŸ»òƒ´b™s.^",6},
	{"N°p≤d°irÇ•a¶iΩcÀ„.^",7},
	{"øPerdÛn?^",8},
	{"Lÿv°",9},
	{"(puesto)",10},
	{"n”g'ßobje–.",11},
	{"/Segu…? ",12},
	{"/J≤gaÑ ≤vo? ",13},
	{"AdiÛs...",14},
	{"OK^",15},
	{"[...]",16},
	{"HòΩæizø°",17},
	{"≈ur›",18},
	{"s",19},
	{".^ ",20},
	{"La¨u∂uaÀ„†Ñ ",21},
	{"¨u∂o",22},
	{"N°lÿv°Ï•–ïo.^",23},
	{"N°p≤πÁya±ÿvoï°Ï•–.^",24},
	{"Ya≈£g°",25},
	{"N°œoï°p∞¥Õ%.^",26},
	{"N°p≤d°lÿvÆ¿#sôsº.^",27},
	{"N°t£goïo.^",28},
	{"P®°÷ ya±ÿv°Ï•–",29},
	{"S",30},
	{"N",31},
	{"M·s...",32},
	{"> ",33},
	{"",34},
	{"E≠t—mp°pºa...^",35},
	{"Aho™≈£g°",36},
	{"Müp∏g°",37},
	{"MüÕit°",38},
	{"Dej°",39},
	{"N°p≤d°p∏®mü",40},
	{"N°p≤d°ÕitÆmü",41},
	{"<T£g°§mºiøò∫sºÇlòm√¬!",42},
	{"D•g™Àøamùüp•Ümºiaπ.",43},
	{"Meto",44},
	{"Aho™ oä#Ç",45},
	{",",46},
	{" Í",47},
	{".",48},
	{"N°t£g°",49},
	{"N°lÿv°Ï•t°",50},
	{"",51},
	{"Es°›ä#Ç",52},
	{"n”g'ßobje–",53},
	{"F·h®°›î∫∂™π.^",54},
	{"F·h®oôrrup–.^",55},
	{"Err∞ íE/S∆F·h®°n°g™baπ.^",56},
	{"DiΩct∞i°ll£o.^",57},
	{"DÊc°ll£o.",58},
	{"NÚbrç f·h®°n°v#liπ.^",59},
	{"NÚbrç≠f·h®o: ",60},
	{"",61},
	{"/P®d„? P∞ fav∞¨r≤baÉŸ»òƒ´b™s.^",62},
	{"AÕ% ",SYSMESS_NPCLISTSTART},
	{"•t# ",SYSMESS_NPCLISTCONTINUE},
	{"est·n",SYSMESS_NPCLISTCONTINUE_PLURAL},
    {"Dè°haÍ",SYSMESS_INSIDE_YOUCANSEE},
    {"EnÀÃ haÍ",SYSMESS_OVER_YOUCANSEE},
    {"",68},
	{"Noï¥lg°Öp≤‘ ÕitÆÈ.^",69},
	{"P∏g°",SYSMESS_YOUPUTOBJECTON },
    {"Noï¥lg°Öp≤‘ôg®ﬁ.^",SYSMESS_YOUCANNOTTAKE},
	{"Noå‡üÖp≤‘¿ov®ﬁ.^", SYSMESS_CANNOTMOVE},
	{"Lÿvoñ¢m√ûvﬂ%º.^", SYSMESS_CARRYNOTHING},
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
    {oCaja, lZonaA2,"ƒq≤tüazul",     nPaquete, aAzul,   1,0x0000 | aMale | aDeterminado},  
    {oTraje, lEsclusa,"t™jüpr•u⁄zaπ",     nTraje, EMPTY_WORD,   1,0x0000 | aWear| aMale | aDeterminado},  
	{oEsclusa, lEsclusa,"∫mÏ®tÜÄ•clu“", nEsclusa, EMPTY_WORD,   1,0x0000 | aStatic | aFemale | aDeterminado},  
	{oPuerta, lEntrada,"Ï®tÜ¿etæ",     nPuerta, EMPTY_WORD,   1,0x0000 | aStatic | aFemale},  
	{obotonrojo, lEsclusa,"bot&ß…jo",     nBoton, aRojo,   1,0x0000 | aStatic | aConcealed | aMale},  
	{obotonverde, lEsclusa,"bot&ßv®§",     nBoton, aVerde,   1,0x0000 | aStatic | aConcealed | aMale},  
	{oCanon, NONCREATED,"‰+&ßívigi´nÀa",     nCanon, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
	{oTeclado, NONCREATED,"teclado",     nTeclado, EMPTY_WORD,   1,0x0000 | aStatic | aMale},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x0000}
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
	{"-Ho´,ªoyÅoëø∞ í≥œgaÀ&ß-r•p∏íu≥ voz¿et#l·a.",1},
	{"-Hº«¨…∂o.",2},
	{"-SoyÅ÷s©mÜ ≥œgaÀ&ß§Ä≥œ∆",3},
	{"-ErõTod C∏n∞,Åpi◊t°§Ä≥œ∆",4},
	{"-La≈∞mùê¿o§™‘∆N°§b®%aª®’ßp…bÿÃ¨ãﬂÂ§r¥≠æÃc$ßus√πÅt™jç¨…©cÀ„.",5},
	{"-E¡am¬îÅ“t$litüJovi√o∆-r•p∏§Åoëø∞.",7},
	{"-Eu…pê’ß“t$litç Jupit®∆EnÄcãilu€≥‘¨∞ J'pit®Å•p‡t#cu◊ïªob®bÒ∆P∞ §sg™Àa u•»oîcÆgoïîÄcãocul«∆",8},
	{"-Eu…ƒ≈i£üu≥Øãs—mprü∞iùøa haÀa J'pit®.",9},
	{"-E¡#ÇußæÃc$n,îÅext®i∞∆T£dr#¢ÖsæirÉäa≈∞mùa∆",10},
	{"-Ti£õÖΩ∫g®’ßƒq≤©ÇEu…ƒ ÍèegÆ◊ÇMÆtü√©Ñ 24h -r•p∏§.",11},
	{"-Mi ÚbΩï DOT∆Si±°pΩfi®•,¨≤dõusÆäü›mbrüa≠hÓ´rÉ€go∆ ",12},
	{"-Soy’ßÌ§l°Cyb®d”ü1997∆ Mi¨…g™mø∞ ∞igi≥≠f≤ÅDr∆Guill®m°Haß§ÄMegaC∞p(tm)∆Meîﬁ+&¥Øa∂Æ’≥Ø√À„Á/Õi®õo%r´?",13},
	{"-Lúmpr•a‹•p∏“blç Öt' Íyoä¬Év®s√πÇEu…ƒ.",14},
	{"-Meî‰∂√ñ¢avùu™sÉv®“Ào≥l•.",17},
	{"-D•c∏oz∫ïüt$rm”oÁ/tüΩfi®õañsÉv®“Ào≥l•?",18},
	{"-Noä#ßmæ,¨®°n°cΩ°Öp≤dòjugÆ¥’≥¿ièºÉduc•.",19},
	{"-Noä#¿æ,¨®oï’ßË∫ôr«¨ã€ gu¡o∆PΩfi®°'ó›chüm#sñrga'ÁÖdu™ Œò12h íj≤g°ít—mp°Ωæ.",20},
	{"-P®°bu£oÁ<÷ïa Œ‰Ät®m”Æ∏!∆R‡u®d°ÖŒ°âûaut∞•,’ß«≠UTO±ühiz°u≥ vi÷«¥l¨…g™mø∞ Öt®m”&≈aßÃ≠Ö§¡ruy®oß–d°ußb◊ÖíofiÀ≥s∆P®oïêŸt™ hi¡∞ia.",21},
	{"-Reæmùün°t£g°m#¢‘tûÛbΩäa¨®Û≥∆S”¶udú™’≥¿ùüÃ•t™¨ã•‰pÆ¥¿i¢Ωgi¡r¬.",22},
	{"-Uß€¡®Ò,ªürum∞ea Ö®a’ßÆ£Ö…j°mut√©∆",23},
	{"-Ußcµeb™d°aut∞ íc&€c Övivi&¿#Ñ¶¬Àùûa+¬∆T£%a’ßcæ◊îÅ§d°«ß§s∫mu≥≠Öfi≥lmùümu⁄&¥p´¡ø°p∞ $l∆E¢ußcl#÷∫Á§b®%òÿ®≈o‘ªuŸb™ vÆiòœc•.",24},
	{"-Unïc⁄bÜ≠÷gl°XVÁg™Àòa $≠t£ûdÊp∏iblõÃ™villò∫m°'Cu√πôm%ás°Ôg…'Çf™nc$s.",25},
	{"-L£guòmu®tºÁhoyÇd%a≈oπÅŒiv®s°hÓó©c›l´›.",26},
	{"-La±£gua f™ncÜ u•»ûd%º.",27},
	{"-Artüﬁcu£Àa≠muy¨oÏ´r¥ fi≥ÿÑ≠÷gl°XX∆",28},
	{"-E≠r•p∏“blçÄÈgaôrË™ti∏.",29},
	{ "-HÓÿÌÑöl°cu√d°t®m”õtu¿i÷„.",30},
	{"-E¢dif%Àlöegir,ñ¢avùu™Ñ ©xt°süvolvi®oßΩæmùüËÏ´rõa ™%z §Äp…lif®aÀ&ßí÷s©ÃÑ ≥œgaÀ„Çau–m&vil•ÁbÆcûÍ≥v•ïƒÀæ•∆",31},
	{ "-TübuscÆ$’≥ Ωæmùüi∂®•a∂üu≥ œz≈®m”•Ä€÷„.",32},
	{"-DaÊy..∆-Co€£za¥ît∏Æªiß§mºiøa f∞tu≥.",33},
	{"-E≠”g£i®°r•p∏“blçÄi∂®faz hum√Ü±û÷s©ÃÑ ≥œgaÀ&ß§ÄMegﬂ∞p(tm)",34},
	{"-L°Öusòpã∫mŒ·Æ©É€go.",35},
	{"-P⁄m®°haÍÖΩ∫g®Åƒq≤©,±≤g°p∏dr$‹umb°a MÆ©∆-tüΩcu®‘Åoëø∞.",36},
	{"-La èøaä# haÍfu®a∆E¢p¬iblüÖn‡•itõæg'ßc&dig°íﬂc•°pãèÆ.",37},
	{"-N°t£g°n”g'n¶a–îÄoë §Äcèa≠ﬂ®cÜ≠c&digo.",38},
	{"-LaØèa≠íZHLä#îÄTi®™.",39},
	{"-EsÄpr•Ü ΩpÆt°íƒq≤t•Ç24h ÖnûƒgaÅs≤ld°yñ¢p—zòpãﬁgui∑Ωc∞⁄£πÅUniv®Û.",40},
	{"-La Ti®™ fuçvºtøÜsÏ$Ñ vÆiûaËcæip÷s∆Ah∞ê’ßlugÆªævaje,¨µigr¬°ü”∫mŒ·aπ.",41 },
	{"-Hûat®⁄zø°c®cÜÄèøa∆Debõsæir¥l†xt®i∞ÁèÆîÅæÃc$ßÍvolv®ÉÅƒq≤tüpãÖp≤dòt®m”ÆÄ€÷„∆",42},
	{"-Eßt∞n°a 150∫C baj°c®oîÅext®i∞∆TüΩ∫€£d°Ölÿv•Åt™jçªup®vivi£Àa.",43},
	{"-LaÉÛlÜ¿√d°mu•t™Å•tø°§Ä≥vüy±¬É»olõm√uæ•∆Actuæmùeä# §“ctivøa¨ãah∞™rî®g%a∆",44},
	{"-E¢n∞Ã≠Ön°Ωcu®dõmuch°æô€£z°íu≥¿i÷„∆P®°n°tüpΩocupeÑï°aho™Á§sÏ$Ñ Œòj∞≥‘Ñ Ω´x≈od°volv®#¥Än∞mæidø.",45},
	{ "-D•Ï$Ñäüt™baj°Ëdr#¢pºÆ Œûd%aÑ Ω´xÇMÆ©.",46},
	{"-YaªÓ•,Åp´Ô« …jo∆Bu£o,¥≥™njø°§síÖ∫m£z&Ät®™f∞ÃÀ„.",47},
	{"-E¢Èj∞ Ön°sæirsç≠©mÜÄ€÷„∆-r•p∏§",48},
	{"-D•Ï$ÑÄΩ∫gidÜbûèegÆÅƒq≤©îÅt£ed∞¶ìdiÓ◊∆UnÜñ¢Ãy∞õ€≥Ñ Hi®r°ÍN%ÕìdìSÊ©Ã So´r.",50},
	{"-Tambi$ßsüÿÉoÂôÌÅt£ed∞¶ìdiÓ◊∆E¢u≥¿i≥ gob®≥‘¨∞Ås”d·at°Œif·ø°ím”®%Ü MÆ©∆",51},
	{"-E¢ußÈ«≠ÓŒ‘∂üp®°muy¨ΩÀaπ∆L°dif%Àlïªu≈™nsp∞©,¨u•ï¿uy¶£s°yØu•« bº«∂üd”®o†xt™®l°§Äatm&sf®aîÄTi®™∆",52},
	{"-Gobi®≥nÉ¿√°du™±ûpΩÀoÑ vùa y±ûﬂu®πÑªum”i¡r¬∆",53},
	{"-Soßt—mpûdif%Àl•∆La hum√idø≈uv°ÖÓ√d∏ÆÄTi®rÜbid°a vÆiògu®rònucÿÆõy¶iﬁm”Æsüp∞Å÷s©Ãªo´r∆",54},
	{"-YaªÓõsum”i¡r¬,¨aq≤t®%a,ŸÀo...",55},
	{"-AÕ% ≥dÜŸÀoÁhaÍÖt®m”ÆÅt™bajo.",56},
	{"-Nu•»°t™bajoÇZHLï èegÆ±ûƒq≤t•Ç24h.",57},
	{"-SühaßÓi®t°vÆiò€≥sÇMÆ©.",58},
	{"-Seg'nÄ§sc⁄pÀ„¶ìm£“jüsüt™tÜ’ßƒq≤tç 27cm x 29cm x 30cm Öp•a 10Kg∆",59},
	{"-Hûat®⁄zaπîÄèøÜ≠æÃc$n∆Sugi®°Ösægòah% fu®a,±´mõaÄÏ®« ÍΩ∫jºÅƒq≤©.",60},
	{"-Vo´m¬Çu≥ ≥vç ΩpÆt°ítip°T•´∆Esômpÿ«mùeö$c»·aªævoÅÌt∞¨r”Àpæ.",61},
	{"-La¿#¢c®c√ê Sol.",62},
	{"-EsÄ•»µópr”Àƒ≠§äü÷s©Ã∆",63},
	{ "-EsÅ÷s©Ã¥≠Öp®t£‡eÄTi®™∆",64},
	{"-Todûlû÷s©mºÇoë∆Op®am¬ÇÌd°íbajoÉsuÌ.",65},
	{"-Pã•oäoy¥Õ%,¨ãayudÆ©∆AlgŒòƒ´bròc´vüÖp≤dõusÆª∏:¿i÷„ÁJ'pit®, ÚbΩ,¿o§◊,¿£“je...",66},
	{"TeÃ: Env%°urgùüa≠T£ed∞ íMÆ©∆Co∂£iπ: Re∫gi‘ÇæÃc$nÇ∫oëøºÇEu…ƒ∆UsÆØ´œ: 32768∆Imp∞t√©: Ma∂£®¥ ©mp®atu™ baj°c®o∆",67},
	{ "-Quiz# haya¥lgoîÅm£“jçlîcÆgo.",70},
	{"-Noï’ßp…bÿÃÉÅt™jçªup®viv£Àa∆Siß$lÄ™diaÀ„ï≈√öevøa Ön°vivir%òm#Ñ Œ¶%a∆",71},
	{"-Lêclu“ªüop®a¿√uæmùe∆E≠bot&ßv®íÀ®™Ä•clu“ yÅ…joÄÓΩ∆ Aﬁg'™tüâÿvÆÅt™jçªup®viv£Àa¨u•–∆",72},
	{"-Debid°aÄfu®tü™diaÀ&ßnu•»ò∫mŒ·aÀ∏õs&l°fŒÀo≥nîÄ≥œ∆NoäÆ$Étig°ah% fu®a∆",68},
	{ "-S∏ñ¢÷g´Ñ¥ctividø†xt™-œh·u´r∆E¢cu√d°sæ•Ç€÷&ßfu®ÜÄ≥œ∆",73},
	{"-Loî∫∂™r#sîÄ•clu“±i¡°pãsu’Û∆R‡u®‘ °sæi∑§Ä≥vü÷ßlÿvÆl°Ï•–.",74},
	{ "-E“¥ÂpÀ&ßn°f∞Ãåtç¿i bºç¶at¬∆-r•p∏§Åoëø∞Éöeg√Àa∆",78},
	{"-YaªÓ•,¨ãﬂ∞tÆ¨a´b™Ñmºiaπñrgº∆",77},
	{"-Sißp…bÿmºÁya °«™Ω°mº∆-r•p∏íußËc°πliπ.",79},
	{"-D∏íæÃc£amûlûƒq≤tõpãsu¶i¡⁄buÀ„.",80},
	{ "-T£ûußf⁄g∞%f·°§d·ø°aäütip°íƒq≤t•∆-r•p∏dçsÏ$Ñ’ßbΩvü÷l£Ào",81},
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

// AÒadir funciones de inyecciÛn de comandos en modo DEBUG

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
			if (fnombre1==nBodega) { ACCwriteln ("A≠sur."); DONE;}
			if (fnombre1==nEsclusa) { ACCwriteln ("A≠o•©."); DONE;}
			if (fnombre1==nEscaleras || fnombre1==nPuente) 
			{
				ACCmessage(5);
				DONE;
			}
			if (fnombre1==nLuz) { ACCwriteln ("P…vi£çl¨uùç¿√π."); DONE; }
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
			writeText ("E≠©c´d°n°r•p∏§∆La¨u®« yaä#¥bi®«.^");
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
				// Ha excedido el n˙mero de intentos
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
            writeText ("Deb®%ò∫g®ï°a∂•.^");
        else
			writeText ("N°v•ï°p∞¥Õ%.^");
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
		ACCwriteln ("N°n‡•itòcÆgÆ °sævÆÇ•tüviajü-d·eÅoëø∞");
		DONE;
	}

	if (fverbo==vPuntos) { ACCscore(); DONE; }
	if (fverbo==vTurnos) { ACCturns(); DONE; }

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
	ACCpicture(flags[flocation]);
	if (CNDat(lZonaA2)) 
	{
		clearTextWindow(INK_BLACK | PAPER_RED | BRIGHT, FALSE);
		defineTextWindow (15,4,3,3); 
		clearTextWindow(INK_BLACK | PAPER_RED | BRIGHT, TRUE);
	}
	defineTextWindow (0,11,32,14); 
	// C·lculo de luz
	// En ZHL todas las localidades tienen luz
	flags[flight]=1; // No est· oscuro

}

char proceso1_post() // DespuÈs de la descripciÛn
{
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
	initParser ();                // Inicializa el parser y la pantalla
 	defineTextWindow (0,11,32,14); // Pantalla reducida en 128Kb, Gr·ficos + Texto

	ACCpicture(9);

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
     writeText ("2 Cr$dit¬");
     //fontStyle (NORMAL);

     gotoxy (9,20);
     writeText ("(C) 2019 KMBR ");
	 
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
				writeTextln ("CΩøa¨∞ KMBR");
				writeTextln ("Rµeºü4 ^");
				writeTextln ("Ag™§À€ùûa¥a@zdk.∞g ÍCÆlûS#nchez (UTO)");
				writeTextln ("CÚpr•i&ßígr#fi∫sÉ ZX7¨∞ E”Æ Saukº");
				waitForAnyKey();
				main();
				break;
			//case 't': // Jugar en modo Tutorial...
			//     flags[fTutorial]=1;
			case '1': // Jugar...
				//clsScreen (0);
				//clsScreen (1);
				clear_screen(INK_YELLOW | PAPER_BLACK, TRUE);
	//			defineTextWindow (0,11,32,14); // Pantalla reducida en 128Kb, Gr·ficos + Texto
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
