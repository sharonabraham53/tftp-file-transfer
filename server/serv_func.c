#include "tftp.h"
#include "server.h"

int client_fd;

Status s_connect()
{
    //defclare variable(s)
    int sockfd, port;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addrsize;

    //socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //error handling 
    if(sockfd == -1)
    {
        perror("SERVER SOCKET");
        return S_FAILURE;
    }

    //assign structure values
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    //bind
    if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1 )
    {
        perror("SERVER BIND");
        return S_FAILURE;
    }

    //listen
    if(listen(sockfd,5) == -1)
    {
        perror("SERVER LISTEN");
        return S_FAILURE;
    }

    //store client address size
    addrsize = sizeof(client_addr);

    //accept
    if((client_fd = accept(sockfd,(struct sockaddr *)&client_addr,&addrsize)) == -1)
    {
        perror("SERVER ACCEPT");
        return S_FAILURE;
    }

    return S_SUCCESS;

}