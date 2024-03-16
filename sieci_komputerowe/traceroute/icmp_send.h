#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

#ifndef TRACEROUTE_ICMP_SEND_H
#define TRACEROUTE_ICMP_SEND_H
void send_packets(int sock_fd, struct sockaddr_in recipient, struct timeval *send_times, int id, int requests_number, int ttl);
#endif //TRACEROUTE_ICMP_SEND_H
