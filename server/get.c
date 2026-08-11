#include "tftp.h"
#include "server.h"

int flag;
char c_mode[8];
char net_data[1034];

Status get()
{
    //declare variable(s)
    int bytes,c_bytes,len;
    char ack[10],buffer[600];

    //initialize variable(s)
    int index = 0;

    //open file
    int fd = open(file_name,O_RDONLY|O_EXCL);

    //error handling
    if(fd == -1)
    {
        //check if error occured because file is not present
        if(errno == ENOENT)
        {
            printf("File is not present\n");
            //send failure ack
            send(client_fd,"failure",8,0);
            return S_FAILURE;
        } 
    }

    //recv mode
    recv(client_fd,c_mode,8,0);

    //set number of bytes to send
    c_bytes = mode();
    
    //send success ack
    send(client_fd,"success",8,0);

    //receive ack 
    recv(client_fd,ack,8,0);

    //check if ack is  failure
    if(strcmp(ack,"failure") == 0)
    {
        return S_FAILURE;
    }

    //read 512 bytes from the file and send to client
    while((bytes = read(fd,buffer,c_bytes)) > 0)
    {
        //sending logic if mode is normal or octet
        if(flag != NET_ASCII)
        {
            send(client_fd,&bytes,4,0);
            
            send(client_fd,buffer,bytes,0);

            //receive ack
            recv(client_fd,ack,10,0);

            //send the data again if the ack is failure
            if(strcmp(ack,"failure") == 0)
            {
                lseek(fd,-bytes,SEEK_CUR);
            }
            
        }else
        {
            //convert buffer data to string
            buffer[bytes] = '\0';

            //function call to replace \n with \r and \n
            replace(buffer);

            //logic to send
            //find length of net_data
            len = strlen(net_data);

            while(1)
            {
                //set number bytes to be send
                if(len>=c_bytes)
                {
                    send(client_fd,&c_bytes,4,0);
            
                    send(client_fd,(net_data+index),c_bytes,0);
                    //receive ack
                    recv(client_fd,ack,10,0);

                    //send the next set of data again only if the ack is success
                    if(strcmp(ack,"failure") != 0)
                    {
                        // lseek(fd,-bytes,SEEK_CUR);
                        len = len-c_bytes;
                        index += c_bytes;
                    }

                }
                else if(len<c_bytes && len>0)
                {
                    send(client_fd,&len,4,0);
            
                    send(client_fd,(net_data+index),len,0);

                    //receive ack
                    recv(client_fd,ack,10,0);

                    //break if sending is success
                    if(strcmp(ack,"failure") != 0)
                    {
                        break;
                    }
                }
            }
        }
    }

    //send size of stop flag
    bytes = 2;
    send(client_fd,&bytes,4,0);
    //send stop flag
    send(client_fd,"0",2,0);

    close(fd);

    return S_SUCCESS;

}

int mode()
{
    //logic for setting bytes
    if(strcmp(c_mode,"NORMAL") == 0)
    {
        flag = NORMAL;
        return 512;
    }
    else if(strcmp(c_mode,"OCTET") == 0)
    {
        flag = OCTET;
        return 1;
    }
    else if(strcmp(c_mode,"NET") == 0)
    {
        flag = NET_ASCII;
        return 512;
    }
}

void replace(char buffer[600])
{
    //initialize variable(s)
    int i = 0,j = 0;

    //logic to replace \n with \r and \n
    while(buffer[i] != '\0')
    {
        if(buffer[i] != '\n')
        {
            net_data[j] = buffer[i];
        }else
        {
            net_data[j] = '\r';
            j++;
            net_data[j] = '\n';
        }

        //increment i and j
        i++;
        j++;
    }

    //convert array to string
    net_data[j] = '\0';

    
}