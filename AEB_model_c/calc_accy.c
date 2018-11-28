/*******计算距离公式准确度*******/
#include <stdio.h>
//#include <stdlib.h>
#include <math.h>
#include "para.h"



/*------------------------------------------------------------------*/
/*                          函数原型                                 */
/*------------------------------------------------------------------*/
//int compare(const void * a, const void * b);                         //stdlib排序函数
//void qsort(void *base,size_t nmemb,size_t size,int (*compar)(const void *, const void *));
void sort(float *a, int l);    //自编排序函数
float mean_array(float * p, int n, int m);

/*------------------------------------------------------------------*/
/*                         各变量数组初始化                            */
/*------------------------------------------------------------------*/
void vd_init(void){           //velocity&distance_initialize()
    int i;
    for (i = 0; i < calc_t; ++i) {
        acce_d[i] = pres_d[i] = v_d[i] = lca_d[i] = 0.0;
        //printf("%.1f\t", v_d[i]);                              //测试行
    }
}

/*------------------------------------------------------------------*/
/*                          速度延迟函数                              */
/*------------------------------------------------------------------*/

//得到一个速度值，存入数组，以前值前移
void v_delay(float v) {
    int i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pv + i) = *(pv + i - 1);
        else
            *pv = v;
    }
}

/*------------------------------------------------------------------*/
/*                          距离延迟函数                              */
/*------------------------------------------------------------------*/

//得到一个位置值，存入数组，以前值前移
void l_delay(float dis) {
    int i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pl + i) = *(pl + i - 1);
        else
            *pl = dis;
    }
}

/*------------------------------------------------------------------*/
/*                          压力延迟函数                              */
/*------------------------------------------------------------------*/

//得到一个压力值，存入数组，以前值前移
void pres_delay(float pres) {
    int i;
    for (i = (calc_t - 1); i > -1; i--) {
        if (i)
            *(pp + i) = *(pp + i - 1);
        else
            *pp = pres;
    }
}

/*------------------------------------------------------------------*/
/*                       由速度得到加速度函数                           */
/*------------------------------------------------------------------*/
void acce_delay(void){
    int i;
    for (i = (calc_t - 1); i>-1; i--){
        if (i)
            *(pa+i) = *(pv+i) - *(pv+i-1);
        else
            *(pa+i) = *(pa+i+1);
    }
}

/*------------------------------------------------------------------*/
/*                          查看存储函数                              */
/*------------------------------------------------------------------*/
void printpv(float * pointer){
    int i;
    
    if (pointer == pv)
        printf("速度存储的值为：");
    else if (pointer == pl)
        printf("距离存储的值为：");
    else if (pointer == pp)
        printf("压力存储的值为：");
    else if (pointer == pa)
        printf("加速度存储的值为：");
    else
        printf("error!");

    for (i=0; i<calc_t; i++)
        printf("%.2f  ",*(pointer+i));                              //查看pv速度 pl距离 pp压力 pa加速度存储值
    printf("\n");
}

/*------------------------------------------------------------------*/
/*                       加速度压力排序函数                            */
/*------------------------------------------------------------------*/
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
    //qsort(pres_s, calc_t, sizeof(float), compare);  //复制压力数组，并依次排序好
    //qsort(acce_s, calc_t, sizeof(float), compare);  //复制加速度数组，并依次排序好
    sort(pres_s, calc_t);
    sort(acce_s, calc_t);
    
    /*for (i=0 ; i < calc_t; i++){
        printf("%.2f  ",pres_s[i]);  //测试行
    }*/
    p_array[0] = ps = pres_s;
    p_array[1] = pa = acce_s;
    return p_array;
}


/*------------------------------------------------------------------*/
/*                       求距离模型准确度函数                           */
/*------------------------------------------------------------------*/
float accury_calc(void){
    float acce_m , dis_r, dis_m, precs;                          //加速度平均值,距离平均值
    acce_m = mean_array(pa, 0, calc_t-1);
    dis_r = mean_array(pl, calc_t-11, calc_t-1) - mean_array(pl, 0, 9); //distance_real实际行驶距离
    dis_m = mean_array(pv, calc_t-11, calc_t-1)*(calc_t/1000) - 0.5 * acce_m * pow((calc_t/1000),2.0);
                                                                       //这里假设采样频率是1000Hz. distantce_modle
    precs = dis_m - dis_r;                                             //模型与实际偏差值。precise = 理论行驶距离 - 实际行驶距离
    
    return precs;
}

