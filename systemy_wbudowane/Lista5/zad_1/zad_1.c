#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

void io_init()
{
  // ustaw pull-up na PD2(INT0)
  BTN_PORT |= _BV(BTN);
  // ustaw wyjście na PB5
  LED_DDR |= _BV(LED);
}

void timer_init(){
    TCCR1A |= _BV(WGM11);
    TCCR1B |= _BV(WGM12) | _BV(WGM13) |_BV(CS12) | _BV(CS10);
    TIMSK1 |= _BV(OCIE1A);
   
    ICR1 = /*1562*/ 155;
}

static unsigned char buff[100];

static int i;

ISR(TIMER1_COMPA_vect) {
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
  timer_init();
  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_IDLE);
  LED_PORT &= ~_BV(LED);
  // odmaskuj przerwania
  sei();

  
  while (1)
  {
    sleep_mode();
  }
}