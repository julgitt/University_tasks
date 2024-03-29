#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

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

FILE uart_file;


void io_init(){
  // ustaw pull-up na PD2 (INT0)
  PORTD |= _BV(PORTD2);
  // ustaw wyzwalanie przerwania na INT0
  EICRA = _BV(ISC00) | _BV(ISC01);
  // odmaskuj przerwania dla INT0
  EIMSK |= _BV(INT0);
}

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  
  ADCSRA |= _BV(ADATE) | _BV(ADIE); // Włącz auto-trigger(automatyczna konwersja) + ADC Conversion Complete Interrupt
  
  ADCSRB |= _BV(ADTS1); 	    // Przerwanie INT0 triggeruje konwersję ADC
  
}

volatile float R1;
volatile float v;
volatile float u;

ISR(INT0_vect){}
ISR(ADC_vect){
  float R2 = 2200.0;
  v = ADC; 	       	            // weź zmierzoną wartość (0..1023)     
  R1 = (R2 * 1024.0) / v - R2;	    // oblicz rezystancję
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // zainicjalizuj wejścia/wyjścia
  io_init();
  
  // zainicjalizuj ADC
  adc_init();
  
  // maska przerwań
  sei();
  
  // mierz napięcie
  while(1) {
    printf("Odczytano: %"PRIu32" %"PRIu32"\r\n", (uint32_t)v, (uint32_t)R1);
    _delay_ms(100);
  }
}

  
