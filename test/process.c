/*******计算是否需要另外加压*******/

#include <stdio.h>
#include "para.h"
#include <math.h>

/********************************************************************/
/***                          计算TTC                             ****/
/********************************************************************/

void calc_ttc(float v_rel,float dis_rel){
    if (v_rel > 0)                                      //v_rel>0 表示前车速度快，此时TTC无意义,雷达未探测到物体的dis_rel是多少？？？
        *p_t = 20;
    else                                                //
        *p_t = (-1) * dis_rel / v_rel;

}
/********************************************************************/
/***                       输出占空比函数                           ****/
/********************************************************************/
//函数原型
float MAX(float, float);
float mean_array(float * p, int n, int m);


float EP[2] = {0.0,0.0};
//第一个值为本次采样后得到的期望占空比，第二个值为上次采样后得到的期望占空比
float Ep_add,* p_ep = EP;                                      //pointer to expect pressure.


float calc_ep(void){
    float * ps, s_m, a_e, acce_ms, v_ms;    //distance_model, acceleration_measure, velocity_measure
    ps = *p_p;
    
    acce_ms = mean_array(pa, 0, 19);       //现在的加速度
    v_ms = mean_array(pv, 0, 19);          //现在的速度
    
    //判断最近的一段时间压力保持平衡,稳定时计算增加加速度，不稳定，输出为0；
    if ((mean_array(ps, 0, 19) < mean_array(pp, 0, 9) * 1.05) &&\
        (mean_array(ps, calc_t-21, calc_t-1) > mean_array(pp, 0, 9)*0.95) &&\
        mean_array(pp, 0, 9) > 10  && v_ms > 1.0){
        
        s_m = dis_rel + prec;                           //修正后的理论距离 = 实际距离 + 模型准确度
        a_e = 2*pow((pow(acce_ms,2.0) + 6*acce_ms*s_m - 6*acce_ms*v_ms + 36*pow(s_m, 2.0) - 36*s_m*v_ms + \
                     12*pow(v_ms, 2.0)),0.5) + 6*v_ms -12*s_m - 2*acce_ms;     //距离修正后需增加的加速度
        if (round(a_e) >= 1  && round(a_e) < 4)
            Ep_add = 0.1*round(a_e);
        else if (round(a_e)<1 && round(a_e)>=0)
            Ep_add = 0.0;
        else if (round(a_e)>= 4)
            Ep_add = 0.4;
        else
            Ep_add = 0.0;
    }
    else if (TTC < 0.8)                              //0.8秒的TTC，强制压力升到最大值
        Ep_add = 0.4;
    else
        Ep_add = 0.0;
    return Ep_add;
}
    
float pres_p(void){                        //根据得到的压力，计算应该增加的加速度，并与上一次采样的结果对比，输出较大值。
    float ep_add;
    ep_add = calc_ep();
    *(p_ep+1) = *p_ep;
    *p_ep = ep_add;
    return MAX(*p_ep, *(p_ep+1));
}
