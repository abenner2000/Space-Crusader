// Author: Andrew Benner, andrewbenner918@gmail.com
// Declarations for SysTick_IRQ driver

#ifndef SYSTICK_IRQ_H
#define SYSTICK_IRQ_H

#include <stdbool.h>
#include <stdint.h>

extern _Bool highHealth;
extern _Bool sound;
extern _Bool displayBuffer;
extern uint16_t ledCntr;
extern uint16_t soundCntr;
extern uint16_t slideVal;

void EnableInterrupts(void);

void SysTick_Init(uint32_t period);
void SysTick_Handler(void);

#endif
