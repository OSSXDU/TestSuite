//by xchhe 2019
#include <algorithm>
#include <iterator>
#include "ghame3.h"
#include "function.h"
#include "config_proc.h"

using namespace std;

//构造函数，初始化参数
ghame3::ghame3(module *mod_list,int num_mod)
{
    //根据mod_list，对模块组件中使用的变量进行定义
    for(int j=0;j<num_mod;j++)
    {
        if((mod_list[j].name=="environment")&&(mod_list[j].def=="def"))
        {
            def_environment();
        }
        else if((mod_list[j].name=="newton")&&(mod_list[j].def=="def"))
        {
            def_newton();
        }
        else if((mod_list[j].name=="aerodynamics")&&(mod_list[j].def=="def"))
        {
            def_aerodynamics();
        }
        else if((mod_list[j].name=="propulsion")&&(mod_list[j].def=="def"))
        {
            def_propulsion();
        }
        else if((mod_list[j].name=="seeker")&&(mod_list[j].def=="def"))
        {
            def_seeker();
        }
        else if((mod_list[j].name=="guidance")&&(mod_list[j].def=="def"))
        {
            def_guidance();
        }
        else if((mod_list[j].name=="control")&&(mod_list[j].def=="def"))
        {
            def_control();
        }
        else if((mod_list[j].name=="forces")&&(mod_list[j].def=="def"))
        {
            def_forces();
        }
        else if((mod_list[j].name=="intercept")&&(mod_list[j].def=="def"))
        {
            def_intercept();
        }
    }
}


ghame3::~ghame3()
{
}

void ghame3::set_name(string na)
{
    name = na;
}

string ghame3::get_name()
{
    return name;
}




/////////////////////////////////////////////////////////////////////////////////
////////////////////////////功能函数，读写参数相关函数////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
bool ghame3::update_data(const std::string &s, const float &fval)
{
    map<string, variable>::iterator index_vars;
    index_vars = vars_map.find(s);
    int int_data;
    if(index_vars != vars_map.end())
    {
        if(!index_vars->second.type.compare(("int")))
        {
            int_data=(int)fval;
            index_vars->second.ival = int_data;
        }
        else
        {
            index_vars->second.rval = fval;
        }
        return true;
    }
    return false;
}




void ghame3::print(std::ostream &out)
{
    int i=0;
    map<string, variable>::iterator index;
    for(index=vars_map.begin(); index!=vars_map.end(); index++)
    {
        out<<i++<<"          "
                <<index->first<<"          "
                <<index->second.name<<"         "
                <<index->second.ival<<"         "
                <<index->second.rval<<"         "
                //<<index->second.def<<"        "
                <<index->second.mod<<"          "
                <<index->second.role<<"         "
                <<index->second.out<<"          "<<endl;
    }
}


void ghame3::read_params(std::ifstream &fin)
{ 
    //在MODULES_2~MODULES_2_END之间读取初始化参数
    string str;
    float fval;

    fval = get_data_from_mod(fin, string("lonx"), 2);
    if(!update_data(string("lonx"), fval)) { };
    fval = get_data_from_mod(fin, string("latx"), 2);
    update_data(string("latx"), fval);
    fval = get_data_from_mod(fin, string("alt"), 2);
    update_data(string("alt"), fval);
    fval = get_data_from_mod(fin, string("psivgx"), 2);
    update_data(string("psivgx"), fval);
    fval = get_data_from_mod(fin, string("thtvgx"), 2);
    update_data(string("thtvgx"), fval);
    fval = get_data_from_mod(fin, string("dvbe"), 2);
    update_data(string("dvbe"), fval);
    fval = get_data_from_mod(fin, string("alphax"), 2);
    update_data(string("alphax"), fval);
    fval = get_data_from_mod(fin, string("phimvx"), 2);
    update_data(string("phimvx"), fval);

    str = get_text_from_mod(fin, string("aero_deck"), 2);
    aero_tabler.read_tables(str);//从气动数据文件中读取气动表

    fval = get_data_from_mod(fin, string("area"), 2);
    update_data(string("area"), fval);

    str = get_text_from_mod(fin, string("prop_deck"), 2);
    prop_tabler.read_tables(str);//从推力数据文件中读取推力表

    fval = get_data_from_mod(fin, string("mprop"), 2);
    update_data(string("mprop"), fval);
    fval = get_data_from_mod(fin, string("mass0"), 2);
    update_data(string("mass0"), fval);
    fval = get_data_from_mod(fin, string("fmass0"), 2);
    update_data(string("fmass0"), fval);
    fval = get_data_from_mod(fin, string("acowl"), 2);
    update_data(string("acowl"), fval);
    fval = get_data_from_mod(fin, string("throttle"), 2);
    update_data(string("throttle"), fval);
    fval = get_data_from_mod(fin, string("thrtl_idle"), 2);
    update_data(string("thrtl_idle"), fval);
    fval = get_data_from_mod(fin, string("thrtl_max"), 2);
    update_data(string("thrtl_max"), fval);
}



