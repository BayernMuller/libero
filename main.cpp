#include <iostream>
#include "HttpServer.h"
using namespace std;

string index(string method, string data)
{
	return "Hello world";
}

int main() try
{
	HttpServer server("0.0.0.0", 8000);
	server.Route("/", index);
	server.Run();
}
catch (std::exception& e)
{
	cout << e.what() << endl;
}