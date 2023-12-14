#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include "i2c.c"
#include <string.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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

FILE uart_file;

#define i2cCheck(code, msg) \
    if ((TWSR & 0xf8) != (code)) { \
      printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      i2cReset(); \
    }
    

const uint8_t eeprom_addr = 0xa0;

static inline void write (uint16_t addr, uint8_t val) {
  i2cStart();
  i2cCheck(0x08, "I2C start");
    
  i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
  i2cCheck(0x18, "I2C EEPROM write request");
  i2cSend(addr & 0xff);
  i2cCheck(0x28, "I2C EEPROM set address");

  i2cSend(val);
  //i2cCheck(0x28, "I2C EEPROM send value ");
  
  i2cStop();
  i2cCheck(0xf8, "I2C stop");
}

static inline int read (uint16_t addr) {
  i2cStart();
  i2cCheck(0x08, "I2C start");
    
  // dummy write  
  i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
  i2cCheck(0x18, "I2C EEPROM write request");
  i2cSend(addr & 0xff);
  i2cCheck(0x28, "I2C EEPROM set address");
  
  // read
  i2cStart();
  i2cCheck(0x10, "I2C second start");

  i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
  i2cCheck(0x40, "I2C EEPROM read request");

  uint8_t data = i2cReadNoAck();
  i2cCheck(0x58, "I2C EEPROM read");
  
  i2cStop();
  i2cCheck(0xf8, "I2C stop");
  return data;
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


  uint16_t addr = 0;
  uint8_t val = 0;
  char command[10];

  while(1) {
    scanf("%s", command);

    if (strcmp(command, "read") == 0) {
      scanf("%x", &addr);
      
      uint8_t res = read(addr);
      printf("Read: %.3x: hex:%x dec:%d\r\n", addr, res, res);
    }
    else if (strcmp(command, "write") == 0) {
      scanf("%x", &addr);
      scanf("%d", &val);

      write(addr, val);
      printf("Write: %.3x: hex:%x dec:%d\r\n", addr, val, val);
    }
    else
      printf("Invalid command. Use write/read instead\r\n");
  }

  return 0;
  
  /*while(1) {
     write(addr, val);
     printf("write:%.3x: %x\r\n", addr, val);
     uint8_t  res = read(addr);
    
     printf("read:%.3x: %x\r\n", addr, res);
     addr++;
     addr &= 0x1ff;
     val++;
     val &= 0x1ff;
     _delay_ms(10);
     
   }*/
}


