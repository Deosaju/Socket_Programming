#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 7891
int compare(char a[],char b[])  
{  
    int flag=0,i=0;  // integer variables declaration  
    while(a[i]!='\0' &&b[i]!='\0')  // while loop  
    {  
       if(a[i]!=b[i])  
       {  
           flag=1;  
           break;  
       }  
       i++;  
    }  
    if(flag==0)  
    return 0;  
    else  
    return 1;  
}  
int main(){
    int TCPSocket, bindSucces ,newSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char buffer[1024],word[100];
    char dictionary[][100][100]={{"deo","loveable"},{"leo","loveee"},{"nithin","derkkboi"}};
    // for(int i =0 ; i<2 ;i++){
    //     printf("%s\n",dictionary[i][0]);
    // }

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
    memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);

    recv(newSocket,buffer,sizeof buffer,0);
    for(int i =0; i<2 ;i++){
        printf("%s ",dictionary[i][1]);
        int c = compare(buffer,dictionary[i][0]);
        if(c){
            strcpy(word,dictionary[i][1]);
            printf("%d",i);
            printf("%s",dictionary[i][1]);
            send(newSocket,word,sizeof word,0);
        }
    }

	return 0;
}