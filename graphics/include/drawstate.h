/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 10/17/14
 *
 * The heirarchical model
 */
 
#ifndef DRAWSTATE_H

#define DRAWSTATE_H

// determine how an object is drawn into the image.
typedef enum { 
	ShadeFrame, // draw only the borders of objects, including polygons.
	ShadeConstant, // draw objects using the current foreground color, fill polygons.
	ShadeDepth, // draw objects using their depth value.
	ShadeFlat, // draw objects using shading calculations, but each polygon is a constant value.
	ShadeGouraud, // draw objects using Gouraud shading.
	ShadePhong // draw objects using Phong shading.
} ShadeMethod;

// how an object is to be drawn into the image.
typedef struct {
	Color color; // the foreground color, used in the default drawing mode.
	Color flatColor; // the color to flat-fill a polygon based on a shading calculation.
	Color body; // the body reflection color, used for shading calculations.
	Color surface; // the surface reflection color, used for shading calculations.
	float surfaceCoeff; // a float that represents the shininess of the surface.
	ShadeMethod shade; // an enumerated type ShadeMethod.
	int zBufferFlag; // whether to use z-buffer hidden surface removal
	Point viewer;
} DrawState;

// Draw State

/*
 * create a new DrawState structure and initialize the fields.
 */
DrawState *drawstate_create( void );

/*
 * set the color field to c.
 */
void drawstate_setColor( DrawState *s, Color c );

/*
 * set the body field to c.
 */
void drawstate_setBody( DrawState *s, Color c );

/*
 * set the surface field to c.
 */
void drawstate_setSurface( DrawState *s, Color c );

/*
 * set the surfaceCoeff field to f.
 */
void drawstate_setSurfaceCoeff( DrawState *s, float f );

/*
 * copy the DrawState data.
 */
void drawstate_copy( DrawState *to, DrawState *from );

#endif
