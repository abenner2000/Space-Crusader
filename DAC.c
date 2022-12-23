// Author: Andrew Benner, andrewbenner918@gmail.com
// Function definitions for DAC.

#include "tm4c123gh6pm.h"
#include "DAC.h"
#include <stdbool.h>
#include <stdint.h>

void DAC_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000002; // clock for PortB
	delay = SYSCTL_RCGC2_R;       // allow time for clock to stabilize
	GPIO_PORTB_DIR_R |= 0x0F;     // PB0-3 input
	GPIO_PORTB_AFSEL_R &= ~0x0F;  // Disable PB0-3 alternate function
	GPIO_PORTB_DEN_R |= 0x0F;     // PB0-3 enable digital I/O
	GPIO_PORTB_AMSEL_R &= ~0x0F;  // PB0-3 disable analog I/O
}

void DAC_Out(unsigned long data){
	GPIO_PORTB_DATA_R = data;
}
