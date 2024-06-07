#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <pthread.h>
#include "util.h"
//#include "C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\libpthread.a"

char *prefix = "test: ";
char *name = "test";
char *ip = "127.0.0.1";
int port = 5000;

SOCKET s;
int clientBuffersize = 1024;
int isRunning = 0;

int createSocket() {
    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s == INVALID_SOCKET) {
        printf("Fehler: Der Socket konnte nicht erstellt werden, fehler code: %d\n", WSAGetLastError());
        return 1;
    } else {
        printf("Socket erstellt!\n");
    }
    return 0;
}

int connectSocket(char ip[], int port) {
    long rc;
    SOCKADDR_IN addr;

    memset( & addr, 0, sizeof(SOCKADDR_IN)); // zuerst alles auf 0 setzten
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    rc = connect(s, (SOCKADDR * ) & addr, sizeof(SOCKADDR));
    if (rc == SOCKET_ERROR) {
        printf("Fehler: connect gescheitert, fehler code: %d\n", WSAGetLastError());
        return 1;
    } else {
        printf("Verbunden mit %s:%i\n", ip, port);
    }

}

void read(char buf[]) {
    long rc;

    rc = recv(s, buf, clientBuffersize, 0);
    if (rc == 0) {
        printf("Server hat die Verbindung getrennt..\n");
        return;
    }
    if (rc == SOCKET_ERROR) {
        printf("Fehler: recv, fehler code: %d\n", WSAGetLastError());
        return;
    }

    //buf[rc]='\0';
    //printf("\nServer antwortet: %s\n",buf);

}

void writer(void * args) {

    while (isRunning) {
        printf("Chat as %s|> ",name);
        char input[clientBuffersize];
        //char *input = malloc(clientBuffersize);
        scanf("%s", &input);


        char *out = mergeArray(prefix, input);
        //printf("%s",out);

        write1(s, out);
    }
}

void * reader(void * args) {
    while (isRunning) {
        char * buf = malloc(clientBuffersize);
        read(buf);
        printf("\nServer: %s\n", buf);
        printf("Chat as %s|> ",name);
        free(buf);
    }
}

void readConfig(){
    printf("Choose your nickname: ");
    scanf("%s",&name);

    prefix = mergeArray(name,": ");

    printf("Enter IP address: ");
    scanf("%s",&ip);

    printf("Enter port: ");
    scanf("%i",&port);


}

int startClient() {
    createSocket();
    //readConfig();
    isRunning = 1;
    connectSocket(ip, port);

    pthread_t reader_id;
    pthread_t writer_id;
    pthread_create( & reader_id, NULL, reader, NULL);
    //pthread_create(&reader_id, NULL, reader, NULL);
    writer(NULL);

    isRunning = 0;
    closesocket(s);

}
