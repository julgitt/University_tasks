#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN_RESET PB4
#define BTN_LEFT PB3
#define BTN_RIGHT PB2
#define BTN_PIN PINB
#define BTN_PORT PORTB

void gray(int x)
{
	LED_PORT = x ^ (x >> 1);
}

static inline void debouncing()
{
	for (int i = 0; i < 500; i++)
	{
		if (counter > 20)
		{
			break;
		}
		if (BTN_PIN & _BV(BTN_RIGHT))
			counter++;
		else
			counter = 0;
		_delay_ms(1);
	}
}

int main()
{
	UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
	BTN_PORT |= _BV(BTN_RESET) | _BV(BTN_LEFT) | _BV(BTN_RIGHT);
	// ustaw wszystkie piny portu D na wyjcie
	LED_DDR = 0xFF;
	LED_PORT = 0;
	int pfx = 0;
	int counter = 0;

	while (1)
	{
		pfx %= 256;
		gray(pfx);
		if (!(BTN_PIN & _BV(BTN_RESET)))
		{
			LED_PORT = 0;
			pfx = 0;
			debouncing();
		}
		if (!(BTN_PIN & _BV(BTN_RIGHT)))
		{
			pfx++;
			debouncing();
		}
		if (!(BTN_PIN & _BV(BTN_LEFT)))
		{
			if (pfx == 0)
				pfx = 255;
			else
				pfx--;
			debouncing();
		}
	}
}
