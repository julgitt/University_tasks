#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <string.h>
#include "hd44780.c"

#define BAUD 9600                            // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD)-1) // zgodnie ze wzorem

#define BUF_SIZE 16
char line_buf[BUF_SIZE];

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

int uart_receive(FILE *stream)
{
  while (!(UCSR0A & _BV(RXC0)))
    ;
  return UDR0;
}

int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}

void shift_line_up(uint8_t length)
{
  LCD_Clear();
  LCD_GoTo(0, 0);
  for (uint8_t i = 0; i < length; i++)
  {
    putchar(line_buf[i]);
    _delay_ms(5);
  }
}

FILE hd44780_file;
FILE uart_file;

int main()
{
  LCD_Initialize();
  LCD_Clear();
  LCD_WriteCommand(HD44780_CURSOR_ON | HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON);

  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;

  uart_init();
  fdev_setup_stream(&uart_file, NULL, uart_receive, _FDEV_SETUP_READ);
  stdin = &uart_file;

  uint8_t i = 0;
  char input;

  while (1)
  {
    input = getc(stdin);
    if (input == '\n' || input == '\r')
    {
      shift_line_up(i);
      i = 0;
      continue;
    }
    LCD_GoTo(i, 1);
    putchar(input);
    line_buf[i++] = input;
    if (i >= BUF_SIZE)
    {
      shift_line_up(i);
      i = 0;
    }
  }
}
