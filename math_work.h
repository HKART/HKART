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
    float base = 20000.0;
    float base_copy = base;
    for (i = 0; i< num_elements-1; ++i) {
        if (data[i+1]>data[i]) 
            base = base + (data[i+1]-data[i]);
        else
            base = base - (data[i]-data[i+1]);
    }
    //rare case
    if (base_copy == base) return 0;

    return (base > base_copy?1:2);
}



#endif /* MATH_WORK_H */
