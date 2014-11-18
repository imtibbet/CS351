/*
 * Author: Ian Tibbetts
 * Date: 11/18/14
 *
 * The lighting function implementations
 */

#include "graphics.h"

//const int MAX_LIGHTS = 64;

// Light functions

/*
 * initialize the light to default values.
 */
void light_init( Light *light ){
	if(!light){
		printf("Null passed to light_init\n");
		return;
	}
}

/*
 * copy the light information.
 */
void light_copy( Light *to, Light *from ){
	if(!to || !from){
		printf("Null passed to light_copy\n");
		return;
	}
}

// Lighting functions

/*
 * allocate and return a new lighting structure set to default values.
 */
Lighting *lighting_create( void ){
	Lighting *l = NULL;
	l = malloc(sizeof(Lighting));
	if(!l){
		printf("malloc failed in lighting_create\n");
		return(NULL);
	}
	return(l);
}

/*
 * initialize the lighting structure to default values.
 */
void lighting_init( Lighting *l){
	if(!l){
		printf("Null passed to lighting_init\n");
		return;
	}
}

/*
 * add a new light to the Lighting structure given the parameters, 
 * some of which may be NULL, depending upon the type. 
 * Make sure you don’t add more lights than MAX_LIGHTS.
 */
void lighting_add( Lighting *l, Color *c, Vector *dir, Point *pos, float cutoff, float sharpness ){
	if(!l){
		printf("Null passed to lighting_add\n");
		return;
	}
}

/*
 * calculate the proper color given the normal N, view vector V, 3D point P, 
 * body color Cb, surface color Cs, sharpness value s, the lighting, 
 * and whether the polygon is one-sided or two-sided. 
 * Put the result in the Color c.
 */
void lighting_shading( Lighting *l, Vector *N, Vector *V, Point *p, 
	Color *Cb, Color *Cs, float s, int oneSided, Color *c){
	if(!l || !N || !V || !p || !Cb || !Cs){
		printf("Null passed to lighting_shading\n");
		return;
	}
}


