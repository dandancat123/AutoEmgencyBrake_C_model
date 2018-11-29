/*  通过计算距离，来确定AEB状态。在不同状态下，进行不同的制动测试  */

//para.h      声明全局变量
//simfun.c    提供一些辅助函数
//calc_dis.c  输出AEB状态
//accuracy.c  输出距离公式准确度
//process.c   输出状态3时的占空比


/*------------------------------------------------------------------*/
/*                            预编译                                 */
/*------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
//#include <stdlib.h>
#include "para.h"
#include <time.h>

/*------------------------------------------------------------------*/
/*                          变量定义                                  */
/*------------------------------------------------------------------*/
float v, dis_rel, dis_min, prec = 0.0, acce_calc, acce_meas, v_rel, pres_now, pres_max, pres_min, Ep, TTC = 20, ** p_p;

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
void printpv(float * pointer);              //打印存储值函数pv:速度,pl:位置,pp:压力,pa:加速度
void calc_ttc(float,float);
float **pa_sort(void);
float pres_p(void);
float accury_calc(void);
int MAX_int(int a, int b);

/*------------------------------------------------------------------*/
/*                           主函数                                  */
/*------------------------------------------------------------------*/
//整个执行过程是什么？每个采样时间点，新的信号值进入，重新执行一遍main()么？
int main(void){
    /*clock_t begin, end;
    double cost;                                            //计时-开始
    begin = clock();*/
    
    vd_init();                                              //开始时，平均距离速度初始化
    //得到新的速度，距离，压力，将该值存入数组;并计算加速度数组
    
    int i = 0;
    while (i++<600){
        /*srand(i);
        v = (rand()%11/10.0)+i/20.0;
        dis_rel = (rand()%101/100.0)+i;
        pres_now = (rand()%21)+150;*/                        //测试行
        
        v_delay(v);
        l_delay(dis_rel);
        pres_delay(pres_now);
        acce_delay();
        
        calc_ttc(-3,3);
        prec = accury_calc();
        p_p = pa_sort();
        
        int AEB_State_now ;                                  //采样时间计算得到的AEB状态.
        int AEB_S_array[2] = {0,0};                          //AEB_State_array.
        int * p_aeb_s = AEB_S_array;                         //pointer to AEB State Array.
        //AEB_State_now = calc_state(v, v_rel, dis_rel);     //计算AEB状态.
        AEB_State_now = calc_state(20.0, -3.0, 3.0);
        //printf("AEB状态：%d\n",AEB_State_now);
        *(p_aeb_s + 1) = *p_aeb_s;
        *p_aeb_s =AEB_State_now;
        
        //为保持压力只增不减的函数
        if (MAX_int(*p_aeb_s, *(p_aeb_s+1)) == 0)
            ;
        else if (MAX_int(*p_aeb_s, *(p_aeb_s+1)) == 1)
            ;
        else if (MAX_int(*p_aeb_s, *(p_aeb_s+1)) == 2)
            ;
        else
            Ep = 0.3 + pres_p();
    }
    
    /*end = clock();                                          //计时-结束
    cost = (double)(end - begin)/CLOCKS_PER_SEC*1000;
    printf("constant CLOCKS_PER_SEC is: %ld, time cost is: %lf msecs\n", CLOCKS_PER_SEC/1000, cost);*/
    //printpv(pl);                                           //打印存储的值
    
    
    return 0;
}


