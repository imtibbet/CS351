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
	light->type = LightAmbient;
	light->color = {0.1, 0.1, 0.1};
}

/*
 * copy the light information.
 */
void light_copy( Light *to, Light *from ){
	if(!to || !from){
		printf("Null passed to light_copy\n");
		return;
	}
	*to = *from;
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
	l->nLights = 1;
	light_init(&(l->light[0]));
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
	l->nLights = 1;
	light_init(&(l->light[0]));
}

/*
 * add a new light to the Lighting structure given the parameters, 
 * some of which may be NULL, depending upon the type. 
 * Make sure you don’t add more lights than MAX_LIGHTS.
 */
void lighting_add( Lighting *l, Color *c, Vector *dir, Point *pos, float cutoff, float sharpness ){
	Light light;
	int lightSet = 0;
	if(!l){
		printf("Null lighting passed to lighting_add\n");
		return;
	} else if(l->nLights == 64) {
		printf("Full lighting passed to lighting_add\n");
		return;
	}
	if (c){
		lightSet = 1;
		light->type = LightAmbient;
		color_copy(&light->color, c);
	}
	if (dir){
		lightSet = 1;
		light->type = LightDirect;
		vector_copy(&light->direction, dir);
	}
	if (pos){
		lightSet = 1;
		light->type = LightPoint;
		point_copy(&light->position, pos);
	}
	if (cutoff && sharpness){
		lightSet = 1;
		light->type = LightSpot;
		light->cutoff = cutoff;
		light->sharpness = sharpness;
	}
	if(!lightSet){
		printf("Null arguments passed to lighting_add, no light added\n");
	} else {
		light_copy(&(lighting->lights[lighting->nLights++]), light);
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
	int i;
	Color curc = {0.0, 0.0, 0.0};
	Vector L, H;
	if(!l || !N || !V || !p || !Cb || !Cs){
		printf("Null passed to lighting_shading\n");
		return;
	}
	for (i = 0; i < l->nLights; i++)
	{
		switch(l->lights[i].type){
			case LightAmbient:
				curc.c[0] += Cb->c[0]*l->lights[i].color.c[0];
				curc.c[1] += Cb->c[1]*l->lights[i].color.c[1];
				curc.c[2] += Cb->c[2]*l->lights[i].color.c[2];
				break;
			case LightDirect:
				vector_copy(&L, &(l->lights[i].direction));
				vector_set(&H,	0.5*(L.val[0] + V->val[0]), 
								0.5*(L.val[1] + V->val[1]), 
								0.5*(L.val[2] + V->val[2]) );

				break;
			case LightPoint:
				vector_set(&L, 	l->lights[i].position.val[0] - p->val[0], 
								l->lights[i].position.val[1] - p->val[1], 
								l->lights[i].position.val[2] - p->val[2] );
				vector_set(&H,	0.5*(L.val[0] + V->val[0]), 
								0.5*(L.val[1] + V->val[1]), 
								0.5*(L.val[2] + V->val[2]) );

				break;
			case LightSpot:
				vector_set(&L, 	l->lights[i].position.val[0] - p->val[0], 
								l->lights[i].position.val[1] - p->val[1], 
								l->lights[i].position.val[2] - p->val[2] );
				vector_set(&H,	0.5*(L.val[0] + V->val[0]), 
								0.5*(L.val[1] + V->val[1]), 
								0.5*(L.val[2] + V->val[2]) );

				break;
			default:
				break;
		}
	}
}


