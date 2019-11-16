
#ifndef _FZX_H
#define _FZX_H

///////////////////////////////////////////////////////////
//                                                       //
//           FZX PROPORTIONAL FONT RENDERER              //
//                                                       //
//     FZX driver - Copyright (c) 2013 Einar Saukas      //
//     FZX format - Copyright (c) 2013 Andrew Owen       //
//                                                       //
//      z88dk library wrapper - aralbrec Nov 2013        //
//                                                       //
///////////////////////////////////////////////////////////

#include <sys/types.h>

///////////////////////////////////////////////////////////
//                  DATA STRUCTURES                      //
///////////////////////////////////////////////////////////

// FONT STRUCTURES

struct fzx_char                 // FONT'S CHAR DESCRIPTOR
{

   uint             kern_offset;     // kern in bits 15..14, offset to bitmap from fzx_char address
   uchar            shift_width_1;   // shift in bits 7..4, width-1 in bits 3..0

};

struct fzx_font                 // FONT STRUCTURE
{

   uchar            height;     // row height in pixels
   uchar            tracking;   // horizontal gap between chars in pixels
   uchar            last_char;  // last defined char bitmap in 32..255
   struct fzx_char  bmp[0];     // begin char bitmap definitions at char code 32

};

struct fzx_cmetric              // FONT CHARACTER METRICS
{

   uchar            kern;       // num pixels to leftshift rendered char within string, 0-3
   uchar            width;      // width of glyph, 1-16
   uchar            shift;      // num pixels to downshift rendered char from top of line, 0-15
   void            *bitmap;     // address of glyph bitmap
   
};

// FONT ENUMERATION

struct fzx_enum
{
   char            *name;       // font name
   struct fzx_font *font;       // pointer to font
};

// FZX STATE

struct fzx_state
{

   struct fzx_font *font;      // current font
   uchar            lm;        // left margin in pixels
   uchar            flags;     // reserved, set to 0 to reset
   uchar            x;         // current x coordinate in pixels
   uchar            y;         // current y coordinate in pixels

};

extern struct fzx_state fzx;   // active fzx state

///////////////////////////////////////////////////////////
//                      DRAW TEXT                        //
///////////////////////////////////////////////////////////

extern int               __LIB__ fzx_setat(uchar y, uchar x);
extern int  __FASTCALL__ __LIB__ fzx_putc(uchar c);

extern int  __FASTCALL__ __LIB__ fzx_puts(char *s);
extern int               __LIB__ fzx_write(void *buf, uint len);

///////////////////////////////////////////////////////////
//                     TEXT EXTENT                       //
///////////////////////////////////////////////////////////

extern int  __LIB__  fzx_cMetric(struct fzx_cmetric *m, uchar c);

extern uint __FASTCALL__ __LIB__ fzx_sExtent(char *s);
extern uint              __LIB__ fzx_bExtent(void *buf, uint len);

extern char __LIB__ *fzx_sPartition(char *s, uint width);
extern char __LIB__ *fzx_sPartitionWW(char *s, uint width);

extern void __LIB__ *fzx_bPartition(void *buf, uint len, uint width);
extern void __LIB__ *fzx_bPartitionWW(void *buf, uint len, uint width);

///////////////////////////////////////////////////////////
//                  FONT ENUMERATION                     //
///////////////////////////////////////////////////////////

#define fzxfonts_names           ((char **)(_fzxfonts_names))
#define fzxfonts_enum_A          ((struct fzx_enum *)(_fzxfonts_enum_A))
#define fzxfonts_enum_B          ((struct fzx_enum *)(_fzxfonts_enum_B))
#define fzxfonts_enum_C          ((struct fzx_enum *)(_fzxfonts_enum_C))
#define fzxfonts_enum_D          ((struct fzx_enum *)(_fzxfonts_enum_D))
#define fzxfonts_enum_E          ((struct fzx_enum *)(_fzxfonts_enum_E))
#define fzxfonts_enum_F          ((struct fzx_enum *)(_fzxfonts_enum_F))

///////////////////////////////////////////////////////////
//                   AVAILABLE FONTS                     //
///////////////////////////////////////////////////////////