void ghame3::plot_label(std::ofstream &out, std::string title)
{
    int plot_var_count=0;
    string buff1,buff2;
    out<<"1 "<< title<<" "<<name<<" "<<__DATE__<<" "<<__TIME__<<endl;

    map<string, variable>::iterator index;
    for(index=vars_map.begin();index!=vars_map.end();index++)
    {
        if(-1 != index->second.out.find("plot"))
        {
            if(!isupper(index->second.name[0]))//矩阵不输出
            {
                plot_var_count++;
            }
        }
    }

    out<<"0  0 " <<plot_var_count<<endl;

    out.setf(ios::left);
    //绘制数据表格第一行label
    for(index=vars_map.begin();index!=vars_map.end();index++)
    {
        if(-1 != index->second.out.find("plot"))
        {
            if(!isupper(index->second.name[0]))//矩阵不输出
            {
                out.width(16);
                out<<index->second.name;
            }
        }
    }
    out<<endl;
}

//////////////////////////////////////////////////////////
//向plot文件输出plot_data
//////////////////////////////////////////////////////////
void ghame3::plot_data(std::ofstream &fout)
{
    fout.setf(ios::left);
    map<string, variable>::iterator index;
    //绘制数据表格
    for(index=vars_map.begin();index!=vars_map.end();index++)
    {
        if(-1 != index->second.out.find("plot"))
        {
            fout.width(16);
            if(!isupper(index->second.name[0]))//矩阵不输出
            {
                if(!index->second.type.compare("int"))
                {
                    fout<<index->second.ival;
                }else
                {
                    fout<<index->second.rval;
                }
            }
        }
    }
    fout<<endl;
}

//设备之间通讯使用
packet* ghame3::loading_packet_init()
{
    com_packet.set_id(name);
    com_packet.set_status(1);

    map<string, variable>::iterator index;
    for(index=vars_map.begin();index!=vars_map.end();index++)
    {
        if(-1 != index->second.out.find("com"))
        {
            com_packet.set_data(index->second);
        }
    }

    return &com_packet;
}

packet* ghame3::loading_packet()
{
    map<string, variable>::iterator index;
    for(index=vars_map.begin();index!=vars_map.end();index++)
    {
        if(-1 != index->second.out.find("com"))
        {
            com_packet.set_data(index->second);
        }
    }

    return &com_packet;
}

//////////////////////////////////////////////////////////
/////////////////////模块函数接口///////////////////////////
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
//环境参数定义
//////////////////////////////////////////////////////////
void ghame3::def_environment()
{
    variable var;
    var.init("0time",0,"Simulation time start - s","environment","exec","plot,com");
    vars_map["0time"] = var;

    var.init("grav",0,"Gravitational acceleration - m/s^2","environment","out","");
    vars_map["grav"] = var;

    var.init("rho",0,"Air density - kg/m^3","environment","out","");
    vars_map["rho"] = var;

    var.init("pdynmc",0,"Dynamic pressure - Pa","environment","out","plot,com");
    vars_map["pdynmc"] = var;

    var.init("mach",0,"Mach number - ND","environment","out","plot,com");
    vars_map["mach"] = var;

    var.init("vsound",0,"Speed of sound - m/s","environment","diag","");
    vars_map["vsound"] = var;

    var.init("press",0,"Atmospheric pressure - Pa","environment","out","");
    vars_map["press"] = var;
}


