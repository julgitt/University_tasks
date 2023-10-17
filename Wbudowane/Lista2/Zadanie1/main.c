#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

int main()
{
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  unsigned char arr[100];
  int i = 0;
  while (i < 100)
  {
    arr[i] = BTN_PIN & _BV(BTN);
    i++;
    _delay_ms(10);
  }

  i = 0;
  while (1)
  {
    if (arr[i])
      LED_PORT &= ~_BV(LED);
    else
      LED_PORT |= _BV(LED);
    arr[i] = BTN_PIN & _BV(BTN);
    i = (i + 1) % 100;
    _delay_ms(10);
  }
}
