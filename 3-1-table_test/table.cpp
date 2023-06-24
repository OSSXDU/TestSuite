//By xchhe 2018
#include "table.h"
#include <fstream>
#include <sstream>
#include "config_proc.h"

using namespace std;
 
int table::count = 0;

/////////////////////////////////////////
//构造函数
/////////////////////////////////////////
table::table()
{	
    name = "";
    dims = 1;
    axes1_size = 1;
    axes2_size = 1;
    data = NULL;
    axes1_values = NULL;
    axes2_values = NULL;

    count++;
    cout<<"tabler: "<<count<<endl;
}
 


/////////////////////////////////////////
//析构函数	
/////////////////////////////////////////
table::~table() 
{
    delete []axes1_values;
    delete []axes2_values;
	delete []data;
}



/////////////////////////////////////////
//获得表格名称
/////////////////////////////////////////
string table::get_name() { return name; }



/////////////////////////////////////////
//获得表格维度
/////////////////////////////////////////
int table::get_dims() { return dims; }



/////////////////////////////////////////
//获得表格第1坐标轴数据
/////////////////////////////////////////
int table::get_axes1_size() { return axes1_size; }



/////////////////////////////////////////
//获得表格第2坐标轴数据
/////////////////////////////////////////
int table::get_axes2_size() { return axes2_size; }



/////////////////////////////////////////
//获得表格第1坐标轴数组
/////////////////////////////////////////
double* table::get_axes1_values() { return axes1_values; }



/////////////////////////////////////////
//获得表格第2坐标轴数组
/////////////////////////////////////////
double* table::get_axes2_values() { return axes2_values; }



/////////////////////////////////////////
//获得表格函数数组
/////////////////////////////////////////
double* table::get_data() { return data; }



/////////////////////////////////////////
//设置表格名称
/////////////////////////////////////////
void table::set_name(const string tbl_name)
{
    name = tbl_name;
}



/////////////////////////////////////////
//初始化table，分配内存
/////////////////////////////////////////
void table::set_table_size(int size1, int size2)
{
    axes1_size = size1;
    axes2_size = size2;

    if(axes2_size>1) {  dims++; }

    int data_size = axes1_size * axes2_size;

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

    if(data == NULL)
    {
        data = new double[data_size];
    }else
    {
        cerr<<"renew for data_values in table::set_table_size()"<<endl;
        exit(0);
    }
}



/////////////////////////////////////////
//设置第1坐标轴对应索引元素值
/////////////////////////////////////////
void table::set_axes1_value(int index, double val)
{
    axes1_values[index] = val;
}



/////////////////////////////////////////
//设置第2坐标轴对应索引元素值
/////////////////////////////////////////
void table::set_axes2_value(int index, double val)
{
    axes2_values[index] = val;
}



/////////////////////////////////////////
//按照多维索引(多维转换为1维索引排列)设置表格对应元素值
/////////////////////////////////////////
void table::set_data(int index, double val)
{
    data[index] = val;
}



/////////////////////////////////////////
//输出
/////////////////////////////////////////
void table::print(ofstream &fout)
{
    fout<<"table_name: "<<get_name()<<"   dims:"<<get_dims()<<endl;
    fout<<endl;

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

    fout<<"data: ";

    for(int j=0; j<axes1_size * axes2_size; j++)
    {
        if(j % axes1_size == 0) {
            fout<<endl;
        }
        fout<<(double)data[j]<<"    ";
    }
    fout<<endl;
    fout<<endl;
    fout<<endl;

}



/////////////////////////////////////////
//输入"1 13"，输出"1","13"
//输入"2 9 13"，输出"9","13"
/////////////////////////////////////////
bool table::parse_size(const std::string &s, std::string &dims, std::string &row, std::string &col)
{
    if(s.length() == 0)
    {
        return false;
    }

    std::string tem_s = trim_note(s);

    std::size_t end = tem_s.find_first_of(" ");

    if(end == std::string::npos) // No non-spaces
    {
        return false;
    }

    dims = trim(std::string(tem_s, 0, end));

    tem_s = tem_s.substr(end+1);
    end = tem_s.find_first_of(" ");
    row = trim(std::string(tem_s, 0, end));

    if(!dims.compare("1"))
    {
        col = "0";
    }else if(!dims.compare("2"))
    {
        col = trim(std::string(tem_s, end+1, tem_s.length()));
    }else
    {
        return false;
    }

    return true;
}



/////////////////////////////////////////
//输入"cd0_vs_mach"，输出"mach","cd0"
/////////////////////////////////////////
bool table::parse_name(std::string &col, std::string &data)
{
    int count=0;
    std::size_t end;
    std::string tem_s = trim(name);
    while((end=tem_s.find_first_of("_")) != std::string::npos)
    {
        tem_s = tem_s.substr(end+1);
        count++;
    }
    if(2 != count)
    {
        return false;
    }


    tem_s = trim(name);
    end = tem_s.find_first_of("_");
    data = std::string(tem_s, 0, end);
    tem_s = tem_s.substr(end+1);
    end = tem_s.find_first_of("_");
    col = tem_s.substr(end+1);
    return true;
}



