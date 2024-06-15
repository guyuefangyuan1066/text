#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
int main(int argc,char* argv[]){
    unsigned short port =8080;
    if(argc>1){
        port=atoi(argv[1]);
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
saddr.sin_addr.s_addr=htonl(0);
int re=::bind(sock,(sockaddr*)&saddr,sizeof(saddr));
if(re!=0){
    printf("bind port error!\n");
    return -1;
}
printf("bind port success!\n");
//listen
listen(sock,10);
//accept
sockaddr new_saddr;
socklen_t len=0;
int  client_sock=accept(sock,&new_saddr,&len);
printf("client sock=%d\n",client_sock);

//send
char buf[50]="hello word!";
int send_len=send(client_sock,buf,strlen(buf),0);

//read

int read_len=recv(client_sock,buf,strlen(buf)-1,0);
if(read_len>0){
buf[read_len]='\0';
printf("%s \n",buf);
}

close(sock);
    return 0;
}