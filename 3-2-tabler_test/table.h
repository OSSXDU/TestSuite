//By xchhe 2018
#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include "constants.h"

//存储查找表数据-简称表格
class table
{
private:

    int dims;        //表格维数
    int	axes1_size;	// 表格第1坐标轴数据个数
    int	axes2_size;	// 表格第2坐标轴数据个数
    int	axes3_size;	// 表格第3坐标轴数据个数

    double *axes1_values;  //表格第1坐标轴数据
    double *axes2_values;  //表格第2坐标轴数据
    double *axes3_values;  //表格第3坐标轴数据
    double *data; // 表格多维数据（维度取决于dims定义），存放在1维数组中。

    table(table &tbl) {};
public:
    std::string name;	//表格名称

    table();
    ~table(); //析构函数

    static int count;
    
    std::string get_name();//获得表格名称
    void set_name(const std::string tbl_name);//设置表格名称

    int get_dims();//获得表格维数
	int get_axes1_size();//获得表格第1坐标轴数据个数
    int get_axes2_size();//获得表格第2坐标轴数据个数
    int get_axes3_size();//获得表格第3坐标轴数据个数

    double *get_axes1_values();//获得表格第1坐标轴数组
    double *get_axes2_values();//获得表格第2坐标轴数组
    double *get_axes3_values();//获得表格第3坐标轴数组
    double *get_data();//获得表格函数数组   

    void set_table_size(int size1, int size2=1, int size3=1);//初始化table，分配内存    

    void set_axes1_value(int index, double val);//设置第1坐标轴对应索引元素值
    void set_axes2_value(int index, double val);//设置第2坐标轴对应索引元素值
    void set_axes3_value(int index, double val);//设置第3坐标轴对应索引元素值
    void set_data(int index, double val);//按照多维索引(多维转换为1维索引排列)设置表格对应元素值

    void print(std::ofstream &fout);//向屏幕输出
};

#endif // TABLE_H
