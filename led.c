#include <avr/io.h>
#include "led.h"

static int TimeVariable = 0; //variable for blink function
static int counter = 0;		 //variable for led rampling  function

void LED_init_Blink()
{
	//static int TimeVariable = 0;

	if (TIFR0 & (1 << OCF0A)) // Interrupt Flag Register
	{
		TimeVariable++; //increment TimeVariable

		TIFR0 |= (1 << OCF0A); // OCF0A is cleared by writing a logic one to the flag.
	}

	if (TimeVariable > 100) //check if variable reached 10 then enter loop
	{
		if (PORTB) //if pin is set to 1
		{
			OCR0A = 0;
		}
		else
			OCR0A = 255;
		PORTB ^= (1 << LED_PIN); //toggle/blink the led
		TimeVariable = 0;		 //reset the variable to 0
	}
}

void LED_Off()
{
	OCR0A = 255;
	PORTB = (1 << LED_PIN);
}

uint8_t simple_ramp()
{
	//static int counter = 0;
	counter++;
	if (counter >= 255) //for 10 milliseconds the counter counts upto 156
	{
		counter = 0;
		return counter;
	}
	else
		return counter;
}
