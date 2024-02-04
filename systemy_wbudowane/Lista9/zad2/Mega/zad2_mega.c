#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

#define BAUD 9600                            // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD)-1) // zgodnie ze wzorem

#define LED PD7
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN PD6
#define BTN_PIN PIND
#define BTN_PORT PORTD


void io_init(){
  // ustaw pull-up
  BTN_PORT |= _BV(BTN);
  // ustaw wyjście na PD7
  LED_DDR |= _BV(LED);
}

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

void SPI_SlaveInit(void) {
  // Ustaw MISO na wyjście
  DDRB = _BV(PB4);
  // Włącz SPI
  SPCR = _BV(SPE);
}

uint8_t SPI_SlaveReceive(void) {
  // Czekamy na zakończenie otrzymywania danych
  while (!(SPSR & (1 << SPIF)))
    ;
  
  // Zapisujemy stan przycisku 
  SPDR = !(BTN_PIN & _BV(BTN));
  // Zwracamy otrzymane dane
  return SPDR;
}

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  sei();
  io_init();
  SPI_SlaveInit();
  
  uint8_t data;
  while(1){
    data = SPI_SlaveReceive();
    // zapalenie/zgaszenie lampki w zaleznosci od stanu przycisku
    if (data) 
        LED_PORT |=  _BV(LED);
    else
        LED_PORT &= ~_BV(LED);
  }
}
