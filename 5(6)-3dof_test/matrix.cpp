// By xchhe 2018.
#include "matrix.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////
//构造函数，重载构造函数，拷贝构造函数
///////////////////////////////////////////////////////////////////////////////
matrix::matrix(){}

matrix::matrix(int row_size,int col_size)
{
	num_row=row_size;
	num_col=col_size;

	pbody=NULL;

	//allocating memory
	num_elem=row_size*col_size;
	try{pbody=new double[num_elem];}
	catch(bad_alloc xa){cerr<<"*** Error: matrix memory allocation failed ***\n";system("pause");exit(1);}

	//initializing array to zero
	for(int i=0;i<num_elem;i++)
			*(pbody+i)=0;
}

matrix::matrix(const matrix &MAT)
{
//	cout<<" >>> copy constructing >>>\n"; \\diagnostic

	num_row=MAT.num_row;
	num_col=MAT.num_col;
	num_elem=MAT.num_elem;
	try{pbody=new double[num_elem];}
	catch(bad_alloc xa){cerr<<"*** Error: matrix memory allocation failed ***\n";system("pause");exit(1);}

	//copying
	for(int i=0;i<num_elem;i++)
			*(pbody+i)=(*(MAT.pbody+i));
}

///////////////////////////////////////////////////////////////////////////////
//析构函数
///////////////////////////////////////////////////////////////////////////////
matrix::~matrix()
{
	delete [] pbody;
}

///////////////////////////////////////////////////////////////////////////////
//向屏幕输出矩阵内容
///////////////////////////////////////////////////////////////////////////////
void matrix::print()
{
	double *pmem=pbody;

	//先行后列
	for(int i=0;i<num_row;i++){
			for(int j=0;j<num_col;j++){
					cout<<*pbody<<"\t";
					pbody++;
			}
			cout<<'\n';
	}
	//遍历后重置指针位置
	pbody=pmem;
	cout<<"\n\n";
}

///////////////////////////////////////////////////////////////////////////////
//作为矢量时，计算并返回矩阵的行列式
//e.g: avalue = VEC.absolute();
///////////////////////////////////////////////////////////////////////////////
double matrix::absolute()
{
	if(num_row>1&&num_col>1){cerr<<" *** Warning: not a vector 'matrix::absolute()' *** \n";}
	double ret=0.0;

	for(int i=0;i<num_elem;i++)
			ret+=(*(pbody+i))*(*(pbody+i));
	ret=sqrt(ret);

	return ret;
}

///////////////////////////////////////////////////////////////////////////////
//计算并返回伴随矩阵
//e.g: BMAT = AMAT.adjoint();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::adjoint()
{
	if(!(num_row==num_col))
	{cerr<<" *** Error: matrix not square 'matrix::adjoint()' *** \n";system("pause");exit(1);}
	if((num_row==1)&&(num_col==1))
	{cerr<<" *** Error: only one element 'matrix::adjoint()' *** \n";system("pause");exit(1);}

	matrix RESULT(num_row,num_col);

	for(int i=0;i<num_elem;i++){
			//row #
			int row=i/num_col+1;
			//column #
			int col=i%num_col+1;

			if (((row+col)%2)==0)
					*(RESULT.pbody+i)=sub_matrix(row,col).determinant();
			else
					*(RESULT.pbody+i)=(-1.0)*sub_matrix(row,col).determinant();
	}
	return RESULT.trans();
}

//////////////////////////////////////////////////////////////////////////////
//在指定元素位置设置值
//e.g: MAT.assign_loc(r,c,val); ((r+1)th-row, (c+1)th-col)
///////////////////////////////////////////////////////////////////////////////
void matrix::assign_loc(const int &r, const int &c, const double &val)
{
	if(r>num_row-1||c>num_col-1)
	{cerr<<" *** Error: location outside array 'matrix::assign_loc()' *** \n";system("pause");exit(1);}

	//assigning value
	int offset=num_col*(r)+c;
	*(pbody+offset)=val;
}

