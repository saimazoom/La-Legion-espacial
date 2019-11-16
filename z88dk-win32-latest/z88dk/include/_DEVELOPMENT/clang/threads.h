
// automatically generated by m4 from headers in proto subdir


#ifndef _THREADS_H
#define _THREADS_H

#include <stdint.h>

// DATA STRUCTURES

typedef struct mtx_s
{

   uint8_t thrd_owner;
   uint8_t mutex_type;
   uint8_t lock_count;
   
   uint8_t spinlock;
   void   *q;             // p_forward_list *

} mtx_t;

typedef uint16_t       once_flag;
#define ONCE_FLAG_INIT 0x00fe

// mutex

extern void call_once(once_flag *flag,void *func);


extern void mtx_destroy(mtx_t *m);


extern int mtx_init(mtx_t *m,int type);


extern int mtx_lock(mtx_t *m);


extern int mtx_timedlock(mtx_t *m,struct timespec *ts);


extern int mtx_trylock(mtx_t *m);


extern int mtx_unlock(mtx_t *m);


extern void spinlock_acquire(char *spinlock);


extern void spinlock_release(char *spinlock);


extern int spinlock_tryacquire(char *spinlock);



#endif
