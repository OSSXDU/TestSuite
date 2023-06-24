// By xchhe 2018.
#ifndef CONSTANTS_H
#define CONSTANTS_H

//仿真中用到的常量
//物理常量
double const REARTH=6370987.308;		//地球半径均值- m
double const WEII3=7.292115e-5;			//地球自转角速度 - rad/s
double const AGRAV=9.80675445;			//重力加速度标准值 - m/s^2 
double const G=6.673e-11;			//万有引力常数 - Nm^2/kg^2
double const EARTH_MASS=5.973e24;		//地球质量 - kg
double const R=287.053;				//理想空气气体常数 - J/(K*kg)=N*m/(K*kg)
double const KBOLTZ=1.38e-23;			//Boltzmann's常数 - Ws/K  


//数值常量
double const PI=3.1415927;			//圆周率
double const EPS=1.e-10;			//计算机误差
double const SMALL=1.e-7;			//小实数
int const    ILARGE=9999;			//大整数


//转换系数
double const RAD=0.0174532925199432;            //角度/弧度 deg->rad
double const DEG=57.2957795130823;		//弧度/角度 rad->deg


//其他，可自行定义！！！


#endif
