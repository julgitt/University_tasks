#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Proces potomny
        printf("Proces potomny (PID: %d) startuje.\n", getpid());
        sleep(20);
        printf("Proces potomny (PID: %d) kończy się.\n", getpid());
        exit(EXIT_SUCCESS);
    } else { // Proces macierzysty
        printf("Proces macierzysty (PID: %d) czeka na zakończenie procesu potomnego (PID: %d).\n", getpid(), pid);
        sleep(50);
        printf("Proces macierzysty (PID: %d) zakończył się.\n", getpid());
    }

/*
        printf("Proces macierzysty (PID: %d) czeka na zakończenie procesu potomnego (PID: %d).\n", getpid(), pid);
        int status;
        pid_t child_pid = waitpid(pid, &status, 0); // Oczekiwanie na zakończenie procesu potomnego
        if (child_pid > 0) {
            if (WIFEXITED(status)) {
                printf("Proces macierzysty: Proces potomny (PID: %d) zakończył się z kodem powrotu %d.\n", child_pid, WEXITSTATUS(status));
            } else {
                printf("Proces macierzysty: Proces potomny (PID: %d) zakończył się niepoprawnie.\n", child_pid);
            }
        } else {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        printf("Proces macierzysty (PID: %d) zakończył się.\n", getpid());
    }
*/
    return 0;
}

