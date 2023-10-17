#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED_DDR DDRD
#define R_DDR DDRC

#define LED_PORT PORTD
#define R_PORT PORTC

#define R0_PIN PC0
#define R1_PIN PC1

#define up 0b11111110
#define right_up 0b11111101
#define right_down 0b11111011
#define down 0b11110111
#define left_down 0b11101111
#define left_up 0b11011111
#define middle 0b10111111
#define dot 0b01111111

#define ZERO up & right_down & right_up & down & left_down &left_up
#define ONE right_down &right_up
#define TWO up & right_up & down & left_down &middle
#define THREE up & right_down & right_up & down &middle
#define FOUR middle & right_down & right_up &left_up
#define FIVE up & right_down & down & left_up &middle
#define SIX up & right_down & down & left_up & middle &left_down
#define SEVEN right_down & right_up &up
#define EIGHT up & right_down & right_up & down & left_down & left_up &middle
#define NINE up & right_down & right_up & down & left_up &middle

int main()
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);

    R_DDR = 0xFF;
    LED_DDR = 0xFF;

    LED_PORT = 0xFF;
    R_PORT = _BV(R0_PIN) | _BV(R1_PIN);

    int8_t numbers[10] = {ZERO, ONE, TWO, THREE, FOUR,
                          FIVE, SIX, SEVEN, EIGHT, NINE};

    while (1)
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int t = 0; t < 50; t++)
                {
                    R_PORT = 0b11111110;
                    LED_PORT = numbers[i];
                    _delay_ms(10);
                    R_PORT = 0b11111101;
                    LED_PORT = numbers[j];
                    _delay_ms(10);
                }
            }
        }
        LED_PORT = 0b11111111;
        _delay_ms(1500);
    }
}
