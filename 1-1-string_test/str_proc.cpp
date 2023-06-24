//by xchhe 2019
#include "str_proc.h"

/////////////////////////////////////////
//取消字符串前后特殊符号' \a\b\f\n\r\t\v'
/////////////////////////////////////////
std::string trim(const std::string& s)
{
  if(s.length() == 0)
  {
      return s;
  }
  std::size_t beg = s.find_first_not_of(" \a\b\f\n\r\t\v");
  std::size_t end = s.find_last_not_of(" \a\b\f\n\r\t\v");
  if(beg == std::string::npos) // No non-spaces
  {
      return "";
  }
  return std::string(s, beg, end - beg + 1);
}




/////////////////////////////////////////
//取消字符串后的注释内容"\\"
/////////////////////////////////////////
std::string trim_note(const std::string &s)
{
    if(s.length() == 0)
    {
        return s;
    }

    std::size_t end = s.find_first_of("//");

    if(end == std::string::npos) // No non-spaces
    {
        return trim(s);
    }

    return trim(std::string(s, 0, end-1));
}




/////////////////////////////////////////
//获得等号左右两边字符串"L=R",返回参数为字符串"L",右侧无内容则为""
/////////////////////////////////////////
std::string trim_context(const std::string &s, std::string &rs)
{
    if(s.length() == 0)
    {
        return s;
    }

    std::string tem_s = trim_note(s);

    std::size_t end = tem_s.find_first_of("=");

    if(end == std::string::npos) // No non-spaces
    {
        rs = "";
        return tem_s;
    }

    rs = trim(std::string(tem_s, end+1, tem_s.length()));
    return trim(std::string(tem_s, 0, end-1));
}
