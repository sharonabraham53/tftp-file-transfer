#ifndef CLIENT_H
#define CLIENT_H

#include "tftp.h"

//macros
#define NORMAL      0
#define OCTET       1
#define NET_ASCII   2

extern int flag;
extern int s_bytes;
extern int connect_flag;

//function declaration
Status menu();
Status c_connect();
Status put();
Status get();
Status mode();
void replace(char buffer[600]);




#endif //CLIENT_H