#include <string>
#include <iostream>
#include "libero.h"
using namespace std;
using namespace libero;

response index(request req)
{
	if (req.method == "GET")
	{
		HtmlRender render;
		string title = "Hello! I'm Jayden.";
		string comment = "Bayern Munich is the best";
		string email = "cjjunk29@gmail.com";
		render.Insert(title);
		render.Insert(comment);
		render.Insert(email);
		return { 200, render("static/index.html") };
	}
	return { 400, "Not allowed method" };
}

int main() 
{
	Libero server("0.0.0.0", 8500);
	server.Route("/", index);
	server.Run();
}

