#ifndef DISTANCE_VECTOR_TYPE_H
#define DISTANCE_VECTOR_TYPE_H

struct Node {
    char *id;
    int port;
};

struct Record {
    char *destination;
    double cost;
    char *next_hop;
    struct Record *next_record;
};

struct Table {
    char *id;
    int count;
    double cost;
    struct Record *records_head;
    struct Record *records_tail;
};

struct Node *NewNode(const char *id, int port);

struct Record *NewRecord(const char *destination, double cost, const char *next_hop);

struct Table *NewTable(const char *id);

void FreeNode(struct Node *node);

void FreeRecord(struct Record *record);

void FreeTable(struct Table *table);

#endif //DISTANCE_VECTOR_TYPE_H
