
#define BYTE unsigned char
#define WORD unsigned int
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

// The function being called (callee) is responsible for cleaning up the stack.
extern void __CALLEE__ putPixel (BYTE x, BYTE y);
extern void __CALLEE__ scrollArriba (BYTE fila_inicial, BYTE columna_inicial);
extern void __CALLEE__scrollArriba2 (BYTE linea_inicial, BYTE num, BYTE step);
extern void __CALLEE__drawRectangle (BYTE xorig, BYTE yorig, BYTE width, BYTE height);
extern void  clsScreen (BYTE effect); // Distintos efectos para borrar la pantalla...
extern void __CALLEE__drawGFX (BYTE gfxnum, BYTE xorig, BYTE yorig);
extern void __CALLEE__ waitForAnyKey();
extern void __CALLEE__drawVline (BYTE x0, BYTE y0, BYTE len);
extern void __CALLEE__drawHline (BYTE x0, BYTE y0, BYTE len);
extern void __CALLEE__clearchar (BYTE x, BYTE y, BYTE color);
extern void __CALLEE__ clear_screen (BYTE color);
extern void __CALLEE__ waitForNoKey();
extern void setRAMPage (BYTE banco);
extern void setRAMBack();
extern void drawGFX (BYTE *pointer, BYTE xorig, BYTE yorig);
extern void drawSprite (BYTE *pointer, BYTE xorig, BYTE yorig, BYTE width, BYTE height);

///////////////////////////////////////////////////////////
//                  DATA STRUCTURES                      //
///////////////////////////////////////////////////////////

// FONT STRUCTURES
/*
struct fzx_char                 // FONT'S CHAR DESCRIPTOR
{

   unsigned int             kern_offset;     // kern in bits 15..14, offset to bitmap from fzx_char address
   unsigned char            shift_width_1;   // shift in bits 7..4, width-1 in bits 3..0

};

struct fzx_font                 // FONT STRUCTURE
{
   unsigned char            height;     // row height in pixels
   unsigned char            tracking;   // horizontal gap between chars in pixels
   unsigned char            last_char;  // last defined char bitmap in 32..255
   struct fzx_char  bmp[0];     // begin char bitmap definitions at char code 32

};

struct fzx_cmetric              // FONT CHARACTER METRICS
{

   unsigned char            kern;       // num pixels to leftshift rendered char within string, 0-3
   unsigned char            width;      // width of glyph, 1-16
   unsigned char            shift;      // num pixels to downshift rendered char from top of line, 0-15
   void            *bitmap;     // address of glyph bitmap
   
};

// FONT ENUMERATION

struct fzx_enum
{
   char            *name;       // font name
   struct fzx_font *font;       // pointer to font
};
*/
// FZX STATE

struct fzx_state
{

  // struct fzx_font *font;      // current font
  // unsigned char            lm;        // left margin in pixels
  // unsigned char            flags;     // reserved, set to 0 to reset
   unsigned char            x;         // current x coordinate in pixels
   unsigned char            y;         // current y coordinate in pixels

};

///////////////////////////////////////////////////////////
//                      DRAW TEXT                        //
///////////////////////////////////////////////////////////
// Functions in printlib.asm
extern int               fzx_setat(unsigned char x, unsigned char y);
extern int  fzx_putc(unsigned char c);

extern int  fzx_puts(char *s);
extern int               fzx_write(unsigned int *buf, unsigned int len);

extern void __CALLEE__ print_string (BYTE x, BYTE y, unsigned char *texto);
extern void __CALLEE__ print_char (BYTE x, BYTE y, unsigned char texto);
extern void __CALLEE__ set_attr (BYTE x, BYTE Y, BYTE attr);


