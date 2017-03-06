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


#endif /* MATH_WORK_H */
