//by xchhe 2018
#ifndef GNAME3_H
#define GHAME3_H

#include "platform.h"
#include "tabler.h"
#include "module.h"

using namespace std;

class ghame3 : public platform
{
protected:
    packet com_packet;//通讯组件

    tabler aero_tabler;//气动表存储与管理组件
    tabler prop_tabler;//推力表存储与管理组件
public:
    ghame3(module *mod_list,int num_mod);//构造函数，初始化参数
    ~ghame3();

    virtual void set_name(std::string na);
    virtual std::string get_name();

    //功能函数接口
    virtual bool update_data(const std::string &s, const float &fval);//更新数据
    virtual void print(std::ostream &out);//输出所有变量，测试使用
    virtual void read_params(std::ifstream &fin);//从input.asc文件中读取设备对应参数
    virtual void plot_label(std::ofstream &fout, std::string title);//向plot文件输出plot_label
    virtual void plot_data(std::ofstream &fout);//向plot文件输出plot_data

    virtual packet* loading_packet_init();//设备之间通讯使用
    virtual packet* loading_packet();//设备之间通讯使用

    //模块函数接口
    virtual void def_environment();//环境参数定义
    virtual void init_environment(double sim_time);//环境参数初始化
    virtual void environment(double sim_time);//环境参数计算

    virtual void def_newton();//牛顿定律参数定义
    virtual void init_newton();//牛顿定律参数初始化
    virtual void newton(double int_step);//牛顿定律计算

    virtual void def_aerodynamics();//气动参数定义
    virtual void init_aerodynamics();//气动参数初始化
    virtual void aerodynamics(double int_step);//气动参数计算

    virtual void def_propulsion();//推力参数定义
    virtual void init_propulsion();//推力参初始化
    virtual void propulsion(double int_step);//推力参数计算

    virtual void def_forces();//合力参数定义
    virtual void init_forces();//合力参数初始化
    virtual void forces(double int_step);//合力参数计算

    virtual void def_control();//控制参数定义
    virtual void init_control();//控制参数初始化
    virtual void control(double int_step);//控制参数计算

    virtual void def_guidance();//制导参数定义
    virtual void init_guidance();//制导参数初始化
    virtual void guidance(packet *combus,int num_vehicles,double int_step);//制导参数计算

    virtual void def_seeker();//导引参数定义
    virtual void init_seeker();//导引参数初始化
    virtual void seeker(packet *combus,int num_vehicles,double sim_time,double int_step);//导引参数计算

    virtual void def_intercept();//传感器参数定义
    virtual void init_intercept();//传感器参数初始化
    virtual void intercept(packet *combus,int vehicle_slot,double int_step,std::string title);//传感器参数计算
};

#endif // GHAME3_H
