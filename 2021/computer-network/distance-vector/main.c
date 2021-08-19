#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <process.h>
#include "lib/argtable3.h"
#include "lib/cJSON.h"
#include "lib/logger.h"
#include "type.h"

#pragma comment(lib, "ws2_32.lib")

// Error code
#define ERROR_ARG 1
#define ERROR_FILE 2
#define ERROR_JSON 3
#define ERROR_SOCKET 4
#define ERROR_THREAD 5

// Max limitation
#define MAX_FILE_SIZE 1048576
#define MAX_BUFFER_SIZE 1048576
#define MAX_LINE_SIZE 1024

#define ACCESS_MUT_NAME "TABLE_ACCESS"

//////////////////////
// Global variables //
//////////////////////

// TODO: Packet this information into one struct
// Global config
int interval = 0;
double max_distance = 0;
int max_timeout = 0;
// Information of this node
struct Node *this = NULL;
int neighbor_count = 0;
struct Node **neighbors = NULL;
struct Table *routing_table = NULL;
// Sockets for communication
SOCKET sock;
struct sockaddr_in *addresses = NULL;
//timer
time_t send_timer = 0;
time_t *receive_timer;

////////////////////
// Core functions //
////////////////////

// Load init file function
int LoadInitFile(const char *filename);

// Thread function for sending routing table to neighbors
unsigned __stdcall SendToNeighbors(void *parameter);

// Thread function for receiving routing table from neighbors
unsigned __stdcall ReceiveFromNeighbors(void *parameter);

///////////////////////
// Utility functions //
///////////////////////

// Convert JSON string to Table type
struct Table *StringToTable(const char *string);

// Convert Table type to JSON string
char *TableToString(struct Table *table);

// Update Table
struct Table *Update(struct Table *neighbour);

// Print neighbors information
void PrintNeighbors();

// Print routing table information
void PrintTable(struct Table *table, int flag);

// Get neighbor index by id
int GetIndexById(const char *id);

///////////////////
// Main function //
///////////////////

