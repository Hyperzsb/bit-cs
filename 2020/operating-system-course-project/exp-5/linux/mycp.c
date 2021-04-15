#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <utime.h>

// Error code
#define E_ARGS -1
#define E_FILETYPE -2
#define E_OPENFILE -3
#define E_READ_LNK -4
#define E_CREATE_LNK -5
#define E_OPENDIR -6
#define E_SUBDIR -7
#define E_NO_FILE -8

/*
 * Check if the destination path is the source path's subdirectory or not
 */
int is_subdirectory(char *source_path, char *destination_path) {
    char source_absolute_path[PATH_MAX] = {0}, destination_absolute_path[PATH_MAX] = {0};
    realpath(source_path, source_absolute_path);
    realpath(destination_path, destination_absolute_path);
    unsigned int source_absolute_path_length = strlen(source_absolute_path),
            destination_absolute_path_length = strlen(destination_absolute_path);
    if (source_absolute_path_length > destination_absolute_path_length)
        return 0;
    for (int i = 0; i < source_absolute_path_length; i++)
        if (source_path[i] != destination_path[i])
            return 0;
    return 1;
}

/*
 * Copy file, including regular file and link file
 */
int copy_file(char *source_path, char *destination_path) {
    // Get source file state
    struct stat file_state;
    lstat(source_path, &file_state);
    // Open source file and create destination file
    int source_fd = open(source_path, O_RDWR | O_CREAT),
            destination_fd = open(destination_path, O_TRUNC | O_WRONLY | O_CREAT, file_state.st_mode);
    // Check open status
    if (source_fd == -1 || destination_fd == -1) {
        perror("Unable to open file");
        return E_OPENFILE;
    }
    // Copy file
    int str_len = 0;
    char buffer[1024] = {0};
    str_len = read(source_fd, buffer, 1000);
    while (str_len) {
        write(destination_fd, buffer, 1000);
        str_len = read(source_fd, buffer, 1000);
    }
    // Change timestamp of file
    struct utimbuf time_buffer;
    time_buffer.actime = file_state.st_atime;
    time_buffer.modtime = file_state.st_mtime;
    utime(destination_path, &time_buffer);

    return 0;
}

int copy_link(char *source_path, char *destination_path) {
    // Get source file state
    struct stat file_state;
    lstat(source_path, &file_state);
    // Copy link file
    char buffer[1024] = {0};
    int status = readlink(source_path, buffer, sizeof(buffer));
    if (status == -1) {
        perror("Unable to read link file");
        return E_READ_LNK;
    }
    status = symlink(buffer, destination_path);
    if (status == -1) {
        perror("Unable to make link file");
        return E_CREATE_LNK;
    }
    // Change timestamp of link file
    struct timeval time_value[2];
    time_value[0].tv_sec = file_state.st_atime;
    time_value[1].tv_sec = file_state.st_mtime;
    time_value[0].tv_usec = 0;
    time_value[1].tv_usec = 0;
    lutimes(destination_path, time_value);

    return 0;
}

/*
 * Copy directory
 */
int copy_dir(char *source_path, char *destination_path) {
    // Get directory state
    struct stat dir_state;
    lstat(source_path, &dir_state);
    if (S_ISREG(dir_state.st_mode)) {
        // If it is a regular file, just copy it
        return copy_file(source_path, destination_path);
    } else if (S_ISLNK(dir_state.st_mode)) {
        // If it is a link file, just copy it
        return copy_link(source_path, destination_path);
    } else if (S_ISDIR(dir_state.st_mode)) {
        // If it is a directory, traverse it and copy all its items
        // If it is a "." or ".." directory, skip it
        if (strcmp(basename(source_path), ".") == 0 || strcmp(basename(source_path), "..") == 0)
            return 0;
        // Open the directory
        DIR *source_dir;
        struct dirent *dir_info;
        // Check open state
        if ((source_dir = opendir(source_path)) == NULL) {
            perror("Unable to open directory!");
            return E_OPENDIR;
        }
        // Create destination directory
        mkdir(destination_path, dir_state.st_mode);
        // Copy all its items
        char next_source_path[PATH_MAX], next_destination_path[PATH_MAX];
        while ((dir_info = readdir(source_dir)) != NULL) {
            memset(next_source_path, 0, PATH_MAX);
            memset(next_destination_path, 0, PATH_MAX);
            sprintf(next_source_path, "%s/%s", source_path, dir_info->d_name);
            sprintf(next_destination_path, "%s/%s", destination_path, dir_info->d_name);
            int status = copy_dir(next_source_path, next_destination_path);
            if (status)
                return status;
        }
        // Change timestamp of directory
        struct utimbuf time_buffer;
        time_buffer.actime = dir_state.st_atime;
        time_buffer.modtime = dir_state.st_mtime;
        utime(destination_path, &time_buffer);
        // Close the directory
        closedir(source_dir);
        return 0;
    } else {
        // If it is a file of other type, throw error
        fprintf(stderr, "File type not supported!\n");
        return E_FILETYPE;
    }
}


int main(int argc, char **argv) {
    // Check arguments' validity
    if (argc != 3) {
        fprintf(stderr, "Illegal arguments number! Please check your input!\n");
        return E_ARGS;
    }
    // Check paths' validity
    if (access(argv[1], F_OK)) {
        fprintf(stderr, "No such file or directory: %s\n", argv[1]);
        return E_NO_FILE;
    }
    if (is_subdirectory(argv[1], argv[2])) {
        fprintf(stderr, "%s is the subdirectory of %s!\n", argv[2], argv[1]);
        return E_SUBDIR;
    }
    // Copy the file or directory
    return copy_dir(argv[1], argv[2]);
}