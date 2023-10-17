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
   

    uint8_t morse[36] = {0b0000, 0b01110, 0b01010, 0b1100, 0b000, 0b11010,
                         0b0100, 0b11110, 0b1000, 0b10000, 0b1000, 0b10110,
                         0b0000, 0b1000, 0b0000, 0b10010, 0b00100,
                         0b0100, 0b1100, 0b000, 0b1000, 0b11100, 0b0000,
                         0b01100, 0b01000, 0b00110, 0b00000, 0b10000, 0b11000,
                         0b11100, 0b11110, 0b11111, 0b01111, 0b00111,
                         0b00011, 0b00001};

    int8_t character = 0;
    int timer = 0;
    char c = 0;
    while(1) {
      if ((BTN_PIN & _BV(BTN))) {
      	timer = 0;
      	while(1) {
      	    _delay_ms(10);
            timer+=10;
      	    // jeżeli przycisk szybko odkliknięty - dot
      	    if (!(BTN_PIN & _BV(BTN)) & (timer < 1000)) {
      	    	character = (character << 1) | 1;
      	    	printf(".");
      	    	break;
      	    } 
      	    else if (!(BTN_PIN & _BV(BTN)) & (timer > 1000)) {
      	    	character = character << 1;
      	    	printf("-");
      	    	break;
      	    }
      	}
      }
      _delay_ms(10);
      timer+=10;
     /* // długo nie było znaku 
      if (timer > 10000) {
      	
      }
      // spacja
      else if (timer > 5000) {
      	//printf(" ");
      }
      // skończono czytać znak 
      else if (timer > 3000) {
      	// szukamy odpowiedniego kodu morsa
      	for (int i = 0; i < 36; i++){
      	  if (morse[i] == character) {
      	    // wypisujemy
      	    //if (i <= 26)
      	      //c = 'A' + i;
      	    //else
      	      //c = '0' + i;
 	    //printf("A");
      	  }
      	}
      	int8_t character = 0;
      }
      // jeżeli naciśnięte 
      
    LED_PORT &= ~_BV(LED);*/
  }
}