
#ifndef _FZXFONTS_UTZ_H
#define _FZXFONTS_UTZ_H

///////////////////////////////////////////////////////////
//                                                       //
//            FZX FONT PACK - FZXFONTS_UTZ               //
//                     by utz                            //
//                                                       //
///////////////////////////////////////////////////////////
//                                                       //
// You can use these fonts freely in your non-commercial //
// projects, provided you credit me.  No exclusive       //
// reservations for game/demo projects will be accepted, //
// these fonts are for everyone.                         //
//                                                       //
// If you want an exclusive font for your project, feel  //
// free to contact me on WOS.                            //
//                                                       //
// https://sites.google.com/site/zxgraph/home/utz/fonts  //
//                                                       //
///////////////////////////////////////////////////////////

#include <fzx.h>

///////////////////////////////////////////////////////////
//                  FONT ENUMERATION                     //
///////////////////////////////////////////////////////////

#define fzxfonts_names_utz     ((char **)(_fzxfonts_names_utz))
#define fzxfonts_enum_utz_A    ((struct fzx_enum *)(_fzxfonts_enum_utz_A))
#define fzxfonts_enum_utz_B    ((struct fzx_enum *)(_fzxfonts_enum_utz_B))
#define fzxfonts_enum_utz_C    ((struct fzx_enum *)(_fzxfonts_enum_utz_C))

///////////////////////////////////////////////////////////
//                  AVAILABLE FONTS                      //
///////////////////////////////////////////////////////////

#define ff_utz_1stGrade        ((struct fzx_font *)(_ff_utz_1stGrade)) // Estilo Escrita a mano, demasiado grande
#define ff_utz_Blokz           ((struct fzx_font *)(_ff_utz_Blokz))     // No funciona
#define ff_utz_GridDrop0       ((struct fzx_font *)(_ff_utz_GridDrop0)) // Fuente por puntos, demasiado grande
#define ff_utz_GridDrop1       ((struct fzx_font *)(_ff_utz_GridDrop1))
#define ff_utz_Handpress       ((struct fzx_font *)(_ff_utz_Handpress)) 
#define ff_utz_KickDrop        ((struct fzx_font *)(_ff_utz_KickDrop)) // No funciona
#define ff_utz_Notez           ((struct fzx_font *)(_ff_utz_Notez))   // Cursiva, pero no muy legible
#define ff_utz_PhatKidzBRK     ((struct fzx_font *)(_ff_utz_PhatKidzBRK)) // Ilegible
#define ff_utz_Phraktur        ((struct fzx_font *)(_ff_utz_Phraktur))  /// Preciosa fuente gótica, muy grande
#define ff_utz_SchoolBrkCD     ((struct fzx_font *)(_ff_utz_SchoolBrkCD)) // No funciona
#define ff_utz_SchoolBrkEXT    ((struct fzx_font *)(_ff_utz_SchoolBrkEXT)) // No funciona
#define ff_utz_SchoolBrkU      ((struct fzx_font *)(_ff_utz_SchoolBrkU)) // No funciona
#define ff_utz_ShadowFlower    ((struct fzx_font *)(_ff_utz_ShadowFlower)) // *Preciosa para títulos
#define ff_utz_Skyscrap        ((struct fzx_font *)(_ff_utz_Skyscrap)) // Fuentes altas, para títulos
#define ff_utz_TinyTexanS      ((struct fzx_font *)(_ff_utz_TinyTexanS)) // Legible, 4pt
#define ff_utz_TinyTexanXS     ((struct fzx_font *)(_ff_utz_TinyTexanXS)) // No funciona
#define ff_utz_TinyTexanXXS    ((struct fzx_font *)(_ff_utz_TinyTexanXXS))  // No funciona

///////////////////////////////////////////////////////////
//                   compiler only                       //
///////////////////////////////////////////////////////////

extern void __LIB__ _fzxfonts_names_utz(void);
extern void __LIB__ _fzxfonts_enum_utz_A(void);
extern void __LIB__ _fzxfonts_enum_utz_B(void);
extern void __LIB__ _fzxfonts_enum_utz_C(void);

extern void __LIB__ _ff_utz_1stGrade(void);
extern void __LIB__ _ff_utz_Blokz(void);
extern void __LIB__ _ff_utz_GridDrop0(void);
extern void __LIB__ _ff_utz_GridDrop1(void);
extern void __LIB__ _ff_utz_Handpress(void);
extern void __LIB__ _ff_utz_KickDrop(void);
extern void __LIB__ _ff_utz_Notez(void);
extern void __LIB__ _ff_utz_PhatKidzBRK(void);
extern void __LIB__ _ff_utz_Phraktur(void);
extern void __LIB__ _ff_utz_SchoolBrkCD(void);
extern void __LIB__ _ff_utz_SchoolBrkEXT(void);
extern void __LIB__ _ff_utz_SchoolBrkU(void);
extern void __LIB__ _ff_utz_ShadowFlower(void);
extern void __LIB__ _ff_utz_Skyscrap(void);
extern void __LIB__ _ff_utz_TinyTexanS(void);
extern void __LIB__ _ff_utz_TinyTexanXS(void);
extern void __LIB__ _ff_utz_TinyTexanXXS(void);

#endif
