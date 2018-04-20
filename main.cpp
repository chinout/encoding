#include <iostream>
#include <string>
#include <clocale>
#include <cstdlib>

std::wstring StringToWstring(const std::string& src_str) {
    unsigned max_len = src_str.size() * 2;
    setlocale(LC_CTYPE, "");
    wchar_t* dst_wstr = new wchar_t[max_len];
#ifdef _WIN32
    size_t out_size;
    mbstowcs_s(&out_size, dst_wstr, src_str.c_str(), max_len);
#else
    mbstowcs(dst_wstr, src_str.c_str(), max_len);
#endif
    std::wstring wstr(dst_wstr);
    delete[] dst_wstr;
    return wstr;
}

std::string WstringToString(const std::wstring & src_wstr) {
    unsigned max_len = src_wstr.size() * 4;
    setlocale(LC_CTYPE, "");
    char* dst_str = new char[max_len];
#ifdef _WIN32
    size_t out_size;
    wcstombs_s(&out_size, dst_str, src_wstr.c_str(),max_len);
#else
    wcstombs(dst_str, src_wstr.c_str(),max_len);
#endif
    std::string str(dst_str);
    delete[] dst_str;
    return str;
}


int main() {
    std::string str = "今天你好";
    std::wstring wstr = StringToWstring(str);

    std::wcout << wstr << std::endl;
    std::wcout << wstr.length() << std::endl;
    
    wstr = L"今天你好";
    str = WstringToString(wstr);


    return 0;
}
