#ifndef HKART_LIVER_H
#define HKART_LIVER_H

typedef struct liver_panel_s {
    /* unit U/L */
    float AST_SGOT; 
    float ALT_SGPT;
    float ALP; 
    /* unit mg/dl */
    float Bilirubin_Total;
    float Bilirubin_Direct; 
    float Bilirubin_Indirect;
    /* unit g/dl */
    float Protein_Total; 
    float Albumin;
    /* no unit */
    float A_G_Ratio;
}liver_panel_t;

typedef struct liver_panel_ref_s {
    /* unit U/L */
    float AST_SGOT_min; /* 5 to 40 U/L */ 
    float AST_SGOT_max; 
    float ALT_SGPT_min; /* 7 to 56 U/L */
    float ALT_SGPT_max;
    float ALP_min; /* 44 to 147 */
    float ALP_max; 
    /* unit mg/dl */
    float Bilirubin_Total_min; /* 0.3 to 1.0 mg/dL */
    float Bilirubin_Total_max;
    float Bilirubin_Direct_min; 
    float Bilirubin_Direct_max; /* 0.1 to 0.3 mg/dL */
    float Bilirubin_Indirect_min; /* 0.2–0.7 mg/dL */
    float Bilirubin_Indirect_max;
    /* unit g/dl */
    float Protein_Total_min; /* 6.4-8.3 */
    float Protein_Total_max; 
    float Albumin_min; /* 3.5-5.0 g/dL */
    float Albumin_max;
    /* no unit */
    float A_G_Ratio_min;/* 0.8-2.0*/
    float A_G_Ratio_max;
}liver_panel_ref_t;

int ca_liver (char *name, char *phone);
#endif /* HKART_LIVER_H */
