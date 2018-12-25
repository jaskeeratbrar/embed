#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

typedef enum{ RELEASED = 0, PRESSED, LOCKED , UNLOCKED} key_t;

#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define LED_PIN2 (1 << PB2)
#define KEY0     (1 << PB3)
#define KEY1     (1 << PB4)

int main(void) {
  key_t keystate = UNLOCKED;
  // set 0 and 1 pins to output, default is input
  DDRB = LED_PIN1|LED_PIN0;

  // PB1 output is high, current flows from that pin, via yellow to PB0
  PORTB = LED_PIN1;

  volatile uint8_t history = 0;
  int count = 0;

  while (1) {

    if(keystate == UNLOCKED){
      _delay_ms(50);
      // swap current source and sink, causing yellow and green to toggle
      PORTB ^= LED_PIN1|LED_PIN0;
    }

    if((PINB & KEY0) == 0 || (PINB & KEY1) ==0){
      history = history | 0x1;
    }

    if ((history & 0b111111) == 0b111111){
      keystate = PRESSED;
      DDRB = LED_PIN1|LED_PIN2;
      PORTB = LED_PIN1;
    }
    else{
      PORTB = 0;
    }
    if ((history & 0b00111111) == 0){
      keystate = RELEASED;
      count +=1;
    }

    if(count == 6){
      keystate = LOCKED;
      DDRB = LED_PIN2|LED_PIN1;
      PORTB = LED_PIN2;
      count = 0;
    }

  }
}
