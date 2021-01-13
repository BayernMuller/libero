#include <string>
#include <iostream>
#include "HttpServer.h"
using namespace std;

response index(request req)
{
	if (req.method == "GET")
	{
		HtmlRender render;
		string title = "BayernMuller";
		string comment = "I am a developer";
		render.Insert(title);
		render.Insert(comment);
		return { 200, render("static/index.html") };
	}
	return { 400, "Not allowed method" };
}

response button(request req)
{
	HtmlRender render;
	return { 200, render("static/button.html") };
}

int main() 
{
	HttpServer server("0.0.0.0", 8000);
	server.Route("/", index);
	server.Route("/button", button);
	server.Run();
}