int main(int argc, char **argv) {
    // Return status value
    int status = 0;

    /////////////////////////////////////////
    // Parse command line args and options //
    /////////////////////////////////////////

    // Generate command line parser
    char program_name[] = "dv.exe";
    struct arg_lit *arg_help;
    struct arg_str *arg_id;
    struct arg_int *arg_port;
    struct arg_file *arg_init_file;
    struct arg_end *arg_arg_end;
    void *arg_table[] = {
            arg_help = arg_litn("h", "help", 0, 1, "Display this arg_help and exit"),
            arg_id = arg_strn(NULL, NULL, "<id>", 1, 1, "ID of the router"),
            arg_port = arg_intn(NULL, NULL, "<port>", 1, 1, "Port of the router"),
            arg_init_file = arg_filen(NULL, NULL, "<init file>", 1, 1, "Init file of the router"),
            arg_arg_end = arg_end(20),
    };
    int errors = arg_parse(argc, argv, arg_table);
    // Command line --help option action
    if (arg_help->count > 0) {
        printf("Distance Vector Algorithm Simulation Program.\n\n");
        printf("Usage: %s", program_name);
        arg_print_syntax(stdout, arg_table, "\n\n");
        arg_print_glossary(stdout, arg_table, "  %-25s  %s\n");
        printf("\nPowered By ZSB & ZPY.\n");
        goto Cleanup;
    }
    // Command line errors action
    if (errors > 0) {
        /* Display the error details contained in the arg_end struct.*/
        arg_print_errors(stdout, arg_arg_end, program_name);
        printf("\nTry '%s --help' for more information.\n", program_name);
        status = ERROR_ARG;
        goto Cleanup;
    }

    ////////////////////
    // Initialization //
    ////////////////////

    // Initialize this node
    this = (struct Node *) malloc(sizeof(struct Node));
    this->id = (char *) malloc((strlen(arg_id->sval[0]) + 1) * sizeof(char));
    strcpy_s(this->id, strlen(arg_id->sval[0]) + 1, arg_id->sval[0]);
    this->port = arg_port->ival[0];

    // Load config from init file
    if (LoadInitFile(arg_init_file->filename[0])) {
        goto Cleanup;
    }

    // Initialize UDP socket
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
        Log(stderr, ERROR_LOG, "SocketInit", "Unable to find usable WinSock DLL");
        status = ERROR_SOCKET;
        goto Cleanup;
    }
    // Create sockets
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        Log(stderr, ERROR_LOG, "SocketInit", "Unable to create socket");
        status = ERROR_SOCKET;
        goto Cleanup;
    }
    // Define socket addresses
    addresses = (struct sockaddr_in *) malloc((neighbor_count + 1) * sizeof(struct sockaddr_in));
    // Define this socket address
    addresses[0].sin_family = AF_INET;
    addresses[0].sin_port = this->port;
    addresses[0].sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    // Define sockets addresses for neighbors
    for (int i = 1; i <= neighbor_count; i++) {
        addresses[i].sin_family = AF_INET;
        addresses[i].sin_port = neighbors[i - 1]->port;
        addresses[i].sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    }
    // Bind socket to source
    if (bind(sock, (struct sockaddr *) &addresses[0], sizeof(addresses[0])) == SOCKET_ERROR) {
        Log(stderr, ERROR_LOG, "SocketInit", "Unable to bind socket to address");
        status = ERROR_SOCKET;
        goto Cleanup;
    }
    // Set non-blocking config for sockets
    int imode = 1;
    if (ioctlsocket(sock, FIONBIO, (u_long *) &imode) == SOCKET_ERROR) {
        Log(stderr, ERROR_LOG, "SocketInit", "Unable to call ioctlsocket");
        status = ERROR_SOCKET;
        goto Cleanup;
    }

    // Initialize timers
    send_timer = clock() - interval / 1000 * CLOCKS_PER_SEC;
    receive_timer = (time_t *) malloc(neighbor_count * sizeof(time_t));
    for (int i = 0; i < neighbor_count; i++)
        receive_timer[i] = clock();

    ////////////////////////////
    // Exchange routing table //
    ////////////////////////////

    // Create threads
    HANDLE hAccessMut = CreateMutex(NULL, FALSE, ACCESS_MUT_NAME);
    //HANDLE send_thread = CreateThread(NULL, 0, SendToNeighbors, NULL, 0, NULL);
    unsigned int send_thread_id, receive_thread_id;
    HANDLE send_thread = (HANDLE) _beginthreadex(NULL, 0, (_beginthreadex_proc_type) SendToNeighbors,
                                                 NULL, 0, &send_thread_id);
    //HANDLE receive_thread = CreateThread(NULL, 0, ReceiveFromNeighbors, NULL, 0, NULL);
    HANDLE receive_thread = (HANDLE) _beginthreadex(NULL, 0, (_beginthreadex_proc_type) ReceiveFromNeighbors,
                                                    NULL, 0, &receive_thread_id);
    if (send_thread == NULL || receive_thread == NULL) {
        Log(stderr, ERROR_LOG, "CreateThreads", "Unable to create threads");
        status = ERROR_THREAD;
        goto Cleanup;
    } else {
        char command[10] = {0};
        while (1) {
            scanf_s("%s", command, 10);
            if (strcmp(command, "K") == 0) {
                printf("Kill this process.\n");
                TerminateThread(send_thread, 0);
                TerminateThread(receive_thread, 0);
                break;
            } else if (strcmp(command, "P") == 0) {
                printf("Pause this process.\n");
                SuspendThread(send_thread);
                SuspendThread(receive_thread);
            } else if (strcmp(command, "C") == 0) {
                printf("Continue this process.\n");
                ResumeThread(send_thread);
                ResumeThread(receive_thread);
            } else {
                printf("Invalid command, do nothing.\n");
            }
        }
        // Wait for threads
        WaitForSingleObject(send_thread, INFINITE);
        WaitForSingleObject(receive_thread, INFINITE);
        // Close threads
        CloseHandle(hAccessMut);
        CloseHandle(send_thread);
        CloseHandle(receive_thread);
    }

    //////////////////////
    // Cleanup and exit//
    //////////////////////

    Cleanup:

    // Cleanup WSA
    WSACleanup();
    // Free command line parser
    arg_freetable(arg_table, sizeof(arg_table) / sizeof(arg_table[0]));
    // Free this
    FreeNode(this);
    // Free neighbor table
    for (int i = 0; i < neighbor_count; i++)
        FreeNode(neighbors[i]);
    // Free routing table
    FreeTable(routing_table);
    // Close socket
    if (closesocket(sock) == SOCKET_ERROR) {
        // Log(stderr, ERROR_LOG, "Cleanup", "Unable to close socket");
        status = WSAGetLastError();
        // printf("%d\n", WSAGetLastError());
    }
    // Free addresses
    free(addresses);
    // Exit
    exit(status);
}


