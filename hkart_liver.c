#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "math_work.h"
#include "hkart_common.h"

#define MAX_FILE_NAME 50
#define MAX_LIVER_TEST 10

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

int ca_liver (char *name, char *phone) {
    return 0;
}
