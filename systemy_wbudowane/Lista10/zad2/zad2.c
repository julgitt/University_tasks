#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "hd44780.c"

#define PERCENT_SYMBOL = 0b00100101

int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}

void upload_symbols()
{
  LCD_WriteCommand(HD44780_CGRAM_SET);
  uint8_t current_symbol = 0;
  for (uint8_t i = 0; i < 6; i++)
  {
    current_symbol |= 1 << (5 - i);
    for (uint8_t j = 0; j < 8; j++)
      LCD_WriteData(current_symbol);
  }
}

void progress_bar(uint8_t current)
{
  LCD_GoTo(6, 1);
  uint16_t percent = (current * 100) / 80;
  
  printf("%.2d", percent);
  putchar(PERCENT_SYMBOL);

  uint8_t pos = current / 6;
  uint8_t current_symbol = current % 6;

  LCD_GoTo(pos + 1, 0);

  if (pos == 13)
    putchar(current_symbol + 3);
  else
    putchar(current_symbol);
}

FILE hd44780_file;

int main()
{
  LCD_Initialize();
  LCD_Clear();

  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;

  upload_symbols();
  while (1)
  {
    for (uint8_t i = 0; i < 81; i++)
    {
      progress_bar(i);
      _delay_ms(200);
    }
    _delay_ms(1000);
    LCD_Clear();
  }
}
