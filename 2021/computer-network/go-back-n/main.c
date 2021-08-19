#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "frame.h"
#include "crc.h"
#include "logger.h"

#pragma comment(lib, "ws2_32.lib")
// Global marcos
#define MAX_FILE_PATH_LENGTH 128
// Go Back N marcos
#define MAX_SEQ 7
#define MAX_TIMEOUT 1000
// Control marcos
#define ERROR_RATE 10
#define LOST_RATE 10

struct CommunicateArg {
    SOCKET sock;
    struct sockaddr *addr;
    FILE *send_file;
    FILE *receive_file;
    FILE *log_file;
};

DWORD WINAPI Communicate(LPVOID arg_struct);

int main(int argc, char **argv) {

    ////////////////////////////////////
    // Check and initialize arguments //
    ////////////////////////////////////

    if (argc != 7 && argc != 9) {
        printf("Usage:\ngo-back-n.exe port another_port send_file_path receive_file_path another_send_file_path another_receive_file_path [log_file_path another_log_file_path]\n");
        exit(0);
    }
    // Initialize arguments
    int port = 0, another_port = 0;
    char send_file_path[MAX_FILE_PATH_LENGTH] = {0}, receive_file_path[MAX_FILE_PATH_LENGTH] = {0},
            another_send_file_path[MAX_FILE_PATH_LENGTH] = {0}, another_receive_file_path[MAX_FILE_PATH_LENGTH] = {0},
            log_file_path[MAX_FILE_PATH_LENGTH] = {0}, another_log_file_path[MAX_FILE_PATH_LENGTH] = {0};
    sscanf_s(argv[1], "%d", &port);
    sscanf_s(argv[2], "%d", &another_port);
    sscanf_s(argv[3], "%s", send_file_path, (unsigned) _countof(send_file_path));
    sscanf_s(argv[4], "%s", receive_file_path, (unsigned) _countof(receive_file_path));
    sscanf_s(argv[5], "%s", another_send_file_path, (unsigned) _countof(another_send_file_path));
    sscanf_s(argv[6], "%s", another_receive_file_path, (unsigned) _countof(another_receive_file_path));
    if (argc == 9) {
        sscanf_s(argv[7], "%s", log_file_path, (unsigned) _countof(log_file_path));
        sscanf_s(argv[8], "%s", another_log_file_path, (unsigned) _countof(another_log_file_path));
    }

    ////////////////
    // Open files //
    ////////////////

    FILE *send_file, *receive_file, *another_send_file, *another_receive_file, *log_file, *another_log_file;
    errno_t error_code;
    error_code = fopen_s(&send_file, send_file_path, "r");
    if (error_code) {
        perror("Unable to open send file");
        exit(error_code);
    }
    error_code = fopen_s(&receive_file, receive_file_path, "w");
    if (error_code) {
        perror("Unable to open receive file");
        exit(error_code);
    }
    error_code = fopen_s(&another_send_file, another_send_file_path, "r");
    if (error_code) {
        perror("Unable to open another send file");
        exit(error_code);
    }
    error_code = fopen_s(&another_receive_file, another_receive_file_path, "w");
    if (error_code) {
        perror("Unable to open another receive file");
        exit(error_code);
    }
    if (argc == 9) {
        error_code = fopen_s(&log_file, log_file_path, "w");
        if (error_code) {
            perror("Unable to open log file");
            exit(error_code);
        }
        error_code = fopen_s(&another_log_file, another_log_file_path, "w");
        if (error_code) {
            perror("Unable to open another log file");
            exit(error_code);
        }
    } else {
        log_file = stdout;
        another_log_file = stdout;
    }

    ///////////////////////
    // Initialize socket //
    ///////////////////////

    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata)) {
        Log(log_file, ERROR_LOG, "Init", "Unable to find usable WinSock DLL");
        WSACleanup();
        exit(WSAGetLastError());
    } else {
        Log(log_file, INFO_LOG, "Init", "Find usable WinSock DLL successfully");
    }
    // Create sockets
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    SOCKET another_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET || another_sock == INVALID_SOCKET) {
        Log(log_file, ERROR_LOG, "Init", "Unable to create socket");
        WSACleanup();
        exit(WSAGetLastError());
    } else {
        Log(log_file, INFO_LOG, "Init", "Initialize create successfully");
    }
    // Define socket addresses
    struct sockaddr_in address, another_address;
    address.sin_family = AF_INET;
    address.sin_port = port;
    address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    another_address.sin_family = AF_INET;
    another_address.sin_port = another_port;
    another_address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    // Bind socket to source
    if (bind(sock, (struct sockaddr *) &address, sizeof(address)) == SOCKET_ERROR ||
        bind(another_sock, (struct sockaddr *) &another_address, sizeof(another_address)) == SOCKET_ERROR) {
        Log(log_file, ERROR_LOG, "Init", "Unable to bind socket to address");
        WSACleanup();
        exit(WSAGetLastError());
    } else {
        Log(log_file, INFO_LOG, "Init", "Bind socket to address successfully");
    }
    // Set non-blocking config for sockets
    int imode = 1;
    if (ioctlsocket(sock, FIONBIO, (u_long *) &imode) == SOCKET_ERROR ||
        ioctlsocket(another_sock, FIONBIO, (u_long *) &imode) == SOCKET_ERROR) {
        Log(log_file, ERROR_LOG, "Init", "Unable to call ioctlsocket");
        if (closesocket(sock) == SOCKET_ERROR || closesocket(another_sock) == SOCKET_ERROR) {
            Log(log_file, ERROR_LOG, "Exit", "Unable to close socket");
            exit(WSAGetLastError());
        } else {
            Log(log_file, INFO_LOG, "Exit", "Close socket successfully");
        }
        WSACleanup();
        exit(WSAGetLastError());
    } else {
        Log(log_file, INFO_LOG, "Init", "Call ioctlsocket successfully");
    }


    ///////////////////////////////////
    // Create threads to communicate //
    ///////////////////////////////////

    // Define arguments for threads
    struct CommunicateArg arg, another_arg;
    arg.sock = sock;
    arg.addr = (struct sockaddr *) &another_address;
    arg.send_file = send_file;
    arg.receive_file = receive_file;
    arg.log_file = log_file;
    another_arg.sock = another_sock;
    another_arg.addr = (struct sockaddr *) &address;
    another_arg.send_file = another_send_file;
    another_arg.receive_file = another_receive_file;
    another_arg.log_file = another_log_file;
    // Create threads
    HANDLE thread = CreateThread(NULL, 0, Communicate, (LPVOID) &arg, 0, NULL);
    HANDLE another_thread = CreateThread(NULL, 0, Communicate, (LPVOID) &another_arg, 0, NULL);
    if (thread == NULL || another_thread == NULL) {
        Log(log_file, ERROR_LOG, "Exit", "Unable to create threads");
    } else {
        // Wait for threads
        WaitForSingleObject(thread, INFINITE);
        WaitForSingleObject(another_thread, INFINITE);
        // Close threads
        CloseHandle(thread);
        CloseHandle(another_thread);
    }

    //////////////////
    // Exit process //
    //////////////////

    // Close socket
    if (closesocket(sock) == SOCKET_ERROR || closesocket(another_sock) == SOCKET_ERROR) {
        Log(log_file, ERROR_LOG, "Exit", "Unable to close socket");
        WSACleanup();
        exit(WSAGetLastError());
    } else {
        Log(log_file, INFO_LOG, "Exit", "Close socket successfully");
    }
    // Close files
    fclose(send_file);
    fclose(receive_file);
    fclose(another_send_file);
    fclose(another_receive_file);
    fclose(log_file);

    exit(0);
}

