#include "HttpServer.h"
#include <thread>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstring>

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
	std::cout << buf << std::endl;

	std::string reqlog;
	reqlog.reserve(22);

	request req = parseRequest(buf);
	reqlog = req.method + " " + req.url + " ";

	response result{ 404, "404 Not Found" };
	auto iter = server->mHanlders.find(req.url);
	if (iter != server->mHanlders.end())
	{
		result = iter->second(std::move(req));
	}
	
	std::string rsp = createResponse(result);
	send(socket, rsp.c_str(), rsp.size(), 0);

	inet_ntop(addr.sin_family, &addr.sin_addr, buf, 128);
	std::cout << buf << ":" << addr.sin_port << " - ";
	std::cout << reqlog << result.first << std::endl;
	close(socket);
}

request HttpServer::parseRequest(char* req)
{
	char* content = strstr(req, "\r\n\r\n");
	if (content)
	{
		content[0] = '\0';
		content += 4;
	}
	std::istringstream iss(req);
	std::string method, url, protocol, key;
	std::map<std::string, std::string> header;
	iss >> method >> url >> protocol;
	while (iss >> key)
	{
		char buf[128] = { 0, };
		key.pop_back();
		iss.getline(buf, sizeof(buf));
		buf[strlen(buf) - 1] = 0;
		header[key] = buf + 1;
	}
	return {std::move(method), std::move(url), content ? content : "", std::move(header)};
}

std::string HttpServer::createResponse(const response& res)
{
	std::ostringstream oss;
	oss << "HTTP/1.1 " << res.first << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << res.second.size() << "\r\n";
	oss << "\r\n" << res.second;
	return std::move(oss.str());
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


