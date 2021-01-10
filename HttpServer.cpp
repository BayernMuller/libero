#include "HttpServer.h"
#include <thread>
#include <sstream>
#include <vector>
#include <iterator>

void HttpServer::Run()
{
	std::cout << "HttpServer is running..." << std::endl;
	while (true)
	{
		auto client = Accept();
		std::thread parser(onRequest, this, client.first, client.second);
		parser.detach();
	}
}

void HttpServer::onRequest(HttpServer* server, SOCKET socket, ADDR addr)
{
	char buf[2049] = { 0, };
	recv(socket, buf, 2048, 0);

	std::istringstream iss(buf);
	std::string method, url;
	iss >> method;
	iss >> url;
	
	auto result = std::make_pair(404, std::string("404 Not Found"));
	auto iter = server->mHanlders.find(url);
	if (iter != server->mHanlders.end())
	{
		result = iter->second(method, url);
	}

	std::ostringstream oss;
	oss << "HTTP/1.1 " << result.first << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << result.second.size() << "\r\n";
	oss << "\r\n" << result.second;
	
	std::string rsp(std::move(oss.str()));
	send(socket, rsp.c_str(), rsp.size(), 0);

	inet_ntop(addr.sin_family, &addr.sin_addr, buf, 128);
	std::cout << buf << ":" << addr.sin_port << " - ";
	std::cout << method << " " << url << " " << result.first << std::endl;

	close(socket);
}

void HttpServer::Route(const char* url, handler fp)
{
	mHanlders[url] = fp;
}

std::pair<SOCKET, TCPServer::ADDR> HttpServer::Accept()
{
	// This function prevents users from using TCPServer::Accept when they call HttpServer's.
	return TCPServer::Accept();
}


