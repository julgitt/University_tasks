#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#define SPI_PORT PORTD
#define SPI_DDR  DDRD

#define MISO PD4
#define MOSI PD5
#define SCK  PD6
#define SS   PD7


#define BAUD 9600                            // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD)-1) // zgodnie ze wzorem

// inicjalizacja UART
void uart_init() {
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) {
  // czekaj aż transmiter gotowy
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream) {
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)))
    ;
  return UDR0;
}

FILE uart_file;

void spi_init() {
  DDRD |= _BV(MOSI) | _BV(SCK) | _BV(SS);
}


void spi_slave_init() {
  // ustaw pin MISO jako wyjście
  DDRB = _BV(PB4);
  // włącz SPI w trybie slave
  SPCR = _BV(SPE);
}

char spi_slave_receive() {
  // SPIF - flaga przerwania w rejestrze SPSR
  // czekamy aż transmisja danych przez mastera zakończy się 
  while (!(SPSR & _BV(SPIF)))
    ;
  // Zwracamy otrzymany bajt danych z SPI Data Register
  return SPDR;
}

void send_by_bit_banging(uint8_t data){
  // wybieramy slave'a do komunikacji
  SPI_PORT &= ~_BV(SS);;

  // wysyłamy kolejne bity informacji
  for(int i = 7; i >= 0; i--){
    if((data >> i) & 1)
      SPI_PORT |= _BV(MOSI);
    else
      SPI_PORT &= ~_BV(MOSI);
    
    // cykl zegara, podczas którego wysyłamy dane do slave'a
    SPI_PORT |= _BV(SCK);
    _delay_ms(5);
    SPI_PORT &= ~_BV(SCK);
  }
  
  // slave jest wyłączony
  SPI_PORT |= _BV(SS);;
}

int main() {
  // zainicjalizuj UART
  uart_init();

  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // zainicjalizuj spi
  spi_slave_init();
  spi_init();
 

  uint8_t i = 0;
  
  while(1){
    send_by_bit_banging(i);
    printf("%d\r\n", spi_slave_receive());
    i += 1;
  }

  return 0;
}
