/*
 MiniIF para ordenadores de 8bit
 Basado en PAWS y NGPAWS-Beta 9 (Uto/Carlos Sanchez) http://www.ngpaws.com
 (c) 2016. Written by KMBR.
 v1.0
*/

// CONSTANTS

// AUX
#define NORMAL 0
#define TITLE 1
#define PLAYER 2

#define TRUE 1
#define FALSE 0
#define BYTE unsigned char
#define WORD unsigned int

// Spectrum
#define INK_BLACK      0x00
#define INK_BLUE       0x01
#define INK_RED        0x02
#define INK_MAGENTA    0x03
#define INK_GREEN      0x04
#define INK_CYAN       0x05
#define INK_YELLOW     0x06
#define INK_WHITE      0x07

#define PAPER_BLACK    0x00
#define PAPER_BLUE     0x08
#define PAPER_RED      0x10
#define PAPER_MAGENTA  0x18
#define PAPER_GREEN    0x20
#define PAPER_CYAN     0x28
#define PAPER_YELLOW   0x30
#define PAPER_WHITE    0x38

#define BRIGHT         0x40
#define FLASH          0x80

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

// Tabla de Localidades

typedef struct
	{
	unsigned char *name;
	unsigned char *descripcion;
	unsigned char id;
	unsigned char visited;
	//unsigned char atributos[4]; // 32bit
	} loc_t;

typedef struct
	{
	unsigned char id;
	unsigned char con[10];
/*
	unsigned char al_n;
	unsigned char al_s;
	unsigned char al_e;
	unsigned char al_o;
	unsigned char al_ne;
	unsigned char al_no;
	unsigned char al_se;
	unsigned char al_so;
	unsigned char arriba;
	unsigned char abajo;
*/
	} cnx_t;

// Tabla de Objetos
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

// Propiedades de la ventana
typedef struct
    {
        BYTE x;
        BYTE y;
        BYTE width;
        BYTE height;
    } textwin_t;

// Global definitions
// Aux
#define SET_VALUE  255 // Value assigned by SET condact
#define EMPTY_WORD  0 // Value for word types when no match is found (as for  sentences without adjective or name)
#define INVALID_WORD 255 //
#define MAX_WORD_LENGHT 5  // Number of characters considered per word
#define FLAG_COUNT 256  // Number of flags
#define NUM_CONNECTION_VERBS 13 // Number of verbs used as connection, from 0 to N - 1
#define NUM_CONVERTIBLE_NOUNS 20
#define NUM_PROPER_NOUNS 50 // Number of proper nouns, can't be used as pronoun reference
#define EMPTY_OBJECT 255 // To remark there is no object when the action requires a objno parameter
#define NO_EXIT 255  // If an exit does not exist, its value is this value
#define MAX_CHANNELS 2 // Number of SFX channels
#define STR_NEWLINE "^"

// Attributes
// Indica el número del bit...
#define aLight  	0x00000001
#define aWear   	0x00000002
#define aContainer  0x00000004
#define aNPC        0x00000008
#define aConcealed  0x00000010
#define aEdible     0x00000020
#define aDrinkable  0x00000040
#define aEnterable  0x00000080
#define aFemale     0x00000100
#define aLockable   0x00000200
#define aLocked     0x00000400
#define aMale       0x00000800
#define aNeuter     0x00001000
#define aOpenable   0x00002000
#define aOpen       0x00004000
#define aPluralName 0x00008000
#define aTransparent 0x00010000
#define aScenery    0x00020000
#define aSupporter  0x00040000
#define aSwitchable 0x00080000
#define aOn         0x00100000
#define aStatic     0x00200000
#define aExamined   0x00400000
#define aTaken      0x00800000
#define aDropped    0x01000000
#define aVisited    0x02000000
#define aTalked     0x04000000
#define aWore       0x08000000
#define aEaten      0x10000000
#define aPropio     0x20000000
#define aDeterminado 0x40000000

// Definición de FLAGS del PARSER...

#define flight 0
#define fobjects_carried_count 1
#define fautodec2 2
#define fautodec3 3
#define fautodec4 4
#define fautodec5 5
#define fautodec6 6
#define fautodec7 7
#define fautodec8 8
#define fautodec9 9
#define fautodec10 10
#define fescape 11
#define fparser_settings 12
#define fobjects_location 15
#define fpicture_settings 29
#define fscore 30
#define fturns_low 31
#define fturns_high 32
#define fverb 33
#define fnoun1 34
#define fadject1 35
#define fadverb 36
#define fmaxobjects_carried 37
#define flocation 38
#define fprep 43
#define fnoun2 44
#define fadject2 45
#define fobj1 51
#define fcapacidad 52
#define fmaxweight_carried 52
#define fobjetoPeso 55
#define fobjetoAttrL 56
#define fobjetoAttrH 57
#define fsalidas 58
#define fcounter flags[59]
#define fcontador flags[59]
#define fend flags[54]
#define fcaracter flags[50]
#define fsalir flags[54]
#define fquit flags[54]
#define fverbo flags[fverb]
#define fnombre1 flags[fnoun1]
#define fnombre2 flags[fnoun2]
#define fadj1 flags[fadject1]
#define fadj2 flags[fadject2]
#define fadv flags[fadverb]
#define fprepo flags[fprep]
#define flocalidad flags[flocation]

