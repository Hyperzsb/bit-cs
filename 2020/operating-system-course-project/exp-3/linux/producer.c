#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

// Error exit code
#define E_OPEN_FILE -4
// Total products to be produced
#define TOTAL_PRODUCTS_PRODUCED 4

void read_buffer(int pid, char *buffer_filename) {
    char line[100] = {0};
    FILE *file = fopen(buffer_filename, "r");
    if (!file) {
        char error_str[200] = {0};
        sprintf(error_str, "[PRODUCER][PID %5d] Unable to open file %s for read", pid, buffer_filename);
        perror(error_str);
        exit(E_OPEN_FILE);
    }
    fgets(line, 100, file);
    printf("[PRODUCER][PID %5d] Buffer: %s", pid, line);
    fclose(file);
}

void produce(int pid, char *buffer_filename) {
    const char products[8] = "HYPERZSB";
    char line[100] = {0};
    FILE *file = fopen(buffer_filename, "r");
    if (!file) {
        char error_str[200] = {0};
        sprintf(error_str, "[PRODUCER][PID %5d] Unable to open file %s for read", pid, buffer_filename);
        perror(error_str);
        exit(E_OPEN_FILE);
    }
    fgets(line, 100, file);
    fclose(file);
    for (int i = 0; line[i] != '\0'; i++)
        if (line[i] == '-') {
            char product = products[random() % 8];
            line[i] = product;
            printf("[PRODUCER][PID %5d] Produce product: %c\n", pid, product);
            break;
        }
    file = fopen(buffer_filename, "w");
    if (!file) {
        char error_str[200] = {0};
        sprintf(error_str, "[PRODUCER][PID %5d] Unable to open file %s for write", pid, buffer_filename);
        perror(error_str);
        exit(E_OPEN_FILE);
    }
    fprintf(file, "%s", line);
    fclose(file);
}

int main(int argc, char **argv) {
    const int pid = getpid();
    // Get semaphore info from arguments
    int sem_set_id = atoi(argv[0]),
            write_sem_index = atoi(argv[1]), read_sem_index = atoi(argv[2]), access_sem_index = atoi(argv[3]);
    // Get buffer filename
    char *buffer_filename = argv[4];
    struct sembuf sem_op;
    sem_op.sem_flg = 0;
    for (int i = 0; i < TOTAL_PRODUCTS_PRODUCED; i++) {
        sleep(random() % 3);
        // Ask for a write semaphore
        sem_op.sem_num = write_sem_index;
        sem_op.sem_op = -1;
        semop(sem_set_id, &sem_op, 1);
        // Ask for access semaphore
        sem_op.sem_num = access_sem_index;
        sem_op.sem_op = -1;
        semop(sem_set_id, &sem_op, 1);

        // Read buffer and produce a product
        read_buffer(pid, buffer_filename);
        produce(pid, buffer_filename);

        // Release a read semaphore
        sem_op.sem_num = read_sem_index;
        sem_op.sem_op = 1;
        semop(sem_set_id, &sem_op, 1);
        // Release access semaphore
        sem_op.sem_num = access_sem_index;
        sem_op.sem_op = 1;
        semop(sem_set_id, &sem_op, 1);
    }

    exit(0);
}
