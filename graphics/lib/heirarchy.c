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
	switch (e->type) {
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
  			polyline_init(&(e->obj.polyline));
			polyline_copy(&(e->obj.polyline), (Polyline*)obj);
			break;
		case ObjPolygon:
  			polygon_init(&(e->obj.polygon));
			polygon_copy(&(e->obj.polygon), (Polygon*)obj);
			break;
		case ObjIdentity:
			break;
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
			printf("ObjectType %d is not handled in element_init\n",type);
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
	//printf("deleting element of type %d\n", e->type);
	switch(e->type){
		case ObjPolyline:
			polyline_clear(&(e->obj.polyline));
			break;
		case ObjPolygon:
			polygon_clear(&(e->obj.polygon));
			break;
		default:
			//printf("ObjectType %d is not handled in element_delete\n",e->type);
			break;
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
	d->head = d->tail = NULL;
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
	if(!e){
		printf("Null e passed to module_insert\n");
		return;
	}
	if(!md->head){
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
	if(!md){
		printf("Null md passed to module_module\n");
		return;
	}
	if(!sub){
		printf("Null sub passed to module_module\n");
		return;
	}
	Element *e = element_init(ObjModule, sub);
	module_insert(md, e);
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_point(Module *md, Point *p){
	if(!md){
		printf("Null md passed to module_point\n");
		return;
	}
	if(!p){
		printf("Null point passed to module_point\n");
		return;
	}
	Element *e = element_init(ObjPoint, p);
	module_insert(md, e);
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_line(Module *md, Line *p){
	if(!md){
		printf("Null md passed to module_line\n");
		return;
	}
	if(!p){
		printf("Null line passed to module_line\n");
		return;
	}
	Element *e = element_init(ObjLine, p);
	module_insert(md, e);
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_polyline(Module *md, Polyline *p){
	if(!md){
		printf("Null md passed to module_polyline\n");
		return;
	}
	if(!p){
		printf("Null polyline passed to module_polyline\n");
		return;
	}
	Element *e = element_init(ObjPolyline, p);
	module_insert(md, e);
}

/*
 * Adds p to the tail of the module’s list.
 */
void module_polygon(Module *md, Polygon *p){
	if(!md){
		printf("Null md passed to module_polygon\n");
		return;
	}
	if(!p){
		printf("Null polygon passed to module_polygon\n");
		return;
	}
	Element *e = element_init(ObjPolygon, p);
	module_insert(md, e);
}

/*
 * Object that sets the current transform to the identity, 
 * placed at the tail of the module’s list.
 */
void module_identity(Module *md){
	if(!md){
		printf("Null md passed to module_identity\n");
		return;
	}
	Element *e;
	e = element_init(ObjIdentity, NULL);
	module_insert(md, e);
}

/*
 * Matrix operand to add a translation matrix to the tail of the module’s list.
 */
void module_translate2D(Module *md, double tx, double ty){
	if(!md){
		printf("Null md passed to module_translate2D\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_translate2D(&m,tx,ty);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a scale matrix to the tail of the module’s list.
 */
void module_scale2D(Module *md, double sx, double sy){
	if(!md){
		printf("Null md passed to module_scale2D\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_scale2D(&m,sx,sy);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a rotation about the Z axis to the tail of the module’s list
 */
void module_rotateZ(Module *md, double cth, double sth){
	if(!md){
		printf("Null md passed to module_rotateZ\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_rotateZ(&m, cth, sth);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a 2D shear matrix to the tail of the module’s list
 */
void module_shear2D(Module *md, double shx, double shy){
	if(!md){
		printf("Null md passed to module_shear2D\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_shear2D(&m, shx, shy);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
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
	DrawState *tempds = drawstate_create();
	Point tempPointLTM, tempPointGTM, tempPointVTM;
	Polyline *tempPolyline = polyline_create();
	Polygon *tempPolygon = polygon_create();
	Element *e = md->head;
	
	matrix_identity(&LTM);
	
	// loop until the end of the linked list is reached
	while(e){
		//printf("Handling type %d\n", e->type);
		// draw based on type
		switch(e->type){
			case ObjNone:
				break;
			case ObjPoint:
				//printf("drawing point ");
				// copy, xform, normalize, draw
				matrix_xformPoint(&LTM, &(e->obj.point), &tempPointLTM);
				matrix_xformPoint(GTM, &tempPointLTM, &tempPointGTM);
				matrix_xformPoint(VTM, &tempPointGTM, &tempPointVTM);
				point_normalize(&(tempPointVTM));
				//point_print(&tempPointVTM, stdout);
				point_draw(&tempPointVTM, src, ds->color);
				break;
			case ObjLine:
				//printf("drawing line ");
				// copy, xform, normalize, draw
				line_copy(&tempLine, &(e->obj.line));
				matrix_xformLine(&LTM, &tempLine);
				matrix_xformLine(GTM, &tempLine);
				matrix_xformLine(VTM, &tempLine);
				line_normalize(&tempLine);
				//line_print(&tempLine, stdout);
				line_draw(&tempLine, src, ds->color);
				break;
			case ObjPolyline:
				//printf("drawing polyline ");
				// copy, xform, normalize, draw
				polyline_copy(tempPolyline, &(e->obj.polyline));
				matrix_xformPolyline(&LTM, tempPolyline);
				matrix_xformPolyline(GTM, tempPolyline);
				matrix_xformPolyline(VTM, tempPolyline);
				polyline_normalize(tempPolyline);
				//polyline_print(tempPolyline, stdout);
				polyline_draw(tempPolyline, src, ds->color);
				break;
			case ObjPolygon:
				//printf("drawing polygon ");
				// copy, xform, normalize, draw
				polygon_copy(tempPolygon, &(e->obj.polygon));
				matrix_xformPolygon(&LTM, tempPolygon);
				matrix_xformPolygon(GTM, tempPolygon);
				matrix_xformPolygon(VTM, tempPolygon);
				polygon_normalize(tempPolygon);
				//polygon_print(tempPolygon, stdout);
				polygon_draw(tempPolygon, src, ds);
				break;
			case ObjColor:
				drawstate_setColor(ds, e->obj.color);
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
				matrix_identity(&LTM);
				break;
			case ObjMatrix:
				matrix_multiply(&(e->obj.matrix), &LTM, &LTM);
				break;
			case ObjModule:
				matrix_multiply(GTM, &LTM, &tempGTM);
				drawstate_copy(tempds, ds);
				module_draw(e->obj.module, VTM, &tempGTM, tempds, lighting, src);
				break;
			default:
				printf("ObjectType %d is not handled in module_draw\n",e->type);
		}
		
		// advance traversal
		e = e->next;
	}
	
	// clean up
	polygon_free(tempPolygon);
	polyline_free(tempPolyline);
	free(tempds);
}

// 3D Module functions

/*
 * Matrix operand to add a 3D translation to the Module.
 */
void module_translate(Module *md, double tx, double ty, double tz){
	if(!md){
		printf("Null md passed to module_translate\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_translate(&m, tx, ty, tz);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a 3D scale to the Module.
 */
void module_scale(Module *md, double sx, double sy, double sz){
	if(!md){
		printf("Null md passed to module_scale\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_scale(&m, sx, sy, sz);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a rotation about the X-axis to the Module.
 */
void module_rotateX(Module *md, double cth, double sth){
	if(!md){
		printf("Null md passed to module_rotateX\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_rotateX(&m, cth, sth);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a rotation about the Y-axis to the Module.
 */
void module_rotateY(Module *md, double cth, double sth){
	if(!md){
		printf("Null md passed to module_rotateY\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_rotateY(&m, cth, sth);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a rotation that orients to the orthonormal axes u,v,w
 */
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w){
	if(!md){
		printf("Null md passed to module_rotateXYZ\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_rotateXYZ(&m, u, v, w);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Matrix operand to add a Z shear matrix to the tail of the module’s list
 */
void module_shearZ(Module *md, double shx, double shy){
	if(!md){
		printf("Null md passed to module_shearZ\n");
		return;
	}
	Element *e;
	Matrix m;
	matrix_identity(&m);
	matrix_shearZ(&m, shx, shy);
	e = element_init(ObjMatrix, &m);
	module_insert(md, e);
}

/*
 * Adds a unit cube, axis-aligned and centered on zero to the Module. 
 * If solid is zero, add only lines. If solid is non-zero, use polygons. 
 * Make sure each polygon has surface normals defined for it.
 */
void module_cube(Module *md, int solid){
	if(!md){
		printf("Null md passed to module_cube\n");
		return;
	}
	Element *e;
 	Polygon p;
	Point v[8];
	Point tv[4];
	Line l;
	
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
		
		// front face lines
		line_set( &l, v[0], v[1] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[1], v[2] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[2], v[3] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[3], v[0] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		
		// back face lines
		line_set( &l, v[4], v[5] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[5], v[6] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[6], v[7] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[7], v[4] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		
		// connecting lines
		line_set( &l, v[2], v[6] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[3], v[7] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[0], v[4] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[1], v[5] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
	}
	else{
	 	// use polygons ( 6 of them )
		// front side
		polygon_set( &p, 4, &(v[0]) );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// back side
		polygon_set( &p, 4, &(v[4]) );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// top side
		point_copy( &tv[0], &v[2] );
		point_copy( &tv[1], &v[3] );
		point_copy( &tv[2], &v[7] );
		point_copy( &tv[3], &v[6] );

		polygon_set( &p, 4, tv );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// bottom side
		point_copy( &tv[0], &v[0] );
		point_copy( &tv[1], &v[1] );
		point_copy( &tv[2], &v[5] );
		point_copy( &tv[3], &v[4] );

		polygon_set( &p, 4, tv );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// left side
		point_copy( &tv[0], &v[0] );
		point_copy( &tv[1], &v[3] );
		point_copy( &tv[2], &v[7] );
		point_copy( &tv[3], &v[4] );

		polygon_set( &p, 4, tv );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// right side
		point_copy( &tv[0], &v[1] );
		point_copy( &tv[1], &v[2] );
		point_copy( &tv[2], &v[6] );
		point_copy( &tv[3], &v[5] );

		polygon_set( &p, 4, tv );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);
	}
	
	// clean up
	polygon_clear(&p);
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
	Element *e;
	e = element_init(ObjColor, c);
	module_insert(md, e);
}

// Bezier Curve and Surface Module Functions

/*
 * use the de Casteljau algorithm to subdivide the Bezier curve divisions times,
 * then add the lines connecting the control points to the module.
 */
void module_bezierCurve(Module *m, BezierCurve *b, int divisions){
	Line templine;
	Point deCast[4];
	Point order1[3];
	Point order2[2];
	Point order3;
	BezierCurve tempbez;
	if(!m || !b){
		printf("Null passed to module_bezierCurve\n");
		return;
	}
	
	// compute all avg points for 3 orders, down to just one point 3rd order
	point_avg(&(order1[0]), &(b->c[0]), &(b->c[1]));
	point_avg(&(order1[1]), &(b->c[1]), &(b->c[2]));
	point_avg(&(order1[2]), &(b->c[2]), &(b->c[3]));
	point_avg(&(order2[0]), &(order1[0]), &(order1[1]));
	point_avg(&(order2[1]), &(order1[1]), &(order1[2]));
	point_avg(&order3, &(order2[0]), &(order2[1]));

	// base case, add six lines to module
	if(divisions == 1){
		// left half
		line_set(&templine, b->c[0], order1[0]);
		module_line(m, &templine);
		line_set(&templine, order1[0], order2[0]);
		module_line(m, &templine);
		line_set(&templine, order2[0], order3);
		module_line(m, &templine);
		// right half
		line_set(&templine, order3, order2[1]);
		module_line(m, &templine);
		line_set(&templine, order2[1], order1[2]);
		module_line(m, &templine);
		line_set(&templine, order1[2], b->c[3]);
		module_line(m, &templine);
	} 
	// recursively add left and right half bezier curves
	else {
		// left half
		point_copy(&(deCast[0]), &(b->c[0]));
		point_copy(&(deCast[1]), &(order1[0]));
		point_copy(&(deCast[2]), &(order2[0]));
		point_copy(&(deCast[3]), &(order3));
		bezierCurve_set(&tempbez, &(deCast[0]));
		module_bezierCurve(m, &tempbez, divisions-1);
		// right half
		point_copy(&(deCast[0]), &(order3));
		point_copy(&(deCast[1]), &(order2[1]));
		point_copy(&(deCast[2]), &(order1[2]));
		point_copy(&(deCast[3]), &(b->c[3]));
		bezierCurve_set(&tempbez, &(deCast[0]));
		module_bezierCurve(m, &tempbez, divisions-1);
	}
}

/*
 * use the de Casteljau algorithm to subdivide the Bezier surface divisions times,
 * then draw either the lines connecting the control points, if solid is 0, 
 * or draw triangles connecting the surface.
 */
void module_bezierSurface(Module *m, BezierSurface *b, int divisions, int solid){
	int i, j, k l;
	Line templine;
	BezierCurve bezCurves[4][2];
	Point deCast[4];
	Point order1[3];
	Point order2[2];
	Point order3;
	Point surfacePoints[4][4];
	BezierSurface tempBezSurf;
	if(!m || !b){
		printf("Null passed to module_bezierSurface\n");
		return;
	}
	
	// compute all avg points for 3 orders, down to just one point 3rd order
	// do for each of the four bezier curves
	for(i=0;i<4;i++){
		point_avg(&(order1[0]), &(b->c[i][0]), 	&([i]b->c[1]));
		point_avg(&(order1[1]), &(b->c[i][1]), 	&([i]b->c[2]));
		point_avg(&(order1[2]), &(b->c[i][2]), 	&([i]b->c[3]));
		point_avg(&(order2[0]), &(order1[0]), 	&(order1[1]));
		point_avg(&(order2[1]), &(order1[1]), 	&(order1[2]));
		point_avg(&(order3), 	&(order2[0]), 	&(order2[1]));
		// left half
		point_copy(&(deCast[0]), &(b->c[i][0]));
		point_copy(&(deCast[1]), &(order1[0]));
		point_copy(&(deCast[2]), &(order2[0]));
		point_copy(&(deCast[3]), &(order3));
		bezierCurve_set(&(bezCurves[i][0]), &(deCast[0]));
		// right half
		point_copy(&(deCast[0]), &(order3));
		point_copy(&(deCast[1]), &(order2[1]));
		point_copy(&(deCast[2]), &(order1[2]));
		point_copy(&(deCast[3]), &(b->c[i][3]));
		bezierCurve_set(&(bezCurves[i][1]), &(deCast[0]));
	}

	// now make the four new bezier surfaces by subdividing across
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){

			// consizer 0, 0 surface


		}
	}
}