int LoadInitFile(const char *filename) {
    int status = 0;
    FILE *init_file;
    if (fopen_s(&init_file, filename, "r")) {
        Log(stderr, ERROR_LOG, "LoadInitFile",
            "Unable to open init file %s, please check your input.", filename);
        return ERROR_FILE;
    }
    char *file_buffer = (char *) malloc(MAX_FILE_SIZE * sizeof(char));
    memset(file_buffer, 0, MAX_FILE_SIZE * sizeof(char));
    char *line_buffer = (char *) malloc(MAX_LINE_SIZE * sizeof(char));
    while (!feof(init_file)) {
        fgets(line_buffer, MAX_LINE_SIZE, init_file);
        strcat_s(file_buffer, MAX_LINE_SIZE, line_buffer);
    }
    cJSON *init_json = cJSON_Parse(file_buffer);
    if (init_json == NULL) {
        const char *error_position = cJSON_GetErrorPtr();
        Log(stderr, ERROR_LOG, "LoadInitFile", "Syntax error near: %s", error_position);
        status = ERROR_JSON;
    } else {
        const cJSON *neighbor_json = NULL;
        const cJSON *neighbors_json = cJSON_GetObjectItem(init_json, "neighbors");
        neighbor_count = cJSON_GetArraySize(neighbors_json);
        neighbors = (struct Node **) malloc(neighbor_count * sizeof(struct Node *));
        routing_table = NewTable(this->id);
        int index = 0;
        cJSON_ArrayForEach(neighbor_json, neighbors_json) {
            cJSON *id_json = cJSON_GetObjectItem(neighbor_json, "id");
            cJSON *cost_json = cJSON_GetObjectItem(neighbor_json, "cost");
            cJSON *port_json = cJSON_GetObjectItem(neighbor_json, "port");
            // Initialize neighbor table
            neighbors[index] = NewNode(id_json->valuestring, port_json->valueint);
            // Initialize routing table
            if (index == 0) {
                routing_table->records_head = NewRecord(id_json->valuestring, cost_json->valuedouble,
                                                        id_json->valuestring);
                routing_table->records_tail = routing_table->records_head;
            } else {
                routing_table->records_tail->next_record = NewRecord(id_json->valuestring, cost_json->valuedouble,
                                                                     id_json->valuestring);
                routing_table->records_tail = routing_table->records_tail->next_record;
            }
            index++;
            routing_table->count = index;
        }
        const cJSON *config_json = cJSON_GetObjectItem(init_json, "config");
        const cJSON *interval_json = cJSON_GetObjectItem(config_json, "interval");
        interval = interval_json->valueint;
        const cJSON *max_distance_json = cJSON_GetObjectItem(config_json, "max_distance");
        max_distance = max_distance_json->valuedouble;
        const cJSON *max_timeout_json = cJSON_GetObjectItem(config_json, "max_timeout");
        max_timeout = max_timeout_json->valueint;
    }
    cJSON_Delete(init_json);
    free(line_buffer);
    free(file_buffer);
    fclose(init_file);
    return status;
}

