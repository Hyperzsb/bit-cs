#include <stdio.h>
#include <Windows.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Too few arguments! Please check your input!\n");
        ExitProcess(1);
    } else if (argc >= 3) {
        fprintf(stderr, "Too many arguments! Please check your input!\n");
        ExitProcess(1);
    } else {
        // Get child process filename
        char filename[MAX_PATH];
        sprintf_s(filename, MAX_PATH, "%s", argv[1]);
        char cmdline[MAX_PATH];
        sprintf_s(cmdline, MAX_PATH, "\"%s\"", filename);
        // Init startupinfo
        STARTUPINFO startupinfo;
        ZeroMemory((void *) &startupinfo, sizeof startupinfo);
        startupinfo.cb = sizeof startupinfo;
        // Get start time
        SYSTEMTIME start_time;
        GetSystemTime(&start_time);
        char time_str[200];
        wsprintf(time_str, "%u-%u-%u %u:%u:%u:%u", start_time.wYear, start_time.wMonth, start_time.wDay,
                 start_time.wHour, start_time.wMinute, start_time.wSecond, start_time.wMilliseconds);
        printf("Start time: %s\n", time_str);
        // Create child process
        PROCESS_INFORMATION process_information;
        BOOL create_status = CreateProcess(filename, cmdline, NULL, NULL, FALSE, 0, NULL, NULL,
                                           &startupinfo, &process_information);
        // Check create status
        if (create_status) {
            printf("Child process started.\n");
            WaitForSingleObject(process_information.hProcess, INFINITE);
            printf("Child process finished.\n");
            // Get end time
            SYSTEMTIME end_time;
            GetSystemTime(&end_time);
            wsprintf(time_str, "%u-%u-%u %u:%u:%u:%u", end_time.wYear, end_time.wMonth, end_time.wDay,
                     end_time.wHour, end_time.wMinute, end_time.wSecond, end_time.wMilliseconds);
            printf("End time: %s\n", time_str);
            if (end_time.wMinute == start_time.wMinute)
                printf("Last time: %u ms\n",
                       (end_time.wSecond - start_time.wSecond) * 1000 + end_time.wMilliseconds -
                       start_time.wMilliseconds);
            else
                printf("Last time: %u ms\n",
                       (end_time.wSecond + 60 - start_time.wSecond) * 1000 + end_time.wMilliseconds -
                       start_time.wMilliseconds);
        } else {
            fprintf(stderr, "Create child process failed.\n");
        }

        printf("Parent process finished.\n");
        ExitProcess(0);
    }
}
