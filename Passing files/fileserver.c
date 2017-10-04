#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#define PORT 6767
int main()
{
int i,sockid;
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
for(i=0;i<8;i++)
server.sin_zero[i]='\0';
int bindstatus;
bindstatus=bind(sockid,(struct sockaddr*)&server,sizeof(struct sockaddr));
if(bindstatus==-1)
{
printf("Bind error\n");
return 0;
}
int listen_status;
listen_status=listen(sockid,2);
if(listen_status==-1)
{
printf("Listen Error");
return 0;
}
int newsd;
int size=sizeof(struct sockaddr);
newsd=accept(sockid,(struct sockaddr*)&dummy,&size);
if(newsd==-1)
{
printf("Accept Error");
return 0;
}
char filename[30];
int msglen;
msglen=recv(newsd,filename,30,0);
if(msglen==-1)
{
printf("Receive Error");
return 0;
}
filename[msglen]='\0';
//puts(filename);
char buf[4000];
int fd=open(filename,O_RDWR);
if(fd==-1)
{
strcpy(buf,"File Not found");
msglen=send(newsd,buf,sizeof(buf),0);
return 0;
}
//char buf[4000];
read(fd,buf,4000);
msglen=send(newsd,buf,sizeof(buf),0);
close(sockid);
return 0;
}

