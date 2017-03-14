#ifndef HKART_KIDNEY_H
#define HKART_KIDNEY_H

typedef struct kidney_panel_s {
    /* unit mg/dl */
    float Glucose_Fasting; /* min 70.0 max 100.0 */
    float Urea; /* min 7.0 max 20.0 */
    float Creatinine; /* min 0.6 max 1.2 */
    float Uric_Acid; /* min 40.0 max 60.0 */
    float Calcium; /* min 8.5 max 10.2 */
    float Phosphorus; /* min 2.5 max 4.5 */ 
    /* unit mEq/L */
    float Sodium; /* min 135 max 145 */
    float Potassium; /* min 3.5 max 5.0 */
    float Chloride; /* min 96 max 106 */
    /* unit mmol/L */
    float Bicarbonate; /* 22 - 29 */
    /* unit U/L */
    float ALP; /* 44 to 147 */
    /* unit g/dl */
    float Protein_Total; /* 6.4-8.3 */
    float Albumin; /* 3.5-5.0 g/dL */
    /* ratio */
    float A_G_Ratio; /* 0.8-2.0 */
}kidney_panel_t;

typedef struct kidney_panel_ref_s {
    /* unit mg/dl */
    float Glucose_Fasting_min; /* min 70.0 max 100.0 */
    float Glucose_Fasting_max; /* min 70.0 max 100.0 */
    float Urea_min; /* min 7.0 max 20.0 */
    float Urea_max; /* min 7.0 max 20.0 */
    float Creatinine_min; /* min 0.6 max 1.2 */
    float Creatinine_max; /* min 0.6 max 1.2 */
    float Uric_Acid_min; /* min 40.0 max 60.0 */
    float Uric_Acid_max; /* min 40.0 max 60.0 */
    float Calcium_min; /* min 8.5 max 10.2 */
    float Calcium_max; /* min 8.5 max 10.2 */
    float Phosphorus_min; /* min 2.5 max 4.5 */ 
    float Phosphorus_max; /* min 2.5 max 4.5 */ 
    /* unit mEq/L */
    float Sodium_min; /* min 135 max 145 */
    float Sodium_max; /* min 135 max 145 */
    float Potassium_min; /* min 3.5 max 5.0 */
    float Potassium_max; /* min 3.5 max 5.0 */
    float Chloride_min; /* min 96 max 106 */
    float Chloride_max; /* min 96 max 106 */
    /* unit mmol/L */
    float Bicarbonate_min; /* 22 - 29 */
    float Bicarbonate_max; /* 22 - 29 */
    /* unit U/L */
    float ALP_min; /* 44 to 147 */
    float ALP_max; /* 44 to 147 */
    /* unit g/dl */
    float Protein_Total_min; /* 6.4-8.3 */
    float Protein_Total_max; /* 6.4-8.3 */
    float Albumin_min; /* 3.5-5.0 g/dL */
    float Albumin_max; /* 3.5-5.0 g/dL */
    /* ratio */
    float A_G_Ratio_min; /* 0.8-2.0 */
    float A_G_Ratio_max; /* 0.8-2.0 */
}kidney_panel_ref_t;

int ca_kidney (char *name , char *phone);
#endif /* HKART_KIDNEY_H */
