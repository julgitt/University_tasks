#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

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

void timer1_init()
{
    // ustaw tryb licznika
    // WGM1  = 0000 -- normal
    // CS1   = 001  -- prescaler 1
    TCCR1B = _BV(CS10);
}
FILE uart_file;

void test_int8()
{
    volatile uint8_t a = 5;
    volatile uint8_t b = 3;

    uint16_t time1 = 0;
    uint16_t time2 = 0;
    uint16_t time3 = 0;

    volatile uint8_t res1;
    volatile uint8_t res2;
    volatile uint8_t res3;

    TCNT1 = 0;
    res1 = a + b;
    time1 = TCNT1;

    TCNT1 = 0;
    res2 = a * b;
    time2 = TCNT1;

    TCNT1 = 0;
    res3 = a / b;
    time3 = TCNT1;

    printf(" %" PRIu8 ", %" PRIu8 "\r\n", a, b);

    printf("Dodawanie: %" PRIu16 " cykli, wynik: %" PRIu8 "\r\n", time1, res1);
    printf("Mnożenie: %" PRIu16 " cykli, wynik: %" PRIu8 "\r\n", time2, res2);
    printf("Dzielenie: %" PRIu16 " cykli, wynik: %" PRIu8 "\r\n", time3, res3);
}

void test_int16()
{
    volatile uint16_t a = 56;
    volatile uint16_t b = 3;

    uint16_t time1 = 0;
    uint16_t time2 = 0;
    uint16_t time3 = 0;

    volatile uint16_t res1;
    volatile uint16_t res2;
    volatile uint16_t res3;

    TCNT1 = 0;
    res1 = a + b;
    time1 = TCNT1;

    TCNT1 = 0;
    res2 = a * b;
    time2 = TCNT1;

    TCNT1 = 0;
    res3 = a / b;
    time3 = TCNT1;

    printf("%" PRIu16 ", %" PRIu16 "\r\n", a, b);

    printf("Dodawanie: %" PRIu16 " cykli, wynik: %" PRIu16 "\r\n", time1, res1);
    printf("Mnożenie: %" PRIu16 " cykli, wynik: %" PRIu16 "\r\n", time2, res2);
    printf("Dzielenie: %" PRIu16 " cykli, wynik: %" PRIu16 "\r\n", time3, res3);
}

void test_int32()
{
    volatile uint32_t a = 1053;
    volatile uint32_t b = 32;

    uint16_t time1 = 0;
    uint16_t time2 = 0;
    uint16_t time3 = 0;

    volatile uint32_t res1;
    volatile uint32_t res2;
    volatile uint32_t res3;

    TCNT1 = 0;
    res1 = a + b;
    time1 = TCNT1;

    TCNT1 = 0;
    res2 = a * b;
    time2 = TCNT1;

    TCNT1 = 0;
    res3 = a / b;
    time3 = TCNT1;

    printf("%" PRIu32 ", %" PRIu32 "\r\n", a, b);

    printf("Dodawanie: %" PRIu16 " cykli, wynik: %" PRIu32 "\r\n", time1, res1);
    printf("Mnożenie: %" PRIu16 " cykli, wynik: %" PRIu32 "\r\n", time2, res2);
    printf("Dzielenie: %" PRIu16 " cykli, wynik: %" PRIu32 "\r\n", time3, res3);
}

void test_int64()
{
    volatile uint64_t a = 10537;
    volatile uint64_t b = 3286;

    uint16_t time1 = 0;
    uint16_t time2 = 0;
    uint16_t time3 = 0;

    volatile uint32_t res1;
    volatile uint32_t res2;
    volatile uint32_t res3;

    TCNT1 = 0;
    res1 = a + b;
    time1 = TCNT1;

    TCNT1 = 0;
    res2 = a * b;
    time2 = TCNT1;

    TCNT1 = 0;
    res3 = a / b;
    time3 = TCNT1;

    // printf("%"PRIu32", %"PRIu32"\r\n",a,b);

    printf("Dodawanie: %" PRIu16 " cykli\r\n", time1);
    printf("Mnożenie: %" PRIu16 " cykli\r\n", time2);
    printf("Dzielenie: %" PRIu16 " cykli\r\n", time3);
}

void test_float()
{
    volatile float a = 10.53;
    volatile float b = 0.4;

    uint16_t time1 = 0;
    uint16_t time2 = 0;
    uint16_t time3 = 0;

    volatile float res1;
    volatile float res2;
    volatile float res3;

    TCNT1 = 0;
    res1 = a + b;
    time1 = TCNT1;

    TCNT1 = 0;
    res2 = a * b;
    time2 = TCNT1;

    TCNT1 = 0;
    res3 = a / b;
    time3 = TCNT1;

    printf("Dodawanie: %" PRIu16 " cykli\r\n", time1);
    printf("Mnożenie: %" PRIu16 " cykli\r\n", time2);
    printf("Dzielenie: %" PRIu16 " cykli\r\n", time3);
}

int main()
{

    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    // zainicjalizuj licznik
    timer1_init();
    //__________________________________________________________________________________

    printf("int8_t");
    test_int8();

    printf("int16_t\r\n");
    test_int16();

    printf("int32_t\r\n");
    test_int32();

    printf("int64_t\r\n");
    test_int64();

    printf("float\r\n");
    test_float();
}
