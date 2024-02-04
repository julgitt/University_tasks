#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

int main() {
    
    // INT8_T
    int8_t a;
    int8_t b;
    
    scanf("%d %d", &a, &b);
    
    printf("%d", a + b);
    printf("%d", a * b);
    printf("%d", a / b);
    
    // INT16_T
    int16_t c;
    int16_t d;
    
    scanf("%d %d", &c, &d);
    
    printf("%d", c + d);
    printf("%d", c * d);
    printf("%d", c / d);
    
    // INT32_T
    int32_t e;
    int32_t f;
    
    scanf("%ld %ld", &e, &f);
    
    printf("%ld", e + f);
    printf("%ld", e * f);
    printf("%ld", e / f);
    
      
    // INT64_T
    int64_t i;
    int64_t j;
    
    int32_t k;
    int32_t l;
    scanf("%ld%ld", &k, &l);
    i = (k << 32) | l;
    
    scanf("%ld%ld", &k, &l);
    j = (k << 32) | l;
    
    printf("%ld%ld", (long)((i + j) >> 32));
    printf("%ld%ld", (long)((i * j) >> 32));
    printf("%ld%ld", (long)((i / j) >> 32));
    
    
    // FLOAT
    float g;
    float h;
    
    scanf("%f %f", &g, &h);
    
    printf("%f", g + h);
    printf("%f", g * h);
    printf("%f", g / h);
}
