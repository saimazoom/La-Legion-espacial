
// automatically generated by m4 from headers in proto subdir


#ifndef _INPUT_SMS_H
#define _INPUT_SMS_H

#include <stdint.h>

///////////
// keyboard
///////////

extern uint16_t in_pause(uint16_t dur_ms);


extern int in_test_key(void);


extern void in_wait_key(void);


extern void in_wait_nokey(void);



////////////
// joysticks
////////////

extern uint16_t in_stick_1(void);


extern uint16_t in_stick_2(void);



#endif
