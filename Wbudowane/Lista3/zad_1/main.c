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


#define TONE(step, delay) \
    for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) { \
      BUZZ_PORT |= _BV(BUZZ); \
      for (i = 0; i < step; i++) \
      	_delay_us(1); \
      BUZZ_PORT &= ~_BV(BUZZ); \
      for (i = 0; i < step; i++) \
      	_delay_us(1); \
    }

int main() {
  BUZZ_DDR |= _BV(BUZZ);
  
  static const int8_t steps[21] PROGMEM = {B5,
                                          C6, E5, G5, C6, D6, G5, B5, C6,
                                          A5, C6, E6, F6, A5, E6, D6,
                                          C6, E5, G5, C6, B5,
                                          E5, G5, A5, A5, A5};

  static const int8_t delays[21] PROGMEM = {HALF_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE,
                                        QUARTER_NOTE, QUARTER_NOTE, NOTE, HALF_NOTE, QUARTER_NOTE};
  int8_t i; 
  while (1) {
    TONE(pgm_read_byte(&steps[0]), pgm_read_byte(&delays[0]));
    for (uint8_t j = 0; j < 3; j++) {
       i = 1;
       while (i < 16) {
          TONE(pgm_read_byte(&steps[i]), pgm_read_byte(&delays[i]));
          i++;
        }
    }

    while (i < 26) {
      TONE(pgm_read_byte(&steps[i]), pgm_read_byte(&delays[i]));
      i++;
    }

    /*
    TONE(B5, HALF_NOTE);
    
    // 1
    TONE(C6, QUARTER_NOTE);
    TONE(E5, QUARTER_NOTE);    
    TONE(G5, QUARTER_NOTE);
    TONE(C6, QUARTER_NOTE);
    TONE(D6, QUARTER_NOTE);
    TONE(G5, QUARTER_NOTE);
    TONE(B5, QUARTER_NOTE);
    TONE(C6, HALF_NOTE);

    TONE(A5, QUARTER_NOTE);
    TONE(C6, QUARTER_NOTE);
    TONE(E6, QUARTER_NOTE);
    TONE(F6, QUARTER_NOTE);
    TONE(A5, QUARTER_NOTE);
    TONE(E6, QUARTER_NOTE);
    TONE(D6, QUARTER_NOTE);

    // 2
    TONE(C6, QUARTER_NOTE);
    TONE(E5, QUARTER_NOTE);    
    TONE(G5, QUARTER_NOTE);
    TONE(C6, QUARTER_NOTE);
    TONE(D6, QUARTER_NOTE);
    TONE(G5, QUARTER_NOTE);
    TONE(B5, QUARTER_NOTE);
    TONE(C6, HALF_NOTE);

    TONE(A5, QUARTER_NOTE);
    TONE(C6, QUARTER_NOTE);
    TONE(E6, QUARTER_NOTE);
    TONE(F6, QUARTER_NOTE);
    TONE(A5, QUARTER_NOTE);
    TONE(E6, QUARTER_NOTE);
    TONE(D6, QUARTER_NOTE);
    
    // 3
    TONE(C6, QUARTER_NOTE);
    TONE(E5, QUARTER_NOTE);    
    TONE(G5, QUARTER_NOTE);
    TONE(C6, QUARTER_NOTE);
    TONE(D6, QUARTER_NOTE);
    TONE(G5, QUARTER_NOTE);
    TONE(B5, QUARTER_NOTE);
    TONE(C6, HALF_NOTE);

    TONE(A5, QUARTER_NOTE);
    TONE(C6, QUARTER_NOTE);
    TONE(E6, QUARTER_NOTE);
    TONE(F6, QUARTER_NOTE);
    TONE(A5, QUARTER_NOTE);
    TONE(E6, QUARTER_NOTE);
    TONE(D6, QUARTER_NOTE);


    TONE(C6, QUARTER_NOTE);
    TONE(E5, QUARTER_NOTE);
    TONE(G5, QUARTER_NOTE);
    TONE(C6, QUARTER_NOTE);
    TONE(B5, QUARTER_NOTE);

    TONE(E5, QUARTER_NOTE);
    TONE(G5, QUARTER_NOTE);
    TONE(A5, NOTE); 
    TONE(A5, HALF_NOTE); 
    TONE(A5, QUARTER_NOTE); */
    }
}
