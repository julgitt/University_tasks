#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

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
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
    // czekaj aż transmiter gotowy
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = data;
    return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
    // czekaj aż znak dostępny
    while (!(UCSR0A & _BV(RXC0)));
    return UDR0;
}

FILE uart_file;

int main()
{
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    // ustaw pin PB5 na wyjście
    LED_DDR |= _BV(LED);
    
    // konfiguracja przycisku
    BTN_PORT |= _BV(BTN);
   

    const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";
    int ptr = 1;

    int timer = 0;
    char c = 0;
    while(1) {
      if (!(BTN_PIN & _BV(BTN))) {
      	timer = 0;
      	while(1) {
      	    _delay_ms(10);
            timer+=10;
            if (timer >= 1000) {
              LED_PORT |= _BV(LED);
            }
      	    if ((BTN_PIN & _BV(BTN)) && (timer < 1000)) {
      	    	ptr = 2*ptr;
      	    	break;
      	    }
      	    else if ((BTN_PIN & _BV(BTN))) {
      	    	ptr = 2*ptr + 1;
      	    	break;
      	    }
      	}
        timer = 0;
      }
      // spacja
      if (timer > 5000) {
      	putchar(' ');
        timer = 0;
      }
      //skończono czytać znak 
      else if (timer > 3000) {
      	// wypisujemy
        if (ptr > 1 ) {
          putchar(letter[ptr]);
          ptr = 1;
          timer = 0;
        }
      }
      _delay_ms(10);
      timer+=10;
      LED_PORT &= ~_BV(LED);
  }
}
