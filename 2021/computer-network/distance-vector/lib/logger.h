#ifndef GO_BACK_N_LOGGER_H
#define GO_BACK_N_LOGGER_H

#include <time.h>
#include <stdio.h>
#include <Windows.h>

#define MAX_MSG_LENGTH 4096

enum LogLevel {
    DEBUG_LOG = 0,
    INFO_LOG = 1,
    WARNING_LOG = 2,
    ERROR_LOG = 3
};

void Log(FILE *file, enum LogLevel level, const char *entity, const char *msg, ...);

#endif //GO_BACK_N_LOGGER_H
