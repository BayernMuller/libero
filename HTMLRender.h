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
		template<class T>
		void Put(const char* name, T&& value);

		template<int N>
		std::string operator()(const char(&html)[N]);

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

	template<int N>
	std::string HtmlRender::operator()(const char(&html)[N])
	{
		std::ifstream file(html);
		std::string str;
		str.reserve(2048);

		if (!file.is_open() || !file.good())
		{
			throw std::runtime_error("file open error");
		}

		std::istreambuf_iterator<char> iter(file), end;
		str.assign(iter, end);

		std::size_t begin_token = 0;
		while ((begin_token = str.find("{{", begin_token)) != std::string::npos)
		{
			std::size_t end_token = str.find("}}", begin_token);
			std::string key = str.substr(begin_token + 2, end_token - begin_token - 2);
			str.replace(begin_token, end_token - begin_token + 2, mValues[key]);
			begin_token = end_token + 2;
		}
		return str;
	}
}

#endif