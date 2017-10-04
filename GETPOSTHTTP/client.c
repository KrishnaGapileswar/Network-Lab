#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#define PORT 9999
struct request{
char method[20];
char version[20];
char url[50];
char username[20];
char password[20];
};
struct response{
char version[20];
char content[3000];
char statuscode[20];
char method[20];
};
int main()
{
int i;
//struct postreq reqmsg;
struct response respmsg;
struct request msg;
int sockid;
sockid=socket(AF_INET,SOCK_STREAM,0);
if(sockid==-1)
{
printf("SocketError");
return 0;
}
char method[20],version[20];
struct sockaddr_in client;
client.sin_family=AF_INET;
client.sin_port=htons(PORT);
client.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client.sin_zero[i]='\0';
int connectstatus;
connectstatus=connect(sockid,(struct sockaddr*)&client,sizeof(struct sockaddr));
 printf("\n\nConnected to Server\n\n");
 printf("Enter method name : ");
scanf("%s",msg.method);
 printf("Enter Version     : ");
scanf("%s",msg.version);
int recvbytes,sentbytes;
if(msg.method[0]=='G')
{
 printf("Enter File Name   : ");
scanf("%s",msg.url);
strcpy(msg.password,"");
strcpy(msg.username,"");
sentbytes=send(sockid,&msg,sizeof(struct request),0);
if(sentbytes==-1)
{
printf("Send Error");
return 0;
}
recvbytes=recv(sockid,&respmsg,sizeof(struct response),0);
if(recvbytes==-1)
{
printf("Receive Error");
return 0;
}
printf("Received from server...\n\n");
printf("HTTP/%s %s %s \r\n\r\n",respmsg.version,respmsg.method,respmsg.statuscode);
puts(respmsg.content);
}
else if(msg.method[0]=='P')
{
char username[20],pass[20];
printf("Enter String1 : ");
scanf(" %s",msg.username);
printf("ENter String2 : ");
scanf(" %s",msg.password);
strcpy(msg.url,"");
sentbytes=send(sockid,&msg,sizeof(struct request),0);
if(sentbytes==-1)
{
printf("Send Error");
return 0;
}
recvbytes=recv(sockid,&respmsg,sizeof(struct response),0);
if(recvbytes==-1)
{
printf("Receive Error");
return 0;
}
printf("Received from Server...\n\n");
printf("HTTP/%s %s %s \r\n\r\n",respmsg.version,respmsg.method,respmsg.statuscode);
puts(respmsg.content);
}
else
{
printf("Enter a Valid Method Name ");
}
close(sockid);
return 0;
}
