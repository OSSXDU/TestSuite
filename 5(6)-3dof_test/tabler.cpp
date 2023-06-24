//By xchhe 2018
#include <fstream>
#include <string.h>
#include "tabler.h"
#include "config_proc.h"

using namespace std;



tabler::tabler()//构造函数
{
}

tabler::~tabler()//析构函数
{
    delete []table_ptr;
}

///////////////////////////////////////////////////////////////////////////////
//创建table指针数组
///////////////////////////////////////////////////////////////////////////////
void tabler::alloc_mem()
{
    table_ptr=new table* [capacity];

    for(int i=0; i<capacity; i++)
    {
        table_ptr[i] = new table();
    }
}

///////////////////////////////////////////////////////////////////////////////
//设置数据卡名称
///////////////////////////////////////////////////////////////////////////////
void tabler::set_title(std::string tabler_title)
{
    title=tabler_title;
}

///////////////////////////////////////////////////////////////////////////////
//获得数据卡名称
///////////////////////////////////////////////////////////////////////////////
string tabler::get_title()
{
    return title;
}

///////////////////////////////////////////////////////////////////////////////
//设置保存table表格的容量
///////////////////////////////////////////////////////////////////////////////
void tabler::set_capacity(int table_numbers)
{
    capacity=table_numbers;
}

///////////////////////////////////////////////////////////////////////////////
//获得保存table表格的容量
///////////////////////////////////////////////////////////////////////////////
int tabler::get_capacity()
{
    return capacity;
}

///////////////////////////////////////////////////////////////////////////////
//设置指向table的索引序号
///////////////////////////////////////////////////////////////////////////////
void tabler::set_index(int count)
{
    tbl_counter=count;
}

///////////////////////////////////////////////////////////////////////////////
//获得当前指向table的索引序号
///////////////////////////////////////////////////////////////////////////////
int tabler::get_index()
{
    return tbl_counter;
}


///////////////////////////////////////////////////////////////////////////////
//使用操作符[]索引，返回索引序号指向的table
///////////////////////////////////////////////////////////////////////////////
table* tabler::operator[](int index)
{
    if(index>=0 && index<capacity)
    {
        return table_ptr[index];
    }
    else
    {
        cout<<"*** Bad pointer value of tabler: "<<index<<'\n';
        return 0;
    }
}
///////////////////////////////////////////////////////////////////////////////
//返回索引序号指向的table
///////////////////////////////////////////////////////////////////////////////
table* tabler::get_tbl(int index)
{
    if(index>=0 && index<capacity)
    {
        return table_ptr[index];
    }
    else
    {
        cout<<"*** Bad pointer value of tabler: "<<index<<'\n';
        return 0;
    }
}



///////////////////////////////////////////////////////////////////////////////
//根据单变量查表，name对应表名称
///////////////////////////////////////////////////////////////////////////////
double tabler::look_up(string name,double value1)
{
    //从table_ptr指针数组中，根据表格名称，查找索引号。
    int index = -1;
    std::string tbl_name;
    do{
        index++;
        tbl_name=get_tbl(index)->get_name();
    }while(name!=tbl_name);

    //从表中离散值找到离value1最近的最小值，注意越界处理
    int aexs1_size=get_tbl(index)->get_axes1_size();
    int loc1=find_index(aexs1_size-1,value1,get_tbl(index)->get_axes1_values());

    //溢出越界处理
    if (loc1==(aexs1_size-1)) return get_tbl(index)->get_data()[loc1];

    //插值
    return interpolate(loc1,loc1+1,index,value1);
}

///////////////////////////////////////////////////////////////////////////////
//根据双变量查表，name对应表名称
///////////////////////////////////////////////////////////////////////////////
double tabler::look_up(string name,double value1,double value2)
{
    //从table_ptr指针数组中，根据表格名称，查找索引号。
    int index = -1;
    string tbl_name;
    do{
        index++;
        tbl_name=get_tbl(index)->get_name();
    }while(name!=tbl_name);


    //从表中离散值找到离value1和value2最近的最小值，注意越界处理
    int aexs1_size=get_tbl(index)->get_axes1_size();
    int loc1=find_index(aexs1_size-1,value1,get_tbl(index)->get_axes1_values());

    int aexs2_size=get_tbl(index)->get_axes2_size();
    int loc2=find_index(aexs2_size-1,value2,get_tbl(index)->get_axes2_values());

    //插值
    return interpolate(loc1,loc1+1,loc2,loc2+1,index,value1,value2);
}


///////////////////////////////////////////////////////////////////////////////
//在table保存的数据表中，查找变量值最近的索引号（查找方法可以修改，这里为二分法查找）
///////////////////////////////////////////////////////////////////////////////
int tabler::find_index(int max,double value,double *list)
{
	//code here.
}

///////////////////////////////////////////////////////////////////////////////
//线性一维插值
//轴坐标数据 x[ind1],x[ind2],x=val
//映射数据  y=(y[ind2]-y[ind1])*(x-x[ind1])/(x[ind2]-x[ind1])
///////////////////////////////////////////////////////////////////////////////
double tabler::interpolate(int ind1,int ind2,int index,double val)
{
    double dx,dy;
    double dumx;

    double diff=val - get_tbl(index)->get_axes1_values()[ind1];
    dx=get_tbl(index)->get_axes1_values()[ind2] - get_tbl(index)->get_axes1_values()[ind1];
    dy=get_tbl(index)->get_data()[ind2] - get_tbl(index)->get_data()[ind1];

    if(dx>EPS)
    {
        dumx=diff/dx;
    }
    dy=dumx*dy;

    return get_tbl(index)->get_data()[ind1]+dy;
}
///////////////////////////////////////////////////////////////////////////////
//线性二维插值
///////////////////////////////////////////////////////////////////////////////
double tabler::interpolate(int ind10,int ind11,int ind20,int ind21,int index,double value1,
                                        double value2)
{
	double RESULT;
	
	//code here.
	
	return RESULT;
}




///////////////////////////////////////////////////////////////////////////////
//从参数文件AERO_DECK和PROP_DECK读取table数据，存入tabler中的table[]结构中。
///////////////////////////////////////////////////////////////////////////////
void tabler::read_tables(string file_name)
{    
    table *ptable;    
    int table_count = 0;//文件中表的总数

    //打开参数文件
    ifstream tbl_stream(file_name);

    if(tbl_stream.fail())
    {
        cerr<<"*** Error: File stream '"<<file_name<<"' failed to open (check spelling) ***\n";
        system("pause");
        exit(1);
    }

    //根据参数，初始化tabler
    set_title(get_sim_title(tbl_stream));
    table_count = int(get_data_from_mod(tbl_stream, "mod_nums"));
    set_capacity(table_count);
    alloc_mem();


    //读入所有表格数据，存入对应表格中
    for(int i=0; i<table_count; i++)
    {
        ptable = get_tbl(i);
        ptable->read_config_data(tbl_stream, i+1);
    }

    tbl_stream.close();
}
