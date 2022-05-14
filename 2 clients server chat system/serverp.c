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
        char data2[200];
  
        while(1)
          {
                  s_socket=accept(l_socket,(struct sockaddr *)&client_addr, &client_sz);


                  if(fork()==0)
                  {
                              close(l_socket);
                   while(1)
                   {
                    int m=recv(s_socket,data,199,0);
                 if(m==0)
                         break;
                     data[m]='\0';
                     printf("Recieved from client %d %s\n",n,data);
                     printf("Enter:");
                     scanf("%s",data2);
                     write(s_socket, data2, strlen(data2));
               }
               close(s_socket);
                  }
                  else {
                          n++;
                          close(s_socket);
                  }
          }


        return(0);

}

