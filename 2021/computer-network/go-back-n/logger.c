#include "logger.h"

void Log(FILE *file, enum LogLevel level, const char *entity, const char *msg, ...) {
    struct tm time_struct;
    time_t time_type;
    time(&time_type);
    localtime_s(&time_struct, &time_type);
    char time_str[64] = {0};
    strftime(time_str, (unsigned) _countof(time_str), "%Y-%m-%d %H:%M:%S", &time_struct);
    char vmsg[MAX_MSG_LENGTH] = {0};
    va_list args;
            va_start(args, msg);
    vsprintf_s(vmsg, (unsigned) _countof(vmsg), msg, args);
            va_end(args);
    switch (level) {
        case DEBUG_LOG: {
            fprintf_s(file, "[%s][DEBUG ~ %s] %s\n", entity, time_str, vmsg);
            break;
        }
        case INFO_LOG: {
            fprintf_s(file, "[%s][INFO ~ %s] %s\n", entity, time_str, vmsg);
            break;
        }
        case WARNING_LOG: {
            fprintf_s(file, "[%s][WARNING ~ %s] %s\n", entity, time_str, vmsg);
            break;
        }
        case ERROR_LOG: {
            fprintf_s(file, "[%s][ERROR ~ %s] %s\n", entity, time_str, vmsg);
            break;
        }
        default: {
            fprintf_s(file, "[%s][UNKNOWN ~ %s] %s\n", entity, time_str, vmsg);
            break;
        }
    }
}

