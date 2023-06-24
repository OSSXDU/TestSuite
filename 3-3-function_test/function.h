//By xchhe 2018.
#ifndef FUNCTION_H
#define FUNCTION_H

#include "matrix.h"


///////////////////////////////////////////////////////////////////////////////
//////////////////////////参考系坐标转换矩阵工具///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//由航迹角thtvg、航向角psivg得到TVG转换矩阵
matrix get_tvg_mat(const double &psivg,const double &thtvg);

//由偏航角psi，俯仰角tht，滚转角phi得到TBG转换矩阵
matrix get_tbg_mat(const double &psi,const double &tht,const double &phi);

//由经度lon，纬度lat计算计算TGE转换矩阵
matrix get_tge_mat(double lon,double lat);

//由仿真时间与地球自转角速度计算TEI转换矩阵
matrix get_tei_mat(double simulation_time);

//由SBIE矢量计算LLA矢量（即SBIG矢量）
matrix get_lla_mat(matrix SBIE);

//由空气动力气流角alpha和空气动力滚转角phi计算TBV转换矩阵（3自由度适用）
matrix get_tbv_mat(double phi,double alpha);

//由地理坐标计算地球惯性系坐标,TIG=TIE*TEG
matrix get_tig_mat(double lon,double lat,double alt,double time);

//获得符号
//e.g: value_signed=value*get_sign(variable)
int get_sign(const double &variable);

//获得矢量夹角
//e.g: theta=angle(VEC1,VEC2);
double get_angle_from_mats(matrix VEC1,matrix VEC2);


///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////积分函数/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//中值法积分
//e.g 一阶拉格朗日方法:	phid_new=(phic-phi)/tphi;
//			phi=integrate(phid_new,phid,phi,int_step);
//			phid=phid_new;
///////////////////////////////////////////////////////////////////////////////
double integrate(const double &dydx_new,const double &dydx,const double &y,const double &int_step);

//矩阵积分MAT(r,c)
Matrix integrate(Matrix &DYDX_NEW,Matrix &DYDX,Matrix &Y,const double int_step);

#endif // FUNCTION_H
