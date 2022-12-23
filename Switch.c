// Author: Andrew Benner, andrewbenner918@gmail.com
// Function definitions for Switches

#include "tm4c123gh6pm.h"
#include "Switch.h"
#include <stdbool.h>
#include <stdint.h>

void Switch_Init(void){
	GPIO_PORTE_DIR_R &= ~0x03;    // PE0-1 input
	GPIO_PORTE_AFSEL_R &= ~0x03;  // Disable PE0-1 alternate function
	GPIO_PORTE_DEN_R |= 0x03;    // PE0-1 enable digital I/O
	GPIO_PORTE_AMSEL_R &= ~0x03;  // PE0-1 disable analog I/O
	GPIO_PORTE_PUR_R |= 0x03;     // Enable pull up resistors PE0-1 (no more external resistors needed for switches)
}

_Bool sw1_Press(void){
	if((GPIO_PORTE_DATA_R & 0x01) != 0){ //check if PB5 is pressed
		return true;
	}
	else{
		return false;
	}
}

_Bool sw2_Press(void){
	if((GPIO_PORTE_DATA_R & 0x02) != 0){ //check if PB6 is pressed
		return true;
	}
	else{
		return false;
	}
}

press_t sw1_check_fsm()
{
	static uint32_t switch_time = 0;
	static enum {ST_NO_PRESS, ST_DEBOUNCE_PRESS, ST_PRESS,
		ST_LONG_PRESS, ST_DEBOUNCE_RELEASE} sw_state=ST_NO_PRESS;

	switch_time++;

	switch(sw_state){
	 default:
	 case ST_NO_PRESS:
		 if( sw1_Press() )
		 {
			 switch_time = 0;
			 sw_state = ST_DEBOUNCE_PRESS;
		 }
		 break;
	 case ST_DEBOUNCE_PRESS:
		 if(!(sw1_Press()))
			 sw_state = ST_NO_PRESS;
		 else if( switch_time >= DEBOUNCE_TIME_MS )
			 sw_state = ST_PRESS;
		 break;
	 case ST_PRESS:
		 if(!(sw1_Press()))
		 {
			 switch_time = 0;
			 sw_state = ST_DEBOUNCE_RELEASE;
			 return SHORTP;
		 }
		 else if( switch_time >= LONG_PRESS_TIME_MS )
			 sw_state = ST_LONG_PRESS;
		 break;
	 case ST_LONG_PRESS :
		 if(!(sw1_Press()))
		 {
			 switch_time = 0;
			 sw_state = ST_DEBOUNCE_RELEASE;
			 return LONGP;
		 }
		 break;
	 case ST_DEBOUNCE_RELEASE:
		 if( switch_time >= DEBOUNCE_TIME_MS )
			 sw_state = ST_NO_PRESS;
		 break;
	}
	return NONE;
}

press_t sw2_check_fsm()
{
	static uint32_t switch_time = 0;
	static enum {ST_NO_PRESS, ST_DEBOUNCE_PRESS, ST_PRESS,
		ST_LONG_PRESS, ST_DEBOUNCE_RELEASE} sw_state=ST_NO_PRESS;

	switch_time++;

	switch(sw_state){
	 default:
	 case ST_NO_PRESS:
		 if( sw2_Press() )
		 {
			 switch_time = 0;
			 sw_state = ST_DEBOUNCE_PRESS;
		 }
		 break;
	 case ST_DEBOUNCE_PRESS:
		 if(!(sw2_Press()))
			 sw_state = ST_NO_PRESS;
		 else if( switch_time >= DEBOUNCE_TIME_MS )
			 sw_state = ST_PRESS;
		 break;
	 case ST_PRESS:
		 if(!(sw2_Press()))
		 {
			 switch_time = 0;
			 sw_state = ST_DEBOUNCE_RELEASE;
			 return SHORTP;
		 }
		 else if( switch_time >= LONG_PRESS_TIME_MS )
			 sw_state = ST_LONG_PRESS;
		 break;
	 case ST_LONG_PRESS :
		 if(!(sw2_Press()))
		 {
			 switch_time = 0;
			 sw_state = ST_DEBOUNCE_RELEASE;
			 return LONGP;
		 }
		 break;
	 case ST_DEBOUNCE_RELEASE:
		 if( switch_time >= DEBOUNCE_TIME_MS )
			 sw_state = ST_NO_PRESS;
		 break;
	}
	return NONE;
}
