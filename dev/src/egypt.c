/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

Draws egypt with cairo and the nearby pyramids of giza. 
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

/* declare methods here for testing flexibility */
static Module* city(int x, int y, int z);
static Module* city(int x, int y, int z){
	Module *b[21];
	Module *city;
	srand(time(NULL));
	int i;
	float f[21];

	Color Grey = {{0.5, 0.5, 0.5}};
	city = module_create();

	 	// buildings
 	b[0] = module_create();
 	module_scale( b[0], 4, 4, 20);
 	module_rotateX( b[0], 0, 1);
 	module_translate( b[0], (int)(-40+x), (int)(2.5+y), (int)z);
 	module_color(b[0], &Grey);
 	module_cube(b[0], 1);
 	b[1] = module_create();
 	module_scale( b[1], 7, 3, 2);
 	module_rotateX( b[1], 0, 1);
 	module_translate( b[1], (int)(-40+x), (int)(-6.5+y), (int)(10+z));
 	module_color(b[1], &Grey);
 	module_cube(b[1], 1);

  	b[2] = module_create();
 	module_scale( b[2], 5, 5, 15);
 	module_rotateX( b[2], 0, 1);
 	module_translate( b[2], (int)(-30+x), (int)y, (int)z);
 	module_color( b[2], &Grey);
 	module_cube( b[2], 1 );
 	b[3] = module_create();
 	module_scale( b[3], 7, 5, 10);
 	module_rotateX( b[3], 0, 1);
 	module_translate( b[3], (int)(-30+x), (int)(-2.5+y), (int)(10+z));
 	module_color(b[3], &Grey);
 	module_cube(b[3], 1);
 	b[4] = module_create();
 	module_scale( b[4], 5, 7, 20);
 	module_rotateX( b[4], 0, 1);
 	module_translate( b[4], (int)(-30+x), (int)(2.5+y), (int)(20+z));
 	module_color(b[4], &Grey);
 	module_cube(b[4], 1);

 	b[5] = module_create();
 	module_scale( b[5], 5, 7, 27);
 	module_rotateX( b[5], 0, 1);
 	module_translate( b[5], (int)(-20+x), (int)(6+y), (int)z);
 	module_color(b[5], &Grey);
 	module_cube(b[5], 1); 
 	b[6] = module_create();
 	module_scale( b[6], 5, 7, 20);
 	module_rotateX( b[6], 0, 1);
 	module_translate( b[6], (int)(-20+x), (int)(2.5+y), (int)(10+z));
 	module_color(b[6], &Grey);
 	module_cube(b[6], 1);
 	b[7] = module_create();
 	module_scale( b[7], 5, 7, 30);
 	module_rotateX( b[7], 0, 1);
 	module_translate( b[7], (int)(-20+x), (int)(7.5+y), (int)(20+z));
 	module_color(b[7], &Grey);
 	module_cube(b[7], 1);

  	b[8] = module_create();
 	module_scale( b[8], 5, 7, 30);
 	module_rotateX( b[8], 0, 1);
 	module_translate( b[8], (int)(-10+x), (int)(7.5+y), (int)z);
 	module_color(b[8], &Grey);
 	module_cube(b[8], 1);
 	b[9] = module_create();
 	module_scale( b[9], 2, 2, 3);
 	module_rotateX( b[9], 0, 1);
 	module_translate( b[9], (int)(-10+x), (int)(-6+y), (int)(10+z));
 	module_color(b[9], &Grey);
 	module_cube(b[9], 1);
 	b[10] = module_create();
 	module_scale( b[10], 2, 2, 3);
 	module_rotateX( b[10], 0, 1);
 	module_translate( b[10], (int)(-10+x), (int)(-6+y), (int)(15+z));
 	module_color(b[10], &Grey);
 	module_cube(b[10], 1);
 	b[11] = module_create();
 	module_scale( b[11], 4, 4, 20);
 	module_rotateX( b[11], 0, 1);
 	module_translate( b[11], (int)(-10+x), (int)(2.5+y), (int)(20+z));
 	module_color(b[11], &Grey);
 	module_cube(b[11], 1);

 	b[12] = module_create();
 	module_scale( b[12], 5, 5, 15);
 	module_rotateX( b[12], 0, 1);
 	module_translate( b[12], (int)x, (int)y, (int)z);
 	module_color( b[12], &Grey);
 	module_cube( b[12], 1);
 	b[13] = module_create();
 	module_scale( b[13], 5, 6, 15);
 	module_rotateX( b[13], 0, 1);
 	module_translate( b[13], (int)x, (int)y, (int)(12.5+z));
 	module_color(b[13], &Grey);
 	module_cube(b[13], 1);
  	b[14] = module_create();
 	module_scale( b[14], 7, 3, 2);
 	module_rotateX( b[14], 0, 1);
 	module_translate( b[14], (int)x, (int)(-6.5+y), (int)(20+z));
 	module_color(b[14], &Grey);
 	module_cube(b[14], 1);

 	b[15] = module_create();
 	module_scale( b[15], 7, 3, 2);
 	module_rotateX( b[15], 0, 1);
 	module_translate( b[15], (int)(10+x), (int)(-6.5+y), (int)z);
 	module_color(b[15], &Grey);
 	module_cube(b[15], 1);
 	b[16] = module_create();
 	module_scale( b[16], 4, 6, 3);
 	module_rotateX( b[16], 0, 1);
 	module_translate( b[16],(int)(10+x), (int)(-6+y), (int)(10+z));
 	module_color(b[16], &Grey);
 	module_cube(b[16], 1);
 	b[17] = module_create();
 	module_scale( b[17], 7, 5, 10);
 	module_rotateX( b[17], 0, 1);
 	module_translate( b[17], (int)(10+x), (int)(-2.5+y), (int)(20+z));
 	module_color(b[17], &Grey);
 	module_cube(b[17], 1);

  	b[18] = module_create();
 	module_scale( b[18], 2, 2, 5);
 	module_rotateX( b[18], 0, 1);
 	module_translate( b[18], (int)(20+x), (int)(-5+y), (int)z);
 	module_color(b[18], &Grey);
 	module_cube(b[18], 1);
 	b[19] = module_create();
 	module_scale( b[19], 8, 3, 4);
 	module_rotateX( b[19], 0, 1);
 	module_translate( b[19], (int)(20+x), (int)(-5.5+y), (int)(10+z));
 	module_color(b[19], &Grey);
 	module_cube(b[19], 1);

 	b[20] = module_create();
 	module_scale( b[20], 7, 3, 2);
 	module_rotateX( b[20], 0, 1);
 	module_translate( b[20], (int)(30+x), (int)(-6.5+y), (int)z);
 	module_color(b[20], &Grey);
 	module_cube(b[20], 1);
 	b[21] = module_create();
 	module_scale( b[21], 7, 5, 10);
 	module_rotateX( b[21], 0, 1);
 	module_translate( b[21], (int)(30+x), (int)(-2.5+y), (int)(10+z));
 	module_color(b[21], &Grey);
 	module_cube(b[21], 1);

	for ( i = 0; i < 22; i++){
		module_module((Module*)city, (Module*)b[i]);
	}

	return((Module*)city);
}

