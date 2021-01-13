#include <iostream>
#include "HttpServer.h"
using namespace std;
#define add(container, x) container[#x] = x

response index(request req)
{
	
	if (req.method == "GET")
	{
		return { 200, req.url };
	}
	return { 400, "Not allowed method" };
}

response me(request req)
{
	return { 200, "<h1>BayernMuller</h1><p><h4>Embedded Software Developer</h4></p>" };
}

int main() 
{
	HttpServer server("0.0.0.0", 8000);
	server.Route("/", index);
	server.Route("/me", me);
	server.Run();
}
