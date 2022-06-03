#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
#include<signal.h>
int net_socket;
int status;
void handle_sigint(int sig)
{
printf("The client program is exiting ...\n");
close(net_socket);
exit(0);
}

int main(int argc, char *argv[])
{

        signal(SIGINT,handle_sigint);
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(net_socket==-1)
    {
    printf("Error while creating socket...");
    exit(0);
    }

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[2]));
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    status=connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));
    if(status==-1)
    {
    printf("Error while connecting...");
    exit(0);
    }
//recv data
char data[201];
int n;

while(1){
    printf("\nEnter:");
    scanf("%s",data);

      write(net_socket,data, strlen(data));
      
 n=recv(net_socket, data,200,0);
    printf("Received from client %d %s port number  %d  and ip: %s:%d\n",n,data,server_address.sin_port,inet_ntoa(server_address.sin_addr));
    

      n=recv(net_socket, data,200,0);
       printf("Received from client %d %s port number  %d  and ip: %s:%d\n",n,data,server_address.sin_port,inet_ntoa(server_address.sin_addr));
    
      write(net_socket,data, strlen(data));

}

    close(net_socket);

    return(0);
}
