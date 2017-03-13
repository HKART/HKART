/**
 * copyright HKART 2017
 * we are using Dr Lal Path Lab as our reference
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hkart_diabetes.h"

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
        printf ("Not supported, development is in progress\n\r");
    else if (!(strcmp(argv[3],"liver")))
        printf ("NA now, we are working on it\n\r");
    else {
        printf ("profile not supported\n\r");
        usage ();
        exit (EXIT_FAILURE);
    }

    return ret;
}
