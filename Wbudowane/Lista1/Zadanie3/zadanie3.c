#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define DDR DDRD
#define PORT PORTD


int main()
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    DDR |= 0b11111111;
    PORT |= 0b11111111;
    // 1 2 3 4 15 16 18 -> 0
    // 15 3 -> 1
    // 16, 15, 17, 2, 1 -> 2
    // 16,15, 17, 3 2 -> 3
    // 15, 3, 17 18 -> 4
    // 16, 3, 2 18 17 -> 5
    // 16, 3, 2 18 17 1 -> 6
    // 15,3 1 -> 7 
    // 1-18 -> 8
    // 2-18 -> 9
    uint8_t numbers[10] = {0b00100000, 0b01110011, 0b00010100, 0b00010001, 
    			   0b01000011, 0b10000001, 0b10000000,
                           0b00100011, 0b00000000, 0b00000001};
    while(1) {
        for (int i = 0; i < 10; i++) {
            PORT = numbers[i];
            _delay_ms(1000);
        }  
        PORT = 0b11111111;
        _delay_ms(1500);
    }
}
