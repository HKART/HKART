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
    for (i = 0; i< num_elements-1; ++i) {
        if (data[i+1]>data[i]) 
            flag_inc ++;
    }
    for (i = 0; i< num_elements-1; ++i) {
        if (data[i+1]< data[i]) 
            flag_dec ++;
    }

    if (flag_inc == (num_elements-1))
        return 1;
    if (flag_dec == (num_elements-1))
        return 2;
    return 0;
}



#endif /* MATH_WORK_H */
