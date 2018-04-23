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
/*
int Wstr2UTF8(const wchar_t* c_str, int a_nSrcSize, char* a_szDest, int a_nDestSize)
bool Wstr2UTF8(const std::wstring & wstr, std::string * str) {
#ifdef _WIN32
    size_t wstr_len = wstr.length();
    int str_len = (wstr_len + 1) * 2;
    int ret = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1,
                                  a_szDest, a_nDestSize, NULL, NULL);
    return ret != 0;
#else
    iconv_t env;
    env = iconv_open("UTF-8","WCHAR_T");
    if (env==(iconv_t)-1)
    {
        printf("iconv_open WCHAR_T->UTF8 error%s %d/n",strerror(errno),errno) ;
        return -1;
    }
    size_t result = iconv(env,(char**)&c_str,(size_t*)&a_nSrcSize,(char**)&a_szDest,(size_t*)&a_nDestSize);
    if (result==(size_t)-1)
    {
        printf("iconv WCHAR_T->UTF8 error %d/n",errno) ;
        return -1;
    }
    iconv_close(env);
    return (int)result;
#endif
}
*/

// UTF-8 转成 wchar_t
bool UTF82Wstr(const std::string & str, std::wstring* wstr) {
#ifdef _WIN32
    int wcs_len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t * wcs = new wchar_t[wcs_len];
    memset(wcs, 0, sizeof(wchar_t) * wcs_len);
    int ret = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wcs, wcs_len);
    if(ret == 0) {
        delete[] wcs;
        return false;
    }
    *wstr = wcs;
    delete[] wcs;
    wcs = nullptr;

    return true;
#else
    iconv_t env;
    env = iconv_open("WCHAR_T","UTF-8");
    if (env == (iconv_t) - 1) {
        printf("iconv_open UTF8->WCHAR_T error %d/n", errno) ;
        return false;
    }

    size_t str_size = str.length();
    wchar_t * wcs = new wchar_t[str_size + 1];
    size_t wcs_bytes = (str_size + 1) * sizeof(wchar_t);
    memset(wcs, 0, wcs_bytes);

    char* iconv_in = (char*)&str.c_str()[0];
    char* iconv_out = (char*)wcs;
    size_t str_bytes = str_size * sizeof(char);

    std::wcout << wcs_bytes << std::endl;

    size_t result = iconv(env, &iconv_in, &str_bytes,
                          &iconv_out, &wcs_bytes);
    if (result == (size_t) - 1) {
        printf("iconv UTF8->WCHAR_T error %d/n",errno) ;
        return false;
    }

    std::wcout << wcs_bytes << std::endl;

    *wstr = wcs;
    delete[] wcs;
    wcs = nullptr;

    iconv_close(env);

    return true;
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