struct Table *StringToTable(const char *string) {
    cJSON *json = cJSON_Parse(string);
    if (json == NULL) {
        const char *error_position = cJSON_GetErrorPtr();
        Log(stderr, ERROR_LOG, "StringToTable", "Syntax error near: %s", error_position);
        return NULL;
    } else {
        const cJSON *id_json = cJSON_GetObjectItem(json, "id");
        const cJSON *count_json = cJSON_GetObjectItem(json, "count");
        const cJSON *this_cost_json = cJSON_GetObjectItem(json, "cost");
        const cJSON *records_json = cJSON_GetObjectItem(json, "records");
        cJSON *record_json = NULL;
        struct Table *table = NewTable(id_json->valuestring);
        table->count = count_json->valueint;
        table->cost = this_cost_json->valuedouble;
        int index = 0;
        cJSON_ArrayForEach(record_json, records_json) {
            cJSON *destination_json = cJSON_GetObjectItem(record_json, "destination");
            cJSON *cost_json = cJSON_GetObjectItem(record_json, "cost");
            cJSON *next_hop_json = cJSON_GetObjectItem(record_json, "next_hop");
            if (index == 0) {
                table->records_head = NewRecord(destination_json->valuestring, cost_json->valuedouble,
                                                next_hop_json->valuestring);
                table->records_tail = table->records_head;
            } else {
                table->records_tail->next_record = NewRecord(destination_json->valuestring, cost_json->valuedouble,
                                                             next_hop_json->valuestring);
                table->records_tail = table->records_tail->next_record;
            }
            index++;
        }
        return table;
    }
}

char *TableToString(struct Table *table) {
    cJSON *json = cJSON_CreateObject();
    if (json == NULL) {
        Log(stderr, ERROR_LOG, "TableToString", "Unable to create cJSON object \"json\"");
        return NULL;
    }
    cJSON *id_json = cJSON_CreateString(table->id);
    if (id_json == NULL) {
        Log(stderr, ERROR_LOG, "TableToString", "Unable to create cJSON object \"id_json\"");
        cJSON_Delete(json);
        return NULL;
    }
    cJSON_AddItemToObject(json, "id", id_json);
    cJSON *count_json = cJSON_CreateNumber(table->count);
    if (count_json == NULL) {
        Log(stderr, ERROR_LOG, "TableToString", "Unable to create cJSON object \"count_json\"");
        cJSON_Delete(json);
        return NULL;
    }
    cJSON_AddItemToObject(json, "count", count_json);
    cJSON *this_cost_json = cJSON_CreateNumber(table->cost);
    if (this_cost_json == NULL) {
        Log(stderr, ERROR_LOG, "TableToString", "Unable to create cJSON object \"this_cost_json\"");
        cJSON_Delete(json);
        return NULL;
    }
    cJSON_AddItemToObject(json, "cost", this_cost_json);
    cJSON *records_json = cJSON_CreateArray();
    if (records_json == NULL) {
        Log(stderr, ERROR_LOG, "TableToString", "Unable to create cJSON object \"records_json\"");
        cJSON_Delete(json);
        return NULL;
    }
    cJSON_AddItemToObject(json, "records", records_json);
    struct Record *record = table->records_head;
    for (int i = 0; i < table->count; i++) {
        cJSON *record_json = cJSON_CreateObject();
        if (record_json == NULL) {
            Log(stderr, ERROR_LOG, "TableToString", "Unable to create cJSON object \"record_json\"");
            cJSON_Delete(json);
            return NULL;
        }
        cJSON_AddItemToArray(records_json, record_json);
        cJSON *destination_json = cJSON_CreateString(record->destination);
        if (destination_json == NULL) {
            Log(stderr, ERROR_LOG, "TableToString",
                "Unable to create cJSON object \"destination_json\" at index %d", i);
            cJSON_Delete(json);
            return NULL;
        }
        cJSON_AddItemToObject(record_json, "destination", destination_json);
        cJSON *cost_json = cJSON_CreateNumber(record->cost);
        if (cost_json == NULL) {
            Log(stderr, ERROR_LOG, "TableToString",
                "Unable to create cJSON object \"cost_json\" at index %d", i);
            cJSON_Delete(json);
            return NULL;
        }
        cJSON_AddItemToObject(record_json, "cost", cost_json);
        cJSON *next_hop_json = cJSON_CreateString(record->next_hop);
        if (next_hop_json == NULL) {
            Log(stderr, ERROR_LOG, "TableToString",
                "Unable to create cJSON object \"next_hop_json\" at index %d", i);
            cJSON_Delete(json);
            return NULL;
        }
        cJSON_AddItemToObject(record_json, "next_hop", next_hop_json);
        record = record->next_record;
    }
    return cJSON_Print(json);
}

