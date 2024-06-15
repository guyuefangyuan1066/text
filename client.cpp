#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
int main(int argc,char*argv[]){

unsigned short port=8080;
const char *ip="127.0.0.1";
if(argc>2){
    ip=argv[1];
    port=atoi(argv[2]);
}
//create socket
int sock=socket(AF_INET,SOCK_STREAM,0);
if(sock<=0){
    printf("creata socket error!\n");
    return -1;
}

printf(" create socket success!\n");
//bind port
sockaddr_in saddr;
memset(&saddr,0,sizeof(saddr));
saddr.sin_family=AF_INET;
saddr.sin_port=htons(port);
saddr.sin_addr.s_addr=inet_addr(ip);
int re=connect(sock,(sockaddr*)&saddr,sizeof(saddr));
if(re!=0){
    printf("connect port error!\n");
    return -1;
}
printf("connect port success!\n");

int len ;
char buf[50];
len=recv(sock,buf,sizeof(buf)-1,0);
if(len>0){
    buf[len]='\0';
    printf("%s \n",buf);
}
strcpy(buf,"send from client");
len =send(sock,buf,sizeof(buf),0);

close(sock);

return 0;
}