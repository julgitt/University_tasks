#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <time.h>


#define RED_PIN PB2
#define GREEN_PIN PB1
#define BLUE_PIN PB3
#define LED_DDR DDRB

const uint16_t values[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
    2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9,
    10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 17, 17, 17, 18, 18,
    18, 19, 19, 20, 20, 20, 21, 21, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 26, 26, 27, 27, 28, 28, 29,
    29, 30, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41,
    41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 49, 50, 51, 52, 53, 54, 55, 56,
    57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 73, 74, 75, 76, 77, 78, 78, 79,
    80, 81, 82, 82, 83, 84, 85, 85, 86, 87, 87, 88, 89, 89, 90, 90, 91, 92, 92, 93, 93, 94, 94, 94, 95,
    95, 96, 96, 96, 97, 97, 97, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99};

void hsv_to_rgb(uint32_t h, uint32_t v, uint32_t *red, uint32_t *green, uint32_t *blue) {
    int c = v;
    int x = c * (60 - abs(h % 120 - 60)) / 60;

    int r, g, b;

    if (h >= 0 && h < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (h >= 60 && h < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (h >= 180 && h < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (h >= 240 && h < 300) {
        r = x;
        g = 0;
        b = c;
    } else {
        r = c;
        g = 0;
        b = x;
    }

    *red = r * 255 / 100;
    *green = g * 255 / 100;
    *blue = b * 255 / 100;
}

void timers_init() {
    ICR1 = 255;
    
    // 	OCR1A OCR1B
    // Fast PWN, TOP - ICR
    // Prescaler 256
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
    TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS12);

    // OCR2A
    TCCR2A = _BV(COM2A1) | _BV(WGM20) | _BV(WGM21);
    TCCR2B = _BV(CS21) | _BV(CS22);

    LED_DDR |= _BV(RED_PIN) | _BV(GREEN_PIN) | _BV(BLUE_PIN);
}

int main() {
    // uruchom liczniki
    timers_init();

    uint8_t direction;
    uint32_t hue;
    uint32_t value;
    uint32_t end_of_arr = sizeof(values) / sizeof(values[0]) - 1;
    uint32_t r = 0, g = 0, b = 0;

    while (1) {
        direction = 1;
        hue = (rand() % 360);
        for (int i = 0; i >= 0;) {
            while (TCNT1 != 0);
            value = pgm_read_word(&(values[i]));
            if (i == end_of_arr)
                direction = 0;

            hsv_to_rgb(hue, value, &r, &g, &b);
            OCR1A = (255 - g);
            OCR1B = (255 - r);
            OCR2A = (255 - b);
            if (direction)
                i++;
            else
                i--;
        }
    }
}
