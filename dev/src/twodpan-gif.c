/*
  Ian Tibbetts
  Fall 2014

  2D view - batman
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char *argv[]) {
	const int frames = 150;
	char command[256];
	char filename[256];
	int frame;
	float vrpx = 0.0; 
	float vrpy = 0.0;
	float vdx = 10.0;
	float va = 0.0;
	  
	for(frame=0;frame<frames;frame++){

		// translate the view across the scene
		if(frame < (frames-frames/10)){
			vrpx = 0.0 - 15.0*frame/frames;
			vrpy = 0.0 + 8.0*frame/frames;
		} else { // spin and zoom on bat symbol at the end
			vdx = 10.0 - 9.0*(frame-(frames-frames/10))/(frames/10);
			va = 0.0 + 360*(frame-(frames-frames/10))/(frames/10);
		}
		sprintf(command,"../bin/twodpan %02f %02f %02f %02f", vrpx, vrpy, vdx, va);
		system(command);
		sprintf(filename,"mv twodpan.ppm %03dtwodpan.ppm",frame);
		system(filename);
	}
	
	printf("converting to gif...\n");
	system("convert -delay 5 -loop 0 *twodpan.ppm twodpan.gif");
	system("rm *twodpan.ppm");
	system("animate twodpan.gif");
	return(0);
}
