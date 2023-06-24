//By xchhe 2018
#include "table.h"
#include <fstream>

using namespace std;
 
int table::count = 0;
//构造函数
table::table()
{	
    name = "";
    dims = 1;
    axes1_size = 1;
    axes2_size = 1;
    axes3_size = 1;
    data = NULL;
    axes1_values = NULL;
    axes2_values = NULL;
    axes3_values = NULL;

    count++;
    cout<<"tabler: "<<count<<endl;
}
 

//析构函数	
table::~table() 
{
    delete []axes1_values;
    delete []axes2_values;
    delete []axes3_values;
	delete []data;
}


//获得表格名称
string table::get_name() { return name; }

//获得表格维度
int table::get_dims() { return dims; }

//获得表格第1坐标轴数据
int table::get_axes1_size() { return axes1_size; }

//获得表格第2坐标轴数据
int table::get_axes2_size() { return axes2_size; }

//获得表格第3坐标轴数据
int table::get_axes3_size() { return axes3_size; }

//获得表格第1坐标轴数组
double* table::get_axes1_values() { return axes1_values; }

//获得表格第2坐标轴数组
double* table::get_axes2_values() { return axes2_values; }

//获得表格第3坐标轴数组
double* table::get_axes3_values() { return axes3_values; }

//获得表格函数数组
double* table::get_data() { return data; }

//设置表格名称
void table::set_name(const string tbl_name)
{
    name = tbl_name;
}

//初始化table，分配内存
void table::set_table_size(int size1, int size2, int size3)
{
    axes1_size = size1;
    axes2_size = size2;
    axes3_size = size3;

    if(axes2_size>1) {  dims++; }
    if(axes3_size>1) {  dims++; }

    int data_size = axes1_size * axes2_size * axes3_size;

    if(axes1_values == NULL)
    {
        axes1_values = new double[axes1_size];
    }else
    {
        cerr<<"renew for axes1_values in table::set_table_size()"<<endl;
        exit(0);
    }

    if(axes2_values == NULL)
    {
        axes2_values = new double[axes2_size];
    }else
    {
        cerr<<"renew for axes2_values in table::set_table_size()"<<endl;
        exit(0);
    }

    if(axes3_values == NULL)
    {
        axes3_values = new double[axes3_size];
    }else
    {
        cerr<<"renew for axes3_values in table::set_table_size()"<<endl;
        exit(0);
    }

    if(data == NULL)
    {
        data = new double[data_size];
    }else
    {
        cerr<<"renew for data_values in table::set_table_size()"<<endl;
        exit(0);
    }
}

//设置第1坐标轴对应索引元素值
void table::set_axes1_value(int index, double val)
{
    axes1_values[index] = val;
}

//设置第2坐标轴对应索引元素值
void table::set_axes2_value(int index, double val)
{
    axes2_values[index] = val;
}

//设置第3坐标轴对应索引元素值
void table::set_axes3_value(int index, double val)
{
    axes3_values[index] = val;
}

//按照多维索引(多维转换为1维索引排列)设置表格对应元素值
void table::set_data(int index, double val)
{
    data[index] = val;
}

//输出
void table::print(ofstream &fout)
{
    fout<<"table name: "<<get_name()<<"   dims:"<<get_dims()<<endl;

    if(axes1_size>1)
    {
        fout<<"axes1_data: ";
        for(int j=0; j<axes1_size; j++)
        {
            fout<<(double)axes1_values[j]<<"    ";
        }
    }
    fout<<endl;

    if(axes2_size>1)
    {
        fout<<"axes2_data: ";
        for(int j=0; j<axes2_size; j++)
        {
            fout<<(double)axes2_values[j]<<"    ";
        }
    }
    fout<<endl;

    if(axes3_size>1)
    {
        fout<<"axes3_data: ";
        for(int j=0; j<axes3_size; j++)
        {
            fout<<(double)axes3_values[j]<<"    ";
        }
    }
    fout<<endl;

    fout<<"data: ";

    for(int j=0; j<axes1_size * axes2_size * axes3_size; j++)
    {
        if(j % axes1_size == 0) {
            fout<<endl;
        }
        fout<<(double)data[j]<<"    ";
    }

}




