#include <iostream>
#include <locale>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

#include "encoding.h"

int main() {
    setlocale(LC_ALL, "");
    std::wcout << L"LC_CTYPE: " << setlocale(LC_CTYPE, NULL) << std::endl;
    //std::wcout.imbue(std::locale("Chinese (Simplified)_China.936"));

	std::wstring test_str = L"今天测试";
	std::wcout << test_str << std::endl;

    std::string str = "测试所以这样就可以了吧，。……今天。，！";
    std::wstring wstr;

#ifdef _WIN32
    bool ret = yu::GBK2Wstr(str, &wstr);
#else
    bool ret = yu::UTF82Wstr(str, &wstr);
#endif
    if(ret) {
        std::wcout << wstr << std::endl;
        std::wcout << wstr.length() << std::endl;
    } else {
        std::wcout << std::boolalpha << false << std::endl;
    }

    for(size_t i = 0; i < wstr.length(); ++i) {
        std::wcout << L"U+" << std::hex << (long)wstr.at(i) << std::endl;
    }
    std::wcout << std::dec;

    /*
    std::srand((unsigned int)time(NULL));
    char buffer[1024];
    memset(buffer, 0, 1024);
    for (int i = 0; i < 1023; ++i) {
        buffer[i] = rand() % 256;
    }
    std::string word_str(buffer, 1024);

#ifdef _WIN32
    ret = yu::GBK2Wstr(word_str, &wstr);
#else
    ret = yu::UTF82Wstr(word_str, &wstr);
#endif
    if(ret) {
        std::wcout << wstr << std::endl;
        std::wcout << wstr.length() << std::endl;
    } else {
        std::wcout << std::boolalpha << false << std::endl;
    }
    */

    std::string filename("std.txt");
    std::ifstream fin(filename);
    if(fin) {
        std::string file_content((std::istreambuf_iterator<char>(fin)),
                                 std::istreambuf_iterator<char>());

        std::wstring wstr;
        bool ret = yu::UTF82Wstr(file_content, &wstr);
        if(ret) {
            std::wcout << wstr;
            std::wcout << wstr.length() << std::endl;
        } else {
            std::wcout << std::boolalpha << false << std::endl;
        }
    }

}
