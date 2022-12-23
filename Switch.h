// Author: Andrew Benner, andrewbenner918@gmail.com
// Declarations for Switch driver

#ifndef SWITCH_H
#define SWITCH_H

#define DEBOUNCE_TIME_MS 5
#define LONG_PRESS_TIME_MS 90000

#include <stdbool.h>
#include <stdint.h>

typedef enum{NONE,SHORTP,LONGP}press_t;

void Switch_Init(void);
_Bool sw1_Press(void);
_Bool sw2_Press(void);
press_t sw1_check_fsm(void);
press_t sw2_check_fsm(void);

#endif
