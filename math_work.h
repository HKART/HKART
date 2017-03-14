#ifndef MATH_WORK_H
#define MATH_WORK_H

#include <math.h>

static inline float calculateSD(float data[], int num_elements)
{
    float sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i=0; i<num_elements; ++i)
    {
        sum += data[i];
    }

    mean = sum/num_elements;

    for(i=0; i<num_elements; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation/num_elements);
}

static inline int detect_changing_trends (float data[], int num_elements)
{
    int i;
    int flag_inc = 0;
    int flag_dec = 0;
    int result_inc = 1;
    int result_dec = 1;
    for (i = 0; i< num_elements-1; ++i) {
        if (data[i+1]>data[i]) 
            flag_inc ++;
        else
            flag_inc = 0;
        result_inc = 1*flag_inc;
    }
    for (i = 0; i< num_elements-1; ++i) {
        if (data[i+1]< data[i]) 
            flag_dec ++;
        else
            flag_dec = 0;
        result_dec = 1*flag_dec;
    }

    if (result_inc > 1)
        return 1;
    if (result_dec > 1)
        return 2;
    return 0;
}



#endif /* MATH_WORK_H */
