//by xchhe  2018
#include "variable.h"
#include <string>

using namespace std;

variable::variable()
{
    name = "";
    rval = 0;
    ival = 0;
    def = "";
    mod = "";
    role = "";
    out = "";

    VEC.dimension(3,1);
    MAT.dimension(3,3);
    VEC5.dimension(5,1);
    MAT5.dimension(5,5);
}

variable::~variable()
{

}

///////////////////////////////////////////////////////////////////////////////
//real
///////////////////////////////////////////////////////////////////////////////
void variable::init(std::string na,double rv,std::string de,std::string mo,std::string ro,std::string ou)
{
    name = na;
    ival = 0;
    rval = rv;
    type = "";
    def = de;
    mod = mo;
    role = ro;
    out = ou;
}
///////////////////////////////////////////////////////////////////////////////
//int
///////////////////////////////////////////////////////////////////////////////
void variable::init(std::string na,std::string ty,int iv,std::string de,std::string mo,std::string ro,std::string ou)
{
    name = na;
    ival = iv;
    rval = 0;
    type = ty;
    def = de;
    mod = mo;
    role = ro;
    out = ou;
}
///////////////////////////////////////////////////////////////////////////////
//'Matrix' for 3x1 vectors
///////////////////////////////////////////////////////////////////////////////
void variable::init(std::string na,double v1,double v2,double v3,std::string de,std::string mo,std::string ro,std::string ou)
{
    name = na;
    ival = 0;
    rval = 0;
    type = "";
    def = de;
    mod = mo;
    role = ro;
    out = ou;

    double *pbody;
    pbody=VEC.get_pbody();
    *pbody=v1;
    *(pbody+1)=v2;
    *(pbody+2)=v3;
}

///////////////////////////////////////////////////////////////////////////////
//'Matrix' for 3x3 matrixs
///////////////////////////////////////////////////////////////////////////////

void variable::init(std::string na,double v11,double v12,double v13,double v21,double v22,double v23,
                    double v31,double v32,double v33,std::string de,std::string mo,std::string ro,std::string ou)
{
    name = na;
    ival = 0;
    rval = 0;
    type = "";
    def = de;
    mod = mo;
    role = ro;
    out = ou;

    double *pbody;
    pbody=MAT.get_pbody();
    *pbody=v11;
    *(pbody+1)=v12;
    *(pbody+2)=v13;
    *(pbody+3)=v21;
    *(pbody+4)=v22;
    *(pbody+5)=v23;
    *(pbody+6)=v31;
    *(pbody+7)=v32;
    *(pbody+8)=v33;
}
///////////////////////////////////////////////////////////////////////////////
//'Matrix' for 5x1 vectors
///////////////////////////////////////////////////////////////////////////////
void variable::init(std::string na,double v1,double v2,double v3,double v4,double v5,
                    std::string de,std::string mo,std::string ro,std::string ou)
{
    name = na;
    ival = 0;
    rval = 0;
    type = "";
    def = de;
    mod = mo;
    role = ro;
    out = ou;

    double *pbody;
    pbody=VEC5.get_pbody();
    *pbody=v1;
    *(pbody+1)=v2;
    *(pbody+2)=v3;
    *(pbody+3)=v4;
    *(pbody+4)=v5;
}

///////////////////////////////////////////////////////////////////////////////
//'Matrix' for 5x5 matrixs
///////////////////////////////////////////////////////////////////////////////

void variable::init(std::string na,
                    double v11,double v12,double v13,double v14,double v15,
                    double v21,double v22,double v23,double v24,double v25,
                    double v31,double v32,double v33,double v34,double v35,
                    double v41,double v42,double v43,double v44,double v45,
                    double v51,double v52,double v53,double v54,double v55,
                    std::string de,std::string mo,std::string ro,std::string ou)
{
    name = na;
    ival = 0;
    rval = 0;
    type = "";
    def = de;
    mod = mo;
    role = ro;
    out = ou;

    double *pbody;
    pbody=MAT5.get_pbody();
    *pbody=v11;     *(pbody+1)=v12; *(pbody+2)=v13; *(pbody+3)=v14; *(pbody+4)=v15;
    *(pbody+5)=v21; *(pbody+6)=v22; *(pbody+7)=v23; *(pbody+8)=v24; *(pbody+9)=v25;
    *(pbody+10)=v31;*(pbody+11)=v32;*(pbody+12)=v33;*(pbody+13)=v34;*(pbody+14)=v35;
    *(pbody+15)=v41;*(pbody+16)=v42;*(pbody+17)=v43;*(pbody+18)=v44;*(pbody+19)=v45;
    *(pbody+20)=v51;*(pbody+21)=v52;*(pbody+22)=v53;*(pbody+23)=v54;*(pbody+24)=v55;
}




