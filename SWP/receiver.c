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
        struct sockaddr_in client;
        client.sin_family=AF_INET;
        client.sin_port=htons(PORT);
        client.sin_addr.s_addr=INADDR_ANY;
        for(i=0;i<8;i++)
                client.sin_zero[i]='\0';
	int connectstatus=connect(sockid,(struct sockaddr*)&client,sizeof(struct sockaddr));
	printf("Connected to Server\n");
	int RWS[1];
	recv(sockid,RWS,sizeof(RWS),0);
	printf("Receive Window Size : %d\n",RWS[0]);
	int k=0;
	int recvbuffer[100];
	int orgbuffer[100];
	for(i=0;i<100;i++)orgbuffer[i]=0;
	int f[1];
	int remainingSize[1],LFR;
	int flag=0;
	int finalbuffer[100],finalptr=0;
	int start=0;
	int c=0;
		int space;
	while(1)
	{
	int recvbuffer[1];
	if(flag==0)
	{
	recv(sockid,recvbuffer,sizeof(recvbuffer),0);
	if(recvbuffer[0]==3)c++;
	if(recvbuffer[0]==3&&c==1)
	{
	send(sockid,"Frame",strlen("Frame"),0);
        send(sockid,recvbuffer,sizeof(recvbuffer),0);
        send(sockid,"NotRecei",strlen("NotRecei"),0);
	space=0;
	                for(i=0;i<RWS[0];i++)
                {
                        if(orgbuffer[i]==0)
                        {
                                space++;
                        }
                }
                remainingSize[0]=space;
                send(sockid,remainingSize,sizeof(remainingSize),0);
	continue;
	}
	orgbuffer[k]=recvbuffer[0];
	k=(k+1)%5;
	for(i=0;i<RWS[0];i++)
	{
		if(orgbuffer[i]!=0)
		printf("%d ",orgbuffer[i]);
	}
	if(k==0)
	f[0]=orgbuffer[RWS[0]-1];
	else
	f[0]=orgbuffer[k-1];
	LFR=f[0];
	printf("Last Frame Received : %d\n",LFR);
	send(sockid,"Frame",strlen("Frame"),0);
	send(sockid,f,sizeof(f),0);
	send(sockid,"Received",strlen("Received"),0);
	}
	else
	{
		finalbuffer[finalptr++]=orgbuffer[start];
		orgbuffer[start]=0;
		start=(start+1)%5;
	}
		space=0;
		for(i=0;i<RWS[0];i++)
		{
			if(orgbuffer[i]==0)
			{
				space++;
			}
		}
		remainingSize[0]=space;
		send(sockid,remainingSize,sizeof(remainingSize),0);
	if(remainingSize[0]==0)
	flag=1;
	else
	flag=0;
	printf("\n");
	printf("Final Write Buffer\n\n");
	for(i=0;i<finalptr;i++)
	{
	printf("%d ",finalbuffer[i]);
	}
	printf("\n");
	}
	printf("\n\n");	
return 0;
}
