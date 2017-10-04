#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#define PORT 6767
int main()
{
int sockid;
sockid=socket(AF_INET,SOCK_STREAM,0);
if(sockid==-1)
{
printf("Socket Error");
return 0;
}
int i;
struct sockaddr_in client,dummy;
client.sin_family=AF_INET;
client.sin_port=htons(PORT);
client.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client.sin_zero[i]='\0';
int connect_status;
connect_status=connect(sockid,(struct sockaddr*)&client,sizeof(struct sockaddr));
if(connect_status==-1)
{
printf("Connect Error");
return 0;
}
char filename[30];
printf("Connected to server....\n");
printf("Enter Filename : ");
scanf("%s",filename);
int sentlen,sentbytes;
sentlen=strlen(filename);
sentbytes=send(sockid,filename,sentlen,0);
if(sentbytes==-1)
{
printf("Sending Error");
return 0;
}
char filedata[4000];
sentbytes=recv(sockid,filedata,4000,0);
filedata[sentbytes]='\0';
//printf("%d",sentbytes);
puts(filedata);
close(sockid);
return 0;
}

