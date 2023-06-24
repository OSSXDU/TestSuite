//by xchhe 2019
#include "config_proc.h"
#include <iostream>
#include <string>
#include <sstream>

enum {SIM_TITLE=0, SIM_TITLE_END, MODULES, MODULES_END, ENUMS};

//配置文件格式标记
static std::string config_defs[ENUMS] =
{
    "SIM_TITLE",
    "SIM_TITLE_END",
    "MODULES",
    "MODULES_END"
};



using namespace std;


/////////////////////////////////////////
//获得仿真配置文件中某个仿真模块内容
/////////////////////////////////////////
void get_config_context(std::ifstream &fin, const std::string str_start, const std::string str_end, std::vector<std::string> &mlist)
{
    string str_line;
    int char_num = 0;
    int start_pos = 0;
    int end_pos = 0;

    fin.clear();
    fin.seekg(0);

    while(!fin.eof())
    {
        getline(fin, str_line);
        char_num += str_line.length() + 2;//2='\r\n'

        if(!trim(str_line).compare(str_start))
        {
            start_pos = char_num;
        }

        if(!trim(str_line).compare(str_end))
        {
            end_pos = char_num;
        }

        while(end_pos > start_pos)
        {
            fin.clear();
            fin.seekg(start_pos, ios::beg);

            getline(fin, str_line);
            start_pos += str_line.length() + 2;//2='\r\n'
            str_line = trim_note(str_line);

            if(end_pos <= start_pos)
            {
                return;
            }

            if(!str_line.empty())
            {
                mlist.push_back(str_line);
            }
        }
    }
}



/////////////////////////////////////////
//获得仿真配置文件中仿真名称
/////////////////////////////////////////
std::string get_sim_title(std::ifstream &fin)
{
    vector<string> title_list;
    get_config_context(fin, config_defs[SIM_TITLE], config_defs[SIM_TITLE_END], title_list);

    return title_list[0];
}



/////////////////////////////////////////
//获得仿真配置文件中模块列表
//0=MODULES,1=MODULES_1,2=MODULES_2...
/////////////////////////////////////////
void get_modules(std::ifstream &fin, std::vector<std::string> &mod_list, int order)
{
    if(order<0)
    {
        cout<<"funciont get_modules wrong order:"<<order<<endl;
        exit(0);
    }

    if(0 == order)
    {
        get_config_context(fin, config_defs[MODULES], config_defs[MODULES_END], mod_list);
    }else
    {
        stringstream sstr;
        string str_start,str_end;
        sstr<<config_defs[MODULES]<<"_"<<order;
        sstr>>str_start;
        sstr<<config_defs[MODULES_END]<<"_"<<order;
        sstr>>str_end;

        get_config_context(fin, str_start, str_end, mod_list);
    }
}




/////////////////////////////////////////
//获得仿真配置文件中某个模块中的某个字符串
//0=MODULES,1=MODULES_1,2=MODULES_2...
/////////////////////////////////////////
std::string get_text_from_mod(std::ifstream &fin, const std::string &inp, int order)
{
    if(order<0)
    {
        cout<<"funciont get_text_from_mod() wrong order:"<<order<<endl;
        exit(0);
    }

    vector<string> mod_list;

    if(0 == order)
    {
        get_config_context(fin, config_defs[MODULES], config_defs[MODULES_END], mod_list);
    }
    else
    {
        stringstream sstr;
        string str_start,str_end;
        sstr<<config_defs[MODULES]<<"_"<<order;
        sstr>>str_start;
        sstr.clear();
        sstr<<config_defs[MODULES_END]<<"_"<<order;
        sstr>>str_end;

        get_config_context(fin, str_start, str_end, mod_list);
    }

    string rs,ls;
    for(int i=0; i<mod_list.size();i++)
    {
        ls = trim_context(mod_list[i],rs);
        if(!inp.compare(ls))
        {
            return rs;
        }
    }

    cout<<"funciont get_text_from_mod() wrong order or inp:"<<order<<" "<<inp<<endl;
    exit(0);
}



/////////////////////////////////////////
//获得仿真配置文件中某个模块中的某个数据
//0=MODULES,1=MODULES_1,2=MODULES_2...
/////////////////////////////////////////
float get_data_from_mod(std::ifstream &fin, const std::string &inp, int order)
{
    if(order<0)
    {
        cout<<"funciont get_text_from_mod() wrong order:"<<order<<endl;
        exit(0);
    }

    vector<string> mod_list;

    if(0 == order)
    {
        get_config_context(fin, config_defs[MODULES], config_defs[MODULES_END], mod_list);
    }
    else
    {
        stringstream sstr;
        string str_start,str_end;
        sstr<<config_defs[MODULES]<<"_"<<order;
        sstr>>str_start;
        sstr.clear();
        sstr<<config_defs[MODULES_END]<<"_"<<order;
        sstr>>str_end;

        get_config_context(fin, str_start, str_end, mod_list);
    }


    string rs,ls;
    for(int i=0; i<mod_list.size();i++)
    {
        ls = trim_context(mod_list[i],rs);
        if(!inp.compare(ls))
        {
            return atof(rs.c_str());
        }
    }

    cout<<"funciont get_text_from_mod() wrong order or inp:"<<order<<" "<<inp<<endl;
    exit(0);
}









