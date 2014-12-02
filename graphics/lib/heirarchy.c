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
				
	/* for antialiasing
	Module *thickLineMod = module_create();			
	Element *thickLineE;
	float dx, dy, dz, lineLength;
	Vector u, v, w;
	
				// in ObjLine case statement
				if(antialias){
					dx = tempLine.b.val[0]-tempLine.a.val[0];
					dy = tempLine.b.val[1]-tempLine.a.val[1];
					dz = tempLine.b.val[2]-tempLine.a.val[2];
					lineLength = sqrt(dx*dx+dy*dy+dz*dz);
					module_scale( thickLineMod, 1, lineLength, 1 );
					vector_set(&v, dx, dy, dz);
					vector_normalize(&v);
					vector_set(&u, -dz, dx, dy);
					vector_cross(&u, &v, &w);
					vector_cross(&v, &w, &u);
					vector_normalize(&u);
					vector_normalize(&w);
					module_rotateXYZ( thickLineMod, &u, &v, &w );
					module_translate( thickLineMod,	tempLine.a.val[0], 
													tempLine.a.val[1], 
													tempLine.a.val[2] );
					module_cylinder( thickLineMod, 4, 1, 1, 0, 0, 0 );
					thickLineE = element_init(ObjModule, thickLineMod);
					thickLineE->next = e->next;
					e->next = thickLineE;
				}
	*/
	
	// all locally needed variables
	Matrix LTM, tempGTM;
	Line tempLine;
	DrawState *tempds = drawstate_create();
	Point tempPointLTM, tempPointGTM, tempPointVTM;
	Polyline *tempPolyline = polyline_create();
	Polygon *tempPolygon = polygon_create();
	Element *e = md->head;
	int verbose = 0;
	matrix_identity(&LTM);
	
	// loop until the end of the linked list is reached
	while(e){
		if(verbose) printf("Handling type %d\n", e->type);
		// draw based on type
		switch(e->type){
			case ObjNone:
				break;
			case ObjPoint:
				if(verbose) printf("drawing ObjPoint\n");
				// copy, xform, normalize, draw
				matrix_xformPoint(&LTM, &(e->obj.point), &tempPointLTM);
				matrix_xformPoint(GTM, &tempPointLTM, &tempPointGTM);
				matrix_xformPoint(VTM, &tempPointGTM, &tempPointVTM);
				point_normalize(&(tempPointVTM));
				if(verbose) point_print(&tempPointVTM, stdout);
				point_draw(&tempPointVTM, src, ds->color);
				break;
			case ObjLine:
				if(verbose) printf("drawing ObjLine\n");
				line_copy(&tempLine, &(e->obj.line));
				// copy, xform, normalize, draw
				matrix_xformLine(&LTM, &tempLine);
				matrix_xformLine(GTM, &tempLine);
				matrix_xformLine(VTM, &tempLine);
				line_normalize(&tempLine);
				line_draw(&tempLine, src, ds->color);
				if(verbose) line_print(&tempLine, stdout);
				break;
			case ObjPolyline:
				if(verbose) printf("drawing ObjPolyline\n");
				// copy, xform, normalize, draw
				polyline_copy(tempPolyline, &(e->obj.polyline));
				matrix_xformPolyline(&LTM, tempPolyline);
				matrix_xformPolyline(GTM, tempPolyline);
				matrix_xformPolyline(VTM, tempPolyline);
				polyline_normalize(tempPolyline);
				if(verbose) polyline_print(tempPolyline, stdout);
				polyline_draw(tempPolyline, src, ds->color);
				break;
			case ObjPolygon:
				// copy, xform, normalize, draw
				polygon_copy(tempPolygon, &(e->obj.polygon));
				if(verbose) printf("drawing ObjPolygon\n");
				matrix_xformPolygon(&LTM, tempPolygon);
				matrix_xformPolygon(GTM, tempPolygon);
				if(ds->shade == ShadeGouraud || ds->shade == ShadeFlat){
					polygon_shade(tempPolygon, lighting, ds);
				}
				matrix_xformPolygon(VTM, tempPolygon);
				polygon_normalize(tempPolygon);
				if(verbose) polygon_print(tempPolygon, stdout);
				polygon_drawShade(tempPolygon, src, ds, NULL);
				break;
			case ObjColor:
				if(verbose) printf("drawing ObjColor\n");
				drawstate_setColor(ds, e->obj.color);
				break;
			case ObjBodyColor:
				if(verbose) printf("drawing ObjBodyColor\n");
				drawstate_setBody(ds, e->obj.color);
				break;
			case ObjSurfaceColor:
				if(verbose) printf("drawing ObjSurfaceColor\n");
				drawstate_setSurface(ds, e->obj.color);
				break;
			case ObjSurfaceCoeff:
				if(verbose) printf("drawing ObjSurfaceCoeff\n");
				drawstate_setSurfaceCoeff(ds, e->obj.coeff);
				break;
			case ObjLight:
				if(verbose) printf("drawing ObjLight\n");
				break;
			case ObjIdentity:
				if(verbose) printf("drawing ObjIdentity\n");
				matrix_identity(&LTM);
				break;
			case ObjMatrix:
				if(verbose) printf("drawing ObjMatrix\n");
				matrix_multiply(&(e->obj.matrix), &LTM, &LTM);
				break;
			case ObjModule:
				if(verbose) printf("drawing ObjModule\n");
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
	Vector tn[4], front, back, left, right, top, bottom;
	int i;
	
	// initialize polygon
	polygon_init( &p );
	polygon_setSided( &p, 1 );
	
	// initialize line
	line_zBuffer(&l, 1);
	
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
		for(i=0;i<3;i++){
			line_set( &l, v[i], v[i+1] );
			e = element_init(ObjLine, &l);
			module_insert(md, e);
		}
		line_set( &l, v[3], v[0] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		
		// back face lines
		for(i=4;i<7;i++){
			line_set( &l, v[i], v[i+1] );
			e = element_init(ObjLine, &l);
			module_insert(md, e);
		}
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
		vector_set(&front, 0, 0, -1);
		vector_set(&back, 0, 0, 1);
		vector_set(&left, -1, 0, 0);
		vector_set(&right, 1, 0, 0);
		vector_set(&top, 0, 1, 0);
		vector_set(&bottom, 0, -1, 0);

		// front side
		polygon_set( &p, 4, &(v[0]) );
		vector_copy( &tn[0], &front );
		vector_copy( &tn[1], &front );
		vector_copy( &tn[2], &front );
		vector_copy( &tn[3], &front );
		polygon_setNormals( &p, 4, tn );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// back side
		polygon_set( &p, 4, &(v[4]) );
		vector_copy( &tn[0], &back );
		vector_copy( &tn[1], &back );
		vector_copy( &tn[2], &back );
		vector_copy( &tn[3], &back );
		polygon_setNormals( &p, 4, tn );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// top side
		point_copy( &tv[0], &v[2] );
		point_copy( &tv[1], &v[3] );
		point_copy( &tv[2], &v[7] );
		point_copy( &tv[3], &v[6] );
		polygon_set( &p, 4, tv );
		vector_copy( &tn[0], &top );
		vector_copy( &tn[1], &top );
		vector_copy( &tn[2], &top );
		vector_copy( &tn[3], &top );
		polygon_setNormals( &p, 4, tn );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// bottom side
		point_copy( &tv[0], &v[0] );
		point_copy( &tv[1], &v[1] );
		point_copy( &tv[2], &v[5] );
		point_copy( &tv[3], &v[4] );
		polygon_set( &p, 4, tv );
		vector_copy( &tn[0], &bottom );
		vector_copy( &tn[1], &bottom );
		vector_copy( &tn[2], &bottom );
		vector_copy( &tn[3], &bottom );
		polygon_setNormals( &p, 4, tn );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// left side
		point_copy( &tv[0], &v[0] );
		point_copy( &tv[1], &v[3] );
		point_copy( &tv[2], &v[7] );
		point_copy( &tv[3], &v[4] );
		polygon_set( &p, 4, tv );
		vector_copy( &tn[0], &left );
		vector_copy( &tn[1], &left );
		vector_copy( &tn[2], &left );
		vector_copy( &tn[3], &left );
		polygon_setNormals( &p, 4, tn );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);

		// right side
		point_copy( &tv[0], &v[1] );
		point_copy( &tv[1], &v[2] );
		point_copy( &tv[2], &v[6] );
		point_copy( &tv[3], &v[5] );
		polygon_set( &p, 4, tv );
		vector_copy( &tn[0], &right );
		vector_copy( &tn[1], &right );
		vector_copy( &tn[2], &right );
		vector_copy( &tn[3], &right );
		polygon_setNormals( &p, 4, tn );
		e = element_init(ObjPolygon, &p);
		module_insert(md, e);
	}
	// clean up
	polygon_clear(&p);
}

