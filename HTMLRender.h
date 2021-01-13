#ifndef  __HTMLRENDER_H__
#define  __HTMLRENDER_H__
#include <map>
#include <string>
#include <sstream>

namespace libero
{
	class HtmlRender
	{
	public:
		template<class T>
		void Put(const char* name, T&& value);

		std::string operator()(const char* html);

	private:
		std::map<std::string, std::string> mValues;
	};

	template<class T>
	void HtmlRender::Put(const char* name, T&& value)
	{
		std::ostringstream oss;
		oss << value;
		mValues[name] = std::move(oss.str());
	}
}

#endif