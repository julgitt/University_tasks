#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "traceroute.h"

struct sockaddr_in convert_ip_address(char* ip_addr) {
    struct sockaddr_in sock_addr;
    bzero(&sock_addr, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;

    if (inet_pton(AF_INET, ip_addr, &(sock_addr.sin_addr)) <= 0) {
        if (errno == 0) {
            fprintf(stderr, "Error: Invalid IP address\n");
        } else {
            fprintf(stderr, "Error: Conversion error: %s\n", strerror(errno));
        }
        exit(EXIT_FAILURE);
    }
    return sock_addr;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <destination_ip>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct sockaddr_in recipient = convert_ip_address(argv[1]);

    int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sock_fd < 0) handle_socket_error();

    traceroute(sock_fd, recipient, argv[1]);

    return EXIT_SUCCESS;
}