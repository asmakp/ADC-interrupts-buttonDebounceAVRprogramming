#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "timer.h"
#include "led.h"
#include "serial.h"
#include "adc.h"

//DELUPPGIFT 2: LÄS AV DIGITALINGÅNG
//#define Key1 0		 //pin 8 from PORTB
//int CurrentKeyState = 0; // variable to store the statechange of the switch
//int PreviousKeyState = 0;
//volatile static int flag = 0;

//DELUPPGIFT 3: Read voltage with help of ADC
//volatile int flag = 0;
//volatile uint8_t pot_val = 0; ///To read the value from the data register the MSB bits ADCH
//void ADC_init(void);

//DELUPPGIFT 4(VG) :ANVÄNDARSTYRT BETEENDE
#define Key1 0 //pin 8 from PORTB

int CurrentKeyState = 0; // variable to store the statechange of the switch
int PreviousKeyState = 0;
volatile static int flag = 0; //interrupt variable
int choice = 0;				  //variable for switch case

volatile uint8_t pot_val = 0; //To read the value from the data register the MSB bits ADCH

volatile int ADC_flag = 0; //flag variable on timer2 compare match.

void main(void)
{

	sei(); //globaly enables interrupts

	//------Uppgift 3 .Potentiometer----------
	//DDRD |= (1<<LED_PIN_PWM);
	//DDRC &= ~(1<<analog_read); //analog pin A0 set as input
	//ADC_init();
	//timer2_init();

	//------Uppgift 2 switch-----------
	//DDRB |= (1 << Key1); //set switch pin 8 as output
	//uart_init();
	//timer_init();

	//-------Uppgift 4 switch choice------------
	DDRB |= (1 << Key1); //set switch pin 8 as output. pin defined in adc.h
	DDRB |= (1 << LED_PIN);
	DDRC &= ~(1 << analog_read);
	uart_init();
	ADC_init();
	timer2_init();

	while (1)
	{

		//Uppgift 2 switch
		/*
		if (flag)
		{
			if ((PINB & (1 << Key1)) == 1 && PreviousKeyState == 0) //If switch is pressed enter loop 
			{ 
				PreviousKeyState = 1;
				CurrentKeyState = 0;
				printf_P(PSTR("pushed\r\n"));
			}

			else if ((PINB & (1 << Key1)) == 0 && (PreviousKeyState != CurrentState))
			{
				printf_P(PSTR("released\r\n"));
				PreviousKeyState = 0;
			}
			flag = 0;
		}*/

		//LABB VG PART
		if (flag)
		{
			if ((PINB & (1 << Key1)) == 1 && PreviousKeyState == 0) //If switch is pressed enter loop
			{
				PreviousKeyState = 1;
				CurrentKeyState = 0;
				choice++;
				printf_P(PSTR("pushed\r\n"));
				if (choice == 4)
				{
					choice = 1;
				}
			}

			else if ((PINB & (1 << Key1)) == 0 && (PreviousKeyState != CurrentKeyState))
			{
				//printf_P(PSTR("released\r\n"));
				PreviousKeyState = 0;
			}
			flag = 0;
		}

		switch (choice)
		{

		case 1:
			PORTB &= ~(1 << LED_PIN); //On the LED, so that function works after case 3
			OCR0A = pot_val;		  //store potval in time compare register
			break;

		case 2:
			if (flag)
			{
				LED_init_Blink();
				flag = 0;
			}
			break;

		case 3:
			LED_Off();
			break;

		default:
			if (flag)
			{
				PORTB &= ~(1 << LED_PIN);
				OCR0A = simple_ramp(); //function in  defined in led.c
				flag = 0;
			}
		}
	}
}

//Interrupt for Uppgift 3
/*
ISR(ADC_vect)

{
	
	pot_val = ADCH; //Register storing MSB bits (8 bits)
}

ISR(TIMER2_COMPA_vect){
	
	ADCSRA  |= (1<< ADSC ) ; //start conversion
	
    OCR0A = pot_val;  // store potval in time compare register
	
}*/

//Interrupt for Uppgift 2
/*
ISR(TIMER0_COMPA_vect)
{ //Interrupt occours on time compare match .i.e., counting up till 156

	flag = 1; //set flag.
	
}*/

//interrupt for upgift 4
ISR(ADC_vect)

{

	pot_val = ADCH; //Register storing MSB bits (8 bits)
}

ISR(TIMER2_COMPA_vect)
{
	flag = 1;

	ADCSRA |= (1 << ADSC); //start conversion
}
