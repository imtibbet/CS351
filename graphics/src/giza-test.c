/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

Draws a city with 3 different kinds of buildings
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

static Module* pyramid(int size, float x, float y, float z);
static Module* pyramid(int size, float x, float y, float z){
	Color dark_sand = {{0.65, 0.47, 0.22}};
	Polygon side[5];
	Polygon tpoly;
	Point tv[4];
    Point v[8];
   	Module *pyra;
    int i;

	// initialize polygons
    for(i=0;i<5;i++) {
        polygon_init( &side[i] );
    }

    // corners of a pyramid, centered at (0, 0, 0)
    point_set3D(&v[0], -1, -1, -1 );
    point_set3D(&v[1],  1, -1, -1 );
    point_set3D(&v[2],  1,  -1, 1 );
    point_set3D(&v[3], -1,  -1, 1 );
    point_set3D(&v[4], 0, 0, 0);

    // front side
    point_copy(&tv[0], &v[0]);
    point_copy(&tv[1], &v[1]);
    point_copy(&tv[2], &v[4]);
    polygon_set(&side[0], 3, tv);

    // back side
    point_copy(&tv[0], &v[3]);
    point_copy(&tv[1], &v[2]);
    point_copy(&tv[2], &v[4]);
    polygon_set(&side[1], 3, tv);

    // bottom side
    polygon_set(&side[2], 4, &(v[0]));

    // left side
    point_copy(&tv[0], &v[0]);
    point_copy(&tv[1], &v[3]);
    point_copy(&tv[2], &v[4]);
    polygon_set(&side[3], 3, tv);

    // right side
    point_copy(&tv[0], &v[1]);
    point_copy(&tv[1], &v[2]);
    point_copy(&tv[2], &v[4]);
    polygon_set(&side[4], 3, tv); 

    pyra = module_create();
    module_scale(pyra, (int)size, (int)size, (int)size);
    module_translate(pyra, (float)x, (float)y, (float)z);

    for( i = 0; i<5; i++){
    	polygon_copy(&tpoly, &side[i]);
    	module_polygon(pyra, &tpoly);
    }

    return(pyra);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 600*2;
	const int cols = 660*2;
	Image *src;
	int i;
	Module *giza, *khuf, *khaf, *menk;
	Polygon p;
	Point pt[4];
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	float bodyWidth = 2.0;
	char command[256];
	float alpha;
	Color Blue, green;
	color_set(&Blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);

	khuf = module_create();
	khaf = module_create();
	menk = module_create();
	giza = module_create();

	// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 40*alpha, 140*alpha, -200*alpha - (alpha*200-cos(alpha)*200) );
    } else {
		point_set3D( &(view.vrp), -40, 0, 50 );
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
	int r;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

	khuf = pyramid(18, 0, 5, 0);
	khaf = pyramid(14, 55, 0, 50);
	menk = pyramid(10, 100, -3, 80);

	module_module(giza, khuf);
	module_module(giza, khaf);
	module_module(giza, menk);

	// create the image and drawstate
	src = image_create( rows, cols );
	image_fillColor(src, green);
	ds = drawstate_create();
	ds->shade = ShadeConstant;
	printf("created the image and drawstate\n");

	// draw scene
	module_draw(giza, &vtm, &gtm, ds, NULL, src);
	
	printf("drew the scene\n");

	// write out the scene
	printf("Writing image\n");
	image_write( src, "giza.ppm" );
	sprintf(command, "convert -scale %03dx%03d giza.ppm giza.ppm", cols/2, rows/2);
	system(command);

	// free the polygon data
	polygon_clear( &p );
	printf("polygon freed\n");

	// free the modules
	module_delete(menk);
	module_delete(khaf);
	module_delete(khuf);
	module_delete(giza);

	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


