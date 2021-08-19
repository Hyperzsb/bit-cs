#include <string.h>
#include <stdlib.h>
#include "type.h"

struct Node *NewNode(const char *id, int port) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->id = (char *) malloc((strlen(id) + 1) * sizeof(char));
    strcpy_s(node->id, strlen(id) + 1, id);
    node->port = port;
    return node;
}

struct Record *NewRecord(const char *destination, double cost, const char *next_hop) {
    struct Record *record = (struct Record *) malloc(sizeof(struct Record));
    record->destination = (char *) malloc((strlen(destination) + 1) * sizeof(char));
    strcpy_s(record->destination, strlen(destination) + 1, destination);
    record->cost = cost;
    record->next_hop = (char *) malloc((strlen(next_hop) + 1) * sizeof(char));
    strcpy_s(record->next_hop, strlen(next_hop) + 1, next_hop);
    record->next_record = NULL;
    return record;
}

struct Table *NewTable(const char *id) {
    struct Table *table = (struct Table *) malloc(sizeof(struct Table));
    table->id = (char *) malloc((strlen(id) + 1) * sizeof(char));
    strcpy_s(table->id, strlen(id) + 1, id);
    table->count = 0;
    table->cost = 0;
    table->records_head = NULL;
    table->records_tail = NULL;
    return table;
}

void FreeNode(struct Node *node) {
    if (node == NULL)
        return;
    free(node->id);
    free(node);
}

void FreeRecord(struct Record *record) {
    if (record == NULL)
        return;
    free(record->destination);
    free(record->next_hop);
    free(record);
}

void FreeTable(struct Table *table) {
    if (table == NULL)
        return;
    free(table->id);
    for (int i = 0; i < table->count; i++) {
        struct Record *temp = table->records_head;
        table->records_head = table->records_head->next_record;
        FreeRecord(temp);
    }
    free(table);
}