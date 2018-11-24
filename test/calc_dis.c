/*******计算AEB状态*******/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*----------------------------------------------------------------------*/
/*                                 宏                                   */
/*----------------------------------------------------------------------*/
#define Sig_delay_t       0.1           //信号延迟时间
#define Prs_delay_t       1.0           //升压时间
#define Pres_init         0.3           //状态3初始占空比
#define Ep_acce_ego       6.0           //自车期望减速度
#define Ep_acce_frt       8.0           //预期汽车最大制动减速度
#define SonRes_time       0.5           //驾驶员声音反应时间
#define HapRes_time       0.5           //驾驶员声音反应时间
#define dis_S0            1.0           //自车与前车距离最小时的距离


/*----------------------------------------------------------------------*/
/*                               函数原型                                */
/*----------------------------------------------------------------------*/
int compare(const void *p1, const void *p2);
void qsort(void *base,size_t nmemb,size_t size,int (*compar)(const void *, const void *));
float ABS(float);
float MAX(float, float);


/*----------------------------------------------------------------------*/
/*                             AEB状态函数                               */
/*----------------------------------------------------------------------*/
int calc_state(float v, float v_rel, float dis_rel){
    float FrSt_t, v_f;                     //前车停止需要时间，前车车速
    int dis_time;
    v_f = v_rel + v;
    
    //未来两车都停止的时刻t，乘以10.
    dis_time = ceil(MAX(v_f/Ep_acce_frt,(v - 0.5 * Ep_acce_ego * Prs_delay_t) / Ep_acce_ego\
                        + Sig_delay_t + Prs_delay_t)*10);
    
    float t[dis_time], Sf[dis_time], Sr[dis_time], dis[dis_time], dis_brake, dis_haptic, dis_sound;
    int i, AEB_state;
    
    for (i = 0; i < dis_time; ++i){
    t[i] = 0.1 * i;
    Sr[i] = Sf[i] = 0.0;
    }
    
    
    

    FrSt_t = v_f/Ep_acce_frt;
    for (i = 0; i < dis_time; ++i){        //计算前车以Ep_acce_frt的制动减速度行驶到停止时的行驶距离
        if (t[i] < FrSt_t)
            Sf[i] = v_f * t[i] - 0.5 * Ep_acce_frt * pow(t[i],2.0);
        else
            Sf[i] = Sf[i-1];
        //printf("%7.2f  %7.2f %7.2f\n",t[i],Sf[i],v_f - Ep_acce_frt*t[i]);  //测试行
        
    }
    
    
    for (i = 0; i < dis_time; ++i){        //计算自车以Ep_acce_ego的制动减速度行驶到停止时的行驶距离
        if (t[i] < Sig_delay_t)
            Sr[i] = v * t[i];
        else if (t[i] < (Sig_delay_t + Prs_delay_t))
            Sr[i] = v * Sig_delay_t + v * (t[i] - Sig_delay_t) - Ep_acce_ego * pow((t[i] - Sig_delay_t), 3.0)/(6.0 * Prs_delay_t);
        else if (t[i] < (Sig_delay_t + Prs_delay_t + (v - 0.5*Ep_acce_ego*Prs_delay_t)/Ep_acce_ego)){
            Sr[i] = v * (Sig_delay_t + Prs_delay_t) - Ep_acce_ego * pow(Prs_delay_t,2.0)/6.0 + \
                 (v - 0.5 * Ep_acce_ego * Prs_delay_t) *  (t[i] - Sig_delay_t - Prs_delay_t)\
            - 0.5 * Ep_acce_ego * pow((t[i] - Sig_delay_t - Prs_delay_t),2);}
        else
            Sr[i] = Sr[i-1];
        //printf("%7.2f  %7.2f\n",t[i],Sr[i]);        //测试行
    }
    
    for (i = 0; i < dis_time; ++i){                   //在任一时刻，两车行驶距离之差
        dis[i] = Sf[i] - Sr[i];
        //printf("%7.2f  %7.2f\n",t[i],dis[i]);       //测试行
    }
    
    qsort (dis, dis_time , sizeof(float), compare);   //将距离差从小到大排序
    /*for (i = 0; i < dis_time; ++i){
        printf("%7.2f\n",dis[i]);
    }*/                                              //测试行
    
    
    dis_brake = dis[0]*(-1) + dis_S0;                                     //最小制动距离
    dis_haptic = dis_brake + HapRes_time * ABS(v_rel) ;                   //触觉报警距离
    dis_sound = dis_haptic + SonRes_time * ABS(v_rel) ;                   //声音报警距离
    if (dis_rel < dis_brake)
        AEB_state = 3;
    else if (dis_rel < dis_haptic)
        AEB_state = 2;
    else if (dis_rel < dis_sound)
        AEB_state = 1;
    else
        AEB_state = 0 ;
    printf("最小制动距离：%5.2f m\n触觉报警距离：%5.2f m\n声音报警距离：%5.2f m\n\n",dis_brake,dis_haptic,dis_sound);
    
    return AEB_state;
}
