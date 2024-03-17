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

void handle_recvfrom_error();

void handle_sending_error();

void handle_poll_error();

void handle_socket_error();

void validate_ip(struct sockaddr_in *ip, char *ip_str);


void traceroute(int sock_fd, struct sockaddr_in recipient, char* ip);
void send_packets(int sock_fd, struct sockaddr_in recipient, int ttl, int id, struct timeval *sending_times, int requests_number);
int receive_packets(int sock_fd, char* senders[], int ttl, int id, struct timeval *receiving_times, int requests_number);
uint16_t compute_icmp_checksum(const void *buf, int len);


#endif //TRACEROUTE_TRACEROUTE_H
