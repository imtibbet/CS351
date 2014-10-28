/*
  Astrid Moore
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
		sprintf(command,"../bin/city 0.%02d",frame);
		system(command);
		sprintf(filename,"mv city.ppm %03dcity.ppm",frame);
		system(filename);
	}
	
	// shrinking back down to give continuous loop
	for(frame=frames-5; frame>-1; frame--){
		sprintf(command,"../bin/city 0.%02d", frame);
		system(command);
		sprintf(filename,"mv city.ppm %03dcity.ppm", 200-frame);
		system(filename);
	}

	printf("converting to gif...\n");
	system("convert -delay 1.5 -loop 0 *city.ppm city.gif");
	system("rm *city.ppm");
	system("animate city.gif");
	return(0);
}
