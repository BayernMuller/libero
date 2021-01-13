#ifndef  __HTMLRENDER_H__
#define  __HTMLRENDER_H__
#include <map>
#include <string>
#define Insert(x) Put(#x, x)

class HtmlRender
{
public:
	template<class T>
	void Put(const char* name, T value);

	template<int N>
	void Put(const char* name, const char(&value)[N]);

	template<>
	void Put(const char* name, std::string value);

	std::string operator()(const char* html);

private:
	std::map<std::string, std::string> mValues;
};

template<class T>
void HtmlRender::Put(const char* name, T value)
{
	mValues[name] = std::move(std::to_string(value));
}

template<int N>
void HtmlRender::Put(const char* name, const char(&value)[N])
{
	mValues[name] = value;
}

template<>
void HtmlRender::Put(const char* name, std::string value)
{
	mValues[name] = value;
}

#endif // ! __HTMLRENDER_H__
