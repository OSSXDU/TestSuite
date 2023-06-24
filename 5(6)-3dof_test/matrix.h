//By xchhe 2018.
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include "constants.h"

//作为矩阵时，保存并处理3*3元素
//作为矢量时，保存并处理1*3、3*1、1*9、9*1元素
class matrix
{
private:
        int num_row;//行数
        int num_col;//列数
        int num_elem;//元素总数
        double *pbody;//指针保存元素数据
public:
        matrix();//构造函数
        matrix(int row_size,int col_size);//构造函数
        matrix(const matrix &MAT);//拷贝构造函数

        ~matrix();//析构函数

        void print();//向屏幕输出矩阵元素

        //e.g: value=VEC.absolute();
        double absolute();//作为矢量时，计算并返回矩阵的行列式

        //e.g: BMAT = AMAT.adjoint();
        matrix adjoint();//计算并返回伴随矩阵

        //e.g: MAT.assign_loc(r,c,val); ((r+1)th-row, (c+1)th-col)
        void assign_loc(const int &r, const int &c, const double &val);//在指定元素位置设置值

        //e.g: VEC.build_vec3(v1,v2,v3)
        matrix & build_vec3(const double &v1,const double &v2,const double &v3);//创建一个3*1矢量

        //e.g: MAT.build_mat33(v11,v12,v13,v21,v22,v23,v31,v32,v33)
        matrix & build_mat33(const double &v11,const double &v12,const double &v13
                            ,const double &v21,const double &v22,const double &v23
                            ,const double &v31,const double &v32,const double &v33);//创建一个3*3矩阵


        //e.g: VEC.pol_to_cart(magnitude,azimuth,elevation);
        matrix &pol_to_cart(const double &magnitude,const double &azimuth,const double &elevation);//极坐标转到笛卡尔坐标 // |V1|             | cos(elevation)*cos(azimuth)|
                                                                                                                        // |V2| = magnitude*|cos(elevation)*sin(azimuth) |
                                                                                                                        // |V3|		    |	  -sin(elevation)        |
        //e.g: VEC = MAT.get_col_vec(2); (第2列!)
        matrix get_col_vec(const int &col);//返回第col个列矢量

        //e.g: det = MAT.determinant();
        double determinant();//计算并返回行列式,仅计算2维矩阵，使用迭代方法

        //e.g: DIAMAT=VEC.vec_to_diamat()
        matrix vec_to_diamat();//若为n*1矢量，则创建并返回n*n对角矩阵,对角元素为n*1元素

        //e.g: VEC=MAT.mat_to_diavec();
        matrix mat_to_diavec();//若为n*n矩阵，则创建并返回其对角元素构成的n*1矢量

        //e.g: MAT.dimension(3,3);
        void dimension(int row,int col);//设置矩阵大小row*col

        //e.g: nc = MAT.get_cols();
        int get_cols();//返回矩阵列的个数

        //e.g: i = MAT.get_index(2,3); (2nd row, 3rd coloumn)
        int get_index(const int &row,const int &col);//根据row、col索引，返回其在指针存储区域的索引

        //e.g: value = MAT.get_loc(2,1); (3rd row, 2nd column)
        double get_loc(const int &r,const int &c);//根据r、c的索引，返回矩阵对应位置的元素

        //e.g: ptr = MAT.get_pbody();
        double* get_pbody();//返回矩阵数据指针

        //e.g: nr = MAT.get_rows();
        int get_rows();//返回矩阵行的个数

        //e.g: I = MAT.identity();
        matrix& identity();//创建一个单位方阵并返回

        //e.g: INVERSE = AMAT.inverse();
        matrix inverse();//返回矩阵求逆结果 INVERSE =(1/det(A))*Adj(A)

        //e.g: MAT=VEC.vec91_to_mat33();
        matrix vec91_to_mat33();//9*1矢量转换为3*3矩阵

        //e.g: MAT.ones();
        matrix & ones();//根据已设置的row、col元素个数，创建全1矩阵并返回

