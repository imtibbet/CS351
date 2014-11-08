/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

draws a fire
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

/* declare methods here for testing flexibility */

/* Creates a pile of logs, limited to a maximum of five logs along
 * the bottom. Returns a module of logs.
 */
static Module * genWood(float x, float y, float z);
static Module * genWood(float x, float y, float z){
	Module *wood, *outline, *woodpile;
	Color brown0, brown1, dkBrown0, dkBrown1, final, outlineC;
	int thickness, gen;
	srand(time(NULL));
	color_set(&brown0, (float)(123/255.0), (float)(63/255.0), 0.0);
	color_set(&brown1, (float)(112/255.0), (float)(66/255.0), (float)(20/255.0));
	color_set(&dkBrown0, (float)(101/255.0), (float)(67/255.0), (float)(33/255.0));
	color_set(&dkBrown1, (float)(72/255.0), (float)(60/255.0), (float)(50/255.0));
	color_set(&final, 0, 0, 0);

	gen = (int)(rand() % 3);
	if (gen == 0){
		color_copy(&final, &brown0);
		color_copy(&outlineC, &dkBrown0);
	}
	if (gen == 1){
		color_copy(&final, &brown1);
		color_copy(&outlineC, &dkBrown1);
	}
	if (gen == 2){
		color_copy(&final, &dkBrown0);
		color_copy(&outlineC, &brown0);
	}
	else{
		color_copy(&final, &dkBrown1);
		color_copy(&outlineC, &brown1);
	}

	wood = module_create();
	woodpile = module_create();
	outline = module_create();

	thickness = 10;

	module_scale(wood, 1, 4, 1);
	module_rotateX(wood, 0, 1);
	module_translate(wood, x, y, z);
	module_color(wood, &final);
	module_cylinder(wood, 20, 1, thickness, 0, 0, 0);
	module_module(woodpile, wood);

	module_scale(outline, 1, 4, 1);
	module_rotateX(outline, 0, 1);
	module_translate(outline, x, y, z);
	module_color(outline, &outlineC);
	module_cylinder(outline, 20, 0, thickness, 0, 0, 0);
	module_module(woodpile, outline);

	printf("added wood\n");

	return((Module*)woodpile);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 600*2;
	const int cols = 660*2;
	Image *src;
	Module *woodpile, *fireside;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	char command[256];
	float alpha;
	Color blue, green;
	color_set(&blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);

	fireside = module_create();

	// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 40*alpha, 140*alpha, -170*alpha - (alpha*170-cos(alpha)*170) );
    } else {
		point_set3D( &(view.vrp), 0, 0, -170 );
    }

	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 8;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

 	woodpile = module_create();
 	woodpile = genWood(0, 0, 0);
 	module_module(fireside, woodpile);
 	woodpile = module_create();
 	woodpile = genWood(2, 0, 0);
 	module_module(fireside, woodpile);
 	woodpile = module_create();
 	woodpile = genWood(4, 0, 0);
 	module_module(fireside, woodpile);
 	woodpile = module_create();
 	woodpile = genWood(-2, 0, 0);
 	module_module(fireside, woodpile);
 	woodpile = module_create();
 	woodpile = genWood(-1, 1.5, 0);
 	module_module(fireside, woodpile);
 	woodpile = module_create();
 	woodpile = genWood(1, 1.5, 0);
 	module_module(fireside, woodpile);
 	woodpile = module_create();
 	woodpile = genWood(3, 1.5, 0);
 	module_module(fireside, woodpile);
 	woodpile = module_create();
 	woodpile = genWood(2, 3, 0);
 	module_module(fireside, woodpile);
 	woodpile = module_create();
 	woodpile = genWood(0, 3, 0);
 	module_module(fireside, woodpile);

	color_set(&blue, 0, 0, 1);

	// create the image and drawstate
	src = image_create( rows, cols );
	image_fillColor(src, blue);
	ds = drawstate_create();
	ds->shade = ShadeConstant;
	printf("created the image and drawstate\n");

	// draw scene
	module_draw(fireside, &vtm, &gtm, ds, NULL, src );
	printf("drew the scene\n");

	// write out the scene
	printf("Writing image\n");
	image_write( src, "fire.ppm" );
	sprintf(command, "convert -scale %03dx%03d fire.ppm fire.ppm", cols/2, rows/2);
	system(command);

	// free the polygon data
	polygon_clear( &p );
	printf("polygon freed\n");

	// free the modules
	module_delete(woodpile);

	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


