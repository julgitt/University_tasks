#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
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
  ADMUX = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0 = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  ADMUX |= _BV(MUX2) | _BV(MUX1) | _BV(MUX3); 
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;


#define size 16
volatile float adc_reading[size];
volatile float vcc[size];
volatile int current = 0;

ISR(ADC_vect) {
  if (current < size) {
    adc_reading[current] = ADC; 	       	            // weź zmierzoną wartość (0..1023)  
    vcc[current] = 1.1 * 1024 / adc_reading[current];
    current++;
  }
}

float get_mean(){
  float mean = 0.0;
  for (int i = 0; i < size; i++)
    mean += vcc[i]; 
  mean /= size;
  return mean;
}

float variance(float mean){
  volatile float var = 0.0;
  for (int i = 0; i < size; i++){
    var += (mean - vcc[i]) * (mean - vcc[i]);
    printf("%f\r\n", adc_reading[i]);
   }
   
   var /= size;
   printf("%f\r\n",var);
   return var;
}


int main()
{
  uart_init();
   // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  adc_init();
  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_ADC);
  
  // odczyt do ustabilizowania się wartości
  for (int i = 0; i < size; i++) {
  	ADCSRA |= _BV(ADSC); 	   // wykonaj konwersję
  	while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
  	ADCSRA |= _BV(ADIF); 	   // wyczyść bit ADIF (pisząc 1!)
    
  	ADC; 	       	  // weź zmierzoną wartość (0..1023)
  	_delay_ms(200);
  } 
  
  for (int i = 0; i < size; i++) {
  	ADCSRA |= _BV(ADSC); 	   // wykonaj konwersję
  	while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
  	ADCSRA |= _BV(ADIF); 	   // wyczyść bit ADIF (pisząc 1!)
    
  	adc_reading[i] = ADC; 	       	  // weź zmierzoną wartość (0..1023)
  	vcc[i] = 1.1 * 1024 / adc_reading[i];
  	_delay_ms(200);
  } 
  float vc = get_mean();
  float var = variance(vc);
  
  printf("Bez Noise Reduction odczytano: VCC:%f, variance: %f\r\n", vc, var);

  // Ustaw ADC Conversion Complete Interrupt
  ADCSRA |= _BV(ADATE) | _BV(ADIE);
  // odmaskuj przerwania
  sei();
  sleep_mode();
  
  while (current < size);
  cli();
  vc = get_mean();
  var = variance(vc);
  
  printf("Z Noise Reduction odczytano: VCC:%f, variance: %f\r\n", vc, var);
    
  while(1) {
    _delay_ms(100);
  }
 

}

