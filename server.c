#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <pthread.h>
#include "util.h"
//#include "C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\libpthread.a"

int buffersize = 512;

SOCKET acceptSocket;

SOCKET connectedSockets[100];
int clients = 0;



void * listenClient(void * args) {
    SOCKET s = args;
    //char *buf = malloc(buffersize);
    char buf[buffersize];
    int rc = 0;

    //printf("Server output:\n");
    do {
        rc = recv(s, buf, buffersize, 0);
        //printf("Received: %i\n", rc);
        //char *out = slice(buf, 0, rc);

        char *out;
        buf[rc] = '\0';
        strcpy(out,buf);
        printf("%s\n", out);

        int i;
        for(i = 0;i<100;i++){
            if(connectedSockets[i] != s){
                write1(connectedSockets[i],out);
            }
        }


    } while (rc > 0);
}


int listenSocket() {

    while (1) {

        SOCKET connectedSocket;

        long rc = listen(acceptSocket, 10);
        if (rc == SOCKET_ERROR) {
            printf("Fehler: listen, fehler code: %d\n", WSAGetLastError());
            return 1;
        } else {
            printf("acceptSocket ist im listen Modus....\n");
        }

        connectedSocket = accept(acceptSocket, NULL, NULL);
        if (connectedSocket == INVALID_SOCKET) {
            printf("Fehler: accept, fehler code: %d\n", WSAGetLastError());
            return 1;
        } else {
            printf("Neue Verbindung wurde akzeptiert!\n");
        }
        //listenClient(connectedSocket);
        pthread_t thread_id;
        pthread_create( & thread_id, NULL, listenClient, connectedSocket);
        connectedSockets[clients] = connectedSocket;
        clients++;

    }
}

int bindSocket(int port) {

    long rc;
    SOCKADDR_IN addr;

    acceptSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (acceptSocket == INVALID_SOCKET) {
        printf("Fehler: Der Socket konnte nicht erstellt werden, fehler code: %d\n", WSAGetLastError());
        return 1;

    } else {
        printf("Socket erstellt!\n");
    }

    memset( & addr, 0, sizeof(SOCKADDR_IN));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = ADDR_ANY;
    rc = bind(acceptSocket, (SOCKADDR * ) & addr, sizeof(SOCKADDR_IN));

    if (rc == SOCKET_ERROR) {
        printf("Fehler: bind, fehler code: %d\n", WSAGetLastError());
        return 1;
    } else {
        printf("Socket an port %i gebunden\n", port);
    }
    return 0;
}

int startServer() {
    bindSocket(5000);
    listenSocket();
}
