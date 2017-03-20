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
#define MAX_LIVER_TEST 9

liver_panel_ref_t ref_liver;

void fillup_liver_ref (liver_panel_ref_t *ref_liver,int age) {
    ref_liver->AST_SGOT_min = 5;
    ref_liver->AST_SGOT_max = 40;
    ref_liver->ALT_SGPT_min = 7;
    ref_liver->ALT_SGPT_max = 56;
    ref_liver->ALP_min = 44.0;
    ref_liver->ALP_max = 147.0;
    ref_liver->Protein_Total_min = 6.4;
    ref_liver->Protein_Total_max = 8.3;
    ref_liver->Albumin_min = 3.5;
    ref_liver->Albumin_max = 5.0;
    ref_liver->A_G_Ratio_min = 0.8;
    ref_liver->A_G_Ratio_max = 2.0;
    ref_liver->Bilirubin_Total_min = 0.3;
    ref_liver->Bilirubin_Total_max = 1.0;
    ref_liver->Bilirubin_Direct_min = 0.1;
    ref_liver->Bilirubin_Total_max = 0.3;
    ref_liver->Bilirubin_Indirect_min = 0.2;
    ref_liver->Bilirubin_Indirect_max = 0.7;
}
const char* getfield_liver(char* line, int num)
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
int parse_csv_liver (FILE *fp, users_t *usr) {
    char buf[100];
    uint8_t count = 0;
    while( fgets(buf,sizeof(buf),fp) != NULL)
    {
        int records = 1;
        if (count == MAX_VALID_RECORDS -1)
            break;
        for (;records <= MAX_LIVER_TEST; ++records) {
            char *tmp = strdup (buf);
            switch (records) {
                case 1:
                    usr->liver_report[count].AST_SGOT = atof(getfield_liver(tmp,records));
                    break;
                case 2:
                    usr->liver_report[count].ALT_SGPT = atof(getfield_liver(tmp,records));
                    break;
                case 3:
                    usr->liver_report[count].ALP = atof(getfield_liver(tmp,records));
                    break;
                case 4:
                    usr->liver_report[count].Bilirubin_Total = atof(getfield_liver(tmp,records));
                    break;
                case 5:
                    usr->liver_report[count].Bilirubin_Direct = atof(getfield_liver(tmp,records));
                    break;
                case 6:
                    usr->liver_report[count].Bilirubin_Indirect = atof(getfield_liver(tmp,records));
                    break;
                case 7:
                    usr->liver_report[count].Protein_Total = atof(getfield_liver(tmp,records));
                    break;
                case 8:
                    usr->liver_report[count].Albumin = atof(getfield_liver(tmp,records));
                    break;
                case 9:
                    usr->liver_report[count].A_G_Ratio = atof (getfield_liver(tmp,records));
                    break;
                default:
                    break;
            }
            free (tmp);
        }
        /* will go to the next records */
        count ++;
        usr->num_liver_records = count;
    }
}
/*
 * This function will check last records with standered reference
 * calculate the deviation with all pre-existing recorde
 * detect changing trends
 */
