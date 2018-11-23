/*******辅助函数*******/

/***************************************************/
/***                 升序函数                     ****/
/***************************************************/

int compare (const void * a, const void * b){
    return  *(float *)a >= *(float *)b ? 1 : -1;
}

// 测试升序排序函数
/*float values[] = { 40, 10, 100, 90, 20, 25 };
 int main ()
{
    int n;
    
    qsort (values, 6, sizeof(float), compare);
    for (n=0; n<6; n++)
        if (n != 5)
            printf ("%.2f ",values[n]);
        else
            printf("%.2f\n\n",values[n]);
    
    return 0;
}*/

/***************************************************/
/***                 声音触觉值函数                ****/
/***************************************************/

float ABS(float a){
    if (a<0)
        return a*(-1);
    else
        return 1;               //注意此处，相对速度大于零时，返回的是1
}

/***************************************************/
/***                 数组平均值函数                ****/
/***************************************************/
//求一个数组从n项到m项的平均值(包含n项，m项）
float mean_array(float * p, int n, int m) {
    float total = 0.0, mean_v;
    int i = n;
    while (i < m+1) {
        total += *(p + i);
        //printf("%.1f  \n", total);
        i += 1;
    }
    mean_v = total / (m-n+1);
    return mean_v;
}

/***************************************************/
/***                取输出较大值函数               ****/
/***************************************************/

float MAX(float a, float b){
    if (a >= b)
        return a;
    else
        return b;
}
