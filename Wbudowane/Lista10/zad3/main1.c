#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define HEATER_PIN    PB5
#define HEATER_PORT   PORTB
#define HEATER_DDR    DDRB	

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
  ADMUX   = _BV(REFS0) | _BV(REFS1); // referencja 1.1
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

static inline void heater_on() {
  PORTB |= _BV(HEATER_PIN);
}

static inline void heater_off() {
  PORTB &= ~_BV(HEATER_PIN);
}

int main()
{
  const float temp = 24.0;
  const float hysteresis = 1.0;

  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  // zainicjalizuj ADC
  adc_init();

  // ustaw pin grzałki na output
  HEATER_DDR |= _BV(HEATER_PIN);
  
  float adc_reading;
  float current_temp;
  float voltage;
  
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    adc_reading = ADC; // weź zmierzoną wartość (0..1023)
    
    voltage = (adc_reading * 1.1) / 1024.0; // Przeliczenie wartości ADC na napięcie
    current_temp = (voltage - 0.5) / 0.01; // Konwersja napięcia na temperaturę

    printf("Odczytano: %f\r\n", current_temp);
    if (current_temp >= temp) {
 	    heater_off();	
    } else if (current_temp <= temp - hysteresis) {
    	heater_on();
    }
    _delay_ms(100);
  }
}