/*
 * insert a pyramid into the module
 */
void module_pyramid(Module *md, int solid, float size, float x, float y, float z){

	if(!md){
		printf("Null md passed to module_pyramid\n");
		return;
	}
	Polygon side;
	Point tv[3];
    Point v[5];
    Line l;
    Element *e;
	Vector tn[4], front, back, left, right, bottom;
    int i;
    
	// initialize polygon
	polygon_init( &side );
	polygon_setSided( &side, 1 );
	
	// initialize line
	line_zBuffer(&l, 1);

    // corners of the pyramid
    point_set3D(&v[0], -1, -1, -1 );
    point_set3D(&v[1],  1, -1, -1 );
    point_set3D(&v[2],  1,  -1, 1 );
    point_set3D(&v[3], -1,  -1, 1 );
    point_set3D(&v[4], 0, 0, 0);
    //printf("points created\n");

    // set pyramid parameters
    module_scale(md, (int)size, (int)size, (int)size);
	module_translate(md, (float)x, (float)y, (float)z);
	//printf("parameters set\n");

    if (solid == 0){
    	// add only lines
    	// foundation
		for(i=0;i<3;i++){
			line_set( &l, v[i], v[i+1] );
			e = element_init(ObjLine, &l);
			module_insert(md, e);
		}
		line_set( &l, v[3], v[0] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		
		// connecting lines
		line_set( &l, v[4], v[0] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[1], v[4] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[2], v[4] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);
		line_set( &l, v[3], v[4] );
		e = element_init(ObjLine, &l);
		module_insert(md, e);

		//printf("successfully passed to module\n");
    } else{
	 	// use polygons ( 5 of them )
		vector_set(&front, 0, 1, -1);
		vector_set(&back, 0, 1, 1);
		vector_set(&left, -1, 1, 0);
		vector_set(&right, 1, 1, 0);
		vector_set(&bottom, 0, -1, 0);

    	// front side
	    point_copy(&tv[0], &v[0]);
	    point_copy(&tv[1], &v[1]);
	    point_copy(&tv[2], &v[4]);
	    polygon_set(&side, 3, tv);
		vector_copy( &tn[0], &front );
		vector_copy( &tn[1], &front );
		vector_copy( &tn[2], &front );
		polygon_setNormals( &p, 3, tn );
	    e = element_init(ObjPolygon, &side);
		module_insert(md, e);

	    // back side
	    point_copy(&tv[0], &v[3]);
	    point_copy(&tv[1], &v[2]);
	    point_copy(&tv[2], &v[4]);
	    polygon_set(&side, 3, tv);
		vector_copy( &tn[0], &back );
		vector_copy( &tn[1], &back );
		vector_copy( &tn[2], &back );
		polygon_setNormals( &p, 3, tn );
	    e = element_init(ObjPolygon, &side);
		module_insert(md, e);

	    // bottom side
	    polygon_set(&side, 4, &(v[0]));
		vector_copy( &tn[0], &bottom );
		vector_copy( &tn[1], &bottom );
		vector_copy( &tn[2], &bottom );
		vector_copy( &tn[3], &bottom );
		polygon_setNormals( &p, 4, tn );
	    e = element_init(ObjPolygon, &side);
		module_insert(md, e);

	    // left side
	    point_copy(&tv[0], &v[0]);
	    point_copy(&tv[1], &v[3]);
	    point_copy(&tv[2], &v[4]);
	    polygon_set(&side, 3, tv);
		vector_copy( &tn[0], &left );
		vector_copy( &tn[1], &left );
		vector_copy( &tn[2], &left );
		polygon_setNormals( &p, 3, tn );
	    e = element_init(ObjPolygon, &side);
		module_insert(md, e);

	    // right side
	    point_copy(&tv[0], &v[1]);
	    point_copy(&tv[1], &v[2]);
	    point_copy(&tv[2], &v[4]);
	    polygon_set(&side, 3, tv); 
		vector_copy( &tn[0], &right );
		vector_copy( &tn[1], &right );
		vector_copy( &tn[2], &right );
		polygon_setNormals( &p, 3, tn );
		e = element_init(ObjPolygon, &side);
		module_insert(md, e);

		//printf("successfully passed to module\n");
    }

    polygon_clear(&side);
}

/*
* Sourced from coursework file test6b.c (Bruce Maxwell)
*/
void module_cylinder( Module *mod, int sides, int fill, int size, float x, float y, float z) {
	Polygon p;
	Point xtop, xbot, pt[4];;
	Element *e;
	Line l;
	double x1, x2, z1, z2;
	Vector tn[4], top, side, bottom;
	int i;

	if(!mod){
		printf("Null md passed to module_cylinder\n");
		return;
	}

	// set cylinder parameters
    module_scale(mod, (int)size, (int)size, (int)size);
	module_translate(mod, (float)x, (float)y, (float)z);
	//printf("parameters set\n");

	// initialize polygon
	polygon_init( &p );
	polygon_setSided( &p, 1 );
	
	// initialize line
	line_zBuffer(&l, 1);
	
	point_set3D( &xtop, 0, 1.0, 0.0 );
	point_set3D( &xbot, 0, 0.0, 0.0 );

	if (fill == 1){

		vector_set(&top, 0, 1, 0);
		vector_set(&bottom, 0, -1, 0);
		// make a fan for the top and bottom sides
		// and quadrilaterals for the sides
		for(i=0;i<sides;i++) {
			vector_set(&side, 0, 1, 0);

			x1 = cos( i * M_PI * 2.0 / sides );// 1
			z1 = sin( i * M_PI * 2.0 / sides );// 0
			x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides ); // cos(2pi/4)=0
			z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides ); // sin(2pi/4)=1

			point_copy( &pt[0], &xtop );
			point_set3D( &pt[1], x1, 1.0, z1 );
			point_set3D( &pt[2], x2, 1.0, z2 );
			polygon_set( &p, 3, pt );
			vector_copy( &tn[0], &top );
			vector_copy( &tn[1], &top );
			vector_copy( &tn[2], &top );
			polygon_setNormals( &p, 3, tn );
			e = element_init(ObjPolygon, &p);
			module_insert(mod, e);

			point_copy( &pt[0], &xbot );
			point_set3D( &pt[1], x1, 0.0, z1 );
			point_set3D( &pt[2], x2, 0.0, z2 );
			polygon_set( &p, 3, pt );
			vector_copy( &tn[0], &bottom );
			vector_copy( &tn[1], &bottom );
			vector_copy( &tn[2], &bottom );
			polygon_setNormals( &p, 3, tn );
			e = element_init(ObjPolygon, &p);
			module_insert(mod, e);

			point_set3D( &pt[0], x1, 0.0, z1 );
			point_set3D( &pt[1], x2, 0.0, z2 );
			point_set3D( &pt[2], x2, 1.0, z2 );
			point_set3D( &pt[3], x1, 1.0, z1 );
			polygon_set( &p, 4, pt );
			vector_copy( &tn[0], &side );
			vector_copy( &tn[1], &side );
			vector_copy( &tn[2], &side );
			vector_copy( &tn[3], &side );
			polygon_setNormals( &p, 4, tn );
			e = element_init(ObjPolygon, &p);
			module_insert(mod, e);
		}
	} else{
		// make a fan for the top and bottom sides
		// and quadrilaterals for the sides
		for(i=0;i<sides;i++) {

			x1 = cos( i * M_PI * 2.0 / sides );
			z1 = sin( i * M_PI * 2.0 / sides );
			x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
			z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

			point_copy( &pt[0], &xtop );
			point_set3D( &pt[1], x1, 1.0, z1 );
			point_set3D( &pt[2], x2, 1.0, z2 );

			line_set( &l, pt[0], pt[1] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[1], pt[2] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[2], pt[0]);
			e = element_init(ObjLine, &l);
			module_insert(mod, e);

			point_copy( &pt[0], &xbot );
			point_set3D( &pt[1], x1, 0.0, z1 );
			point_set3D( &pt[2], x2, 0.0, z2 );

			line_set( &l, pt[0], pt[1] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[1], pt[2] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[2], pt[0]);
			e = element_init(ObjLine, &l);
			module_insert(mod, e);

			point_set3D( &pt[0], x1, 0.0, z1 );
			point_set3D( &pt[1], x2, 0.0, z2 );
			point_set3D( &pt[2], x2, 1.0, z2 );
			point_set3D( &pt[3], x1, 1.0, z1 );

			line_set( &l, pt[0], pt[1] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[1], pt[2] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[2], pt[3]);
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[3], pt[0]);
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
		}
	}

	polygon_clear( &p );
}

