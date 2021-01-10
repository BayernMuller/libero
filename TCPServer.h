#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include <iostream>
#include <string>

#ifdef _WIN32
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using SOCKET = unsigned int;
#endif

class TCPServer
{
	using ADDR = ::sockaddr_in;
public:
	TCPServer(const char* ip, int port);
	virtual ~TCPServer();
	std::pair<SOCKET, ADDR> Accept();
	
protected:
	void close(SOCKET sock);

private:
	SOCKET mServerSock;
	std::string mIPAdress;
	int mPort;
};

#endif