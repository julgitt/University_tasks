#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define LED PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PA7
#define BTN_PIN PINA
#define BTN_PORT PORTA

#define N 100
static unsigned char buff[N];
static uint8_t i;

void io_init(){
  // ustaw pull-up
  BTN_PORT |= _BV(BTN);
  // ustaw wyjście na PB2
  LED_DDR |= _BV(LED);
}

void timer1_init(){
    TCCR1A |= _BV(WGM11);
    TCCR1B |= _BV(WGM12) | _BV(WGM13) |_BV(CS12) | _BV(CS10);
    TIMSK1 |= _BV(OCIE1A);
   
    ICR1 = 10;
}

ISR(TIM1_COMPA_vect) {
  if (buff[i])
    LED_PORT &= ~_BV(LED);
  else
    LED_PORT |= _BV(LED);
  buff[i] = BTN_PIN & _BV(BTN);
  i = (i + 1) % 100;
}

int main() {
  // zainicjalizuj wejścia/wyjścia
  io_init();
  timer1_init();
  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_IDLE);
  // odmaskuj przerwania
  sei();
  
  while (1) 
  {
    sleep_mode();
  }
}
