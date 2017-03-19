#ifndef HKART_LIVER_H
#define HKART_LIVER_H

typedef struct liver_panel_s {
    /* unit U/L */
    float AST_SGOT; 
    float ALT_SGPT;
    float GGTP;
    float ALP; 
    /* unit mg/dl */
    float Bilirubin_Total;
    float Bilirubin_Direct; 
    float Bilirubin_Indirect;
    /* unit g/dl */
    float Protein_Total; 
    float Albumin;
    /* no unit */
    float A:G_Ratio;
}liver_panel_t;

typedef struct liver_panel_ref_s {
    /* unit U/L */
    float AST_SGOT_min; 
    float AST_SGOT_max; 
    float ALT_SGPT_min;
    float ALT_SGPT_max;
    float GGTP_min;
    float GGTP_max;
    float ALP_min; 
    float ALP_max; 
    /* unit mg/dl */
    float Bilirubin_Total_min;
    float Bilirubin_Total_max;
    float Bilirubin_Direct_min; 
    float Bilirubin_Direct_max; 
    float Bilirubin_Indirect_min;
    float Bilirubin_Indirect_max;
    /* unit g/dl */
    float Protein_Total_min; 
    float Protein_Total_max; 
    float Albumin_min;
    float Albumin_max;
    /* no unit */
    float A:G_Ratio_min;
    float A:G_Ratio_max;
}liver_panel_ref_t;

#endif /* HKART_LIVER_H */
