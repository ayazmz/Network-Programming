#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

char user[20];
char password[20];
void messaging(int sockid){
    char message[20];

    printf("\nUsername:");
    scanf("%s", user);

    printf("\nPassword:");
    scanf("%s", password);

    write(sockid, user, sizeof(user));
    write(sockid, password, sizeof(password));
    for(;;){
    read(sockid, message, sizeof(message));

    printf("\nEnter message to be sent:");
    scanf("%s", message);

    if(strcmp(message, "n") == 0)//Messaging terminated when 'n' entered
        break;

    printf("[+]Sending\n");
    write(sockid, message, sizeof(message));
    }
    exit(0);
}
int main(){
    int socketid;
    struct sockaddr_in server_addr, client_addr;

    socketid = socket(AF_INET, SOCK_STREAM, 0);
    if(socketid == -1){
        printf("[-]Socket Creation Failed\n");
        exit(0);
    }
    else
        printf("[+]Socket Created!\n");
    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);
    
    if(connect(socketid, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0){
        printf("[-]Connection with server failed\n");
        exit(0);
    }
    else{
        printf("[+]Connected to server!\n");
    }

    messaging(socketid);
    close(socketid);
    return 0;
}