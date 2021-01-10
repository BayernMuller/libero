#include <iostream>
#include "TCPServer.h"
using namespace std;

int main() try
{
	TCPServer server("0.0.0.0", 8000);
	auto info = server.Accept();
	cout << "connected" << endl;
	char buf[1024] = {0};
	recv(info.first, buf, 1024, 0);
	cout << buf << endl;
}
catch (std::exception& e)
{
	cout << e.what() << endl;
}
catch (...)
{

}