// Julia Noczyńska 331013

#include "traceroute.h"
#include "utilities.h"

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
    if (bytes_sent < 0) handle_sending_error();
}

void send_packets(int sock_fd, struct sockaddr_in recipient, int ttl, int id, struct timeval *sending_times, int requests_number) {
    for (int i = 0; i < requests_number; i++) {
        send_icmp_request(sock_fd, recipient, ttl, id);
        gettimeofday(&sending_times[i], NULL);
    }
}