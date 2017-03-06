/**
 * copyright HKART 2017
 * we are using Dr Lal Path Lab as our reference
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "math_work.h"

#define MAX_FILE_NAME 50
#define MAX_DIABETES_TEST 10

diabetes_panel_ref_t ref_diabetes;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void usage (void) {
    printf ("Please provide <name> <phone>\n\r");
    printf ("./hkart <name> <phone> \n\r");
}

/**
 * parse the csv file for a specific user
 * this function will fillup the patient records
 * looking at csv file for that user
 */
const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
int parse_csv_diabetes (FILE *fp, users_t *usr) {
    char buf[100];
    uint8_t count = 0;
    while( fgets(buf,sizeof(buf),fp) != NULL)
    {
        int records = 1;
        if (count == MAX_VALID_RECORDS -1)
            break;
        for (;records <= MAX_DIABETES_TEST; ++records) {
            char *tmp = strdup (buf);
            switch (records) {
                case 1:
                    usr->diabetes_report[count].Glucose_Fasting = atof(getfield(tmp,records));
                    break;
                case 2:
                    usr->diabetes_report[count].Glucose_PP = atof(getfield(tmp,records));
                    break;
                case 3:
                    usr->diabetes_report[count].Cholesterol_Total = atof(getfield(tmp,records));
                    break;
                case 4:
                    usr->diabetes_report[count].Triglycerides = atof(getfield(tmp,records));
                    break;
                case 5:
                    usr->diabetes_report[count].HDL_Cholesterol = atof(getfield(tmp,records));
                    break;
                case 6:
                    usr->diabetes_report[count].LDL_Cholesterol = atof(getfield(tmp,records));
                    break;
                case 7:
                    usr->diabetes_report[count].Uric_Acid = atof(getfield(tmp,records));
                    break;
                case 8:
                    usr->diabetes_report[count].Creatinine = atof(getfield(tmp,records));
                    break;
                case 9:
                    usr->diabetes_report[count].HbA1c = atof(getfield(tmp,records));
                    break;
                case 10:
                    usr->diabetes_report[count].Microalbumin_Urine = atof(getfield(tmp,records));
                    break;
                default:
                    break;
            }
            free (tmp);
        }
        /* will go to the next records */
        count ++;
        usr->num_records = count;
    }
}
/* Helper function to print a record */
void print_diabetes_user_records (int record_num, users_t *usr) {
    if ((record_num > (MAX_VALID_RECORDS -1)) || (record_num < 0)) {
        printf ("Invalid record number %d\n\r",record_num);
        return;
    }

    printf ("%f %f %f %f %f %f %f %f %f %f \n\r",usr->diabetes_report[record_num].Glucose_Fasting,
            usr->diabetes_report[record_num].Glucose_PP,
            usr->diabetes_report[record_num].Cholesterol_Total,
            usr->diabetes_report[record_num].Triglycerides,
            usr->diabetes_report[record_num].HDL_Cholesterol,
            usr->diabetes_report[record_num].LDL_Cholesterol,
            usr->diabetes_report[record_num].Uric_Acid,
            usr->diabetes_report[record_num].Creatinine,
            usr->diabetes_report[record_num].HbA1c,
            usr->diabetes_report[record_num].Microalbumin_Urine);
}

