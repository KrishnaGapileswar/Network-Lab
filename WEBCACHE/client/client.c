#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#define PORT 8000
int main()
{
int sockid;
sockid=socket(AF_INET,SOCK_STREAM,0);
if(sockid==-1)
{
printf("Socket Error\n");
return 0;
}
int i;
struct sockaddr_in client;
client.sin_family=AF_INET;
client.sin_port=htons(PORT);
client.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
{
client.sin_zero[i]='\0';
}
int connectstatus;
connectstatus=connect(sockid,(struct sockaddr*)&client,sizeof(struct sockaddr));
if(connectstatus==-1)
{
printf("Connection Error\n");
return 0;
}
else
{
printf("\nConnected to Proxy....\n");
}
char name[20];
printf("Enter Filename : ");
scanf("%s",name);
int sentbytes=send(sockid,name,sizeof(name),0);
if(sentbytes==-1)
{
printf("Send Error\n");
return 0;
}
char result[3000];
int recvbytes;
recvbytes=recv(sockid,result,3000,0);
if(recvbytes==-1)
{
printf("Receive Error");
return 0;
}
result[recvbytes]='\0';
printf("The content of the file %s is\n\n",name);
puts(result);
close(sockid);
return 0;
}
