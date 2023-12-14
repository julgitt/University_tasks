#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>


#define mainLED_BUTTON_TASK_PRIORITY   2
#define mainLED_BAR_TASK_PRIORITY 1

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

#define LEDBAR_DDR DDRD
#define LEDBAR_PORT PORTD

static void vLedBar(void* pvParameters);
static void vLedButton(void* pvParameters);

int uart_transmit(char c, FILE *stream);
int uart_receive(FILE *stream);

FILE uart_file = FDEV_SETUP_STREAM(uart_transmit, uart_receive, _FDEV_SETUP_RW);

// inicjalizacja UART
void uart_init(void)
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

int uart_transmit(char c, FILE *stream) {
  while (!(UCSR0A & _BV(UDRE0))) taskYIELD();
  UDR0 = c;
  return 0;
}

int uart_receive(FILE *stream) {
  while (!(UCSR0A & _BV(RXC0))) taskYIELD();
  return UDR0;
}

int main(void)
{
    // Create task.
    xTaskHandle led_button_handle;
    xTaskHandle led_bar_handle;

    xTaskCreate
        (
         vLedButton,
         "led_button",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_BUTTON_TASK_PRIORITY,
         &led_button_handle
        );

    xTaskCreate
        (
         vLedBar,
         "vLedBar",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_BAR_TASK_PRIORITY,
         &led_bar_handle
        );

    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}


void vApplicationIdleHook(void)
{

}


static void vLedButton (void* pvParameters)
{
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);
  unsigned char arr[100];
  int i = 0;
  while (i < 100)
  {
    arr[i] = BTN_PIN & _BV(BTN);
    i++;
    vTaskDelay(10);
  }

  i = 0;
  while (1)
  {
    if (arr[i])
      LED_PORT &= ~_BV(LED);
    else
      LED_PORT |= _BV(LED);
    arr[i] = BTN_PIN & _BV(BTN);
    i = (i + 1) % 100;
    vTaskDelay(10);
  }
}
  
  
static void vLedBar(void* pvParameters)
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    // ustaw wszystkie piny portu D na wyjcie
    LEDBAR_DDR = 0xFF;
    LEDBAR_PORT =  1;
    
    while(1) {
    	for (int i = 0; i < 7; i++) {
    		LEDBAR_PORT = LEDBAR_PORT << 1;
    		vTaskDelay(100);
    	}
    	
    	for (int i = 0; i < 7; i++) {
    		LEDBAR_PORT = LEDBAR_PORT >> 1;
    		vTaskDelay(100);
    	}
    }
}
