//by xchhe 2019
#ifndef CONFIG_PROC_H
#define CONFIG_PROC_H

#include <string>
#include <fstream>
#include <vector>
#include "str_proc.h"


//获得仿真配置文件中某个仿真模块内容
void get_config_context(std::ifstream &fin, const std::string str_start, const std::string str_end, std::vector<std::string> &mlist);

//获得仿真配置文件中模块列表
//0=MODULES,1=MODULES_1,2=MODULES_2...
void get_modules(std::ifstream &fin, std::vector<std::string> &mod_list, int order=0);

//获得仿真配置文件中某个模块中的某个字符串
//0=MODULES,1=MODULES_1,2=MODULES_2...
std::string get_text_from_mod(std::ifstream &fin, const std::string &inp, int order=0);

//获得仿真配置文件中某个模块中的某个数据
//0=MODULES,1=MODULES_1,2=MODULES_2...
float get_data_from_mod(std::ifstream &fin, const std::string &inp, int order=0);

//获得仿真配置文件中仿真名称
std::string get_sim_title(std::ifstream &fin);

#endif // CONFIG_PROC_H
