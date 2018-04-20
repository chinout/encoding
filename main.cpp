#include <iostream>
#include <string>
#include <clocale>
#include <cstdlib>
#include <cstring>

bool Str2Wstr(const std::string & str, std::wstring & wstr)
{
    size_t max_len = str.size() * 2;
    setlocale(LC_CTYPE, "");
    wchar_t* dst_wstr = new wchar_t[max_len];
#ifdef _WIN32
    size_t out_size;
    int ret = mbstowcs_s(&out_size, dst_wstr, max_len, str.c_str(), max_len);
    if(ret != 0)
    {
        delete[] dst_wstr;
        return false;
    }
#else
    size_t ret = mbstowcs(dst_wstr, str.c_str(), max_len);
    std::cerr << ret << std::endl;
    std::cerr << static_cast<size_t>(-1) << std::endl;

    if(ret == static_cast<size_t>(-1))
    {
        delete[] dst_wstr;
        return false;
    }
#endif
    wstr = dst_wstr;
    delete[] dst_wstr;

    return true;
}

bool Wstr2Str(const std::wstring & wstr, std::string & str)
{
    size_t max_len = wstr.size() * 4;
    setlocale(LC_CTYPE, "");
    char* dst_str = new char[max_len];
#ifdef _WIN32
    size_t out_size;
    int ret = wcstombs_s(&out_size, dst_str, max_len, wstr.c_str(), max_len);
    if(ret != 0)
    {
        delete[] dst_str;
        return false;
    }
#else
    size_t ret = wcstombs(dst_str, wstr.c_str(),max_len);
    std::cerr << ret << std::endl;
    std::cerr << static_cast<size_t>(-1) << std::endl;
    if(ret == static_cast<size_t>(-1)) {
        delete[] dst_str;
        return false;
    }
#endif
    str = dst_str;
    delete[] dst_str;

    return true;
}


int main() {

    {
        std::string str = "今天你好，。#！";
        std::wstring wstr;
        bool ret = Str2Wstr(str, wstr);

        std::wcout << std::boolalpha << ret << std::endl;
        if(ret)
        {
            std::wcout << wstr << std::endl;
            std::wcout << wstr.length() << std::endl;
        }
    }

    {
        srand(time(NULL));
        char buffer[1024];
        memset(buffer, 0, 1024);
        for(int i = 0; i < 1023; ++i)
        {
            buffer[i] = rand() % 256;
        }
        std::string str(buffer, 1024);

        std::wstring wstr;
        bool ret = Str2Wstr(str, wstr);

        std::wcout << std::boolalpha << ret << std::endl;
        if(ret)
        {
            std::wcout << wstr << std::endl;
            std::wcout << wstr.length() << std::endl;
        }
    }

    {
        /*
        std::wstring wstr = L"今天你好，。#！";
        std::string str;
        bool ret = Wstr2Str(wstr, str);

        std::cout << str << std::endl;
        std::cout << str.length() << std::endl;
        }
        */
    }

    return 0;
}
