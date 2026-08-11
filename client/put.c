#include "client.h"
#include "tftp.h"

//global variable(s)
extern int sockfd;
char net_data[1034];

Status put()
{
    //declare variable(s)
    int fd,bytes,len;
    char file_name[15],ack[10],buffer[600];

    //initialize variable(s)
    int index = 0;

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

    //open if file is present or return if file is not present
    fd = open(file_name,O_RDONLY);

    //error handling
    if(fd == -1)
    {
        //check if error occured because file is not present
        if(errno == ENOENT)
        {
            printf("File is not present\n");
            return C_FAILURE;
        }
    }

    char cmd[4] = "PUT";
    //send file name and operation to server
    send(sockfd,file_name,15,0);   
    //send PUT request 
    send(sockfd,cmd,4,0);

    //recv ack
    recv(sockfd,ack,10,0);

    //error handling
    if(strcmp(ack,"failure") == 0)
    {
        printf("Server refused to perform PUT operation\n");
        return C_FAILURE;
    }

    //read data from the file
    while((bytes = read(fd,buffer,s_bytes)) > 0)
    {
        //sending logic if mode is normal or octet
        if(flag != NET_ASCII)
        {
            send(sockfd,&bytes,4,0);
            
            send(sockfd,buffer,bytes,0);

            //receive ack
            recv(sockfd,ack,10,0);

            //send the data again if the ack is failure
            if(strcmp(ack,"failure") == 0)
            {
                lseek(fd,-bytes,SEEK_CUR);
            }
        }
        //logic if mode is net ascii
        else
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
                if(len>=s_bytes)
                {
                    send(sockfd,&s_bytes,4,0);
            
                    send(sockfd,(net_data+index),s_bytes,0);
                    //receive ack
                    recv(sockfd,ack,10,0);

                    //send the next set of data again only if the ack is success
                    if(strcmp(ack,"failure") != 0)
                    {
                        // lseek(fd,-bytes,SEEK_CUR);
                        len = len-s_bytes;
                        index += s_bytes;
                    }

                }
                else if(len<s_bytes && len>0)
                {
                    send(sockfd,&len,4,0);
            
                    send(sockfd,(net_data+index),len,0);

                    //receive ack
                    recv(sockfd,ack,10,0);

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
    send(sockfd,&bytes,4,0);
    //send stop flag
    send(sockfd,"0",2,0);

    close(fd);

    return C_SUCCESS;
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
