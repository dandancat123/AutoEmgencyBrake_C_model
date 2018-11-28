#ifndef para_h
#define para_h

/*------------------------------------------------------------------*/
/*                           宏                                     */
/*------------------------------------------------------------------*/
#define calc_t   500                                  //计算过去0.5s的值

/*------------------------------------------------------------------*/
/*                           变量声明                                 */
/*------------------------------------------------------------------*/


extern float v_d[calc_t], lca_d[calc_t], pres_d [calc_t], acce_d[calc_t];
//velocity_deposit,location_deposit,pressure_deposit,acceleration_deposit.

extern float Ep, TTC , **p_p;
//pointer to pointer 指向指针的指针，返回的是一个排序好的压力和加速度数组。

extern float * pv , *pl , *pp , *pa , *p_t ;
/*pointer to velocity,pointer to location, pointer to pressure,
  pointer to acceleration, pointer to ttc.*/

extern float v, dis_rel, dis_min, prec , acce_calc, acce_meas, v_rel, pres_now, pres_max, pres_min, ttime;
/*变量依次为：本车速度，相对距离，瞬时最小距离，距离公式精确度，计算减速度，实际测量减速度,
 相对速度, 本车速度+相对速度 = 前车速度, 现在压力， 压力最大值， 压力最小值， */






#endif

/* para_h */
