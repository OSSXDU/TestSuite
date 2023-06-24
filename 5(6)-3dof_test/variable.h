//by xchhe 2018
#ifndef VARIABLE_H
#define VARIABLE_H

#include "matrix.h"

class variable
{
public:
    std::string name; //变量组件名称
    std::string type; //变量组件类型，如："int";"real",默认为real type
    double rval;	  //
    int ival;         //    
    matrix VEC;		  //3x1 vector for 3dof simulation
    matrix MAT;		  //3x3 matrix for 3dof simulation
    matrix VEC5;	  //5x1 vector for 5dof simulation
    matrix MAT5;	  //5x5 matrix for 5dof simulation
    std::string def;  //变量组件物理定义
    std::string mod;  //变量组件在仿真模块中的使用范围
    std::string role; //变量组件在仿真中的性质
    std::string out;  //变量组件输出定义: 如"plot"点迹, "com"通讯    

public:
    variable();
    ~variable();

    //初始化重载函数
    void init(std::string na,double rv,std::string de,std::string mo,std::string ro,std::string ou);
    void init(std::string na,std::string ty,int iv,std::string de,std::string mo,std::string ro,std::string ou);
    void init(std::string na,double v1,double v2,double v3,std::string de,std::string mo,std::string ro,std::string ou);
    void init(std::string na,double v11,double v12,double v13,double v21,double v22,double v23,
                       double v31,double v32,double v33,std::string de,std::string mo,std::string ro,std::string ou);
    void init(std::string na,double v1,double v2,double v3,double v4,double v5,
                       std::string de,std::string mo,std::string ro,std::string ou);
    void init(std::string na,
                       double v11,double v12,double v13,double v14,double v15,
                       double v21,double v22,double v23,double v24,double v25,
                       double v31,double v32,double v33,double v34,double v35,
                       double v41,double v42,double v43,double v44,double v45,
                       double v51,double v52,double v53,double v54,double v55,
                       std::string de,std::string mo,std::string ro,std::string ou);

};


#endif // VARIABLE_H