void PrintNeighbors() {
    printf("%s has %d neighbors:\n", this->id, neighbor_count);
    for (int i = 0; i < neighbor_count; i++) {
        printf("No.%d\tDestination: %-10s Port: %-10d\n", i, neighbors[i]->id, neighbors[i]->port);
    }
}

void PrintTable(struct Table *table, int flag) {
    printf("Routing table of %s has %d records:\n", table->id, table->count);
    if (flag)
        printf("From %s to here cost %f\n", table->id, table->cost);
    struct Record *record = table->records_head;
    for (int i = 0; i < table->count; i++) {
        printf("No.%d\tDestination: %-10s Cost: %-10f NextHop: %-10s\n", i, record->destination, record->cost,
               record->next_hop);
        record = record->next_record;
    }
}

int GetIndexById(const char *id) {
    for (int i = 0; i < neighbor_count; i++)
        if (strcmp(neighbors[i]->id, id) == 0)
            return i;
}

unsigned __stdcall SendToNeighbors(void *parameter) {
    time_t now_time;
    HANDLE hAccessMut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, ACCESS_MUT_NAME);
    while (1) {
        now_time = clock();
        if ((now_time - send_timer) / CLOCKS_PER_SEC * 1000 >= interval) {
            send_timer = clock();
            for (int i = 0; i < neighbor_count; i++) {
                if (receive_timer[i] == -1) {
                    continue;
                }
                WaitForSingleObject(hAccessMut, INFINITE);
                struct Record *tmp = routing_table->records_head;
                while (tmp != NULL) {
                    if (strcmp(tmp->destination, neighbors[i]->id) == 0) {
                        routing_table->cost = tmp->cost;
                        break;
                    }
                    tmp = tmp->next_record;
                }
                char *buffer = TableToString(routing_table);
                ReleaseMutex(hAccessMut);
                addresses[i + 1].sin_port = neighbors[i]->port;
                printf("\n%d Send to: %s at %d\n", i, neighbors[i]->id, addresses[i + 1].sin_port);
                printf("i: %d timer: %lld now %lld\n", i, receive_timer[i], now_time);
                sendto(sock, buffer, strlen(buffer) + 1, 0, (struct sockaddr *) &addresses[i + 1],
                       sizeof(struct sockaddr));
                free(buffer);
            }
        }
    }
}

