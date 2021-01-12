#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__
#include "TCPServer.h"
#include <functional>
#include <map>

using response = std::pair<int, std::string>;
struct request
{
	std::string method;
	std::string url;
	std::string content;
	std::map<std::string, std::string> header;
};

class HttpServer : public TCPServer
{
	using handler = response(*)(request);
public:
	using TCPServer::TCPServer;
	void Run();
	void Route(const char* url, handler fp);

private:
	std::pair<SOCKET, ADDR> Accept() override;
	static void onRequest(HttpServer* server, SOCKET socket, ADDR addr);
	static request parseRequest(char* req);
	static std::string createResponse(const response& res);

private:
	std::map<std::string, handler> mHanlders;
};

#endif

