#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include "server.h"
#include "client.h"


void askMode(){
	printf("Do you want to be a server or a client?(s/c) ");
	char input;
	scanf("%c",&input);

	//printf("Input: %c",input);

	if(input == 's'){
		startServer();
	}else{
		startClient();
	}
}


int init() {
	long rc;
	WSADATA wsa;
	rc = WSAStartup(MAKEWORD(2, 0), & wsa);
	if (rc != 0) {
    	printf("Fehler: startWinsock, fehler code: %d\n", rc);
    	return 1;
	} else {
		printf("Winsock gestartet!\n");
	}




	return 0;
}


int cleanup(){
	WSACleanup();
}


int main() {
  init();
  askMode();
  cleanup();
  return 0;

}
