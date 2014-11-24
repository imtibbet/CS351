/*
  Bruce A. Maxwell
  Fall 2014

  Example code for drawing a single cube

  C Version
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
  Image *src;
  Matrix VTM;
  Matrix GTM;
  Module *cube;
  int rows = 360;
  int cols = 640;

  Color White;
  Color Grey;

  DrawState *ds;
  View3D view;

  Lighting *light;

	color_set( &White, 1.0, 1.0, 1.0 );
	color_set( &Grey, 0.6, 0.62, 0.64 );

  // initialize the image
  src = image_create(rows, cols);

  // initialize matrices
  matrix_identity(&GTM);
  matrix_identity(&VTM);

  // set the View parameters
  point_set3D(&(view.vrp), 5, 5, -7.0);
  vector_set(&(view.vpn), -5, -5, 7);
  vector_set(&(view.vup), 0.0, 1.0, 0.0);
  view.d = 2.0;
  view.du = 1.6;
  view.dv = .9;
  view.f = 0.0;
  view.b = 15;
  view.screenx = cols;
  view.screeny = rows;
  matrix_setView3D(&VTM, &view);

  // print out VTM
  printf("Final VTM: \n");
  matrix_print(&VTM, stdout);

  // make a simple cube module
  cube = module_create();
  module_scale( cube, 3, 1, 2 );

  // this would color the cube in ShadeConstant mode
  module_color( cube, &Grey );

  // the example cube is blue (Y/-Y), red (Z/-Z), yellow (X/-X)
  // these colors should be the body colors
  module_cube( cube, 1);

  // manually add a light source to the Lighting structure
  // put it in the same place as the eye in world space
  light = lighting_create();
  lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );

  // set the shading to Gouraud
  ds = drawstate_create();
  point_copy(&(ds->viewer), &(view.vrp));
	ds->shade = ShadeGouraud;
	//	ds->shade = ShadeFlat;

  matrix_identity(&GTM);
  module_draw(cube, &VTM, &GTM, ds, light, src);

  // write out the image
  image_write(src, "test9a.ppm");

  // free stuff here
  module_delete( cube );
  image_free( src );
  

  return(0);
=======
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

int main(int argc, char *argv[]) {

	Vector N;
	Vector V;
	Point p;
	Color Cb = {{0.4, 0.5, 0.6}};
	Color Cs = {{0.2, 0.2, 0.2}};
	float s = 10;
	Lighting *l;
	Color c;
	Color amb = {{0.3, 0.3, 0.3}};
	Color pt = {{1.0, 1.0, 1.0}};
	Point loc;

	point_set3D(&p, 0, 0, 0); // origin
	point_set3D(&N, 0, 1, 0); // up
	vector_set(&V, 1, 2, 3);
	

	l = lighting_create();
	lighting_add( l, LightAmbient, &amb, NULL, NULL, 0, 0);

	point_set3D( &loc, 3, 2, 1 );
	lighting_add( l, LightPoint, &pt, NULL, &loc, 0, 0 );

	lighting_shading( l, &N, &V, &p, &Cb, &Cs, s, 1, &c );

	printf("c: %.2f %.2f %.2f\n", c.c[0], c.c[1], c.c[2] );

	return(0);
}
