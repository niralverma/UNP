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