//////////////////////////////////////////////////////////
//环境参数初始化
//////////////////////////////////////////////////////////
void ghame3::init_environment(double sim_time)
{
    //从当前时间开始仿真
    vars_map.find("0time")->second.rval = sim_time;
}

//////////////////////////////////////////////////////////
//环境参数计算
//////////////////////////////////////////////////////////
void ghame3::environment(double sim_time)
{    
    double temp,k;
    double grav,rho,pdynmc,mach,vsound,press,alt,dvbe;
    temp = k = grav = rho = pdynmc = mach = vsound = press = alt = dvbe = 0;

    //获得高度和速度
    //code here

    //地球引力加速度
    //code here

    //US76大气标准
	//code here
	
	
    //缓存
    vars_map.find("grav")->second.rval  = grav;
    vars_map.find("rho")->second.rval   = rho;
    vars_map.find("pdynmc")->second.rval= pdynmc;
    vars_map.find("mach")->second.rval  = mach;
    vars_map.find("vsound")->second.rval= vsound;
    vars_map.find("press")->second.rval = press;
    vars_map.find("0time")->second.rval = sim_time;
}

//////////////////////////////////////////////////////////
//牛顿定律参数定义
//////////////////////////////////////////////////////////
void ghame3::def_newton()
{
    variable var;

    var.init("lonx",0,"Vehicle longitude - deg","newton","init/diag","plot,com");
    vars_map["lonx"] = var;

    var.init("latx",0,"Vehicle latitude - deg","newton","init/diag","plot,com");
    vars_map["latx"] = var;

    var.init("alt",0,"Vehicle altitude - m","newton","init/out","plot,com");
    vars_map["alt"] = var;

    var.init("dvbe",0,"Vehicle speed - m/s","newton","init/out","");    
    vars_map["dvbe"] = var;

    var.init("psivgx",0,"Vehicle heading angle - deg","newton","init/out","plot,com");
    vars_map["psivgx"] = var;

    var.init("thtvgx",0,"Vehicle flight path angle - deg","newton","init/out","plot,com");
    vars_map["thtvgx"] = var;

    var.init("SBII",0,0,0,"Inertial position - m ","newton","state","com");
    vars_map["SBII"] = var;

    var.init("VBII",0,0,0,"Inertial velocity - m/s ","newton","state","");
    vars_map["VBII"] = var;

    var.init("ABII",0,0,0,"Inertial acceleration - m/s^2 ","newton","state","");
    vars_map["ABII"] = var;

    var.init("SBEG",0,0,0,"Geographic position wrt ground point below launch - m","newton","state","scrn,plot,com");
    vars_map["SBEG"] = var;

    var.init("VBEG",0,0,0,"Geographic velocity - m/s","newton","state","scrn,plot,com");
    vars_map["VBEG"] = var;

    var.init("TGE",0,0,0,0,0,0,0,0,0,"Geographic wrt Earth - ND ","newton","out","");
    vars_map["TGE"] = var;

    var.init("TGV",0,0,0,0,0,0,0,0,0,"TM of geographic wrt geo velocity coord - ND ","newton","init","");
    vars_map["TGV"] = var;

    var.init("TIG",0,0,0,0,0,0,0,0,0,"TM of inertial wrt geographic coordinates ","newton","init/out","");
    vars_map["TIG"] = var;

    var.init("WEII",0,0,0,0,0,0,0,0,0,"Earth's angular velocity (skew-sym) - rad/s ","newton","init","");
    vars_map["WEII"] = var;
}

