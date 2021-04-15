#include <stdio.h>
#include <Windows.h>
#include <shlwapi.h>
#include <psapi.h>

#pragma comment(lib, "shlwapi.lib")

void ShowProtectionType(DWORD dwType) {
    printf("\tBlock protection type: ");
    if (dwType & PAGE_READONLY)
        printf("PAGE_READONLY\t");
    if (dwType & PAGE_GUARD)
        printf("PAGE_GUARD\t");
    if (dwType & PAGE_NOCACHE)
        printf("PAGE_NOCACHE\t");
    if (dwType & PAGE_READWRITE)
        printf("PAGE_READWRITE\t");
    if (dwType & PAGE_WRITECOPY)
        printf("PAGE_WRITECOPY\t");
    if (dwType & PAGE_EXECUTE)
        printf("PAGE_EXECUTE\t");
    if (dwType & PAGE_EXECUTE_READ)
        printf("PAGE_EXECUTE_READ\t");
    if (dwType & PAGE_EXECUTE_READWRITE)
        printf("PAGE_EXECUTE_READWRITE\t");
    if (dwType & PAGE_EXECUTE_WRITECOPY)
        printf("PAGE_EXECUTE_WRITECOPY\t");
    if (dwType & PAGE_NOACCESS)
        printf("PAGE_NOACCESS\t");
    printf("\n");
}

void ShowProcVirtualMemory(HANDLE hProc) {
    // Initialize system information
    SYSTEM_INFO sSystemInfo;
    ZeroMemory(&sSystemInfo, sizeof sSystemInfo);
    GetSystemInfo(&sSystemInfo);
    // Initialize memory basic information for process
    MEMORY_BASIC_INFORMATION sMemBasicInfo;
    ZeroMemory(&sMemBasicInfo, sizeof sMemBasicInfo);

    // Show virtual memory information for process
    LPCVOID pBlockStart = (LPVOID) sSystemInfo.lpMinimumApplicationAddress;

    int nBlockIndex = 0;
    while (pBlockStart < sSystemInfo.lpMaximumApplicationAddress) {
        // Get one virtual memory block
        if (VirtualQueryEx(hProc, pBlockStart, &sMemBasicInfo, sizeof sMemBasicInfo) != sizeof sMemBasicInfo) {
            GetLastError();
            return;
        }

        // Show size address and size information
        LPCVOID pBlockEnd = (PBYTE) pBlockStart + sMemBasicInfo.RegionSize;
        TCHAR szRegionSize[MAX_PATH];
        StrFormatByteSize(sMemBasicInfo.RegionSize, szRegionSize, MAX_PATH);
        printf("No.%d block ranges from 0x%08lx to 0x%08lx\n", nBlockIndex, (DWORD) pBlockStart, (DWORD) pBlockEnd);

        // Show state information
        switch (sMemBasicInfo.State) {
            case MEM_COMMIT:
                printf("\tBlock state: Committed\n");
                break;
            case MEM_FREE:
                printf("\tBlock state: Free\n");
                break;
            case MEM_RESERVE:
                printf("\tBlock state: Reserved\n");
                break;
            default:
                printf("\tBlock state: Unknown\n");
        }

        // Show protection type information
        if (sMemBasicInfo.Protect == 0 && sMemBasicInfo.State != MEM_FREE)
            sMemBasicInfo.Protect = PAGE_READONLY;
        ShowProtectionType(sMemBasicInfo.Protect);

        switch (sMemBasicInfo.Type) {
            case MEM_IMAGE:
                printf("\tBlock type: MEM_IMAGE\n");
                break;
            case MEM_MAPPED:
                printf("\tBlock type: MEM_MAPPED\n");
                break;
            case MEM_PRIVATE:
                printf("\tBlock type: MEM_PRIVATE\n");
                break;
            default:
                printf("\tBlock type: Unknown\n");
        }

        // Move to next block;
        pBlockStart = pBlockEnd;
        nBlockIndex++;
    }
}

