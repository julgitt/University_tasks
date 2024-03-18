// Julia Noczyńska 331013

#include "traceroute.h"
#include "utilities.h"

#define TIMEOUT 1000
#define MAX_IP_STR_LEN 20
#define RETURNED_TIMEOUT 2
#define FOUND 0
#define NOT_FOUND 1

int receive_icmp_response(int sock_fd, char *sender_ip_str, int ttl, int id);
int handle_response(int sock_fd, char *sender_ip_str, int ttl, int id);
int is_valid_response(struct ip *buffer, int id, int ttl);

int receive_packets(int sock_fd, char* senders[], int ttl, int id, struct timeval *receiving_times, int requests_number) {
    int received = 0;
    char sender_ip_str[MAX_IP_STR_LEN];

    struct timeval start;
    gettimeofday(&start, NULL);
    int start_time = timeval_to_ms(start);
    int end_time = 0;
    while (received < requests_number && end_time < start_time + TIMEOUT) {
        int result = receive_icmp_response(sock_fd, sender_ip_str, ttl, id);
        if (result == FOUND) {
            strncpy(senders[received], sender_ip_str, MAX_IP_STR_LEN);
            gettimeofday(&receiving_times[received], NULL);
            received++;
        } else if (result == RETURNED_TIMEOUT){
            return received;
        }
        end_time = timeval_to_ms(receiving_times[received]);
    }
    return received;
}

int receive_icmp_response(int sock_fd, char *sender_ip_str, int ttl, int id) {
    struct pollfd ps;
    ps.fd = sock_fd;
    ps.events = POLLIN;
    ps.revents = 0;

    int ready = poll(&ps, 1, TIMEOUT);
    if (ready < 0) handle_poll_error();
    if (ready == 0) return RETURNED_TIMEOUT;
    if (ps.revents == POLLHUP) handle_poll_error();
    if (ps.revents != POLLIN) return NOT_FOUND;

    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    ssize_t packet_len = recvfrom(sock_fd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr *)&sender, &sender_len);
    if (packet_len < 0)
        handle_recvfrom_error();

    char sender_ip[ MAX_IP_STR_LEN];
    validate_ip(&sender, sender_ip);

    if (is_valid_response((struct ip *)buffer, id, ttl) == 1) {
        strncpy(sender_ip_str, sender_ip, MAX_IP_STR_LEN);
        return FOUND;
    }
    return NOT_FOUND;
}

int is_valid_response(struct ip* ip_header, int id, int ttl) {
    ssize_t ip_header_len = 4 * (ssize_t)(ip_header->ip_hl);

    struct icmp *data = (struct icmp *)((uint8_t *)ip_header + ip_header_len);

    if (data->icmp_type == ICMP_TIME_EXCEEDED){
        struct ip *ip_header1 = (struct ip *)((uint8_t *)data + 8);
        struct icmp *data1 = (struct icmp *)((uint8_t *)ip_header1 + ip_header_len);
        if(data1->icmp_seq==ttl && data1->icmp_id==id)
            return 1;
    } else if(data->icmp_type == ICMP_ECHOREPLY && data->icmp_seq==ttl && data->icmp_id==id)
        return 1;
    return 0;
}