/////////////////////////////////////////
//输入"ca_vs_alpha_mach"，输出"alpha","mach","ca"
/////////////////////////////////////////
bool table::parse_name(std::string &row, std::string &col, std::string &data)
{
    int count=0;
    std::size_t end;
    std::string tem_s = trim(name);
    while((end=tem_s.find_first_of("_")) != std::string::npos)
    {
        tem_s = tem_s.substr(end+1);
        count++;
    }
    if(3 != count)
    {
        return false;
    }

    tem_s = trim(name);
    end = tem_s.find_first_of("_");
    data = std::string(tem_s, 0, end);
    tem_s = tem_s.substr(end+1);
    end = tem_s.find_first_of("_");
    tem_s = tem_s.substr(end+1);
    end = tem_s.find_first_of("_");
    row = std::string(tem_s, 0, end);
    col = tem_s.substr(end+1);

    return true;
}




/////////////////////////////////////////
//解析数据并存储到数组中
/////////////////////////////////////////
bool table::parse_data(const std::string &s, double array[], const int len)
{
    int count=0;
    std::string tem_s = trim(s);
    std::string word;
    std::size_t end;

    while((end=tem_s.find_first_of(" ")) != std::string::npos)
    {
        tem_s = trim(tem_s.substr(end+1));
        count++;
    }
    if(tem_s.length()>0)
    {
        count++;
    }
    if(count != len)
    {
        return false;
    }

    tem_s = trim(s);
    count=0;
    while((end=tem_s.find_first_of(" ")) != std::string::npos)
    {
        word = trim(string(tem_s, 0, end));
        tem_s = trim(tem_s.substr(end+1));
        array[count] = atof(word.c_str());
        count++;
    }
    if(tem_s.length()>0)
    {
        word = trim(tem_s);
        array[count] = atof(word.c_str());
    }

    return true;
}




/////////////////////////////////////////
//从字符串设置第1坐标轴对应索引元素值
/////////////////////////////////////////
bool table::read_axes1_value(const std::string s_data, const int len)
{
    double data_array[len];
    if(!parse_data(s_data, data_array, len))
    {
        return false;
    }

    for(int i=0; i<len; i++)
    {
        set_axes1_value(i, data_array[i]);
    }

    return true;
}



/////////////////////////////////////////
//从字符串设置第2坐标轴对应索引元素值
/////////////////////////////////////////
bool table::read_axes2_value(const std::string s_data, const int len)
{
    double data_array[len];
    if(!parse_data(s_data, data_array, len))
    {
        return false;
    }

    for(int i=0; i<len; i++)
    {
        set_axes2_value(i, data_array[i]);
    }

    return true;
}



/////////////////////////////////////////
//从字符串设置表格对应索引元素值
/////////////////////////////////////////
bool table::read_data_value(const std::string s_data, const int len)
{    
    double data_array[len];

    if(!parse_data(s_data, data_array, len))
    {
        return false;
    }

    for(int i=0; i<len; i++)
    {
        set_data(i, data_array[i]);
    }

    return true;
}



/////////////////////////////////////////
//从配置文件读取指定模块的参数数据
/////////////////////////////////////////
bool table::read_config_data(std::ifstream &fin, int mod_num)
{
    //ifstream fin("ghame3_prop_deck.txt");
    string t_name, t_size, t_dims, t_col, t_row;
    int dims, col, row;

    t_name = get_text_from_mod(fin, "name", mod_num);
    //cout<<"name:"<<t_name<<endl;
    set_name(t_name);

    t_size = get_text_from_mod(fin, "size", mod_num);
    if(parse_size(t_size, t_dims, t_row, t_col))
    {
        //cout<<"size:"<<t_size<<"    dims:"<<t_dims<<"   row:"<<t_row<<"   col:"<<t_col<<endl;
    }
    dims = atoi(t_dims.c_str());
    row = atoi(t_row.c_str());
    col = atoi(t_col.c_str());

    string row_name, col_name, data_name;
    string row_data, col_data, data_data;
    if(1 == dims)
    {
        parse_name(row_name, data_name);
        set_table_size(row);
        row_data    = get_text_from_mod(fin, row_name, mod_num);
        read_axes1_value(row_data, row);
        data_data   = get_text_from_mod(fin, data_name, mod_num);
        //cout<<data_data<<endl;
        if(!read_data_value(data_data, row))
        {
            return false;
        }
    }else if(2 == dims)
    {
        parse_name(row_name, col_name, data_name);
        set_table_size(row, col);
        row_data    = get_text_from_mod(fin, row_name, mod_num);
        read_axes1_value(row_data, row);
        col_data    = get_text_from_mod(fin, col_name, mod_num);
        if(!read_axes2_value(col_data, col))
        {
            return false;
        }

        stringstream strs;
        string tem_dn, tem_data, tem_data_all;
        for(int i=1;i<=row;i++)
        {
            strs.clear();
            strs<<data_name<<"_"<<i<<endl;
            strs>>tem_dn;
            tem_data = get_text_from_mod(fin, tem_dn, mod_num);
            tem_data_all += " " + tem_data;
            //cout<<tem_data<<endl;
        }
        if(!read_data_value(tem_data_all, row*col))
        {
            return false;
        }

    }else
    {
        return false;
    }

    return true;
}

