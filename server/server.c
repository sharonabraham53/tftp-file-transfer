#include "tftp.h"
#include "server.h"
//global variable(s)
char buffer[50],file_name[20],op[10];

int main() 
{

    //display message
    printf("Server is running\n");

    //connect
    if(s_connect() == S_FAILURE)
    {
        perror("s_connect()");
        exit(1);
    }
    
   
    //recieve file name and operation
    recv(client_fd,file_name,15,0);
    recv(client_fd,op,4,0);
    
    printf("%s\n",file_name);
    printf("%s\n",op);

    if(operation(file_name,op) == S_FAILURE)
    {
        send(client_fd,"failiure",8,0);
    }

    

    
}