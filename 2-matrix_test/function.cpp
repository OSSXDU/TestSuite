//By xchhe 2018.
#include "function.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////
//////////////////////////参考系坐标转换矩阵工具///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//由航迹角thtvg、航向角psivg得到TVG转换矩阵
////////////////////////////////////////////////////////////////////////////////
matrix get_tvg_mat(const double &psivg,const double &thtvg)
{
    matrix AMAT(3,3);

	//code here.

    return AMAT;
}


////////////////////////////////////////////////////////////////////////////////
//由偏航角psi，俯仰角tht，滚转角phi得到TBG转换矩阵
////////////////////////////////////////////////////////////////////////////////
matrix get_tbg_mat(const double &psi,const double &tht,const double &phi)
{
    double spsi=sin(psi);
    double cpsi=cos(psi);
    double stht=sin(tht);
    double ctht=cos(tht);
    double sphi=sin(phi);
    double cphi=cos(phi);

    matrix AMAT(3,3);

	//code here.

    return AMAT;
}





////////////////////////////////////////////////////////////////////////////////
//由经度lon，纬度lat计算计算TGE转换矩阵
////////////////////////////////////////////////////////////////////////////////
matrix get_tge_mat(double lon,double lat)
{
    matrix AMAT(3,3);
    double clon(0);
    double slon(0);
    double clat(0);
    double slat(0);

    clon = cos(lon);
    slon = sin(lon);
    clat = cos(lat);
    slat = sin(lat);

	//code here.

    return AMAT;
}



////////////////////////////////////////////////////////////////////////////////
//由仿真时间与地球自转角速度计算TEI转换矩阵
////////////////////////////////////////////////////////////////////////////////
matrix get_tei_mat(double simulation_time)
{
    double xi(0);
    double sxi(0);
    double cxi(0);
    matrix TEI(3,3);

    xi=WEII3*simulation_time;
    sxi=sin(xi);
    cxi=cos(xi);

    TEI.identity();
    TEI.assign_loc(0,0, cxi); TEI.assign_loc(0,1, sxi);
    TEI.assign_loc(1,0,-sxi); TEI.assign_loc(1,1, cxi);

    return TEI;
}




////////////////////////////////////////////////////////////////////////////////
//由SBIE矢量计算LLA矢量（即SBIG矢量）
////////////////////////////////////////////////////////////////////////////////
matrix get_lla_mat(matrix SBIE)
{
    double dum4(0);
    double alamda(0);
    double x(0),y(0),z(0);
    x=SBIE.get_loc(0,0);
    y=SBIE.get_loc(1,0);
    z=SBIE.get_loc(2,0);
    double dbi;
    double alt;
    double lat;
    double lon;
    matrix RESULT(3,1);

    //Latitude
    dbi=sqrt(x*x+y*y+z*z);
    lat=asin((z)/dbi);

    //Altitude
    alt=dbi-REARTH;

    //Longitude
    dum4=asin(y/sqrt(x*x+y*y));

    //Resolving the multi-valued arcsin function
    if((x>=0)&&(y>=0))
    {
            alamda=dum4;		   //quadrant I
    }
    if((x<0)&&(y>=0))
    {
            alamda=180*RAD-dum4;   //quadrant II
    }
    if((x<0)&&(y<0))
    {
            alamda=180*RAD-dum4;  //quadrant III
    }
    if((x>=0)&&(y<0))
    {
            alamda=360*RAD+dum4;  //quadrant IV
    }
    lon=alamda;
    if(lon>180*RAD)
    {
            lon= -(360*RAD-lon);  //east positive, west negative
    }
    RESULT.assign_loc(0,0,lon);
    RESULT.assign_loc(1,0,lat);
    RESULT.assign_loc(2,0,alt);

    return RESULT;
}



////////////////////////////////////////////////////////////////////////////////
//由空气动力气流角alpha和空气动力滚转角phi计算TBV转换矩阵（3自由度适用）
////////////////////////////////////////////////////////////////////////////////
matrix get_tbv_mat(double phi,double alpha)
{
    matrix AMAT(3,3);

    double salpha=sin(alpha);
    double calpha=cos(alpha);
    double sphi=sin(phi);
    double cphi=cos(phi);

	//code here.

    return AMAT;
}



////////////////////////////////////////////////////////////////////////////////
//由地理坐标计算地球惯性系坐标,TIG=TIE*TEG
////////////////////////////////////////////////////////////////////////////////
matrix get_tig_mat(double lon,double lat,double alt,double time)
{
    matrix VEC(3,1);

    double rad=alt+REARTH;
    double cel_lon=lon+WEII3*time;
    double clat=cos(lat);
    double slat=sin(lat);
    double clon=cos(cel_lon);
    double slon=sin(cel_lon);

    VEC.assign_loc(0,0,rad*clat*clon);
    VEC.assign_loc(1,0,rad*clat*slon);
    VEC.assign_loc(2,0,rad*slat);

    return VEC;
}




////////////////////////////////////////////////////////////////////////////////
//获得符号
//e.g: value_signed=value*get_sign(variable)
////////////////////////////////////////////////////////////////////////////////
int get_sign(const double &variable)
{
    int sign(0);
    if(variable<0.)sign=-1;
    if(variable>=0.)sign=1;

    return sign;
}



////////////////////////////////////////////////////////////////////////////////
//获得矢量夹角
//e.g: theta=angle(VEC1,VEC2);
////////////////////////////////////////////////////////////////////////////////
double get_angle_from_mats(matrix VEC1,matrix VEC2)
{
    double argument(0);
    double scalar=VEC1^VEC2;
    double abs1=VEC1.absolute();
    double abs2=VEC2.absolute();

    double dum=abs1*abs2;
    if(abs1*abs2>EPS)
            argument=scalar/dum;
    else
            argument=1.;
    if(argument>1.) argument=1.;
    if(argument<-1.) argument=-1.;

    return acos(argument);
}








///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////积分函数////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//中值法积分
//e.g 一阶laplace方法:	phid_new=(phic-phi)/tphi;
//			phi=integrate(phid_new,phid,phi,int_step);
//			phid=phid_new;
///////////////////////////////////////////////////////////////////////////////
double integrate(const double &dydx_new,const double &dydx,const double &y,const double &int_step)
{
	double RESULT;
	
	//code here.
	
    return RESULT;	
}

///////////////////////////////////////////////////////////////////////////////
//矩阵积分MAT(r,c)
///////////////////////////////////////////////////////////////////////////////
matrix integrate(matrix &DYDX_NEW,matrix &DYDX,matrix &Y,const double int_step)
{
        int nrow=Y.get_rows();int nrow1=DYDX_NEW.get_rows();int nrow2=DYDX.get_rows();
        int ncol=Y.get_cols();int ncol1=DYDX_NEW.get_cols();int ncol2=DYDX.get_cols();

        if(nrow!=nrow1||nrow!=nrow2)
                {cerr<<" *** Error: row-dimensions in integrate() *** \n";system("pause");exit(1);}
        if(ncol!=ncol1||ncol!=ncol2)
                {cerr<<" *** Error: column-dimensions in integrate() *** \n";system("pause");exit(1);}

        matrix RESULT(nrow,ncol);
        for(int r=0;r<nrow;r++)
                for(int c=0;c<ncol;c++)
                        RESULT.assign_loc(r,c,integrate(DYDX_NEW.get_loc(r,c)
                        ,DYDX.get_loc(r,c),Y.get_loc(r,c),int_step));

        return RESULT;
}