#define LOCATION_MAX  251
#define LOCATION_WORN 253
#define LOCATION_CARRIED 254
#define LOCATION_NONCREATED 252
#define LOCATION_HERE 255

// Disponibles para la aventura: 60 to 250.

#define STATE_MENU 0
#define STATE_LOOP 1
#define STATE_QUIT 2
#define STATE_SAVE 3
#define STATE_LOAD 4


//-------------------------------------
// SYSTEM MESSAGES
//-------------------------------------
#define SYSMESS_ISDARK 0
#define SYSMESS_YOUCANSEE 1
#define SYSMESS_PROMPT0 2
#define SYSMESS_PROMPT1 3
#define SYSMESS_PROMPT2 4
#define SYSMESS_PROMPT3 5
#define SYSMESS_IDONTUNDERSTAND 6
#define SYSMESS_WRONGDIRECTION 7
#define SYSMESS_CANTDOTHAT 8
#define SYSMESS_YOUARECARRYING 9
#define SYSMESS_WORN 10
#define SYSMESS_CARRYING_NOTHING 11
#define SYSMESS_AREYOUSURE 12
#define SYSMESS_PLAYAGAIN 13
#define SYSMESS_FAREWELL 14
#define SYSMESS_OK 15
#define SYSMESS_PRESSANYKEY 16
#define SYSMESS_TURNS_START 17
#define SYSMESS_TURNS_CONTINUE 18
#define SYSMESS_TURNS_PLURAL 19
#define SYSMESS_TURNS_END 20
#define SYSMESS_SCORE_START 21
#define SYSMESS_SCORE_END 22
#define SYSMESS_YOURENOTWEARINGTHAT 23
#define SYSMESS_YOUAREALREADYWEARINGTHAT 24
#define SYSMESS_YOUALREADYHAVEOBJECT 25
#define SYSMESS_CANTSEETHAT 26
#define SYSMESS_CANTCARRYANYMORE 27
#define SYSMESS_YOUDONTHAVETHAT 28
#define SYSMESS_YOUAREALREADYWAERINGOBJECT 29
#define SYSMESS_YOUCANNOTREMOVEOBJECT 70
#define SYSMESS_YES 30
#define SYSMESS_NO 31
#define SYSMESS_MORE 32
#define SYSMESS_CARET 33
#define SYSMESS_TIMEOUT 35
#define SYSMESS_YOUTAKEOBJECT 36
#define SYSMESS_YOUWEAROBJECT 37
#define SYSMESS_YOUREMOVEOBJECT 38
#define SYSMESS_YOUDROPOBJECT 39
#define SYSMESS_YOUCANTWEAROBJECT 40
#define SYSMESS_YOUCANTREMOVEOBJECT 41
#define SYSMESS_CANTREMOVE_TOOMANYOBJECTS 42
#define SYSMESS_WEIGHSTOOMUCH 43
#define SYSMESS_YOUPUTOBJECTIN 44
#define SYSMESS_YOUCANTTAKEOBJECTOUTOF 45
#define SYSMESS_LISTSEPARATOR 46
#define SYSMESS_LISTLASTSEPARATOR 47
#define SYSMESS_LISTEND 48
#define SYSMESS_YOUDONTHAVEOBJECT 49
#define SYSMESS_YOUARENOTWEARINGOBJECT 50
#define SYSMESS_PUTINTAKEOUTTERMINATION 51
#define SYSMESS_THATISNOTIN 52
#define SYSMESS_EMPTYOBJECTLIST 53
#define SYSMESS_FILENOTVALID 54
#define SYSMESS_CORRUPTFILE 55
#define SYSMESS_IOFAILURE 56
#define SYSMESS_DIRECTORYFULL 57
#define SYSMESS_LOADFILE 58
#define SYSMESS_FILENOTFOUND 59
#define SYSMESS_SAVEFILE 60
#define SYSMESS_SORRY  61
#define SYSMESS_NONSENSE_SENTENCE 62
#define SYSMESS_NPCLISTSTART 63
#define SYSMESS_NPCLISTCONTINUE 64
#define SYSMESS_NPCLISTCONTINUE_PLURAL 65
#define SYSMESS_INSIDE_YOUCANSEE 66
#define SYSMESS_OVER_YOUCANSEE 67
#define SYSMESS_YOUCANTTAKEOBJECTFROM 69
#define SYSMESS_YOUPUTOBJECTON 70
