/*
  Ian Tibbetts
  Fall 2014

  Test function for 3D matrix viewing
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char *argv[]) {
	const int frames = 99;
	char command[1000];
	char filename[1000];
	int frame;
	  
	for(frame=0;frame<frames;frame++){
		sprintf(command,"../bin/threedpan 0.%02d",frame);
		system(command);
		sprintf(filename,"mv threedpan.ppm %03dthreedpan.ppm",frame);
		system(filename);
	}
	
	// shrinking back down to give continuous loop
	for(frame=frames-2;frame>-1;frame--){
		sprintf(command,"../bin/threedpan 0.%02d",frame);
		system(command);
		sprintf(filename,"mv threedpan.ppm %03dthreedpan.ppm",200-frame);
		system(filename);
	}
	
	printf("converting to gif...\n");
	system("convert -delay 1.5 -loop 0 *threedpan.ppm threedpan.gif");
	system("rm *threedpan.ppm");
	system("animate threedpan.gif");
	return(0);
}
