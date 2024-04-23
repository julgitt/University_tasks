#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <getopt.h>

#define BUF_SIZE 512
#define DEFAULT_PERIOD 1
#define DEFAULT_INTERVAL 60
#define DEFAULT_LOGFILE "/var/log/mystat.log"


static int PERIOD;
static int INTERVAL;
static char *LOGFILE;

void print_usage() {
    printf("Usage: mystat [OPTIONS]\n");
    printf("Options:\n");
    printf("  -p, --period    Set the period for reading CPU load (default: 1 second)\n");
    printf("  -i, --interval  Set the interval for logging (default: 60 seconds)\n");
    printf("  -f, --logfile   Set the logfile path (default: /var/log/mystat.log)\n");
}

void parse_options(int argc, char *argv[]) {
    int opt;
    static struct option long_options[] = {
        {"period",   required_argument, 0, 'p'},
        {"interval", required_argument, 0, 'i'},
        {"logfile",  required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };
    
    PERIOD = DEFAULT_PERIOD;
    INTERVAL = DEFAULT_INTERVAL;
    LOGFILE = strdup(DEFAULT_LOGFILE);

    while ((opt = getopt_long(argc, argv, "p:i:f:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'p':
                PERIOD = atoi(optarg);
                break;
            case 'i':
                INTERVAL = atoi(optarg);
                break;
            case 'f':
                free(LOGFILE);
                LOGFILE = strdup(optarg);
                break;
            default:
                print_usage();
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    parse_options(argc, argv);

    int fd;
    FILE *logfile;

    if ((fd = open("/proc/stat", O_RDONLY)) == -1) {
        perror("Failed to open /proc/stat");
        exit(EXIT_FAILURE);
    }

    if ((logfile = fopen(LOGFILE, "a")) == NULL) {
        perror("Failed to open logfile");
        exit(EXIT_FAILURE);
    }
	
	char buf[BUF_SIZE];
    unsigned long long prev_total = 0, prev_idle = 0;
    unsigned long long total;
    unsigned long long user, nice, system, idle, iowait, irq, softirq;
    int count = 0;
    double cpu_delta, cpu_idle, cpu_used, cpu_usage;
    double avg_usage = 0, max_usage = 0, min_usage = 100;

    while (1) {
        lseek(fd, 0, SEEK_SET);
        if (read(fd, buf, BUF_SIZE) == -1) {
            perror("Failed to read /proc/stat");
            exit(EXIT_FAILURE);
        }
        sscanf(buf, "cpu %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle, &iowait, &irq, &softirq);
        total = user + nice + system + idle + iowait + irq + softirq;
        
        cpu_delta = total - prev_total;
        cpu_idle = idle - prev_idle;
        cpu_used = cpu_delta - cpu_idle;
        
        cpu_usage = 100 * cpu_used / cpu_delta;
        
        avg_usage += cpu_usage;
        if (cpu_usage > max_usage) max_usage = cpu_usage;
        if (cpu_usage < min_usage) min_usage = cpu_usage;

        prev_total = total;
        prev_idle = idle;

        count++;

        if (count == INTERVAL / PERIOD) {
            avg_usage /= count;

            printf("Logfile updated.");
            fprintf(logfile, "Average usage: %.2lf%%, Max usage: %.2lf%%, Min usage: %.2lf%%\n",
                    avg_usage, max_usage, min_usage);
            fflush(logfile);

            avg_usage = 0;
            max_usage = 0;
            min_usage = 100;
            count = 0;
        }

        sleep(PERIOD);
    }

    close(fd);
    fclose(logfile);
    free(LOGFILE);

    return 0;
}