/*
* Sourced from coursework file test6b.c (Bruce Maxwell)
*/
void module_cone( Module *mod, int sides, int fill, int size, float x, float y, float z) {
	Polygon p;
	Point xtop, xbot;
	Element *e;
	Line l;
	double x1, x2, z1, z2;
	int i;

	if(!mod){
		printf("Null md passed to module_cylinder\n");
		return;
	}

	// set cone parameters
    module_scale(mod, (int)size, (int)size, (int)size);
	module_translate(mod, (float)x, (float)y, (float)z);
	printf("parameters set\n");

	// initialize polygon
	polygon_init( &p );
	polygon_setSided( &p, 1 );
	
	// initialize line
	line_zBuffer(&l, 1);
	
	point_set3D( &xtop, 0, 1.0, 0.0 );
	point_set3D( &xbot, 0, 0.0, 0.0 );

	if (fill == 1){
		// make a fan for the top and bottom sides
		// and quadrilaterals for the sides
		for(i=0;i<sides;i++) {
			Point pt[6];

			x1 = cos( i * M_PI * 2.0 / sides );
			z1 = sin( i * M_PI * 2.0 / sides );
			x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
			z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

			point_copy( &pt[0], &xbot );
			point_set3D( &pt[1], x1, 0.0, z1 );
			point_set3D( &pt[2], x2, 0.0, z2 );

			polygon_set( &p, 3, pt );
			e = element_init(ObjPolygon, &p);
			module_insert(mod, e);

			point_set3D( &pt[3], x1, 0.0, z1 );
			point_set3D( &pt[4], x2, 0.0, z2 );
			point_copy( &pt[5], &xtop);

			polygon_set( &p, 3, &pt[3] );
			e = element_init(ObjPolygon, &p);
			module_insert(mod, e);
		}
	} else{
		// make a fan for the top and bottom sides
		// and quadrilaterals for the sides
		for(i=0;i<sides;i++) {
			Point pt[8];

			x1 = cos( i * M_PI * 2.0 / sides );
			z1 = sin( i * M_PI * 2.0 / sides );
			x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
			z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

			point_copy( &pt[0], &xbot );
			point_set3D( &pt[1], x1, 0.0, z1 );
			point_set3D( &pt[2], x2, 0.0, z2 );

			line_set( &l, pt[0], pt[1] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[1], pt[2] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[2], pt[0]);
			e = element_init(ObjLine, &l);
			module_insert(mod, e);

			point_set3D( &pt[3], x1, 0.0, z1 );
			point_set3D( &pt[4], x2, 0.0, z2 );
			point_set3D( &pt[5], x2, 1.0, z2 );
			point_set3D( &pt[6], x1, 1.0, z1 );
			point_copy( &pt[7], &xtop);

			line_set( &l, pt[0], pt[7] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[1], pt[7] );
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[2], pt[7]);
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
			line_set( &l, pt[3], pt[7]);
			e = element_init(ObjLine, &l);
			module_insert(mod, e);
		}
	}
	polygon_clear( &p );
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

