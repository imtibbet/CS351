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
	char command[1000];
	char filename[1000];
	int frames = 99;
	int frame;
	  
	for(frame=0;frame<frames;frame++){
		sprintf(command,"../bin/3dreq 0.%02d",frame);
		system(command);
		sprintf(filename,"mv pyramid.ppm %03dpyramid.ppm",frame);
		system(filename);
	}
	
	// shrinking back down to give continuous loop
	for(frame=frames-2;frame>-1;frame--){
		sprintf(command,"../bin/3dreq 0.%02d",frame);
		system(command);
		sprintf(filename,"mv pyramid.ppm %03dpyramid.ppm",200-frame);
		system(filename);
	}
	
	printf("converting to gif...\n");
	system("convert -delay 1.5 -loop 0 *pyramid.ppm pyramid.gif");
	system("rm *pyramid.ppm");
	system("animate pyramid.gif");
	return(0);
}