//////////////////////////////////////////////////////////
//牛顿定律参数初始化
//////////////////////////////////////////////////////////
void ghame3::init_newton()
{     
    //临时变量
    matrix TEI(3,3);
    matrix SBIE(3,1);
    matrix SBIG(3,1);
    matrix VBEI(3,1);
    matrix TGI(3,3);
    matrix TEG(3,3);
    matrix TVG(3,3);

    //临时变量
    matrix TGE(3,3);
    matrix TGV(3,3);
    matrix TIG(3,3);
    matrix WEII(3,3);
    matrix VBEG(3,1);
    matrix SBII(3,1);
    matrix VBII(3,1);


    //获得输入
    double dvbe = vars_map.find("dvbe")->second.rval;
    double psivgx = vars_map.find("psivgx")->second.rval;
    double thtvgx = vars_map.find("thtvgx")->second.rval;
    double lonx = vars_map.find("lonx")->second.rval;
    double latx = vars_map.find("latx")->second.rval;
    double alt = vars_map.find("alt")->second.rval;

    //由lonx、latx、alt计算SBIE
    double temp = -(alt+REARTH);
    SBIG.assign_loc(2,0,temp);
    TGE = get_tge_mat(lonx*RAD,latx*RAD);
    TEG = TGE.trans();
    SBIE = TEG*SBIG;

    //仿真开始时，认为SBII==SBIE
    SBII = SBIE;

    //由气流坐标系下的速度计算机体坐标系下的速度。
    VBEG.pol_to_cart(dvbe,psivgx*RAD,thtvgx*RAD);

    //地球参考系和地球惯性系之间的角速度。
    WEII.zero();
    WEII.assign_loc(0,1,-WEII3);
    WEII.assign_loc(1,0,WEII3);

    //仿真开始时，任务TIG==TEG
    TIG = TEG;

    //计算VBII
    VBII = TIG*VBEG+WEII*SBII;

    //计算TVG
    TVG = get_tvg_mat(psivgx*RAD,thtvgx*RAD);
    TGV=TVG.trans();

    //缓存
    vars_map.find("TGV")->second.MAT    = TGV;
    vars_map.find("TIG")->second.MAT    = TIG;
    vars_map.find("WEII")->second.MAT   = WEII;
    vars_map.find("VBEG")->second.VEC   = VBEG;
    vars_map.find("TGE")->second.MAT    = TGE;
    vars_map.find("SBII")->second.VEC   = SBII;
    vars_map.find("VBII")->second.VEC   = VBII;
}


//////////////////////////////////////////////////////////
//牛顿定律计算
//////////////////////////////////////////////////////////
void ghame3::newton(double int_step)
{  
    //local variables
    matrix SBIE(3,1);
    matrix TEMP(3,1);
    matrix VBEI(3,1);
    matrix GRAV(3,1);
    matrix ABII_NEW(3,1);
    matrix VBII_NEW(3,1);
    matrix POLAR(3,1);
    matrix VBEG_NEW(3,1);
    matrix TEI(3,3);
    matrix TGI(3,3);
    matrix TEG(3,3);
    matrix TVG(3,3);
    matrix TGE(3,3);

    //获得输入
    matrix WEII = vars_map.find("WEII")->second.MAT;
    matrix SBEG = vars_map.find("SBEG")->second.VEC;
    matrix VBEG = vars_map.find("VBEG")->second.VEC;
    matrix SBII = vars_map.find("SBII")->second.VEC;
    matrix VBII = vars_map.find("VBII")->second.VEC;
    matrix ABII = vars_map.find("ABII")->second.VEC;

    matrix TGV = vars_map.find("TGV")->second.MAT;
    matrix TIG = vars_map.find("TIG")->second.MAT;

    double time = vars_map.find("0time")->second.rval;
    matrix FSPV = vars_map.find("FSPV")->second.VEC;
    double grav = vars_map.find("grav")->second.rval;

    //地理坐标系下矢量形式
    //code here

    //惯性参考系下积分计算
	//code here
	
    //计算SBIE
	//code here
	
    //计算lla
	//code here
	
    //计算TGE
    //code here

    //计算TGI
    //code here

    //计算VBEG=TGI*(VBII-(WEII*SBII));
    //code here

    //更新SBEG，VBEG
	//code here
	
    //获得速度坐标系下的角度和速度数值
	//code here
	
    //更新TIG,TGV,
	//code here

    //缓存
    vars_map.find("SBEG")->second.VEC   = SBEG;
    vars_map.find("VBEG")->second.VEC   = VBEG;
    vars_map.find("SBII")->second.VEC   = SBII;
    vars_map.find("VBII")->second.VEC   = VBII;
    vars_map.find("ABII")->second.VEC   = ABII;
    vars_map.find("TGV")->second.MAT    = TGV;
    vars_map.find("TIG")->second.MAT    = TIG;
    vars_map.find("TGE")->second.MAT    = TGE;

    vars_map.find("dvbe")->second.rval  = dvbe;
    vars_map.find("psivgx")->second.rval= psivgx;
    vars_map.find("thtvgx")->second.rval= thtvgx;
    vars_map.find("lonx")->second.rval  = lonx;
    vars_map.find("latx")->second.rval  = latx;
    vars_map.find("alt")->second.rval   = alt;
}