void fill_up_diabetes_ref (diabetes_panel_ref_t *ref_diabetes, int age) {
    ref_diabetes->Glucose_Fasting_min = 70.0;
    ref_diabetes->Glucose_Fasting_max = 100.0;
    ref_diabetes->Glucose_PP_min = 70.0;
    ref_diabetes->Glucose_PP_max = 140.0;
    ref_diabetes->Uric_Acid_min = 40.0;
    ref_diabetes->Uric_Acid_max = 60.0;
    ref_diabetes->Microalbumin_Urine_min = -1.0; //Not Applicable
    ref_diabetes->Microalbumin_Urine_max = 30.0;
    ref_diabetes->HbA1c_min = 4.0;
    ref_diabetes->HbA1c_max = 6.0;
    ref_diabetes->Cholesterol_Total_min = -1.0; //N/A
    ref_diabetes->Cholesterol_Total_max = 200.0;
    ref_diabetes->Triglycerides_min = -1; //N/A
    ref_diabetes->Triglycerides_max = 150.0;
    ref_diabetes->LDL_Cholesterol_min = -1.0; // N/A
    ref_diabetes->LDL_Cholesterol_max = 100.0;
    ref_diabetes->HDL_Cholesterol_min = 40.0; //Major risk cardiac attack
    ref_diabetes->HDL_Cholesterol_max = 60.0; // The higher the better
    ref_diabetes->Creatinine_min = 0.6;
    ref_diabetes->Creatinine_max = 1.2;

    return;
}

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
void print_details_analysis (int ret,float val,float ref_min,float ref_max,float sd ,char event[120]) {
    switch (ret) {
        case 0:
            printf ("%s :Your Value - %f Reference - [ min %f - max %f ]",event,val,ref_min,ref_max);
            break;
        case 1:
            printf ("!!! Attention : abnormality seen in %s \n\r",event);
            printf ("%s : Your Value - [%f] Reference - [ min %f - max %f ]",event,val,ref_min,ref_max);
            break;
        case 2:
            printf ("!!! Attention : abnormality seen in %s \n\r",event);
            printf ("%s : Your Value - [%f] Reference - [ min %f - max %f ]",event,val,ref_min,ref_max);
            break;
        case 3:
            printf ("!!! Attention : reached the min reference value %s \n\r",event);
            printf ("%s : Your Value - [%f] Reference - [ min %f - max %f ]",event,val,ref_min,ref_max);
            break;
        case 4:
            printf ("!!! Attention : reached the max reference value %s \n\r",event);
            printf ("%s : Your Value - [%f] Reference - [ min %f - max %f ]",event,val,ref_min,ref_max);
            break;
        default:
            break;
    }
    printf ("\n\r");
    printf ("Deviation of %s --> %f\n\r",event,sd);
}

