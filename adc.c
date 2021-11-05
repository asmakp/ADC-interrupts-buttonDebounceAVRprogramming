#include <avr/io.h>

#include "adc.h"

void ADC_init()
{
    //  DELUPPGIFT 3: Read voltage with help of ADC
    //ADC Control and Status Register A
    //ADEN: ADC Enable Writing this bit to one enables the ADC.
    //ADSC : ADC Start Conversion In Single Conversion mode, write this bit to one to start each conversion.
    //ADIF: ADC Interrupt Flag This bit is set when an ADC conversion completes and the Data Registers are updated.
    //ADIE: ADC Interrupt Enable When this bit is written to one , the ADC Conversion Complete Interrupt is activated.
    //ADPSn: ADC Prescaler Select,the 2 bits determine the division factor between the system clock frequency
    //and the input clock to the ADC. ( 0 1 1  = prescalar 8)

    ADCSRA = (1 << ADEN) | (1 << ADIE);
    //ADCSRA |=(1<< ADIF ) ; have a little doubt this
    ADCSRA |= (1 << ADSC);

    ADCSRA &= ~(1 << ADPS2);
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0);

    DIDR0 = (1 << ADC0D); //Digital Input Disable Register 0 set to logic one, the buffer on the corresponding ADC pin is disabled.

    ADMUX = (1 << REFS0);   //REFSn: Reference Selection,These bits select the voltage reference for the ADC.
    ADMUX &= ~(1 << REFS1); // we select AVcc the supply voltage 5V.

    ADMUX |= (1 << ADLAR); //ADLAR: ADC Left Adjust - to left adjust the result the ADC Data Register.
                           //Reading 8  MSB bit
    ADMUX &= ~(1 << MUX3); //TO select the analog pin ADC0
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX0);
}