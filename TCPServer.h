#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

class TCPServer
{
	using ADDR = struct sockaddr_in;
public:
	TCPServer(int port);
	virtual ~TCPServer();
	std::pair<SOCKET, ADDR> Accept();
	
protected:
	void close(SOCKET sock);

private:
	SOCKET mServerSock;
};

#endif