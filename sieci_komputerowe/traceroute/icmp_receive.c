#include "traceroute.h"

#define TIMEOUT 1000

int receive_icmp_response(int sock_fd, struct in_addr *sender_ip, int ttl, int id) {
    struct pollfd ps;
    ps.fd = sock_fd;
    ps.events = POLLIN;
    ps.revents = 0;

    int ready = poll(&ps, 1, TIMEOUT);
    if (ready < 0) {
        fprintf(stderr, "poll error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (ready == 0) {
        return -1;
    }
    if (ps.revents == POLLIN) {
        struct sockaddr_in sender;
        socklen_t sender_len = sizeof(sender);
        u_int8_t buffer[IP_MAXPACKET];

        ssize_t packet_len = recvfrom(sock_fd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr *)&sender, &sender_len);
        if (packet_len < 0 && (errno != EAGAIN || errno !=  EWOULDBLOCK)) {
            fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        char sender_ip_str[20];
        if (!inet_ntop(AF_INET,
                      &(sender.sin_addr),
                      sender_ip_str,
                      sizeof(sender_ip_str))) {
            fprintf(stderr, "inet_ntop error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        struct ip *ip_header = (struct ip *)buffer;
        ssize_t ip_header_len = 4 * (ssize_t)(ip_header->ip_hl);

        struct icmp *data = (struct icmp *)((uint8_t *)ip_header + ip_header_len);

        if (data->icmp_type == ICMP_TIME_EXCEEDED){
            struct ip *ip_header1 = (struct ip *)((uint8_t *)data + 8);
            struct icmp *data1 = (struct icmp *)((uint8_t *)ip_header1 + ip_header_len);
            if(data1->icmp_seq==ttl && data1->icmp_id==id){
                *sender_ip=ip_header->ip_src;
                return 1;
            }
        } else if(data->icmp_type == ICMP_ECHOREPLY && data->icmp_seq==ttl && data->icmp_id==id){
            *sender_ip=ip_header->ip_src;
            return 1;
        }

    }
    return 0;
}

int receive_packets(int sock_fd, struct timeval *receive_times, int requests_number, struct in_addr *senders, int ttl, int id) {
    int received = 0;
    struct in_addr curr_ip;
    for (int i = 0; i < requests_number; i++) {
        int result = receive_icmp_response(sock_fd, &curr_ip, ttl, id);
        if (result == 1) {
            senders[i] = curr_ip;
            gettimeofday(&receive_times[i], NULL);
            received++;
        }
    }
    return received;
}