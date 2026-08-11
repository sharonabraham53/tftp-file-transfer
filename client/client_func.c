#include "tftp.h"
#include "client.h"

//global variable
int sockfd;

Status c_connect()
{
    //declare variable(s)
    char buffer[50],ip_addr[30];
    socklen_t addrsize;
    struct sockaddr_in server_addr;

    //initialize variable(s)
    int i = 0,count = 0, invalid_ip = 0;

    //read ip address from user
    //prompt message
    printf("Enter ip address : \n");
    //read input from user
    scanf("%s",ip_addr);

    //validate ip address
    while(ip_addr[i] != '\0')
    {
        if(ip_addr[i] == '.')
        {
            count++;
        }

        if(ip_addr[i] == '.' && ip_addr[i+1] == '.')
        {
            invalid_ip = 1;
        }

        //increment i
        i++;
    }

    if(count != 3 || invalid_ip == 1)
    {
        printf("CLIENT : Invalid ip address\n");
        exit(1);
    }

    

    //socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //error handling 
    if(sockfd == -1)
    {
        perror("CLIENT SOCKET");
        return C_FAILURE;
    }

    //assign structure values
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);

    //store size of address
    addrsize = sizeof(server_addr);

    if(connect(sockfd,(struct sockaddr *)&server_addr,addrsize) == -1)
    {
        perror("CLIENT CONNECT");
        return C_FAILURE;
    }

    connect_flag = 1;
    return C_SUCCESS;
}