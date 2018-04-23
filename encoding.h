#include <cstring>
#include <cstdio>
#include <iostream>
#include <cerrno>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#else
#include <iconv.h>
#endif

// wchar_t 转成 UTF-8
bool Wstr2UTF8(const std::wstring & wstr, std::string * str) {
#ifdef _WIN32
    int out_str_bytes = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1,
                                      NULL, 0, NULL, NULL);
    size_t out_str_len = out_str_bytes / sizeof(char);
    if(out_str_len * sizeof(char) < out_str_bytes) {
        ++out_str_len;
    }
    char * out_str = new char[out_str_len];
    out_str_bytes = (int)out_str_len * sizeof(char);
    memset(out_str, 0, out_str_bytes);
    int ret = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1,
                                  out_str, out_str_bytes, NULL, NULL);
    if (ret == 0) {
        delete[] out_str;
        out_str = NULL;
        return false;
    }
    *str = out_str;
    delete[] out_str;
    out_str = NULL;
    return true;
#else
    iconv_t env;
    env = iconv_open("UTF-8", "WCHAR_T");
    if (env == (iconv_t)-1) {
        return -1;
    }


    size_t wstr_len = wstr.length();
    size_t c_str_len = wstr_len * sizeof(wchar_t) + 1;
    char * c_str = new char[c_str_len];
    size_t c_str_bytes = c_str_len * sizeof(char);
    memset(c_str, 0, c_str_bytes);

    char * iconv_in = (char *)&wstr.c_str()[0];
    char * iconv_out = (char *)c_str;
    size_t wstr_bytes = wstr_len * sizeof(wchar_t);

    std::cout << wstr_bytes << std::endl;
    std::cout << c_str_bytes << std::endl;
    size_t result = iconv(env, (char**)&iconv_in, (size_t*)&wstr_bytes,
                          (char**)&iconv_out, (size_t*)&c_str_bytes);
    if (result == (size_t)-1) {
        perror("iconv");
        delete[] c_str;
        c_str = nullptr;
        return false;
    }
    *str = c_str;
    delete[] c_str;
    c_str = nullptr;
    iconv_close(env);

    return true;
#endif
}

// UTF-8 转成 wchar_t
bool UTF82Wstr(const std::string & str, std::wstring* wstr) {
#ifdef _WIN32
    size_t out_wstr_len = MultiByteToWideChar(CP_ACP, 0, str.c_str(),
                                             -1, NULL, 0);
	//return false;
    wchar_t * out_wstr = new wchar_t[out_wstr_len];
    int out_wstr_size = (int)out_wstr_len * sizeof(wchar_t);
    memset(out_wstr, 0, out_wstr_size);
	std::wcout << out_wstr_size << std::endl;
	std::wcout << out_wstr_len << std::endl;
    int ret = MultiByteToWideChar(CP_ACP, 0, str.c_str(),
                                  -1, out_wstr, out_wstr_size);
    if (ret == 0) {
        delete[] out_wstr;
        out_wstr = NULL;
        return false;
    }
    *wstr = out_wstr;
    delete[] out_wstr;
    out_wstr = NULL;

    return true;
#else
    iconv_t env;
    env = iconv_open("WCHAR_T","UTF-8");
    if (env == (iconv_t) - 1) {
        return false;
    }

    size_t str_len = str.length();
    size_t wc_str_len = str_len + 1;
    wchar_t * wc_str = new wchar_t[wc_str_len];
    size_t wc_str_bytes = wc_str_len * sizeof(wchar_t);
    memset(wc_str, 0, wc_str_bytes);

    char* iconv_in = (char*)&str.c_str()[0];
    char* iconv_out = (char*)wc_str;
    size_t str_bytes = str_len * sizeof(char);

    std::wcout << wc_str_bytes << std::endl;

    size_t result = iconv(env, &iconv_in, &str_bytes,
                          &iconv_out, &wc_str_bytes);
    if (result == (size_t) - 1) {
        perror("iconv");
        delete[] wc_str;
        wc_str = nullptr;
        return false;
    }

    std::wcout << wc_str_bytes << std::endl;

    *wstr = wc_str;
    delete[] wc_str;
    wc_str = nullptr;

    iconv_close(env);

    return true;
#endif
}
