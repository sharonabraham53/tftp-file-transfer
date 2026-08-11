#include "tftp.h"
#include "server.h"



Status operation()
{
    
    
    if(strcmp(op,"PUT") == 0)
    {
        put();
    }
    else if(strcmp(op,"GET") == 0)
    {
        get();
    }
    
}