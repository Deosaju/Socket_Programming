#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<time.h>

#define PORT 7891

int main(){
    int TCPSocket, bindSucces ,newSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char buffer[1024];
    time_t tick;


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


    memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));

    bindSucces = bind(TCPSocket,(struct sockaddr*)&serverAddr,sizeof serverAddr);
    if(bindSucces >-1){
        printf("Bind Successfull \n");
    }
    else{
        printf("Bind Failed \n");
    }

    if(listen(TCPSocket,10)==0){
        printf("Listening\n");
    }
    else{
        printf("Error\n");
    }
    addr_size = sizeof serverAddr;
    newSocket = accept(TCPSocket,(struct sockaddr*)&serverAddr,&addr_size);

    //Reciveing Ipaddress
    recv(newSocket,buffer,1024,0);
    printf("IP of Client : %s",buffer);
	return 0;
}