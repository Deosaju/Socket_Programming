#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 7891

int main(){
    int TCPSocket, bindSucces ,connectionRes;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char buffer[1024];

    TCPSocket = socket(AF_INET,SOCK_STREAM,0);
    if(TCPSocket < 0){
        printf("Error In creating Socket \n");
    }
    else{
        printf("Socket created Successfully \n");
    }

    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7821);
    addr_size = sizeof serverAddr;
    memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
    connectionRes = connect(TCPSocket,(struct sockaddr*)&serverAddr,addr_size);
    
    strcpy(buffer,inet_ntoa(serverAddr.sin_addr));
    send(TCPSocket,buffer,1024,0);

    printf("IP Send to server");
}