//////////////////////////////////////////////////////////
//气动参数定义
//////////////////////////////////////////////////////////
void ghame3::def_aerodynamics()
{
    variable var;

    var.init("area",0,"Aerodynamic reference area - m^2","aerodynamics","data","");
    vars_map["area"] = var;

    var.init("alphax",0,"Angle of attack - deg","aerodynamics","data","");
    vars_map["alphax"] = var;

    var.init("phimvx",0,"Bank angle - deg","aerodynamics","data","");
    vars_map["phimvx"] = var;

    var.init("cl",0,"Lift coefficient - ND","aerodynamics","out","");
    vars_map["cl"] = var;

    var.init("cd",0,"Drag coefficient - ND","aerodynamics","out","");
    vars_map["cd"] = var;

    var.init("cl_ov_cd",0,"Lift-over-drag ratio - ND","aerodynamics","diag","scrn,plot");
    vars_map["cl_ov_cd"] = var;

    var.init("cla",0,"Lift coefficient slope - 1/deg","aerodynamics","out","");
    vars_map["cla"] = var;
}



//////////////////////////////////////////////////////////
//气动参数初始化
//////////////////////////////////////////////////////////
void ghame3::init_aerodynamics()
{

}


//////////////////////////////////////////////////////////
//气动参数计算
//////////////////////////////////////////////////////////
void ghame3::aerodynamics(double int_step)
{
    //获得输入
    double alphax = vars_map.find("alphax")->second.rval;
    double mach = vars_map.find("mach")->second.rval;

    //从气动表获得内插数据
    double cd0 = aero_tabler.look_up("cd0_vs_mach",mach);
    double cl0 = aero_tabler.look_up("cl0_vs_mach",mach);
    double cla = aero_tabler.look_up("cla_vs_mach",mach);
    double ckk = aero_tabler.look_up("ckk_vs_mach",mach);
    double cla0= aero_tabler.look_up("cla0_vs_mach",mach);
	//code here
	//cl cd cl_ov_vd

    //缓存
    vars_map.find("cl")->second.rval    = cl;
    vars_map.find("cd")->second.rval    = cd;
    vars_map.find("cla")->second.rval   = cla;
    vars_map.find("cl_ov_cd")->second.rval = cl_ov_cd;
}

//////////////////////////////////////////////////////////
//推力参数定义
//////////////////////////////////////////////////////////
void ghame3::def_propulsion()
{
    variable var;

    var.init("mprop","int",0,"=0:none; =1:fixed-throttle; =2:auto-throttle","propulsion","data","");
    vars_map["mprop"] = var;

    var.init("acowl",0,"Cowl area of engine inlet - m^2","propulsion","data","");
    vars_map["acowl"] = var;

    var.init("throttle",0,"Throttle controlling fuel/air ratio - ND","propulsion","data/diag","plot");
    vars_map["throttle"] = var;

    var.init("thrtl_max",0,"Max throttle - ND","propulsion","data","");
    vars_map["thrtl_max"] = var;

    var.init("qhold",0,"Dynamic pressure hold command - Pa","propulsion","data","");
    vars_map["qhold"] = var;

    var.init("mass",0,"Vehicle mass - kg","propulsion","out","scrn,plot");
    vars_map["mass"] = var;

    var.init("mass0",0,"Initial gross mass - kg","propulsion","data","");
    vars_map["mass0"] = var;

    var.init("tq",0,"Autothrottle time constant - sec","propulsion","data","");
    vars_map["tq"] = var;

    var.init("thrtl_idle",0,"Idle throttle - ND","propulsion","data","");
    vars_map["thrtl_idle"] = var;

    var.init("fmass0",0,"Initial fuel mass in stage - kg","propulsion","data","");
    vars_map["fmass0"] = var;

    var.init("fmasse",0,"Fuel mass expended (zero initialization required) - kg","propulsion","state","");
    vars_map["fmasse"] = var;

    var.init("fmassd",0,"Fuel mass expended derivative - kg/s","propulsion","state","");
    vars_map["fmassd"] = var;

    var.init("ca",0,"Capture area factor - ND","propulsion","diag","");
    vars_map["ca"] = var;

    var.init("spi",0,"Specific impulse - sec","propulsion","diag","");
    vars_map["spi"] = var;

    var.init("thrust",0,"Thrust - N","propulsion","out","scrn,plot");
    vars_map["thrust"] = var;

    var.init("mass_flow",0,"Mass flow through hypersonic engine - kg/s","propulsion","diag","");
    vars_map["mass_flow"] = var;

    var.init("fmassr",0,"Remaining fuel mass - kg","propulsion","diag","plot");
    vars_map["fmassr"] = var;
}



