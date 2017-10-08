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
#define LEN 1024
#define PORT 3456
int main()
{
int i,sockid;
sockid=socket(AF_INET,SOCK_DGRAM,0);
if(sockid==-1)
{
printf("Socket Error");
return 0;
}
int recvbytes,sentbytes;
struct sockaddr_in client;
client.sin_family=AF_INET;
client.sin_port=htons(PORT);
client.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client.sin_zero[i]='\0'; 
int connectstatus=connect(sockid,(struct sockaddr*)&client,sizeof(struct sockaddr));
int j;
for(j=1;j<=5;j++)
{
char msg[100],repmsg[100];
int size=sizeof(struct sockaddr);
printf("\nEnter Message to send : ");
gets(repmsg);
sentbytes=sendto(sockid,repmsg,strlen(repmsg),0,(struct sockaddr*)&client,size);
recvbytes=recvfrom(sockid,msg,sizeof(msg),0,NULL,NULL);
msg[recvbytes]='\0';
printf("Message From Server : %s ",msg);
}
return 0;
}