#define ff_Aribeth14             ((struct fzx_font *)(_ff_Aribeth14))
#define ff_Aribeth6              ((struct fzx_font *)(_ff_Aribeth6))
#define ff_Aribeth8              ((struct fzx_font *)(_ff_Aribeth8))
#define ff_Arkade                ((struct fzx_font *)(_ff_Arkade))
#define ff_Blackadder            ((struct fzx_font *)(_ff_Blackadder))
#define ff_Cayeux                ((struct fzx_font *)(_ff_Cayeux))
#define ff_Cheveron              ((struct fzx_font *)(_ff_Cheveron))
#define ff_Chloe                 ((struct fzx_font *)(_ff_Chloe))
#define ff_Dutch                 ((struct fzx_font *)(_ff_Dutch))
#define ff_GenevaMonoBold        ((struct fzx_font *)(_ff_GenevaMonoBold))
#define ff_GenevaMonoBoldItalic  ((struct fzx_font *)(_ff_GenevaMonoBoldItalic))
#define ff_GenevaMonoCyrillic    ((struct fzx_font *)(_ff_GenevaMonoCyrillic))
#define ff_GenevaMonoItalic      ((struct fzx_font *)(_ff_GenevaMonoItalic))
#define ff_GenevaMonoRoman       ((struct fzx_font *)(_ff_GenevaMonoRoman))
#define ff_GenevaMonoSymbol      ((struct fzx_font *)(_ff_GenevaMonoSymbol))
#define ff_Grotesk               ((struct fzx_font *)(_ff_Grotesk))
#define ff_Hemery                ((struct fzx_font *)(_ff_Hemery))
#define ff_Hiroshi               ((struct fzx_font *)(_ff_Hiroshi))
#define ff_Jangeborg             ((struct fzx_font *)(_ff_Jangeborg))
#define ff_Kaitaia               ((struct fzx_font *)(_ff_Kaitaia))
#define ff_Klausjahn             ((struct fzx_font *)(_ff_Klausjahn))
#define ff_Lettera               ((struct fzx_font *)(_ff_Lettera))
#define ff_Napier                ((struct fzx_font *)(_ff_Napier))
#define ff_Newbrand              ((struct fzx_font *)(_ff_Newbrand))
#define ff_OldEnglish            ((struct fzx_font *)(_ff_OldEnglish))
#define ff_OpenDyslexic          ((struct fzx_font *)(_ff_OpenDyslexic))
#define ff_Orion                 ((struct fzx_font *)(_ff_Orion))
#define ff_Prefect               ((struct fzx_font *)(_ff_Prefect))
#define ff_Programmer            ((struct fzx_font *)(_ff_Programmer))
#define ff_RoundelSans           ((struct fzx_font *)(_ff_RoundelSans))
#define ff_RoundelSerif          ((struct fzx_font *)(_ff_RoundelSerif))
#define ff_Sabon                 ((struct fzx_font *)(_ff_Sabon))
#define ff_Sinclair              ((struct fzx_font *)(_ff_Sinclair))
#define ff_SoixanteQuatre        ((struct fzx_font *)(_ff_SoixanteQuatre))
#define ff_Soxz                  ((struct fzx_font *)(_ff_Soxz))
#define ff_SpecDings             ((struct fzx_font *)(_ff_SpecDings))
#define ff_Swiss                 ((struct fzx_font *)(_ff_Swiss))
#define ff_Trader                ((struct fzx_font *)(_ff_Trader))
#define ff_Twombly               ((struct fzx_font *)(_ff_Twombly))
#define ff_Vickers               ((struct fzx_font *)(_ff_Vickers))
#define ff_Videotex              ((struct fzx_font *)(_ff_Videotex))
#define ff_Zaibatsu              ((struct fzx_font *)(_ff_Zaibatsu))

///////////////////////////////////////////////////////////
//                   compiler only                       //
///////////////////////////////////////////////////////////

extern void __LIB__ _fzxfonts_names(void);
extern void __LIB__ _fzxfonts_enum_A(void);
extern void __LIB__ _fzxfonts_enum_B(void);
extern void __LIB__ _fzxfonts_enum_C(void);
extern void __LIB__ _fzxfonts_enum_D(void);
extern void __LIB__ _fzxfonts_enum_E(void);
extern void __LIB__ _fzxfonts_enum_F(void);

