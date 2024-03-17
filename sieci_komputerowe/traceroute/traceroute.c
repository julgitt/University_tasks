#include "traceroute.h"

#define MAX_IP_STR_LEN 20
#define MAX_HOPS 30
#define REQUESTS_NUMBER 3

void allocate_memory(char* array[], int size);
void free_memory(char* array[], int size);
void print_result(int ttl, char* senders[], int received_packets,
                  struct timeval *sending_times, struct timeval *receiving_times);

void print_senders(char* senders[], int number);

long calculate_avr_time(struct timeval *sending_times, struct timeval *receiving_times, int received_packets);

void traceroute(int sock_fd, struct sockaddr_in recipient, char* ip) {
    struct timeval sending_times[REQUESTS_NUMBER] = {0}, receiving_times[REQUESTS_NUMBER] = {0};
    char* senders[REQUESTS_NUMBER];
    allocate_memory(senders, REQUESTS_NUMBER);

    int id = getpid();
    int received_packets;

    for (int ttl = 1; ttl <= MAX_HOPS; ttl++) {
        setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

        send_packets(sock_fd, recipient, ttl, id, sending_times, REQUESTS_NUMBER);
        received_packets = receive_packets(sock_fd, senders, ttl, id, receiving_times, REQUESTS_NUMBER);

        print_result(ttl, senders, received_packets, sending_times, receiving_times);
        if (strcmp(senders[0], ip) == 0)
            break;
    }

    free_memory(senders, REQUESTS_NUMBER);
    close(sock_fd);
}

void allocate_memory(char* array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = malloc(MAX_IP_STR_LEN);
        if (array[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            exit(EXIT_FAILURE);
        }
    }
}

void free_memory(char* array[], int size) {
    for (int i = 0; i < size; i++) {
        free(array[i]);
    }
}

void print_result(int ttl, char* senders[], int received_packets,
               struct timeval *sending_times, struct timeval *receiving_times) {
    printf("%d. ", ttl);
    if (received_packets == 0) {
        fprintf(stdout, "*\n");
        return;
    }
    if (received_packets != REQUESTS_NUMBER) {
        print_senders(senders, received_packets);
        fprintf(stdout, "???\n");
        return;
    }

    print_senders(senders, received_packets);

    fprintf(stdout,"%ld ms\n", calculate_avr_time(sending_times, receiving_times, received_packets));
}

void print_senders(char* senders[], int number) {
    for (int i = 0; i < number; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j)
                fprintf(stdout, "%s\t", senders[i]);
            if (strcmp(senders[i], senders[j]) == 0)
                break;
        }
    }
}

long calculate_avr_time(struct timeval *sending_times, struct timeval *receiving_times, int received_packets) {
    long sum_time = 0;
    for (int i = 0; i < REQUESTS_NUMBER; i++) {
        sum_time += (receiving_times[i].tv_sec - sending_times[i].tv_sec) * 1000 +
                    (receiving_times[i].tv_usec - sending_times[i].tv_usec) / 1000;

    }
    return sum_time / received_packets;
}