//////////////////////////////////////////////////////////
//推力初始化
//////////////////////////////////////////////////////////
void ghame3::init_propulsion()
{
    double mass0 = vars_map.find("mass0")->second.rval;
    double mass=mass0;
    vars_map.find("mass")->second.rval = mass;
}


//////////////////////////////////////////////////////////
//推力参数计算
//////////////////////////////////////////////////////////
void ghame3::propulsion(double int_step)//推力参数计算
{   
    //获得输入
    int mprop       = vars_map.find("mprop")->second.ival;
    double acowl    = vars_map.find("acowl")->second.rval;
    double throttle = vars_map.find("throttle")->second.rval;
    double thrtl_max= vars_map.find("thrtl_max")->second.rval;
    double qhold    = vars_map.find("qhold")->second.rval;
    double mass0    = vars_map.find("mass0")->second.rval;
    double fmass0   = vars_map.find("fmass0")->second.rval;
    double tq       = vars_map.find("tq")->second.rval;
    double thrtl_idle = vars_map.find("thrtl_idle")->second.rval;

    double mass     = vars_map.find("mass")->second.rval;
    double fmassr   = vars_map.find("fmassr")->second.rval;

    double fmasse   = vars_map.find("fmasse")->second.rval;
    double fmassd   = vars_map.find("fmassd")->second.rval;

    double rho      = vars_map.find("rho")->second.rval;
    double pdynmc   = vars_map.find("pdynmc")->second.rval;
    double mach     = vars_map.find("mach")->second.rval;
    double dvbe     = vars_map.find("dvbe")->second.rval;
    double cd       = vars_map.find("cd")->second.rval;
    double area     = vars_map.find("area")->second.rval;
    double alphax   = vars_map.find("alphax")->second.rval;

    double spi,ca,thrust,mass_flow;
    //根据推力引擎油门状态，计算推力
    if(mprop > 0){
        //超音速条件下
        if(mprop==1 || mprop==2){
            //spi查表
            spi = prop_tabler.look_up("spi_vs_throttle_mach",throttle,mach);

            //ca查表
            ca = prop_tabler.look_up("ca_vs_alpha_mach",alphax,mach);
        }
        //固定油门
        if(mprop == 1){
            thrust = spi*0.029*throttle*AGRAV*rho*dvbe*ca*acowl;
        }
        //自动油门
        if(mprop == 2){
            double denom = 0.029*spi*AGRAV*rho*dvbe*ca*acowl;
            if(denom != 0){
                double thrst_req = area*cd*qhold/cos(alphax*RAD);
                double throtl_req = thrst_req/denom;
                double gainq = 2*mass/(rho*dvbe*denom*tq);
                double ethrotl = gainq*(qhold-pdynmc);
                throttle = ethrotl + throtl_req;
            }
            //油门限制
            if(throttle < 0) { throttle=thrtl_idle; }
            if(throttle > thrtl_max) { throttle=thrtl_max; }

            //推力
            spi = prop_tabler.look_up("spi_vs_throttle_mach",throttle,mach);
            thrust = spi*0.029*throttle*AGRAV*rho*dvbe*ca*acowl;
        }

        //计算燃料损耗
        if(spi != 0){
            double fmassd_next = thrust/(spi*AGRAV);
            fmasse = integrate(fmassd_next,fmassd,fmasse,int_step);
            fmassd = fmassd_next;
        }
        //计算飞行器质量,质流,剩余燃料质量
        mass=mass0-fmasse;
        fmassr=fmass0-fmasse;

        //推力单位为KN
        mass_flow = thrust/(AGRAV*spi);

        //当燃料消耗完，则推力引擎停止工作
        if(fmassr<=0)
            mprop=0;
    }

    //无推力条件下
    if(mprop==0){
        fmassd=0;
        thrust=0;
    }


    //缓存
    vars_map.find("fmasse")->second.rval    = fmasse;
    vars_map.find("fmassd")->second.rval    = fmassd;
    vars_map.find("mprop")->second.ival     = mprop;
    vars_map.find("mass")->second.rval      = mass;
    vars_map.find("thrust")->second.rval    = thrust;
    vars_map.find("throttle")->second.rval  = throttle;
    vars_map.find("ca")->second.rval        = ca;
    vars_map.find("spi")->second.rval       = spi;
    vars_map.find("mass_flow")->second.rval = mass_flow;
    vars_map.find("fmassr")->second.rval    = fmassr;
}

