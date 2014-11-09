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

/* Creates a flame using a bezier surface*/
static Module* genFire(float x, float y, float z, int divisions);
static Module* genFire(float x, float y, float z, int divisions){
	Module *f[20];
	Module *fire;
	BezierSurface bc;
	int gen, i;
	Color ltOrange, orange, dkOrange, red, yellow, amber, final, c[6];
	Point p[16];
	srand(time(NULL));
	color_set(&ltOrange, 1, (float)(167/255), 0);
	color_set(&orange, 1, (float)(127/255), 0);
	color_set(&dkOrange, 1, (float)(103/255), 0);
	color_set(&red, 1, 0, 0);
	color_set(&yellow, 1, (float)(233/255), 0);
	color_set(&amber, 1, (float)(191/255), 0);
	color_set(&final, 0, 0, 0);

	color_copy(&c[0], &ltOrange);
	color_copy(&c[1], &orange);
	color_copy(&c[2], &dkOrange);
	color_copy(&c[3], &red);
	color_copy(&c[4], &yellow);
	color_copy(&c[5], &amber);

	fire = module_create();

	// create a curved surface sitting above the plane
	point_set3D(&p[0], 0.0, 0.0, 0.0); // first row, constant x, even spacing in z
	point_set3D(&p[1], 0.0, 0.2, 0.33);
	point_set3D(&p[2], 0.0, 0.5, 0.66);
	point_set3D(&p[3], 0.0, 0.1, 1.0);
	point_set3D(&p[4], 0.33, 0.8, 0.0); // second row
	point_set3D(&p[5], 0.33, -0.1, 0.33);
	point_set3D(&p[6], 0.33, 0.0, 0.66);
	point_set3D(&p[7], 0.33, 0.3, 1.0);
	point_set3D(&p[8], 0.66, 0.3, 0.0); // third row
	point_set3D(&p[9], 0.66, 0.8, 0.33);
	point_set3D(&p[10], 0.66, 0.9, 0.66);
	point_set3D(&p[11], 0.66, 0.5, 1.0);
	point_set3D(&p[12], 1.0, 0.4, 0.0); // fourth row
	point_set3D(&p[13], 1.0, 0.2, 0.33);
	point_set3D(&p[14], 1.0, 0.5, 0.66);
	point_set3D(&p[15], 1.0, 1.0, 1.0);
	bezierSurface_set(&bc, p);

	for (i = 0; i < 20; i++){
		gen = (int)(rand() % 6);
		f[i] = module_create();
		module_scale(f[i], (float)((rand()%10)+5), (float)(rand()%30), (float)(rand()%20));
		module_translate(f[i], x+20, y, z);
		module_color(f[i], &c[((int)gen)]);
		module_bezierSurface(f[i], &bc, divisions, 1);
		module_module((Module*)fire, (Module*)f[i]);
	}

	printf("Creating flames with %d subdivisions\n", divisions);

	// this method may work for matrix rotation of gtm
	return((Module*)fire);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 600*2;
	const int cols = 660*2;
	Image *src;
	Module *flame;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	char command[256];
	float alpha;
	Color blue, green;
	int i;
	color_set(&blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);

	// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 20*alpha, alpha, -50*alpha - (alpha*170-cos(alpha)*170) );
    } else {
		point_set3D( &(view.vrp), 0, 0, -50);
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

 	flame = module_create();
 	flame = genFire(0, 0, 0, 4);

	color_set(&blue, 0, 0, 1);

	// create the image and drawstate
	src = image_create( rows, cols );
	image_fillColor(src, blue);
	ds = drawstate_create();
	ds->shade = ShadeConstant;
	printf("created the image and drawstate\n");

	// draw scene
	module_draw(flame, &vtm, &gtm, ds, NULL, src );
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
	module_delete(flame);

	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


