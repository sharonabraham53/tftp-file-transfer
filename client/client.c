#include "tftp.h"
#include "client.h"

//global variable(s)
int flag,s_bytes,connect_flag;

int main()
{
    //socket
    if(menu() == C_SUCCESS)
    {
        printf("CLIENT : Conncected successfully\n");
    }
    else
    {
        printf("CLIENT : Connection failed\n");
        exit(1);
    }



    return 0;
}