void nail_down_predictions (diabetes_panel_ref_t *ref_diabetes, users_t *usr) {

    //TODO its not easy
    /* First check with the last records to make sure
     * nothing abnormal in last records
     */
    int num_records = usr->num_records;
    float data[MAX_VALID_RECORDS];
    int i = 0;
    int ret = 0;
    /* sd for Glucose_Fasting */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].Glucose_Fasting;
    }
    float sd_Glucose_Fasting = calculateSD (data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->Glucose_Fasting_min,ref_diabetes->Glucose_Fasting_max,usr->diabetes_report[i-1].Glucose_Fasting);
    print_details_analysis (ret,usr->diabetes_report[i-1].Glucose_Fasting,
            ref_diabetes->Glucose_Fasting_min,ref_diabetes->Glucose_Fasting_max,sd_Glucose_Fasting,"Glucose_Fasting");

    /* sd for Glucose_PP */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].Glucose_PP;
    }
    float sd_Glucose_PP = calculateSD (data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->Glucose_PP_min,ref_diabetes->Glucose_PP_max,usr->diabetes_report[i-1].Glucose_PP);
    print_details_analysis (ret,usr->diabetes_report[i-1].Glucose_PP,
            ref_diabetes->Glucose_PP_min,ref_diabetes->Glucose_PP_max,sd_Glucose_PP,"Glucose_PP");

    /* sd for Cholesterol_Total */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].Cholesterol_Total;
    }
    float sd_Cholesterol_Total = calculateSD (data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->Cholesterol_Total_min,ref_diabetes->Cholesterol_Total_max,usr->diabetes_report[i-1].Cholesterol_Total);
    print_details_analysis (ret,usr->diabetes_report[i-1].Cholesterol_Total,
            ref_diabetes->Cholesterol_Total_min,ref_diabetes->Cholesterol_Total_max,sd_Cholesterol_Total,"Cholesterol_Total");

    /* sd for Triglycerides */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].Triglycerides;
    }
    float sd_Triglycerides = calculateSD(data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->Triglycerides_min,ref_diabetes->Triglycerides_max,usr->diabetes_report[i-1].Triglycerides);
    print_details_analysis (ret,usr->diabetes_report[i-1].Triglycerides,
            ref_diabetes->Triglycerides_min,ref_diabetes->Triglycerides_max,sd_Triglycerides,"Triglycerides");

    /* sd for HDL_Cholesterol */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].HDL_Cholesterol;
    }
    float sd_HDL_Cholesterol = calculateSD(data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->HDL_Cholesterol_min,ref_diabetes->HDL_Cholesterol_max,usr->diabetes_report[i-1].HDL_Cholesterol);
    print_details_analysis (ret,usr->diabetes_report[i-1].HDL_Cholesterol,
            ref_diabetes->HDL_Cholesterol_min,ref_diabetes->HDL_Cholesterol_max,sd_HDL_Cholesterol,"HDL_Cholesterol");

    /* sd for LDL_Cholesterol */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].LDL_Cholesterol;
    }
    float sd_LDL_Cholesterol = calculateSD(data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->LDL_Cholesterol_min,ref_diabetes->LDL_Cholesterol_max,usr->diabetes_report[i-1].LDL_Cholesterol);
    print_details_analysis (ret,usr->diabetes_report[i-1].LDL_Cholesterol,
            ref_diabetes->LDL_Cholesterol_min,ref_diabetes->LDL_Cholesterol_max,sd_LDL_Cholesterol,"LDL_Cholesterol");

    /* sd for Uric_Acid */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].Uric_Acid;
    }
    float sd_Uric_Acid = calculateSD(data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->Uric_Acid_min,ref_diabetes->Uric_Acid_max,usr->diabetes_report[i-1].Uric_Acid);
    print_details_analysis (ret,usr->diabetes_report[i-1].Uric_Acid,
            ref_diabetes->Uric_Acid_min,ref_diabetes->Uric_Acid_max,sd_Uric_Acid,"Uric_Acid");

    /* sd for Creatinine */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].Creatinine;
    }
    float sd_Creatinine = calculateSD(data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->Creatinine_min,ref_diabetes->Creatinine_max,usr->diabetes_report[i-1].Creatinine);
    print_details_analysis (ret,usr->diabetes_report[i-1].Creatinine,
            ref_diabetes->Creatinine_min,ref_diabetes->Creatinine_max,sd_Creatinine,"Creatinine");

    /* sd for HbA1c VVIP Need to handle very carefully */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].HbA1c;
    }
    float sd_HbA1c = calculateSD(data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->HbA1c_min,ref_diabetes->HbA1c_max,usr->diabetes_report[i-1].HbA1c);
    print_details_analysis (ret,usr->diabetes_report[i-1].HbA1c,
            ref_diabetes->HbA1c_min,ref_diabetes->HbA1c_max,sd_HbA1c,"HbA1c");

    /* sd for Microalbumin_Urine */
    for (i = 0; i< num_records; ++i)
    {
        data[i] = usr->diabetes_report[i].Microalbumin_Urine;
    }
    float sd_Microalbumin_Urine = calculateSD(data,num_records);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_diabetes->Microalbumin_Urine_min,ref_diabetes->Microalbumin_Urine_max,usr->diabetes_report[i-1].Microalbumin_Urine);
    print_details_analysis (ret,usr->diabetes_report[i-1].Microalbumin_Urine,
            ref_diabetes->Microalbumin_Urine_min,ref_diabetes->Microalbumin_Urine_max,sd_Microalbumin_Urine,"Microalbumin_Urine");

    return;
}

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    users_t user;

    if (argc <3) {
        usage ();
        exit (0);
    }
    /* copy the user name & phone number */
    strncpy ((char *)user.name,argv[1],MAX_NAME_STR);
    user.phone = atol (argv[2]);
    printf ("##### Welcome %s #####\n\r",user.name);

    char file_name[MAX_FILE_NAME];
    sprintf(file_name, "%s_%s.csv", argv[1],argv[2]);
    /* open the patient csv file in read only mode */
    fp = fopen (file_name,"r");
    if (NULL == fp) {
        printf ("Unable to open %s",file_name);
        return -1; //error
    }
    fill_up_diabetes_ref (&ref_diabetes, 0); //for now age is not in consideration
    parse_csv_diabetes (fp, &user);
    nail_down_predictions (&ref_diabetes,&user);
    fclose (fp);
    return 0;//success
}