        //e.g: if(AMAT!=BMAT){...};
        bool operator!=(const matrix &B);//根据EPS，判断两个矩阵是否不相等,计算每个元素之间的差值

        //e.g: CMAT = AMAT * b;
        matrix operator*(const double &b);//矩阵*常数

        //e.g: CMAT = AMAT * BMAT;
        matrix operator*(const matrix &B);//矩阵*矩阵（矢量操作）

        //e.g: AMAT *= b; meaning: AMAT = AMAT * b
        matrix & operator*=(const double &b);//矩阵元素*=常数

        //e.g: AMAT *= BMAT; meaning: AMAT = AMAT * BMAT;
        matrix & operator*=(const matrix &B);//矩阵*=矩阵（矢量操作）

        //e.g: CMAT = AMAT + b;
        matrix operator+(const double &b);//矩阵元素+常数

        //e.g: CMAT = AMAT + BMAT;
        matrix operator+(const matrix &B);//矩阵元素+矩阵元素（必须大小一致）

        //e.g: AMAT += b; meaning: AMAT = AMAT + b
        matrix & operator+=(const double &b);//矩阵元素+=常数

        //e.g: AMAT += BMAT; meaning: AMAT = AMAT + BMAT;
        matrix & operator+=(const matrix &B);//矩阵元素+=矩阵元素（必须大小一致）

        //e.g: CMAT = AMAT - b;
        matrix operator-(const double &b);//矩阵元素-常数

        //e.g: CMAT = AMAT - BMAT;
        matrix operator-(const matrix &B);//矩阵元素-矩阵元素（必须大小一致）

        //e.g: AMAT -= b; meaning: AMAT = AMAT - b
        matrix & operator-=(const double &b);//矩阵元素-=常数

        //e.g: AMAT -= BMAT; meaning: AMAT = AMAT - BMAT;
        matrix & operator-=(const matrix &B);//矩阵元素-=矩阵元素（必须大小一致）

        //e.g: AMAT = BMAT;
        matrix &operator=(const matrix &B);//矩阵=矩阵（矩阵赋值,数值操作）

        //e.g: if(AMAT==BMAT){...};
        bool operator==(const matrix &B);//根据EPS，判断两个矩阵是否相等,计算每两个元素之差

        //e.g: comp_i=VEC[i]; VEC[i]=comp_i;
        double & operator [](const int &r);//作为矢量时，返回索引位置的数值

        //e.g: value = AMAT ^ BMAT;
        double operator^(const matrix &B);//SUM（矩阵元素*矩阵元素）

        //e.g: BMAT = ~AMAT;
        matrix operator~();//矩阵转置

        //e.g: POLAR = VEC.cart_to_pol();
        matrix cart_to_pol();//笛卡尔坐标转换到极坐标           // magnitude = POLAR(0,0) = |V|
                                                            // azimuth   = POLAR(1,0) = atan2(V2,V1)
                                                            // elevation = POLAR(2,0) = atan2(-V3,sqrt(V1^2+V2^2)

        //e.g: VEC = MAT.get_row_vec(2); (第2行!)
        matrix get_row_vec(const int &row);//返回第row个行向量

        //e.g: MAT = VEC.skew_sym();
        matrix skew_sym();//由3*1矢量构建3*3的反对称矩阵         //      | 0 -c  b|	     |a|
                                                             //      | c  0 -a| <--  |b|
                                                             //      |-b  a  0|	     |c|

        //e.g: BMAT = AMAT.sub_matrix(1,3);
        matrix sub_matrix(const int &row, const int &col);//返回第row、col个元素的余子式

        //e.g: BMAT = AMAT.trans();
        matrix trans();//转置

        //e.g: UVEC=VEC.univec3();
        matrix univec3();//计算并返回3*1矢量的单位矢量

        //e.g: VEC=MAT.mat33_to_vec91();
        matrix mat33_to_vec91();//3*3矩阵转换为9*1矢量

        //e.g: MAT.zero();
        matrix &zero();//根据已创建的大小，设置为0矩阵
};

















#endif // MATRIX_H
