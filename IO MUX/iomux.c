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

//blocking mode


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