int increase(int n) {
    return (n + 1) % (MAX_SEQ + 1);
}

int decrease(int n) {
    return (n + MAX_SEQ) % (MAX_SEQ + 1);
}

int between(int a, int b, int c) {
    if ((a <= b) && (b < c) || (c < a) && (a <= b) || (b < c) && (c < a))
        return 1;
    else
        return 0;
}

DWORD WINAPI Communicate(LPVOID arg_struct) {
    // Cast argument
    struct CommunicateArg *arg = (struct CommunicateArg *) arg_struct;
    // Log entity
    char entity[10] = {0};
    sprintf_s(entity, (unsigned) _countof(entity), "%d", arg->sock);
    // Control variables
    int error_count = 0, lost_count = 5;
    // Go Back N variables
    struct Frame frame_received, frame_sending, frame_buffer[MAX_SEQ + 1];
    int addr_length = sizeof(struct sockaddr);
    int current_buffer_size = 0;
    int receive_finished = 0;
    int send_finished = 0, send_completed = 0;
    int frame_to_send = 0, frame_expected = 0;
    int ack_expected = 0;
    int is_timer_running = 0;
    time_t timer = 0, time_start = clock();
    // Start Go Back N
    while (1) {
        // Set timer
        if (is_timer_running) {
            timer += (clock() - time_start);
        }
        time_start = clock();

        ///////////////////////////////////
        // Receive a frame from opposite //
        ///////////////////////////////////

        if (recvfrom(arg->sock, (char *) &frame_received, sizeof(struct Frame), 0,
                     (struct sockaddr *) arg->addr, &addr_length) > 0) {
            Log(arg->log_file, INFO_LOG, entity,
                "Received frame: seq=%d ack=%d; frame_expected=%d frame_to_send=%d ack_expected=%d",
                frame_received.seq, frame_received.ack, frame_expected, frame_to_send, ack_expected);
            // Check CRC checksum
            if (CheckCRC(&frame_received)) {
                // If invalid, drop it
                Log(arg->log_file, WARNING_LOG, entity, "Checksum is invalid, discarded");
                continue;
            } else {
                Log(arg->log_file, INFO_LOG, entity, "Checksum is valid");
            }
            // As a receiver, if this frame is what I want
            if (frame_received.seq == frame_expected) {
                Log(arg->log_file, INFO_LOG, entity, "Received frame is expected: seq=%d ack=%d",
                    frame_received.seq, frame_received.ack);
                receive_finished = SaveFrameData(arg->receive_file, &frame_received);
                if (receive_finished) {
                    Log(arg->log_file, INFO_LOG, entity, "Receiving completed");
                } else {
                    frame_expected = increase(frame_expected);
                }
                // Vital
                // If sending is finished, ack should still be sent to opposite
                if (send_completed) {
                    frame_sending.seq = frame_to_send;
                    frame_sending.ack = decrease(frame_expected);
                    frame_sending.length = -1;
                    frame_sending.checksum = GetCRC(&frame_sending, 0);
                    sendto(arg->sock, (char *) &frame_sending, sizeof(struct Frame), 0,
                           (struct sockaddr *) arg->addr, addr_length);
                }
            } else {
                Log(arg->log_file, WARNING_LOG, entity, "Received frame is unexpected, discarded: seq=%d ack=%d",
                    frame_received.seq, frame_received.ack);
            }
            // As a sender, if opposite sent a valid ack
            while (between(ack_expected, frame_received.ack, frame_to_send)) {
                Log(arg->log_file, INFO_LOG, entity, "Shifting ack_expected=%d to target=%d...",
                    ack_expected, frame_received.ack);
                current_buffer_size--;
                timer = 0;
                ack_expected = increase(ack_expected);
                if (send_finished && current_buffer_size == 0) {
                    Log(arg->log_file, INFO_LOG, entity, "Sending completed");
                    frame_sending.length = -1;
                    frame_sending.seq = frame_to_send;
                    frame_sending.ack = decrease(frame_expected);
                    frame_sending.checksum = GetCRC(&frame_sending, 0);
                    sendto(arg->sock, (char *) &frame_sending, sizeof(struct Frame), 0,
                           (struct sockaddr *) arg->addr, addr_length);
                    send_completed = 1;
                }
            }
        }

        /////////////////////////////////
        // If sending is not completed //
        /////////////////////////////////

        if (current_buffer_size < MAX_SEQ && !send_finished) {
            send_finished = GetFrameData(arg->send_file, &frame_sending);
            frame_sending.seq = frame_to_send;
            frame_sending.ack = decrease(frame_expected);
            CopyFrame(&frame_sending, &frame_buffer[current_buffer_size++]);
            frame_sending.checksum = GetCRC(&frame_sending, 0);
            if (error_count++ % ERROR_RATE == 0) {
                Log(arg->log_file, INFO_LOG, entity, "Distort sent frame: seq=%d ack=%d",
                    frame_to_send, decrease(frame_expected));
                srand((unsigned) time(NULL));
                for (int i = 0; i < 1024; i++) {
                    frame_sending.data[i] = rand() % 128;
                }
            } else if (lost_count++ % LOST_RATE) {
                Log(arg->log_file, INFO_LOG, entity, "Drop sent frame: seq=%d ack=%d",
                    frame_to_send, decrease(frame_expected));
            } else {
                Log(arg->log_file, INFO_LOG, entity, "Sent frame: seq=%d ack=%d",
                    frame_to_send, decrease(frame_expected));
                sendto(arg->sock, (char *) &frame_sending, sizeof(struct Frame), 0,
                       (struct sockaddr *) arg->addr, addr_length);
            }
            is_timer_running = 1;
            frame_to_send = increase(frame_to_send);
        }

        ////////////////
        // If timeout //
        ////////////////

        if (timer > MAX_TIMEOUT) {
            Log(arg->log_file, WARNING_LOG, entity, "Time out");
            frame_to_send = ack_expected;
            for (int i = 0; i < current_buffer_size; i++) {
                Log(arg->log_file, INFO_LOG, entity, "Resent frame: seq=%d ack=%d",
                    frame_to_send, decrease(frame_expected));
                CopyFrame(&frame_buffer[frame_to_send], &frame_sending);
                frame_sending.ack = decrease(frame_expected);
                frame_sending.seq = frame_to_send;
                frame_sending.checksum = GetCRC(&frame_sending, 0);
                sendto(arg->sock, (char *) &frame_sending, sizeof(struct Frame), 0,
                       (struct sockaddr *) arg->addr, addr_length);
                frame_to_send = increase(frame_to_send);
            }
            timer = 0;
        }

        ///////////////////////////////////////////
        // If sending and receiving are all done //
        ///////////////////////////////////////////

        if (send_completed && receive_finished) {
            break;
        }
    }
    return 0;
}