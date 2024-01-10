#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#define BAUD 9600                            // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD)-1) // zgodnie ze wzorem

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
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)))
    ;
  return UDR0;
}

FILE uart_file;

void timer1_init() {
  // COM1A = 10   -- non-inverting mode
  // częstotliwość 16e6/(8*(1+2048)) ~ 976 HZ
  ICR1 = 2048;
  TCCR1A = _BV(COM1A1) | (COM1A0);
  TCCR1B = _BV(WGM13) | _BV(CS11); // prescaler 8, Phase and Frequency Correct PWM 
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}

// close
ISR(TIMER1_CAPT_vect) {
  TIMSK1 &= ~_BV(ICIE1);
  ADCSRA |= _BV(ADSC);
}
 
// open
ISR(TIMER1_OVF_vect) {
  ADCSRA |= _BV(ADSC);
  TIMSK1 &= ~_BV(TOIE1);
}


// inicjalizacja ADC
void adc_init() {
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D) | _BV(ADC1D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) /*| _BV(ADPS1) | _BV(ADPS2)*/; // preskaler 2
  ADCSRA |= _BV(ADEN); // włącz ADC
}

int main() {
  timer1_init();
  adc_init();
  sei();

  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  uint16_t counter = 0, ADC_LOWER, ADC_UPPER;
  while (1) {
    ADMUX &= ~_BV(MUX0);
    
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    OCR1A = 2 * v;
    
    if(counter == 1000) {
      ADMUX |= _BV(MUX0);
      counter = 0;
      
      TIMSK1 |= _BV(ICIE1);
      while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
      ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
      ADC_LOWER = ADC; // weź zmierzoną wartość (0..1023)
      
      TIMSK1 |= _BV(TOIE1);
      while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
      ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
      ADC_UPPER = ADC; // weź zmierzoną wartość (0..1023)
    
      float result1 = (float)ADC_UPPER * 5000.0 / 1024.0;
      float result2 = 5000.0 - (float)ADC_LOWER * 5000.0 / 1024.0;
      
      printf("Napięcia CLOSED: %.4f mV, OPEN: %.4f mV                  \r", result2, result1);
    }
    counter++;
  }
}
