#include "htmlrender.h"

namespace libero
{
    HtmlRender::HtmlRender(const char* file_path)
        : mFilePath(file_path)
    {
    }
    
	std::string HtmlRender::operator()(const char* html)
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

    HtmlRender::operator std::string()
    {
		if (mFilePath.empty())
		{
			throw std::runtime_error("file path is empty");
		}
        return (*this)(mFilePath.c_str());
    }
}