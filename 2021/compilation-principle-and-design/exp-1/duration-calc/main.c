#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define ITERATION_COUNT 10

int main(int argc, char *argv[])
{
    double duration[ITERATION_COUNT] = {0};
    double total_duration = 0;
    double average_duration = 0;
    // Initialize child args
    char **child_argv = (char **)malloc(argc * sizeof(char *));
    for (int i = 1; i < argc; i++)
        child_argv[i - 1] = argv[i];
    child_argv[argc - 1] = NULL;
    printf("Executing: \"");
    for (int i = 0; i < argc - 1; i++)
        printf(" %s", child_argv[i]);
    printf(" \"\n");
    // Start iteration
    struct timeval start_time, end_time;
    for (int i = 0; i < ITERATION_COUNT; i++)
    {
        // Get start time
        gettimeofday(&start_time, NULL);
        // Call fork() to create child process
        pid_t pid;
        pid = fork();
        if (pid == -1)
        {
            // Failed to create child process, abort
            perror("FORK ERROR");
            exit(-1);
        }
        else if (pid == 0)
        {
            // Call execv to execute command
            int status = execv(argv[1], child_argv);
            if (status == -1)
            {
                // Failed to execute command, abort
                perror("EXECV ERROR");
                exit(-1);
            }
            exit(0);
        }
        else
        {
            // Wait for child process
            wait(0);
            // Get end time
            gettimeofday(&end_time, NULL);
            // Calculate duration
            printf("No.%d iteration duration: %.3lf ms\n", i + 1, (double)(end_time.tv_sec - start_time.tv_sec) * 1000 + (double)(end_time.tv_usec - start_time.tv_usec) / 1000);
            duration[i] = (double)(end_time.tv_sec - start_time.tv_sec) * 1000 + (double)(end_time.tv_usec - start_time.tv_usec) / 1000;
            total_duration += duration[i];
        }
    }
    // Calculate average duration
    average_duration = total_duration / ITERATION_COUNT;
    printf("Average duration: %.3lf ms\n", average_duration);

    exit(0);
}
