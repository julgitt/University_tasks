#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem


void timer1_init() {
  // No prescaler
  // ICR1 = 211
  // TOP = 212
  // f = 37914
  OCR1A = 421; // 16 mHz / (37,9 kHz - 26 ms okres) = 421
  OCR1B = 211; // nadajemy przez 600 ms nie nadajemy - 600 ms
  TCCR1A = _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(ICES1) | _BV(CS10);
  DDRB |= _BV(PB2);
}

int main() {
  timer1_init();
  uint16_t x = ICR1;
  DDRB |= _BV(PB5);
  while(1) {
    for (uint16_t i = 0; i < 6; i++) {
      
      PORTB &= ~_BV(PB5);
      if (x != ICR1) {
        PORTB |= _BV(PB5);
        x = ICR1;
      }
      DDRB |= _BV(PB2);
      _delay_us(600);
      DDRB &= ~_BV(PB2);
      _delay_us(600);
    }
    _delay_ms(100);
  }
}
