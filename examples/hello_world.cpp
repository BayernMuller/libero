#include <libero/libero.h>
using namespace libero;

response index(request req)
{
	return { 200, HtmlRender()("static/hello_world.html") };
}

int main() 
{
	Libero server("0.0.0.0", 8500);
	server.Route("/", index);
	server.Run();
}

