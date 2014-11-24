/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 10/17/14
 *
 * The heirarchical model
 */
 
#ifndef HEIRARCHY_H

#define HEIRARCHY_H

typedef enum { // example of an enumerated type
	ObjNone,
	ObjLine,
	ObjPoint,
	ObjPolyline,
	ObjPolygon,
	ObjIdentity,
	ObjMatrix,
	ObjColor,
	ObjBodyColor,
	ObjSurfaceColor,
	ObjSurfaceCoeff,
	ObjLight,
	ObjModule
} ObjectType;

// option 2 for Element structure (union option)
typedef union {
	Point point;
	Line line;
	Polyline polyline;
	Polygon polygon;
	Matrix matrix;
	Color color;
	float coeff;
	void *module;
} Object;

// Module structure
typedef struct EElement {
	ObjectType type;
	Object obj;
	struct EElement *next;
} Element;

typedef struct {
	Element *head; // pointer to the head of the linked list
	Element *tail; // keep around a pointer to the last object
} Module;

// 2D and Generic Module Function

/*
 * Allocate and return an initialized but empty Element.
 */
Element *element_create( void );

/*
 * Allocate an Element and store a duplicate of the data pointed to by 
 * obj in the Element. Modules do not get duplicated. The function needs
 * to handle each type of object separately in a case statement.
 */
Element *element_init(ObjectType type, void *obj);

/*
 * free the element and the object it contains, as appropriate.
 */
void element_delete(Element *e);

/*
 * Allocate an empty module.
 */
Module *module_create( void );

/*
 * clear the module’s list of Elements, freeing memory as appropriate.
 */
void module_clear(Module *md);

/*
 * Free all of the memory associated with a module, 
 * including the memory pointed to by md.
 */
void module_delete(Module *md);

/*
 * Generic insert of an element into the module at the tail of the list.
 */
void module_insert(Module *md, Element *e);

/*
 * Adds a pointer to the Module sub to the tail of the module’s list.
 */
void module_module(Module *md, Module *sub);

/*
 * Adds p to the tail of the module’s list.
 */
void module_point(Module *md, Point *p);

/*
 * Adds p to the tail of the module’s list.
 */
void module_line(Module *md, Line *p);

/*
 * Adds p to the tail of the module’s list.
 */
void module_polyline(Module *md, Polyline *p);

/*
 * Adds p to the tail of the module’s list.
 */
void module_polygon(Module *md, Polygon *p);

/*
 * Object that sets the current transform to the identity, 
 * placed at the tail of the module’s list.
 */
void module_identity(Module *md);

/*
 * Matrix operand to add a translation matrix to the tail of the module’s list.
 */
void module_translate2D(Module *md, double tx, double ty);

/*
 * Matrix operand to add a scale matrix to the tail of the module’s list.
 */
void module_scale2D(Module *md, double sx, double sy);

/*
 * Matrix operand to add a rotation about the Z axis to the tail of the module’s list
 */
void module_rotateZ(Module *md, double cth, double sth);

/*
 * Matrix operand to add a 2D shear matrix to the tail of the module’s lisT
 */
void module_shear2D(Module *md, double shx, double shy);

/*
 * Draw the module into the image using the given view transformation matrix [VTM], 
 * Lighting and DrawState by traversing the list of Elements. 
 * (For now, Lighting can be an empty structure.)
 */
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, 
				Lighting *lighting, Image *src);

// 3D Module functions

/*
 * Matrix operand to add a 3D translation to the Module.
 */
void module_translate(Module *md, double tx, double ty, double tz);

/*
 * Matrix operand to add a 3D scale to the Module.
 */
void module_scale(Module *md, double sx, double sy, double sz);

/*
 * Matrix operand to add a rotation about the X-axis to the Module.
 */
void module_rotateX(Module *md, double cth, double sth);

/*
 * Matrix operand to add a rotation about the Y-axis to the Module.
 */
void module_rotateY(Module *md, double cth, double sth);

/*
 * Matrix operand to add a rotation that orients to the orthonormal axes u,v,w
 */
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w);

/*
 * Matrix operand to add a Z shear matrix to the tail of the module’s list
 */
void module_shearZ(Module *md, double shx, double shy);

/*
 * Adds a unit cube, axis-aligned and centered on zero to the Module. 
 * If solid is zero, add only lines. If solid is non-zero, use polygons. 
 * Make sure each polygon has surface normals defined for it.
 */
void module_cube(Module *md, int solid);

/*
 * insert a pyramid into the module
 */
void module_pyramid(Module *md, int solid, float size, 
					float x, float y, float z);

/*
* Sourced from coursework file test6b.c (Bruce Maxwell)
*/
void module_cylinder( Module *mod, int sides, int fill, int size, 
					float x, float y, float z);

/*
 * insert cone into the module
 */
 void module_cone(Module *mod, int sides, int fill, int size, float x, 
 	float y, float z);

// Shading/Color Module Functions

/*
 * Adds the foreground color value to the tail of the module’s list
 */
void module_color(Module *md, Color *c); 

/*
 * Adds the body color value to the tail of the module’s list.
 */
void module_bodyColor(Module *md, Color *c);

/*
 * Adds the surface color value to the tail of the module’s list.
 */
void module_surfaceColor(Module *md, Color *c);

/*
 * Adds the specular coefficient to the tail of the module’s list
 */
void module_surfaceCoeff(Module *md, float coeff);

// Bezier Curve and Surface Module Functions

/*
 * use the de Casteljau algorithm to subdivide the Bezier curve divisions times,
 * then add the lines connecting the control points to the module.
 */
void module_bezierCurve(Module *m, BezierCurve *b, int divisions);

/*
 * use the de Casteljau algorithm to subdivide the Bezier surface divisions times,
 * then draw either the lines connecting the control points, if solid is 0, 
 * or draw triangles connecting the surface.
 */
void module_bezierSurface(Module *m, BezierSurface *b, int divisions, int solid);

/*
 * add a teapot to the module with the specified number of divisions
 */
void module_teapot(Module *m, int divisions, int solid);

#endif
