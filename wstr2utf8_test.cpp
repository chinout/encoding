#include <iostream>
#include <locale>
#include <string>

#include "encoding.h"

int main() {
    std::setlocale(LC_ALL, "");
    std::cout << "LC_CTYPE: " << std::setlocale(LC_CTYPE, NULL) << std::endl;

    std::wstring wstr = L"测试所以这样就可以了吧，。……今天。，！";
    std::string str;

    std::cout << std::boolalpha << Wstr2UTF8(wstr, &str) << std::endl;
    std::cout << str.length() << std::endl;
    std::cout << str << std::endl;

}