/*
 * Adds the body color value to the tail of the module’s list.
 */
void module_bodyColor(Module *md, Color *c){
	if(!md){
		printf("Null module passed to module_bodyColor\n");
		return;
	}
	if(!c){
		printf("Null color passed to module_bodyColor\n");
		return;
	}
	Element *e;
	e = element_init(ObjBodyColor, c);
	module_insert(md, e);
}

/*
 * Adds the surface color value to the tail of the module’s list.
 */
void module_surfaceColor(Module *md, Color *c){
	if(!md){
		printf("Null module passed to module_surfaceColor\n");
		return;
	}
	if(!c){
		printf("Null color passed to module_surfaceColor\n");
		return;
	}
	Element *e;
	e = element_init(ObjSurfaceColor, c);
	module_insert(md, e);
}

/*
 * Adds the specular coefficient to the tail of the module’s list
 */
void module_surfaceCoeff(Module *md, float coeff){
	if(!md){
		printf("Null module passed to module_surfaceCoeff\n");
		return;
	}
	Element *e;
	e = element_init(ObjSurfaceCoeff, &coeff);
	module_insert(md, e);
}

// Bezier Curve and Surface Module Functions

static inline void deCasteljau(Point *dest, Point *controls){
	Point order1[3];
	Point order2[2];
	Point order3;
	
	point_avg(&(order1[0]), &(controls[0]), &(controls[1]));
	point_avg(&(order1[1]), &(controls[1]), &(controls[2]));
	point_avg(&(order1[2]), &(controls[2]), &(controls[3]));
	point_avg(&(order2[0]), &(order1[0]), 	&(order1[1]));
	point_avg(&(order2[1]), &(order1[1]), 	&(order1[2]));
	point_avg(&(order3), 	&(order2[0]), 	&(order2[1]));
	// left half
	dest[0] = controls[0];
	dest[1] = order1[0];
	dest[2] = order2[0];
	dest[3] = order3;
	// right half
	dest[4] = order2[1];
	dest[5] = order1[2];
	dest[6] = controls[3];
}

