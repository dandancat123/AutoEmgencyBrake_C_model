/*  通过计算距离，来确定AEB状态。在不同状态下，进行不同的制动测试  */


/***************************预编译*************************************/
/*-------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "para.h"

//simfun.c    提供一些辅助函数；
//calc_dis.c  输出AEB状态；
//accuracy.c  输出距离公式准确度；
//process.c   输出状态3时的占空比。

/*************************声明变量***********************************/
/*-----------------------------------------------------------------*/



/************************函数原型************************************/
/*-----------------------------------------------------------------*/
float calc_dis(float v);
int calc_state(float, float, float);
void vd_init(void);
void v_delay(float);
void l_delay(float);
void pres_delay(float);
void acce_delay(void);
void calc_ttc(float,float);
float **pa_sort(void);
float pres_p(void);
float accury_calc(void);

/************************主函数**************************************/
/*-----------------------------------------------------------------*/
//整个执行过程是什么？每个采样时间点，新的信号值进入，重新执行一遍main()么？
int main(void){
    float ** p_p;
    
    vd_init();                                 //开始时，平均距离速度初始化
    if (1){                                    //得到新的速度，距离，压力，将该值存入数组;并计算加速度数组
        //v_delay(v);
        //l_delay(dis);
        //pres_delay(pres);
        //acce_delay();
        //pa_sort();
        ;
    }
    calc_ttc(v_rel,dis_rel);
    prec = accury_calc();
    p_p = pa_sort();
    int m = 8;
    
        
    int AEB_State = 0;
    //AEB_State = calc_state(v, v_rel, dis_rel);     //计算AEB状态
    //printf("AEB状态：%d\n",AEB_State);
    
    if (AEB_State == 0)
        ;
    else if (AEB_State == 1)
        ;
    else if (AEB_State == 2)
        ;
    else
        Ep_s = 0.3 + pres_p();                         //expect_start 初始期望占空比
    return 0;
}


