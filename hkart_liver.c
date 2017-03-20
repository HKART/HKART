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
