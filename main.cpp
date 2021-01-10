#include <iostream>
#include "HttpServer.h"
using namespace std;

response index(string method, string data)
{
	return { 200, "Hello world" };
}

int main()
{
	HttpServer server("0.0.0.0", 8000);
	server.Route("/", index);
	server.Run();
}
