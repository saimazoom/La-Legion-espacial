/*
 MiniIF para ordenadores de 8bit
 Basado en PAWS y NGPAWS-Beta 9 (Uto/Carlos Sanchez) http://www.ngpaws.com
 (c) 2016. Written by KMBR.
 v0.1

 
 License
-----------------------------------------------------------------------------------
 Released under the the GPL v2 or later license.
-----------------------------------------------------------------------------------


FASTCALL: https://www.z88dk.org/forum/viewtopic.php?id=8848

*/

// Parser structures

// Parser Structures
typedef struct {
        unsigned char id;
        unsigned char page; // Página de RAM
        unsigned char *paddr; // Puntero a la memoria
} img_t;

typedef struct {
		unsigned char *word;
		unsigned char id;
		} token_t;

// Locations table

typedef struct
	{
	unsigned char *name;
	unsigned char *descripcion;
	unsigned char id;
	unsigned char visited;
	unsigned long int atributos; // 32bit
	} loc_t;

typedef struct
	{
	unsigned char id;
	unsigned char con[12];
	} cnx_t;

// Objects table
typedef struct
    {
        unsigned char id;
		unsigned char locid;
		unsigned char *nombre_corto; // Texto que muestra el nombre
		BYTE vnombre; // Nombre de Vocabulario
		BYTE vadj1;   // Adjetivo de Vocabulario
		unsigned char peso;
		unsigned long int atributos; // 32bit
    } obj_t;

// Window properties
// Values are characters for rows and cols *not in píxel*
typedef struct
    {
        BYTE x;
        BYTE y;
        BYTE width;
        BYTE height;
    } textwin_t;


// Funciones declaradas en juego.c ...
extern char  proceso1();
extern char  proceso2();
extern char  proceso1_post();
extern char  proceso2_post();
extern char  respuestas();
extern char  respuestas_post ();

// Main flow
extern  void  initParser ();
extern  void  ParserLoop ();

// Library for parsing strings
void  parse();
BYTE buscador (token_t *tabla, unsigned char *word, unsigned char*result);

// Condacts library
extern BYTE CNDobjfound(BYTE attrno, BYTE locno);
extern BYTE CNDobjnotfound(BYTE attrno, BYTE locno);
extern BYTE __FASTCALL__ CNDcarried(BYTE objno);
extern BYTE __FASTCALL__ CNDpresent(BYTE objno);
extern BYTE __FASTCALL__ CNDabsent(BYTE objno);
extern BYTE __FASTCALL__ CNDworn(BYTE objno);
extern BYTE __FASTCALL__ CNDnotworn(BYTE objno);
extern BYTE CNDozero(BYTE objno, unsigned long int attrno);
extern BYTE CNDonotzero(BYTE objno, unsigned long int attrno);
extern BYTE CNDweight();
extern BYTE CNDisat(BYTE objid, BYTE locid);
extern BYTE CNDisnotat(BYTE objid, BYTE locid);
extern BYTE __FASTCALL__ CNDat(unsigned char locid);
extern BYTE CNDisat(BYTE objid, unsigned char locid);
extern BYTE CNDisnotat(BYTE objid, BYTE locid);
extern BYTE CNDnotat(BYTE locid);
extern BYTE __FASTCALL__ CNDatgt(BYTE locid);
extern BYTE __FASTCALL__ CNDatlt(BYTE locid);
//extern BYTE __FASTCALL__ CNDverb(BYTE verbid);
//extern BYTE __FASTCALL__ CNDnoun1(BYTE nounid);
//extern BYTE __FASTCALL__ CNDnoun2(BYTE nounid);
//extern BYTE __FASTCALL__ CNDadj1(BYTE adjid);
//extern BYTE __FASTCALL__ CNDadj2(BYTE adjid);

