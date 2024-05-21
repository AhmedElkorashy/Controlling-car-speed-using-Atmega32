/*
 * main.c
 *
 *  Created on: Mar 31, 2024
 *      Author: User
 */

#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "TIMERS_Interface.h"
#include "TIMERS_Private.h"
#include <util/delay.h>
u8 Car[] = {
		0x1F,
		0x1F,
		0x1F,
		0x1F,
		0x1F,
		0x1F,
		0x1F,
		0x1F
};
u8 Wheel_1[] = {
		0x01,
		0x03,
		0x03,
		0x03,
		0x03,
		0x1F,
		0x1F,
		0x0E
};
u8  Wheel_2[] = {
		0x10,
		0x18,
		0x18,
		0x18,
		0x18,
		0x1F,
		0x1F,
		0x0E
};

int main()
{
	LCD_voidInit();
	TIMER0_voidInit();
	LCD_voidSendString((u8*)"Hello ! Fast & Furious 10:");
	LCD_voidSendCustomCharacter(Car,0,1,0);

	LCD_voidSendCustomCharacter(Car,0,1,39);
	LCD_voidSendCustomCharacter(Wheel_1,1,1,2);
	LCD_voidSendCustomCharacter(Wheel_2,2,1,3);
	_delay_ms(3000);
	DIO_u8SetPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT);
	int i;
	for(i=2;i<39;i++)
	{
		if(i<=10 || (i>=33 && i<=36))
		{
			TIMER0_voidSetFastPWM(32);
			LCD_voidSetPosition(0,0);
			LCD_voidSendString((u8*)"Car Speed : Low           ");
			LCD_voidSendCustomCharacter(Wheel_1,1,1,i);
			LCD_voidSendCustomCharacter(Wheel_2,2,1,i+1);
			_delay_ms(400);
			LCD_voidSetPosition(1,i);
			LCD_voidSendString((u8*)"  ");
			if(i==36)
			{
				TIMER0_voidSetFastPWM(0);
				DIO_u8SetPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_INPUT);
			}
		}
		if(i>=11 && i<=21)
		{
			TIMER0_voidSetFastPWM(128);
			LCD_voidSetPosition(0,0);
			LCD_voidSendString((u8*)"Car Speed : Medium");
			LCD_voidSendCustomCharacter(Wheel_1,1,1,i);

			LCD_voidSendCustomCharacter(Wheel_2,2,1,i+1);
			_delay_ms(100);
			LCD_voidSetPosition(1,i);
			LCD_voidSendString((u8*)"  ");
		}
		if(i>=22 && i<=32)
		{
			TIMER0_voidSetFastPWM(255);
			LCD_voidSetPosition(0,0);
			LCD_voidSendString((u8*)"Car Speed : High  ");
			LCD_voidSetPosition(1,i);
			LCD_voidSendCustomCharacter(Wheel_1,1,1,i);
			LCD_voidSendCustomCharacter(Wheel_2,2,1,i+1);
			_delay_ms(50);
			LCD_voidSetPosition(1,i);
			LCD_voidSendString((u8*)"  ");
		}
	}
	LCD_voidSendCustomCharacter(Wheel_1,1,1,36);
	LCD_voidSendCustomCharacter(Wheel_2,2,1,37);

	while(1)
	{
	}

}
