
// automatically generated by m4 from headers in proto subdir


#ifndef _ADT_P_STACK_H
#define _ADT_P_STACK_H

#include <stddef.h>

// DATA STRUCTURES

typedef void* p_stack_t;

extern void p_stack_clear(p_stack_t *s) __preserves_regs(b,c);
extern void p_stack_clear_fastcall(p_stack_t *s) __preserves_regs(b,c) __z88dk_fastcall;
#define p_stack_clear(a) p_stack_clear_fastcall(a)


extern int p_stack_empty(p_stack_t *s) __preserves_regs(b,c,d,e);
extern int p_stack_empty_fastcall(p_stack_t *s) __preserves_regs(b,c,d,e) __z88dk_fastcall;
#define p_stack_empty(a) p_stack_empty_fastcall(a)


extern void p_stack_init(void *p) __preserves_regs(b,c);
extern void p_stack_init_fastcall(void *p) __preserves_regs(b,c) __z88dk_fastcall;
#define p_stack_init(a) p_stack_init_fastcall(a)


extern void *p_stack_pop(p_stack_t *s) __preserves_regs(b,c);
extern void *p_stack_pop_fastcall(p_stack_t *s) __preserves_regs(b,c) __z88dk_fastcall;
#define p_stack_pop(a) p_stack_pop_fastcall(a)


extern void p_stack_push(p_stack_t *s,void *item) __preserves_regs(b,c);
extern void p_stack_push_callee(p_stack_t *s,void *item) __preserves_regs(b,c) __z88dk_callee;
#define p_stack_push(a,b) p_stack_push_callee(a,b)


extern size_t p_stack_size(p_stack_t *s) __preserves_regs(b,c);
extern size_t p_stack_size_fastcall(p_stack_t *s) __preserves_regs(b,c) __z88dk_fastcall;
#define p_stack_size(a) p_stack_size_fastcall(a)


extern void *p_stack_top(p_stack_t *s) __preserves_regs(b,c,d,e);
extern void *p_stack_top_fastcall(p_stack_t *s) __preserves_regs(b,c,d,e) __z88dk_fastcall;
#define p_stack_top(a) p_stack_top_fastcall(a)



#endif
