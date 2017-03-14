#ifndef USER_H
#define USER_H

#include "hkart_diabetes.h"
#include "hkart_kidney.h"
#include <stdint.h>

typedef enum sex_s {
    MALE = 0,
    FEMALE = 1,
    INTERSEX = 2,
    SEX_MAX = 4
} sex_t;
#define MAX_NAME_STR 50
#define MAX_VALID_RECORDS 50

typedef struct users_s
{
    uint8_t ID;
    uint8_t name[MAX_NAME_STR];
    sex_t sex;
    uint64_t phone;
    /*TODO we are currently evaluating only diabetes */
    diabetes_panel_t diabetes_report[MAX_VALID_RECORDS];
    uint8_t num_records_diabetes;
    kidney_panel_t kidney_report[MAX_VALID_RECORDS];
    uint8_t num_kidney_records;
} users_t;


#endif /* USER_H */
