//System header files declare the interfaces to parts of the operating system. 
//We include them in our program to supply the definitions and declarations we need to invoke system calls and libraries.
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

//declaring global variables to access inside any of the functions defined for the program
  int l_socket;
  int status;

//defining this function to specify that the signal should be ignored
void do_nothing(int sig)
{
pid_t childid;
childid=wait(NULL);
printf("%d child has terminated...\n", childid);  //prints the statement
}

//to print the exiting statement before stopping the process
void handle_sigint(int sig)
{
printf("The server program is exiting ...\n");
close(l_socket);  //closes the socket
exit(0); //exits the program
}

int main(int argc, char *argv[])  //A main is a predefined keyword or function in C. It is the first function of every C program that is responsible for starting the execution and termination of the program
{

        signal(SIGINT,handle_sigint); 
        //The signal() function chooses one of three ways in which receipt of the signal number sig is to be subsequently handled. If the value of func is SIG_DFL, default handling for that signal will occur. If the value of func is SIG_IGN, the signal will be ignored
//signal(SIGCHLD,SIG_IGN);

signal(SIGCHLD,do_nothing);
        //listening socket
      
          /*
     * syntax : int socket(int domain, int type, int protocol);
     * input : domain: type of ip => ipv4, ipv6, sets protocols
     *         type : specifies connection type
     *         protocol : protocol to be used
     * socket()  creates  an  endpoint for communication and returns a file descriptor that refers to that endpoint.  The
       file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently  open  for
       the process.
     * return : file descriptor on success else -1
     **/
     
        l_socket=socket(AF_INET, SOCK_STREAM, 0);
      if(l_socket == -1)
      { // checking if socket created successfully or not
        printf("Error while creating socket!!\n"); // prompt message if not created
        exit(0); //exit if not creating
        }
        
        
           /*
     * syntax of sizeof
     * sizeof(exp or datatype)
     * returns : size of datatype or expresion
     * **/
        
        int len=sizeof(struct sockaddr_in);

        //store server details
        struct sockaddr_in server_addr;  // allocation of memory to struct server_addr
        server_addr.sin_family=AF_INET;  // server address family =ipv4
   server_addr.sin_port = htons(0);  // port : let it select by own
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // address = ip
    
        //bind the socket to port
        
    /*
     * syntax of bind:
     *  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
     *  input : int sockfd : file descriptor of socket
     *          const char struct sockaddr *addr : pointer to variable of sockaddr type
     *          socklen_t : size of sockaddr
     * description: When a socket is created with socket(2), it exists in a name space (address family) but has no address assigned to
       it.  bind() assigns the address specified by addr to the socket referred to by the file  descriptor  sockfd.  
       It assigns the "local" end's port number.
       return : -1 if failed 0 on success
     * **/
        
        status=bind(l_socket,(struct sockaddr *) &server_addr,sizeof(server_addr));
            if(status==-1)
    {
    printf("Error while binding...");
    exit(0);
    }
    
        /*
     * syntax of getsockname:
     * int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
     * input : int sockfd : file descriptor of socket
     *          const char struct sockaddr *addr : pointer to variable of sockaddr type
     *          socklen_t : size of sockaddr
     * description :  getsockname()  returns  the current address to which the socket sockfd is bound, in the buffer pointed to by addr.
       The addrlen argument should be initialized to indicate the amount of space (in bytes) pointed to by addr.  
       On  return it contains the actual size of the socket address.
       return : -1 if failed , 0 if success
     * **/

   status=getsockname(l_socket,(struct sockaddr *) &server_addr, &len);
       if(status==-1)
    {
    printf("Error while getting the socket name...");
    exit(0);
    }
    printf("Port number is=%d\n",(int)ntohs(server_addr.sin_port));

        //start listen process
            /*
     * listen function syntax:
     *  int listen(int sockfd, int backlog);
     * description: listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept 
     incoming connection requests using accept(2)
     * return : 0 if success and -1 if failed
     * **/
        
        status=listen(l_socket,10);
            if(status==-1)
    {
    printf("Error while listening...");
    exit(0);
    }

          int s_socket;
        int n;
        struct sockaddr_in client_addr; //
        int client_sz;
        char data[200];
        char data2[200];
  
        while(1)
          {
          
               /*
         * syntax of accept:
         * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
         * description: the  accept()  system  call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET).  It extracts
            the first connection request on the queue of pending connections for the listening socket, sockfd, creates  a  new
            connected  socket, and returns a new file descriptor referring to that socket.  The newly created socket is not in
            the listening state.  The original socket sockfd is unaffected by this call.
        * return : non negative int (fd ) on success or -1 if failed
         * **/
         
                  s_socket=accept(l_socket,(struct sockaddr *)&client_addr, &client_sz);
                      if(s_socket==-1)
    {
    printf("Error while accepting...");
    exit(0);
    }


                  if(fork()==0) //System call fork() is used to create processes. It takes no arguments and returns a process ID. The purpose of fork() is to create a new process, which becomes the child process of the caller. After a new child process is created, both processes will execute the next instruction following the fork() system call.
                  {
                              close(l_socket);
                   while(1)
                   {
                   
                     /*
                 * syntax of recv
                 * ssize_t recv(int socket, void* buffer, size_t length, int flags)
                 * input : int socket : specifies socket file descriptor
                 *         void* buffer : pointer to buffer where the message will be stored
                 *         size_t length : specifies the length of buffer in bytes
                 *         int flags : specifies the type of message reception.
                 * description : recieve the message and store in buffer
                 * return :  message length on success , -1 if failed
                 * **/
                 
                 
                    int m=recv(s_socket,data,199,0);
                             if(m==-1)
    {
    printf("Error while receiving...");
    exit(0);
    }
                 if(m==0)
                         break;
                      data[m]='\0';
                      
                               /*
                 * syntax of getpeername
                 * int getpeername(int  sockfd,  struct sockaddr *addr, socklen_t *addrlen);
                 * input : int sockfd : file descriptor of socket
                 *                      const char struct sockaddr *addr : pointer to variable of sockaddr type
                 *                      socklen_t : size of sockaddr
                 * description : returns  the address of the peer connected to the socket sockfd, in the buffer
                                 pointed to by addr.  The addrlen argument should be initialized to indicate
                                 the amount of space pointed to by  addr.   On return  it  contains  the actual
                                 size of the name returned (in bytes).  The name is truncated if the buffer
                                 provided is too small.
                 * return : 0 on success , -1 on failure
                 * **/
                status = getpeername(s_socket, (struct sockaddr *)&client_addr, &client_sz);
                if(status == -1){
                    printf("Error : no response from client!\n"); 
                    exit(0); 
                }
                      
                      //print message recieved from client
                     printf("Received from client %d %s port number  %d  and ip: %s\n",n,data,client_addr.sin_port,inet_ntoa(client_addr.sin_addr));
                     printf("Enter:");
                     scanf("%s",data2);
                     
                     
                /*
                 * syntax of write
                 * ssize_t write(int socket, void* buffer, size_t length)
                 * input : int socket : specifies socket file descriptor
                 *         void* buffer : pointer to buffer where the message will be stored
                 *         size_t length : specifies the length of buffer in byte
                 * description : writes up to the length bytes from buffer starting at buffer to file reffered by socket
                 * return :  message length on success , -1 if failed
                 * **/
                     write(s_socket, data2, strlen(data2));
               }
               //closing the socket and exiting
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
