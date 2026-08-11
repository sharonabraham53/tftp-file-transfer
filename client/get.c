#include "tftp.h"
#include "client.h"

//global variable(s)
extern int sockfd;

Status get()
{
    //declare variable(s)
    int fd,bytes,size;
    char file_name[15],ack[10],buffer[600];

    //checking connection is made or not
    if(connect_flag == 0)
    {
        printf("ERROR : Connection with server has to be made first\n");
        return C_FAILURE;
    }

    //read file name from user
    //prompt message 
    printf("Enter file name : \n");
    //read file input from user
    scanf("%s",file_name);

    //send file name and operation to server
    send(sockfd,file_name,15,0);
    send(sockfd,"GET",4,0);
    
    //send mode
    if(flag == NORMAL)
    {
        send(sockfd,"NORMAL",7,0);
    }
    else if(flag == OCTET)
    {
        send(sockfd,"OCTET",6,0);
    }
    else if(flag == NET_ASCII)
    {
        send(sockfd,"NET",4,0);
    }

    //receive ack
    recv(sockfd,ack,8,0);

    //check if ack is success or failure
    if(strcmp(ack,"failure") == 0)
    {
        return C_FAILURE;
    }

    //open file to receive
    //open file
    fd = open(file_name,O_CREAT|O_RDWR|O_EXCL,0644);

    //error handling
    if(fd == -1)
    {
        if(errno == EEXIST)
        {
            fd = open(file_name,O_RDWR|O_TRUNC);
        }else
        {
            return S_FAILURE;
        }
    }

    //send ack to start receiving data
    send(sockfd,"success",8,0);

    //receive data
    while(1)
    {
        
        //receive size length of data send
        recv(sockfd,&size,4,0);
        
        //receive data
        bytes = recv(sockfd,buffer,size,0);

        //send ack by checking if correct no. of bytes is received or not
        if(bytes == size)
        {
            send(sockfd,"success",8,0);
        }
        else
        {
            send(sockfd,"failure",8,0);

        }

        //convert received data to string
        buffer[bytes] = '\0';

        //check for end flag
        if(strcmp(buffer,"0") == 0)
        {
            break;
        }

        //write data to file
        write(fd,buffer,strlen(buffer));
    }

    
}