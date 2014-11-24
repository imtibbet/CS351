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
	light->type = LightNone;

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
	l->nLights = 0;
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
	l->nLights = 0;
	light_init(&(l->light[0]));
}

/*
 * add a new light to the Lighting structure given the parameters, 
 * some of which may be NULL, depending upon the type. 
 * Make sure you don’t add more lights than MAX_LIGHTS.
 */
void lighting_add( Lighting *l, LightType type, Color *c, Vector *dir, 
	Point *pos, float cutoff, float sharpness ){
	Light light;
	if(!l){
		printf("Null lighting passed to lighting_add\n");
		return;
	} else if(l->nLights == 64) {
		printf("Full lighting passed to lighting_add\n");
		return;
	}
	light.type = type;
	if (c){
		color_copy(&light.color, c);
	}
	if (dir){
		vector_copy(&(light.direction), dir);
	}
	if (pos){
		point_copy(&light.position, pos);
	}
	if (type == LightSpot){
		light.cutoff = cutoff;
		light.sharpness = sharpness;
	}
	light_copy(&(l->light[l->nLights++]), &light);
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
	float LdotN, HdotNpowS, nLdotD, spotSharp, invlenLplusV;
	Color curc = {{0.0, 0.0, 0.0}};
	Vector L, nL, H;//, LplusV;
	if(!l || !N || !V || !p || !Cb || !Cs){
		printf("Null passed to lighting_shading\n");
		return;
	}
	for (i = 0; i < l->nLights; i++)
	{
		switch(l->light[i].type){

			case LightAmbient:
				printf("Ambient Light\n");
				curc.c[0] += Cb->c[0] * l->light[i].color.c[0];
				curc.c[1] += Cb->c[1] * l->light[i].color.c[1];
				curc.c[2] += Cb->c[2] * l->light[i].color.c[2];
				break;

			case LightDirect:
				printf("Direct Light\n");
				vector_set(&L, 	-1 * l->light[i].direction.val[0], 
								-1 * l->light[i].direction.val[1],
								-1 * l->light[i].direction.val[2]);
				vector_normalize(&L);
				vector_normalize(V);
				//vector_set(&LplusV,	L.val[0] + V->val[0], 
				//					L.val[1] + V->val[1], 
				//					L.val[2] + V->val[2] );
				invlenLplusV = 0.5;//1/vector_length(&LplusV);
				vector_set(&H,	invlenLplusV*(L.val[0] + V->val[0]), 
								invlenLplusV*(L.val[1] + V->val[1]), 
								invlenLplusV*(L.val[2] + V->val[2]) );
				if(oneSided && vector_dot(&L, N) < 0){
					N->val[0] *= -1;
					N->val[1] *= -1;
					N->val[2] *= -1;
				}
				LdotN = vector_dot(&L, N);
				if(LdotN > 0){
					HdotNpowS = pow(vector_dot(&H, N), s);
					curc.c[0] += 	Cb->c[0] * l->light[i].color.c[0] * LdotN + 
									Cs->c[0] * l->light[i].color.c[0] * HdotNpowS;
					curc.c[1] += 	Cb->c[1] * l->light[i].color.c[1] * LdotN + 
									Cs->c[1] * l->light[i].color.c[1] * HdotNpowS;
					curc.c[2] += 	Cb->c[2] * l->light[i].color.c[2] * LdotN + 
									Cs->c[2] * l->light[i].color.c[2] * HdotNpowS;
				}
				break;

			case LightPoint:
				printf("Point Light\n");
				vector_set(&L, 	l->light[i].position.val[0] - p->val[0], 
								l->light[i].position.val[1] - p->val[1], 
								l->light[i].position.val[2] - p->val[2] );
				vector_normalize(&L);
				vector_normalize(V);
				//vector_set(&LplusV,	L.val[0] + V->val[0], 
				//					L.val[1] + V->val[1], 
				//					L.val[2] + V->val[2] );
				invlenLplusV = 0.5;//1/vector_length(&LplusV);
				vector_set(&H,	invlenLplusV*(L.val[0] + V->val[0]), 
								invlenLplusV*(L.val[1] + V->val[1]), 
								invlenLplusV*(L.val[2] + V->val[2]) );
				if(oneSided && vector_dot(&L, N) < 0){
					N->val[0] *= -1;
					N->val[1] *= -1;
					N->val[2] *= -1;
				}
				LdotN = vector_dot(&L, N);
				if(LdotN > 0){
					HdotNpowS = pow(vector_dot(&H, N), s);
					curc.c[0] += 	Cb->c[0] * l->light[i].color.c[0] * LdotN + 
									Cs->c[0] * l->light[i].color.c[0] * HdotNpowS;
					curc.c[1] += 	Cb->c[1] * l->light[i].color.c[1] * LdotN + 
									Cs->c[1] * l->light[i].color.c[1] * HdotNpowS;
					curc.c[2] += 	Cb->c[2] * l->light[i].color.c[2] * LdotN + 
									Cs->c[2] * l->light[i].color.c[2] * HdotNpowS;
				}
				break;

			case LightSpot:
				printf("Spot Light\n");
				vector_set(&L, 	-1 * (l->light[i].position.val[0] - p->val[0]), 
								-1 * (l->light[i].position.val[1] - p->val[1]), 
								-1 * (l->light[i].position.val[2] - p->val[2]) );
				vector_normalize(&L);
				vector_normalize(V);
				//vector_set(&LplusV,	L.val[0] + V->val[0], 
				//					L.val[1] + V->val[1], 
				//					L.val[2] + V->val[2] );
				invlenLplusV = 0.5;//1/vector_length(&LplusV);
				vector_set(&H,	invlenLplusV*(L.val[0] + V->val[0]), 
								invlenLplusV*(L.val[1] + V->val[1]), 
								invlenLplusV*(L.val[2] + V->val[2]) );
				if(oneSided && vector_dot(&L, N) < 0){
					N->val[0] *= -1;
					N->val[1] *= -1;
					N->val[2] *= -1;
				}
				LdotN = vector_dot(&L, N);
				vector_set(&nL,	-1 * L.val[0], // negative L
								-1 * L.val[1], 
								-1 * L.val[2] );
				nLdotD = vector_dot(&nL, &(l->light[i].direction));
				if(	LdotN > 0 && nLdotD > cos(l->light[i].cutoff)){
					HdotNpowS = pow(vector_dot(&H, N), s);
					spotSharp = pow(nLdotD, l->light[i].sharpness);
					curc.c[0] += 	(Cb->c[0] * l->light[i].color.c[0] * LdotN + 
									Cs->c[0] * l->light[i].color.c[0] * HdotNpowS) * 
									spotSharp;
					curc.c[1] += 	(Cb->c[1] * l->light[i].color.c[1] * LdotN + 
									Cs->c[1] * l->light[i].color.c[1] * HdotNpowS) * 
									spotSharp;
					curc.c[2] += 	(Cb->c[2] * l->light[i].color.c[2] * LdotN + 
									Cs->c[2] * l->light[i].color.c[2] * HdotNpowS) * 
									spotSharp;
				}
				break;

			default:
				break;
		}
		printf("light %d: %.2f %.2f %.2f\n", i, curc.c[0], curc.c[1], curc.c[2]);
	}

	// clip colors to that are over-saturated down to one
	c->c[0] = curc.c[0] > 1.0 ? 1.0 : curc.c[0];
	c->c[1] = curc.c[1] > 1.0 ? 1.0 : curc.c[1];
	c->c[2] = curc.c[2] > 1.0 ? 1.0 : curc.c[2];
}


