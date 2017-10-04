#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#define PORT 8888
struct request{
char method[20];
char version[20];
char url[50];
char username[20];
char password[20];
char date1[20];
};
struct response{
char version[20];
char content[3000];
char statuscode[20];
char method[20];
char date1[20];
};

char username[20][10]={"Ganesh","Ram","Abi","Ravi","Sam"};
char password[20][10]={"abc","bcd","cda","agt","tre"};
int main()
{
//struct postreq reqmsg;
struct response respmsg;
struct request msg;
int i,sockid;
sockid=socket(AF_INET,SOCK_STREAM,0);
if(sockid==-1)
{
printf("SocketError");
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
printf("Error in binding");
return 0;
}
int listenstatus;
listenstatus=listen(sockid,20);
if(listenstatus==-1)
{
printf("Listen Error");
return 0;
}
int newsockid;
int size=sizeof(struct sockaddr);
newsockid=accept(sockid,(struct sockaddr*)&dummy,&size);
if(newsockid==-1)
{
printf("Accept Error");
return 0;
}
printf("\n\nConnection Established...\n\n");
int recvbytes;
printf("Request from client.....\n\nReceived on");
int sentbytes;
recvbytes=recv(newsockid,&msg,sizeof(struct request),0);
system("date");
if(recvbytes==-1)
{
printf("Receive Error");
return 0;
}
printf("%s %s HTTP/%s\r\n\r\n",msg.method,msg.url,msg.version);
if(msg.method[0]=='G')
{
int fd=open(msg.url,O_RDWR);
read(fd,respmsg.content,3000);
strcpy(respmsg.version,msg.version);
strcpy(respmsg.statuscode,"OK");
strcpy(respmsg.method,msg.method);
sentbytes=send(newsockid,&respmsg,sizeof(struct response),0);
if(sentbytes==-1)
{
printf("Send Error");
return 0;
}
}
else
{
int i,flag=0;
int array[30];
int pos=0;
for(i=0;msg.username[i]!='\0';i++)
{
int as=(int)msg.username[i];
array[pos++]=as;
}
int num=0;
for(i=0;i<pos;i++)
{
num=num*100+array[i];
}
printf("%d",num);
/*for(i=0;i<5;i++)
{
if(strcmp(msg.username,username[i])==0)
{
if(strcmp(msg.password,password[i])==0)
{
strcpy(respmsg.content,"Ok username and Password are verified");
flag=1;
break;
}
}
}
if(flag==0)
{
strcpy(respmsg.content,"Invalid username or Password");
}*/
strcpy(respmsg.version,msg.version);
strcpy(respmsg.statuscode,"OK");
strcpy(respmsg.method,msg.method);
sentbytes=send(newsockid,&respmsg,sizeof(struct response),0);
if(sentbytes==-1)
{
printf("Send error");
return 0;
}
}
close(sockid);
return 0;
}
