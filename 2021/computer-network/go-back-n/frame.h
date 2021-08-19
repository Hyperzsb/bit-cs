#ifndef GO_BACK_N_FRAME_H
#define GO_BACK_N_FRAME_H

#include <stdio.h>
#include <Windows.h>

// Frame marcos
#define MAX_DATA_LENGTH 1024

struct Frame {
    int seq, ack, length;
    char data[MAX_DATA_LENGTH + 5];
    WORD checksum;
};

void CopyFrame(struct Frame *frame, struct Frame *another_frame);

int GetFrameData(FILE *file, struct Frame *frame);

int SaveFrameData(FILE *file, struct Frame *frame);

#endif //GO_BACK_N_FRAME_H
