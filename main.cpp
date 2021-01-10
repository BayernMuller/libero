#include <iostream>
#include "HttpServer.h"
using namespace std;

int main() try
{
	HttpServer server("0.0.0.0", 8000);
	server.Run();
}
catch (std::exception& e)
{
	cout << e.what() << endl;
}
catch (...)
{

}