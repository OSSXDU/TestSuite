//by xchhe 2019
#ifndef STR_PROC_H
#define STR_PROC_H
#include <string>
#include <cstddef>

//取消字符串前后特殊符号' \a\b\f\n\r\t\v'
std::string trim(const std::string& s);

//取消字符串后的注释内容"\\"
std::string trim_note(const std::string &s);

//获得等号左右两边字符串"L=R",返回参数为字符串"L",右侧无内容则为""
std::string trim_context(const std::string &s, std::string &rs);




#endif
