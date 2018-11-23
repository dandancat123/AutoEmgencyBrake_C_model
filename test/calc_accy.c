/*******计算距离公式准确度*******/

#include <stdlib.h>
#include <math.h>
#include "para.h"



/********************************************************************/
/***                        函数原型                              ****/
/********************************************************************/
int compare(const void * a, const void * b);
void qsort(void *base,size_t nmemb,size_t size,int (*compar)(const void *, const void *));
float mean_array(float * p, int n, int m);

/********************************************************************/
/***                        各变量数组初始化                        ****/
/********************************************************************/
void vd_init(void){           //velocity&distance_initialize()
    int i;
    for (i = 0; i < calc_t; ++i) {
        acce_d[i] = pres_d[i] = v_d[i] = lca_d[i] = 0.0;
        //printf("%.1f\t", v_d[i]);                              //测试行
    }
}

/********************************************************************/
/***                        速度延迟函数                           ****/
/********************************************************************/

//得到一个速度/距离值，存入数组，以前值前移
void v_delay(float v) {
    int i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pv + i) = *(pv + i - 1);
        else
            *pv = v;
    }
    for (i = 0; i<calc_t; i ++)
        if (i != calc_t){
            //printf("%.2f  ", *(pv+i));                          //测试行
            ;}
}

/********************************************************************/
/***                        距离延迟函数                           ****/
/********************************************************************/

//得到一个速度/距离值，存入数组，以前值前移
void l_delay(float dis) {
    int i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pl + i) = *(pl + i - 1);
        else
            *pl = dis;
    }
    for (i = 0; i<calc_t; i ++)
        //printf("%.2f  ", *(pl+i));                             //测试行
        ;
}

/********************************************************************/
/***                        压力延迟函数                           ****/
/********************************************************************/

//得到一个速度/距离值，存入数组，以前值前移
void pres_delay(float pres) {
    int i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pp + i) = *(pp + i - 1);
        else
            *pp = pres;
    }
    for (i = 0; i<calc_t; i ++)
        //printf("%.2f  ", *(pp+i));                             //测试行
    ;
}

/********************************************************************/
/***                     由速度得到加速度函数                        ****/
/********************************************************************/
void acce_delay(void){
    int i;
    for (i = (calc_t - 1); i>-1; i--){
        if (i)
            *(pa+i) = *(pv+i) - *(pv+i-1);
        else
            *(pa+i) = *(pa+i+1);
    }
    for (i=0; i<calc_t; i++)
        //printf("%.2f  ",*(pa+i));                              //测试行
        ;
}

/********************************************************************/
/***                     加速度压力排序函数                         ****/
/********************************************************************/
float pres_s[calc_t],acce_s[calc_t];                             //pressure_sorted,acceleration_sorted
float * p_array[2];

float **pa_sort(void){
    int i;
    float * pa, *ps;                                             //pointer to pressure,pointer to acceleration.
    for (i=0 ; i < calc_t; i++){
        pres_s[i] = pres_d[i];
        acce_s[i] = acce_d[i];
        //printf("%.2f  ",pres_s[i]);                            //测试行
    }
    qsort(pres_s, calc_t, sizeof(float), compare);  //复制原压力数组，并依次排序好
    qsort(acce_s, calc_t, sizeof(float), compare);  //同上
    /*for (i=0 ; i < calc_t; i++){
        printf("%.2f  ",pres_s[i]);  //测试行
    }*/
    p_array[0] = ps = pres_s;
    p_array[1] = pa = acce_s;
    return p_array;
}


/********************************************************************/
/***                     求距离模型准确度函数                        ****/
/********************************************************************/
float accury_calc(void){
    float acce_m = 0.0 , dis_r, dis_m, precs;                          //加速度平均值,距离平均值
    acce_m = mean_array(pa, 0, calc_t-1);
    dis_r = mean_array(pl, calc_t-11, calc_t-1) - mean_array(pl, 0, 9); //distance_real实际行驶距离
    dis_m = mean_array(pv, calc_t-11, calc_t-1)*(calc_t/1000) - 0.5 * acce_m * pow((calc_t/1000),2.0);
                                                                       //这里假设采样频率是1000Hz. distantce_modle
    precs = dis_m - dis_r;                                             //模型与实际偏差值。precise = 理论行驶距离 - 实际行驶距离
    
    return precs;
}

