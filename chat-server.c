#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

//#include<time.h>
//#include<string.h>
int main(int argc,char *argv[])
{
        //listening socket
        int l_socket;
        l_socket=socket(AF_INET, SOCK_STREAM, 0);

        //store server details
        struct sockaddr_in server_addr;
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(6000);
        server_addr.sin_addr.s_addr=inet_addr(argv[1]);

        //bind the socket to port
        bind(l_socket,(struct sockaddr *) &server_addr,sizeof(server_addr));

        //start listen process
        listen(l_socket,10);

        int s_socket;
        int n;
        struct sockaddr_in client_addr;
        int client_sz;
        char data[200];
        //time_t tick;
        while(1)
          {
                        n=recv(s_socket, data,199,0);
                        printf("%s\n",data);
                        if(n==0)
                                break;
                        data[n]='\0';
                        //printf("%d\n",n);
                        write(s_socket,data, sizeof(data));
                        printf("Enter:");
                        scanf("%s",data);
                        write(s_socket,data, strlen(data));
                        n=recv(s_socket, data,199,0);
                        printf("%s\n",data);
                }
                        close(s_socket);
        }
        return(0);

}
                                                                                                                 59,1          Bot

