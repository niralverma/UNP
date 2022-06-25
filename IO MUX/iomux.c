#include<sys/select.h>
#include<stdio.h>
int main()
{
        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(0,&read_set); //FD_SET(fileno(stdin),&read_set);
        select(1,&read_set,NULL,NULL,NULL);
        printf("Completed...\n");
        return(0);

}

////////////////////////////////////////////////////////


#include<sys/select.h>
#include<stdio.h>
int main()
{
        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(3,&read_set); //FD_SET(fileno(stdin),&read_set);
        int sr = select(4,&read_set,NULL,NULL,NULL);


        printf("Completed...with select return %d\n",sr);
        return(0);

}

output: -1

////////////////////////////////////////////////////



#include<sys/select.h>
#include<stdio.h>
int main()
{
        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(0,&read_set); //FD_SET(fileno(stdin),&read_set);
        int sr = select(1,&read_set,NULL,NULL,NULL);


        printf("Completed...with select return %d\n",sr);
        return(0);

}

output: 1

//////////////////////////////////////////////////////////////
        //using select function as sleep function 
#include<sys/select.h>
#include<stdio.h>
#include<sys/time.h>
//struct timeval{
//long tv_sec;
//long tv_usec;
//};
int main()
{
        struct timeval t;
        t.tv_sec=5;
        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(0,&read_set); //FD_SET(fileno(stdin),&read_set);
        int sr = select(1,&read_set,NULL,NULL,&t);


        printf("Completed...with select return %d\n",sr);
        return(0);

}
    
output: 0
        
 /////////////////////////////////////////////////////////////
       POLL
       
     #include<sys/select.h>
#include<stdio.h>
#include<sys/time.h>
#include<poll.h>
//struct timeval{
//long tv_sec;
//long tv_usec;
//};
int main()
{  /*
        struct timeval t;
        t.tv_sec=5;
        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(0,&read_set); //FD_SET(fileno(stdin),&read_set);
        int sr = select(1,&read_set,NULL,NULL,&t);
        

        printf("Completed...with select return %d\n",sr);
*/
        struct pollfd fds[1];
        fds[0].fd=0;
        fds[0].events=POLLIN|POLLERR;
        poll(fds,1,-1);

        printf("completed...\n");
        return(0);

}

/////////////////////////////////////////////////////////////////

#include<sys/select.h>
#include<stdio.h>
#include<sys/time.h>
#include<poll.h>
//struct timeval{
//long tv_sec;
//long tv_usec;
//};
int main()
{  /*
        struct timeval t;
        t.tv_sec=5;
        fd_set read_set;
        FD_ZERO(&read_set);
        FD_SET(0,&read_set); //FD_SET(fileno(stdin),&read_set);
        int sr = select(1,&read_set,NULL,NULL,&t);
        

        printf("Completed...with select return %d\n",sr);
*/
        struct pollfd fds[1];
        fds[0].fd=0;
        fds[0].events=POLLIN|POLLERR;
        poll(fds,1,5000); //5000ms to wait

        printf("completed...\n");
        return(0);

}