extern void  ACCdesc();
extern void  ACCdone();
extern void  ACCbreak();
extern void __FASTCALL__ ACCdestroy(BYTE objno);
extern void __FASTCALL__ ACCcreate(BYTE objno);
extern BYTE __FASTCALL__ ACCget(BYTE objno);
extern BYTE __FASTCALL__ ACCdrop(BYTE objid);
extern BYTE  __FASTCALL__ ACCremove(BYTE objid);
extern BYTE  __FASTCALL__ ACCwear(BYTE objid);
extern void __FASTCALL__ ACCgoto(BYTE locno);
extern void ACCweigh(BYTE objno, BYTE flagno);
extern void ACClistat (BYTE locno, BYTE container_objno);
extern BYTE __FASTCALL__ ACCobjat (BYTE locid);
extern void ACCoset(BYTE objid, unsigned long int attrno);
extern void ACCoclear(BYTE objid, unsigned long int attrno);
extern void ACConeg(BYTE objid, unsigned long int attrno);
extern void ACClistobj();
extern void ACCplace(BYTE objid, BYTE locno);
extern void ACCend();
extern void __FASTCALL__ ACCsysmess(BYTE sysno);
extern void ACCnewline();
extern void ACCcls();
extern BYTE __FASTCALL__ ACCgetReferredObject(BYTE num);
extern void ACCputin(BYTE objid, BYTE obj2id);
extern void ACCtakeout(BYTE objid, BYTE obj2id);
extern void ACCautop();
extern void ACCautot();
extern void ACCautor(); // Auto-remove an object
extern void ACCautow(); // Auto-wear an object
extern void ACCclearexit(BYTE locid, BYTE value);
extern BYTE ACCgetexit(BYTE locid, BYTE value);
extern BYTE ACCsetexit(BYTE loc_orig, BYTE value, BYTE loc_dest);
extern void __FASTCALL__ ACCmessage(BYTE mesid);
extern void __FASTCALL__ ACCmes (BYTE mesid);
extern void __FASTCALL__ ACCwrite (unsigned char *texto);
extern void __FASTCALL__ ACCwriteln (unsigned char *texto);


// Library functions for the parser
void writeValue (unsigned int value);
BYTE  __FASTCALL__ isAccesibleContainer(BYTE objno);
extern BYTE __FASTCALL__ findMatchingObject(BYTE locno);
BYTE __FASTCALL__ trytoGet(BYTE objno);  // auxiliaty function for ACCget
extern void ParserLoop (void);
BYTE __FASTCALL__ getFlag (BYTE flagno);
void __FASTCALL__ setFlag (BYTE flagno, BYTE valor);
void done();
void desc();
BYTE loc_here ();
extern BYTE __FASTCALL__ get_obj_pos (BYTE objid);
BYTE  get_table_pos (token_t *tabla, BYTE noun_id);
BYTE __FASTCALL__ getObjectLocation (BYTE objno);
BYTE __FASTCALL__ getObjectWeight(BYTE objno);
BYTE __FASTCALL__ getLocationObjectsWeight(BYTE locno);
BYTE __FASTCALL__ getObjectCountAt (BYTE locno);
BYTE getObjectCountAtWithAttr(BYTE locno, unsigned long int attrno);
BYTE __FASTCALL__ getNPCCountAt(BYTE locno);
BYTE __FASTCALL__ objectIsSupporter (BYTE objno);
BYTE __FASTCALL__ objectIsContainer (BYTE objno);
BYTE objectIsAttr (BYTE objno, unsigned long int att);
BYTE __FASTCALL__ objectIsNPC(BYTE objno);
extern BYTE __FASTCALL__ get_loc_pos (BYTE locid);
extern BYTE __FASTCALL__ get_img_pos (BYTE imgid);
extern BYTE __FASTCALL__ get_msg_pos (BYTE mesid);

extern void __FASTCALL__ writeText (unsigned char *texto);
extern void __FASTCALL__ writeTextln (unsigned char *texto);

void __FASTCALL__ writeSysMessage (BYTE messno);
void __FASTCALL__ writeMessage (BYTE messno);
void __FASTCALL__ writeObject(BYTE objno);
BYTE setObjectLocation(BYTE objno, BYTE location);
void defineGraphWindow (BYTE x, BYTE y, BYTE width, BYTE height);
extern void defineTextWindow (BYTE x, BYTE y, BYTE width, BYTE height);
extern void clearTextWindow (BYTE color, BYTE clear);
extern void clearTextLine (BYTE x, BYTE y, BYTE color);
void __FASTCALL__ clearGraphWindow (BYTE color);
extern void gotoxy (BYTE x, BYTE y);
void clearchar (BYTE x, BYTE y, BYTE color);
void __FASTCALL__ scrollVTextWindow (BYTE lineas);
extern void __FASTCALL__ CaptionBox (BYTE *texto);
extern void __FASTCALL__ writeTextCenter (BYTE *texto);
extern void __FASTCALL__ fontStyle (BYTE style);
extern void newLine ();
extern void getInput ();
void hideGraphicsWindow();
void debugger ();
void setConnection (BYTE loc_orig, BYTE value, BYTE loc_dest);
BYTE getConnection (BYTE loc_orig, BYTE value);
extern void incr16bit (BYTE *pointer);


