#ifndef HKART_CARDIAC_H
#define HKART_CARDIAC_H

typedef struct cardiac_panel_s {
    float Apolipoprotein_A1;
    float Apolipoprotein_B;
    float Homocysteine;
    float Lipoprotein_A;
    float S_Homocysteine;
    float S_Fibrinogen;
}cardiac_panel_t;

typedef struct cardiac_panel_ref_s {
    float Apolipoprotein_A1_min;
    float Apolipoprotein_A1_max;
    float Apolipoprotein_B_min;
    float Apolipoprotein_B_max;
    float Homocysteine_min;
    float Homocysteine_max;
    float Lipoprotein_A_min;
    float Lipoprotein_A_max;
    float S_Homocysteine_min;
    float S_Homocysteine_max;
    float S_Fibrinogen_min;
    float S_Fibrinogen_max;
}cardiac_panel_ref_t;

#endif /*HKART_CARDIAC_H*/
