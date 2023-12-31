/*
 * main.c
 *
 *  Created on: Nov 19, 2023
 *      Author: medoa
 */

#include"Bit_Math.h"	
#include"Dio.h"
#include"Timer0.h"
#include"Std_Types.h"

u16 X=0,Y=0, Z=0;
int main()
{
	Lcd_Init();
	Lcd_Start();
	Dio_ConfigChannel(DIO_PORTD, DIO_PIN6, INPUT);
	u16 ICR = ((TIMER1_ICR1H_REG <<8) | (TIMER1_ICR1L_REG));
	u16 TCNT= ((TIMER1_TCNT1H_REG<<8) | (TIMER1_TCNT1L_REG));
	SET_BIT(TIMER0_TIFR_REG, 5);	// Clear input capture flag
	while(1){
		TCNT = 0;
		TIMER1_TCCR1A_REG = 0;
		//  Capture Rising Edge
		TIMER1_TCCR1B_REG = 0x41;	// Capture in Rising, No Prescaler
		while(!(CHK_BIT(TIMER0_TIFR_REG, 5)));
		X = ICR;		// Store The First Value
		SET_BIT(TIMER0_TIFR_REG, 5);

		//  Capture Falling Edge
		TIMER1_TCCR1B_REG = 0x01;	// Capture in Falling, No  Prescaler
		while(!(CHK_BIT(TIMER0_TIFR_REG, 5)));
		Y = ICR;		// Store The second Value
		SET_BIT(TIMER0_TIFR_REG, 5);

		// Capture Rising Edge
		TIMER1_TCCR1B_REG = 0x41;	// Capture in Rising, No Prescaler
		while(!(CHK_BIT(TIMER0_TIFR_REG, 5)));
		Z = ICR;		// Store The First Value
		SET_BIT(TIMER0_TIFR_REG, 5);

		// Stop The Timer 
		TIMER1_TCCR1B_REG = 0;
		Update_Data();
		PWM_Drawer();
	}
	return 0;
}


void Lcd_Start()
{
	Lcd_Cmd(_LCD_CLEAR);			// to clrear lcd
	Lcd_Goto_Row_Column(0, 0);		// Start From Begin
	Lcd_DisplayStr("f-");
	Lcd_Goto_Row_Column(0, 6);
	Lcd_DisplayStr("t-");
	Lcd_Goto_Row_Column(0, 12);
	Lcd_DisplayStr("d-");
}

void Update_Data()
{
	int timer = Z-X;
	int freq = (16000000/timer)/1000;			// Calculate frequency
	int dutycycle = (u16)((Y-X)*100)/timer;	// Calculate Duty Cycle
	Lcd_Goto_Row_Column(0, 2);          // put freq and timer and duty on the top of lcd
	Lcd_DisplayNum(freq);
	Lcd_Goto_Row_Column(0, 8);
	Lcd_DisplayNum(timer);
	Lcd_Goto_Row_Column(0, 14);
	Lcd_Display2Num(dutycycle);
}

void PWM_Drawer()
{
// draw the pwm on the button of the lcd
	int duty = (((Y-X)*100)/(Z-X)); 
	int get_up = (duty*8)/100;
	int loop =0;
	int get_down = 8-get_up;
	Lcd_Goto_Row_Column(1, 0);
	while(loop<4){
		Lcd_DisplayChr(0);
		for(int up=1; up<get_up; up++)
			Lcd_DisplayChr(1);
		Lcd_DisplayChr(2);
		for(int down=1; down<get_down; down++)
			Lcd_DisplayChr(3);
		loop++;
	}
}
