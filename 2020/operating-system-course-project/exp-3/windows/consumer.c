#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// Exit error code
#define E_OPEN_SEM_MUT -1
#define E_OPEN_FILE -3
// Semaphore and mutex arguments index
#define WRITE_SEM_NAME_INDEX 2
#define READ_SEM_NAME_INDEX 3
#define ACCESS_MUT_NAME_INDEX 4
// Total products to be consumed
#define TOTAL_PRODUCTS_CONSUMED 3

void ReadBuffer(int nPid, char *szBufferFilename) {
    FILE *pFile = fopen(szBufferFilename, "r");
    char szLine[100] = {0};
    if (!pFile) {
        char error_str[200] = {0};
        sprintf(error_str, "[PRODUCER][PID %5d] Unable to open file %s for read", nPid, szBufferFilename);
        perror(error_str);
        exit(E_OPEN_FILE);
    }
    fgets(szLine, 100, pFile);
    printf("[PRODUCER][PID %5d] Buffer: %s", nPid, szLine);
    fclose(pFile);
}

void Consume(int nPid, char *szBufferFilename) {
    char szLine[100] = {0};
    FILE *pFile = fopen(szBufferFilename, "r");
    if (!pFile) {
        char szError[200] = {0};
        sprintf(szError, "[CONSUMER][PID %5d] Unable to open file %s for read", nPid, szBufferFilename);
        perror(szError);
        exit(E_OPEN_FILE);
    }
    fgets(szLine, 100, pFile);
    fclose(pFile);
    char cProduct = szLine[2];
    printf("[CONSUMER][PID %5d] Consume product: %c\n", nPid, cProduct);
    szLine[2] = szLine[6];
    szLine[6] = szLine[10];
    szLine[10] = szLine[14];
    szLine[14] = '-';
    pFile = fopen(szBufferFilename, "w");
    if (!pFile) {
        char szError[200] = {0};
        sprintf(szError, "[CONSUMER][PID %5d] Unable to open file %s for write", nPid, szBufferFilename);
        perror(szError);
        exit(E_OPEN_FILE);
    }
    fprintf(pFile, "%s", szLine);
    fclose(pFile);
}

int main(int argc, char **argv) {
    // Get buffer filename by argument
    char *szBufferFilename = argv[1];
    // Open semaphore and mutex by arguments
    HANDLE hWriteSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, argv[WRITE_SEM_NAME_INDEX]);
    HANDLE hReadSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, argv[READ_SEM_NAME_INDEX]);
    HANDLE hAccessMut = OpenMutex(MUTEX_ALL_ACCESS, TRUE, argv[ACCESS_MUT_NAME_INDEX]);
    if (hWriteSem == INVALID_HANDLE_VALUE || hReadSem == INVALID_HANDLE_VALUE || hAccessMut == INVALID_HANDLE_VALUE) {
        GetLastError();
        ExitProcess(E_OPEN_SEM_MUT);
    }

    // Start to consume
    srand(GetCurrentProcessId());
    for (int nProduceCt = 0; nProduceCt < TOTAL_PRODUCTS_CONSUMED; nProduceCt++) {
        Sleep(rand() % 3000);
        WaitForSingleObject(hReadSem, INFINITE);
        WaitForSingleObject(hAccessMut, INFINITE);
        ReadBuffer(GetCurrentProcessId(), szBufferFilename);
        Consume(GetCurrentProcessId(), szBufferFilename);
        ReleaseSemaphore(hWriteSem, 1, NULL);
        ReleaseMutex(hAccessMut);
    }

    CloseHandle(hWriteSem);
    CloseHandle(hReadSem);
    CloseHandle(hAccessMut);

    ExitProcess(0);
}
