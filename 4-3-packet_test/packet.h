//by xchhe 2018
#ifndef PACKET_H
#define PACKET_H

#include "variable.h"
#include <map>

//设备间通讯数据结构
class packet
{
private:
    std::string id;		//设备ID
    int status;			//设备状态, 正常=1, 摧毁=0. 击中=-1.
    std::map<std::string,variable> data_map;		//数组存放变量组件
public:
    packet();//构造函数
    ~packet();//析构函数

    void set_id(std::string identification);//set id

    void set_status(int vehicle_status);//set status

    void set_data(std::string id, double rval);//set data with id
    void set_data(variable &var);//set data

    std::string get_id();//get id

    int get_status();//get status

    int get_data_size();//get num of data

    std::map<std::string,variable>* get_data();//get *data
};

#endif // PACKET_H
