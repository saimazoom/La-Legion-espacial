
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

extern void __CALLEE__ putPixel (BYTE x, BYTE y);
extern void __CALLEE__ scrollArriba (BYTE fila_inicial, BYTE columna_inicial);
extern void __CALLEE__scrollArriba2 (BYTE linea_inicial, BYTE num, BYTE step);
extern void __CALLEE__drawRectangle (BYTE xorig, BYTE yorig, BYTE width, BYTE height);
extern void __CALLEE__ clsScreen (BYTE effect); // Distintos efectos para borrar la pantalla...
extern void __CALLEE__drawGFX (BYTE gfxnum, BYTE xorig, BYTE yorig);
extern void __CALLEE__ waitForAnyKey();
extern void __CALLEE__drawVline (BYTE x0, BYTE y0, BYTE len);
extern void __CALLEE__drawHline (BYTE x0, BYTE y0, BYTE len);
extern void __CALLEE__clearchar (BYTE x, BYTE y, BYTE color);
extern void __CALLEE__ clear_screen (BYTE color);
extern void __CALLEE__ waitForNoKey();
extern void setRAMPage (BYTE banco);
extern void setRAMBack();
