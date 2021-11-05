#include <avr/io.h>

#include "timer.h"

void timer_init() {
	
	TCCR0A = (1<<WGM01 ) | (0<<WGM00);//select CTC mode in Timer/Counter Control Register.ATmel 42735 Datasheet Ca 19.9.1 page 138
	TCCR0B &= ~(1<<WGM02 ); //select CTC mode,set WGM02 to 0, normal opration, OC0A(PD6) is disconnected

	TIMSK0 = (1<<OCIE0A); //Interrupt Mask Register, Output Compare A Match Interrupt Enable.

	//setting the prescalar to 1024, in Timer/Counter Control Register- this sets the clock.ATmel 42735 datasheet page 141 ,142	
	TCCR0B |= (1<<CS02 ) |(1<<CS00 ) ;
    TCCR0B &= ~(1<<CS01 );
	
    // An 8-bit comparator continuously compares TCNT0 with the Output Compare Registers (OCR0A)
    OCR0A = 156; // f_OCnx = f_clk_i/o / (2*N(1+OCRnx))  //    OCR0A = 16000000HZ/(2*1024*100HZ)

}

void timer_intitPWM(){

	TCCR0A = (1<<COM0A1);    //Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
	TCCR0A &=  ~(1<<COM0A0); //19.9.1. TC0 Control Register A, page 123

	TCCR0A |= (1<<WGM01 ) | (1<<WGM00 ); //sett fast PWM mode TOP as 0XFF , Update of OCR0X at BOTTOM
	TCCR0B &=  ~(1 << WGM02);
     
	//TIMSK0 = (1<<OCIE0A); //Interrupt Mask Register, Output Compare A Match Interrupt Enable


	TCCR0B &= ~(1<<FOC0A ); //set these bits to zero for future device compatibility.
	TCCR0B &= ~(1<<FOC0B );
	  
    TCCR0B |= (1<<CS01) | (1<<CS00); //setting clock  64 prescaler

//	 OCR0A = dutyCycle;
}

void timer2_init(){
	timer_intitPWM();
	//TCCR2A = (1<<COM2A1);    //Clear OC2A on Compare Match, set OC2A at BOTTOM (non-inverting mode)
	//TCCR2A &=  ~(1<<COM2A0); //19.9.1. TC0 Control Register A, page 123

	TCCR2A  |= (1<<WGM21 ) ; //select CTC mode  ATmel 42735 Datasheet Ca 22.11.1 page 203 
	TCCR2A &= ~(1<<WGM20);
    TCCR2B &= ~(1<<WGM22); //select CTC mode,set WGM22 to 0.

	TIMSK2 = (1<<OCIE2A); //

	TCCR2B |= (1<<CS22 ) | (1<<CS21 )|(1<<CS20 ); //select clkI/O/1024 (From prescaler) in order to get a time period of 16ms.
	OCR2A = 156;     // To get a time period of 10ms frequency 100Hz. Calcutated from https://eleccelerator.com/avr-timer-calculator/
}