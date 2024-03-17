#include "traceroute.h"

#define MAX_IP_STR_LEN 20

void handle_poll_error() {
    fprintf(stderr, "poll error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

void handle_recvfrom_error() {
    fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

void handle_sending_error() {
    fprintf(stderr, "Error sending ICMP request: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

void validate_ip(struct sockaddr_in *ip, char *ip_str) {
    if (!inet_ntop(AF_INET, &(ip->sin_addr), ip_str, MAX_IP_STR_LEN)) {
        fprintf(stderr, "inet_ntop error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void handle_socket_error() {
    fprintf(stderr, "socket error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}