#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <sys/time.h>

#ifndef TRACEROUTE_ICMP_RECEIVE_H
#define TRACEROUTE_ICMP_RECEIVE_H

int receive_packets(int sock_fd, struct timeval *receive_times, int requests_number, struct in_addr *senders, int ttl, int id);

#endif //TRACEROUTE_ICMP_RECEIVE_H
