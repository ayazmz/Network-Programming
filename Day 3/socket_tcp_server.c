#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void messaging(int connid)
{
    char user[20], password[20];
    char buffer[80];
    int n;
    read(connid, user, sizeof(user));
    read(connid, password, sizeof(password));
    printf("[+]USERNAME:%s", user);//User Credentials
    printf("[+]PASSWORD:%s", password);

    printf("Authenticate- 'y' or 'n'");
    scanf("%s", buffer);
    for(;;){
    write(connid, buffer, sizeof(buffer));
    if(strcmp(buffer, "n") == 0)
        exit(0);

    read(connid, buffer, sizeof(buffer));

    printf("\n[+]Message from client:%s", buffer);
    write(connid, buffer, sizeof(buffer));
    }
    exit(0);
}
  

int main(){
    char server_message[2000], client_message[2000];
    int client_sock, client_size, len;

    
    struct sockaddr_in server_addr, client_addr;//struct to store server and client details
    int socketid = socket(AF_INET, SOCK_STREAM, 0);//Creating socket

    if(socketid < 0){
        printf("[-]Error!:Socket could not be created\n");
        exit(1);
    }
    printf("[+]Socket created\n");

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;//Specifying IPV4 address family
    server_addr.sin_port = htons(8080);//Specifying port number in binary
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//Local address

    //Binding socket to port & IP
    if ((bind(socketid, (struct sockaddr *)&server_addr, sizeof(server_addr))) != 0)
    {
        printf("\n[-]Socket binding failed.\n");
        exit(0);
    }
    printf("[+]Binded to port\n");

    if((listen(socketid, 5)) != 0){
        printf("[-]Listen Failed\n");
        exit(0);
    }
    else
        printf("[+]Server Listening\n");
    len = sizeof(client_addr);
    client_sock=accept(socketid, (struct sockaddr*)&client_addr, &len);
    if(client_sock<0){
        printf("[-]Server accept failed\n");
        exit(0);
    }
    else{
        printf("[+]Server accepted client\n");
    }
    messaging(client_sock);
    close(socketid);
}
