#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

//DELUPPGIFT 2: LÄS AV DIGITALINGÅNG
#define KeyRead 0                     //pin 8 from PORTB
int stateChange = 0;                 // variable to store the statechange of the switch
volatile static int flag = 0;


void main (void) {
	
    sei();                   //globaly enables interrupts
	DDRB |= (1<< KeyRead);  //set switch pin 8 as output
	uart_init();
	timer_init();

    	
	while (1) {
		
	  if(flag)
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
	       }
    } 
}

//Interrupt for Uppgift 2

ISR (TIMER0_COMPA_vect){    //Interrupt occours on time compare match .i.e., counting up till 156

	flag = 1;               //set flag.     

}


	
