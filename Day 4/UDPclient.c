#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024

void messaging(int socket_desc, struct sockaddr_in server_addr){

	char client_msg[MAXLINE], server_msg[MAXLINE];
	int server_struct_len = sizeof(server_addr);
	
	for(;;){
	
	memset(server_msg, '\0', sizeof(server_msg));
    	memset(client_msg, '\0', sizeof(client_msg));
	
	printf("\n[+]Enter message('n' to stop) : ");
	scanf("%s", client_msg);
	
	if(strcmp("n",client_msg) == 0)
		exit(0);
	
	if(sendto(socket_desc, client_msg, strlen(client_msg), 0, (struct sockaddr*)&server_addr, server_struct_len) < 0){
		printf("[-]Unable to send message\n");
		exit(0);
	}
	
	if(recvfrom(socket_desc, server_msg, sizeof(server_msg), 0, (struct sockaddr*)&server_addr, &server_struct_len) < 0){
		printf("[-]Error while receiving server message\n");
		exit(0);
	}
	printf("[+]Server's response: %s\n", server_msg);
	}
}

void main(){
	int socket_desc;
	struct sockaddr_in server_addr;
	
	socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if(socket_desc < 0){
		printf("[-]Error: Could not create socket\n");
		exit(0);
	}
	printf("[+]Socket created succesfully\n");
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	messaging(socket_desc, server_addr);
	close(socket_desc);
}
