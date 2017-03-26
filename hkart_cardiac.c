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
#define MAX_CARDIAC_TEST 5

cardiac_panel_ref_t ref_cardiac;

/**
 * parse the csv file for a specific user
 * this function will fillup the patient records
 * looking at csv file for that user
 */
const char* getfield_cardiac(char* line, int num)
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
 * parsing logic, it will parse the csv file for cardiac
 * fillup the value for user
 * return 0 for success
 */
int parse_csv_cardiac (FILE *fp, users_t *usr) {
    char buf[100];
    uint8_t count = 0;
    while( fgets(buf,sizeof(buf),fp) != NULL)
    {
        int records = 1;
        if (count == MAX_VALID_RECORDS -1)
            break;
        for (;records <= MAX_CARDIAC_TEST; ++records) {
            char *tmp = strdup (buf);
            switch (records) {
                case 1:
                    usr->cardiac_report[count].Apolipoprotein_A1 = atof(getfield_cardiac(tmp,records));
                    break;
                case 2:
                    usr->cardiac_report[count].Apolipoprotein_B = atof(getfield_cardiac(tmp,records));
                    break;
                case 3:
                    usr->cardiac_report[count].Lipoprotein_A = atof(getfield_cardiac(tmp,records));
                    break;
                case 4:
                    usr->cardiac_report[count].S_Homocysteine = atof(getfield_cardiac(tmp,records));
                    break;
                case 5:
                    usr->cardiac_report[count].S_Fibrinogen = atof(getfield_cardiac(tmp,records));
                    break;
                default:
                    break;
            }
            free (tmp);
        }
        /* will go to the next records */
        count ++;
        usr->num_records_cardiac = count;
    }
}

/*
 * Fillup the standered reference value for cardiac panel
 * Taken reference value from Lal Path Lab
 * Thanks Lalpath lab for making it public
 */
void fill_up_cardiac_ref (cardiac_panel_ref_t *ref_cardiac, int age) {
    ref_cardiac->Apolipoprotein_A1_max = 120.0;
    ref_cardiac->Apolipoprotein_A1_min = 120.0; // lower that this will cause cardiovascular disease
    ref_cardiac->Apolipoprotein_B_max = 125;
    ref_cardiac->Apolipoprotein_A1_min = 40;
    ref_cardiac->Lipoprotein_A_max = 10; // the higher cardiovascular risk
    ref_cardiac->Lipoprotein_A_min = -1; // the lower the better
    ref_cardiac->S_Homocysteine_max = 15;// the higher the risk (kidney)
    ref_cardiac->S_Homocysteine_min = 4; // lower the better
    ref_cardiac->S_Fibrinogen_max = 400;
    ref_cardiac->S_Fibrinogen_min = 150;//lower that 100 is very risky

    return;
}

/*
 * This function will check last records with standered reference
 * calculate the deviation with all pre-existing recorde
 * detect changing trends
 */
