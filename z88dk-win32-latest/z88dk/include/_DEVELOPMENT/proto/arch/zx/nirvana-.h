include(__link__.m4)

#ifndef __NIRVANA_MINUS_H__
#define __NIRVANA_MINUS_H__

#include <arch.h>
#include <intrinsic.h>

/* ----------------------------------------------------------------
 * Z88DK INTERFACE LIBRARY FOR NIRVANA- ENGINE - by Einar Saukas
 *
 * If you use this interface library, you must load afterwards the
 * NIRVANA+ ENGINE and a bicolor tile set. For a detailed sample
 * see file "nirvanadem.c".
 * ----------------------------------------------------------------
 */

// ----------------------------------------------------------------
// Activate NIRVANA ENGINE
// ----------------------------------------------------------------

__OPROTO(`b,c,d,e,h,l',`b,c,d,e,h,l',void,,NIRVANAM_start,void)

// ----------------------------------------------------------------
// Deactivate NIRVANA ENGINE
// ----------------------------------------------------------------

__OPROTO(`b,c,d,e,h,l',`b,c,d,e,h,l',void,,NIRVANAM_stop,void)

// ----------------------------------------------------------------
// Execute HALT (wait for next frame).
//
// If an interrupt occurs while certain routines are under execution
// the program may crash (routines NIRVANAM_fillT, NIRVANAM_drawT and
// NIRVANAM_drawW), or a sprite may be displayed at an incorrect
// location (routine NIRVANAM_spriteT).
//
// Routine NIRVANAM_halt can be used to avoid these problems.
// Immediately after calling it, your program will have some time
// (about 12.5K T) to execute a few other routines without any
// interruption.
// ----------------------------------------------------------------

#define NIRVANAM_halt()  intrinsic_halt()

// ----------------------------------------------------------------
// Location of NIRVANA ISR hook
// ----------------------------------------------------------------

extern unsigned char NIRVANAM_ISR_HOOK[3];

// ----------------------------------------------------------------
// Location of NIRVANA hole
// ----------------------------------------------------------------

#define NIRVANAM_HOLE_SIZE __NIRVANAM_HOLE_SIZE

#if NIRVANAM_HOLE_SIZE > 0
extern unsigned char NIRVANAM_HOLE[NIRVANAM_HOLE_SIZE];
#endif

// ----------------------------------------------------------------
// Instantly draw tile (16x16 pixels) at specified position
//
// Parameters:
//     tile: tile index (0-255)
//     lin: pixel line (0-200, even values only)
//     col: char column (0-30)
//
// WARNING: If the *_raw routine is under execution when interrupt
//          occurs, program may crash!!! (see NIRVANAM_halt)
// ----------------------------------------------------------------

__DPROTO(,,void,,NIRVANAM_drawT,unsigned char tile,unsigned char lin,unsigned char col)
__DPROTO(,,void,,NIRVANAM_drawT_raw,unsigned char tile,unsigned char lin,unsigned char col)

// ----------------------------------------------------------------
// Instantly change the attributes in a tile area (16x16 pixels) to
// the specified value (use the same INK and PAPER values to "erase"
// a tile)
//
// Parameters:
//     attr: attribute value (0-255), INK+8*PAPER+64*BRIGHT+128*FLASH
//     lin: pixel line (0-200, even values only)
//     col: char column (0-30)
//
// WARNING: If the *_raw routine is under execution when interrupt
//          occurs, program may crash!!! (see NIRVANAhalt)
// ----------------------------------------------------------------

__DPROTO(,,void,,NIRVANAM_fillT,unsigned char attr,unsigned char lin,unsigned char col)
__DPROTO(,,void,,NIRVANAM_fillT_raw,unsigned char attr,unsigned char lin,unsigned char col)

// ----------------------------------------------------------------
// Instantly print a 8x8 character at specified position, afterwards
// paint it with a provided sequence of 4 attribute values.
//
// Parameters:
//     ch: character code (0-255)
//     attrs: attributes address
//     lin: pixel line (16-192, even values only)
//     col: char column (0-31)
// ----------------------------------------------------------------

__DPROTO(,,void,,NIRVANAM_printC,unsigned char ch,void *attrs,unsigned char lin,unsigned char col)

// ----------------------------------------------------------------
// Instantly paint a 8x8 character at specified position with a
// provided sequence of 4 attribute values.
//
// Parameters:
//     attrs: attributes address
//     lin: pixel line (16-192, even values only)
//     col: char column (0-31)
// ----------------------------------------------------------------

__DPROTO(,,void,,NIRVANAM_paintC,void *attrs,unsigned char lin,unsigned char col)

// -----------------------------------------------------------------------------
// Retrieve a sequence of 4 attribute values from specified 8x8 block
//
// Parameters:
//     attrs: destination for read sequence
//     lin: pixel line (16-192, even values only)
//     col: char column (0-31)
// -----------------------------------------------------------------------------

__DPROTO(,,void,,NIRVANAM_readC,void *attrs,unsigned char lin,unsigned char col)

// ----------------------------------------------------------------
// Instantly change attributes in 8x8 character area to the
// specified value (use the same INK and PAPER values to "erase" a
// character).
//
// Parameters:
//     attr: attribute value (0-255), INK+8*PAPER+64*BRIGHT+128*FLASH
//     lin: pixel line (16-192, even values only)
//     col: char column (0-31)
// ----------------------------------------------------------------

__DPROTO(`b',`b',void,,NIRVANAM_fillC,unsigned char attr,unsigned char lin,unsigned char col)

// ----------------------------------------------------------------
// Update sprite information, so the specified tile will automatically
// appear at the specified location when the next interrupt occurs
// (and automatically redrawn at every interrupt afterwards, until
// this sprite information is updated again).
//
// Sprites are displayed in increasing priority order, i.e.
// sprite 7 will appear in front of everything else.
//
// Notice there's no way to disable sprites. If you don't want to
// display a certain sprite, simply move it to line zero, so it
// will be hidden outside the screen.
//
// Parameters:
//     sprite: sprite number (0-7)
//     tile: tile index (0-255)
//     lin: pixel line (0-200, even values only)
//     col: char column (0-30)
//
// WARNING: If this routine is under execution when interrupt occurs,
//          a sprite (containing partially updated information) may
//          be displayed at an incorrect location on screen (see
//          NIRVANAhalt)
// ----------------------------------------------------------------

__DPROTO(,,void,,NIRVANAM_spriteT,unsigned char sprite,unsigned char tile,unsigned char lin,unsigned char col)

// -----------------------------------------------------------------------
// Instantly draw wide tile (24x16 pixels) at specified position
//
// Parameters:
//     tile: wide tile index (0-255)
//     lin: pixel line (0-200, even values only)
//     col: char column (0-29)
//
// WARNING: If the *_raw routine is under execution when interrupt
//          occurs, program may crash!!! (see NIRVANAhalt)
//
// WARNING: This routine is only available if NIRVANA_drawW was enabled!!!
// -----------------------------------------------------------------------

__DPROTO(,,void,,NIRVANAM_drawW,unsigned char tile,unsigned char lin,unsigned char col)
__DPROTO(,,void,,NIRVANAM_drawW_raw,unsigned char tile,unsigned char lin,unsigned char col)

// ----------------------------------------------------------------------------------
// Executes NIRVANA_drawT for wide sprites but takes as long as NIRVANA_drawW.
// This way each wide sprite can freely switch between both without affecting timing.
// ----------------------------------------------------------------------------------
// Parameters:
//     tile: tile index (0-255)
//     lin: pixel line (0-200, even values only)
//     col: char column (0-30)
//
// WARNING: If *_raw routine is under execution when interrupt
//          occurs, program may crash!!! (see NIRVANAM_halt)
//
// WARNING: This routine is only available if NIRVANA_drawW was enabled!!!
// ----------------------------------------------------------------------------------

__DPROTO(,,void,,NIRVANAM_drawTW,unsigned char tile,unsigned char lin,unsigned char col)
__DPROTO(,,void,,NIRVANAM_drawTW_raw,unsigned char tile,unsigned char lin,unsigned char col)

// ----------------------------------------------------------------
// Reconfigure NIRVANA ENGINE to read bicolor tiles (16x16 pixels)
// from another address (default value is 48000).
//
// Parameters:
//     addr: New tile images address
// ----------------------------------------------------------------

extern unsigned char NIRVANAM_TILE_IMAGES[];
#define NIRVANAM_tiles(addr) intrinsic_store16(_NIRVANAM_TILE_IMAGES,addr)

// ----------------------------------------------------------------
// Reconfigure NIRVANA ENGINE to read wide bicolor tiles (24x16
// pixels) from another address (default value is 54000).
//
// Parameters:
//     addr: New wide tile images address
//
// WARNING: Only use this routine if NIRVANAM_drawW was enabled!!!
// ----------------------------------------------------------------

extern unsigned char NIRVANAM_WIDE_IMAGES[];
#define NIRVANAM_wides(addr) intrinsic_store16(_NIRVANAM_WIDE_IMAGES,addr)

// ----------------------------------------------------------------
// Reconfigure NIRVANA ENGINE to read character table from another
// address (default value is 15360 that corresponds to the standard
// ROM character table).
//
// Parameters:
//     addr: New character table address
// ----------------------------------------------------------------

extern unsigned char NIRVANAM_CHAR_TABLE[];
#define NIRVANAM_chars(addr) intrinsic_store16(_NIRVANAM_CHAR_TABLE,addr)

// ----------------------------------------------------------------
// Advanced conversions
// ----------------------------------------------------------------

#define ROW2LIN(row)            (((row)+1)<<3)
#define LIN2ROW_UP(lin)         (((lin)>>3)-1)
#define LIN2ROW_DOWN(lin)       (((lin)-1)>>3)

#define SPRITECOL(sprite)       ((unsigned char *)57574+((sprite)<<3))
#define SPRITELIN(sprite)       ((unsigned char *)57575+((sprite)<<3))
#define SPRITEVAL(sprite)       ((unsigned char *)57577+((sprite)<<3))

#endif
