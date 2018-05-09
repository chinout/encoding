#include <iostream>
#include <locale>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

#include "encoding.h"

int main() {
	std::wcout.sync_with_stdio(false);
#if defined(_WIN32) && defined(_MSC_VER) && _MSC_VER < 1800
#else
	std::locale::global(std::locale(""));
#endif
	std::wcout.imbue(std::locale(""));

    std::wstring wstr = L"测试所以这样就可以了吧，。……今天。，！";
    std::string str;

#ifdef _WIN32
    bool ret = yu::Wstr2GBK(wstr, &str);
#else
    bool ret = yu::Wstr2UTF8(wstr, &str);
#endif
    if (ret) {
        std::cout << str.length() << std::endl;
        std::cout << str << std::endl;
    } else {
        std::cout << std::boolalpha << std::endl;
    }

    /*
    std::srand((unsigned int)time(NULL));
    wchar_t buffer[1024];
    memset(buffer, 0, 1024);
    for (int i = 0; i < 1023; ++i) {
        buffer[i] = rand() % 65535;
    }
    std::wstring word_str(buffer, 1024);

#ifdef _WIN32
    ret = yu::Wstr2GBK(word_str, &str);
#else
    ret = yu::Wstr2UTF8(word_str, &str);
#endif    // _WIN32
    if (ret) {
        std::cout << str.length() << std::endl;
        std::cout << str << std::endl;
    } else {
        std::cout << std::boolalpha << std::endl;
    }
    */

    std::string filename("std.txt");
    std::ofstream fout(filename.c_str());
    if(fout) {
        std::wstring wstr = L"测试所以这样就可以了吧，。……今天。，！";
        std::string str;
        bool ret = yu::Wstr2UTF8(wstr, &str);
        if (ret) {
            std::cout << str.length() << std::endl;
            std::cout << str << std::endl;

            fout << str << std::endl;
        } else {
            std::cout << std::boolalpha << std::endl;
        }
    }
}
