//By xchhe 2018
#ifndef TABLER_H
#define TABLER_H

#include <iostream>
#include "table.h"

//保存table表格，对其进行查找
class tabler
{
private:
    std::string title; //数据卡名称
    int capacity; //保存table表格最大数量
    int tbl_counter; //指向当前table的索引序号
    table **table_ptr; //保存table指针的数组

public:
    tabler();//构造函数
    ~tabler();//析构函数

    void alloc_mem();//创建table指针数组

    void set_title(std::string tabler_title);//设置数据卡名称

    std::string get_title();//获得数据卡名称

    void set_capacity(int table_numbers);//设置保存table表格的容量

    int get_capacity();//获得保存table表格的容量

    void set_index(int count);//设置指向table的索引序号

    int get_index();//获得当前指向table的索引序号}

    table* operator[](int index);//使用操作符[]索引，返回索引序号指向的table

    table* get_tbl(int index);//返回索引序号指向的table

    void read_tables(std::string file_name);//从参数文件AERO_DECK和PROP_DECK读取table数据，存入tabler中的table[]结构中。

    double look_up(std::string name,double value1);//根据单变量查表，name对应表名称
    double look_up(std::string name,double value1,double value2);//根据双变量查表，name对应表名称    

    int find_index(int max,double value,double *list);//在table保存的数据表中，查找变量值最近的索引号（查找方法可以修改，这里为二分法查找）

    double interpolate(int ind,int ind2,int index,double val);  //线性一维插值
                                                                //轴坐标数据 x[ind1],x[ind2],x=val
                                                                //映射数据  y=(y[ind2]-y[ind1])*(x-x[ind1])/(x[ind2]-x[ind1])

    double interpolate(int ind10,int ind11,int ind20,int ind21,
                       int index,double value1,double value2);    //线性二维插值
};

#endif // TABLER_H
