#ifndef  __HTMLRENDER_H__
#define  __HTMLRENDER_H__
#include <map>
#include <string>
#define Insert(x) Put(#x, x)

class HTMLRender
{
public:
	template<class T>
	void Put(const char* name, T&& value);

private:
	std::map<std::string, std::string> mValues;
};

template<class T>
void HTMLRender::Put(const char* name, T&& value)
{
	mValues[name] = std::to_string(value);
}

#endif // ! __HTMLRENDER_H__
