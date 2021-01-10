#include "HttpServer.h"
#include <thread>

void HttpServer::Run()
{
	std::cout << "HttpServer is running..." << std::endl;
	while (true)
	{
		auto client = Accept();
		char buf[128] = { 0, };
		inet_ntop(client.second.sin_family, &client.second.sin_addr, buf, 128);
		std::cout << buf << ":" << client.second.sin_port << std::endl;
		std::thread parser(onRequest, client.first, client.second);
		parser.detach();
	}
}

void HttpServer::onRequest(SOCKET socket, ADDR addr)
{
	char buf[2049] = { 0, };
	recv(socket, buf, 2048, 0);
	std::cout << buf << std::endl;

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


