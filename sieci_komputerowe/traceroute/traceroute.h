#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/time.h>
#include <assert.h>
#include <stdint.h>


#ifndef TRACEROUTE_TRACEROUTE_H
#define TRACEROUTE_TRACEROUTE_H

void traceroute(int sock_fd, struct sockaddr_in recipient, char* ip);
void send_packets(int sock_fd, struct sockaddr_in recipient, struct timeval *send_times, int id, int requests_number, int ttl);
int receive_packets(int sock_fd, struct timeval *receive_times, int requests_number, struct in_addr *senders, int ttl, int id);
uint16_t compute_icmp_checksum(const void *buf, int len);

#endif //TRACEROUTE_TRACEROUTE_H
