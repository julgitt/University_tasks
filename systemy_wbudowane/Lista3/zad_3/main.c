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

uint32_t exps(int32_t v){
    return (v >> 2) * (v >> 2); 
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

  LED_DDR |= _BV(LED);
  LED_PORT &= _BV(LED);

  uint32_t timer = 0;
  uint32_t v;
  
  // mierz napięcie
  while(1) {
    LED_PORT = ~_BV(LED);
    ADCSRA |= _BV(ADSC);           // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); 	   // wyczyść bit ADIF (pisząc 1!)
    
    v = ADC; 	       	           // weź zmierzoną wartość (0..1023)     
    LED_PORT = _BV(LED);
    
    timer = (exps(v) << 10) >> 16; // *1024 / 
    
    for (int i = 0; i < timer; i++){
        _delay_us(1);
    }
    
    LED_PORT = ~_BV(LED);
 
    for (int i = 0; i < 1024 - timer; i++){
        _delay_us(1);
    }
    
    _delay_us(2);
 
   
    printf("Odczytano: %"PRIu32" %"PRIu32"\r\n", (int32_t)v, timer);
  }
}

  
