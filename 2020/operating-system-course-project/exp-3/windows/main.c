#include <stdio.h>
#include <Windows.h>

// Exit error code
#define E_CREATE_SEM_MUT -1
#define E_CREATE_PROC -2
#define E_OPEN_FILE -3
// Semaphore and mutex name
#define WRITE_SEM_NAME "WRITE_SEM_0x0001"
#define READ_SEM_NAME "READ_SEM_0x0001"
#define ACCESS_MUT_NAME "ACCESS_MUTEX_0x0001"
// Buffer attributes
#define BUFFER_FILENAME "../buffer.txt"
#define BUFFER_MAX 4
// Producer and consumer number
#define TOTAL_PRODUCERS 3
#define TOTAL_CONSUMERS 4

void InitBuffer(char *szBufferFilename) {
    FILE *pFile = fopen(szBufferFilename, "w");
    if (!pFile) {
        perror("Unable to initialize buffer.");
        exit(E_OPEN_FILE);
    }
    fprintf(pFile, "| - | - | - | - |\n");
    fclose(pFile);
}

int main() {
    // Initialize buffer file
    InitBuffer(BUFFER_FILENAME);
    // Initialize semaphore and mutex
    HANDLE hWriteSem = CreateSemaphore(NULL, BUFFER_MAX, BUFFER_MAX, WRITE_SEM_NAME);
    HANDLE hReadSem = CreateSemaphore(NULL, 0, BUFFER_MAX, READ_SEM_NAME);
    HANDLE hAccessMut = CreateMutex(NULL, FALSE, ACCESS_MUT_NAME);
    if (hWriteSem == INVALID_HANDLE_VALUE || hReadSem == INVALID_HANDLE_VALUE || hAccessMut == INVALID_HANDLE_VALUE) {
        GetLastError();
        ExitProcess(E_CREATE_SEM_MUT);
    }

    // Create child processes
    STARTUPINFO aProducerStartUpInfo[TOTAL_PRODUCERS], aConsumerStartUpInfo[TOTAL_CONSUMERS];
    PROCESS_INFORMATION aProducerProcInfo[TOTAL_PRODUCERS], aConsumerProcInfo[TOTAL_CONSUMERS];
    // Create producers
    for (int nProducerIndex = 0; nProducerIndex < TOTAL_PRODUCERS; nProducerIndex++) {
        // Initialize variable memory
        ZeroMemory(&aProducerStartUpInfo[nProducerIndex], sizeof aProducerStartUpInfo[nProducerIndex]);
        aProducerStartUpInfo[nProducerIndex].cb = sizeof aProducerStartUpInfo[nProducerIndex];
        ZeroMemory(&aProducerProcInfo[nProducerIndex], sizeof aProducerProcInfo[nProducerIndex]);
        // Define process arguments
        char szApplicationName[MAX_PATH] = "producer.exe";
        char szCommandLine[MAX_PATH];
        sprintf(szCommandLine, "%s %s %s %s %s", szApplicationName, BUFFER_FILENAME,
                WRITE_SEM_NAME, READ_SEM_NAME, ACCESS_MUT_NAME);
        // Create producers process
        BOOL bCreateProcStatus = CreateProcess(NULL, szCommandLine,
                                               NULL, NULL, FALSE, 0, NULL, NULL,
                                               &aProducerStartUpInfo[nProducerIndex],
                                               &aProducerProcInfo[nProducerIndex]);
        // Check create status
        if (!bCreateProcStatus) {
            GetLastError();
            ExitProcess(E_CREATE_PROC);
        }
    }
    // Create consumers
    for (int nConsumerIndex = 0; nConsumerIndex < TOTAL_CONSUMERS; nConsumerIndex++) {
        // Initialize variable memory
        ZeroMemory(&aConsumerStartUpInfo[nConsumerIndex], sizeof aConsumerStartUpInfo[nConsumerIndex]);
        aConsumerStartUpInfo[nConsumerIndex].cb = sizeof aConsumerStartUpInfo[nConsumerIndex];
        ZeroMemory(&aConsumerProcInfo[nConsumerIndex], sizeof aConsumerProcInfo[nConsumerIndex]);
        // Define process arguments
        char szApplicationName[MAX_PATH] = "consumer.exe";
        char szCommandLine[MAX_PATH];
        sprintf(szCommandLine, "%s %s %s %s %s", szApplicationName, BUFFER_FILENAME,
                WRITE_SEM_NAME, READ_SEM_NAME, ACCESS_MUT_NAME);
        // Create producers process
        BOOL bCreateProcStatus = CreateProcess(NULL, szCommandLine,
                                               NULL, NULL, FALSE, 0, NULL, NULL,
                                               &aConsumerStartUpInfo[nConsumerIndex],
                                               &aConsumerProcInfo[nConsumerIndex]);
        // Check create status
        if (!bCreateProcStatus) {
            GetLastError();
            ExitProcess(E_CREATE_PROC);
        }
    }

    for (int nProducerIndex = 0; nProducerIndex < TOTAL_PRODUCERS; nProducerIndex++) {
        WaitForSingleObject(aProducerProcInfo[nProducerIndex].hThread, INFINITE);
        WaitForSingleObject(aProducerProcInfo[nProducerIndex].hProcess, INFINITE);
        CloseHandle(aProducerProcInfo[nProducerIndex].hThread);
        CloseHandle(aProducerProcInfo[nProducerIndex].hProcess);
    }

    for (int nConsumerIndex = 0; nConsumerIndex < TOTAL_CONSUMERS; nConsumerIndex++) {
        WaitForSingleObject(aConsumerProcInfo[nConsumerIndex].hThread, INFINITE);
        WaitForSingleObject(aConsumerProcInfo[nConsumerIndex].hProcess, INFINITE);
        CloseHandle(aConsumerProcInfo[nConsumerIndex].hThread);
        CloseHandle(aConsumerProcInfo[nConsumerIndex].hProcess);
    }

    CloseHandle(hWriteSem);
    CloseHandle(hReadSem);
    CloseHandle(hAccessMut);

    ExitProcess(0);
}
