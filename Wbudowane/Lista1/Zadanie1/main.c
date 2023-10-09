#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
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

void dioda(int8_t how_long) {
    LED_PORT |= _BV(LED);
    while (how_long > 0){
	    _delay_ms(300);
	    how_long--;
    }
    LED_PORT &= ~_BV(LED);
    _delay_ms(1500);
}

int main()
{
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    // ustaw pin PB5 na wyjście
    LED_DDR |= _BV(LED);

    // program testowy
    uint8_t morse[36] = {0b1010000, 0b10001110, 0b10001010, 0b1101100, 0b110000, 0b10011010,
                         0b1100100, 0b10011110, 0b1011000, 0b10010000, 0b1101000, 0b10010110,
                         0b1000000, 0b1001000, 0b1100000, 0b10010010, 0b10000100,
                         0b1110100, 0b1111100, 0b100000, 0b1111000, 0b10011100, 0b1110000,
                         0b10001100, 0b10001000, 0b10000110, 0b10000000, 0b10110000, 0b10111000,
                         0b10111100, 0b10111110, 0b10111111, 0b10101111, 0b10100111,
                         0b10100011, 0b10100001};
    int8_t len = 0;
    int8_t len_code = 0;
    int8_t code = 0;
    int8_t j = 4;
    char a[128];
    while(1) {
        scanf("%[^\r\n]%c", a);
        printf("Odczytano: %s\r\n", a);
        for (int i = 0; i < strlen(a); i++) {
            len_code = (a[i] <= '9') ? morse[a[i] - '0' + 26] : morse[a[i] - 'A'];
            len = (len_code & 0b11100000) >> 5;
            code = len_code & 0b00011111;
            j = 4;
            while (len > 0) {
                if (((code >> j)&1) == 1) {
                    dioda(1);
                } else {
                    dioda(3);
                }
                j--;
                len--;
            }
        }
    }
}
