// Julia Noczyńska 331013
#include "traceroute.h"

uint16_t compute_icmp_checksum (const void *buff, int length)
{
    const uint16_t* ptr = buff;
    uint32_t sum = 0;
    assert (length % 2 == 0);
    for (; length > 0; length -= 2)
        sum += *ptr++;
    sum = (sum >> 16U) + (sum & 0xffffU);
    return (uint16_t)(~(sum + (sum >> 16U)));
}

