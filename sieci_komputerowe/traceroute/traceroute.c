#include "traceroute.h"


#define MAX_HOPS 30
#define REQUESTS_NUMBER 3

void traceroute(int sock_fd, struct sockaddr_in recipient, char* ip) {
    struct timeval sending_times[REQUESTS_NUMBER] = {0}, receiving_times[REQUESTS_NUMBER] = {0};
    struct in_addr senders[REQUESTS_NUMBER];

    int id = getpid();
    int received_packets;

    for (int ttl = 1; ttl <= MAX_HOPS; ttl++) {
        printf("%d. ", ttl);
        setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

        send_packets(sock_fd, recipient, sending_times, id, REQUESTS_NUMBER, ttl);

        received_packets = receive_packets(sock_fd, receiving_times, REQUESTS_NUMBER, senders, ttl, id);

        char buf[20], buf2[20];

        if (received_packets == 0)
            fprintf(stdout, "*\n");
        else if (received_packets != REQUESTS_NUMBER) {
            for (int i = 0; i < REQUESTS_NUMBER; i++) {
                inet_ntop(AF_INET, &(senders[i]), buf, sizeof(buf));
                for (int j = 0; j < i; j++) {
                    inet_ntop(AF_INET, &(senders[i]), buf, sizeof(buf));
                    if (strcmp(buf, buf2))
                        continue;
                }
                fprintf(stdout, "%s\t", buf);
            }
            fprintf(stdout, "???\n");
        } else {
            long sum_time = 0;
            for (int i = 0; i < REQUESTS_NUMBER; i++) {
                inet_ntop(AF_INET, &(senders[i]), buf, sizeof(buf));
                sum_time += (receiving_times[i].tv_sec - sending_times[i].tv_sec) * 1000 +
                            (receiving_times[i].tv_usec - sending_times[i].tv_usec) / 1000;

                for (int j = 0; j <= i; j++) {
                    inet_ntop(AF_INET, &(senders[i]), buf, sizeof(buf));
                    if (i == j)
                        fprintf(stdout, "%s\t", buf);
                    if (strcmp(buf, buf2))
                        break;
                }

            }
            fprintf(stdout,"%ld ms\n",sum_time / received_packets);
        }
        if (strcmp(buf, ip) == 0) {
            break;
        }
    }

    close(sock_fd);
}

