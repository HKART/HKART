/*
 * Copyright (C) 2017 Susobhan Dey(www.vcliniq.com)  All rights reserved.
 * 
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "math_work.h"
#include "hkart_common.h"

#define MAX_FILE_NAME 50
#define MAX_KIDNEY_TEST 14
kidney_panel_ref_t ref_kidney;

void fillup_kidney_ref (kidney_panel_ref_t *ref_kidney,int age) {
    ref_kidney->Glucose_Fasting_min = 70.0;
    ref_kidney->Glucose_Fasting_max = 100.0;
    ref_kidney->Urea_min = 7.0;
    ref_kidney->Urea_max = 20.0;
    ref_kidney->Creatinine_min = 0.6;
    ref_kidney->Creatinine_max = 1.2;
    ref_kidney->Uric_Acid_min = 3.4;
    ref_kidney->Uric_Acid_max = 7.2;
    ref_kidney->Calcium_min = 8.5;
    ref_kidney->Calcium_max = 10.2;
    ref_kidney->Phosphorus_min = 2.5;
    ref_kidney->Phosphorus_max = 4.5;
    ref_kidney->Sodium_min = 135.0;
    ref_kidney->Sodium_max = 145.0;
    ref_kidney->Potassium_min = 3.5;
    ref_kidney->Potassium_max = 5.0;
    ref_kidney->Chloride_min = 96.0;
    ref_kidney->Chloride_max = 106.0;
    ref_kidney->Bicarbonate_min = 22.0;
    ref_kidney->Bicarbonate_max = 29.0;
    ref_kidney->ALP_min = 44.0;
    ref_kidney->ALP_max = 147.0;
    ref_kidney->Protein_Total_min = 6.4;
    ref_kidney->Protein_Total_max = 8.3;
    ref_kidney->Albumin_min = 3.5;
    ref_kidney->Albumin_max = 5.0;
    ref_kidney->A_G_Ratio_min = 0.8;
    ref_kidney->A_G_Ratio_max = 2.0;
}
const char* getfield_kidney(char* line, int num)
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
/*
 * parsing logic, it will parse the csv file for diabetes
 * fillup the value for user
 * return 0 for success
 */
int parse_csv_kidney (FILE *fp, users_t *usr) {
    char buf[100];
    uint8_t count = 0;
    while( fgets(buf,sizeof(buf),fp) != NULL)
    {
        int records = 1;
        if (count == MAX_VALID_RECORDS -1)
            break;
        for (;records <= MAX_KIDNEY_TEST; ++records) {
            char *tmp = strdup (buf);
            switch (records) {
                case 1:
                    usr->kidney_report[count].Glucose_Fasting = atof(getfield_kidney(tmp,records));
                    break;
                case 2:
                    usr->kidney_report[count].Urea = atof(getfield_kidney(tmp,records));
                    break;
                case 3:
                    usr->kidney_report[count].Creatinine = atof(getfield_kidney(tmp,records));
                    break;
                case 4:
                    usr->kidney_report[count].Uric_Acid = atof(getfield_kidney(tmp,records));
                    break;
                case 5:
                    usr->kidney_report[count].Calcium = atof(getfield_kidney(tmp,records));
                    break;
                case 6:
                    usr->kidney_report[count].Phosphorus = atof(getfield_kidney(tmp,records));
                    break;
                case 7:
                    usr->kidney_report[count].Sodium = atof(getfield_kidney(tmp,records));
                    break;
                case 8:
                    usr->kidney_report[count].Potassium = atof(getfield_kidney(tmp,records));
                    break;
                case 9:
                    usr->kidney_report[count].Chloride = atof(getfield_kidney(tmp,records));
                    break;
                case 10:
                    usr->kidney_report[count].Bicarbonate = atof(getfield_kidney(tmp,records));
                    break;
                case 11:
                    usr->kidney_report[count].ALP = atof(getfield_kidney(tmp,records));
                    break;
                case 12:
                    usr->kidney_report[count].Protein_Total = atof(getfield_kidney(tmp,records));
                    break;
                case 13:
                    usr->kidney_report[count].Albumin = atof(getfield_kidney(tmp,records));
                    break;
                case 14:
                    usr->kidney_report[count].A_G_Ratio = atof (getfield_kidney(tmp,records));
                    break;
                default:
                    break;
            }
            free (tmp);
        }
        /* will go to the next records */
        count ++;
        usr->num_kidney_records = count;
    }
}

