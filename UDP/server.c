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
int j;
for(j=1;j<=5;j++)
{
char msg[100],repmsg[100];
int size=sizeof(struct sockaddr);
recvbytes=recvfrom(sockid,msg,sizeof(msg),0,(struct sockaddr*)&dummy,&size);
msg[recvbytes]='\0';
printf("\nMessage From Client : %s ",msg);
printf("\nENter Message to send : ");
gets(repmsg);
sentbytes=sendto(sockid,repmsg,strlen(repmsg),0,(struct sockaddr*)&dummy,size);
}
return 0;
}
