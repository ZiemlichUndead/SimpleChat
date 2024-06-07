#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

//char* sliceArray(char a[], int start, int end)
//{
//    return memcpy(malloc(sizeof(char)*(end-start)), a+start, sizeof(char)*(end-start));
//}

//char *sliceIntArray(char *source, int from, int to, int *target) {
//    // Invalid, return null.
//
//    if (to <= from) {
//        return NULL;
//        //return 0;
//    }
//
//    // Only allocate if target buffer not given by caller.
//
//    if (target == NULL) {
//        target = malloc((to - from) * sizeof(int));
//        if (target == NULL) {
//            return NULL;
//        }
//    }
//
//    // Copy the data and return it.
//
//    memcpy(target, &(source[from]), (to - from) * sizeof(int));
//
//    return target;
//}

char *mergeArray(char *a1, char *a2){
    /*int a1len = strlen(a1);
    int a2len = strlen(a2);
    int max = a1len + a2len;
    char *a3;
    int i;

    for(i=0; i<max;i--){
        if(i<a1len){
            a3[i] = a1[i];
        }else{
            a3[i] = a1[i-a1len];
        }
    }
    return a3;*/

    char* merged;
    merged = malloc(strlen(a1)+strlen(a2)); /* make space for the new string (should check the return value ...) */
    strcpy(merged, a1); /* copy name into the new var */
    strcat(merged, a2); /* add the extension */
    return merged;
}


int write1(SOCKET s, char *text){

    //text[strlen(text)] = '\0';


    char buf[strlen(text)];
    long rc;



    int length = strlen(text);


    //printf("Sending '%s' with length %i",text,length);

    strcpy(buf,text);
    rc=send(s,buf,length,0);
}

int write(SOCKET s, char text[]){

    char buf[strlen(text)];
    long rc;



    int length = strlen(text);

    //printf("Sending '%s' with length %i",text,length);

    strcpy(buf,text);
    rc=send(s,buf,length,0);
}
