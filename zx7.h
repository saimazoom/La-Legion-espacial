/* ----------------------------------------------------------------------------
 * Z88DK LIBRARY FOR ZX7 DECOMPRESSORS
 *
 * USAGE:
 *
 * 1. Copy files "zx7.h" and "zx7.lib" to same folder as your program.
 *
 * 2. Include this library in your program like this:
 *    #include "zx7.h"
 *
 * 3. Choose a ZX7 decompressor and use it in your program like this:
 *    dzx7Turbo(((unsigned char *)51200), ((unsigned char *)16384));
 *
 * 4. Compile your program like this:
 *    zcc.exe +zx -lm -lndos -lzx7 -create-app prog.c -oprog.bin
 *
 * Original version and further information is available at
 * http://www.worldofspectrum.org/infoseekid.cgi?id=0027996
 * http://www.worldofspectrum.org/infoseekid.cgi?id=0028048
 *
 * Copyleft (k) Einar Saukas
 * ----------------------------------------------------------------------------
 */
#ifndef __ZX7_H__
#define __ZX7_H__

// ----------------------------------------------------------------------------
// Decompress (from source to destination address) data that was previously
// compressed using ZX7. This is the smallest version of the ZX7 decompressor.
//
// Parameters:
//     src: source address (compressed data)
//     dst: destination address (decompressing)
// ----------------------------------------------------------------------------
extern void __LIB__ dzx7Standard(unsigned char *src, unsigned char *dst);


// ----------------------------------------------------------------------------
// Decompress (from source to destination address) data that was previously
// compressed using ZX7. This is the intermediate version of the ZX7
// decompressor, providing the best balance between speed and size.
//
// Parameters:
//     src: source address (compressed data)
//     dst: destination address (decompressing)
// ----------------------------------------------------------------------------
extern void __LIB__ dzx7Turbo(unsigned char *src, unsigned char *dst);


// ----------------------------------------------------------------------------
// Decompress (from source to destination address) data that was previously
// compressed using ZX7. This is the fastest version of the ZX7 decompressor.
//
// Parameters:
//     src: source address (compressed data)
//     dst: destination address (decompressing)
// ----------------------------------------------------------------------------
extern void __LIB__ dzx7Mega(unsigned char *src, unsigned char *dst);


// ----------------------------------------------------------------------------
// Decompress (from source to destination address) data that was previously
// compressed using ZX7. This is the smallest version of the integrated RCS+ZX7
// decompressor.
//
// IMPORTANT: Data decompressed directly to the ZX-Spectrum screen must be both
// RCS encoded and ZX7 compressed, everything else must be ZX7 compressed only.
//
// Parameters:
//     src: source address (compressed data)
//     dst: destination address (decompressing)
// ----------------------------------------------------------------------------
extern void __LIB__ dzx7SmartRCS(unsigned char *src, unsigned char *dst);


// ----------------------------------------------------------------------------
// Decompress (from source to destination address) data that was previously
// compressed using ZX7. This is the fastest version of the integrated RCS+ZX7
// decompressor.
//
// IMPORTANT: Data decompressed directly to the ZX-Spectrum screen must be both
// RCS encoded and ZX7 compressed, everything else must be ZX7 compressed only.
//
// Parameters:
//     src: source address (compressed data)
//     dst: destination address (decompressing)
// ----------------------------------------------------------------------------
extern void __LIB__ dzx7AgileRCS(unsigned char *src, unsigned char *dst);


// ----------------------------------------------------------------------------
// LIBRARY OPTIMIZATIONS (developers can safely ignore this part!)
// ----------------------------------------------------------------------------
extern void __CALLEE__ __LIB__ dzx7Standard_callee(unsigned char *src, unsigned char *dst);
#define dzx7Standard(src, dst)  dzx7Standard_callee(src, dst)
extern void __CALLEE__ __LIB__ dzx7Turbo_callee(unsigned char *src, unsigned char *dst);
#define dzx7Turbo(src, dst)  dzx7Turbo_callee(src, dst)
extern void __CALLEE__ __LIB__ dzx7Mega_callee(unsigned char *src, unsigned char *dst);
#define dzx7Mega(src, dst)  dzx7Mega_callee(src, dst)
extern void __CALLEE__ __LIB__ dzx7SmartRCS_callee(unsigned char *src, unsigned char *dst);
#define dzx7SmartRCS(src, dst)  dzx7SmartRCS_callee(src, dst)
extern void __CALLEE__ __LIB__ dzx7AgileRCS_callee(unsigned char *src, unsigned char *dst);
#define dzx7AgileRCS(src, dst)  dzx7AgileRCS_callee(src, dst)

#endif
