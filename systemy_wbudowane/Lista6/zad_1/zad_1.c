#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
  // włącz przerwania
  UCSR0B |= _BV(RXCIE0);
}

volatile char character;
// Obsługa przerwania receive complete
ISR(USART_RX_vect) {
  character = UDR0;
  UCSR0A &= ~_BV(RXC0);
  // włącz przerwanie na pustym rejestrze nadawczym UDRE0
  UCSR0B |= _BV(UDRIE0);
}

// Obsługa przerwania pustego rejestru nadawczego
ISR(USART_UDRE_vect) {
  UDR0 = character;
  UCSR0B &= ~_BV(UDRIE0);
}

int main()
{
  // zainicjalizuj UART
  uart_init();

  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();
  
  while(1) {
    sleep_mode();
  }
}
