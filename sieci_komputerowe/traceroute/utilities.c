// Julia Noczyńska 331013

#include "utilities.h"

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

void handle_socket_error() {
    fprintf(stderr, "socket error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

void allocate_array(char* array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = malloc(MAX_IP_STR_LEN);
        if (array[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            exit(EXIT_FAILURE);
        }
    }
}

void free_array(char* array[], int size) {
    for (int i = 0; i < size; i++) {
        free(array[i]);
    }
}

void validate_ip(struct sockaddr_in *ip, char *ip_str) {
    if (!inet_ntop(AF_INET, &(ip->sin_addr), ip_str, MAX_IP_STR_LEN)) {
        fprintf(stderr, "inet_ntop error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int timeval_to_ms(struct timeval time) {
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}