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

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = 101  -- prescaler 1024
  // ICR1  = 15624
  // częstotliwość 16e6/(1024*(1+15624)) = 1 Hz
  // wzór: datasheet 20.12.3 str. 164
  ICR1 = 15624;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10) | _BV(CS12);
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
  

  uint32_t v;
  uint32_t u;
  uint32_t imp;
  
  // mierz napięcie
  while(1) {
    LED_PORT = ~_BV(LED);
    ADCSRA |= _BV(ADSC);           // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); 	   // wyczyść bit ADIF (pisząc 1!)
    
    v = ADC; 	       	           // weź zmierzoną wartość (0..1023)     
    LED_PORT = _BV(LED);
    
    u = (v * 5.0) / 1023.0;
		imp = (u * 10000.0) / (5.0 - u);
		//if (imp < 3000000){
		//	LED_BR = ((imp / 3000000.0)*255) ;
		//}else{
		//	LED_BR = 1;
		//}
 
   
    printf("Odczytano: %"PRIu32" %"PRIu32" %"PRIu32"\r\n", (int32_t)v, u, imp);
  }
}

  
