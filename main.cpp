#include <iostream>
#include <ctime>
#include "HttpServer.h"
using namespace std;

response index(string method, string data)
{
	char str[128] = {0,};
	auto now = time(nullptr);
	ctime_s(str, 128, &now);
	return { 200, str };
}

response name(string method, string data)
{
	return { 200, "<h1>BayernMuller</h1>" };
}

int main()
{
	HttpServer server("0.0.0.0", 8000);
	server.Route("/", index);
	server.Route("/name", name);
	server.Run();
}
