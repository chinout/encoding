#include <iostream>
#include <locale>
#include <string>

#include "encoding.h"

int main() {
    std::setlocale(LC_ALL, "");
    std::wcout << L"LC_CTYPE: " << std::setlocale(LC_CTYPE, NULL) << std::endl;
    //std::wcout.imbue(std::locale("zh_CN.UTF-8"));

    std::string str = "测试所以这样就可以了吧，。……今天。，！";
    std::wstring wstr;

    std::wcout << std::boolalpha << UTF82Wstr(str, &wstr) << std::endl;

    std::wcout << wstr << std::endl;
    std::wcout << wstr.length() << std::endl;

    for(size_t i = 0; i < wstr.length(); ++i) {
        std::wcout << L"U+" << std::hex << (long)wstr.at(i) << std::endl;
    }

}
