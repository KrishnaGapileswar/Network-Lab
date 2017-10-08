#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<time.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#define PORT 5678
int main()
{
        int sockid;
        sockid=socket(AF_INET,SOCK_STREAM,0);
        if(sockid==-1)
        {
                printf("Socket Error");
                return 0;
        }
        struct sockaddr_in server,dummy;
        server.sin_family=AF_INET;
        server.sin_port=htons(PORT);
        server.sin_addr.s_addr=INADDR_ANY;
        int bindstatus=bind(sockid,(struct sockaddr*)&server,sizeof(struct sockaddr));
        if(bindstatus==-1)
        {
                printf("Bind Error");
                return 0;
        }
        int listenstatus=listen(sockid,10);
        if(listenstatus==-1)
        {
                printf("Listen Error");
                return 0;
        }
        int size=sizeof(struct sockaddr);
	while(1)
	{
	int newsd=accept(sockid,(struct sockaddr*)&dummy,&size);
	printf("\nConnected\n");
	int pid=fork();
	if(pid==0)
	{
		char recvmsg[100],sendmsg[100];
		while(1)
		{
		int recvbytes=recv(newsd,recvmsg,100,0);
		printf("Message from client : %s\n",recvmsg);
		if(strcmp(recvmsg,"bye")==0)
		{
			break;
		}	
		printf("ENter message to send to client : ");
		scanf(" %s",sendmsg);
		send(newsd,sendmsg,sizeof(sendmsg),0);	
		}
	}
	}
	close(sockid);
}