/*
 * use the de Casteljau algorithm to subdivide the Bezier curve divisions times,
 * then add the lines connecting the control points to the module.
 */
void module_bezierCurve(Module *m, BezierCurve *b, int divisions){
	Line tempLine;
	Point deCast[7];
	BezierCurve tempbez;
	if(!m || !b){
		printf("Null passed to module_bezierCurve\n");
		return;
	}
	
	// initialize line
	line_zBuffer(&tempLine, b->zBuffer);
	
	// initialize temporary curve
	tempbez.zBuffer = b->zBuffer;
	
	// base case, add six lines to module
	if(divisions == 0){
		line_set(&tempLine, b->c[0], b->c[1]);
		module_line(m, &tempLine);
		line_set(&tempLine, b->c[1], b->c[2]);
		module_line(m, &tempLine);
		line_set(&tempLine, b->c[2], b->c[3]);
		module_line(m, &tempLine);
		return;
	}
	
	// compute all avg points for 3 orders, down to just one point 3rd order
	deCasteljau(&(deCast[0]), &(b->c[0]));
	// left half
	bezierCurve_set(&tempbez, &(deCast[0]));
	module_bezierCurve(m, &tempbez, divisions-1);
	// right half
	bezierCurve_set(&tempbez, &(deCast[3]));
	module_bezierCurve(m, &tempbez, divisions-1);
}

/*
 * use the de Casteljau algorithm to subdivide the Bezier surface divisions times,
 * then draw either the lines connecting the control points, if solid is 0, 
 * or draw triangles connecting the surface.
 */
void module_bezierSurface(Module *m, BezierSurface *b, int divisions, int solid){
	int i, j, k, l;
	Line tempLine;
	Point grid[7][7];
	Point controls[7];
	Point deCast[7];
	Point surfacePoints[16];
	BezierSurface tempBezSurf;
	Polygon *temptri = polygon_create();
	if(!m || !b){
		printf("Null passed to module_bezierSurface\n");
		return;
	}
	
	// initialize polygon
	polygon_setSided( temptri, 0 );
	polygon_zBuffer(temptri, b->zBuffer);
	
	// initialize line
	line_zBuffer(&tempLine, b->zBuffer);
	
	// initialize temporary surface
	tempBezSurf.zBuffer = b->zBuffer;
	
	// base case
	if(divisions == 0){
		// lines
		if(solid == 0){
			for(i=0;i<4;i++){
				for(j=0;j<3;j++){
					line_set(&tempLine, b->c[i][j], b->c[i][j+1]);
					module_line(m, &tempLine);
					line_set(&tempLine, b->c[j][i], b->c[j+1][i]);
					module_line(m, &tempLine);
				}
			}
		} 
		// triangles
		else {
			controls[0] = b->c[0][0];
			controls[1] = b->c[0][3];
			controls[2] = b->c[3][3];
			controls[3] = b->c[3][0];
			controls[4] = b->c[0][0];
			polygon_set(temptri, 3, &(controls[0]));
			module_polygon(m, temptri);
			polygon_set(temptri, 3, &(controls[2]));
			module_polygon(m, temptri);
		}
	}
	
	// divide and recurse
	else {

		// compute all avg points for 3 orders, down to just one point 3rd order
		// do for each of the four bezier curves
		for(i=0;i<4;i++){
			deCasteljau(&(deCast[0]), &(b->c[i][0]));
			for(j=0;j<7;j++){
				grid[2*i][j] = deCast[j];
			}
		}

		// now traverse the other direction, populating grid
		for(i=0;i<7;i++){
			for(j=0;j<4;j++){
				controls[j] = grid[2*j][i];
			}
			deCasteljau(&(deCast[0]), &(controls[0]));
			for(j=0;j<7;j++){
				grid[j][i] = deCast[j];
			}
		}

		// now make the four new bezier surfaces by subdividing across
		for(i=0;i<2;i++){
			for(j=0;j<2;j++){
				for(k=0;k<4;k++){
					for(l=0;l<4;l++){
						surfacePoints[4*k+l] = grid[k+3*i][l+3*j];
					}
				}
				bezierSurface_set(&tempBezSurf, &(surfacePoints[0]));
				// recursive call
				module_bezierSurface(m, &tempBezSurf, divisions-1, solid);
			}
		}
	}
	
	// clean up
	polygon_free(temptri);
}

