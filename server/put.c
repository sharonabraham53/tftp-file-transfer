#include "tftp.h"
#include "server.h"



Status put()
{

    //declare variable(s)
    int bytes,size,fd;
    char buffer[600];

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

    //send ack 
    send(client_fd,"SUCCESS",8,0);

    //receive data
    while(1)
    {
        //receive size length of data send
        recv(client_fd,&size,4,0);
        
        //receive data
        bytes = recv(client_fd,buffer,sizeof(buffer),0);

        //send ack by checking if correct no. of bytes is received or not
        if(bytes == size)
        {
            send(client_fd,"success",8,0);
        }
        else
        {
            send(client_fd,"failure",8,0);

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
