
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
extern unsigned char flags[255]; // Flags 60...250 Disponibles para el usuario

// Flags del Juego
#include "juego_flags.h"

// Tabla de imágenes del juego
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

// última localidad como ID 0 
loc_t localidades_t [] =
{
	{"Puš¿Ç¸","E¬i´¨i° £€³Ñ‹# iluØ³d¡d$bilmšŸp°€¹nsol‡¿Ç¸ÆU³®uz²mb±i³Èi+ŸlžÏÂrumšo„Ž¹l°¯#lid¡ØŠ¼—ext¨i°¾ŸïatŸu³È°mš‡ hi¶oÆE¬Ýd¡cŠa¬£€³vŸà—cuŠaòajÇ¸Žt«mŒ–c½¨™a¬surÆ",l_puente, FALSE, 0x00000000},
	{"Nod¡cŠa¬","La ³vŸha¾id¡dià+À‡ f°Ë¿oduªrÆE¬Ýd¡cŠ½ƒåÃpuš¿Ç¸ƒ€¥cluÐ²l xt¨i°²¬o¥©äy€bo£ó²¬surÆU³È¤uŸiluØ³Í&§pÅvi¤Ÿd…s–c½¨a„¬puš¬mÇ¸Æ",l_nodo, FALSE, 0x00000000},
	{"Esclusa","LclusÛs©m‡ i´¨æmbiŒ­r¥i&§Šeext¨i° y€zo³ hïiÃbl€³Ñ.",l_esclusa, FALSE, 0x00000000},
	{"Exterior","E¬Í¶o–Žb°r&§’nÒvŸy¯×Â½e„ hi¶oÆLaÈ°mša¯¼tió€sup¨fiÍe—€zo³ Ácur‡ EuÅÊÆLa ³vŸfÚÃ²­ocžcš%ßÄo„€sup¨fiÍeƒgeªÔÆA¬o¥tŸsŸdiÂÏguŸu³¿ol¿eÃ¬ˆçdr%a¾¨€ŠÀ‡¬½Ëc$n.",l_exterior, FALSE, 0x00000000},
    {"E‘Ô²¬½Ëc$n","U³¿ol¿eÃ¬à—cuŠa—cªvÀa—€sup¨fiÍŸheªd‡ EuÅÊÆ",l_almacen, FALSE, 0x00000000},
    {"Zo³ A1","L¼‹a´¨%™»pÖÃ„ƒt¤ed°bªncžc»a§u³²tm&sf¨aÙpr¥ivaÆU§p¼ill¡ëgr¡a¬o¥tŸÔ²cc¥¡aÙt«¾½‡¬½Ëc$n.",l_zonaA1, FALSE, 0x00000000},
    {"Zo³ A2","E¬½Ëc$§t¨Ø³‚u³¾a”ïoÑdÀa­i´À‡òªn¹ÆAÎ% hay²u§m#sƒt¤ed°p¨fåÃmšŸ°£³¸s‚¥Ã´¨%¼.",l_zonaA2, FALSE, 0x00000000},
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
	{"ZHL \§E´»ómžsu­aqµ©‚24hÆ\§(c) 2016ä2019 KMBRÆR¶e¼Ÿ4."},
	{"N¡Ñ¡³Ô‚p±tîuªr.",2},
	{"ZHLòìKMBR",3},
	{"D¥Í¤£§a¬Ýd¡cŠ½.",4},
	{"AsÍ¤£§a¬puš¿Ç¸.",5},
	{"E¬m&dul¡p¹mÇd±€³Ñ.",6},
	{"La v%a®#c©a‚nu¥Ä¡c¼o.",7},
	{"Laƒsol‡¿Ç¸„€³ÑÆEsŽè£l¡b¼Ã´Ÿnµvo,°£³d° ’ï°d¡à—c±g‡€³ÑóÍ&§yÈodžlÁ˜mÇdžsŸ»½iza§p° vozÆEn‹Ÿèmšo€Ê´½l‡€¹nsoª‹#‚ëgÅ.",8},
	{"-FÉÍo³mÁ‚èdŒòajoƒsuèÆLaƒsol‡bŸp¨mÇå¨²ÊgÀa -r¥pº£°£³d°.",9},
	{"PÅvi¤€¹nsol‡¿Ç¸sÆLaƒsoª‹#‚èdŒòajoƒsuèÆ",10},
	{"NÒvŸìhi¶¡a 150 C¶Ûu¢baj¡c¨o.",11},
	{"E¬Ûs©ËÈ$rØc¡ap¤™pµ’evit±€f°ËÍ&§’c×Â½¥—ext¨i°¦•Ê«b×s¼.",12},
	{"SŸf°mÇ‚lžg«dišt$rØ¹„¬Ê«b×Ð„€³Ñ.",13},
	{"La ³v »p±t¡¸n’»c°r¥€óªxiaÆ",14},
	{"-Co´Åª€©mp¨atu«—i´¨i° y‚lžÏÂrumšžpevit±¾u £t¨i°¡-Ïf°Ë°£³d°.",15},
	{"E¢É¡†ždžt«je„¾up¨viv¤ÍaÌå¥±i¡p»½iz± EVAÆE¬t«je–˜mpÖÃmšŸauÕm#tî¡yÈi¤Ÿu³²utºñ%‡Ùch¡ho«sÆ",16},
	{"Paqµta Šeg±—€Ti¨«.",17},
	{"EÂ#²ÊgÀa.",18},
	{"-N¡sob»vivir$‚EuÅÊ¾Ït«jŸpÅ©ct°.",19},
	{"-Debid¡a€¹´aØ³Í&§£jat«jŸÇ©„­¼±²¬Ýd¡cŠa¬-tŸ»cu¨Ô°£³d°.",20},
	{"LcluÐ¾irvŸpiguaªr€pr¥i&§Šeext¨i° yi´¨i° £€³ÑÆ",21},
	{"EÂ#¯¨«Ô.",22},
	{"EÂ#²bi¨Ã.",23},
	{"-LcluÐ¾Ÿï»ƒ®ÁƒÄolmÇu½e„€¥cluÐ -Ïf°Ë°£³d°.",24}, 
	{"-LcluÐ¾ŸÍ¨«ƒ®ÁƒÄolmÇu½e„€¥cluÐ -Ïf°Ë°£³d°Æ",25},
	{"Puls±­ï×r€¥cluÐÆADVERTENCIA: USAR EL TRAJE DE SUPERVIVENCIA EN ENTORNOS HOSTILES.",26},
	{"Puls±­c¨«r€¥cluÐ.",27},
	{"-LcluÐ ya‹#²bi¨Ã.",28},
	{"-Ab×¤¸˜mpu¨t›xt¨i° y²êªn¸i´¨i° -dié°£³d°ÆLa˜mpu¨t›xt¨i°¾Ÿï»ƒŽÛà¡ØŠ™sŸiguaªn“¢pr¥iº¥.",29},
	{"-C¨«n¸˜mpu¨t›xt¨i°- »pi©°£³d°",30},
	{"U³ Ñz€¹mpu¨t›xt¨i°¾Ÿha¯¨«¸äÉžch°Å„²irŸa­r¥i&§surg¤¦…¢p±edp¶imÏ±®ÁƒÃØ³´Ÿiguaª·’nµvo€pr¥iã.",30},
	{"U§pÇ•sŸïrŸy­¨Ø©Üc¥¡a¬i´¨i° £€³Ñ.",31},
	{"-LcluÐ ya‹#¯¨«Ô -»p°Ã¹mputÀ° ’ï°¸.",32},
	{"Ap¤™ÉžØl%ßÄo„­l#Âî¡y¿eÃ¬tŸàÊ«n¦•ext¨i°.",33},
	{"-Fr%¡a¬ÃcÕ.",34},
	{"ToÃ¬Ácu×dÀ¾½v¡p°b×lÚ–Îiv¡†žÄozo„ hi¶¡ˆ¥t#§æy¤¸.",35},
	{"La ³vŸèduªr‹#â± ’ZHLÆPi´À‡²m±ill¡yƒÚgŒ€¹mÊ+%a‚g«âÖÄ™Åj¼.",36},
	{"ZHL 24h",37},
	{"Cº¦ifîultÀ¦iÂÏgu¥p¨fi¬£ŽedifiÍŒ¿eÃ¬»c°Ã¸ƒt«Í¶oÆ",38},
	{"EnŽªt¨a¬£€ŠÀaŽ©cªd¡num$×c¡iluØ³®eÑmše€Ácu×dÀ.",39},
	{"P°Ó³²b¨tu«¾slizaŽæ+&§l#s¨ ˆtŸapu´a: TECLEE EL C&DIGO DE ACCESOÆTIENE UNA OPORTUNIDAD ANTES DE SER DESINTEGRADO.",40},
	{"U§æ+&§’¼påt¡p¶igrÁ¡ÛguŸtu¢èviØšÁ.",41},
	{"Tod¡so§æj™bªnæ„ ÃË+¡ÛØªrÆL™m#¢g«âà—cuŠÇ‚lÁ‹a´m#¢bajÁ.",42},
	{"AÚja§£c¤a„­eqµ+Áƒt¤ed°bªn¹s.",43},
	{"Tod¡fÉÍo³lÆEl–ÊÍ¡sufiÍšŸpË´¤¨“sƒdiÍºnå¥±i™ppr¥¨v±¿at¨i½bál&gi¹s.",44},
	{"U³ò&ÑÔÌ¡muy²lÃ f°Ë©chŒ‹a¾aª.",45},
	{"U§ÊqµtŸazulƒŽg«§ÏdîÀ° ’p¶igr¡bál&gi¹—fÅ´½Æ",46},
	{"-Es©–ÊqµtŸ-susur«°£³d°‚tuÙ%¸.",47},
	{"-N¡pµ¸,“¢di»ctiva„€ðpr¥a¿Ÿl¡impi£nÆ",48},
	{"P¶igr¡bál&gi¹ÆCºs¨v±²¿¤o„ 100¯¶Ûu¢baj¡c¨oÆN¡mÇipuª·Û§pÅ©cÍãÆN¡ï×rÆN¡golpe±ÆMat¨ia¬fr#gil.",49},
	// Textos relativos al ordenador
	{"-Co°dÏ¡ÕdžlžÛs©Ë„€³ÑÆPhïªrƒØgo mpÖa: °£³d°­aªb«¯ªÑÆAlgÉ™sug¨¤Ía„­aªbr™cªvŸsº: °£³d°²yuÔä°£³d°Ìñb»ä°£³d°¿iÛã..Æ-tŸr¥pº’s¨viÍ½°£³d° ’³ÑóÍã.",50},
	{"-Ohävaya˜m¡n¡p¤s$‚Ö¨–¡-dié¹mputÀ°ƒ f½Ð²dØ«Íã.",51},
	{" ",52},
	{"N¡Ýt¡³Ô‚p±tîuªr.",53},
	{"NÀa ˆ£ÂÜ±.",54},
	{"No––peÍ½mšŸi´¨¥Ç©.",55},
	{"N¡sué’³Ô Ï¥p¨a¸.",56},
	{"E¬aullidŒ¬viš¡sŸÏfilt«­°fuàªje.",57},
	{"-Bu¤È«baj¡-aprµba€voz¾atêfåh‡¬°£³d°Æ ",58},
	{"-Ah°¿ñšŒ­º¨Þumb¡a M±©ÆBaja²€bo£g‡¯±ó¿iŠ™»ÏiÍ¡lžÛs©Ë„€³vŸ-dié°£³d°­»mu«Æ",59},
	{"D¥Í¤d¡lÁ–c½ºa€bo£ó ì£pÁiÕÊqµtŸju´¡a®o„m#¢p¤diše„ ŠeóÆA¬»gr¥± £scubÅ‰€Ð”sŸha¯¨«¸.",60},
	{"-No– ³Ô­¨so³¬p¨o–¿ñšŒ »Ícª·-dié€voz¦•°£³d°-¿iŠ¼Žg™ÏÉÔ€bo£ó y¯a¥‚u§pÅfÉd¡sµ+o.",61}, 
	{"L¡m#¢duÅ–È¤¨ ˆ»Ícª·su¢pÒz™Ê«€ÛguišŸØÛãÆLÖó§a¯»¨sŸhumÇÁÆE§fÏ..Æ-suspi«°£³d°¿iŠ™»¹gŸlžr¥Õ„Èu¯u¨çƒÓ³ Åbof»go³.",62},
	{"-CŠ½,²Î% Tod Cºn° -dié€voz- VolÑmža M±©ƒÊqµ©ÆRepit¡volÑmÁƒÊqµ©Æ",63},
	{"Hay¦žbotº¥: Åj¡ìv¨£ÆSŸutiliza§pc¨«·y²b×r€¥cluÐ²l xt¨i°Æ",172},
	{"Paqµtˆ¥p¨a§su Šeó.",173},
	{"No–¿ñšŒ jug±²¬SokobÇ.",174},
	{"-Vooª»..ÆoohÙooh -tvµlvŸcrµlåŒ€³Ñ.",175},
	{"-Ca´±e,ÙohÙooh -i´š¼—tº± \§-N•blu¦ipi´¡diòlu...",176},
	{"S&Ú–cucho‹#tiæÆLaÈ°mša i´¨fi¨e‚ªs˜mÉiæÍº¥.",177},
	{"EÂoy—€coculÃ,Ì¡Ñ¡J'pit¨.",178},
	{"Sat$litŸheªd¡ŸÏh&spiÕ.",179}, 
	{"La ŠÀa²¬½Ëc$nÆ",180},
	{"FÉÍo³ƒ˜mÇ¸„ voz²¬°£³d°: °£³d°¯ªÑ.",181}, 
	{"EsŽbÚˆßt#lî¡»cÃnguª·ˆsŸi´¨³òaj¡ti¨«.",182}, 
	{"(¤©cª¸)",183},
	{"La­u¨t‡¬½Ëc$§ya‹#²bi¨Ã.",184},
	{"E¬©cªd¡sŸiluØ³‚ÅjoÆCODIGO INCORRECTO.",185}, 
	{"E¬©cªd¡sŸiluØ³‚v¨£ÆCODIGO CORRECTOÆE¬æ+&§l#s¨¾Ÿ»plÒó‚su˜mp±timšo.",186}, 
	{"E¬æ+&§l#s¨˜Ø¤za²¯½š±à.",187},
	{"E¬æ+&§l#s¨¾Ÿp»pa¦êÊ«rÆ",188},
	{"E¬æ+&§l#s¨¦êÊ«Æ",189},
	{"P¨¡³Ô¾ué£ÆU³ volut‡ hum¡y²lgÉ™chêp™surg¤¦•æ+ã.",190},
	{"Sºƒt¤ed°e„È«nsp°©.",191}, 
	{"(¹gi¤d¡a´¥t«je)",192},
	{"-E´ºc©‰d±%™a¾oªs‚¥tŸlug± Ïh&spit¡-tŸ»cu¨Ô°£³d°.",193},
	{"-Bus¹ŽÊqµtŸazulÆ",194}
};

