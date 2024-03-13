#include <libero/libero.h>
using namespace libero;

response index(request req)
{
	if (req.method == "GET")
	{
		HtmlRender render;
		std::string title = "Hello! I'm Jayden, also known as bayernmuller";
		std::string comment = "Bayern München is the best team in the world";
		std::string email = "cjjunk29@gmail.com";
		render.Insert(title);
		render.Insert(comment);
		render.Insert(email);
		return { 200, render("static/introduction.html") };
	}
	return { 400, "Not allowed method" };
}

response muller(request req)
{
    return { 200, R"(
            <html>
                <head>
                    <title>Link</title>
                </head>
                <body>
                    <a href="/">Back</a>
                    <h1>He is Thomas Muller!</h1>
                </body>
            </html>
        )" };
}

int main() 
{
	Libero server("0.0.0.0", 8500);
	server.Route("/", index);
    server.Route("/muller", muller);
	server.Run();
}

