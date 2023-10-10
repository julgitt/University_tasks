#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED_DDR DDRD
#define LED_PORT PORTD
#define LED0 PD0
#define LED1 PD1
#define LED2 PD2
#define LED3 PD3
#define LED4 PD4
#define LED5 PD5
#define LED6 PD6
#define LED7 PD7

void dioda(int led) {
	LED_PORT |= _BV(led);
	_delay_ms(100);
	LED_PORT &= ~_BV(led);
}

int main()
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    // ustaw wszystkie piny portu D na wyjcie
    LED_DDR = 0xFF;
    

    while(1) {
    	dioda(PD0);
    	dioda(PD1);
    	dioda(PD2);
    	dioda(PD3);
    	dioda(PD4);
    	dioda(PD5);
    	dioda(PD6);
    	dioda(PD7);
    	
    	dioda(PD7);
    	dioda(PD6);
    	dioda(PD5);
    	dioda(PD4);
    	dioda(PD3);
    	dioda(PD2);
    	dioda(PD1);
    	dioda(PD0);
    }
}