void cardiac_nail_down_predictions (cardiac_panel_ref_t *ref_cardiac, users_t *usr) {

    //TODO its not easy
    /* First check with the last records to make sure
     * nothing abnormal in last records
     */
    int num_records_cardiac = usr->num_records_cardiac;
    float data[MAX_VALID_RECORDS];
    int i = 0;
    int ret = 0;
    /* sd for Apolipoprotein_A1 */
    for (i = 0; i< num_records_cardiac; ++i)
    {
        data[i] = usr->cardiac_report[i].Apolipoprotein_A1;
    }
    float sd_Apolipoprotein_A1 = calculateSD (data,num_records_cardiac);
    int ct_Apolipoprotein_A1 = detect_changing_trends (data,num_records_cardiac);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_cardiac->Apolipoprotein_A1_min,ref_cardiac->Apolipoprotein_A1_max,usr->cardiac_report[i-1].Apolipoprotein_A1);
    print_details_analysis (ret,usr->cardiac_report[i-1].Apolipoprotein_A1,
            ref_cardiac->Apolipoprotein_A1_min,ref_cardiac->Apolipoprotein_A1_max,sd_Apolipoprotein_A1,ct_Apolipoprotein_A1,"Apolipoprotein_A1");

    /* sd for Apolipoprotein_B */
    for (i = 0; i< num_records_cardiac; ++i)
    {
        data[i] = usr->cardiac_report[i].Apolipoprotein_B;
    }
    float sd_Apolipoprotein_B = calculateSD (data,num_records_cardiac);
    int ct_Apolipoprotein_B = detect_changing_trends (data,num_records_cardiac);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_cardiac->Apolipoprotein_B_min,ref_cardiac->Apolipoprotein_B_max,usr->cardiac_report[i-1].Apolipoprotein_B);
    print_details_analysis (ret,usr->cardiac_report[i-1].Apolipoprotein_B,
            ref_cardiac->Apolipoprotein_B_min,ref_cardiac->Apolipoprotein_B_max,sd_Apolipoprotein_B,ct_Apolipoprotein_B,"Apolipoprotein_B");

    /* sd for Lipoprotein_A */
    for (i = 0; i< num_records_cardiac; ++i)
    {
        data[i] = usr->cardiac_report[i].Lipoprotein_A;
    }
    float sd_Lipoprotein_A = calculateSD (data,num_records_cardiac);
    int ct_Lipoprotein_A = detect_changing_trends (data,num_records_cardiac);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_cardiac->Lipoprotein_A_min,ref_cardiac->Lipoprotein_A_max,usr->cardiac_report[i-1].Lipoprotein_A);
    print_details_analysis (ret,usr->cardiac_report[i-1].Lipoprotein_A,
            ref_cardiac->Lipoprotein_A_min,ref_cardiac->Lipoprotein_A_max,sd_Lipoprotein_A,ct_Lipoprotein_A,"Lipoprotein_A");

    /* sd for S_Homocysteine */
    for (i = 0; i< num_records_cardiac; ++i)
    {
        data[i] = usr->cardiac_report[i].S_Homocysteine;
    }
    float sd_S_Homocysteine = calculateSD(data,num_records_cardiac);
    int ct_S_Homocysteine = detect_changing_trends (data,num_records_cardiac);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_cardiac->S_Homocysteine_min,ref_cardiac->S_Homocysteine_max,usr->cardiac_report[i-1].S_Homocysteine);
    print_details_analysis (ret,usr->cardiac_report[i-1].S_Homocysteine,
            ref_cardiac->S_Homocysteine_min,ref_cardiac->S_Homocysteine_max,sd_S_Homocysteine,ct_S_Homocysteine,"S_Homocysteine");

    /* sd for S_Fibrinogen */
    for (i = 0; i< num_records_cardiac; ++i)
    {
        data[i] = usr->cardiac_report[i].S_Fibrinogen;
    }
    float sd_S_Fibrinogen = calculateSD(data,num_records_cardiac);
    int ct_S_Fibrinogen = detect_changing_trends (data,num_records_cardiac);
    /* check the latest records with ref value */
    ret = check_against_ref_value(ref_cardiac->S_Fibrinogen_min,ref_cardiac->S_Fibrinogen_max,usr->cardiac_report[i-1].S_Fibrinogen);
    print_details_analysis (ret,usr->cardiac_report[i-1].S_Fibrinogen,
            ref_cardiac->S_Fibrinogen_min,ref_cardiac->S_Fibrinogen_max,sd_S_Fibrinogen,ct_S_Fibrinogen,"S_Fibrinogen");
    return;
}

/*
 * comparative analysis for cardiac
 * parse the csv
 * fillup structure
 * calculate standered deviation (sd)
 * calculate changing trends (ct)
 * do comparative analysis
 * create graph
 */
int ca_cardiac (char *name , char *phone) {
    users_t user;
    int i;
    FILE *fp = NULL;
    /* copy the user name & phone number */
    strncpy ((char *)user.name,name,MAX_NAME_STR);
    user.phone = atol (phone);

    char file_name[MAX_FILE_NAME];
    sprintf(file_name, "%s_%s_cardiac.csv", name,phone);
    /* open the patient csv file in read only mode */
    fp = fopen (file_name,"r");
    if (NULL == fp) {
        printf ("Unable to open %s",file_name);
        return -1; //error
    }
    fill_up_cardiac_ref (&ref_cardiac, 0); //for now age is not in consideration
    parse_csv_cardiac (fp, &user);
    cardiac_nail_down_predictions (&ref_cardiac,&user);
    for (i = 1; i<= 10; ++i) {
        char str1[50];
        char str2[100] = "cat ";
        strcat (str2,file_name);
        sprintf (str1, " | cut -d ',' -f%d >tmp%d",i,i);
        strcat (str2,str1);
        system (str2);
    }

    char user_graph[100];
    char system_script [120] = "./script_cardiac.sh ";
    sprintf (user_graph, "%s_%s_cardiac.png",name,phone);
    strcat (system_script,user_graph);

    system(system_script);
    system ("rm -f tmp*");
    fclose (fp);
    return 0;
}
