#include <cstring>
#include <cstdio>
#include <iostream>
#include <cerrno>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#include <ctype.h>
#else
#include <iconv.h>
#endif



// wchar_t转成UTF-8
int Wstr2UTF8(const wchar_t* c_str, int a_nSrcSize, char* a_szDest, int a_nDestSize)
{
#ifdef _WIN32
    return WideCharToMultiByte(CP_UTF8, 0, c_str, -1, a_szDest, a_nDestSize, NULL, NULL);
#else
    size_t result;
    iconv_t env;
    env = iconv_open("UTF-8","WCHAR_T");
    if (env==(iconv_t)-1)
    {
        printf("iconv_open WCHAR_T->UTF8 error%s %d/n",strerror(errno),errno) ;
        return -1;
    }
    result = iconv(env,(char**)&c_str,(size_t*)&a_nSrcSize,(char**)&a_szDest,(size_t*)&a_nDestSize);
    if (result==(size_t)-1)
    {
        printf("iconv WCHAR_T->UTF8 error %d/n",errno) ;
        return -1;
    }
    iconv_close(env);
    return (int)result;
#endif
}

// UTF-8 转成 wchar_t
int UTF82Wstr(const std::string & str, std::wstring* wstr) {
#ifdef _WIN32
    int wcs_len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t * wcs = new wchar_t[wcs_len];
    memset(wcs, 0, sizeof(wchar_t) * wcs_len);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wcs, wcs_len);
    *wstr = wcs;
    delete[] wcs;
    wcs = nullptr;
#else
    iconv_t env;
    env = iconv_open("WCHAR_T","UTF-8");
    if (env == (iconv_t) - 1) {
        printf("iconv_open UTF8->WCHAR_T error %d/n", errno) ;
        return -1;
    }

    size_t str_size = str.length();
    size_t wcs_len = (str_size + 1) * sizeof(wchar_t);
    wchar_t * wcs = new wchar_t[wcs_len];
    memset(wcs, 0, sizeof(wchar_t) * wcs_len);

    char* iconv_in = (char*)&str.c_str()[0];
    char* iconv_out = (char*)wcs;

    std::wcout << wcs_len << std::endl;

    size_t result = iconv(env, &iconv_in, &str_size,
                          &iconv_out, &wcs_len);
    if (result == (size_t) - 1) {
        printf("iconv UTF8->WCHAR_T error %d/n",errno) ;
        return -1;
    }

    std::wcout << wcs_len << std::endl;

    *wstr = wcs;
    delete[] wcs;
    wcs = nullptr;

    iconv_close(env);

    return 0;
#endif
}

int main() {
    std::setlocale(LC_ALL, "");
    std::wcout << L"LC_CTYPE: " << std::setlocale(LC_CTYPE, NULL) << std::endl;
    //std::wcout.imbue(std::locale("zh_CN.UTF-8"));

    std::string str = "测试所以这样就可以了吧，。……今天。，！";
    std::wstring wstr;

    UTF82Wstr(str, &wstr);

    std::wcout << wstr << std::endl;
    std::wcout << wstr.length() << std::endl;

    for(size_t i = 0; i < wstr.length(); ++i) {
        std::wcout << L"U+" << std::hex << (long)wstr.at(i) << std::endl;
    }

}
