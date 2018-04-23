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

    bool ret = Wstr2UTF8(wstr, &str);
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

    ret = Wstr2UTF8(word_str, &str);
    if (ret) {
        std::cout << str.length() << std::endl;
        std::cout << str << std::endl;
    } else {
        std::cout << std::boolalpha << std::endl;
    }

	getchar();
}