int main() {
    // Show system memory info
    printf("-------- System memory info --------\n\n");
    MEMORYSTATUSEX MemStatusEx;
    ZeroMemory(&MemStatusEx, sizeof MemStatusEx);
    MemStatusEx.dwLength = sizeof MemStatusEx;
    GlobalMemoryStatusEx(&MemStatusEx);
    // Show physical memory info
    printf("Physical memory:\n");
    TCHAR szTotalPhysMem[MAX_PATH];
    StrFormatByteSize(MemStatusEx.ullTotalPhys, szTotalPhysMem, MAX_PATH);
    printf("\tTotal: %s\n", szTotalPhysMem);
    TCHAR szAvailPhysMem[MAX_PATH];
    StrFormatByteSize(MemStatusEx.ullAvailPhys, szAvailPhysMem, MAX_PATH);
    printf("\tAvailable: %s\n", szAvailPhysMem);
    printf("\tLoad: %lu%%\n", MemStatusEx.dwMemoryLoad);
    // Show page file info
    printf("Page file:\n");
    TCHAR szTotalPageFile[MAX_PATH];
    StrFormatByteSize(MemStatusEx.ullTotalPageFile, szTotalPageFile, MAX_PATH);
    printf("\tTotal: %s\n", szTotalPageFile);
    TCHAR szAvailPageFile[MAX_PATH];
    StrFormatByteSize(MemStatusEx.ullAvailPageFile, szAvailPageFile, MAX_PATH);
    printf("\tAvailable: %s\n", szAvailPageFile);
    // Show virtual memory info
    printf("Virtual memory:\n");
    TCHAR szTotalVirtualMem[MAX_PATH];
    StrFormatByteSize(MemStatusEx.ullTotalVirtual, szTotalVirtualMem, MAX_PATH);
    printf("\tTotal: %s\n", szTotalVirtualMem);
    TCHAR szAvailVirtualMem[MAX_PATH];
    StrFormatByteSize(MemStatusEx.ullAvailVirtual, szAvailVirtualMem, MAX_PATH);
    printf("\tAvailable: %s\n", szAvailVirtualMem);

    // Show performance info
    printf("\n------ System performance info -----\n\n");
    PERFORMACE_INFORMATION PerformanceInfo;
    ZeroMemory(&PerformanceInfo, sizeof PerformanceInfo);
    PerformanceInfo.cb = sizeof PerformanceInfo;
    GetPerformanceInfo(&PerformanceInfo, sizeof PerformanceInfo);
    // Show page size
    TCHAR szPageSize[MAX_PATH];
    StrFormatByteSize(PerformanceInfo.PageSize, szPageSize, MAX_PATH);
    printf("Page size: %s\n", szPageSize);
    // Show commit pages info
    printf("Commit pages number:\n");
    printf("\tCurrent: %lu\n", PerformanceInfo.CommitTotal);
    printf("\tPeak: %lu\n", PerformanceInfo.CommitPeak);
    printf("\tLimit: %lu\n", PerformanceInfo.CommitLimit);
    // Show physical memory pages info
    printf("Physical memory pages number:\n");
    printf("\tTotal: %lu\n", PerformanceInfo.PhysicalTotal);
    printf("\tAvailable: %lu\n", PerformanceInfo.PhysicalAvailable);
    printf("System cache pages number: %lu\n", PerformanceInfo.SystemCache);
    // Show memory pages in kernel pool
    printf("Kernel pool pages number:\n");
    printf("\tTotal: %lu\n", PerformanceInfo.KernelTotal);
    printf("\tPaged: %lu\n", PerformanceInfo.KernelPaged);
    printf("\tNonpaged: %lu\n", PerformanceInfo.KernelNonpaged);

    // Show process basic memory info
    printf("\n----- Process basic memory info ----\n\n");
    printf("For each process:\n");
    SYSTEM_INFO SystemInfo;
    ZeroMemory(&SystemInfo, sizeof SystemInfo);
    GetSystemInfo(&SystemInfo);
    StrFormatByteSize(SystemInfo.dwPageSize, szPageSize, MAX_PATH);
    printf("\tVirtual memory page size: %s\n", szPageSize);
    printf("\tMin application address: 0x%08lx\n", (DWORD) SystemInfo.lpMinimumApplicationAddress);
    printf("\tMax application address: 0x%08lx\n", (DWORD) SystemInfo.lpMaximumApplicationAddress);
    DWORD dwMemSize = (DWORD) SystemInfo.lpMaximumApplicationAddress - (DWORD) SystemInfo.lpMinimumApplicationAddress;
    TCHAR szMemSize[MAX_PATH];
    StrFormatByteSize(dwMemSize, szMemSize, MAX_PATH);
    printf("\tTotal virtual memory: %s\n", szMemSize);

    // Show ParentProcess virtual memory info
    // Create ParentProcess
    STARTUPINFO StartupInfo;
    ZeroMemory(&StartupInfo, sizeof StartupInfo);
    StartupInfo.cb = sizeof StartupInfo;
    PROCESS_INFORMATION ProcInfo;
    BOOL bCreateStatus = CreateProcess("ParentProcess.exe", "ParentProcess.exe ChildProcess.exe",
                                       NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL,
                                       &StartupInfo, &ProcInfo);
    if (!bCreateStatus)
        ExitProcess(-1);
    printf("\n--- ParentProcess.exe memory info --\n\n");
    ShowProcVirtualMemory(ProcInfo.hProcess);
    printf("\n------------------------------------\n");

    ExitProcess(0);
}
