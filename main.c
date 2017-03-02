#include <stdio.h>
#include <stdlib.h>
#include "users.h"

#define MAX_FILE_NAME 50

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void usage (void) {
	printf ("Please provide <name> <phone>\n\r");
	printf ("./hkart <name> <phone> \n\r");
}
int main(int argc, char *argv[]) {
	FILE *fp = NULL;
	printf("HKART\n\r");

	if (argc <3) {
		usage ();
		exit (0);
	}
	uint8_t file_name[MAX_FILE_NAME];
	sprintf(file_name, "%s_%s.csv", argv[1],argv[2]);
	/* open the patient csv file in read only mode */
	fp = fopen (file_name,"r");
	if (NULL == fp) {
		printf ("Unable to open %s",file_name);
		return -1; //error
	}
	
	return 0;//success
}
