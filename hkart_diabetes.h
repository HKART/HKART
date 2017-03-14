#ifndef HKART_DIABETES_H
#define HKART_DIABETES_H

typedef struct diabetes_panel_s {
    /* unit mg/dl */
    float Glucose_Fasting;
    float Glucose_PP;
    float Cholesterol_Total; 
    float Triglycerides;
    float HDL_Cholesterol; 
    float LDL_Cholesterol; 
    float Uric_Acid; 
    float Creatinine; 
    /* unit % */
    float HbA1c; 
    /* mg/g Creatinine */
    float Microalbumin_Urine; 
}diabetes_panel_t;

typedef struct diabetes_panel_ref_s {
    float Glucose_Fasting_min;
    float Glucose_Fasting_max;
    float Glucose_PP_min;
    float Glucose_PP_max;
    float Cholesterol_Total_min;
    float Cholesterol_Total_max;
    float Triglycerides_min;
    float Triglycerides_max;
    float HDL_Cholesterol_min;
    float HDL_Cholesterol_max;
    float LDL_Cholesterol_min;
    float LDL_Cholesterol_max;
    float Uric_Acid_min;
    float Uric_Acid_max;
    float Creatinine_min;
    float Creatinine_max;
    float HbA1c_min;
    float HbA1c_max;
    float Microalbumin_Urine_min;
    float Microalbumin_Urine_max;
} diabetes_panel_ref_t;

int ca_diabetes (char *name, char *phone);
   

#endif /* HKART_DIABETES_H */
