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

/* declare methods here for testing flexibility */
static Module* city(int x, int y, int z);
static Module* city(int x, int y, int z){
  Module *b;
  Module *city;
  srand(time(NULL));

  Color Grey = {{0.5, 0.5, 0.5}};
  Color ltGrey = {{0.7, 0.7, 0.7}};
  city = module_create();

  // buildings
  b = module_create();
  module_scale( b, 4, 20, 4);
  module_translate( b, x-60, y+18, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 7, 2, 3);
  module_translate( b, x-60, y, z-5);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 15, 5);
  module_translate( b, x-60, y+12.5, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube( b, 1 );
  module_module(city, b);

  b = module_create();
  module_scale( b, 7, 10, 5);
  module_translate( b, x-40, y+7.5, z+5);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 20, 7);
  module_translate( b, x-40, y+16.5, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 5, 25, 7);
  module_translate( b, x-20, y+21, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1); 
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 20, 7);
  module_translate( b, x-20, y+16, z-5);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 30, 7);
  module_translate( b, x-20, y+26.5, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 5, 30, 7);
  module_translate( b, x, y+26.5, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 2, 3, 2);
  module_translate( b, x, y, z-7.5);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 2, 3, 2);
  module_translate( b, x, y, z);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 4, 20, 4);
  module_translate( b, x, y+18, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 5, 15, 6);
  module_translate( b, x+20, y+12, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 15, 5);
  module_translate( b, x+20, y+12.5, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube( b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 7, 2, 3);
  module_translate( b, x+20, y, z);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 7, 2, 3);
  module_translate( b, x+40, y, z);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 4, 5, 6);
  module_translate( b, x+40, y+2, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 7, 10, 5);
  module_translate( b, x+40, y+7.5, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 2, 5, 2);
  module_translate( b, x+60, y+4, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 8, 4, 3);
  module_translate( b, x+60, y+2.5, z+10);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 7, 2, 3);
  module_translate( b, x+70, y, z);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 7, 10, 5);
  module_translate( b, x+70, y+7.5, z+20);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  return((Module*)city);
}

static Module* sandscape();
static Module* sandscape(){
  Module *b, *terrain;
  terrain = module_create();

  // set up color palette
  Color brown =  {{72/255.0, 57/255.0, 42/255.0}};
  Color wBrown = {{50/255.0, 31/255.0, 12/255.0}};
  Color sandyBrown = {{87/255.0, 68/255.0, 44/255.0}};
  Color ltBrown = {{147/255.0, 106/255.0, 57/255.0}};
  Color sandy = {{0.68, 0.52, 0.28}};

  b = module_create();
  module_scale(b, 85, 1, 90);
  module_translate(b, 0, -2.5, 13);
  module_bodyColor(b, &ltBrown);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 85, 1.5, 90);
  module_translate(b, 0, -6, 13);
  module_bodyColor(b, &brown);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 85, 2, 90);
  module_translate(b, 0, -10, 13);
  module_bodyColor(b, &wBrown);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 85, 0.5, 90);
  module_translate(b, 0, -13, 13);
  module_bodyColor(b, &brown);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 85, 1, 90);
  module_translate(b, 0, -15, 13);
  module_bodyColor(b, &sandyBrown);
  module_cube(b, 1);
  module_module(terrain, b);

  return((Module*)terrain);
}

static Module* pyramid(int size, float x, float y, float z);
static Module* pyramid(int size, float x, float y, float z){
  Module *pyra;
  Color dark_sand = {{0.65, 0.42, 0.33}};
  
  pyra = module_create();
  module_bodyColor(pyra, &dark_sand);
  module_pyramid(pyra, 1, size, x, y, z);

  return((Module*)pyra);
}

int main(int argc, char *argv[]) {
  Image *src;
  Module *cairo, *sand, *giza, *khuf, *khaf, *menk;
  View3D view;
  Matrix vtm, gtm;
  DrawState *ds;
  Lighting *light;
  char command[256];
  float alpha;
  const int rows = 600*2;
  const int cols = 660*2;

    // set up color palette
  Color White = {{1.0, 1.0, 1.0}};

  cairo = module_create();
  sand = module_create();
  giza = module_create();
  khuf = module_create();
  khaf = module_create();
  menk = module_create();

  // grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 200*alpha, 200*alpha, -140*alpha - (1.0-cos(alpha)*140) );
    } else {
        point_set3D( &(view.vrp), 40, 50, 100 );
    }
  // set up the view
  vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
  vector_set( &(view.vup), 0, 1, 0 );
  view.d = 5;
  view.du = 6;
  view.f = 1;
  view.b = 400;
  view.screenx = cols;
  view.screeny = rows;

  printf("set up view\n");

  matrix_setView3D( &vtm, &view );
  matrix_identity( &gtm );

  sand = (Module*)sandscape();
  cairo = (Module*)city(0, 1, 65);
  khuf = pyramid(18, -40, 15, -50);
  khaf = pyramid(14, -5, 10, -10);
  menk = pyramid(10, 25, 5, 5);

  module_module(giza, khuf);
  module_module(giza, khaf);
  module_module(giza, menk);

  printf("added light\n");

  // create the image and drawstate
  src = image_create( rows, cols );
  ds = drawstate_create();
  point_copy(&(ds->viewer), &(view.vrp));
  ds->shade = ShadeGouraud;
  ds->surfaceCoeff = 7;
  printf("created the image and drawstate\n");

  // make two lights: point for contrast, ambient for general brightness
  light = lighting_create();
  light->light[0].type = LightPoint;
  light->light[1].type = LightAmbient;
  light->light[0].position.val[0] = view.vrp.val[0];
  light->light[0].position.val[1] = view.vrp.val[1];
  light->light[0].position.val[2] = view.vrp.val[2];
  light->light[1].position.val[0] = view.vrp.val[0];
  light->light[1].position.val[1] = view.vrp.val[1];
  light->light[1].position.val[2] = view.vrp.val[2];
  light->light[0].color.c[0] = 1;
  light->light[0].color.c[1] = 1;
  light->light[0].color.c[2] = 1;
  light->light[1].color.c[0] = 1;
  light->light[1].color.c[1] = 1;
  light->light[1].color.c[2] = 1;
  light->nLights = 2;

  module_draw(sand, &vtm, &gtm, ds, light, src );
  module_draw(giza, &vtm, &gtm, ds, light, src); 
  module_draw(cairo, &vtm, &gtm, ds, light, src);

  printf("drew the scene\n");

  // write out the scene
  printf("Writing image\n");
  image_write( src, "egypt-lighting.ppm" );
  sprintf(command, "convert -scale %03dx%03d egypt-lighting.ppm egypt-lighting.ppm", cols/2, rows/2);
  system(command);

  // free the modules
  module_delete(sand);
  module_delete(menk);
  module_delete(khaf);
  module_delete(khuf);
  module_delete(giza);
  module_delete(cairo);
  printf("modules freed\n");

  // free drawstate
  free(ds);
  printf("drawstate freed\n");

  // free image
  image_free( src );
  printf("image freed\n");
  
  return(0);
}
