/*  通过计算距离，来确定AEB状态。在不同状态下，进行不同的制动测试  */

//simfun.c    提供一些辅助函数
//calc_dis.c  输出AEB状态
//accuracy.c  输出距离公式准确度
//process.c   输出状态3时的占空比


/*------------------------------------------------------------------*/
/*                            预编译                                 */
/*------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "para.h"

/*------------------------------------------------------------------*/
/*                          变量定义                                  */
/*------------------------------------------------------------------*/
float v, dis_rel, dis_min, prec = 0.0, acce_calc, acce_meas, v_rel, pres_now, pres_max, pres_min, ttime, Ep, TTC = 20, ** p_p;

float v_d[calc_t], lca_d[calc_t], pres_d[calc_t], acce_d[calc_t];

float *pv = v_d, *pl = lca_d, *pp = pres_d, *pa = acce_d, *p_t = &TTC;


/*------------------------------------------------------------------*/
/*                          函数原型                                 */
/*------------------------------------------------------------------*/
int calc_state(float, float, float);
void vd_init(void);
void v_delay(float);
void l_delay(float);
void pres_delay(float);
void acce_delay(void);
void printpv(void);
void calc_ttc(float,float);
float **pa_sort(void);
float pres_p(void);
float accury_calc(void);

/*------------------------------------------------------------------*/
/*                           主函数                                  */
/*------------------------------------------------------------------*/
//整个执行过程是什么？每个采样时间点，新的信号值进入，重新执行一遍main()么？
int main(void){
    
    vd_init();                                 //开始时，平均距离速度初始化
    //得到新的速度，距离，压力，将该值存入数组;并计算加速度数组
    if (1){
        v_delay(10);
        l_delay(20);
        pres_delay(1.4);
        acce_delay();
        printpv();
        
        calc_ttc(-3,3);
        prec = accury_calc();
        p_p = pa_sort();
        
        int AEB_State ;
        //AEB_State = calc_state(v, v_rel, dis_rel);     //计算AEB状态
        AEB_State = calc_state(20.0, -3.0, 3.0);
        printf("AEB状态：%d\n",AEB_State);
        
        if (AEB_State == 0)
            ;
        else if (AEB_State == 1)
            ;
        else if (AEB_State == 2)
            ;
        else
            Ep = 0.3 + pres_p();
    }
    return 0;
}


