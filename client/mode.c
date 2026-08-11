#include "client.h"
#include "tftp.h"


Status mode()
{
    //declare variable(s)
    int mode;

    //prompt message
    printf("Please select any one of the following option : \n");
    printf("1.Normal mode\n");
    printf("2.Octet mode\n");
    printf("3.Net ascii mode\n");

    //read input from user
    scanf("%d",&mode);

    //switch for selecting mode
    switch(mode)
    {
        //normal mode
        case 1:
            flag = NORMAL;
            s_bytes = 512;
        break;
        
        //octet mode
        case 2:
            flag = OCTET;
            s_bytes = 1;
        break;
        
        //net ascii mode
        case 3:
            flag = NET_ASCII;
            s_bytes = 512;
        break;

        //default
        default:
            printf("Invalid option");
        break;
    }

    return C_SUCCESS;
}