/*
 * This function will check last records with standered reference
 * calculate the deviation with all pre-existing recorde
 * detect changing trends
 */
void kidney_nail_down_predictions (kidney_panel_ref_t *ref_kidney, users_t *usr) {

    //TODO its not easy
    /* First check with the last records to make sure
     * nothing abnormal in last records
     */
    int num_records_kidney = usr->num_kidney_records;
    float data[MAX_VALID_RECORDS];
    int i = 0;
    int ret = 0;
    /* sd for Glucose_Fasting */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Glucose_Fasting;
    }
    float sd_Glucose_Fasting = calculateSD (data,num_records_kidney);
    int ct_Glucose_Fasting = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Glucose_Fasting_min,ref_kidney->Glucose_Fasting_max,usr->kidney_report[i-1].Glucose_Fasting);
    print_details_analysis (ret,usr->kidney_report[i-1].Glucose_Fasting,
            ref_kidney->Glucose_Fasting_min,ref_kidney->Glucose_Fasting_max,sd_Glucose_Fasting,ct_Glucose_Fasting,"Glucose_Fasting");

    /* sd for Urea */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Urea;
    }
    float sd_Urea = calculateSD (data,num_records_kidney);
    int ct_Urea = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Urea_min,ref_kidney->Urea_max,usr->kidney_report[i-1].Urea);
    print_details_analysis (ret,usr->kidney_report[i-1].Urea,
            ref_kidney->Urea_min,ref_kidney->Urea_max,sd_Urea,ct_Urea,"Urea");

    /* sd for Creatinine */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Creatinine;
    }
    float sd_Creatinine = calculateSD (data,num_records_kidney);
    int ct_Creatinine = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Creatinine_min,ref_kidney->Creatinine_max,usr->kidney_report[i-1].Creatinine);
    print_details_analysis (ret,usr->kidney_report[i-1].Creatinine,
            ref_kidney->Creatinine_min,ref_kidney->Creatinine_max,sd_Creatinine,ct_Creatinine,"Creatinine");

    /* sd for Uric_Acid */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Uric_Acid;
    }
    float sd_Uric_Acid = calculateSD(data,num_records_kidney);
    int ct_Uric_Acid = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Uric_Acid_min,ref_kidney->Uric_Acid_max,usr->kidney_report[i-1].Uric_Acid);
    print_details_analysis (ret,usr->kidney_report[i-1].Uric_Acid,
            ref_kidney->Uric_Acid_min,ref_kidney->Uric_Acid_max,sd_Uric_Acid,ct_Uric_Acid,"Uric_Acid");

    /* sd for Calcium */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Calcium;
    }
    float sd_Calcium = calculateSD(data,num_records_kidney);
    int ct_Calcium = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Calcium_min,ref_kidney->Calcium_max,usr->kidney_report[i-1].Calcium);
    print_details_analysis (ret,usr->kidney_report[i-1].Calcium,
            ref_kidney->Calcium_min,ref_kidney->Calcium_max,sd_Calcium,ct_Calcium,"Calcium");

    /* sd for Phosphorus */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Phosphorus;
    }
    float sd_Phosphorus = calculateSD(data,num_records_kidney);
    int ct_Phosphorus = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Phosphorus_min,ref_kidney->Phosphorus_max,usr->kidney_report[i-1].Phosphorus);
    print_details_analysis (ret,usr->kidney_report[i-1].Phosphorus,
            ref_kidney->Phosphorus_min,ref_kidney->Phosphorus_max,sd_Phosphorus,ct_Phosphorus,"Phosphorus");

    /* sd for Sodium */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Sodium;
    }
    float sd_Sodium = calculateSD(data,num_records_kidney);
    int ct_Sodium = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Sodium_min,ref_kidney->Sodium_max,usr->kidney_report[i-1].Sodium);
    print_details_analysis (ret,usr->kidney_report[i-1].Sodium,
            ref_kidney->Sodium_min,ref_kidney->Sodium_max,sd_Sodium,ct_Sodium,"Sodium");

    /* sd for Potassium */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Potassium;
    }
    float sd_Potassium = calculateSD(data,num_records_kidney);
    int ct_Potassium = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Potassium_min,ref_kidney->Potassium_max,usr->kidney_report[i-1].Potassium);
    print_details_analysis (ret,usr->kidney_report[i-1].Potassium,
            ref_kidney->Potassium_min,ref_kidney->Potassium_max,sd_Potassium,ct_Potassium,"Potassium");

    /* sd for Chloride */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Chloride;
    }
    float sd_Chloride = calculateSD(data,num_records_kidney);
    int ct_Chloride = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Chloride_min,ref_kidney->Chloride_max,usr->kidney_report[i-1].Chloride);
    print_details_analysis (ret,usr->kidney_report[i-1].Chloride,
            ref_kidney->Chloride_min,ref_kidney->Chloride_max,sd_Chloride,ct_Chloride,"Chloride");

    /* sd for Bicarbonate */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Bicarbonate;
    }
    float sd_Bicarbonate = calculateSD(data,num_records_kidney);
    int ct_Bicarbonate = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Bicarbonate_min,ref_kidney->Bicarbonate_max,usr->kidney_report[i-1].Bicarbonate);
    print_details_analysis (ret,usr->kidney_report[i-1].Bicarbonate,
            ref_kidney->Bicarbonate_min,ref_kidney->Bicarbonate_max,sd_Bicarbonate,ct_Bicarbonate,"Bicarbonate");

    /* sd for ALP */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].ALP;
    }
    float sd_ALP = calculateSD(data,num_records_kidney);
    int ct_ALP = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->ALP_min,ref_kidney->ALP_max,usr->kidney_report[i-1].ALP);
    print_details_analysis (ret,usr->kidney_report[i-1].ALP,
            ref_kidney->ALP_min,ref_kidney->ALP_max,sd_ALP,ct_ALP,"ALP");

    /* sd for Protein_Total */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Protein_Total;
    }
    float sd_Protein_Total = calculateSD(data,num_records_kidney);
    int ct_Protein_Total = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Protein_Total_min,ref_kidney->Protein_Total_max,usr->kidney_report[i-1].Protein_Total);
    print_details_analysis (ret,usr->kidney_report[i-1].Protein_Total,
            ref_kidney->Protein_Total_min,ref_kidney->Protein_Total_max,sd_Protein_Total,ct_Protein_Total,"Protein_Total");

    /* sd for Albumin */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].Albumin;
    }
    float sd_Albumin = calculateSD(data,num_records_kidney);
    int ct_Albumin = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->Albumin_min,ref_kidney->Albumin_max,usr->kidney_report[i-1].Albumin);
    print_details_analysis (ret,usr->kidney_report[i-1].Albumin,
            ref_kidney->Albumin_min,ref_kidney->Albumin_max,sd_Albumin,ct_Albumin,"Albumin");


    /* sd for A:G Ratio */
    for (i = 0; i< num_records_kidney; ++i)
    {
        data[i] = usr->kidney_report[i].A_G_Ratio;
    }
    float sd_A_G_Ratio = calculateSD(data,num_records_kidney);
    int ct_A_G_Ratio = detect_changing_trends (data,num_records_kidney);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_kidney->A_G_Ratio_min,ref_kidney->A_G_Ratio_max,usr->kidney_report[i-1].A_G_Ratio);
    print_details_analysis (ret,usr->kidney_report[i-1].A_G_Ratio,
            ref_kidney->A_G_Ratio_min,ref_kidney->A_G_Ratio_max,sd_A_G_Ratio,ct_A_G_Ratio,"A_G_Ratio");


    return;
}
int ca_kidney (char *name, char *phone) {
    users_t user;
    int i;
    FILE *fp = NULL;
    /* copy the user name & phone number */
    strncpy ((char *)user.name,name,MAX_NAME_STR);
    user.phone = atol (phone);

    char file_name[MAX_FILE_NAME];
    sprintf(file_name, "%s_%s_kidney.csv", name,phone);
    /* open the patient csv file in read only mode */
    fp = fopen (file_name,"r");
    if (NULL == fp) {
        printf ("Unable to open %s",file_name);
        return -1; //error
    }
    fillup_kidney_ref (&ref_kidney, 0); //for now age is not in consideration
    parse_csv_kidney (fp, &user);
    kidney_nail_down_predictions (&ref_kidney,&user);

    for (i = 1; i<= 14; ++i) {
        char str1[50];
        char str2[100] = "cat ";
        strcat (str2,file_name);
        sprintf (str1, " | cut -d ',' -f%d >tmp%d",i,i);
        strcat (str2,str1);
        system (str2);
    }

    char user_graph[100];
    char system_script [120] = "./script_kidney.sh ";
    sprintf (user_graph, "%s_%s_kidney.png",name,phone);
    strcat (system_script,user_graph);

    system(system_script);
    system ("rm -f tmp*");
    fclose (fp);
    return 0;
}
