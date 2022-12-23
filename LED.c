// Author: Andrew Benner, andrewbenner918@gmail.com
// Function definitions for LEDs

#include "tm4c123gh6pm.h"
#include "LED.h"
#include <stdint.h>

void LED_Init(void){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000010; // clock for PortE
	delay = SYSCTL_RCGC2_R;       // allow time for clock to stabilize
	GPIO_PORTE_DIR_R |= 0x08;    // PE3 output
	GPIO_PORTE_AFSEL_R &= ~0x08;  // Disable PE3 alternate function
	GPIO_PORTE_DEN_R |= 0x08;    // PE3 enable digital I/O
	GPIO_PORTE_AMSEL_R &= ~0x08;  // PE3 disable analog I/O
}

void LED_On(void){
	GPIO_PORTE_DATA_R |= 0x08;
}

void LED_Off(void){
	GPIO_PORTE_DATA_R &= ~0x08;
}

void LED_Toggle(void){
	GPIO_PORTE_DATA_R ^= 0x08;
}
