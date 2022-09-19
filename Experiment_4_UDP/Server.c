#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
    int udpSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    udpSocket = socket(AF_INET,SOCK_DGRAM,0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(udpSocket,(struct sockaddr *) &serverAddr ,sizeof serverAddr);

    addr_size = sizeof serverStorage;

    while(1){
        recvfrom(udpSocket,buffer,sizeof buffer,0,(struct sockaddr *)&serverStorage ,&addr_size);
        printf("From Client : %s ",buffer);
        if(strcmp(buffer,"bye\n")==0){
            break;
        }
        else
        {
            printf("Checking for message");
        }
        sendto(udpSocket,buffer,sizeof buffer,0,(struct sockaddr *)&serverStorage , addr_size);
    }

}