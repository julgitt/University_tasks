#include <stdio.h>
#include <avr/interrupt.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define BAUD 9600                            // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD)-1) // zgodnie ze wzorem

int uart_transmit(char data, FILE *stream);
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

int uart_transmit(char data, FILE *stream)
{
  while (!(UCSR0A & _BV(UDRE0)))
  {
    taskYIELD();
  }
  UDR0 = data;
  return 0;
}

int uart_receive(FILE *stream)
{
  while (!(UCSR0A & _BV(RXC0)))
    taskYIELD();
  return UDR0;
}

void adc_init(uint8_t mux)
{
  ADMUX = _BV(REFS0) | mux;
  DIDR0 = _BV(mux); // wyłącz wejście cyfrowe na mux
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADIE); // preskaler 128
  ADCSRB |= _BV(ADTS1) | _BV(ACME);
}

xSemaphoreHandle adcSemaphore;
uint16_t adcReading;

ISR(ADC_vect)
{
  adcReading = ADC;
  vTaskNotifyGiveFromISR(xSemaphoreGetMutexHolder(adcSemaphore), NULL);
}

uint16_t readADC(uint8_t mux)
{
  uint16_t res;

  while (xSemaphoreTake(adcSemaphore, 100) == pdFALSE) {}

  adc_init(mux);
  ADCSRA |= _BV(ADEN);

  ADCSRA |= _BV(ADSC);
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  ADCSRA |= _BV(ADIF);

  res = adcReading;
  printf("%d -> %d\n\r", mux, res);

  ADCSRA &= ~_BV(ADEN);

  xSemaphoreGive(adcSemaphore);

  return res;
}

void adcTask(void *pvParameters)
{
  uint8_t mux = (uint8_t)pvParameters;
  vTaskDelay(pdMS_TO_TICKS(250 * mux));
  while (1)
  {
    uint16_t result = readADC(mux);
    vTaskDelay(1250 * mux);
  }
}

int main(void)
{
  sei();

  uart_init();
  stdin = stdout = stderr = &uart_file;
  
  adcSemaphore = xSemaphoreCreateMutex();

  xTaskHandle adcTask1;
  xTaskHandle adcTask2;
  xTaskHandle adcTask3;

  xTaskCreate(
      adcTask,
      "adcTask1",
      configMINIMAL_STACK_SIZE,
      (void *)1,
      1,
      &adcTask1);
  xTaskCreate(
      adcTask,
      "adcTask2",
      configMINIMAL_STACK_SIZE,
      (void *)2,
      1,
      &adcTask2);
  xTaskCreate(
      adcTask,
      "adcTask3",
      configMINIMAL_STACK_SIZE,
      (void *)3,
      1,
      &adcTask3);

  // Start scheduler.
  vTaskStartScheduler();

  return 0;
}

void vApplicationIdleHook(void)
{
}
