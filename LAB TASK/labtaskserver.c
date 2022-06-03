#System header files declare the interfaces to parts of the operating system. 
#We include them in our program to supply the definitions and declarations we need to invoke system calls and libraries.
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
//#include<time.h>
//#include<string.h>

#declaring global variables to access inside any of the functions defined for the program
  int l_socket;
  int status;

#defining this function to specify that the signal should be ignored
void do_nothing(int sig)
{
pid_t childid;
childid=wait(NULL);
printf("%d child has terminated...\n", childid);  #prints the statement
}

#to print the exiting statement before stopping the process
void handle_sigint(int sig)
{
printf("The server program is exiting ...\n");
close(l_socket);  #closes the socket
exit(0); #exits the program
}

int main(int argc, char *argv[])  #A main is a predefined keyword or function in C. It is the first function of every C program that is responsible for starting the execution and termination of the program
{

        signal(SIGINT,handle_sigint); 
//signal(SIGCHLD,SIG_IGN);
signal(SIGCHLD,do_nothing);
        //listening socket
      
        l_socket=socket(AF_INET, SOCK_STREAM, 0);
                 if(l_socket==-1)
    {
    printf("Error while creating socket...");
    exit(0);
    }
        int len=sizeof(struct sockaddr_in);

        //store server details
        struct sockaddr_in server_addr;
        server_addr.sin_family=AF_INET;
   server_addr.sin_port = htons(0);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
        //bind the socket to port
        status=bind(l_socket,(struct sockaddr *) &server_addr,sizeof(server_addr));
            if(status==-1)
    {
    printf("Error while binding...");
    exit(0);
    }

   status=getsockname(l_socket,(struct sockaddr *) &server_addr, &len);
       if(status==-1)
    {
    printf("Error while getting the socket name...");
    exit(0);
    }
    printf("Port number is=%d\n",(int)ntohs(server_addr.sin_port));

        //start listen process
        status=listen(l_socket,10);
            if(status==-1)
    {
    printf("Error while listening...");
    exit(0);
    }

          int s_socket;
        int n;
        struct sockaddr_in client_addr;
        int client_sz;
        char data[200];
        char data2[200];
  
        while(1)
          {
                  s_socket=accept(l_socket,(struct sockaddr *)&client_addr, &client_sz);
                      if(s_socket==-1)
    {
    printf("Error while accepting...");
    exit(0);
    }


                  if(fork()==0)
                  {
                              close(l_socket);
                   while(1)
                   {
                    int m=recv(s_socket,data,199,0);
                             if(m==-1)
    {
    printf("Error while receiving...");
    exit(0);
    }
                 if(m==0)
                         break;
                      data[m]='\0';
                     printf("Received from client %d %s port number  %d  and ip: %s:%d\n",n,data,server_addr.sin_port,inet_ntoa(client_addr.sin_addr));
                     printf("Enter:");
                     scanf("%s",data2);
                     write(s_socket, data2, strlen(data2));
               }
               close(s_socket);
               exit(0);
                  }
                  else {
                          n++;
                          close(s_socket);
                  }
          }


        return(0);

}
