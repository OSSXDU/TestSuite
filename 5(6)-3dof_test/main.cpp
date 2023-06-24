//by xchhe 2018
#include <fstream>
#include <iostream>
#include <vector>
#include "ghame3.h"
#include "config_proc.h"
#include "module.h"



//仿真执行
void execute(const std::string title, \
             const std::string &print, \
             double sim_time, \
             const double end_time, \
             const int num_mods, \
             const int num_devs, \
             const double int_step, \
             vector<platform*> &dev_list, \
             const module *mod_list, \
             std::ofstream &fout, \
             const double print_step);


using namespace std;

int main(int argc, char *argv[])
{
    double sim_time = 0;//仿真起始时间

    std::ifstream fin("ghame3_input.txt");//打开"input.txt"仿真配置文件
    std::ofstream fout;//输出文件，记录、分析数据使用

    string title;//仿真名称
    title = get_sim_title(fin);//获得仿真名称

    int mod_nums;//使用模块数量
    mod_nums = get_data_from_mod(fin, "mod_nums");

    //获得仿真模块列表
    string str;
    module *module_list;
    module_list = new module[mod_nums];
    str = "environment";
    mod_read(fin, str, module_list[0]);
    str = "aerodynamics";
    mod_read(fin, str, module_list[1]);
    str = "propulsion";
    mod_read(fin, str, module_list[2]);
    str = "forces";
    mod_read(fin, str, module_list[3]);
    str = "newton";
    mod_read(fin, str, module_list[4]);

    //获得仿真步长,仿真结束时间，存储标记
    string record_flag;//仿真记录
    double int_step;//仿真时间步长
    double end_time;//仿真结束时间
    double print_step;//存储步长
    int_step = get_data_from_mod(fin, "int_step", 1);
    end_time = get_data_from_mod(fin, "end_time", 1);
    print_step = get_data_from_mod(fin, "print_step", 1);
    record_flag = get_text_from_mod(fin, "print", 1);

    ghame3 *dev3;
    dev3 = new ghame3(module_list, mod_nums);//创建仿真设备对象
    std::string dev_name;//仿真对象名称

    //获得设备对象名称
    str = "dev_name";
    dev_name = get_text_from_mod(fin, str, 2);

    //模块定义
    for (int i=0;i<mod_nums;i++)
    {
        if((module_list[i].name=="environment")&&(module_list[i].def=="def")) { dev3->def_environment(); }
        else if((module_list[i].name=="propulsion")&&(module_list[i].def=="def")) { dev3->def_propulsion(); }
        else if((module_list[i].name=="aerodynamics")&&(module_list[i].def=="def")) { dev3->def_aerodynamics(); }
        else if((module_list[i].name=="forces")&&(module_list[i].def=="def")) { dev3->def_forces(); }
        else if((module_list[i].name=="newton")&&(module_list[i].def=="def")) { dev3->def_newton(); }
    }

    //设备对象从"input.txt"文件中读取对应参数
    dev3->read_params(fin);

    //模块初始化
    for(int i=0; i<mod_nums; i++)
    {
        if((module_list[i].name=="environment")&&(module_list[i].init=="init")) { dev3->init_environment(sim_time); }
        else if((module_list[i].name=="propulsion")&&(module_list[i].init=="init")) { dev3->init_propulsion(); }
        else if((module_list[i].name=="aerodynamics")&&(module_list[i].init=="init")) { dev3->init_aerodynamics(); }
        else if((module_list[i].name=="forces")&&(module_list[i].init=="init")) { dev3->init_forces(); }
        else if((module_list[i].name=="newton")&&(module_list[i].init=="init")) { dev3->init_newton();; }
    }


    //输出文件
    if(!record_flag.compare("ON"))
    {
        fout.open("ghame3_output.txt");

        //表格绘制行label
        dev3->plot_label(fout, title);
    }

    int dev_nums = 1;
    vector<platform*> devs;
    devs.push_back(dev3);

    //test for read_params();
    devs[0]->print(cout);

    execute(title, record_flag, sim_time, end_time, mod_nums, dev_nums, int_step, devs, module_list, fout, print_step);


    //关闭文件
    fin.close();
    if(!record_flag.compare("ON"))
    {
        fout.close();
    }


    delete []module_list;
    devs.clear();

    getchar();
    return 0;
}











//仿真执行
void execute(const std::string title, \
             const std::string &print, \
             double sim_time, \
             const double end_time, \
             const int num_mods, \
             const int num_devs, \
             const double int_step, \
             vector<platform*> &dev_list, \
             const module *mod_list, \
             std::ofstream &fout, \
             const double print_step)
{
    int dev_index = 0;
    double print_time = 0;
    bool increment_print_time = false;

    while (sim_time<=(end_time+int_step))
    {
        for (int i=0;i<num_devs;i++)
        {
            dev_index = i;

            //按照顺序执行模块组件
            for(int j=0;j<num_mods;j++)
            {
                if(mod_list[j].name=="environment")
                {
                    dev_list[j]->environment(sim_time);
                }
                else if(mod_list[j].name=="control")
                {
                    //dev_list[i]->control(int_step);
                }
                else if(mod_list[j].name=="propulsion")
                {
                    dev_list[i]->propulsion(int_step);
                }
                else if(mod_list[j].name=="aerodynamics")
                {
                    dev_list[i]->aerodynamics(int_step);
                }
                else if(mod_list[j].name=="forces")
                {
                    dev_list[i]->forces(int_step);
                }
                else if(mod_list[j].name=="newton")
                {
                    dev_list[i]->newton(int_step);
                }
                else if(mod_list[j].name=="guidance")
                {
                    //dev_list[i]->guidance(combus,num_devs,sim_time);
                }
                else if(mod_list[j].name=="seeker")
                {
                    //dev_list[i]->seeker(combus,num_devs,sim_time,int_step);
                }
                else if(mod_list[j].name=="intercept")
                {
                    //dev_list[i]->intercept(combus,dev_slot,int_step,title);
                }
            } //end of module loop

            //保留活动的设备
            //暂无
            //更新通讯数据
            //暂无
            //更新设备活动状态
            //暂无
            //设置通讯数据当前仿真时间
            //暂无


            //输出绘制数据fout
            if(fabs(print_time-sim_time)<(int_step/2+EPS))
            {
                if(!print.compare("ON"))
                {
                    dev_list[i]->plot_data(fout);
                    if(i==(num_devs-1))
                    {
                        increment_print_time=true;
                    }
                }
                if(increment_print_time) print_time+=print_step;
            }
        }//end of num_devs loop

        //仿真时间
        sim_time += int_step;

    }//仿真积分

    //最后一次仿真数据输出到fout
    if(!print.compare("ON"))
    {
        for (int i=0;i<num_devs;i++)
            dev_list[i]->plot_data(fout);
    }
}

