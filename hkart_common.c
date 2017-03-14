#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * return 0 if val is in normal range
 * return 1 if val is lesser than min value of reference
 * return 2 if val is greater than max value of reference
 * return 3 if val is equal to min value of reference
 * return 4 if val is equal to max value of reference
 */

int check_against_ref_value (float std_min, float std_max, float val) {
    int ret = 0;
    if (std_min != -1) {
        if (val == std_min)
            ret = 3;
        if (val < std_min)
            ret = 1;
    }
    if (val == std_max)
        ret = 4;
    if (val > std_max)
        ret = 2;
    return ret;
}
void print_details_analysis (int ret,float val,float ref_min,float ref_max,float sd,int ct ,char event[120]) {
    switch (ret) {
        case 0:
            printf ("%s\n\r",event);
            printf ("%f Reference: [min %f - max %f]\n\r",val,ref_min,ref_max);
            printf ("Normal\n\r");
            break;
        case 1:
            printf ("%s\n\r",event);
            printf ("%f Reference: [min %f - max %f]\n\r",val,ref_min,ref_max);
            printf ("Less than min reference\n\r");
            break;
        case 2:
            printf ("%s\n\r",event);
            printf ("%f Reference: [min %f - max %f]\n\r",val,ref_min,ref_max);
            printf ("More than max reference\n\r");
            break;
        case 3:
            printf ("%s\n\r",event);
            printf ("%f Reference: [min %f - max %f]\n\r",val,ref_min,ref_max);
            printf ("Reached min reference\n\r");
            break;
        case 4:
            printf ("%s\n\r",event);
            printf ("%f Reference: [min %f - max %f]\n\r",val,ref_min,ref_max);
            printf ("Reached max reference\n\r");
            break;
        default:
            break;
    }
    printf ("Deviation: %f\n\r",sd);
    if (ct == 1) {
        printf ("Detect changing trends: keep increasing\n\r");
    }else if (ct == 2) {
        printf ("Detect changing trends: keep decreasing\n\r");
    }
    printf ("\n\r");
}
