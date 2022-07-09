#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
        int net_socket=socket(AF_INET, SOCK_DGRAM,0);
        if(net_socket<0)
                perror("socket error");
        else
                printf("socket created...\n");

        struct sockaddr_in server_addr;
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(33456);
        server_addr.sin_addr.s_addr=inet_addr("0.0.0.0");

        int len=sizeof(struct sockaddr_in);
        int br=bind(net_socket,(struct sockaddr *)&server_addr, len);
        if(br<0)
                perror("bind error");
        else
                printf("bind completed");

        len=sizeof(struct sockaddr_in);
        getsockname(net_socket, (struct sockaddr *)&server_addr,&len);
        printf("local ip: %s\n",inet_ntoa(server_addr.sin_addr));
        printf("local port: %d\n",ntohs(server_addr.sin_port));

        char buffer[200];
        int n;
        struct sockaddr_in ca;
        while(1)
        {
                n=recvfrom(net_socket,buffer,200,0,(struct sockaddr *)&ca,&len);
                if (n<0)
                        perror("read failed");

                buffer[n]='\0';
                len=sizeof(struct sockaddr_in);
                n=sendto(net_socket,buffer,strlen(buffer),0,(struct sockaddr *)&ca,len);
                if(n<0)
                        perror("write failed...");
}
close(net_socket);
return(0);
}
