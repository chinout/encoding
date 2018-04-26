#include <string>

namespace yu {

#ifdef _WIN32
bool Str2Wstr(const std::string & str, const unsigned int & code_page,
              std::wstring* wstr);

bool Wstr2Str(const std::wstring & wstr, const unsigned int& code_page,
              std::string* str);

bool GBK2Wstr(const std::string& str, std::wstring* wstr);

bool Wstr2GBK(const std::wstring& wstr, std::string* str);
#endif    // _WIN32

bool UTF82Wstr(const std::string & str, std::wstring* wstr);

bool Wstr2UTF8(const std::wstring & wstr, std::string * str);

}    // namespace yu
