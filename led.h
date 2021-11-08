#ifndef _LED_H_
#define _LED_H_
#define LED_PIN 1 // pin 9 (arduino) on portB

void LED_init_Blink(void);
void LED_Off(void);

uint8_t simple_ramp(void); //Declaration of simple_ramp function
void LED_Rampning(void);

#endif // _LED_H_
