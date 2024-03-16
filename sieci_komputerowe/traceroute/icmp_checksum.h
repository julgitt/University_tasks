#include <assert.h>
#include <stdint.h>

#ifndef TRACEROUTE_ICMP_CHECKSUM_H
#define TRACEROUTE_ICMP_CHECKSUM_H
uint16_t compute_icmp_checksum(const void *buf, int len);
#endif //TRACEROUTE_ICMP_CHECKSUM_H
