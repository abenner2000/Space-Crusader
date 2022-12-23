// Author: Andrew Benner, andrewbenner918@gmail.com
// Function protoypes for Timer2 driver

#ifndef TIMER2_H
#define TIMER2_H

#include <stdbool.h>
#include <stdint.h>

void Timer2A_Init(uint32_t period);
void Timer2A_Handler(void);

void Sound_Init(uint16_t period);
void Sound_Play(const unsigned char *pt, unsigned long count);

void Timer2A_Stop(void);
void Timer2A_Start(void);

#endif
