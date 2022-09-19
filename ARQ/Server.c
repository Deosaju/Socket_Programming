#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct packect{
    char data[1024];
}Packet;
typedef struct frame{
    int frame_kind;
    int sq_no;
    Packet packet;
    int ack;
}Frame;


int main(){
    int TCPSocket, bindSucces ,newSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;


    int frame_id=0;
	Frame frame_recv;
	Frame frame_send;	


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
    // if(bindSucces >-1){
    //     printf("Bind Successfull \n");
    // }
    // else{
    //     printf("Bind Failed \n");
    // }

    if(listen(TCPSocket,10)==0){
        printf("Listening\n");
    }
    else{
        printf("Error\n");
    }
    addr_size = sizeof serverAddr;  
    newSocket = accept(TCPSocket,(struct sockaddr*)&serverAddr,&addr_size);
    printf("%d",newSocket);
    while(1){
		int f_recv_size = recvfrom(TCPSocket, &frame_recv, sizeof(Frame), 0, (struct sockaddr*)&serverAddr, &addr_size);
		if (f_recv_size > 0 && frame_recv.frame_kind == 1 && frame_recv.sq_no == frame_id){
			printf("[+]Frame Received: %s\n", frame_recv.packet.data);
			
			frame_send.sq_no = 0;
			frame_send.frame_kind = 0;
			frame_send.ack = frame_recv.sq_no + 1;
			sendto(TCPSocket, &frame_send, sizeof(frame_send), 0, (struct sockaddr*)&serverAddr, addr_size);
			printf("[+]Ack Send\n");
		}else{
			printf("[+]Frame Not Received\n");
		}
		frame_id++;	
	}
	return 0;
}