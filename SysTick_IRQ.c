// Author: Andrew Benner, andrewbenner918@gmail.com
// Function definitions for SysTick to set up interrupts

#include "tm4c123gh6pm.h"
#include "SysTick_IRQ.h"
#include "ADC_Ain1.h"
#include "LED.h"
#include "Nokia5110.h"
#include <stdbool.h>
#include <stdint.h>

_Bool highHealth = true;
_Bool sound = false;
_Bool displayBuffer = false;
uint16_t ledCntr = 0;
uint16_t soundCntr = 0;
uint16_t slideVal = 0;

void SysTick_Init(uint32_t period){ //assuming 16MHz clock
	NVIC_ST_CTRL_R = 0;   			// disable SysTick during setup
	NVIC_ST_RELOAD_R = period-1;// reload value
	NVIC_ST_CURRENT_R = 0;			// any write to current clears
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // priority 2
	
	NVIC_ST_CTRL_R = 0x07;      // enable SysTick with core clock and interrupts
}

void SysTick_Handler(void){
	slideVal = ADC_InSeq3(); // Check Slide Pot. value (PE2)
	displayBuffer = true;
}
