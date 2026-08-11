#include "tftp.h"
#include "client.h"

Status menu()
{
    //declare variable(s)
    int opt;
    //super loop
    while(1)
    {
        //diplay menu
        printf("1.CONNECT\n");
        printf("2.PUT\n");
        printf("3.GET\n");
        printf("4.MODE\n");
        printf("5.EXIT\n");
        printf("Enter the choice : \n");

        //read input from user
        scanf("%d",&opt);

        //switch case for perform function call or exit based on user's choice
        switch(opt)
        {
            //connect
            case 1:

                if(c_connect() == C_SUCCESS)
                {
                    printf("CLIENT : Connection made successfully\n");
                } 
                else
                {
                    printf("CLIENT : Failed to connect\n");
                }
                
            break;

            case 2:

            if(put() == C_SUCCESS)
            {
                printf("CLIENT : PUT operation successful\n");
            }
            else
            {
                printf("CLIENT : PUT operation failed\n");
                
            }
            
            break;
            
            case 3:
           
            if(get() == C_SUCCESS)
            {
                printf("CLIENT : GET operation successful\n");
            }
            else
            {
                printf("CLIENT : GET operation failed\n");
                
            }

            break;

            case 4:

            if(mode() == C_SUCCESS)
            {
                printf("CLIENT : MODE operation successful\n");
            }
            else
            {
                printf("CLIENT : MODE operation failed\n");
                
            }

            break;

            //return to main function for exit
            case 5:
                return C_SUCCESS;
            break;

        }
    }
}