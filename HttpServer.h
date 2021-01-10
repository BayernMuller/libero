#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__
#include "TCPServer.h"
#include <functional>
#include <map>

class HttpServer : public TCPServer
{
	using handler = std::string(*)(std::string, std::string);
public:
	using TCPServer::TCPServer;
	void Run();
	void Route(const char* url, handler fp);

private:
	std::pair<SOCKET, ADDR> Accept() override;
	static void onRequest(SOCKET socket, ADDR addr);

private:
	std::map<std::string, handler> mHanlders;
};

#endif

