/*
 MiniIF para ordenadores de 8bit
 Basado en PAWS y NGPAWS-Beta 9 (Uto/Carlos Sanchez) http://www.ngpaws.com
 (c) 2016. Written by KMBR.
 v0.1

  License
-----------------------------------------------------------------------------------
 Released under the the GPL v2 or later license. The parser license does not extend 
 to the applications including it. The application is free to choose the license model.
-----------------------------------------------------------------------------------

*/

// CONSTANTS

// AUX
// Estilos de fuentes
#define NORMAL 0
#define TITLE 1
#define PLAYER 2

#define TRUE 1
#define FALSE 0
#define BYTE unsigned char
#define WORD unsigned int
#define DONE ACCdone(); return TRUE
#define NOTDONE ACCbreak(); return FALSE 

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
#define SCREEN_WIDTH 	256
#define SCREEN_HEIGHT 	192 
#define COLS_WIDTH		32
#define ROWS_HEIGHT 	24

// C64 colors

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
#define MAX_INPUT_LENGTH 32
#define MAX_INPUT_WORD 25

// Object attributes
// Indicates the bit number (0...31)
#define aLight  	  0
#define aLight_hex  0x00000001
// aWear: The object can be weared.
#define aWear   	  1
#define aWear_hex   0x00000002
// aContainer: The object can contain things. Additionally it can be also a supporter.
#define aContainer  2
#define aContainer_hex 0x00000004
#define aNPC        3
#define aNPC_hex 0x00000008
// Concealed is a hidden object that can be manipulated
#define aConcealed  4
#define aConcealed_hex 0x00000010

#define aEdible     5
#define aEdible_hex 0x00000020

#define aDrinkable  6
#define aDrinkable_hex 0x00000040

#define aEnterable  7
#define aEnterable_hex  0x00000080

#define aFemale     8
#define aFemale_hex 0x00000100

#define aLockable   9
#define aLockable_hex 0x00000200

#define aLocked     10
#define aLocked_hex 0x00000400

#define aMale       11
#define aMale_hex   0x00000800

#define aNeuter       12
#define aNeuter_hex   0x00001000

// aOpenable =1 -> The object can be opened. OPEN/CLOSE commands will change its status.
#define aOpenable     13
#define aOpenable_hex 0x00002000

// aOpen = 1 -> OPEN, aOpen =0 -> CLOSE
#define aOpen       14
#define aOpen_hex   0x00004000 

// aPluralName = 1, when listed plural article is used
#define aPluralName 15
#define aPluralName_hex  0x00008000

#define aTransparent 16
#define aTransparent_hex 0x00010000

// Scenery: An object which is concealed, present and cannot manipulated just examined (Concealed+Scenery).
#define aScenery    17
#define aScenery_hex 0x00020000

#define aSupporter  18
#define aSupportex_hex 0x00040000

#define aSwitchable 19
#define aSwitchable_hex 0x00080000

// aOn =1 -> ON, aON=0 -> OFF
#define aOn         20
#define aOn_hex     0x00100000
// Static: An object which cannot be manipulated but is present in the location and listed
#define aStatic     21
#define aStatic_hex 0x00200000

#define aExamined   22
#define aExamined_hex  0x00400000

#define aTaken      23
#define aTaken_hex 0x00800000

#define aDropped    24
#define aDropped_hex 0x01000000

#define aVisited    25
#define aVisited_hex 0x02000000

#define aTalked     26
#define aTalked_hex 0x04000000

#define aWore       27
#define aWore_hex  0x08000000

#define aEaten      28
#define aEaten_hex 0x10000000
// The parser does not add the article, in example for a character's name
#define aPropio     29
#define aPropio_hex 0x20000000

// The parser adds the definitive article, the object is known.
// In spanish: el,la, los, las, in English: the  
#define aDeterminado 31
#define aDeterminado_hex 0x80000000

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
#define fadjetivo1 flags[fadject1]
#define fadjetivo2 flags[fadject2]
#define fadverbio flags[fadverb]
#define fpreposicion flags[fprep]
#define flocalidad flags[flocation]

// Some dupes here due to historic reasons i.e. PAWS, DAAD, NGPAWS, etc
#define LOCATION_MAX  251
#define LOCATION_WORN 253
#define LOCATION_CARRIED 254
#define LOCATION_NOTCREATED 252
#define LOCATION_NONCREATED 252
#define LOCATION_HERE 255
#define CARRIED 254
#define HERE 255
#define NOT_CREATED 252
#define WORN 253
#define NONCREATED 252 

// Localidades disponibles para la aventura: 60 to 250.

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
#define SYSMESS_YOUCANNOTTAKE 71
#define SYSMESS_CANNOTMOVE 72
#define SYSMESS_CARRYNOTHING 73
#define SYSMESS_EXITSLIST 74