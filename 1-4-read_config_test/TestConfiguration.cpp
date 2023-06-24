#include "TestConfiguration.h"
#include "str_proc.h"
#include "config_proc.h"
#include <regex>
#include <iostream>
using namespace std;
void TestConfiguration::readConfiguration()
{
    std::ifstream fin("E:/codebase/cpp/code/1-4-read_config_test/read_config_test_for_student/ghame3_input.txt");
    if (!fin)
    {
        std::cout << "can't open the input file" << std::endl;
    }

    // 读取仿真名称
    std::string simTitle = get_sim_title(fin);
    std::cout << "仿真名称： " << simTitle << std::endl;
    paramValues.simTitle = simTitle;
    // 读取模块列表
    std::vector<std::string> modList;
    get_modules(fin, modList);
    std::cout << "模块列表：" << std::endl;
    
    // 提取键值对的值
    int configNums = 0;
    int modNums = 0;
    std::string environment;
    std::string aerodynamics;
    std::string propulsion;
    std::string forces;
    std::string newton;
    std::regex keyValRegex(R"(\s*([^=]+)\s*=\s*(.+)\s*)");
    std::regex commaRegex(R"(\s*,\s*)");

    std::cout << "模块列表：" << std::endl;
    for (const auto& mod : modList) {
        std::smatch matches;//存放结果
        if(std::regex_match(mod, matches, keyValRegex)) {
            std::string key = matches[1];
            std::string val = matches[2];
            
            //去除空格
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
            val.erase(std::remove_if(val.begin(), val.end(), ::isspace), val.end());

            std::cout << key << ": " << val << std::endl;
              // 根据键提取值
            if (key == "config_nums") {
                configNums = std::stoi(val);
            } else if (key == "mod_nums") {
                modNums = stoi(val);
            } else if (key == "environment") {
                environment = val;
            } else if (key == "aerodynamics") {
                aerodynamics = val;
            } else if (key == "propulsion") {
                propulsion = val;
            } else if (key == "forces") {
                forces = val;
            } else if (key == "newton") {
                newton = val;
            }
        }
        // std::cout << mod <<std::endl;
    }
    //写入类的成员变量
    paramValues.configNums = configNums;
    paramValues.modNums = modNums;
    paramValues.environment = environment;
    paramValues.aerodynamics = aerodynamics;
    paramValues.propulsion = propulsion;
    paramValues.forces = forces;
    paramValues.newton = newton;
    

    // 读取模块1中的数据
    std::string print = get_text_from_mod(fin, "print", 1);
    float printStep = get_data_from_mod(fin, "print_step", 1);
    float intStep = get_data_from_mod(fin, "int_step", 1);
    float endTime = get_data_from_mod(fin, "end_time", 1);

    //写入类的成员变量
    paramValues.print = print;
    paramValues.printStep = printStep;
    paramValues.int_step= intStep;
    paramValues.endTime = endTime;
    

    // 打印模块1中的数据
    std::cout << "模块1数据：" << std::endl;
    std::cout << "print: " << print << std::endl;
    std::cout << "print_step: " << printStep << std::endl;
    std::cout << "int_step: " << intStep << std::endl;
    std::cout << "end_time: " << endTime << std::endl;

    // 读取模块2中的数据
    std::string dev_name = get_text_from_mod(fin, "dev_name", 2);
    std::string lonx = get_text_from_mod(fin, "lonx", 2);
    std::string latx = get_text_from_mod(fin, "latx", 2);
    std::string alt = get_text_from_mod(fin, "alt", 2);
    std::string psivgx = get_text_from_mod(fin, "psivgx", 2);
    std::string thtvgx = get_text_from_mod(fin, "thtvgx", 2);
    std::string dvbe = get_text_from_mod(fin, "dvbe", 2);
    std::string alphax = get_text_from_mod(fin, "alphax", 2);
    std::string phimvx = get_text_from_mod(fin, "phimvx", 2);
    std::string aero_deck = get_text_from_mod(fin, "aero_deck", 2);
    std::string area = get_text_from_mod(fin, "area", 2);
    std::string prop_deck = get_text_from_mod(fin, "prop_deck", 2);
    std::string mprop = get_text_from_mod(fin, "mprop", 2);
    std::string mass0 = get_text_from_mod(fin, "mass0", 2);
    std::string fmass0 = get_text_from_mod(fin, "fmass0", 2);
    std::string acowl = get_text_from_mod(fin, "acowl", 2);
    std::string throttle = get_text_from_mod(fin, "throttle", 2);
    std::string thrtl_idle = get_text_from_mod(fin, "thrtl_idle", 2);
    std::string thrtl_max = get_text_from_mod(fin, "thrtl_max", 2);

    //写入类的成员变量
    paramValues.dev_name = dev_name;
    paramValues.lonx = std::stod(lonx);
    paramValues.latx = std::stod(latx);
    paramValues.alt = std::stod(alt);
    paramValues.psivgx = std::stod(psivgx);
    paramValues.thtvgx = std::stod(thtvgx);
    paramValues.dvbe = std::stod(dvbe);
    paramValues.alphax = std::stod(alphax);
    paramValues.phimvx = std::stod(phimvx);
    paramValues.aero_deck = aero_deck;
    paramValues.area = std::stod(area);
    paramValues.prop_deck = prop_deck;
    paramValues.mprop = std::stod(mprop);
    paramValues.mass0 = std::stod(mass0);
    paramValues.fmass0 = std::stod(fmass0);
    paramValues.acowl = std::stod(acowl);
    paramValues.throttle = std::stod(throttle);
    paramValues.thrtl_idle = std::stod(thrtl_idle);
    paramValues.thrtl_max = std::stod(thrtl_max);
    // 关闭配置文件
    fin.close();
}

void TestConfiguration::writeConfiguration()
{
     // 将测试结果存入文件
    std::ofstream fout("test_result.txt");
    if (!fout)
    {
        std::cout << "无法打开结果文件。" << std::endl;
        return;
    }
    //写入标题
    fout << "ConfigurationTest Result:" << std::endl;
    long passNum = getNumPassed();
    long failNum = getNumFailed();
    fout<<"passNum: "<<passNum<<std::endl;
    fout<<"failNum: "<<failNum<<std::endl;
    // 关闭结果文件
    fout.close();

    std::cout << "测试结果已存入文件 test_result.txt。" << std::endl;

}