//
// Created by Steffen on 03.03.2022.
//

#ifndef SOCKETTEST_UTIL_H
#define SOCKETTEST_UTIL_H

#include <winsock2.h>
#include <windows.h>

char *mergeArray(char *a1, char *a2);
int write1(SOCKET s, char *text);
int write(SOCKET s, char text[]);


#endif //SOCKETTEST_UTIL_H
