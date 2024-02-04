#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>


#define BAUD 9600                            // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD)-1) // zgodnie ze wzorem

#define RX_BUFFER_SIZE 128
#define TX_BUFFER_SIZE 128

volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t rx_read = 0;
volatile uint8_t rx_write = 1;
volatile uint8_t tx_buffer[TX_BUFFER_SIZE];
volatile uint8_t tx_read = 0;
volatile uint8_t tx_write = 1;
volatile uint8_t end;

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

// Przerwanie dla odebrania danych
ISR(USART_RX_vect) {
    uint8_t data = UDR0;
    uint8_t next_write = (rx_write + 1) % RX_BUFFER_SIZE;
    
    // jeżeli bufor nie jest zapełniony oraz znak nie jest końcem linii
    if (data != 0 && next_write != rx_read) {
        rx_buffer[rx_write] = data;
        rx_write = next_write;
    }
    // jeżeli kończymy odbieranie danych
    if (data == 0 || next_write == rx_read) {
    	rx_buffer[rx_write] = 0;
    	end = 1;
    }
}

// Funkcja odbierania danych z bufora
int uart_receive(FILE *stream) {
    uint8_t next_read = (rx_read + 1) % RX_BUFFER_SIZE;
    // czekaj jeśli bufor jest pusty
    while (next_read == rx_write && end == 0);
    uint8_t data = rx_buffer[next_read];
    rx_read = next_read;
    end = 0;
    return data;
}

// Przerwanie dla gotowości do wysłania danych
ISR(USART_UDRE_vect) {
    uint8_t next_read = (tx_read + 1) % TX_BUFFER_SIZE;
    // jeżeli w buforze nadawczym coś jest, to czytaj
    if (next_read != tx_write) {
        UDR0 = tx_buffer[tx_read];
        tx_read = next_read;
    } else {
        UCSR0B &= ~_BV(UDRIE0); // Wyłącz przerwanie UDRE, gdy bufor nadawczy jest pusty
    }
}

// Funkcja wysyłania danych z bufora cyklicznego
int uart_transmit(char data, FILE *stream) {
    uint8_t next_write = (tx_write + 1) % TX_BUFFER_SIZE;
    // jeśli bufor jest pusty to czekaj
    while (tx_read == tx_write); 
    tx_buffer[tx_write] = data;
    tx_write = next_write;
    UCSR0B |= _BV(UDRIE0); 
    return 0;
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  sei();

  // program testowy
  printf("Hello world!\r\n");

  char input[128];
  scanf("%s", &input);

  for(int i = 0; i <= strlen(input); i++){
    putc(input[i], stdout);
  }
  printf("\r\n");
  scanf("%s", &input);

  for(int i = 0; i <= strlen(input); i++){
    putc(input[i], stdout);
  }
  printf("\r\n");
  scanf("%s", &input);

  printf("%s\r\n",input);
  while(1);
}