///////////////////////////////////////////////////////////////////////////////
//创建一个3*1矢量
//e.g: VEC.build_vec3(v1,v2,v3);
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::build_vec3(const double &v1,const double &v2,const double &v3)
{
	num_row=3;
	num_col=1;
	*pbody=v1;
	*(pbody+1)=v2;
	*(pbody+2)=v3;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//创建一个3*3矩阵
//e.g: MAT.build_mat33(v11,v12,v13,v21,v22,v23,v31,v32,v33);
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::build_mat33(const double &v11,const double &v12,const double &v13
                            ,const double &v21,const double &v22,const double &v23
                            ,const double &v31,const double &v32,const double &v33)
{
	num_row=3;
	num_col=3;
	*pbody=v11;    *(pbody+1)=v12;*(pbody+2)=v13;
	*(pbody+3)=v21;*(pbody+4)=v22;*(pbody+5)=v23;
	*(pbody+6)=v31;*(pbody+7)=v32;*(pbody+8)=v33;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//极坐标转到笛卡尔坐标-实现
//|V1|             | cos(elevation)*cos(azimuth)|
//|V2| = magnitude*|cos(elevation)*sin(azimuth) |
//|V3|		   |	  -sin(elevation)       |
//
//e.g: VEC.pol_to_cart(magnitude,azimuth,elevation);
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::pol_to_cart(const double &magnitude,const double &azimuth
                                                   ,const double &elevation)
{
	//this place for your code.

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//返回第col个列矢量
//e.g: VEC = MAT.col_vec(2); (2nd column!)
///////////////////////////////////////////////////////////////////////////////
matrix matrix::get_col_vec(const int &col)
{
	if(col<=0||col>num_col)
	{cerr<<" *** Error: column outside array 'matrix::col_vec()' *** \n";system("pause");exit(1);}

	matrix RESULT(num_row,1);

	for(int i=0;i<num_row;i++){
			int offset=i*num_col+col-1;
			*(RESULT.pbody+i)=(*(pbody+offset));
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//计算并返回行列式,仅计算2维矩阵，使用迭代方法-实现
//e.g: det = MAT.determinant();
///////////////////////////////////////////////////////////////////////////////
double matrix::determinant()
{
	if(!(num_row==num_col))
	{cerr<<" *** Error: matrix not square 'matrix::determinant()' *** \n";system("pause");exit(1);}

	double result=0.0;
   
	if ((num_col==1)&&(num_row==1))//1*1
	{
		//this place for your code.
	}else if ((num_col==2)&&(num_row==2))//2*2
	{	
		//this place for your code.
	}
	else//3*3
	{
		//this place for your code.
	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////
//若为n*1矢量，则创建并返回n*n对角矩阵,对角元素为n*1元素
//Example: DIAMAT=VEC.vec_to_diamat()
///////////////////////////////////////////////////////////////////////////////
matrix matrix::vec_to_diamat()
{
	if(num_col!=1)
	{cerr<<" *** Error: not a vector 'matrix::diagmat_vec()' *** \n";system("pause");exit(1);}

	matrix RESULT(num_row,num_row);
	for(int i=0;i<num_row;i++){
			int offset=i*num_row+i;
			*(RESULT.pbody+offset)=(*(pbody+i));
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//若为n*n矩阵，则创建并返回其对角元素构成的n*1矢量
//Example: VEC=MAT.mat_to_diavec();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::mat_to_diavec()
{
	if(!(num_row==num_col))
	{cerr<<" *** Error: matrix not square 'matrix::diavec_mat()' *** \n";system("pause");exit(1);}

	matrix RESULT(num_row,1);
	for(int i=0;i<num_row;i++){
			int offset=i*num_row+i;
			*(RESULT.pbody+i)=(*(pbody+offset));
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//设置矩阵大小row*col
//e.g: MAT.dimension(3,3);
///////////////////////////////////////////////////////////////////////////////
void matrix::dimension(int row,int col)
{
	num_row=row;
	num_col=col;

	pbody=NULL;

	//allocating memory
	num_elem=row*col;
	try{pbody=new double[num_elem];}
	catch(bad_alloc xa){cerr<<"*** Error: memory allocation failed 'matrix::dimension()' ***\n";system("pause");exit(1);}

	//initializing array to zero
	for(int i=0;i<num_elem;i++)
			*(pbody+i)=0.;
}


///////////////////////////////////////////////////////////////////////////////
//返回矩阵列的个数
//e.g: nc = MAT.get_cols();
///////////////////////////////////////////////////////////////////////////////
int matrix::get_cols()
{
	return num_col;
}

///////////////////////////////////////////////////////////////////////////////
//根据row、col索引，返回其在指针存储区域的索引
//e.g: i = MAT.get_index(2,3); (2nd row, 3rd column)
//////////////////////////////////////////////////////////////////////////////
int matrix::get_index(const int &row, const int &col)
{
	int index;
	index=(row-1)*num_col+col-1;
	return index;
}

///////////////////////////////////////////////////////////////////////////////
//根据r、c的索引，返回矩阵对应位置的元素
//Example: value = MAT.get_loc(2,1); (3rd row, 2nd column)
///////////////////////////////////////////////////////////////////////////////
double matrix::get_loc(const int &r,const int &c)
{
	if((r<num_row)&&(c<num_col))
	return *(pbody+r*num_col+c);
	else
	{cout<<"*** Error: invalid matrix location 'matrix::get_loc()' *** ";system("pause");exit(1);}
}

///////////////////////////////////////////////////////////////////////////////
//返回矩阵行的个数
//Example: nr = MAT.get_rows();
///////////////////////////////////////////////////////////////////////////////
int matrix::get_rows()
{
	return num_row;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the pointer to MAT
//Example: ptr = MAT.get_pbody();
///////////////////////////////////////////////////////////////////////////////
double * matrix::get_pbody()
{
	return pbody;
}

///////////////////////////////////////////////////////////////////////////////
//创建一个单位方阵并返回
//e.g:	MAT.identity();
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::identity()
{
	if (num_row==num_col)
	{
			for(int r=0;r<num_row;r++)
			{
				*(pbody+r*num_row+r)=1.;
			}
	}
	else
	{cout<<"*** Error: matrix not square 'matrix::identiy()'*** ";system("pause");exit(1);}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//返回矩阵求逆结果-实现
//INVERSE =(1/det(A))*Adj(A)
//e.g: INVERSE = AMAT.inverse();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::inverse()
{
	if (num_col!=num_row)
	{cerr<<" *** Error: not a square matrix 'matrix::inverse()' *** \n";system("pause");exit(1);}

	matrix RESULT(num_row,num_col);
	double d=0.;

	d=determinant();
	if (d==0.)
	{cerr<<" *** Error: singular! 'matrix::inverse()' *** \n";system("pause");exit(1);}

	//this place for your code.
	
	return RESULT;
}
///////////////////////////////////////////////////////////////////////////////
//9*1矢量转换为3*3矩阵
//e.g: MAT=VEC.vec91_to_mat33();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::vec91_to_mat33()
{
	if(!(num_row==9 && num_col==1))
	{cerr<<" *** Error: vector not 9 x 1 'matrix::mat33_vec9()' *** \n";system("pause");exit(1);}

	matrix RESULT(3,3);
	for(int i=0;i<9;i++){
			*(RESULT.pbody+i)=*(pbody+i);
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//根据已设置的row、col元素个数，创建全1矩阵并返回
//e.g: MAT.ones();
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::ones()
{
	for(int r=0;r<num_elem;r++)
			*(pbody+r)=1.;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//根据EPS，判断两个矩阵是否不相等,计算每个元素之间的差值
//e.g: if(AMAT!=BMAT){...};
///////////////////////////////////////////////////////////////////////////////
bool matrix::operator!=(const matrix &B)
{
	//check dimensions
	if (num_col!=B.num_col)
	{
		return true;
	}
	else if(num_row!=B.num_row)
	{
		return true;
	}

	for (int i=0;i<num_elem;i++)
	{
		//check to see if values differ by more or less than EPS
		if ((*(pbody+i)-(*(B.pbody+i)))>EPS)
		{
			return true;
		}
		else if ((*(pbody+i)-(*(B.pbody+i)))<(-1.*EPS))
		{
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵*常数
//e.g: CMAT = AMAT * b;
///////////////////////////////////////////////////////////////////////////////
matrix matrix::operator*(const double &b)
{
	matrix RESULT(num_row,num_col);

	for (int i=0;i<num_elem;i++)
			*(RESULT.pbody+i)=*(pbody+i)*b;

	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵*矩阵（矢量操作）
//e.g: CMAT = AMAT * BMAT;
///////////////////////////////////////////////////////////////////////////////
matrix matrix::operator*(const matrix &B)
{
	//create resultant matrix
	matrix RESULT(num_row,B.num_col);
	int r=0; int c=0;

	//check for proper dimensions
	if (num_col!=B.num_row)
	{cout<<"*** Error: incompatible dimensions 'matrix::operator*()' *** ";system("pause");exit(1);}

	for(int i=0;i<RESULT.num_elem;i++){
			r=i/B.num_col;
			c=i%B.num_col;
			for (int k=0; k<num_col;k++){
					*(RESULT.pbody+i)+= *(pbody+k+num_col*r)*(*(B.pbody+k*B.num_col+c));
			}
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵元素*=常数
//e.g: AMAT *= b; meaning: AMAT = AMAT * b
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::operator*=(const double &b)
{
	for (int i=0;i<num_elem;i++)
			*(pbody+i)=*(pbody+i)*b;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵*=矩阵（矢量操作）
//e.g: AMAT *= BMAT; meaning: AMAT = AMAT * BMAT;
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::operator*=(const matrix &B)
{
	//create resultant matrix
	matrix RESULT(num_row,B.num_col);

	//check for proper dimensions
	if (num_col!=B.num_row)
	{cout<<"*** Error: incompatible dimensions 'matrix::operator*=()' *** ";system("pause");exit(1);}

	//check for squareness of B
	if (B.num_col!=B.num_row)
	{cout<<"*** Error: Second matrix is not square 'matrix::operator*=()' *** ";system("pause");exit(1);}

	int i;
	for(i=0;i<RESULT.num_elem;i++){
			int r=i/B.num_col;
			int c=i%B.num_col;
			for (int k=0; k<num_col;k++){
					*(RESULT.pbody+i)+= *(pbody+k+num_col*r)*(*(B.pbody+k*B.num_col+c));
			}
	}
	num_col=RESULT.num_col;
	num_row=RESULT.num_row;
	num_elem=num_row*num_col;
	for (i=0;i<num_elem;i++)
			*(pbody+i)=*(RESULT.pbody+i);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵元素+常数
//e.g: CMAT = AMAT + b;
///////////////////////////////////////////////////////////////////////////////
matrix  matrix::operator+(const double &b)
{
	matrix RESULT(num_row,num_col);

	for (int i=0;i<num_elem;i++)
			*(RESULT.pbody+i)=*(pbody+i)+b;

	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵元素+矩阵元素（必须大小一致）
//e.g: CMAT = AMAT + BMAT;
///////////////////////////////////////////////////////////////////////////////
matrix matrix::operator+(const matrix &B)
{
	matrix RESULT(num_row,num_col);

	if ((num_col!=B.num_col)||(num_row!=B.num_row))
	{cout<<"*** Error: matrices have different dimensions 'matrix::operator +' *** ";system("pause");exit(1);}

	for (int i=0;i<num_elem;i++)
			*(RESULT.pbody+i)=*(pbody+i)+(*(B.pbody+i));

	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵元素+=常数
//e.g: AMAT += b; meaning: AMAT = AMAT + b
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::operator+=(const double &b)
{
	for (int i=0;i<num_elem;i++)
			*(pbody+i)=*(pbody+i)+b;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵元素+=矩阵元素（必须大小一致）
//e.g: AMAT += BMAT; meaning: AMAT = AMAT + BMAT;
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::operator+=(const matrix &B)
{
	if ((num_col!=B.num_col)||(num_row!=B.num_row))
	{cout<<"*** Error: matrices have different dimensions 'matrix::operator +=' *** ";system("pause");exit(1);}

	for (int i=0;i<num_elem;i++)
			*(pbody+i)=*(pbody+i)+(*(B.pbody+i));

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵元素-常数
//e.g: CMAT = AMAT - b;
///////////////////////////////////////////////////////////////////////////////
matrix matrix::operator-(const double &b)
{
	matrix RESULT(num_row,num_col);
	for (int i=0;i<num_elem;i++)
			*(RESULT.pbody+i)=*(pbody+i)-b;

	return RESULT;
}
///////////////////////////////////////////////////////////////////////////////
//矩阵元素-矩阵元素
//e.g: CMAT = AMAT - BMAT;
///////////////////////////////////////////////////////////////////////////////
matrix matrix::operator-(const matrix &B)
{
	matrix RESULT(num_row,num_col);

	if ((num_col!=B.num_col)||(num_row!=B.num_row))
	{cout<<"*** Error: matrices have different dimensions 'matrix::operator -' *** ";system("pause");exit(1);}
	for (int i=0;i<num_elem;i++)
			*(RESULT.pbody+i)=*(pbody+i)-*(B.pbody+i);

	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵元素-=常数
//e.g: AMAT -= b; meaning: AMAT = AMAT - b
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::operator-=(const double &b)
{
	for (int i=0;i<num_elem;i++)
			*(pbody+i)=*(pbody+i)-b;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵元素-=矩阵元素
//e.g: AMAT -= BMAT; meaning: AMAT = AMAT - BMAT;
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::operator-=(const matrix &B)
{
	if ((num_col!=B.num_col)||(num_row!=B.num_row))
	{cout<<"*** Error: matrices have different dimensions 'matrix::operator +=' *** ";system("pause");exit(1);}

	for (int i=0;i<num_elem;i++)
			*(pbody+i)=*(pbody+i)-(*(B.pbody+i));

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//矩阵=矩阵（矩阵赋值,数值操作）
//e.g: AMAT = BMAT;
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::operator=(const matrix &B)
{
	if((num_row != B.num_row)||(num_col != B.num_col))
	{cerr<<" *** Error: incompatible dimensions 'matrix::operator=()' *** \n";system("pause");exit(1);}

	delete [] pbody;
	num_elem=B.num_elem;
	num_row=B.num_row;
	num_col=B.num_col;
	pbody=new double[num_elem];

	for (int i=0;i<num_elem;i++)
			*(pbody+i)=(*(B.pbody+i));

	return *this;
}
///////////////////////////////////////////////////////////////////////////////
//根据EPS，判断两个矩阵是否相等,计算每两个元素之差
//e.g: if(AMAT==BMAT){...};
///////////////////////////////////////////////////////////////////////////////
bool matrix::operator==(const matrix &B)
{
	//check dimensions
	if(num_col!=B.num_col)
	{
		return false;
	}
	else if(num_row!=B.num_row)
	{
		return false;
	}
	for(int i=0;i<num_elem;i++)
	{
		//check to see if values differ by more or less than EPS
		if((*(pbody+i)-(*(B.pbody+i)))>EPS)
		{
			return false;
		}
		else if((*(pbody+i)-(*(B.pbody+i)))<(-1.*EPS))
		{
			return false;
		}
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////
//作为矢量时，返回索引位置的数值
//e.g: comp_i=VEC[i]; VEC[i]=comp_i;
///////////////////////////////////////////////////////////////////////////////
double & matrix::operator[](const int &r)
{
	if((r<num_row)&&(num_col=1))
	{
		return *(pbody+r);
	}
	else
	{
		{cout<<"*** Error: invalid matrix location,'matrix::operator[]' *** ";system("pause");exit(1);}
	}
}
///////////////////////////////////////////////////////////////////////////////
//SUM（矩阵元素*矩阵元素）
//e.g: value = AMAT ^ BMAT;
///////////////////////////////////////////////////////////////////////////////
double matrix::operator^(const matrix &B)
{
	//initialize the result
	double result=0.0;

	//check dimensions
	bool one=false;
	bool dim=false;
	//true if both arrays have dimension '1'
	if((num_row==1||num_col==1)&&(B.num_row==1||B.num_col==1))one=true;
	//true if both arrays have at least one equal dimension
	if((num_row==B.num_row||num_row==B.num_col)&&(num_col==B.num_col||num_col==B.num_row))dim=true;
	if(!one||!dim)
	{cerr<<" *** Error: incompatible dimensions 'matrix::operator^()' *** \n";system("pause");exit(1);}

	for (int i=0;i<num_row;i++)
	{
		result+=*(pbody+i)*(*(B.pbody+i));
	}
	return result;
}
///////////////////////////////////////////////////////////////////////////////
//矩阵转置
//e.g: BMAT = ~AMAT;
///////////////////////////////////////////////////////////////////////////////
matrix matrix::operator~()
{
	matrix RESULT(num_col, num_row);
	int i=0; //offset for original matrix
	int j=0; //offset for transposed matrix

	for (int r=0;r<num_row;r++)
	{
			for(int c=0;c<num_col;c++)
			{
					//offset for transposed
					j=c*num_row+r;
					*(RESULT.pbody+j)=*(pbody+i);
					i++;j++;
			}
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//笛卡尔坐标转换到极坐标-实现
// magnitude = POLAR(0,0) = |V|
// azimuth   = POLAR(1,0) = atan2(V2,V1)
// elevation = POLAR(2,0) = atan2(-V3,sqrt(V1^2+V2^2)
//e.g: POLAR = VEC.cart_to_pol();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::cart_to_pol()
{
	double d=0.0;
	double azimuth=0.0;
	double elevation=0.0;
	double denom;
	matrix POLAR(3,1);

	double v1=(*pbody);
	double v2=(*(pbody+1));
	double v3=(*(pbody+2));

	//this place for your code.

	return POLAR;
}

///////////////////////////////////////////////////////////////////////////////
//返回第row个行向量
//e.g: VEC = MAT.row_vec(2); (2nd row!)
///////////////////////////////////////////////////////////////////////////////
matrix matrix::get_row_vec(const int &row)
{
	if(row<=0||row>num_row)
	{cerr<<" *** Error: row outside array 'matrix::row_vec()' *** \n";system("pause");exit(1);}

	matrix RESULT(1,num_col);

	for(int i=0;i<num_col;i++){
			int offset=(row-1)*num_col+i;
			*(RESULT.pbody+i)=(*(pbody+offset));
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//由3*1矢量构建3*3的反对称矩阵-实现
//			| 0 -c  b|	|a|
//			| c  0 -a| <--	|b|
//			|-b  a  0|	|c|
//
//e.g: MAT = VEC.skew_sym();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::skew_sym()
{
	matrix RESULT(3,3);
	//check for proper dimensions
	if (num_col!=1||num_row!=3)
	{cout<<"*** Error: not a 3x1 column vector 'matrix::skew_sym()' *** ";system("pause");exit(1);}

	//this place for your code.

	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//返回第row、col个元素的余子式-实现
//e.g: BMAT = AMAT.sub_matrix(1,3); (deleting first row and third column!)
///////////////////////////////////////////////////////////////////////////////
matrix matrix::sub_matrix(const int &row, const int &col)
{
	if((row>num_row)||(col>num_col))
	{cerr<<" *** Error: row or column outside array 'matrix::sub_matrix()' *** \n";system("pause");exit(1);}
	if(row==0||col==0)
	{cerr<<" *** Error: row/col are numbered not offset 'matrix::sub_matrix()' *** \n";system("pause");exit(1);}

	//create return matrix
	matrix RESULT(num_row-1,num_col-1);

	//this place for your code.

	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//转置
//e.g: BMAT = AMAT.trans();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::trans()
{
	matrix RESULT(num_col, num_row);
	int i=0; //offset for original matrix
	int j=0; //offset for transposed matrix

	for (int r=0;r<num_row;r++){
			for(int c=0;c<num_col;c++){
					//offset for transposed
					j=c*num_row+r;
					*(RESULT.pbody+j)=*(pbody+i);
					i++;j++;
			}
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//计算并返回3*1矢量的单位矢量
//e.g: UVEC=VEC.univec3();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::univec3()
{
	matrix RESULT(3,1);
	//check for proper dimensions
	if (num_col!=1||num_row!=3)
	{cout<<" *** Error: not a 3x1 column vector in 'matrix::univec()' *** \n";system("pause");exit(1);}

	double v1=(*pbody);
	double v2=(*(pbody+1));
	double v3=(*(pbody+2));
	double d=sqrt(v1*v1+v2*v2+v3*v3);

	//if VEC is zero than the unit vector is also a zero vector
	if(d==0){
			*RESULT.pbody=0;
			*(RESULT.pbody+1)=0;
			*(RESULT.pbody+2)=0;
	}
	else{
			*RESULT.pbody=v1/d;
			*(RESULT.pbody+1)=v2/d;
			*(RESULT.pbody+2)=v3/d;
	}
	return RESULT;
}
///////////////////////////////////////////////////////////////////////////////
//3*3矩阵转换为9*1矢量
//e.g: VEC=MAT.mat33_to_vec91();
///////////////////////////////////////////////////////////////////////////////
matrix matrix::mat33_to_vec91()
{
	if(!(num_row==3 && num_col==3))
	{cerr<<" *** Error: matrix not 3 x 3 'matrix::vec9_mat33()' *** \n";system("pause");exit(1);}

	matrix RESULT(9,1);
	for(int i=0;i<9;i++){
			*(RESULT.pbody+i)=*(pbody+i);
	}
	return RESULT;
}

///////////////////////////////////////////////////////////////////////////////
//根据已创建的大小，设置为0矩阵
//e.g: MAT.zero();
///////////////////////////////////////////////////////////////////////////////
matrix & matrix::zero()
{
	for(int i=0;i<num_elem;i++)
			*(pbody+i)=0.0;

	return *this;
}
