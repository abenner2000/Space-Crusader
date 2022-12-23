// Author: Andrew Benner, andrewbenner918@gmail.com
// Function definitions for Timer2 and handlers

#include "tm4c123gh6pm.h"
#include "DAC.h"
#include "Sound.h"
#include "Timer2.h"
#include "LED.h"
#include <stdbool.h>
#include <stdint.h>

unsigned long Index = 0;
const unsigned char *Wave;
unsigned long Count = 0;
uint32_t ledCnt = 0;

void Timer2A_Init(uint32_t period){
	unsigned long volatile delay;
	SYSCTL_RCGCTIMER_R |= 0x04; //activate timer2
	delay = SYSCTL_RCGCTIMER_R;
	TIMER2_CTL_R = 0x00;       // disable timer2a during setup
	TIMER2_CFG_R = 0x00;       // configure for 32 bit mode
	TIMER2_TAMR_R = 0x02;      // configure for periodic mode
	TIMER2_TAILR_R = period - 1; // reload value
	TIMER2_TAPR_R = 0;         // clock resolution
	TIMER2_ICR_R = 0x01;       // clear timer2a timeout flag
	TIMER2_IMR_R = 0x01;       // arm interrupt
	NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // priority 4
	NVIC_EN0_R = (1<<23);      //enable IRQ 23
	TIMER2_CTL_R |= 0x01;      //enable Timer2A
}

void Timer2A_Handler(void){ 
	TIMER2_ICR_R = 0x01;
	
	// Conditional to toggle LED at a slower rate than interrupt rate
	if(ledCnt < 500){
		ledCnt++;
	}
	else{
		ledCnt = 0;
		LED_Toggle();
	}
	
	// Conditional to play sound data structues from Sound.c
	if(Count){
    DAC_Out(Wave[Index]>>4);
    Index = Index + 1;
    Count = Count - 1;
  }
	else{
		Timer2A_Stop();           // Disable Timer2A to stop sound
		LED_Off();                // Turn off LED after stopping sound
  }
	
}

void Sound_Init(uint16_t period){
  DAC_Init();           // initialized in main
  Timer2A_Init(period);     // ~11 kHz
  Index = 0;
  Count = 0;
}
void Sound_Play(const unsigned char *pt, unsigned long count){
  Wave = pt;
  Index = 0;
  Count = count;
  Timer2A_Start();
}

void Timer2A_Stop(void){
	TIMER2_CTL_R &= ~0x01;
}

void Timer2A_Start(void){
	TIMER2_CTL_R |= 0x01;
}