extern void __LIB__ _ff_Aribeth14(void);
extern void __LIB__ _ff_Aribeth6(void);
extern void __LIB__ _ff_Aribeth8(void);
extern void __LIB__ _ff_Arkade(void);
extern void __LIB__ _ff_Blackadder(void);
extern void __LIB__ _ff_Cayeux(void);
extern void __LIB__ _ff_Cheveron(void);
extern void __LIB__ _ff_Chloe(void);
extern void __LIB__ _ff_Dutch(void);
extern void __LIB__ _ff_GenevaMonoBold(void);
extern void __LIB__ _ff_GenevaMonoBoldItalic(void);
extern void __LIB__ _ff_GenevaMonoCyrillic(void);
extern void __LIB__ _ff_GenevaMonoItalic(void);
extern void __LIB__ _ff_GenevaMonoRoman(void);
extern void __LIB__ _ff_GenevaMonoSymbol(void);
extern void __LIB__ _ff_Grotesk(void);
extern void __LIB__ _ff_Hemery(void);
extern void __LIB__ _ff_Hiroshi(void);
extern void __LIB__ _ff_Jangeborg(void);
extern void __LIB__ _ff_Kaitaia(void);
extern void __LIB__ _ff_Klausjahn(void);
extern void __LIB__ _ff_Lettera(void);
extern void __LIB__ _ff_Napier(void);
extern void __LIB__ _ff_Newbrand(void);
extern void __LIB__ _ff_OldEnglish(void);
extern void __LIB__ _ff_OpenDyslexic(void);
extern void __LIB__ _ff_Orion(void);
extern void __LIB__ _ff_Prefect(void);
extern void __LIB__ _ff_Programmer(void);
extern void __LIB__ _ff_RoundelSans(void);
extern void __LIB__ _ff_RoundelSerif(void);
extern void __LIB__ _ff_Sabon(void);
extern void __LIB__ _ff_Sinclair(void);
extern void __LIB__ _ff_SoixanteQuatre(void);
extern void __LIB__ _ff_Soxz(void);
extern void __LIB__ _ff_SpecDings(void);
extern void __LIB__ _ff_Swiss(void);
extern void __LIB__ _ff_Trader(void);
extern void __LIB__ _ff_Twombly(void);
extern void __LIB__ _ff_Vickers(void);
extern void __LIB__ _ff_Videotex(void);
extern void __LIB__ _ff_Zaibatsu(void);

extern int  __CALLEE__  __LIB__ fzx_setat_callee(uchar y, uchar x);
extern int  __CALLEE__  __LIB__ fzx_write_callee(void *buf, uint len);
extern int  __CALLEE__  __LIB__ fzx_cMetric_callee(struct fzx_char_metric *m, uchar c);
extern uint __CALLEE__  __LIB__ fzx_bExtent_callee(void *buf, uint len);
extern char __CALLEE__  __LIB__ *fzx_sPartition_callee(char *s, uint width);
extern char __CALLEE__  __LIB__ *fzx_sPartitionWW_callee(char *s, uint width);
extern void __CALLEE__  __LIB__ *fzx_bPartition_callee(void *buf, uint len, uint width);
extern void __CALLEE__  __LIB__ *fzx_bPartitionWW_callee(void *buf, uint len, uint width);

#define fzx_setat(a,b)            fzx_setat_callee(a,b)
#define fzx_write(a,b)            fzx_write_callee(a,b)
#define fzx_cMetric(a,b)          fzx_cMetric_callee(a,b)
#define fzx_bExtent(a,b)          fzx_bExtent_callee(a,b)
#define fzx_sPartition(a,b)       fzx_sPartition_callee(a,b)
#define fzx_sPartitionWW(a,b)     fzx_sPartitionWW_callee(a,b)
#define fzx_bPartition(a,b,c)     fzx_bPartition_callee(a,b,c)
#define fzx_bPartitionWW(a,b,c)   fzx_bPartitionWW_callee(a,b,c)

#endif
