#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <avr/interrupt.h>

#define mainREAD_TASK_PRIORITY 1
#define mainLED_TASK_PRIORITY 2

static void vBlinkLed(void *pvParameters);
static void vReadNum(void *pvParameters);

int uart_transmit(char data, FILE *stream);
int uart_receive(FILE *stream);

#define RX_BUFFER_SIZE 100
#define TX_BUFFER_SIZE 100

#define BAUD 9600                            // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD)-1) // zgodnie ze wzorem

#define LED_DDR DDRB
#define LED PB5
#define LED_PORT PORTB

QueueHandle_t rx_buffer;

QueueHandle_t tx_buffer;

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
  // włącz przerwania
  UCSR0B |= _BV(RXCIE0);
}

// Przerwanie dla odebrania danych
ISR(USART_RX_vect)
{
  // jeżeli bufor nie jest zapełniony
  if (xQueueIsQueueFullFromISR(rx_buffer) == pdFALSE)
  {
    xQueueSendToBackFromISR(rx_buffer, &UDR0, 0);
  }
}

// Funkcja odbierania danych z bufora
int uart_receive(FILE *stream)
{
  char data;
  // czekaj jeśli bufor jest pusty
  while (uxQueueMessagesWaiting(rx_buffer) == 0)
  {
    vTaskDelay(10);
  }
  xQueueReceive(rx_buffer, (void *)&data, 0);
  return data;
}

// Przerwanie dla gotowości do wysłania danych
ISR(USART_UDRE_vect)
{
  // jeżeli w buforze nadawczym coś jest, to czytaj
  if (xQueueIsQueueEmptyFromISR(tx_buffer) == pdFALSE)
  {
    xQueueReceiveFromISR(tx_buffer, (void *)&UDR0, 0);
  }
  else
  {
    UCSR0B &= ~_BV(UDRIE0); // Wyłącz przerwanie UDRE, gdy bufor nadawczy jest pusty
  }
}

// Funkcja wysyłania danych z bufora cyklicznego
int uart_transmit(char data, FILE *stream)
{
  // jeśli bufor jest pełny to czekaj
  while (uxQueueMessagesWaiting(tx_buffer) == TX_BUFFER_SIZE)
  {
    vTaskDelay(10);
    //taskYIELD();
  }
  xQueueSendToBack(tx_buffer, (void *)&data, 0);
  UCSR0B |= _BV(UDRIE0);
  return 0;
}

FILE uart_file;

int main(void)
{
  // Create task.
  xTaskHandle blink_handle;
  xTaskHandle read_handle;

  // Create xQueue
  rx_buffer = xQueueCreate(RX_BUFFER_SIZE, sizeof(char));
  tx_buffer = xQueueCreate(TX_BUFFER_SIZE, sizeof(char));

  xTaskCreate(
      vReadNum,
      "read",
      200,
      NULL,
      mainREAD_TASK_PRIORITY,
      &read_handle);

  xTaskCreate(
      vBlinkLed,
      "blink",
      configMINIMAL_STACK_SIZE,
      NULL,
      mainLED_TASK_PRIORITY,
      &blink_handle);

  // Start scheduler.
  vTaskStartScheduler();

  return 0;
}

void vApplicationIdleHook(void) {}

static void vReadNum(void *pvParameters)
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  sei();
  char input[10];
  for (;;)
  {
    scanf("%s", input);
    printf("Hello %s\r\n", input);
  }
}

static void vBlinkLed(void *pvParameters)
{
  LED_DDR |= _BV(LED);
  while (1)
  {
    LED_PORT |= _BV(LED);
    vTaskDelay(100);
    LED_PORT &= ~_BV(LED);
    vTaskDelay(100);
  }
}