token_t mensajesSistema_t [] =
{
	{"N¡pµd¡v¨ ³Ô,‹#¿uìÁcuÅ.^",0},
	{"Tambi$§haì",1},
	{"Esc×bŸtu¢&r£naÎ%",2},
	{"",3},
	{"",4},
	{"",5},
	{"/C&è? P° fav°­rµbaƒÙÄ™Êªb«s.^",6},
	{"N¡pµd¡ir‚¥a¦i»cÍã.^",7},
	{"¿Perdón?^",8},
	{"LÖv¡",9},
	{"(puesto)",10},
	{"nÏg'§objeÕ.",11},
	{"/SeguÅ? ",12},
	{"/Jµó„Ìµvo? ",13},
	{"Adiós...",14},
	{"OK^",15},
	{"[...]",16},
	{"H™»½izÀ¡",17},
	{"ÈurÝ",18},
	{"s",19},
	{".^ ",20},
	{"La­u´uaÍã „ ",21},
	{"­u´o",22},
	{"N¡lÖv¡pu¥Õ–o.^",23},
	{"N¡pµ¸äya®Övo–¡pu¥Õ.^",24},
	{"YaÈ¤g¡",25},
	{"N¡Ño–¡p°²Î%.^",26},
	{"N¡pµd¡lÖv±¿#s˜s¼.^",27},
	{"N¡t¤go–o.^",28},
	{"P¨¡Û ya®Öv¡pu¥Õ",29},
	{"S",30},
	{"N",31},
	{"Más...",32},
	{"> ",33},
	{"",34},
	{"E¬tÒmp¡p¼a...^",35},
	{"He˜gid¡",36},
	{"MŸpºg¡",37},
	{"MŸÎit¡",38},
	{"Dej¡",39},
	{"N¡pµd¡pº¨mŸ",40},
	{"N¡pµd¡Îit±mŸ",41},
	{"<T¤gŒm¼iÀ¼˜s¼‚l™mÇÁ!",42},
	{"D¥g«ÍÀamšŸp¥‡m¼ia¸",43},
	{"Met¡",44},
	{"Aho«Ìo‹#‚",45},
	{",",46},
	{" ì",47},
	{".",48},
	{"N¡t¤g¡",49},
	{"N¡lÖv¡pu¥t¡",50},
	{"",51},
	{"Es¡Ý‹#‚",52},
	{"nÏg'§objeÕ",53},
	{"Fîh¨¡Ý—¹‘¸.^",54},
	{"Fîh¨o˜rrupÕ.^",55},
	{"Err° ’E/SÆFîh¨¡n¡g«ba¸.^",56},
	{"Di»ct°i¡ll¤o.^",57},
	{"Dêc¡ll¤o.",58},
	{"Nñbr fîh¨¡n¡v#li¸.^",59},
	{"Nñbr¬fîh¨o: ",60},
	{"",61},
	{"/P¨dã? P° fav°­rµbaƒÙÄ™Êªb«s.^",62},
	{"AÎ% ",63},
	{"¥t# ",64},
	{"están",65},
    {"DŠ¡haì",66},
    {"EnÍË haì",67},
    {"",68},
	{"No–²lg¡ˆpµÔ Îit±ß.^",69},
	{"Pºg¡",70},
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
// último elemento debe ser 0

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
// No existe la limitación de PAWS donde el objeto 1 siemmpre es la fuente de luz 
// La luz en ngpaws se calcula en función del atributo de los objetos presentes en la localidad, puestos y llevados.
// Localidades de sistema: LOCATION_WORN,LOCATION_CARRIED, LOCATION_NONCREATED, LOCATION_HERE, CARRIED, HERE, NONCREATED, WORN

// Atributos con OR: aLight, aWear, aContainer, aNPC, aConcealed, aEdible, aDrinkable, aEnterable, aFemale, aLockable, aLocked, aMale, aNeuter, aOpenable, aOpen, aPluralName, aTransparent, aScenary, aSupporter, aSwitchable, aOn, aStatic, aExamined, aTaken, aDropped, aVisited, aTalked, aWore, aEaten, aPropio, aDeterminado

obj_t objetos_t[]=
{
    // ID, LOC, NOMBRE, NOMBREID, ADJID, PESO, ATRIBUTOS
    {o_Caja, l_zonaA2,"u§ÊqµtŸazul",     n_paquete, aAzul,   1,0x0000 },  
    {o_Traje, l_esclusa,"u§t«jŸpr¥u×za¸",     n_traje, EMPTY_WORD,   1,0x0000 | aWear },  
	{o_Esclusa, l_esclusa,"”¹mpu¨t‡€¥cluÐ",     n_esclusa, EMPTY_WORD,   1,0x0000 | aStatic },  
	{o_Puerta, l_esclusa,"u³­u¨t‡¿et½",     n_puerta, EMPTY_WORD,   1,0x0000 | aStatic},  
	{o_Puerta, l_esclusa,"u§bot&§Åjo",     n_boton, aRojo,   1,0x0000 | aStatic | aConcealed},  
	{o_Puerta, l_esclusa,"u§bot&§v¨£",     n_boton, aVerde,   1,0x0000 | aStatic | aConcealed},  
	{o_Puerta, NONCREATED,"u§æ+&§’vigiªnÍa",     n_canon, EMPTY_WORD,   1,0x0000 | aStatic },  
	{o_Puerta, NONCREATED,"u§©cª¸",     n_teclado, EMPTY_WORD,   1,0x0000 | aStatic},  
    {0,0,"",                EMPTY_WORD,EMPTY_WORD,            0,0x0000}
}; // Tabla de objetos de la aventura


typedef struct {
	BYTE *topic;
	BYTE *respuesta;
} tema_t;

// Tabla de conversación con el ordenador 
tema_t ordenador_t[]= 
{
	{"Hola","-Hoª,¾oy°£³d° ’³ÑóÍ&§-r¥pº’u³ voz¿et#liæ."},
	{"Adios","-H¼Ã­Å´o."},
	{"trabajo","-SoyÛs©m‡ ³ÑóÍ&§£€³ÑÆ"},
	{"yo/piloto/conductor/transportista","-ErTod Cºn°,piÚtŒ€³ÑÆ"},
	{"tormenta/parabrisas", "-LaÈ°mš¿o£«ÔÆNŒb¨%a¾¨ŽpÅbÖË­Üé£r²¬½Ëc$§usÇ¸t«j­Å©cÍã."},
	{"Europa/luna",	"-EÂamÁ—Ðt$litŸJoviÇoÆ-r¥pº£°£³d°."},
	{"Joviano/Jupiter",	"-EuÅpŽÐt$lit Jupit¨ÆEn€ciluØ³Ô­° J'pit¨¥påt#cuÚ–¾ob¨báÆP° £sg«ÍaÌu¥Äo—c±go–—€coculÃÆ"},
	{"cara/lado", "-EuÅÊÈi¤Ÿu³¯sÒmprŸ°išÀa haÍa J'pit¨."},
	{"donde", "-EÂ#‚u§½Ëc$n,—ext¨i°ÆT¤dr#¢ˆs½irƒ‹aÈ°mšaÆ"},
	{"Mision","-T¤ðžˆ»¹g¨ŽÊqµ©‚EuÅÊ ìŠeg±Ú‚M±tŸÇ©„ 24h -r¥pº£."},
	{"nombre",	"-MiÌñb»– TODÆSi®¡p»fi¨¥,­µdus±‹ŸÝmbrŸa¬hïªrƒØgoÆ "},
	{"modelo/ordenador", "-SoyŽè£l¡Cyb¨dÏŸ1997Æ Mi­Åg«mÀ° °igi³¬fµDrÆGuill¨m¡Ha§£€Meó C°ç«tiºÆMe—à+&²¯a´±Ó³¯ÇÍãä/Îi¨o%rª?"},
	{"mega/megacorp/corporacion/ciberdine/cyberdine","-L›mpr¥aÞ¥pºÐbl ˆt' ìyo‹ðÁƒv¨sÇ¸‚EuÅÊ."},
	{"aventuras/conversacionales","-Me—æ´Ç“¢avšu«sƒv¨ÐÍo³l¥."},
	{"if/fi/ficcion/interactiva","-D¥¹Ýz¹–Ÿt$rmÏoä/tŸ»fi¨a“sƒv¨ÐÍo³l¥?"},
	{"graficas","-No‹#§m½,­¨¡n¡c»¡ˆpµd™jug±²Ó³¿iŠ¼ƒduc¥."},
	{"transilvania","-No‹#¿½,­¨o–Žç¹˜rÃ­Ø guÂoÆP»fi¨¡'”ÝchŸm#s“ró'äˆdu« É™12h ’jµgŒÈÒmp¡»½."},
	{"isla",	"-P¨¡bu¤oä<Û–aÌÉæ€t¨mÏ±º!ÆRåu¨d¡ˆÉ¡†žaut°¥,ŽÃ¬UTO®Ÿhiz¡u³ viÛÃ²¬pÅg«mÀ° ˆt¨mÏ& Ã§Ë¬ˆ£Âruy¨o§Õ¸ŽbÚˆ’ofiÍ³sÆP¨o–Ùt« hiÂ°ia."},
	{"uto",	"-Re½mšŸn¡t¤g¡m#¢Ôtžsob»‹a­¨so³ÆSÏ¦ud›«Ó³¿šŸË¥t«­±æp±²¿i¢»giÂrÁ."},
	{"kmbr","-U§ØÂ¨á,¾Ÿrum°ea ˆ¨aŽ±¤ˆÅj¡muÃn©Æ"},
	{"kno",	"-U§c¶eb«d¡aut° ’c&Øc ˆvivi&¿#„¦ÁÍšža+ÁÆT¤%aŽc½Ú—£d¡Ã§£s¹mu³¬ˆfi³lmšŸmu×&²pªÂÀ¡p° $lÆEsŽcl#Û¹ä£b¨%™Ö¨ÈoÔ¾uÙb« v±i™Ñc¥."},
	{"dela/dla","-Un–c×b‡¬Ûgl¡XVäg«Í™a $¬t¤ðždêpºiblË«vilªs˜m¡'CuÇ¸˜m%‰s¡ëgÅ'‚f«nc$s."},
	{"frances/ingles/italiano/aleman",	"-L¤gu™mu¨t¼ähoy‚d%aÈo¸Éiv¨s¡hï”©cÝlªÝ."},
	{"tecnollano/castellano/espanol/mexicano", "-La®¤gua f«nc‡Ìu¥Äžd%¼."},
	{"comic", "-ArtŸàcu¤Ía¬muy­opuªr² fi³Ö„¬Ûgl¡XXÆ"},
	{"daniel/danixi", "-E¬r¥pºÐbl€ßó˜rç«tiº."},
	{"obra", "-HïÖè„œl¡cuÇd¡t¨mÏtu¿iÛã."},
	{"avšu« fav°iÃ", "-E¢dif%Ílœegir,¾Ÿvolvi¨o§»½mšŸçpuªra «%z £€pÅlif¨aÍ&§’Ûs©Ë„ ³ÑóÍã‚auÕm&vil¥äb±cžì³v¥–ÊÍ½¥Æ"},
	{"jug±²všu«", "-TŸbusc±$Ó³ »½mšŸi´¨¥a´Ÿu³ ÑzÈ¨mÏ¥€ØÛã."},
	{"cancion/oir/canta/tararea", "-Daêy..Æ-CoØ¤za²—tº±¾i§£m¼iÀa f°tu³."},
	{"guillermo", "-E¬Ïg¤i¨¡r¥pºÐbl€i´¨faz huË³ †žÛs©Ë„ ³ÑóÍ&§£€Meó˜rç«tiº"},
	{"interfa",	"-L¡ˆus™phïªrƒØgo."},
	{"viajar", "-P×m¨¡haìˆ»¹g¨Êqµ©,®µg¡pºdr$Þumb¡a M±©Æ-tŸ»cu¨Ô°£³d°."},
	{"entrada", "-La ŠÀa‹# haìfu¨aÆE¢pÁiblŸˆnå¥it½g'§c&digŒ²cc¥¡pŠ±."},
	{"codigo", "-N¡t¤g¡nÏg'n¦aÕ—€°£§£€cŠa¬Ü¨c‡¬c&digo."},
	{"central", "-La¯Ša¬’ZEUR‹#—€Ti¨«."},
	{"ZEUR", "-Es€ðpr¥‡ »p±tŒ­aqµt¥‚24h ˆnžÊósµld¡y“¢pÒz™pàgui·»c°×¤¸"},
	{"Tierra", "	•Univ¨so." },
	{"almacen", "-S½vo‚l™zº™pÅ©gid™sŸhaƒv¨ti¸‚ÉƒgÚm¨ÀŒ¿eó-urb¥ÆU§Ûti¡p¶igrÁo,­¨¡ll¤ŒÙp°tÉiÔ£s."},
	{"temperatura", "-Hðžat¨×zÀ¡c¨c‡€ŠÀaÆDebs½ir²l xt¨i°äŠ±—½Ëc$§ìvolv¨ƒÊqµtŸpˆpµd™t¨mÏ±€ØÛãÆ"},
	{"consola", "-E§t°n¡a 150ºCòaj¡c¨o—ext¨i°ÆTŸ»¹Ø¤d¡ˆlÖv¥t«j¾up¨vivi¤Ía."},
	{"-Laƒsol‡¿Çd¡mu¥t«¥tÀŒ€³vŸy®ÁƒÄolmÇu½¥ÆActu½mše‹# £ÐctivÀa­ah°«r—¨g%aÆ", "Ütiv±ƒsoª"},
	{"-E¢ßj°–p¨±²˜mpÖt±€ØÛãÆEÂamÁ‚èdŒòajoƒsuè.", "£Ðctiv±ƒsoª"},
	{"memoria", "-Ya‹# £ÐctivÀaÆ"},
	{ "relax/jornadas/vacaciones","-E¢n°Ë¬ˆn¡»cu¨dmuch¡½˜Ø¤zŒÓ³¿iÛãÆP¨¡n¡tŸp»ocupe„–¡aho«ä£spu$„ É™j°³Ô„ »ªxÈod¡volv¨#²€n°m½idÀ."},
	{"marte","-D¥pu$„‹Ÿt«baj¡çdr#¢p¼± Éžd%a„ »ªx‚M±©."},
	{"venus/saturno/pluton/lunas/urano/neptuno/mercurio","-Ya¾ï¥,pªëÃ ÅjoÆBu¤o,²³«njÀŒs’ˆdá˜Ø¤zo€t¨«f°ËÍã."},
	{"terraformacion","-E¢ßj° ˆn¡s½irs¬©m‡€ØÛãÆ-r¥pº£"},
	{"minas","-HÜŸÉža+Á˜m¤z±º€ext«cÍ&§’mÏ¨½¥,²b×¨o§v±i™mÏ™y˜m¤z±o§lžt«bajo„È¨«f°ËÍã."},
	{"Tenedor","-D¥pu$„€»¹gid‡bðžŠeg±Êqµ©‚E¬T¤ed°ÆU³¦…¢Ëy°Ø³„ Hi¨r¡ìN%Î•d•Sê©Ë Soªr."},
	{"Hierro/Niquel","-Tambi$§sŸÖƒoé˜èT¤ed°¦•diïÚÆE¢u³¿i³ gob¨³Ô­°sÏdiæt¡ÉifîÀŒ¿Ï¨%‡ M±©Æ"},
	{"sindicato","-EsŽßÃ¬ïÉÔ´Ÿp¨¡muy­»Ía¸ÆL¡dif%Íl–¾uÈ«nsp°©,­u¥–¿uì£ns¡y¯u¥Ãò¼Ã´ŸdÏ¨o xt«¨lŒ€atm&sf¨a—€Ti¨«Æ"},
	{"humanidad","-Gobi¨³nƒ¿Ç¡du«®žp»Ío„ vša y®žÜu¨¸„¾umÏiÂrÁÆ"},
	{"operaciones","-SŸh›xt¤did¡p°€óªxiaÆP¨¡lŸt¤$i¢b¼Ã´Ÿapeg¡a¬Ûs©Ë SoªräˆsŸË´i¤e˜ècŠŒÈod¼“¢op¨aÍº¥."},
	{"ocio", "-Ya¾ïsumÏiÂrÁ,­aqµt¨%a,ÙÍo..."},
	{"paqueteria", "-AÎ% ³d‡ÙÍoähaìˆt¨mÏ±t«bajo."},
	{"suministros", "-Nu¥Ä¡t«bajo‚ZEUR– Šeg±®žÊqµt¥‚24h"},
	{"paquete", "-SŸha§ïi¨t¡v±i™Ø³s‚M±©ƒobjetivŒ²ba«t±p»ÍŒ­º¨²lgÉ™Ët¨i™p×m¼—¥ÊÍo."},
	{"recoger/recogida", "-Seg'n€£sc×pÍã¦•m¤ÐjŸsŸt«t‡ŽÊqµt 27cm x 29cm x 30cm ˆp¥a 10KgÆ"},
	{"nave", "-Hðžat¨×za¸—€ŠÀ‡¬½Ëc$nÆSugi¨¡ˆs½g™ah% fu¨a,®ªma€pu¨Ã ì»¹j¼Êqµ©."},
	{"estrellas", "-VoªmÁ‚u³ ³v »p±tŒÈip¡T¥ªÆEs˜mpÖÃmšeœ$cÄiæ,²s% ˆØŠ™t¤ómžu³‹r¶”c¨æ­od»mž»c±g±“¢bat¨%¼."},
	{"Sol", "-La¿#¢c¨cÇ Sol."},
	{"-Es€¥Ä¶”prÏÍÊ¬£‹ŸÛs©ËÆ", "Sê©Ë Soªr"},
	{"sistemas", "-EsÛs©Ë²¬ˆp¨t¤åe€Ti¨«Æ"},
	{"ayuda", "-TodžlžÛs©m¼‚°£nÆOp¨amÁ‚èdŒòajoƒsuè."},
	{"mensaje/comanda/encargo/entrega"	"-P±o‹oy²Î%,­ayud±©ÆAlgÉ™Êªbr™cªvŸˆpµdus±¾º:¿iÛãäJ'pit¨,Ìñb»,¿o£Ú,¿¤Ðje..."},
	{"clave", "TeË: Env%¡urgšŸa¬T¤ed° ’M±©ÆCo´¤i¸: Re¹giÔ‚½Ëc$n‚¹°£³d¼‚EuÅÊÆUs±¯ªÑ: 32768ÆImp°Ãn©: Ma´¤¨² ©mp¨atu«òaj¡c¨oÆ"},
	{"radiacion", "-Quiz# haya²lgo—m¤Ðjl—c±go."},
	{"airlock/esclusa/boton/botones", "-No–ŽpÅbÖËƒt«j¾up¨viv¤ÍaÆSÏœ€«diaÍã– ÃnœevÀa ˆn¡vivir%™m#„Žd%aÆ"},
	{"comunicaciones", "-LcluÐ¾Ÿop¨a¿Çu½mšeÆE¬bot&§v¨’Í¨«€¥cluÐ yÅjo€ï»Æ Aàg'«tŸ†Öv±t«j¾up¨viv¤Ía­u¥ÕÆ"},
	{"eva", "-Debid¡a€fu¨tŸ«diaÍ&§nu¥t«s˜mÉiæÍºs&l¡fÉÍo³n—€³ÑÆNo‹±$ƒtig¡ah% fu¨aÆ"},
	{"traje/superviviencia/proteccion"	"-Sº“¢Ûgª„²ctividÀ xt«-ÑhîuªrÆE¢cuÇd¡s½¥‚ØÛ&§fu¨‡€³ÑÆ"},
	{"mierda/tacos/culo/joder/hija/puta/puton/hijo/comemierda", "-Lo—¹‘r#s—€¥cluÐ®iÂ¡psuÓsoÆRåu¨ÔÌ¡s½i·£€³vŸÛ§lÖv±l¡pu¥Õ."},
	{"siglas", "-EÐ²épÍ&§n¡f°Ë­±t¿iò¼¦atÁÆ-r¥pº£°£³d°ƒœegÇÍaÆ"},
	{"calla", "-Ya¾ï¥,­Ü°t± f«à„m¼ia¸“rg¼Æ"},
	{"bodega", "-Si§pÅbÖm¼äyaÌ¡Ã«»¡m¼Æ-r¥pº£Žçc¡¸li¸."},
	{"temperatura/frigo/congelador/frigorifico/enfriar", "-Dº’½Ëc¤amžlžÊqµtpsu¦iÂ×buÍã."},
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

// Añadir funciones de inyección de comandos en modo DEBUG

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
// Descripciones comúnes para la nave
if (fverb==vAbrir && fnoun1== n_contenedor) 
	{
		ACCmessage(48);
		return TRUE;
	}

if (fverb==vExaminar && fnoun1==n_nave)	
	{
		if (CNDatlt (l_exterior)) { ACCmessage (14); return TRUE; }
		if (CNDatlt (l_almacen)) { ACCmessage(36); return TRUE;}
		// Si estamos dentro del almacén no vemos la nave...
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
// Entrada al almacén
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
// Se llama después de ejecutar con éxito una entrada de la tabla de respuestas
// ----------------------------------------------------------

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
 // Usar proceso en otras páginas require compilar código por separado
 //proceso1_post_pagina0();
}

char proceso2() // Después de cada turno, haya tenido o no la entrada en la tabla de respuestas
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
    ACCgoto(l_puente); // Localidad inicial, en el puente de mando
    flags[LOCATION_MAX] = 8; // Número más alto de localidad
    ACCability(10,20);

	ParserLoop (); // Pone en marcha el bucle principal
}
