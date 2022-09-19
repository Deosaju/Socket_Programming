#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 7891

typedef struct packect{
    char data[1024];
}Packet;

typedef struct frame{
    int frame_kind;
    int sq_no;
    int ack;
    Packet packet;
}Frame;

int main(){
    int TCPSocket, bindSucces ,connectionRes;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char buffer[1024];

    int frame_id = 0;
	Frame frame_send;
	Frame frame_recv;
	int ack_recv = 1;

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
    connectionRes = connect(TCPSocket,(struct sockaddr*)&serverAddr,addr_size);
    
    
while(1){
		
		if(ack_recv == 1){
			frame_send.sq_no = frame_id;
			frame_send.frame_kind = 1;
			frame_send.ack = 0;		
	
			printf("Enter Data: ");
			scanf("%s", buffer);
			strcpy(frame_send.packet.data, buffer);
			sendto(TCPSocket, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
			printf("[+]Frame Send\n");
		}
		int addr_size = sizeof(serverAddr);
		int f_recv_size = recvfrom(TCPSocket, &frame_recv, sizeof(frame_recv), 0 ,(struct sockaddr*)&serverAddr, &addr_size);
		
		if( f_recv_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frame_id+1){
			printf("[+]Ack Received\n");
			ack_recv = 1;
		}else{
			printf("[-]Ack Not Received\n");
			ack_recv = 0;
		}	
  			
		frame_id++;		
	}
}