void liver_nail_down_predictions (liver_panel_ref_t *ref_liver, users_t *usr) {

    //TODO its not easy
    /* First check with the last records to make sure
     * nothing abnormal in last records
     */
    int num_records_liver = usr->num_liver_records;
    float data[MAX_VALID_RECORDS];
    int i = 0;
    int ret = 0;
    /* sd for AST SGOT */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].AST_SGOT;
    }
    float sd_AST_SGOT = calculateSD (data,num_records_liver);
    int ct_AST_SGOT = detect_changing_trends (data,num_records_liver);

    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->AST_SGOT_min,ref_liver->AST_SGOT_max,usr->liver_report[i-1].AST_SGOT);
    print_details_analysis (ret,usr->liver_report[i-1].AST_SGOT,
            ref_liver->AST_SGOT_min,ref_liver->AST_SGOT_max,sd_AST_SGOT,ct_AST_SGOT,"AST SGOT");

    /* sd for ALT_SGPT */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].ALT_SGPT;
    }
    float sd_ALT_SGPT = calculateSD (data,num_records_liver);
    int ct_ALT_SGPT = detect_changing_trends (data,num_records_liver);

    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->ALT_SGPT_min,ref_liver->ALT_SGPT_max,usr->liver_report[i-1].ALT_SGPT);
    print_details_analysis (ret,usr->liver_report[i-1].ALT_SGPT,
            ref_liver->ALT_SGPT_min,ref_liver->ALT_SGPT_max,sd_ALT_SGPT,ct_ALT_SGPT,"ALT SGPT");

    /* sd for ALP */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].ALP;
    }
    float sd_ALP = calculateSD(data,num_records_liver);
    int ct_ALP = detect_changing_trends (data,num_records_liver);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->ALP_min,ref_liver->ALP_max,usr->liver_report[i-1].ALP);
    print_details_analysis (ret,usr->liver_report[i-1].ALP,
            ref_liver->ALP_min,ref_liver->ALP_max,sd_ALP,ct_ALP,"ALP");

    /* sd for Bilirubin_Total */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].Bilirubin_Total;
    }
    float sd_Bilirubin_Total = calculateSD(data,num_records_liver);
    int ct_Bilirubin_Total = detect_changing_trends (data,num_records_liver);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->Bilirubin_Total_min,ref_liver->Bilirubin_Total_max,usr->liver_report[i-1].Bilirubin_Total);
    print_details_analysis (ret,usr->liver_report[i-1].Bilirubin_Total,
            ref_liver->Bilirubin_Total_min,ref_liver->Bilirubin_Total_max,sd_Bilirubin_Total,ct_Bilirubin_Total,"Bilirubin_Total");

    /* sd for Bilirubin_Direct */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].Bilirubin_Direct;
    }
    float sd_Bilirubin_Direct = calculateSD(data,num_records_liver);
    int ct_Bilirubin_Direct = detect_changing_trends (data,num_records_liver);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->Bilirubin_Direct_min,ref_liver->Bilirubin_Direct_max,usr->liver_report[i-1].Bilirubin_Direct);
    print_details_analysis (ret,usr->liver_report[i-1].Bilirubin_Direct,
            ref_liver->Bilirubin_Direct_min,ref_liver->Bilirubin_Direct_max,sd_Bilirubin_Direct,ct_Bilirubin_Direct,"Bilirubin_Direct");

    /* sd for Bilirubin_Indirect */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].Bilirubin_Indirect;
    }
    float sd_Bilirubin_Indirect = calculateSD(data,num_records_liver);
    int ct_Bilirubin_Indirect = detect_changing_trends (data,num_records_liver);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->Bilirubin_Indirect_min,ref_liver->Bilirubin_Indirect_max,usr->liver_report[i-1].Bilirubin_Indirect);
    print_details_analysis (ret,usr->liver_report[i-1].Bilirubin_Indirect,
            ref_liver->Bilirubin_Indirect_min,ref_liver->Bilirubin_Indirect_max,sd_Bilirubin_Indirect,ct_Bilirubin_Indirect,"Bilirubin_Indirect");

    /* sd for Protein_Total */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].Protein_Total;
    }
    float sd_Protein_Total = calculateSD(data,num_records_liver);
    int ct_Protein_Total = detect_changing_trends (data,num_records_liver);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->Protein_Total_min,ref_liver->Protein_Total_max,usr->liver_report[i-1].Protein_Total);
    print_details_analysis (ret,usr->liver_report[i-1].Protein_Total,
            ref_liver->Protein_Total_min,ref_liver->Protein_Total_max,sd_Protein_Total,ct_Protein_Total,"Protein_Total");

    /* sd for Albumin */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].Albumin;
    }
    float sd_Albumin = calculateSD(data,num_records_liver);
    int ct_Albumin = detect_changing_trends (data,num_records_liver);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->Albumin_min,ref_liver->Albumin_max,usr->liver_report[i-1].Albumin);
    print_details_analysis (ret,usr->liver_report[i-1].Albumin,
            ref_liver->Albumin_min,ref_liver->Albumin_max,sd_Albumin,ct_Albumin,"Albumin");


    /* sd for A:G Ratio */
    for (i = 0; i< num_records_liver; ++i)
    {
        data[i] = usr->liver_report[i].A_G_Ratio;
    }
    float sd_A_G_Ratio = calculateSD(data,num_records_liver);
    int ct_A_G_Ratio = detect_changing_trends (data,num_records_liver);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_liver->A_G_Ratio_min,ref_liver->A_G_Ratio_max,usr->liver_report[i-1].A_G_Ratio);
    print_details_analysis (ret,usr->liver_report[i-1].A_G_Ratio,
            ref_liver->A_G_Ratio_min,ref_liver->A_G_Ratio_max,sd_A_G_Ratio,ct_A_G_Ratio,"A_G_Ratio");


    return;
}
int ca_liver (char *name, char *phone) {
    users_t user;
    int i;
    FILE *fp = NULL;
    /* copy the user name & phone number */
    strncpy ((char *)user.name,name,MAX_NAME_STR);
    user.phone = atol (phone);

    char file_name[MAX_FILE_NAME];
    sprintf(file_name, "%s_%s_liver.csv", name,phone);
    /* open the patient csv file in read only mode */
    fp = fopen (file_name,"r");
    if (NULL == fp) {
        printf ("Unable to open %s",file_name);
        return -1; //error
    }
    fillup_liver_ref (&ref_liver, 0); //for now age is not in consideration
    parse_csv_liver (fp, &user);
    liver_nail_down_predictions (&ref_liver,&user);

    for (i = 1; i<= 14; ++i) {
        char str1[50];
        char str2[100] = "cat ";
        strcat (str2,file_name);
        sprintf (str1, " | cut -d ',' -f%d >tmp%d",i,i);
        strcat (str2,str1);
        system (str2);
    }

    char user_graph[100];
    char system_script [120] = "./script_liver.sh ";
    sprintf (user_graph, "%s_%s_liver.png",name,phone);
    strcat (system_script,user_graph);

    system(system_script);
    system ("rm -f tmp*");
    fclose (fp);
    return 0;
}
