#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

// Error exit code
#define E_CREATE_SEM -1
#define E_CTL_SEM -2
#define E_CREATE_PROC -3
#define E_OPEN_FILE -4
// Semaphore attributes
#define SEM_KEY 1120180
#define WRITE_SEM_INDEX 0
#define READ_SEM_INDEX 1
#define ACCESS_SEM_INDEX 2
// Buffer attributes
#define BUFFER_FILENAME "../buffer.txt"
#define BUFFER_MAX 4
// Producer and consumer number
#define TOTAL_PRODUCERS 3
#define TOTAL_CONSUMERS 4

void init_buffer(char *buffer_filename) {
    FILE *file = fopen(buffer_filename, "w");
    if (!file) {
        perror("Unable to initialize buffer.");
        exit(E_OPEN_FILE);
    }
    fprintf(file, "| - | - | - | - |\n");
    fclose(file);
}

int main() {
    // Initialize buffer
    init_buffer(BUFFER_FILENAME);
    // Get a semaphore set
    int sem_set_id = semget(SEM_KEY, 3, IPC_CREAT | SEM_A | SEM_R);
    if (sem_set_id == -1) {
        perror("Unable to get a semaphore set");
        exit(E_CREATE_SEM);
    }

    // Initialize semaphore set
    union semun sem_val;
    sem_val.val = BUFFER_MAX;
    if (semctl(sem_set_id, WRITE_SEM_INDEX, SETVAL, sem_val) == -1) {
        perror("Unable to set semaphore value for write");
        exit(E_CTL_SEM);
    }
    sem_val.val = 0;
    if (semctl(sem_set_id, READ_SEM_INDEX, SETVAL, sem_val) == -1) {
        perror("Unable to set semaphore value for read");
        exit(E_CTL_SEM);
    }
    sem_val.val = 1;
    if (semctl(sem_set_id, ACCESS_SEM_INDEX, SETVAL, sem_val) == -1) {
        perror("Unable to set semaphore value for access");
        exit(E_CTL_SEM);
    }

    // Initialize argument strings for child processes
    char sem_set_id_str[20] = {0};
    sprintf(sem_set_id_str, "%d", sem_set_id);
    char write_sem_index_str[5] = {0}, read_sem_index_str[5] = {0}, access_sem_index_str[5] = {0};
    sprintf(write_sem_index_str, "%d", WRITE_SEM_INDEX);
    sprintf(read_sem_index_str, "%d", READ_SEM_INDEX);
    sprintf(access_sem_index_str, "%d", ACCESS_SEM_INDEX);

    // Create producers and consumers
    pid_t *producer_pid = (pid_t *) malloc(TOTAL_PRODUCERS * sizeof(pid_t)),
            *consumer_pid = (pid_t *) malloc(TOTAL_CONSUMERS * sizeof(pid_t));
    // Create TOTAL_PRODUCERS producers
    for (int i = 0; i < TOTAL_PRODUCERS; i++) {
        producer_pid[i] = fork();
        if (producer_pid[i] == -1) {
            perror("Unable to create producer process");
            exit(E_CREATE_PROC);
        } else if (producer_pid[i] == 0) {
            execl("./producer",
                  sem_set_id_str, write_sem_index_str, read_sem_index_str, access_sem_index_str, BUFFER_FILENAME,
                  NULL);
        } else
            continue;
    }
    // Create TOTAL_CONSUMERS consumers
    for (int i = 0; i < TOTAL_CONSUMERS; i++) {
        consumer_pid[i] = fork();
        if (consumer_pid[i] == -1) {
            perror("Unable to create consumer process");
            exit(E_CREATE_PROC);
        } else if (consumer_pid[i] == 0) {
            execl("./consumer",
                  sem_set_id_str, write_sem_index_str, read_sem_index_str, access_sem_index_str, BUFFER_FILENAME,
                  NULL);
        } else
            continue;
    }

    // Wait for child processes
    // waitpid(0, NULL, 0);
    for (int i = 0; i < TOTAL_PRODUCERS + TOTAL_CONSUMERS; i++)
        wait(NULL);
    // Main process exit
    printf("Main process finished.\n");
    exit(0);
}