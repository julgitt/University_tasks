#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

int main()
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    // ustaw wszystkie piny portu D na wyjcie
    LED_DDR = 0xFF;
    LED_PORT =  1;
    
    while(1) {
    	for (int i = 0; i < 7; i++) {
    		LED_PORT = LED_PORT << 1;
    		_delay_ms(100);
    	}
    	
    	for (int i = 0; i < 7; i++) {
    		LED_PORT = LED_PORT >> 1;
    		_delay_ms(100);
    	}
    }
}