//////////////////////////////////////////////////////////
//合力参数定义
//////////////////////////////////////////////////////////
void ghame3::def_forces()
{    
    variable var;

    var.init("FSPV",0,0,0,"Specific force in V-coord - m/s^2","forces","out","plot");
    vars_map["FSPV"] = var;
}



//////////////////////////////////////////////////////////
//合力参数初始化
//////////////////////////////////////////////////////////
void ghame3::init_forces()
{

}



//////////////////////////////////////////////////////////
//合力参数计算
//////////////////////////////////////////////////////////
void ghame3::forces(double int_step)
{
    //获得输入
    double pdynmc   = vars_map.find("pdynmc")->second.rval;
    matrix FSPV     = vars_map.find("FSPV")->second.VEC;
    double mass     = vars_map.find("mass")->second.rval;
    double thrust   = vars_map.find("thrust")->second.rval;
    double cl       = vars_map.find("cl")->second.rval;
    double cd       = vars_map.find("cd")->second.rval;
    double area     = vars_map.find("area")->second.rval;
    double alphax   = vars_map.find("alphax")->second.rval;
    double phimvx   = vars_map.find("phimvx")->second.rval;
	
    double phimv=phimvx*RAD;
    double alpha=alphax*RAD;

	//code here
	//fspv1,fspv2,fspv3
	//FSPV

    //缓存
    vars_map.find("FSPV")->second.VEC = FSPV;
}

//////////////////////////////////////////////////////////
//控制参数定义
//////////////////////////////////////////////////////////
void ghame3::def_control()
{

}

//////////////////////////////////////////////////////////
//控制参数初始化
//////////////////////////////////////////////////////////
void ghame3::init_control()
{

}

//////////////////////////////////////////////////////////
//控制参数计算
//////////////////////////////////////////////////////////
void ghame3::control(double int_step)
{

}

//////////////////////////////////////////////////////////
//制导参数定义
//////////////////////////////////////////////////////////
void ghame3::def_guidance()
{

}

//////////////////////////////////////////////////////////
//制导参数初始化
//////////////////////////////////////////////////////////
void ghame3::init_guidance()
{

}

//////////////////////////////////////////////////////////
//制导参数计算
//////////////////////////////////////////////////////////
void ghame3::guidance(packet *combus,int num_vehicles,double int_step)
{

}

//////////////////////////////////////////////////////////
//导引参数定义
//////////////////////////////////////////////////////////
void ghame3::def_seeker()
{

}

/////////////////////////////////////////////////////////
//导引参数初始化
/////////////////////////////////////////////////////////
void ghame3::init_seeker()
{

}

//////////////////////////////////////////////////////////
//导引参数计算
//////////////////////////////////////////////////////////
void ghame3::seeker(packet *combus,int num_vehicles,double sim_time,double int_step)
{

}

//////////////////////////////////////////////////////////
//传感器参数定义
//////////////////////////////////////////////////////////
void ghame3::def_intercept()
{

}

//////////////////////////////////////////////////////////
//传感器参数初始化
//////////////////////////////////////////////////////////
void ghame3::init_intercept()
{

}

//////////////////////////////////////////////////////////
//传感器参数计算
//////////////////////////////////////////////////////////
void ghame3::intercept(packet *combus,int vehicle_slot,double int_step,std::string title)
{

}
