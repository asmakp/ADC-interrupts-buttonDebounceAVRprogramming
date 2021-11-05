#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "adc.h"

//DELUPPGIFT 2: LÄS AV DIGITALINGÅNG
//#define KeyRead 0                     //pin 8 from PORTB
//int stateChange = 0;                 // variable to store the statechange of the switch
//volatile static int flag = 0;



//DELUPPGIFT 3: Read voltage with help of ADC
volatile int flag = 0;
volatile uint8_t pot_val = 0; ///To read the value from the data register the MSB bits ADCH
//void ADC_init(void);


void main (void) {

	sei(); //globaly enables interrupts


	//Uppgift 3 .Potentiometer
	DDRD |= (1<<LED_PIN_PWM);   
	DDRC &= ~(1<<analog_read); //analog pin A0 set as input
	ADC_init();
	timer2_init();

    
	//Uppgift 2 switch
	//DDRB |= (1<< KeyRead);  //set switch pin 8 as output
	//uart_init();
	//timer_init();

    	
	while (1) {
		
	 /* if(flag)
		   {
			if((PINB & (1<<KeyRead)) == 1  && stateChange == 0){ //If switch is pressed enter loop
					stateChange = 1;
					printf_P(PSTR("pushed\r\n"));
					flag = 0;
			}
			else  if((PINB & (1<<KeyRead)) == 1  && stateChange == 1) {
				 flag = 0;
                      
				}
				else if((PINB & (1<<KeyRead)) == 0  && stateChange == 1){
				 printf_P(PSTR("released\r\n"));
					   stateChange = 0;
					   flag = 0;
			       }
	       }*/
    } 
}

//Interrupt for Uppgift 3

ISR(ADC_vect)

{
	
	pot_val = ADCH; //Register storing MSB bits (8 bits)
}

ISR(TIMER2_COMPA_vect){
	
	ADCSRA  |= (1<< ADSC ) ; //start conversion
	
    OCR0A = pot_val;  // store potval in time compare register
	
}

//Interrupt for Uppgift 2

/*ISR (TIMER0_COMPA_vect){    //Interrupt occours on time compare match .i.e., counting up till 156

	flag = 1;               //set flag.     

}*/


	
