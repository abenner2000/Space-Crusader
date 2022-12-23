// Author: Andrew Benner, andrewbenner918@gmail.com
// Function protoypes for ADC_Ain1 driver

#ifndef ADC_AIN1_H
#define ADC_AIN1_H

#include <stdbool.h>
#include <stdint.h>

void ADC0_InitSWTriggerSeq3_Ain1(void);
uint16_t ADC_InSeq3(void);

#endif
