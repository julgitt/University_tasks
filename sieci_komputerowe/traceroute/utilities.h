// Julia Noczyńska 331013

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#ifndef TRACEROUTE_UTILITIES_H
#define TRACEROUTE_UTILITIES_H

void handle_recvfrom_error();
void handle_sending_error();
void handle_poll_error();
void handle_socket_error();

void allocate_array(char* array[], int size);
void free_array(char* array[], int size);
void validate_ip(struct sockaddr_in *ip, char *ip_str);

int timeval_to_ms(struct timeval time);

#endif //TRACEROUTE_UTILITIES_H
