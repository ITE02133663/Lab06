#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>


void err_quit(const char *fmt, ...);

char *concat(const char *s1, const char *s2);

/*
 * 網路程式
 * 1. ip 位置
 * 2. bind (port 0~65535)
 */

int main(int argc, char *argv[]) {
    int socket_desc;
    struct sockaddr_in server;
    char *message, server_reply[2000];

    if (argc < 3) {
        err_quit("usage: a.out <IPaddress> or <Port> \n");
    }

//Create socket
    /**
    * @param Address Family - AF_INET (this is IP version 4)
    * @param Type - SOCK_STREAM (this means connection oriented TCP protocol)
    * @param Protocol - 0 [ or IPPROTO_IP This is IP protocol]
    * Function socket() creates a socket and returns a descriptor
    * which can be used in other functions.
    * The above code will create a socket with following properties
    */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    // check return value.
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    // ipv4 32bits
    // ipv6 128bits
    server.sin_addr.s_addr = inet_addr(argv[1]); // 轉換為 32bits 位置
    server.sin_family = AF_INET;

    int port = atoi(argv[2]);
    server.sin_port = htons(port); // 每台電腦 cpu 不同，位元不同，host to network 轉為統一格式

//Connect to remote server
    // sizeof => bytes
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {

        // check return value.
        puts("connect error");
        return 1;
    }
    puts("Connected");
//Send some data
    message = "GET / HTTP/1.1\r\nHost: ";

    message = concat(message, argv[1]);
    message = concat(message, "\r\n\r\n");

    if (send(socket_desc, message, strlen(message), 0) < 0) {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
//Receive a reply from the server
    if (recv(socket_desc, server_reply, 2000, 0) < 0) {
        puts("recv failed");
    }
    puts("Reply received\n");
    puts(server_reply);
    return 0;

}


void err_quit(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

char *concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}