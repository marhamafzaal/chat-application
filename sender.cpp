/*
====================================================================
 Sender - Bi-Directional Chat Application using IPC (Pipes) in C++
====================================================================
 Description: This program sends messages to the receiver via a FIFO.

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

#define FIFO1 "fifo1"  // FIFO used for sending messages

using namespace std;

void clear_screen() {
    cout << "\033[H\033[J";  // ANSI escape code to clear the screen
}

void print_header() {
    clear_screen();
    cout << "====================================================\n";
    cout << "  Sender - IPC Chat Application  \n";
    cout << "====================================================\n";
}

int main() {
  
    int fd_write = open(FIFO1, O_WRONLY);
    if (fd_write < 0) {
        perror("Error opening FIFO1");
        return 1;
    }

    print_header();
    cout << "Type 'exit' to end the chat.\n\n";

    string send_msg;

    while (true) {
        cout << "You: ";
        getline(cin, send_msg);
        write(fd_write, send_msg.c_str(), send_msg.length() + 1);
        fsync(fd_write);  // Force flush to send immediately

        if (send_msg == "exit") break;
    }

    close(fd_write);
    cout << "\nChat ended. Goodbye!\n";
    return 0;
}

