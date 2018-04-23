#include <iostream>
#include <locale>
#include <string>
#include <ctime>
#include <cstdlib>

#include "encoding.h"

int main() {
    setlocale(LC_ALL, "");
    std::cout << "LC_CTYPE: " << setlocale(LC_CTYPE, NULL) << std::endl;

    std::wstring wstr = L"测试所以这样就可以了吧，。……今天。，！";
    std::string str;

#ifdef _WIN32
    bool ret = Wstr2GBK(wstr, &str);
#else
    bool ret = Wstr2UTF8(wstr, &str);
#endif
    if (ret) {
        std::cout << str.length() << std::endl;
        std::cout << str << std::endl;
    } else {
        std::cout << std::boolalpha << std::endl;
    }

    std::srand((unsigned int)time(NULL));
    wchar_t buffer[1024];
    memset(buffer, 0, 1024);
    for (int i = 0; i < 1023; ++i) {
        buffer[i] = rand() % 65535;
    }
    std::wstring word_str(buffer, 1024);

#ifdef _WIN32
    ret = Wstr2GBK(word_str, &str);
#else
    ret = Wstr2UTF8(word_str, &str);
#endif    // _WIN32
    if (ret) {
        std::cout << str.length() << std::endl;
        std::cout << str << std::endl;
    } else {
        std::cout << std::boolalpha << std::endl;
    }

	getchar();
}
