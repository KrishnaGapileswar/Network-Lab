#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#define PORT 3056
struct recvmsg{
int rollno;
char name[200];
};
int main()
{
struct recvmsg output,input;
int i,sockid,connect_status;
sockid=socket(AF_INET,SOCK_STREAM,0);
if(sockid==-1)
{
printf("Socket Creation Error");
return 0;
}
struct sockaddr_in client,dummy;
client.sin_family=AF_INET;
client.sin_port=PORT;
client.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client.sin_zero[i]='\0';
connect_status=connect(sockid,(struct sockaddr*)&client,sizeof(struct sockaddr));
if(connect_status==-1)
{
printf("Connect Err");
return 0;
}
//char recvmsg[101];
int msgbytes,msglen;
msgbytes=recv(sockid,&output,sizeof(struct recvmsg),0);
printf("Received from Server.....\n");
printf("Roll No : %d\n",output.rollno);
printf("Name : %s\n",output.name);
printf("\n\nEnter Your Rollno : ");
scanf("%d",&input.rollno);
printf("Enter Your Name : ");
scanf("%s",input.name);
msgbytes=send(sockid,&input,sizeof(struct recvmsg),0);
if(msgbytes==-1)
{
printf("Send Error");
return 0;
}
close(sockid);
return 0;
}
