#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define DDR DDRB
#define PORT PORTD


int main()
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    DDR |= 0b11111111;
    PORT |= 0b11111111;
    uint8_t numbers[10] = {0b00000001, 0b00000010, 0b00000100, 
    			    0b00001000, 0b00010000, 0b00100000,
                            0b01000000, 0b10000000, 0b10000001, 0b10000010};
    while(1) {
        for (int i = 0; i < 10; i++) {
            PORT = numbers[i];
            _delay_ms(800);
        }
    }
}
