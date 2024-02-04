#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <inttypes.h>

#define BUZZ PB5
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#define QUARTER_NOTE 250
#define HALF_NOTE 500
#define NOTE 1000

#define C4 1908
#define D4 1701
#define E4 1515
#define F4 1433
#define G4 1276
#define A4 1136
#define B4 1012
#define C5 956
#define D5 852
#define E5 759
#define F5 716
#define G5 638
#define A5 568
#define B5 506
#define C6 478
#define D6 426
#define E6 379
#define F6 358
#define G6 319
#define A6 284
#define B6 253
#define PAUSE 0

void my_delay(uint16_t t){
  for (uint16_t i = 0; i < t; i++){
    _delay_us(1);
  }
}

#define TONE(step, delay) \
    for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) { \
      BUZZ_PORT |= _BV(BUZZ); \
      my_delay(step); \
      BUZZ_PORT &= ~_BV(BUZZ); \
      my_delay(step); \
    }

int main() {
  BUZZ_DDR |= _BV(BUZZ);
  
  static const uint16_t steps[] PROGMEM = {B5,
                             C6, E5, G5, C6, D6, G5, B5, C6,
                             A5, C6, E6, F6, A5, E6, D6,
                             C6, E5, G5, C6, D6, G5, B5, C6,
                             A5, C6, E6, F6, A5, E6, D6,
                             C6, E5, G5, C6, D6, G5, B5, C6,
                             A5, C6, E6, F6, A5, E6, D6,
                             C6, E5, G5, C6, B5,
                             E5, G5, A5, A5, A5};

  static const uint16_t delays[] PROGMEM = {HALF_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, NOTE, HALF_NOTE, QUARTER_NOTE};
 
  uint16_t s;
  uint16_t t;
  while (1) {
    for (uint16_t j = 0; j < 56; j++) {
      s = pgm_read_word_near(steps + j);
      t = pgm_read_word_near(delays + j);
      TONE(s,t);
    }
  }
}
