/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 10/17/14
 *
 * The heirarchical model
 */

#include "graphics.h"

// 2D and Generic Module Function

/*
 * Allocate and return an initialized but empty Element.
 */
Element *element_create(){
	Element *e = malloc(sizeof(Element));
	if(!e){
		printf("malloc failed in element_create\n");
		return NULL;
	}
	return e;
}

/*
 * Allocate an Element and store a duplicate of the data pointed to by 
 * obj in the Element. Modules do not get duplicated. The function needs
 * to handle each type of object separately in a case statement.
 */
Element *element_init(ObjectType type, void *obj){
	Element *e = malloc(sizeof(Element));
	if(!e){
		printf("malloc failed in element_init\n");
		return NULL;
	}
	e->type = type;
	switch (type) {
		case ObjNone:
			printf("ObjNone not implemented in element_init\n");
			break;
		case ObjLine:
			line_copy(&(e->obj.line), (Line*)obj);
			break;
		case ObjPoint:
			point_copy(&(e->obj.point), (Point*)obj);
			break;
		case ObjPolyline:
			polyline_copy(&(e->obj.polyline), (Polyline*)obj);
			break;
		case ObjPolygon:
			polygon_copy(&(e->obj.polygon), (Polygon*)obj);
			break;
		case ObjIdentity:
		case ObjMatrix:
			matrix_copy(&(e->obj.matrix), (Matrix*)obj);
			break;
		case ObjColor:
		case ObjBodyColor:
		case ObjSurfaceColor:
			color_copy(&(e->obj.color), (Color*)obj);
			break;
		case ObjSurfaceCoeff:
			e->obj.coeff = *(float*)obj;
			break;
		case ObjLight:
			printf("ObjLight not implemented in element_init\n");
			break;
		case ObjModule:
			e->obj.module = obj;
			break;
		default:
			printf("ObjectType type is not handled in element_init\n");
	}
	return e;
}

/*
 * free the element and the object it contains, as appropriate.
 */
void element_delete(Element *e){
	if(!e){
		printf("Null e passed to element_delete\n");
		return;
	}
	if(e->type == ObjModule && e->obj){
		free(e->obj);
	}
	free(e);

}

/*
 * Allocate an empty module.
 */
Module *module_create(){
	Module *d = malloc(sizeof(Module));
	if(!d){
		printf("malloc failed in module_create\n");
		return NULL;
	}
	return d;
}

/*
 * clear the module’s list of Elements, freeing memory as appropriate.
 */
void module_clear(Module *md){
	Element *curE, *next;
	if(!md){
		printf("Null md passed to module_clear\n");
		return;
	}
	curE = md->head;
	md->head = md->tail = NULL;
	while(curE){
		next = curE->next;
		free(curE);
		curE = next;
	}
}

/*
 * Free all of the memory associated with a module, 
 * including the memory pointed to by md.
 */
void module_delete(Module *md){

	// module_clear(md)
	Element *curE, *next;
	if(!md){
		printf("Null md passed to module_delete\n");
		return;
	}
	curE = md->head;
	md->head = md->tail = NULL;
	while(curE){
		next = curE->next;
		free(curE);
		curE = next;
	}

	// free module itself after clearing
	free(md);
}

/*
 * Generic insert of an element into the module at the tail of the list.
 */
void module_insert(Module *md, Element *e){
	if(!md){
		printf("Null md passed to module_insert\n");
		return;
	}
	if(md->head){
		md->head = md->tail = e;
	} else {
		md->tail->next = e;
		md->tail = e;
	}
}

/*
 * Adds a pointer to the Module sub to the tail of the module’s list.
 */
void module_module(Module *md, Module *sub){
	Element *e = element_init(ObjModule, sub);
	module_insert(md, e);
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_point(Module *md, Point *p){
	Element *e = element_init(ObjPoint, p);
	module_insert(md, e);
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_line(Module *md, Line *p){
	Element *e = element_init(ObjLine, p);
	module_insert(md, e);
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_polyline(Module *md, Polyline *p){
	Element *e = element_init(ObjPolyline, p);
	module_insert(md, e);
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_polygon(Module *md, Polygon *p){
	Element *e = element_init(ObjPolygon, p);
	module_insert(md, e);
}

/*
 * Object that sets the current transform to the identity, 
 * placed at the tail of the module’s list.
 */
void module_identity(Module *md){
	Element *e;
	Matrix m;
	matrix_identity(&m);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a translation matrix to the tail of the module’s list.
 */
void module_translate2D(Module *md, double tx, double ty){
	Element *e;
	Matrix m;
	matrix_translate2D(&m,tx,ty);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a scale matrix to the tail of the module’s list.
 */
void module_scale2D(Module *md, double sx, double sy){
	Element *e;
	Matrix m;
	matrix_scale2D(&m, sx, sy);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a rotation about the Z axis to the tail of the module’s list
 */
void module_rotateZ(Module *md, double cth, double sth){
	Element *e;
	Matrix m;
	matrix_rotateZ(&m, cth, sth);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a 2D shear matrix to the tail of the module’s lisT
 */
void module_shear2D(Module *md, double shx, double shy){
	Element *e;
	Matrix m;
	matrix_shear2D(&m, shx, shy);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Draw the module into the image using the given view transformation matrix [VTM], 
 * Lighting and DrawState by traversing the list of Elements. 
 * (For now, Lighting can be an empty structure.)
 */
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, 
				Lighting *lighting, Image *src){

}

// 3D Module functions

/*
 * Matrix operand to add a 3D translation to the Module.
 */
void module_translate(Module *md, double tx, double ty, double tz){
	Element *e;
	Matrix m;
	matrix_translate(&m, tx, ty, tz);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a 3D scale to the Module.
 */
void module_scale(Module *md, double sx, double sy, double sz){
	Element *e;
	Matrix m;
	matrix_scale(&m, sx, sy, sz);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a rotation about the X-axis to the Module.
 */
void module_rotateX(Module *md, double cth, double sth){
	Element *e;
	Matrix m;
	matrix_rotateX(&m, cth, sth);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a rotation about the Y-axis to the Module.
 */
void module_rotateY(Module *md, double cth, double sth){
	Element *e;
	Matrix m;
	matrix_rotateY(&m, cth, sth);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a rotation that orients to the orthonormal axes u,v,w
 */
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w){
	Element *e;
	Matrix m;
	matrix_rotateXYZ(&m, u, v, w);
	e = element_init(ObjIdentity, m);
	module_insert(md, e);
}


/*
 * Adds a unit cube, axis-aligned and centered on zero to the Module. 
 * If solid is zero, add only lines. If solid is non-zero, use polygons. 
 * Make sure each polygon has surface normals defined for it.
 */
void module_cube(Module *md, int solid){

}

// Shading/Color Module Functions

/*
 * Adds the foreground color value to the tail of the module’s list
 */
void module_color(Module *md, Color *c){

}

// Draw State

/*
 * create a new DrawState structure and initialize the fields.
 */
void drawstate_create( void ){

}

/*
 * set the color field to c.
 */
void drawstate_setColor( DrawState *s, Color c ){

}

/*
 * set the body field to c.
 */
void drawstate_setBody( DrawState *s, Color c ){

}

/*
 * set the surface field to c.
 */
void drawstate_setSurface( DrawState *s, Color c ){

}

/*
 * set the surfaceCoeff field to f.
 */
void drawstate_setSurfaceCoeff( DrawState *s, float f ){

}

/*
 * copy the DrawState data.
 */
void drawstate_copy( DrawState *to, DrawState *from ){

}

