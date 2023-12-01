#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem


#define up 		0b11111110
#define right_up 	0b11111101
#define right_down 	0b11111011
#define down 		0b11110111
#define left_down 	0b11101111
#define left_up 	0b11011111
#define middle 		0b10111111
#define dot 		0b01111111

// inicjalizacja SPI
void spi_init()
{
    // ustaw piny MOSI, SCK i ~SS jako wyjścia
    DDRB |= _BV(DDB3) | _BV(DDB5) | _BV(DDB2);
    // włącz SPI w trybie master z zegarem 250 kHz
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1);
}

// transfer jednego bajtu
uint8_t spi_transfer(uint8_t data)
{
    // rozpocznij transmisję
    SPDR = data;
    // czekaj na ukończenie transmisji
    while (!(SPSR & _BV(SPIF)));
    // wyczyść flagę przerwania
    SPSR |= _BV(SPIF);
    // zwróć otrzymane dane
    return SPDR;
}

int main()
{
    DDRB |= _BV(PORTB);

    int8_t numbers[10] = {up & right_down & right_up & down & left_down & left_up & dot,
    			  right_down &right_up & dot,
    			  up & right_up & down & left_down & middle & dot, 
    			  up & right_down & right_up & down &middle & dot,
    			  middle & right_down & right_up &left_up & dot,
                          up & right_down & down & left_up &middle & dot,
                          up & right_down & down & left_up & middle & left_down & dot,
                          right_down & right_up &up & dot,
                          up & right_down & right_up & down & left_down & left_up &middle & dot,
                          up & right_down & right_up & down & left_up &middle & dot};

  // zainicjalizuj SPI
  spi_init();
  PORTB |= _BV(PB1);
  
  while(1) {
    for(int i = 0; i < 10; i++) { 
    	uint8_t w = spi_transfer(~numbers[i]);
    	_delay_ms(1000);
    }
  }
}

