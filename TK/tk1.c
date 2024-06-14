#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2, pid3;

    // First fork - creates P2 and P3
    pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    if (pid1 == 0) {
        // This is P2
        printf("P2 (Child of P1) with PID: %d\n", getpid());
    } else {
        // Still in P1
        // Fork again to create P3
        pid2 = fork();

        if (pid2 < 0) {
            fprintf(stderr, "Fork Failed\n");
            return 1;
        }
        if (pid2 == 0) {
            // This is P3
            printf("P3 (Child of P1) with PID: %d\n", getpid());

            // Fork to create P4
            pid3 = fork();

            if (pid3 < 0) {
                fprintf(stderr, "Fork Failed\n");
                return 1;
            }
            if (pid3 == 0) {
                // This is P4
                printf("P4 (Child of P3) with PID: %d\n", getpid());
            } else {
                // Still in P3
                // Fork again to create P5
                pid3 = fork();

                if (pid3 < 0) {
                    fprintf(stderr, "Fork Failed\n");
                    return 1;
                }
                if (pid3 == 0) {
                    // This is P5
                    printf("P5 (Child of P3) with PID: %d\n", getpid());
                }
            }
        } else {
            // Still in P1
            printf("P1 (Original Parent) with PID: %d\n", getpid());
        }
    }

    // Ensures all processes wait before exiting
    sleep(1);

    return 0;
}
