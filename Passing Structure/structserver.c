#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#define PORT 3056
struct message{
int rollno;
char name[200];
};
int main()
{
struct message input,output;
int i,listen_status,sockid,bind_status;
sockid=socket(AF_INET,SOCK_STREAM,0);
if(sockid==-1)
{
printf("Socket Creation Error");
return 0;
}
struct sockaddr_in server,dummy;
server.sin_family=AF_INET;
server.sin_port=htons(PORT);
server.sin_addr.s_addr=htonl(INADDR_ANY);
for(i=0;i<8;i++)
server.sin_zero[i]='\0';
bind_status=bind(sockid,(struct sockaddr*)&server,sizeof(struct sockaddr));
if(bind_status==-1)
{
printf("Bind Error");
return 0;
}
listen_status=listen(sockid,2);
if(listen_status==-1)
{
printf("Listen Error");
return 0;
}
printf("Enter Your Rollno : ");
scanf("%d",&input.rollno);
printf("Enter Your Name : ");
scanf("%s",input.name);
int size=sizeof(struct sockaddr);
int newsocketid;
newsocketid=accept(sockid,(struct sockaddr*)&dummy,&size);
if(newsocketid==-1)
{
printf("Accept error");
return 0;
}
int msglen,msgbytes;
msglen=sizeof(struct message);
msgbytes=send(newsocketid,&input,msglen,0);
if(msgbytes==-1)
{
printf("Sending error");
return 0;
}
printf("\n\n");
msgbytes=recv(newsocketid,&output,sizeof(struct message),0);
if(msgbytes==-1)
{
printf("Receive Error");
return 0;
}
printf("Message from Client Side.........\n\n");
printf("RollNo : %d",output.rollno);
printf("\nName : %s\n",output.name);
close(sockid);
return 0;
}
