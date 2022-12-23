// Author: Andrew Benner, andrewbenner918@gmail.com
// Function protoypes for DAC driver

#ifndef DAC_H
#define DAC_H

#include <stdbool.h>
#include <stdint.h>

void DAC_Init(void);
void DAC_Out(unsigned long data);

#endif