/*
 * add a teapot to the module with the specified number of divisions
 */
void module_teapot(Module *m, int divisions, int solid){
	int i, j;
	Point teapot[127] = 
	{
		{{  0.2000,  0.0000, 2.70000, 1.0 }}, {{  0.2000, -0.1120, 2.70000, 1.0 }},
		{{  0.1120, -0.2000, 2.70000, 1.0 }}, {{  0.0000, -0.2000, 2.70000, 1.0 }},
		{{  1.3375,  0.0000, 2.53125, 1.0 }}, {{  1.3375, -0.7490, 2.53125, 1.0 }},
		{{  0.7490, -1.3375, 2.53125, 1.0 }}, {{  0.0000, -1.3375, 2.53125, 1.0 }},
		{{  1.4375,  0.0000, 2.53125, 1.0 }}, {{  1.4375, -0.8050, 2.53125, 1.0 }},
		{{  0.8050, -1.4375, 2.53125, 1.0 }}, {{  0.0000, -1.4375, 2.53125, 1.0 }},
		{{  1.5000,  0.0000, 2.40000, 1.0 }}, {{  1.5000, -0.8400, 2.40000, 1.0 }},
		{{  0.8400, -1.5000, 2.40000, 1.0 }}, {{  0.0000, -1.5000, 2.40000, 1.0 }},
		{{  1.7500,  0.0000, 1.87500, 1.0 }}, {{  1.7500, -0.9800, 1.87500, 1.0 }},
		{{  0.9800, -1.7500, 1.87500, 1.0 }}, {{  0.0000, -1.7500, 1.87500, 1.0 }},
		{{  2.0000,  0.0000, 1.35000, 1.0 }}, {{  2.0000, -1.1200, 1.35000, 1.0 }},
		{{  1.1200, -2.0000, 1.35000, 1.0 }}, {{  0.0000, -2.0000, 1.35000, 1.0 }},
		{{  2.0000,  0.0000, 0.90000, 1.0 }}, {{  2.0000, -1.1200, 0.90000, 1.0 }},
		{{  1.1200, -2.0000, 0.90000, 1.0 }}, {{  0.0000, -2.0000, 0.90000, 1.0 }},
		{{ -2.0000,  0.0000, 0.90000, 1.0 }}, {{  2.0000,  0.0000, 0.45000, 1.0 }},
		{{  2.0000, -1.1200, 0.45000, 1.0 }}, {{  1.1200, -2.0000, 0.45000, 1.0 }},
		{{  0.0000, -2.0000, 0.45000, 1.0 }}, {{  1.5000,  0.0000, 0.22500, 1.0 }},
		{{  1.5000, -0.8400, 0.22500, 1.0 }}, {{  0.8400, -1.5000, 0.22500, 1.0 }},
		{{  0.0000, -1.5000, 0.22500, 1.0 }}, {{  1.5000,  0.0000, 0.15000, 1.0 }},
		{{  1.5000, -0.8400, 0.15000, 1.0 }}, {{  0.8400, -1.5000, 0.15000, 1.0 }},
		{{  0.0000, -1.5000, 0.15000, 1.0 }}, {{ -1.6000,  0.0000, 2.02500, 1.0 }},
		{{ -1.6000, -0.3000, 2.02500, 1.0 }}, {{ -1.5000, -0.3000, 2.25000, 1.0 }},
		{{ -1.5000,  0.0000, 2.25000, 1.0 }}, {{ -2.3000,  0.0000, 2.02500, 1.0 }},
		{{ -2.3000, -0.3000, 2.02500, 1.0 }}, {{ -2.5000, -0.3000, 2.25000, 1.0 }},
		{{ -2.5000,  0.0000, 2.25000, 1.0 }}, {{ -2.7000,  0.0000, 2.02500, 1.0 }},
		{{ -2.7000, -0.3000, 2.02500, 1.0 }}, {{ -3.0000, -0.3000, 2.25000, 1.0 }},
		{{ -3.0000,  0.0000, 2.25000, 1.0 }}, {{ -2.7000,  0.0000, 1.80000, 1.0 }},
		{{ -2.7000, -0.3000, 1.80000, 1.0 }}, {{ -3.0000, -0.3000, 1.80000, 1.0 }},
		{{ -3.0000,  0.0000, 1.80000, 1.0 }}, {{ -2.7000,  0.0000, 1.57500, 1.0 }},
		{{ -2.7000, -0.3000, 1.57500, 1.0 }}, {{ -3.0000, -0.3000, 1.35000, 1.0 }},
		{{ -3.0000,  0.0000, 1.35000, 1.0 }}, {{ -2.5000,  0.0000, 1.12500, 1.0 }},
		{{ -2.5000, -0.3000, 1.12500, 1.0 }}, {{ -2.6500, -0.3000, 0.93750, 1.0 }},
		{{ -2.6500,  0.0000, 0.93750, 1.0 }}, {{ -2.0000, -0.3000, 0.90000, 1.0 }},
		{{ -1.9000, -0.3000, 0.60000, 1.0 }}, {{ -1.9000,  0.0000, 0.60000, 1.0 }},
		{{  1.7000,  0.0000, 1.42500, 1.0 }}, {{  1.7000, -0.6600, 1.42500, 1.0 }},
		{{  1.7000, -0.6600, 0.60000, 1.0 }}, {{  1.7000,  0.0000, 0.60000, 1.0 }},
		{{  2.6000,  0.0000, 1.42500, 1.0 }}, {{  2.6000, -0.6600, 1.42500, 1.0 }},
		{{  3.1000, -0.6600, 0.82500, 1.0 }}, {{  3.1000,  0.0000, 0.82500, 1.0 }},
		{{  2.3000,  0.0000, 2.10000, 1.0 }}, {{  2.3000, -0.2500, 2.10000, 1.0 }},
		{{  2.4000, -0.2500, 2.02500, 1.0 }}, {{  2.4000,  0.0000, 2.02500, 1.0 }},
		{{  2.7000,  0.0000, 2.40000, 1.0 }}, {{  2.7000, -0.2500, 2.40000, 1.0 }},
		{{  3.3000, -0.2500, 2.40000, 1.0 }}, {{  3.3000,  0.0000, 2.40000, 1.0 }},
		{{  2.8000,  0.0000, 2.47500, 1.0 }}, {{  2.8000, -0.2500, 2.47500, 1.0 }},
		{{  3.5250, -0.2500, 2.49375, 1.0 }}, {{  3.5250,  0.0000, 2.49375, 1.0 }},
		{{  2.9000,  0.0000, 2.47500, 1.0 }}, {{  2.9000, -0.1500, 2.47500, 1.0 }},
		{{  3.4500, -0.1500, 2.51250, 1.0 }}, {{  3.4500,  0.0000, 2.51250, 1.0 }},
		{{  2.8000,  0.0000, 2.40000, 1.0 }}, {{  2.8000, -0.1500, 2.40000, 1.0 }},
		{{  3.2000, -0.1500, 2.40000, 1.0 }}, {{  3.2000,  0.0000, 2.40000, 1.0 }},
		{{  0.0000,  0.0000, 3.15000, 1.0 }}, {{  0.8000,  0.0000, 3.15000, 1.0 }},
		{{  0.8000, -0.4500, 3.15000, 1.0 }}, {{  0.4500, -0.8000, 3.15000, 1.0 }},
		{{  0.0000, -0.8000, 3.15000, 1.0 }}, {{  0.0000,  0.0000, 2.85000, 1.0 }},
		{{  1.4000,  0.0000, 2.40000, 1.0 }}, {{  1.4000, -0.7840, 2.40000, 1.0 }},
		{{  0.7840, -1.4000, 2.40000, 1.0 }}, {{  0.0000, -1.4000, 2.40000, 1.0 }},
		{{  0.4000,  0.0000, 2.55000, 1.0 }}, {{  0.4000, -0.2240, 2.55000, 1.0 }},
		{{  0.2240, -0.4000, 2.55000, 1.0 }}, {{  0.0000, -0.4000, 2.55000, 1.0 }},
		{{  1.3000,  0.0000, 2.55000, 1.0 }}, {{  1.3000, -0.7280, 2.55000, 1.0 }},
		{{  0.7280, -1.3000, 2.55000, 1.0 }}, {{  0.0000, -1.3000, 2.55000, 1.0 }},
		{{  1.3000,  0.0000, 2.40000, 1.0 }}, {{  1.3000, -0.7280, 2.40000, 1.0 }},
		{{  0.7280, -1.3000, 2.40000, 1.0 }}, {{  0.0000, -1.3000, 2.40000, 1.0 }},
		{{  0.0000,  0.0000, 0.00000, 1.0 }}, {{  1.4250, -0.7980, 0.00000, 1.0 }},
		{{  1.5000,  0.0000, 0.07500, 1.0 }}, {{  1.4250,  0.0000, 0.00000, 1.0 }},
		{{  0.7980, -1.4250, 0.00000, 1.0 }}, {{  0.0000, -1.5000, 0.07500, 1.0 }},
		{{  0.0000, -1.4250, 0.00000, 1.0 }}, {{  1.5000, -0.8400, 0.07500, 1.0 }},
		{{  0.8400, -1.5000, 0.07500, 1.0 }}
	};
	
	int rim[16] = 
		{ 102, 103, 104, 105,   4,   5,   6,   7,
		    8,   9,  10,  11,  12,  13,  14,  15 };
	int body[2][16] = {
		{  12,  13,  14,  15,  16,  17,  18,  19,
		   20,  21,  22,  23,  24,  25,  26,  27 },
		{  24,  25,  26,  27,  29,  30,  31,  32,
		   33,  34,  35,  36,  37,  38,  39,  40 } };
	int lid[2][16] = {
		{  96,  96,  96,  96,  97,  98,  99, 100,
		  101, 101, 101, 101,   0,   1,   2,   3 },
		{   0,   1,   2,   3, 106, 107, 108, 109,
		  110, 111, 112, 113, 114, 115, 116, 117 } };
	int handle[2][16] = {
		{  41,  42,  43,  44,  45,  46,  47,  48,
		   49,  50,  51,  52,  53,  54,  55,  56 },
		{  53,  54,  55,  56,  57,  58,  59,  60,
		   61,  62,  63,  64,  28,  65,  66,  67 } };
	int spout[2][16] = {
		{  68,  69,  70,  71,  72,  73,  74,  75,
		   76,  77,  78,  79,  80,  81,  82,  83 },
		{  80,  81,  82,  83,  84,  85,  86,  87,
		   88,  89,  90,  91,  92,  93,  94,  95 } };
	int bottom[16] = 
		{ 118, 118, 118, 118, 124, 122, 119, 121,
		  123, 126, 125, 120,  40,  39,  38,  37 };
		  
	BezierSurface rimSurf, body1Surf, body2Surf, lid1Surf, lid2Surf, 
				handle1Surf, handle2Surf, spout1Surf, spout2Surf, bottomSurf;
				
	// init all surfaces
	rimSurf.zBuffer = body1Surf.zBuffer = body2Surf.zBuffer = lid1Surf.zBuffer =
	lid2Surf.zBuffer = handle1Surf.zBuffer = handle2Surf.zBuffer = 
	spout1Surf.zBuffer = spout2Surf.zBuffer = bottomSurf.zBuffer = 1;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			rimSurf.c[i][j] = 		teapot[rim[j+4*i]];
			body1Surf.c[i][j] = 	teapot[body[0][j+4*i]];
			body2Surf.c[i][j] = 	teapot[body[1][j+4*i]];
			lid1Surf.c[i][j] = 		teapot[lid[0][j+4*i]];
			lid2Surf.c[i][j] = 		teapot[lid[1][j+4*i]];
			handle1Surf.c[i][j] = 	teapot[handle[0][j+4*i]];
			handle2Surf.c[i][j] = 	teapot[handle[1][j+4*i]];
			spout1Surf.c[i][j] = 	teapot[spout[0][j+4*i]];
			spout2Surf.c[i][j] = 	teapot[spout[1][j+4*i]];
			bottomSurf.c[i][j] = 	teapot[bottom[j+4*i]];
		}
	}
	
	// add surfaces to module so y is up
	module_rotateX(m, cos(1.5*M_PI), sin(1.5*M_PI));
	for(i=0;i<4;i++){
		module_rotateY(m, cos(0.5*M_PI*i), sin(0.5*M_PI*i));
		module_bezierSurface(m, &rimSurf, divisions, solid);
		module_bezierSurface(m, &body1Surf, divisions, solid);
		module_bezierSurface(m, &body2Surf, divisions, solid);
		module_bezierSurface(m, &lid1Surf, divisions, solid);
		module_bezierSurface(m, &lid2Surf, divisions, solid);
		module_bezierSurface(m, &bottomSurf, divisions, solid);
	}
	module_bezierSurface(m, &handle1Surf, divisions, solid);
	module_bezierSurface(m, &handle2Surf, divisions, solid);
	module_bezierSurface(m, &spout1Surf, divisions, solid);
	module_bezierSurface(m, &spout2Surf, divisions, solid);
	for(i=0;i<4;i++){ // reflect handle over xz plane
		for(j=0;j<4;j++){
			handle1Surf.c[i][j].val[1] = -1*handle1Surf.c[i][j].val[1];
			handle2Surf.c[i][j].val[1] = -1*handle2Surf.c[i][j].val[1];
			spout1Surf.c[i][j].val[1] = -1*spout1Surf.c[i][j].val[1];
			spout2Surf.c[i][j].val[1] = -1*spout2Surf.c[i][j].val[1];
		}
	}
	module_bezierSurface(m, &handle1Surf, divisions, solid);
	module_bezierSurface(m, &handle2Surf, divisions, solid);
	module_bezierSurface(m, &spout1Surf, divisions, solid);
	module_bezierSurface(m, &spout2Surf, divisions, solid);
}
