/*
Interface 2x2 KeyPad. KeyPad customized using 4 push buttons. Also Interface 4 LEDs.

4 LEDs are connected on PortB:
PB0 - LED0
PB1 - LED1
PB2 - LED2
PB3 - LED3

2x2 KeyPad is connected on PortC:
PC0 - ROW0
PC1 - ROW1
PC2 - COL0
PC3 - COL2


Aim: Its a 4 PushButton keypad. When PushButton1(1st ROW 1st COLUMN) is pressed LED1 is ON.
								When PushButton2(1st ROW 2nd COLUMN) is pressed LED2 is ON.
								When PushButton3(2nd ROW 1st COLUMN) is pressed LED3 is ON.
								When PushButton2(2nd ROW 2nd COLUMN) is pressed LED4 is ON.
								
Program Logic:
First make the COLUMN0 line as LOW and COLUMN1 line as HIGH.
Then check the OUTPUT signal on both ROW0 and ROW1

Then, make the COLUMN0 line as HIGH and COLUMN1 line as LOW.
Then check the OUTPUT signal on both ROW0 and ROW1

Note: The strange think is for both conditions the value on ROW0 and ROW1 are same


*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	uint8_t kp;
	DDRB = 0xff; //PortB all pins as OUTPUTS for LEDs
	//PORTB &= ~(1<<0);	//
	DDRC = 0b00001100;	//Make 
	DDRC &= ~((1<<0)|(1<<1));	 //Make the PC0, PC1 pins as INPUTS for ROWS1,2
	DDRC |= ((1<<2)|(1<<3)); //Make the PC2,PC3 pins as OUTPUTS for COLUMNS1,2
	
	while (1)
	{
		PORTC &= ~(1<<2);
		PORTC |= (1<<3);
		kp = (PINC & 0x03);
		//if((PINC & (1<<0))==0)
		if(kp==0x02)
		PORTB |= (1<<0);
		else
		if(kp==0x01)
		PORTB |= (1<<2);
		else;
		
		_delay_ms(200);
		
		PORTC &= ~(1<<3);
		PORTC |= (1<<2);
		kp = (PINC & 0x03);
		if(kp == 0x02)
		PORTB |= (1<<1);
		else
		if(kp == 0x01)
		PORTB |= (1<<3);
		else;
	}
	PORTB &= ~(1<<0)|(1<<1)|(1<<2)|(1<<3);
}