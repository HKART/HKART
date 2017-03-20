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
#include "hkart_diabetes.h"
#include "hkart_kidney.h"
#include "hkart_liver.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void usage (void) {
    printf ("Please provide <name> <phone> <profile>\n\r");
    printf ("./hkart <name> <phone> <profile>\n\r");
    printf ("Example: ./hkart susobhan 9674465334 diabetes\n\r");
    printf ("Supported profiles are <diabetes>, <cardiac> <kidney> <liver>\n\r");
}


int main(int argc, char *argv[]) {

    if (argc <4) {
        usage ();
        exit (0);
    }
    int ret;
    if (!(strcmp(argv[3],"diabetes")))
        ret = ca_diabetes (argv[1],argv[2]);
    else if (!(strcmp(argv[3],"cardiac")))
        printf ("Not supported\n\r");
    else if (!(strcmp(argv[3],"kidney")))
        ret = ca_kidney (argv[1],argv[2]);
    else if (!(strcmp(argv[3],"liver")))
        ret = ca_liver (argv[1],argv[2]);
    else {
        printf ("profile not supported\n\r");
        usage ();
        exit (EXIT_FAILURE);
    }

    return ret;
}
