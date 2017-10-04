#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<fcntl.h>
#define PORT 1024
int a[]={1,2,3,4,5,6,7,8,9,10,11,12};
int main()
{
        int i,sockid;
        sockid=socket(AF_INET,SOCK_STREAM,0);
        if(sockid==-1)
        {
                printf("Socket Error");
                return 0;
        }
        int sentbytes,recvbytes;
        struct sockaddr_in server,dummy;
        server.sin_family=AF_INET;
        server.sin_port=htons(PORT);
        server.sin_addr.s_addr=INADDR_ANY;
        for(i=0;i<8;i++)
                server.sin_zero[i]='\0';
        int bindstatus=bind(sockid,(struct sockaddr*)&server,sizeof(struct sockaddr));
        if(bindstatus==-1)
        {
                printf("Bind Error");
                close(sockid);
        }
	int listenstatus=listen(sockid,20);
	int size=sizeof(struct sockaddr);
	int newsockid=accept(sockid,(struct sockaddr*)&dummy,&size);
	printf("\nConnected to Client\n");
	int SWS[1],LAR,LFS=0;
	printf("Enter Send Window Size : ");
	scanf("%d",&SWS[0]);
	send(newsockid,(int*)SWS,sizeof(SWS),0);
	int b[1];
	i=1;
	int start=0,flag=0;
	while(1)
	{
		int remainingSize[1];
		char s1[5],s2[8];
		int a1[1];
		if(flag==0)
		{
		if(start+1<=12)
		b[0]=a[start++];
		else
		break;
		send(newsockid,b,sizeof(b),0);
		LFS=b[0];
		printf("Last Frame Sent %d \n",LFS);
		int recvbytes=recv(newsockid,s1,sizeof(s1),0);
		s1[recvbytes]='\0';
		recv(newsockid,a1,sizeof(a1),0);
		recvbytes=recv(newsockid,s2,sizeof(s2),0);
		s2[recvbytes]='\0';
		printf("%s %d %s\n",s1,a1[0],s2);
		if(s2[0]=='N')
		{
			start--;
			printf("Advertised Window\n");
                recv(newsockid,remainingSize,sizeof(remainingSize),0);
                printf("%d\n",remainingSize[0]);
		flag=0;
			continue;
		}
		LAR=a1[0];
		}
		printf("Advertised Window\n");
		recv(newsockid,remainingSize,sizeof(remainingSize),0);
		printf("%d\n",remainingSize[0]);
		if(remainingSize[0]==0)
		flag=1;
		else
		flag=0;
		printf("\n\n");
	}
close(sockid);
return 0;
}
