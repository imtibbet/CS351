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
	e->next = NULL;
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
	switch(e->type){
		case ObjPolyline:
			polyline_free(&(e->obj.polyline));
			break;
		case ObjPolygon:
			polygon_free(&(e->obj.polygon));
			break;
		case ObjModule:
			module_clear(((Module *)(e->obj.module)));
			break;
		default:
			printf("ObjectType type is not handled in element_delete\n");
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
		element_delete(curE);
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
		element_delete(curE);
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
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_line(Module *md, Line *p){
	Element *e = element_init(ObjLine, p);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_polyline(Module *md, Polyline *p){
	Element *e = element_init(ObjPolyline, p);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_polygon(Module *md, Polygon *p){
	Element *e = element_init(ObjPolygon, p);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Object that sets the current transform to the identity, 
 * placed at the tail of the module’s list.
 */
void module_identity(Module *md){
	Element *e;
	Matrix m;
	matrix_identity(&m);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Matrix operand to add a translation matrix to the tail of the module’s list.
 */
void module_translate2D(Module *md, double tx, double ty){
	Element *e;
	Matrix m;
	matrix_translate2D(&m,tx,ty);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Matrix operand to add a scale matrix to the tail of the module’s list.
 */
void module_scale2D(Module *md, double sx, double sy){
	Element *e;
	Matrix m;
	matrix_scale2D(&m, sx, sy);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Matrix operand to add a rotation about the Z axis to the tail of the module’s list
 */
void module_rotateZ(Module *md, double cth, double sth){
	Element *e;
	Matrix m;
	matrix_rotateZ(&m, cth, sth);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Matrix operand to add a 2D shear matrix to the tail of the module’s lisT
 */
void module_shear2D(Module *md, double shx, double shy){
	Element *e;
	Matrix m;
	matrix_shear2D(&m, shx, shy);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Draw the module into the image using the given view transformation matrix [VTM], 
 * Lighting and DrawState by traversing the list of Elements. 
 * (For now, Lighting can be an empty structure.)
 */
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, 
				Lighting *lighting, Image *src){
				
	// all locally needed variables
	Matrix LTM, tempGTM;
	Line tempLine;
	Point tempPointLTM, tempPointGTM, tempPointVTM;
	Polyline *tempPolyline = polyline_create();
	Polygon *tempPolygon = polygon_create();
	Element *e = md->head;
	matrix_identity(&LTM);

	// loop until the end of the linked list is reached
	while(e){
	
		// draw based on type
		switch(e->type){
			case ObjNone:
				break;
			case ObjPoint:
				// copy, xform, normalize, draw
				matrix_xformPoint(&LTM, &(e->obj.point), &tempPointLTM);
				matrix_xformPoint(GTM, &tempPointLTM, &tempPointGTM);
				matrix_xformPoint(VTM, &tempPointGTM, &tempPointVTM);
				point_normalize(&(tempPointVTM));
				point_draw(&tempPointVTM, src, ds->color);
				break;
			case ObjLine:
				// copy, xform, normalize, draw
				line_copy(&tempLine, &(e->obj.line));
				matrix_xformLine(&LTM, &tempLine);
				matrix_xformLine(GTM, &tempLine);
				matrix_xformLine(VTM, &tempLine);
				point_normalize(&(tempLine.a));
				point_normalize(&(tempLine.b));
				line_draw(&tempLine, src, ds->color);
				break;
			case ObjPolyline:
				// copy, xform, normalize, draw
				polyline_copy(tempPolyline, &(e->obj.polyline));
				matrix_xformPolyline(&LTM, tempPolyline);
				matrix_xformPolyline(GTM, tempPolyline);
				matrix_xformPolyline(VTM, tempPolyline);
				polyline_normalize(tempPolyline);
				polyline_draw(tempPolyline, src, ds->color);
				break;
			case ObjPolygon:
				// copy, xform, normalize, draw
				polygon_copy(tempPolygon, &(e->obj.polygon));
				matrix_xformPolygon(&LTM, tempPolygon);
				matrix_xformPolygon(GTM, tempPolygon);
				matrix_xformPolygon(VTM, tempPolygon);
				polygon_normalize(tempPolygon);
				polygon_draw(tempPolygon, src, ds->color);
				break;
			case ObjColor:
				ds->color = e->obj.color;
				break;
			case ObjBodyColor:
				break;
			case ObjSurfaceColor:
				break;
			case ObjSurfaceCoeff:
				break;
			case ObjLight:
				break;
			case ObjIdentity:
				break;
			case ObjMatrix:
				matrix_multiply(&(e->obj.matrix), &LTM, &LTM);
				break;
			case ObjModule:
				matrix_multiply(GTM, &LTM, &tempGTM);
				module_draw(e->obj.module, VTM, &tempGTM, ds, lighting, src);
				break;
			default:
				printf("ObjectType type is not handled in module_draw\n");
		}
		
		// advance traversal
		e = e->next;
	}
	
	// clean up
	polygon_free(tempPolygon);
	polyline_free(tempPolyline);
}

// 3D Module functions

/*
 * Matrix operand to add a 3D translation to the Module.
 */
void module_translate(Module *md, double tx, double ty, double tz){
	Element *e;
	Matrix m;
	matrix_translate(&m, tx, ty, tz);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Matrix operand to add a 3D scale to the Module.
 */
void module_scale(Module *md, double sx, double sy, double sz){
	Element *e;
	Matrix m;
	matrix_scale(&m, sx, sy, sz);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Matrix operand to add a rotation about the X-axis to the Module.
 */
void module_rotateX(Module *md, double cth, double sth){
	Element *e;
	Matrix m;
	matrix_rotateX(&m, cth, sth);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Matrix operand to add a rotation about the Y-axis to the Module.
 */
void module_rotateY(Module *md, double cth, double sth){
	Element *e;
	Matrix m;
	matrix_rotateY(&m, cth, sth);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}

/*
 * Matrix operand to add a rotation that orients to the orthonormal axes u,v,w
 */
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w){
	Element *e;
	Matrix m;
	matrix_rotateXYZ(&m, u, v, w);
	e = element_init(ObjIdentity, &m);
	if (!md->head){
		md->head = e;
	} 
	else {
		md->tail = e;
	}
}


/*
 * Adds a unit cube, axis-aligned and centered on zero to the Module. 
 * If solid is zero, add only lines. If solid is non-zero, use polygons. 
 * Make sure each polygon has surface normals defined for it.
 */
void module_cube(Module *md, int solid){
	Element *e;
 	Polygon p;
	Line l;
	Point v[8];
	Point tv[4];
	int i;
	
	// initialize polygon
	polygon_init( &p );
  
	// corners of a cube, centered at (0, 0, 0)
	point_set3D( &v[0], -0.5, -0.5, -0.5 );
	point_set3D( &v[1],  0.5, -0.5, -0.5 );
	point_set3D( &v[2],  0.5,  0.5, -0.5 );
	point_set3D( &v[3], -0.5,  0.5, -0.5 );
	point_set3D( &v[4], -0.5, -0.5,  0.5 );
	point_set3D( &v[5],  0.5, -0.5,  0.5 );
	point_set3D( &v[6],  0.5,  0.5,  0.5 );
	point_set3D( &v[7], -0.5,  0.5,  0.5 );
		
	if(solid == 0){
		// add only lines ( 12 of them )
		//line_set( &l, &(v[0]), &(v[1]) );
		//e = element_init(ObjLine, &l);
		//module_insert(md, e);
	}
	else{
	 	// use polygons ( 6 of them )
		// front side
		polygon_set( &p, 4, &(v[0]) );
		e = element_init(ObjPolygon, &p);
		if (!md->head){
		md->head = e;
		} else {
			md->tail = e;
		}

		// back side
		polygon_set( &p, 4, &(v[4]) );
		e = element_init(ObjPolygon, &p);
		if (!md->head){
		md->head = e;
		} else {
			md->tail = e;
		}

		// top side
		point_copy( &tv[0], &v[2] );
		point_copy( &tv[1], &v[3] );
		point_copy( &tv[2], &v[7] );
		point_copy( &tv[3], &v[6] );

		polygon_set( &p, 4, tv );
		e = element_init(ObjPolygon, &p);
		if (!md->head){
		md->head = e;
		} else {
			md->tail = e;
		}

		// bottom side
		point_copy( &tv[0], &v[0] );
		point_copy( &tv[1], &v[1] );
		point_copy( &tv[2], &v[5] );
		point_copy( &tv[3], &v[4] );

		polygon_set( &p, 4, tv );
		e = element_init(ObjPolygon, &p);
		if (!md->head){
		md->head = e;
		} else {
			md->tail = e;
		}

		// left side
		point_copy( &tv[0], &v[0] );
		point_copy( &tv[1], &v[3] );
		point_copy( &tv[2], &v[7] );
		point_copy( &tv[3], &v[4] );

		polygon_set( &p, 4, tv );
		e = element_init(ObjPolygon, &p);
		if (!md->head){
		md->head = e;
		} else {
			md->tail = e;
		}

		// right side
		point_copy( &tv[0], &v[1] );
		point_copy( &tv[1], &v[2] );
		point_copy( &tv[2], &v[6] );
		point_copy( &tv[3], &v[5] );

		polygon_set( &p, 4, tv );
		e = element_init(ObjPolygon, &p);
		if (!md->head){
		md->head = e;
		} else {
			md->tail = e;
		}
	}
}

// Shading/Color Module Functions

/*
 * Adds the foreground color value to the tail of the module’s list
 */
void module_color(Module *md, Color *c){
	if(!md){
		printf("Null module passed to module_color\n");
		return;
	}
	if(!c){
		printf("Null color passed to module_color\n");
		return;
	}
	if(!md->tail){
		printf("Empty module passed to module_color\n");
		return;
	}
	md->tail->obj.color = *c;
}

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
	color_set(&(ds->color), 1.0, 1.0, 1.0);
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

