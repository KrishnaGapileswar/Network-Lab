#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<time.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#define PORT 9000
int main()
{
	int sockid;
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
	int bindstatus=bind(sockid,(struct sockaddr*)&server,sizeof(struct sockaddr));
	if(bindstatus==-1)
	{
		printf("Bind Error");
		return 0;
	}
	int listenstatus=listen(sockid,10);
	if(listenstatus==-1)
	{
		printf("Listen Error");
		return 0;
	}
	int size=sizeof(struct sockaddr);
	int newsd=accept(sockid,(struct sockaddr*)&dummy,&size);
	if(newsd==-1)
	{
		printf("Accept Error");
		return 0;
	}
	printf("Connected to Proxy Client...\n");
	int recvbytes;
	char reqtype[10];
	recvbytes=recv(newsd,reqtype,10,0);
	printf("%s",reqtype);
	if(reqtype[0]=='N')
	{
	//puts("here");
	char filename1[20];
	recvbytes=recv(newsd,filename1,20,0);
	if(recvbytes==-1)
	{
		printf("Receive Error\n");
		return 0;
	}

	int fd=open(filename1,O_RDWR | S_IREAD | S_IWRITE);
	if(fd==-1)
	{
		printf("File not found");
		perror("fd");
		close(sockid);
		return 0;
	}
	lseek(fd,0,0);
	char result[3000];
	read(fd,result,3000);
	close(fd);
		int sentbytes=send(newsd,result,sizeof(result),0);
		if(sentbytes==-1)
		{
			printf("Send Error\n");
			return 0;
		}
	close(sockid);
	}
	else
	{
        char filename[8];
	//filename[20]='\0';
	//strcpy(filename,'\0');
        recvbytes=recv(newsd,filename,8,0);
	printf("%s",filename);
	char status[100];
	//strcpy(status,'\0');
	int recvbytes1=recv(newsd,status,100,0);
	printf("\n%s",status);
        if(recvbytes==-1)
        {
                printf("Receive Error\n");
                return 0;
        }
	char result1[100];
	struct stat sb;
	stat(filename,&sb);
	strcpy(result1,ctime(&sb.st_mtime));
	char decision[30];
	int sentbytes;
	if(strcmp(result1,status)==0)
	{
	strcpy(decision,"Uptodate");
	sentbytes=send(newsd,decision,strlen(decision),0);
	}
	else
	{
	strcpy(decision,"NotUptoDate");
	sentbytes=send(newsd,decision,strlen(decision),0);
        int fd=open(filename,O_RDWR | S_IREAD | S_IWRITE);
        if(fd==-1)
        {
                printf("File not found");
                perror("fd");
                close(sockid);
                return 0;
        }
        lseek(fd,0,0);
        char result[3000];
        read(fd,result,3000);
        close(fd);
                sentbytes=send(newsd,result,sizeof(result),0);
                if(sentbytes==-1)
                {
                        printf("Send Error\n");
                        return 0;
                }
        close(sockid);	
	}		
	}	
	return 0;
}
