/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 10/17/14
 *
 * The heirarchical model
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drawstate.h"

// Draw State

/*
 * create a new DrawState structure and initialize the fields.
 */
DrawState *drawstate_create(){
	DrawState *ds = malloc(sizeof(DrawState));
	if(!ds){
		printf("malloc failed in drawstate_create\n");
		return NULL;
	}
	
	// set defaults
	ds->shade = ShadeConstant;
	color_set(&(ds->flatColor), 1.0, 1.0, 1.0);
	color_set(&(ds->body), 1.0, 1.0, 1.0);
	color_set(&(ds->surface), 1.0, 1.0, 1.0);
	color_set(&(ds->color), 1.0, 1.0, 1.0);
	ds->zBufferFlag = 0;
	point_set3D(&(ds->viewer), 0.0, 0.0, 0.0);
	return ds;
}

/*
 * set the color field to c.
 */
void drawstate_setColor( DrawState *s, Color c ){
	if(!s){
		printf("Null DrawState passed to drawstate_setColor\n");
		return;
	}
	s->color = c;
}

/*
 * set the body field to c.
 */
void drawstate_setBody( DrawState *s, Color c ){
	if(!s){
		printf("Null DrawState passed to drawstate_setBody\n");
		return;
	}
	s->body = c;
}

/*
 * set the surface field to c.
 */
void drawstate_setSurface( DrawState *s, Color c ){
	if(!s){
		printf("Null DrawState passed to drawstate_setSurface\n");
		return;
	}
	s->surface = c;
}

/*
 * set the surfaceCoeff field to f.
 */
void drawstate_setSurfaceCoeff( DrawState *s, float f ){
	if(!s){
		printf("Null DrawState passed to drawstate_setSurfaceCoeff\n");
		return;
	}
	s->surfaceCoeff = f;
}

/*
 * copy the DrawState data.
 */
void drawstate_copy( DrawState *to, DrawState *from ){
	if(!to){
		printf("Null 'to' DrawState passed to drawstate_copy\n");
		return;
	}
	if(!from){
		printf("Null 'from' DrawState passed to drawstate_copy\n");
		return;
	}
	*to = *from;
}

