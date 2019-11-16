
// automatically generated by m4 from headers in proto subdir


#ifndef _ADT_WV_STACK_H
#define _ADT_WV_STACK_H

#include <stddef.h>

// DATA STRUCTURES

typedef struct wv_stack_s
{

   void       *data;
   size_t      size;
   size_t      capacity;
   size_t      max_size;

} wv_stack_t;

extern size_t wv_stack_capacity(wv_stack_t *s) __preserves_regs(b,c,d,e);
extern size_t wv_stack_capacity_fastcall(wv_stack_t *s) __preserves_regs(b,c,d,e) __z88dk_fastcall;
#define wv_stack_capacity(a) wv_stack_capacity_fastcall(a)


extern void wv_stack_clear(wv_stack_t *s) __preserves_regs(b,c,d,e);
extern void wv_stack_clear_fastcall(wv_stack_t *s) __preserves_regs(a,b,c,d,e) __z88dk_fastcall;
#define wv_stack_clear(a) wv_stack_clear_fastcall(a)


extern void wv_stack_destroy(wv_stack_t *s) __preserves_regs(b,c);
extern void wv_stack_destroy_fastcall(wv_stack_t *s) __preserves_regs(b,c) __z88dk_fastcall;
#define wv_stack_destroy(a) wv_stack_destroy_fastcall(a)


extern int wv_stack_empty(wv_stack_t *s) __preserves_regs(b,c,d,e);
extern int wv_stack_empty_fastcall(wv_stack_t *s) __preserves_regs(b,c,d,e) __z88dk_fastcall;
#define wv_stack_empty(a) wv_stack_empty_fastcall(a)


extern wv_stack_t *wv_stack_init(void *p,size_t capacity,size_t max_size);
extern wv_stack_t *wv_stack_init_callee(void *p,size_t capacity,size_t max_size) __z88dk_callee;
#define wv_stack_init(a,b,c) wv_stack_init_callee(a,b,c)


extern size_t wv_stack_max_size(wv_stack_t *s) __preserves_regs(b,c,d,e);
extern size_t wv_stack_max_size_fastcall(wv_stack_t *s) __preserves_regs(b,c,d,e) __z88dk_fastcall;
#define wv_stack_max_size(a) wv_stack_max_size_fastcall(a)


extern void *wv_stack_pop(wv_stack_t *s);
extern void *wv_stack_pop_fastcall(wv_stack_t *s) __z88dk_fastcall;
#define wv_stack_pop(a) wv_stack_pop_fastcall(a)


extern int wv_stack_push(wv_stack_t *s,void *item);
extern int wv_stack_push_callee(wv_stack_t *s,void *item) __z88dk_callee;
#define wv_stack_push(a,b) wv_stack_push_callee(a,b)


extern int wv_stack_reserve(wv_stack_t *s,size_t n);
extern int wv_stack_reserve_callee(wv_stack_t *s,size_t n) __z88dk_callee;
#define wv_stack_reserve(a,b) wv_stack_reserve_callee(a,b)


extern int wv_stack_shrink_to_fit(wv_stack_t *s);
extern int wv_stack_shrink_to_fit_fastcall(wv_stack_t *s) __z88dk_fastcall;
#define wv_stack_shrink_to_fit(a) wv_stack_shrink_to_fit_fastcall(a)


extern size_t wv_stack_size(wv_stack_t *s) __preserves_regs(b,c,d,e);
extern size_t wv_stack_size_fastcall(wv_stack_t *s) __preserves_regs(b,c,d,e) __z88dk_fastcall;
#define wv_stack_size(a) wv_stack_size_fastcall(a)


extern void *wv_stack_top(wv_stack_t *s);
extern void *wv_stack_top_fastcall(wv_stack_t *s) __z88dk_fastcall;
#define wv_stack_top(a) wv_stack_top_fastcall(a)



#endif
