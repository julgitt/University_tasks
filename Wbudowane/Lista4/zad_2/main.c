#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define LED_DDR  DDRB
#define LED_PORT  PORTB
#define LED PB5

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
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

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;


void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = CS10 - bez prescalera
  // ICR1  = 1023
  // częstotliwość 16e6/(1024*(1+15624)) = 1 Hz
  // wzór: datasheet 20.12.3 str. 164
  ICR1 = 1023;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}


int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // zainicjalizuj ADC
  adc_init();

  // uruchom licznik
  timer1_init();

  LED_DDR |= _BV(LED);
  LED_PORT &= _BV(LED);
  

  float v;
  uint16_t val;
  
  // mierz napięcie
  while(1) {
    LED_PORT = ~_BV(LED);
    ADCSRA |= _BV(ADSC);           // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); 	         // wyczyść bit ADIF (pisząc 1!)
    
    v = ADC; 	       	            // weź zmierzoną wartość (0..1023)     

    val = 1023 - ((sqrt(v)*40) > 1023? 1023 :(40*sqrt(v)));
    
    OCR1A = val;
    printf("Odczytano: %"PRIu32" %"PRIu16" %"PRIu32"\r\n", (uint32_t)v, val, OCR1A);
  }
}

  
