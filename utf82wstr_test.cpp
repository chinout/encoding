#include <iostream>
#include <locale>
#include <string>
#include <ctime>
#include <cstdlib>

#include "encoding.h"

int main() {
    std::setlocale(LC_ALL, "");
    std::wcout << L"LC_CTYPE: " << std::setlocale(LC_CTYPE, NULL) << std::endl;
    //std::wcout.imbue(std::locale("zh_CN.UTF-8"));

    std::string str = "测试所以这样就可以了吧，。……今天。，！";
    std::wstring wstr;

    bool ret = UTF82Wstr(str, &wstr);
    if(ret) {
        std::wcout << wstr << std::endl;
        std::wcout << wstr.length() << std::endl;
    } else {
        std::wcout << std::boolalpha << false << std::endl;
    }

    for(size_t i = 0; i < wstr.length(); ++i) {
        std::wcout << L"U+" << std::hex << (long)wstr.at(i) << std::endl;
    }

    std::srand(time(NULL));
    char buffer[1024];
    memset(buffer, 0, 1024);
    for (int i = 0; i < 1023; ++i) {
        buffer[i] = rand() % 256;
    }
    std::string word_str(buffer, 1024);

    ret = UTF82Wstr(word_str, &wstr);
    if(ret) {
        std::wcout << wstr << std::endl;
        std::wcout << wstr.length() << std::endl;
    } else {
        std::wcout << std::boolalpha << false << std::endl;
    }
}
