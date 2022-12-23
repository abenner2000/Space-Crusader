// Author: Andrew Benner, andrewbenner918@gmail.com
// Function definitions for ADC_Ain1 to read slide pot.

#include "tm4c123gh6pm.h"
#include "ADC_Ain1.h"
#include <stdbool.h>
#include <stdint.h>

void ADC0_InitSWTriggerSeq3_Ain1(void){
	volatile unsigned long delay;
	GPIO_PORTE_DIR_R &= ~0x04;    // PE2 input
	GPIO_PORTE_AFSEL_R |= 0x04;   // Enable PE2 alternate function
	GPIO_PORTE_DEN_R &= ~0x04;    // PE2 disable digital I/O
	GPIO_PORTE_AMSEL_R |= 0x04;   // PE2 enable analog I/O
	SYSCTL_RCGC0_R |= 0x00010000; // Activate ADC0
	delay = SYSCTL_RCGC0_R; 
	SYSCTL_RCGC0_R &= ~0x00000300;// Configure for 125k
	ADC0_SSPRI_R = 0x0123;        // Sequencer 3 highest priority
	ADC0_ACTSS_R &= ~0x0008;      // Disable Seq3
	ADC0_EMUX_R &= ~0xF000;       // software trigger for Seq3
	ADC0_SSMUX3_R &= ~0x000F;     // clear SS3 field
	ADC0_SSMUX3_R += 1;           // set channel Ain1
	ADC0_SSCTL3_R = 0x0006;       // no TS0 D0, yes IE0 END0
	ADC0_ACTSS_R |= 0x0008;       // Enable Seq3
}

uint16_t ADC_InSeq3(void){
	uint16_t result;
	ADC0_PSSI_R = 0x0008;         // Initiate SS3
	while((ADC0_RIS_R&0x08)==0){};// wait for conversion
	result = ADC0_SSFIFO3_R&0xFFF;// read result
	ADC0_ISC_R = 0x0008;          // set acknowledge flag
	return result;
}
