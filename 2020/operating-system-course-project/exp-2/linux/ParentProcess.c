#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Too few arguments! Please check your input!\n");
        exit(1);
    } else if (argc >= 3) {
        fprintf(stderr, "Too many arguments! Please check your input!\n");
        exit(1);
    } else {
        struct timeval start_time, end_time;
        struct tm *time;
        char time_str[100];
        // Get and print start time
        gettimeofday(&start_time, NULL);
        time = gmtime(&start_time.tv_sec);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time);
        printf("Start time: %s:%d\n", time_str, start_time.tv_usec / 1000);
        // Call fork() to create child process
        pid_t pid;
        pid = fork();
        if (pid == -1) {
            // Failed to create child process, abort
            fprintf(stderr, "Failed to call fork()! Please try again later!\n");
            exit(-1);
        } else if (pid == 0) {
            // Start child process
            printf("Child process started.\n");
            execv(argv[1], NULL);
            printf("Child process finished.\n");
            exit(0);
        } else {
            // Return to parent process
            printf("Returned to Parent process.\n");
            wait(0);
            // Get and print end time
            gettimeofday(&end_time, NULL);
            time = gmtime(&end_time.tv_sec);
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time);
            printf("End time: %s:%d\n", time_str, end_time.tv_usec / 1000);
            printf("Last time: %.3lf ms\n", (double) (end_time.tv_sec - start_time.tv_sec) * 1000 +
                                            (double) (end_time.tv_usec - start_time.tv_usec) / 1000);
            printf("Parent process finished.\n");
            exit(0);
        }
    }
}
