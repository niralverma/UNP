#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{

    //create a socket
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //connect to a server
    //where we want to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6000);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connect( net_socket, ( struct sockaddr * ) &server_address, sizeof( server_address));

   char data[201];
int n;
while(1){
    printf("\nEnter:");
    scanf("%s",data);

      write(net_socket,data, strlen(data));

      n=recv(net_socket, data,200,0);


      printf("%s\n",data);
        n=recv(net_socket, data,200,0);
      printf("%s\n",data);
      write(net_socket,data, strlen(data));

}

    close(net_socket);

    return(0);
}

