#include "module.h"

using namespace std;

bool mod_read(std::ifstream &fin, std::string &inp, module &mod)
{
    std::string tem_s,word;
    std::size_t end;
    tem_s = get_text_from_mod(fin, inp);

    mod.name = inp;

    while((end = tem_s.find_first_of(",")) != std::string::npos)
    {
        word = trim(std::string(tem_s, 0, end));
        if(!word.compare("def"))
        {
            mod.def = word;
        }else if(!word.compare("init"))
        {
            mod.init = word;
        }else if(!word.compare("exec"))
        {
            mod.exe = word;
        }else if(!word.compare("exit"))
        {
            mod.exit = word;
        }else
        {
            return false;
        }
        tem_s = tem_s.substr(end+1);
    }
    if(tem_s.length()>0)
    {
        word = trim(std::string(tem_s, 0, end));
        if(!word.compare("def"))
        {
            mod.def = word;
        }else if(!word.compare("init"))
        {
            mod.init = word;
        }else if(!word.compare("exec"))
        {
            mod.exe = word;
        }else if(!word.compare("exit"))
        {
            mod.exit = word;
        }else
        {
            return false;
        }
    }
    return true;
}
