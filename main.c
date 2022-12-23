// Author: Andrew Benner, andrewbenner918@gmail.com
// Date: July 21, 2022

// Current Stack Size is 10240 for sprintf. Was previously 512.
// Handheld Video Game using SSI Nokia 3310 LCD Graphic Display
// PA2 SSI0Clk, PA3 SSI0Fss, PA4 SSI0Rx, PA5 SSI0Tx, PA6 D/C, PA7 RST
// PE0 Sw1, PE1 Sw2, PE2 Slide Pot, PE3 LED, PB0-3 for 4-bit DAC

// Runs on LM4F120 or TM4C123 Launchpad

// Include drivers and libraries
#include "ADC_Ain1.h"
#include "SysTick_IRQ.h"
#include "Switch.h"
#include "LED.h"
#include "DAC.h"
#include "Sound.h"
#include "Timer2.h"
#include "Nokia5110.h"
#include "Game_Functions.h"
#include "random.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
	
// Main function
int main(void){
	// Variable initializations
	static enum {ST_HOME,ST_LEVEL1,ST_LEVEL2,ST_LEVEL3,ST_END} state=ST_HOME;
	press_t sw1;
	press_t sw2;
	
	// Driver initializations
	SysTick_Init(528000);          // SysTick 33ms period (30 Hz)
	LED_Init();                    // First init because initializes RCGC2 for PortE
	Switch_Init();
	ADC0_InitSWTriggerSeq3_Ain1();
	Nokia5110_Init();
	Sound_Init(1500);              //DAC and Timer2A (after Nokia init) are initialized here
	Timer2A_Stop();
	
	// Initial LCD Display
	Nokia5110_Clear();
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	
	// Main while loop
	while(1){
		sw1 = sw1_check_fsm();     // Check sw1 (PE0 status)
		sw2 = sw2_check_fsm();     // Check sw2 (PE1 status)
		
		switch(state)
		{
			case ST_HOME:
				Game_HomeSetup();
			
				if(sw1 == SHORTP){
					Sound_Shoot();
					Game_Level1Setup();
					Game_Level1Draw();
					state = ST_LEVEL1;
				}
				
				break;
			case ST_LEVEL1:
				if(displayBuffer == true){
					Game_Level1Draw();
				}
				
				Game_PlayerMove(slideVal);
				Game_Level1EnemyMove();
				Game_Level1CheckHit();
				
				if(Game_Level1CheckWin() == true){
					Nokia5110_ClearBuffer();
					Nokia5110_DisplayBuffer();
					Game_Level2Setup();
					Game_Level2Draw();
					state = ST_LEVEL2;
				}
				
				if(Game_Level1CheckLose() == true){
					Nokia5110_ClearBuffer();
					Nokia5110_DisplayBuffer();
					Game_CalcScore();
					state = ST_END;
				}
				
				if(sw1 == SHORTP){
					Game_LaserShoot();
				}
				else if(sw2 == SHORTP){
					Game_MissileShoot();
				}
				
				break;
			case ST_LEVEL2:
				if(displayBuffer == true){
					Game_Level2Draw();
				}
				
				Game_PlayerMove(slideVal);
				Game_Level2EnemyMove();
				Game_Level2CheckHit();
				
				if(Game_Level2CheckWin() == true){
					Nokia5110_ClearBuffer();
					Nokia5110_DisplayBuffer();
					Game_Level3Setup();
					Game_Level3Draw();
					state = ST_LEVEL3;
				}
				
				if(Game_Level2CheckLose() == true){
					Nokia5110_ClearBuffer();
					Nokia5110_DisplayBuffer();
					Game_CalcScore();
					state = ST_END;
				}
				
				if(sw1 == SHORTP){
					Game_LaserShoot();
				}
				else if(sw2 == SHORTP){
					Game_MissileShoot();
				}
				
				break;
			case ST_LEVEL3:
				if(displayBuffer == true){
					Game_Level3Draw();
				}
				
				Game_PlayerMove(slideVal);
				Game_Level3EnemyMove();
				Game_Level3CheckHit();
				
				if(Game_Level3CheckWin() == true){
					Nokia5110_ClearBuffer();
					Nokia5110_DisplayBuffer();
					Game_Level1Setup();
					Game_Level1Draw();
					state = ST_LEVEL1;
				}
				
				if(Game_Level3CheckLose() == true){
					Nokia5110_ClearBuffer();
					Nokia5110_DisplayBuffer();
					Game_CalcScore();
					state = ST_END;
				}
				
				if(sw1 == SHORTP){
					Game_LaserShoot();
				}
				else if(sw2 == SHORTP){
					Game_MissileShoot();
				}
				
				break;
			case ST_END:
				Game_EndScreen();
			
				if(sw1 == SHORTP){
					Nokia5110_Clear();
					Game_HomeSetup();
					state = ST_HOME;
				}
				
				break;
		}
	}
}
