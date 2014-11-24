/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

draws a castle wall
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

/* declare methods here for testing flexibility */

/* Creates bricks using cube modules, color for the is chosen randomly from 
 * one of 4 colors of grey and brown. 
 */
static Module * genBrick(float x, float y, float z);
static Module * genBrick(float x, float y, float z){
	// set up fields
	Module *brick;
	Color ltGrey, grey, dkGrey, final, dkBrown1;
	int thickness, gen;
	// set up different grey colors for castle blocks
	color_set(&ltGrey, (float)(192/255.0), (float)(197/255.0), 
		(float)(186/255.0));
	color_set(&grey, (float)(164/255.0), (float)(168/255.0), 
		(float)(163/255.0));
	color_set(&dkGrey, (float)(118/255.0), (float)(126/255.0), 
		(float)(121/255.0));
	color_set(&dkBrown1, (float)(72/255.0), (float)(60/255.0), 
		(float)(50/255.0));
	color_set(&final, 1, 1, 1);

	// randomly generate a number between 0 and 3 inclusive
	gen = (int)(rand() % 3);
	// select fill color depending on gen
	if (gen == 0){
		color_copy(&final, &ltGrey);
	}
	if (gen == 1){
		color_copy(&final, &grey);
	}
	if (gen == 2){
		color_copy(&final, &dkGrey);
	}
	else{
		color_copy(&final, &dkBrown1);
	}

	// create modules
	brick = module_create();

	module_scale(brick, 1, 3, 1);
	module_rotateX(brick, 0, 1);
	module_translate(brick, x, y, z);
	module_color(brick, &final);
	module_cube(brick, 1);

	return((Module*)brick);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 500*2;
	const int cols = 560*2;
	Image *src;
	Module *bricks[60], *wall;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	int frame;
	char command[256];
	srand(time(NULL));

	// create drawstate + image
	ds = drawstate_create();
	src = image_create( rows, cols );

	// set up the view
	point_set3D( &(view.vrp), 0, 0, 0);
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 5;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

 	// create the animation by adjusting the gtm
	for(frame=0;frame<60;frame++) {
		char buffer[256];
		bricks[frame] = module_create();
		bricks[frame] = genBrick(frame, frame, frame);
		wall = module_create();

		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( bricks[frame], &vtm, &gtm, ds, NULL, src );

		// write out image
		sprintf(buffer, "wall-frame%03d.ppm", frame);
		image_write(src, buffer);
		sprintf(command, "convert -scale %03dx%03d wall-frame%03d.ppm wall-frame%03d.ppm", 
		cols/2, rows/2, frame, frame);
		system(command);
		// reset image
		image_reset(src);
	}

	// convert to gif
	printf("converting to gif...\n");
	system("convert -delay 2 -loop 0 wall-frame*.ppm wall.gif");
	printf("converted gif\n");
	// remove ppm files
	system("rm wall-frame*.ppm");
	printf("animating gif...\n");
	// animate gif
	system("animate wall.gif");

	// free drawstate, image, modules
	free(ds);
	image_free(src);
	for(frame=0;frame<60;frame++){
		module_delete(bricks[frame]);
	}

	return(0);
}