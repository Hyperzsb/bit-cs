# include "frame.h"

void CopyFrame(struct Frame *frame, struct Frame *another_frame) {
    another_frame->seq = frame->seq;
    another_frame->ack = frame->ack;
    another_frame->length = frame->length;
    memset(another_frame->data, 0, (unsigned) _countof(another_frame->data));
    if (frame->length >= 0) {
        for (int i = 0; i < frame->length; i++) {
            another_frame->data[i] = frame->data[i];
        }
    }
    another_frame->checksum = frame->checksum;
}

int GetFrameData(FILE *file, struct Frame *frame) {
    memset(frame->data, 0, _countof(frame->data));
    char character = '\0';
    int count = 0;
    while ((character = (char) fgetc(file)) != EOF && count < 1023) {
        frame->data[count++] = character;
    }
    if (character != EOF) {
        frame->data[count++] = character;
        frame->length = count;
        return 0;
    } else {
        frame->length = count;
        return 1;
    }
}

int SaveFrameData(FILE *file, struct Frame *frame) {
    if (frame->length == -1)
        return 1;
    for (int i = 0; i < frame->length; i++) {
        fputc(frame->data[i], file);
    }
    return 0;
}