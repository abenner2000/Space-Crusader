// Author: Andrew Benner, andrewbenner918@gmail.com
// Function definitions for random

#include "random.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

uint16_t rand;

void Random_Init(unsigned long seed){
    rand = seed % 9;
}

unsigned long Random(void){
    return (rand + (rand % 2));
}
unsigned long Random32(void){
    return (rand + (rand % 2));
}
