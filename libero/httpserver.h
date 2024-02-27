#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__
#include "TCPServer.h"
#include <map>

namespace libero
{
	// simple response object for users that saves http state code and data.
	using response = std::pair<int, std::string>;

	// structor saves the result that parsed http request.
	struct request
	{
		std::string method;
		std::string url;
		std::string content;
		std::map<std::string, std::string> header;
	};

	class HttpServer : public TCPServer
	{
		// Http Request Handler Type for users
		using handler = response(*)(request);

	public:
		// using parent's constructor
		using TCPServer::TCPServer;

		// The function that begins http server.
		void Run();

		// The function that adds url and handlert.
		void Route(const char* url, handler fp);

	private:
		// It is a public function in TCPServer, but private in HttpServer.
		std::pair<SOCKET, ADDR> Accept() override;

		// Thread function that handles http request.
		static void onRequest(HttpServer* server, SOCKET socket, ADDR addr);

		// parsing http request protocol.
		static request parseRequest(char* req);

		// creating http response protocol with response object.
		static std::string createResponse(const response& res);

	private:
		// saving url and its handlers.
		std::map<std::string, handler> mHanlders;
	};
}
#endif

