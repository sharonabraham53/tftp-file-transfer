#ifndef TFTP_H
#define TFTP_H

//header files
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

//macro
#define PORT 5000

//enum
typedef enum
{
    S_SUCCESS,
    S_FAILURE,
    C_SUCCESS,
    C_FAILURE
}Status;

#endif //TFTP_H