unsigned __stdcall ReceiveFromNeighbors(void *parameter) {
    char *buffer = (char *) malloc(MAX_BUFFER_SIZE * sizeof(char));
    HANDLE hAccessMut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, ACCESS_MUT_NAME);
    while (1) {
        time_t now_time = clock();
        if (recvfrom(sock, buffer, MAX_BUFFER_SIZE, 0,
                     NULL, NULL) > 0) {
            struct Table *received_table, *current_table;
            current_table = routing_table;
            received_table = StringToTable(buffer);
            int index = GetIndexById(received_table->id);

            printf("\n%d Received from: %s\n", index, neighbors[index]->id);
            printf("Before update:\n");
            PrintTable(routing_table, 0);

            if (receive_timer[index] == -1) {
                printf("\nThe router %s came back!\n", neighbors[index]->id);
                struct Record *temp = routing_table->records_head;
                while (temp != NULL) {
                    if (strcmp(temp->destination, neighbors[index]->id) == 0) {
                        temp->cost = received_table->cost;
                        free(temp->next_hop);
                        temp->next_hop = (char *) malloc((strlen(received_table->id) + 1) * sizeof(char));
                        strcpy_s(temp->next_hop, strlen(received_table->id) + 1, received_table->id);
                        break;
                    }
                    temp = temp->next_record;
                }
            }
            PrintTable(received_table, 1);
            receive_timer[index] = clock();
            WaitForSingleObject(hAccessMut, INFINITE);
            routing_table = Update(received_table);
            ReleaseMutex(hAccessMut);
            FreeTable(current_table);
            FreeTable(received_table);
            printf("After update:\n");
            PrintTable(routing_table, 0);
            printf("\n");
        }
        for (int i = 0; i < neighbor_count; i++) {
            if (receive_timer[i] != -1 && (now_time - receive_timer[i]) / CLOCKS_PER_SEC * 1000 > max_timeout) {
                printf("\nRouter %s is deleted!\n", neighbors[i]->id);
                struct Record *temp = routing_table->records_head;
                for (int j = 0; j < routing_table->count; j++) {
                    if (strcmp(neighbors[i]->id, temp->destination) == 0) {
                        temp->cost = max_distance;
                        receive_timer[i] = -1;
                        break;
                    }
                    temp = temp->next_record;
                }
            }
        }
    }
}

struct Table *Update(struct Table *neighbour) {
    struct Table *new_table = NewTable(routing_table->id);
    new_table->count = routing_table->count;
    new_table->records_head = NewRecord(routing_table->records_head->destination, routing_table->records_head->cost,
                                        routing_table->records_head->next_hop);
    new_table->records_tail = new_table->records_head;
    struct Record *old_record = routing_table->records_head;
    struct Record *new_record = new_table->records_head;
    while (old_record != routing_table->records_tail) {
        new_record->next_record = NewRecord(old_record->next_record->destination, old_record->next_record->cost,
                                            old_record->next_record->next_hop);
        new_record = new_record->next_record;
        old_record = old_record->next_record;
    }
    new_table->records_tail = new_record;
    if (new_table->records_head == NULL) {
        printf("new_table's routing table is null.");
    }
    struct Record *existed_record = new_table->records_head;
    double now_cost = -1;
    for (int i = 0; i < new_table->count; i++) {
        if (strcmp(existed_record->destination, neighbour->id) == 0) {
            now_cost = existed_record->cost;
        }
        existed_record = existed_record->next_record;
    }
    if (now_cost == -1) {
        printf("The node is not neighbour.");
    }
    if (neighbour->records_head == NULL) {
        printf("neighbour's routing table is null.");
    }
    struct Record *received_record = neighbour->records_head;
    for (int i = 0; i < neighbour->count; i++) {
        if (strcmp(received_record->destination, routing_table->id) == 0) {
            received_record = received_record->next_record;
            continue;
        }
        int f = 0;
        existed_record = new_table->records_head;
        for (int j = 0; j < new_table->count; j++) {
            if (strcmp(received_record->destination, existed_record->destination) == 0) {
                f = 1;
                if (existed_record->cost >= max_distance && received_record->cost + now_cost >= max_distance) {
                    existed_record->cost = max_distance;
                    break;
                }
                if (received_record->cost + now_cost < existed_record->cost) {
                    existed_record->cost = received_record->cost + now_cost;
                    free(existed_record->next_hop);
                    existed_record->next_hop = (char *) malloc((strlen(neighbour->id) + 1) * sizeof(char));
                    strcpy_s(existed_record->next_hop, strlen(neighbour->id) + 1, neighbour->id);
                } else {
                    if (strcmp(existed_record->next_hop, neighbour->id) == 0) {
                        existed_record->cost = received_record->cost + now_cost;
                    }
                }
                break;
            }
            existed_record = existed_record->next_record;
        }
        if (f == 0) {
            struct Record *now_record = NewRecord(received_record->destination, received_record->cost + now_cost,
                                                  neighbour->id);
            new_table->records_tail->next_record = now_record;
            new_table->records_tail = now_record;
            new_table->count++;
        }
        received_record = received_record->next_record;
    }
    return new_table;
}