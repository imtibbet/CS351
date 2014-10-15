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
	const int frames = 200;
	char command[256];
	char filename[256];
	int frame, zoom;
	  
	for(frame=0;frame<frames/2;frame++){
		sprintf(command,"../bin/threedpan 0.%02d",100-frame);
		system(command);
		sprintf(filename,"mv threedpan.ppm %03dthreedpan.ppm",frame);
		system(filename);
	}
	
	// shrinking back down to give continuous loop
	for(zoom=frames/2;zoom<frames;zoom++){
		sprintf(command,"../bin/threedpan 0.0 %02f",
				1.0+10.0*(zoom-frames/2)/(frames/2)); 
				//0.0+360.0*(zoom-frames/2)/(frames/2));
		system(command);
		sprintf(filename,"mv threedpan.ppm %03dthreedpan.ppm",zoom);
		system(filename);
	}
	
	printf("converting to gif...\n");
	system("convert -delay 1.5 -loop 0 *threedpan.ppm threedpan.gif");
	system("rm *threedpan.ppm");
	system("animate threedpan.gif");
	return(0);
}
