#include "traceroute.h"

struct icmp create_header(int seq, int id) {
    struct icmp header;
    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_hun.ih_idseq.icd_id = id;
    header.icmp_hun.ih_idseq.icd_seq = seq;
    header.icmp_cksum = 0;
    header.icmp_cksum = compute_icmp_checksum (
            (u_int16_t*)&header, sizeof(header));
    return header;
}

void send_icmp_request(int sock_fd, const struct sockaddr_in recipient, int seq, int id) {
    struct icmp header = create_header(seq, id);

    ssize_t bytes_sent = sendto(sock_fd, &header, sizeof(header), 0, (struct sockaddr *) &recipient, sizeof(recipient));
    if (bytes_sent < 0) {
        fprintf(stderr, "Error sending ICMP request: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (bytes_sent != sizeof(header)) {
        fprintf(stderr, "Error sending ICMP request: Incomplete packet sent\n");
        exit(EXIT_FAILURE);
    }
}

void send_packets(int sock_fd, struct sockaddr_in recipient, struct timeval *send_times, int id, int requests_number, int ttl) {
    for (int i = 0; i < requests_number; i++) {
        send_icmp_request(sock_fd, recipient, ttl, id);
        gettimeofday(&send_times[i], NULL);
    }
}