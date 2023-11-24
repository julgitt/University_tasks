#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <util/delay.h>

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

void io_init()
{
  DDRB &= ~ _BV(PB0); // Ustawienie pinu jako wejście
  PORTB |= _BV(PB0); // Włączenie pull-up resistora
}
void timer1_init()
{
  // Ustaw przerwanie dla Capture Event
  TIMSK1 |= _BV(ICIE1);
  
  //TCCR1A |=  _BV(WGM10);
  //TCCR1B |= _BV(WGM12) | _BV(WGM13);
  // Ustaw tryb przechwytywania (Capture)
  TCCR1B |= _BV(ICES1); // rosnące zbocze

  TCCR1B |= _BV(CS10) | _BV(CS12); // prescaler: 1024
}

volatile uint8_t flag;
volatile uint16_t prevCapturedValue;
volatile uint16_t capturedValue;
volatile float frequency;

ISR(TIMER1_CAPT_vect)
{
  if (flag == 0)
  {
    prevCapturedValue = ICR1;
  } else if (flag == 1)
  {
    capturedValue = ICR1;
    if (capturedValue > prevCapturedValue){
        uint16_t diff = capturedValue - prevCapturedValue;
        frequency = 15625.0f / ((float)diff);
    }
  } else if (flag == 2){
    	printf("frequency: %f\r\n", frequency);
        flag = 0;
        return;
    }
  flag++;
}

int main()
{
  io_init();
  flag = 0;
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  timer1_init();
  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_IDLE);

  // odmaskuj przerwania
  sei();

  while (1)
  {
    sleep_mode();
  }
}
