#include <stdio.h>
#include <Windows.h>

// Error code
#define E_ARGS -1
#define E_OPENFILE -3
#define E_OPENDIR -6
#define E_SUBDIR -7
#define E_NO_FILE -8
#define E_WRITE -9

/*
 * Check if the destination path is the source path's subdirectory or not
 */
int IsSubdirectory(LPCTSTR szSourcePath, LPCTSTR szDestinationPath) {
    TCHAR szSourceAbsolutePath[MAX_PATH] = {0}, szDestinationAbsolutePath[MAX_PATH] = {0};
    _fullpath(szSourceAbsolutePath, szSourcePath, MAX_PATH);
    _fullpath(szDestinationAbsolutePath, szDestinationPath, MAX_PATH);
    unsigned int nSourceAbsolutePathLength = strlen(szSourceAbsolutePath),
            nDestinationAbsolutePathLength = strlen(szDestinationAbsolutePath);
    if (nSourceAbsolutePathLength > nDestinationAbsolutePathLength)
        return 0;
    for (int nIndex = 0; nIndex < nSourceAbsolutePathLength; nIndex++)
        if (szSourceAbsolutePath[nIndex] != szDestinationAbsolutePath[nIndex])
            return 0;
    return 1;
}

/*
 * Copy file, including regular file and link file
 */
int MyCopyFile(LPCTSTR szSourcePath, LPCTSTR szDestinationPath) {
    // Get the source directory info
    WIN32_FIND_DATA fdDataInfo;
    HANDLE hFile = FindFirstFile(szSourcePath, &fdDataInfo);
    // Open source file
    HANDLE hSourceFile = CreateFile(szSourcePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    // Check source file status
    if (hSourceFile == INVALID_HANDLE_VALUE) {
        fprintf_s(stderr, "Unable to open file: %s (error code %d)\n", szSourcePath, GetLastError());
        return E_OPENFILE;
    }
    // Open destination file
    HANDLE hDestinationFile = CreateFile(szDestinationPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                                         FILE_ATTRIBUTE_NORMAL, NULL);
    // Check destination file
    if (hSourceFile == INVALID_HANDLE_VALUE) {
        fprintf_s(stderr, "Unable to open file: %s (error code %d)\n", szDestinationPath, GetLastError());
        return E_OPENFILE;
    }
    // Copy file
    TCHAR sBuffer[1024] = {0};
    DWORD dwReadLength = 0, dwWriteLength = 0;
    while (ReadFile(hSourceFile, sBuffer, 1024, &dwReadLength, NULL) &&
           dwReadLength > 0) {
        WriteFile(hDestinationFile, sBuffer, dwReadLength, &dwWriteLength, NULL);
        if (dwReadLength != dwWriteLength) {
            fprintf_s(stderr, "Error occurred when write to file %s (error code %d)\n",
                      szDestinationPath, GetLastError());
            return E_WRITE;
        }
    }
    // Change timestamp of file
    SetFileTime(hDestinationFile, &fdDataInfo.ftCreationTime,
                &fdDataInfo.ftLastAccessTime, &fdDataInfo.ftLastWriteTime);

    CloseHandle(hSourceFile);
    CloseHandle(hDestinationFile);
    return 0;
}

/*
 * Copy directory
 */
int MyCopyDir(LPCTSTR szSourcePath, LPCTSTR szDestinationPath) {
    // Get the source directory info
    WIN32_FIND_DATA fdDataInfo;
    HANDLE hFile = FindFirstFile(szSourcePath, &fdDataInfo);
    CloseHandle(hFile);
    if (fdDataInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        // If it is a directory, traverse it and copy all its items
        hFile = FindFirstFile(szDestinationPath, &fdDataInfo);
        // If destination directory does not exit, create it
        if (hFile == INVALID_HANDLE_VALUE) {
            BOOL bCreateStatus = CreateDirectory(szDestinationPath, NULL);
            // Check create status
            if (bCreateStatus == FALSE) {
                fprintf_s(stderr, "Unable to create directory: %s (error code %d)\n",
                          szDestinationPath, GetLastError());
                return E_OPENDIR;
            }
        }
        CloseHandle(hFile);
        // Traverse the source directory and copy all its items
        TCHAR szSourceDirPath[MAX_PATH], szDestinationDirPath[MAX_PATH];
        sprintf_s(szSourceDirPath, MAX_PATH, "%s\\*", szSourcePath);
        sprintf_s(szDestinationDirPath, MAX_PATH, "%s\\", szDestinationPath);
        // Get all its items
        hFile = FindFirstFile(szSourceDirPath, &fdDataInfo);
        if (hFile == INVALID_HANDLE_VALUE) {
            fprintf_s(stderr, "Unable to open directory: %s (error code %d)\n",
                      szSourcePath, GetLastError());
            return E_OPENDIR;
        }
        // Format source directory path string
        size_t nSourceDirPathLength = strlen(szSourceDirPath);
        szSourceDirPath[nSourceDirPathLength - 1] = 0;
        do {
            CloseHandle(hFile);
            // If it is a "." or ".." directory, skip it
            if (strcmp(fdDataInfo.cFileName, ".") == 0 || strcmp(fdDataInfo.cFileName, "..") == 0)
                continue;
            TCHAR szSourceDirItem[MAX_PATH], szDestinationDirItem[MAX_PATH];
            sprintf_s(szSourceDirItem, MAX_PATH, "%s%s", szSourceDirPath, fdDataInfo.cFileName);
            sprintf_s(szDestinationDirItem, MAX_PATH, "%s%s", szDestinationDirPath, fdDataInfo.cFileName);
            int nStatus = MyCopyDir(szSourceDirItem, szDestinationDirItem);
            if (nStatus)
                return nStatus;
        } while (FindNextFile(hFile, &fdDataInfo));
        // Change timestamp of directory
        hFile = FindFirstFile(szSourcePath, &fdDataInfo);
        hFile = CreateFile(szDestinationPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_DELETE,
                           NULL, OPEN_ALWAYS, FILE_FLAG_BACKUP_SEMANTICS, NULL);
        SetFileTime(hFile, &fdDataInfo.ftCreationTime,
                    &fdDataInfo.ftLastAccessTime, &fdDataInfo.ftLastWriteTime);
        CloseHandle(hFile);
        return 0;
    } else {
        // If it is a regular file or link file, just copy it
        return MyCopyFile(szSourcePath, szDestinationPath);
    }
}

int main(int argc, char **argv) {
    // Check arguments validity
    if (argc != 3) {
        fprintf(stderr, "Illegal arguments number! Please check your input!\n");
        return E_ARGS;
    }
    // Check paths' validity
    WIN32_FIND_DATA fdDataInfo;
    HANDLE hFile = FindFirstFile(argv[1], &fdDataInfo);
    if (hFile == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "No such file or directory: %s\n", argv[1]);
        return E_NO_FILE;
    }
    if (IsSubdirectory(argv[1], argv[2])) {
        fprintf(stderr, "%s is the subdirectory of %s!\n", argv[2], argv[1]);
        return E_SUBDIR;
    }
    // Copy the file or directory
    return MyCopyDir(argv[1], argv[2]);
}
