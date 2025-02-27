/*
====================================================================
 Receiver - Bi-Directional Chat Application using IPC (Pipes) in C++
====================================================================
 Description: This program listens for messages from the sender via a FIFO.

 Author: Your Name
 Platform: Ubuntu (Linux)
====================================================================
*/

#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>  // For mkfifo()
#include <cstdlib>     // For exit()
#include <cstring>     // For memset()

#define FIFO1 "fifo1"  // FIFO used for receiving messages

using namespace std;

void clear_screen() {
    cout << "\033[H\033[J";  // ANSI escape code to clear the screen
}

void print_header() {
    clear_screen();
    cout << "====================================================\n";
    cout << "  Receiver - IPC Chat Application  \n";
    cout << "====================================================\n";
}

int main() {
  

    int fd_read = open(FIFO1, O_RDONLY);
    if (fd_read < 0) {
        perror("Error opening FIFO1");
        return 1;
    }

    print_header();
    cout << "Waiting for messages...\n\n";

    string recv_msg;
    char buffer[256];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        read(fd_read, buffer, sizeof(buffer) - 1);
        buffer[strlen(buffer)] = '\0';  // Ensure proper string termination
        recv_msg = string(buffer);

        if (recv_msg == "exit") break;

        cout << "Sender: " << recv_msg << endl;
    }

    close(fd_read);
    cout << "\nChat ended. Goodbye!\n";
    return 0;
}