static Module* sandscape();
static Module* sandscape(){
	Module *sand;
	Color sandy = {{0.68, 0.52, 0.28}};

	sand = module_create();
	module_scale(sand, 100, 2, 100);
	module_translate(sand, 30, -6, 40);
	module_color(sand, &sandy);
	module_cube(sand, 1);

	return((Module*)sand);
}

static Module* pyramid(int size, float x, float y, float z);
static Module* pyramid(int size, float x, float y, float z){
	Color dark_sand = {{0.65, 0.42, 0.33}};
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
    module_color(pyra, &dark_sand);

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
	Module *cairo, *sand, *giza, *khuf, *khaf, *menk;
	Polygon p;
	Point pt[4];
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	float bodyWidth = 2.0;
	char command[256];
	float alpha;
	Color blue, green;
	color_set(&blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);

	khuf = module_create();
	khaf = module_create();
	menk = module_create();
	giza = module_create();
	cairo = module_create();

	// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 40*alpha, 140*alpha, -170*alpha - (alpha*170-cos(alpha)*170) );
    } else {
		point_set3D( &(view.vrp), -40, 0, 50 );
    }
	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 10;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;
	int r;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

 	sand = (Module*)sandscape();
 	cairo = (Module*)city(30, 1, 55);

	khuf = pyramid(9, 0, 3, 0);
	khaf = pyramid(7, 25, 0, 25);
	menk = pyramid(5, 50, -3, 40);

	module_module(giza, khuf);
	module_module(giza, khaf);
	module_module(giza, menk);

	color_set(&blue, 0, 0, 1);

	// create the image and drawstate
	src = image_create( rows, cols );
	image_fillColor(src, blue);
	ds = drawstate_create();
	ds->shade = ShadeConstant;
	printf("created the image and drawstate\n");

	// draw scene
	module_draw(sand, &vtm, &gtm, ds, NULL, src );
	module_draw(giza, &vtm, &gtm, ds, NULL, src);	
	module_draw(cairo, &vtm, &gtm, ds, NULL, src);
	
	printf("drew the scene\n");

	// write out the scene
	printf("Writing image\n");
	image_write( src, "egypt.ppm" );
	sprintf(command, "convert -scale %03dx%03d egypt.ppm egypt.ppm", cols/2, rows/2);
	system(command);

	// free the polygon data
	polygon_clear( &p );
	printf("polygon freed\n");

	// free the modules
	module_delete(sand);
	module_delete(menk);
	module_delete(khaf);
	module_delete(khuf);
	module_delete(giza);
	module_delete(cairo);

	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


