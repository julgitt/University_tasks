#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include "i2c.c"
#include <string.h>
#include <util/delay.h>

#define BAUD 9600                            // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD)-1) // zgodnie ze wzorem

// inicjalizacja UART
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

#define i2cCheck(code, msg)                               \
  if ((TWSR & 0xf8) != (code))                            \
  {                                                       \
    printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
    i2cReset();                                           \
  }

const uint8_t clock_addr = 0xd0;

static inline void write(uint8_t addr, uint8_t value)
{
  i2cStart();

  i2cSend(clock_addr);
  i2cSend(addr);

  uint8_t high, low;

  high = value / 10 << 4;
  low = value % 10;

  i2cSend(high | low);
  i2cStop();
}

static inline int read(int8_t addr)
{
  // dummy write
  i2cStart();

  i2cSend(clock_addr);
  i2cSend(addr);

  // read
  i2cStart();
  i2cSend(clock_addr | 0x1);
  uint8_t value = i2cReadNoAck();

  uint8_t low, high;
  high = (value >> 4) * 10;
  low = value & 0b1111;

  uint8_t data = high + low;
  i2cStop();
  return data;
}

static inline void date()
{
  printf("%d-%d-%d\r\n", read(4), read(5), read(6));
}

static inline void time()
{
  printf("%d:%d:%d\r\n", read(2), read(1), read(0));
}

static inline void set_date(int day, int month, int year)
{
  write(4, day);
  write(5, month);
  write(6, year);
}

static inline void set_time(int hour, int minute, int second)
{
  write(0, second);
  write(1, minute);
  write(2, hour);
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj I2C
  i2cInit();

  uint8_t val1 = 0, val2 = 0, val3 = 0;
  char command[10];
  
  while (1)
  {
    scanf("%s", command);
    if (strcmp(command, "time") == 0)
      time();
    else if (strcmp(command, "date") == 0)
      date();
    else if (strcmp(command, "set") == 0)
    {
      scanf("%s", command);

      if (strcmp(command, "time") == 0)
      {
        scanf("%d:%d:%d", &val1, &val2, &val3);
        set_time(val1, val2, val3);
        printf("Write: %d:%d:%d\r\n", val1, val2, val3);
      }
      else if (strcmp(command, "date") == 0)
      {
        scanf("%d-%d-%d", &val1, &val2, &val3);
        set_date(val1, val2, val3);
        printf("Write: %d-%d-%d\r\n", val1, val2, val3);
      }
      else
        printf("Invalid command. Use set time/set date instead\r\n");
    }
    else
      printf("Invalid command. Use time/date/set time/set date instead\r\n");
  }
}
