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


#endif /* HKART_DIABETES_H */
