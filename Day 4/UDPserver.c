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

void messaging(int socket_desc, struct sockaddr_in client_addr){

	char client_msg[MAXLINE], server_msg[MAXLINE];
	int client_struct_length = sizeof(client_addr);
	for(;;){
	
	memset(server_msg, '\0', sizeof(server_msg));
   	memset(client_msg, '\0', sizeof(client_msg));
    
	if(recvfrom(socket_desc, client_msg, sizeof(client_msg), 0, (struct sockaddr*)&client_addr, &client_struct_length) < 0){
		printf("[-]Could not receive message\n");
		exit(0);
	}
	printf("[+]Received message from IP: %s & port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	printf("[+]Message from client: %s\n", client_msg);
	
	printf("\n[+]Enter message to client('n' to stop): ");
	scanf("%s", server_msg);
	
	if(strcmp("n", server_msg) == 0)
		exit(0);
	
	if(sendto(socket_desc, server_msg, strlen(server_msg), 0, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0){
		printf("[-]Can't send\n");
		exit(0);
	}
	}
}
	
void main(){
	int socket_desc;
	struct sockaddr_in server_addr, client_addr;
	
	socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if(socket_desc < 0){
		printf("[-]Error: Could not create socket\n");
		exit(0);
	}
	
	printf("[+] Socket Created!\n");
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
	printf("[-]Error: Could not bind to port\n");
	exit(0);
	}
	printf("[+] Binded to port\n");
	
	messaging(socket_desc, client_addr);
	close(socket_desc);
}
