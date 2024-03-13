#ifndef  __HTMLRENDER_H__
#define  __HTMLRENDER_H__
#include <map>
#include <string>
#include <sstream>
#include <fstream>

namespace libero
{
	class HtmlRender
	{
	public:
		HtmlRender() = default;
		HtmlRender(const char* file_path);
		~HtmlRender() = default;

		operator std::string();
		std::string operator()(const char* file_path);

		template<class T>
		void Put(const char* name, T&& value);

	private:
		std::string mFilePath;
		std::map<std::string, std::string> mValues;
	};

	template<class T>
	void HtmlRender::Put(const char* name, T&& value)
	{
		std::ostringstream oss;
		oss << value;
		mValues[name] = oss.str();
	}
}

#endif