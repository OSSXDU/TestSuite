//by xchhe 2018
#ifndef PLATFORM_H
#define PLATFORM_H

#include <fstream>
#include "packet.h"
#include <map>

//基类，作为接口使用。
class platform
{
protected:
    std::string name;
    std::map<std::string, variable> vars_map;
public:    
    ~platform() {};

    virtual void set_name(std::string na)=0;
    virtual std::string get_name()=0;

    //功能函数接口
    virtual bool update_data(const std::string &s, const float &fval)=0;//更新数据
    virtual void print(std::ostream &out)=0;//输出所有变量，测试使用
    virtual void read_params(std::ifstream &fin)=0;//从input.asc文件中读取设备对应参数
    virtual void plot_label(std::ofstream &fout, std::string title)=0;//向plot文件输出plot_label
    virtual void plot_data(std::ofstream &fout)=0;//向plot文件输出plot_data

    virtual packet* loading_packet_init()=0;//设备之间通讯使用
    virtual packet* loading_packet()=0;//设备之间通讯使用

    //模块函数接口
    virtual void def_environment()=0;//环境参数定义
    virtual void init_environment(double sim_time)=0;//环境参数初始化
    virtual void environment(double sim_time)=0;//环境参数计算

    virtual void def_newton()=0;//牛顿定律参数定义
    virtual void init_newton()=0;//牛顿定律参数初始化
    virtual void newton(double int_step)=0;//牛顿定律计算

    virtual void def_aerodynamics()=0;//气动参数定义
    virtual void init_aerodynamics()=0;//气动参数初始化
    virtual void aerodynamics(double int_step)=0;//气动参数计算

    virtual void def_propulsion()=0;//推力参数定义
    virtual void init_propulsion()=0;//推力参初始化
    virtual void propulsion(double int_step)=0;//推力参数计算

    virtual void def_forces()=0;//合力参数定义
    virtual void init_forces()=0;//合力参数初始化
    virtual void forces(double int_step)=0;//合力参数计算

    virtual void def_control()=0;//控制参数定义
    virtual void init_control()=0;//控制参数初始化
    virtual void control(double int_step)=0;//控制参数计算

    virtual void def_guidance()=0;//制导参数定义
    virtual void init_guidance()=0;//制导参数初始化
    virtual void guidance(packet *combus,int num_vehicles,double int_step)=0;//制导参数计算

    virtual void def_seeker()=0;//导引参数定义
    virtual void init_seeker()=0;//导引参数初始化
    virtual void seeker(packet *combus,int num_vehicles,double sim_time,double int_step)=0;//导引参数计算

    virtual void def_intercept()=0;//传感器参数定义
    virtual void init_intercept()=0;//传感器参数初始化
    virtual void intercept(packet *combus,int vehicle_slot,double int_step,std::string title)=0;//传感器参数计算
};

#endif // PLATFORM_H
