#define stain static inline
#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET sock;
typedef struct sockaddr_in sockip;
stain sockip ipaddrint(int addr,int port){
	struct sockaddr_in ip={.sin_family=AF_INET,.sin_addr=htons(addr),.sin_port=htons(port)};
	return ip;
}
stain sockip ipaddr(char*addr,int port){
	return ipaddrint(inet_addr(addr),port);
}
stain sock socksock(ipaddr*ip,int type,int proto){
	sock s=socket(AF_INET,type,proto);
	connect(s,(struct sockaddr*)ip,sizeof(ipaddr));
	return s;
}
stain sock tcpsock(ipaddr*ip){
	return socksock(ip,OCK_STREAM,IPPROTO_TCP);
}
stain sock udpsock(ipaddr*ip){
	return socksock(ip,SOCK_DGRAM,IPPROTO_UDP);
}
stain sock lissock(int port,int mx){
	sock l=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	struct sockaddr_in ip={.sin_family=AF_INET,.sin_addr.s_addr=htonl(INADDR_ANY),.sin_port=htons(port)};
	bind(lis,(void*)&ip,sizeof(ip));
	listen(l,mx);
	return l;
}
stain sock acpsock(sock lis){
	return accept(lis,0,0);
}
stain void pull(sock s,void*p,int len){
	do{
		int r;
		while((r=read(s,p,len))==-1&&errno==EINTR);
		p+=r;
		len-=r;
	}while(len);
}
stain void push(sock s,void*p,int len){
	do{
		int r;
		while((r=write(s,p,len))==-1&&errno==EINTR);
		p+=r;
		len-=r;
	}while(len);
}
stain void close(sock s){
	closesocket(s)
}
#else
#include <errno.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
typedef int sock;
typedef struct sockaddr_in sockip;
stain sockip ipaddrint(int addr,int port){
	struct sockaddr_in ip={.sin_family=AF_INET,.sin_addr=htons(addr),.sin_port=htons(port)};
	return ip;
}
stain sockip ipaddr(char*addr,int port){
	struct sockaddr_in ip={.sin_family=AF_INET,.sin_port=htons(port)};
	inet_aton(addr,&ip.sin_addr);
	return ip;
}
stain sock socksock(ipaddr*ip,int type,int proto){
	sock s=socket(AF_INET,type,proto);
	connect(s,(struct sockaddr*)ip,sizeof(ipaddr));
	return s;
}
stain sock tcpsock(ipaddr*ip){
	return socksock(ip,SOCK_STREAM,IPPROTO_TCP);
}
stain sock udpsock(ipaddr*ip){
	return socksock(ip,SOCK_DGRAM,IPPROTO_UDP);
}
stain sock lissock(int port,int mx){
	sock l=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	struct sockaddr_in ip={.sin_family=AF_INET,.sin_addr.s_addr=htonl(INADDR_ANY),.sin_port=htons(port)};
	bind(lis,(void*)&ip,sizeof(ip));
	listen(l,mx);
	return l;
}
stain sock acpsock(sock lis){
	return accept(lis,0,0);
}
stain void pull(sock s,void*p,int len){
	do{
		int r;
		while((r=read(s,p,len))==-1&&errno==EINTR);
		p+=r;
		len-=r;
	}while(len);
}
stain void push(sock s,void*p,int len){
	do{
		int r;
		while((r=write(s,p,len))==-1&&errno==EINTR);
		p+=r;
		len-=r;
	}while(len);
}
stain void close(sock s){
	close(s)
}
stain int any(int s){
	struct pollfd pfd={.fd=s,.events=POLLIN};
	while((s=poll(&pfd,1,1))==-1);
	return s;
}
#endif
#undef stain