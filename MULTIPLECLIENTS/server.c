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
#define PORT 2120
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
	int i=1;
	while(i<=3)
	{
        int newsd=accept(sockid,(struct sockaddr*)&dummy,&size);
        if(newsd==-1)
        {
                printf("Accept Error");
                return 0;
        }
        printf("Connected to Client %d\n",i);
	i++;
	int recvbytes;
	char message[30];
	recvbytes=recv(newsd,message,30,0);
	printf("Message from Client %d\n",i-1);
	printf("%s",message);
	char reply[30];
	scanf(" %s",reply);
	int sentbytes=send(newsd,reply,strlen(reply),0);
	}
	close(sockid);
	return 0;
}
