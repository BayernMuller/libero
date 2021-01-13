#include <string>
#include <iostream>
#include "HttpServer.h"
using namespace std;

response index(request req)
{
	HtmlRender render;

	string title = "BayernMuller";
	string comment = "I am a developer";
	render.Put("title",title);
	render.Insert(comment);
	
	if (req.method == "GET")
	{
		return { 200, render("static/index.html") };
	}
	return { 400, "Not allowed method" };
}

int main() 
{
	HttpServer server("0.0.0.0", 8000);
	server.Route("/", index);
	server.Run();
}
