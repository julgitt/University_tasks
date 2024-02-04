#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  // zainicjalizuj ADC
  adc_init();

  float temp;
  
  uint32_t v;
  float vcc;
  
  float r1;
  float r2 = 2200.0;
  
  int32_t b = 3085.0;
  
  float b2;
  float current_temp = 294.0;
  
  // mierz napięcie
  while(1) {
   
    ADCSRA |= _BV(ADSC);           // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); 	   // wyczyść bit ADIF (pisząc 1!)
    
    v = ADC; 	       	           // weź zmierzoną wartość (0..1023)     
    
    vcc = v * 5.0 / 1024.0;
    
    r1 = 5 * r2 / vcc - r2;
    
    //b2 =  log(4700.0 / r1) / ((1.0 / 298.0) - (1 / current_temp));
    
    temp = 1.0 / ((1.0 / 298.0) - log(4700.0 / r1) / b) - 273.0;
    
    _delay_us(10);
   
    printf("Odczytano: %f %f %f \r\n", vcc, r1, temp/*, b2*/);
  }
}

  
