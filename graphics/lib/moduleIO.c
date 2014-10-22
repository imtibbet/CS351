// These functions read and write text files defining modules for graphics heirarchies
// Ian Tibbetts and Astrid Moore
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

// read in rgb values from the ppm file output by cqcam
int genModule(char *infilename, char *outfilename) {
	FILE *infile, *outfile;
	char buf[1000];
	char *codeline;

	// open input file for reading
	infile =fopen(infilename,"r");
	if (!infile){
		printf("%s did not open for reading properly\n",infilename);
		return 0;
	}

	// open ouput file for writing
	outfile =fopen(outfilename,"w");
	if (!infile){
		printf("%s did not open for writing properly\n",outfilename);
		fclose(infile);
		return 0;
	}

	// loop until EOF is reached
	while (fgets(buf,1000, infile)!=NULL){
		printf("%s\n", buf);
		if(strcmp(buf, "begin module") == 0){
			codeline = "create module";
		}
		fprintf(outfile, "%s\n", codeline);
	}

	fclose(infile);
	fclose(outfile);
	return 1;
}

