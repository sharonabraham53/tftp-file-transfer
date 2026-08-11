#ifndef SERVER_H
#define SERVER_H

extern int client_fd;
extern char file_name[20],op[10];

//macros
#define NORMAL      0
#define OCTET       1
#define NET_ASCII   2


//function declaration
Status s_connect();
Status put();
Status get();
Status operation();
int mode();
void replace(char buffer[600]);



#endif //SERVER_H
