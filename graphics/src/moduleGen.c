/*
	Ian Tibbetts
	Fall 2014

	for easily generating modules
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

typedef union {
	Point point;
	Line line;
	Polyline polyline;
	Polygon polygon;
	Matrix matrix;
	Color color;
	float coeff;
	Module *module;
} Item;

typedef struct{
	char *name;
	Item item;
} TableItem;

int main(int argc, char *argv[]) {

	// variables for the view and image
	Point vrp;
	Vector xaxis;
	DrawState *ds;
	Image *src;
	View2D view2D;
	View3D view3D;
	Matrix vtm;
	Matrix gtm;

	// variables for parsing
	char *infilename, *outfilename;
	FILE *infile;
	char *linein, *firstword, *secondword, *thirdword, *searchname;
	char *delim = " \n";
	int i, j, is2D;
	int activeMod = -1;
	int numpoints = 0;
	int numlines = 0;
	int numpolylines = 0;
	int numpolygons = 0;
	TableItem *pt[1000], *l[1000], *pl[1000], *pg[1000], *mod[1000];
	Point temppts[50];
	Line templine;
	Polyline temppolyline;
	Polygon temppolygon;
	float x, y, z;

	// init
	polyline_init(&temppolyline);
	polygon_init(&temppolygon);
	ds = drawstate_create();

	// grab input filename from command line
	if( argc < 2 ) {
		printf("Usage: require input filename as command line parameter\n");
		return(0);
	} else if (argc == 2) {
		infilename =  argv[1];
		outfilename = "moduleGen_output.ppm";
	} else {
		infilename =  argv[1];
		outfilename = argv[2];  
	}

	// open input file for reading
	infile =fopen(infilename,"r");
	if (!infile){
		printf("%s did not open for reading properly\n",infilename);
		return 1;
	}

	// loop until EOF is reached, generating modules
	while (fgets(buff,1000, infile)!=NULL){

		// remove newline
		linein = strtok (buff, "\n");
		printf("reading line: %s\n", linein);

		// get the first word
		firstword = strtok (buff,delim);

		if(strcmp(firstword, "def") == 0){
			secondword = strtok (NULL, delim);
			if(strcmp(secondword, "point") == 0){
				thirdword = strtok (NULL, delim);
				pt[numpoints] = malloc(sizeof(TableItem));
				pt[numpoints]->name = thirdword;
				thirdword = strtok (NULL, delim);
				x = atof(thirdword);
				thirdword = strtok (NULL, delim);
				y = atof(thirdword);
				thirdword = strtok (NULL, delim);
				if(thirdword == NULL){
					point_set2D(&(pt[numpoints++]->item.point), x, y);
				} else {
					z = atof(thirdword);
					point_set3D(&(pt[numpoints++]->item.point), x, y, z);
				}
			}
			else if(strcmp(secondword, "line") == 0){
				thirdword = strtok (NULL, delim);
				l[numlines] = malloc(sizeof(TableItem));
				l[numlines]->name = thirdword;
				for(i=0;i<2;i++){
					searchname = strtok (NULL, delim));
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i] = pt[j]->item.point;
							break;
						}
					}
				}
				line_set(&(l[numlines++]->item.line), temppts[0], temppts[1]);
			}
			else if(strcmp(secondword, "polyline") == 0){
				thirdword = strtok (NULL, delim);
				pl[numpolylines] = malloc(sizeof(TableItem));
				pl[numpolylines]->name = thirdword;
				searchname = strtok (NULL, delim));
				i = 0;
				while(searchname != NULL){
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i++] = pt[j]->item.point;
							break;
						}
					}
					searchname = strtok (NULL, delim));
				}
				pl[numpolylines++]->item.polyline = *(polyline_createp(i, &(temppts[0])));
			}
			else if(strcmp(secondword, "polygon") == 0){
				thirdword = strtok (NULL, delim);
				pg[numpolygons] = malloc(sizeof(TableItem));
				pg[numpolygons]->name = thirdword;
				searchname = strtok (NULL, delim));
				i = 0;
				while(searchname != NULL){
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i++] = pt[j]->item.point;
							break;
						}
					}
					searchname = strtok (NULL, delim));
				}
				pg[numpolygons++]->item.polygon = *(polygon_createp(i, &(temppts[0])));
			}
			else if(strcmp(secondword, "module") == 0){
				thirdword = strtok (NULL, delim);
				mod[++activeMod] = malloc(sizeof(TableItem));
				mod[activeMod]->name = thirdword;
				mod[activeMod]->item.module = module_create();
			}
			else {
				printf("def NOT RECOGNIZED");
			}
		}
		else if(strcmp(firstword, "add") == 0){
			secondword = strtok (NULL, delim);
			if(strcmp(firstword, "module") == 0){
				printf("can't add module, must def and put named modules only\n");
			} 
			else if(strcmp(secondword, "point") == 0){
				thirdword = strtok (NULL, delim);
				x = atof(thirdword);
				thirdword = strtok (NULL, delim);
				y = atof(thirdword);
				thirdword = strtok (NULL, delim);
				if(thirdword == NULL){
					point_set2D(&(temppts[0]), x, y);
				} else {
					z = atof(thirdword);
					point_set3D(&(temppts[0]), x, y, z);
				}
				module_point(mod[activeMod]->item.module, &(temppts[0]));
			} 
			else if(strcmp(secondword, "line") == 0){
				for(i=0;i<2;i++){
					searchname = strtok (NULL, delim));
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i] = pt[j]->item.point;
							break;
						}
					}
				}
				line_set(&templine, temppts[0], temppts[1]);
				module_line(mod[activeMod]->item.module, &templine);
			} 
			else if(strcmp(secondword, "polyline") == 0){
				thirdword = strtok (NULL, delim);
				pl[numpolylines] = malloc(sizeof(TableItem));
				pl[numpolylines]->name = thirdword;
				searchname = strtok (NULL, delim));
				i = 0;
				while(searchname != NULL){
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i++] = pt[j]->item.point;
							break;
						}
					}
					searchname = strtok (NULL, delim));
				}
				polyline_set(&temppolyline, i, &(temppts[0]));
				module_polyline(mod[activeMod]->item.module, &temppolyline);
			}
			else if(strcmp(secondword, "polygon") == 0){
				thirdword = strtok (NULL, delim);
				pg[numpolygons] = malloc(sizeof(TableItem));
				pg[numpolygons]->name = thirdword;
				searchname = strtok (NULL, delim));
				i = 0;
				while(searchname != NULL){
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i++] = pt[j]->item.point;
							break;
						}
					}
					searchname = strtok (NULL, delim));
				}
				polygon_set(&temppolygon, i, &(temppts[0]));
				module_polygon(mod[activeMod]->item.module, &temppolygon);
			} 
			else {
				printf("add NOT RECOGNIZED");
			}
		}
		else if(strcmp(firstword, "put") == 0){
			secondword = strtok (NULL, delim);
			if(strcmp(secondword, "module") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<activeMod;j++){
					if(strcmp(mod[j]->name, searchname) == 0){
						break;
					}
				}
				module_module(mod[activeMod]->item.module, mod[j]->item.module);
			} 
			else if(strcmp(secondword, "point") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<numpoints;j++){
					if(strcmp(pt[j]->name, searchname) == 0){
						break;
					}
				}
				module_point(mod[activeMod]->item.module, &(pt[j]->item.point));
			} 
			else if(strcmp(secondword, "line") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<numlines;j++){
					if(strcmp(l[j]->name, searchname) == 0){
						break;
					}
				}
				module_line(mod[activeMod]->item.module, &(l[j]->item.line));
			} 
			else if(strcmp(secondword, "polyline") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<numpolylines;j++){
					if(strcmp(pl[j]->name, searchname) == 0){
						break;
					}
				}
				module_polyline(mod[activeMod]->item.module, &(pl[j]->item.polyline));
			} 
			else if(strcmp(secondword, "polygon") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<numpolygons;j++){
					if(strcmp(pg[j]->name, searchname) == 0){
						break;
					}
				}
				module_polygon(mod[activeMod]->item.module, &(pg[j]->item.polygon));
			} 
			else {
				printf("put NOT RECOGNIZED");
			}
		}
		else if(strcmp(firstword, "view2D") == 0){
			is2D = 1;
			secondword = strtok (NULL, delim);
			if(strcmp(secondword, "vrp") == 0){
				thirdword = strtok (NULL, delim);
				x = atof(thirdword);
				thirdword = strtok (NULL, delim);
				y = atof(thirdword);
				z = 0;
				point_set3D(&(view2D.vrp), x, y, z);
			}
			else if(strcmp(secondword, "x") == 0){
				thirdword = strtok (NULL, delim);
				x = atof(thirdword);
				thirdword = strtok (NULL, delim);
				y = atof(thirdword);
				z = 0;
				vector_set(&(view2D.x), x, y, z);
			}
			else if(strcmp(secondword, "dx") == 0){
				thirdword = strtok (NULL, delim);
				view2D.dx = atof(thirdword);
			}
			else if(strcmp(secondword, "screenx") == 0){
				thirdword = strtok (NULL, delim);
				view2D.dx = atof(thirdword);
			}
			else if(strcmp(secondword, "screeny") == 0){
				thirdword = strtok (NULL, delim);
				view2D.dx = atof(thirdword);
			}
			else{
				printf("view2D NOT RECOGNIZED");
			}
		}
		else if(strcmp(firstword, "view3D") == 0){
			is2D = 0;
			secondword = strtok (NULL, delim);
			if(strcmp(secondword, "vrp") == 0){
				thirdword = strtok (NULL, delim);
				x = atof(thirdword);
				thirdword = strtok (NULL, delim);
				y = atof(thirdword);
				thirdword = strtok (NULL, delim);
				z = atof(thirdword);
				point_set3D(&(view3D.vrp), x, y, z);
			}
			else if(strcmp(secondword, "vpn") == 0){
				thirdword = strtok (NULL, delim);
				x = atof(thirdword);
				thirdword = strtok (NULL, delim);
				y = atof(thirdword);
				thirdword = strtok (NULL, delim);
				z = atof(thirdword);
				vector_set(&(view3D.vpn), x, y, z);
			}
			else if(strcmp(secondword, "vup") == 0){
				thirdword = strtok (NULL, delim);
				x = atof(thirdword);
				thirdword = strtok (NULL, delim);
				y = atof(thirdword);
				thirdword = strtok (NULL, delim);
				z = atof(thirdword);
				vector_set(&(view3D.vup), x, y, z);
			}
			else if(strcmp(secondword, "d") == 0){
				thirdword = strtok (NULL, delim);
				view3D.d = atof(thirdword);
			}
			else if(strcmp(secondword, "du") == 0){
				thirdword = strtok (NULL, delim);
				view3D.du = atof(thirdword);
			}
			else if(strcmp(secondword, "screenx") == 0){
				thirdword = strtok (NULL, delim);
				view3D.screenx = atof(thirdword);
			}
			else if(strcmp(secondword, "screeny") == 0){
				thirdword = strtok (NULL, delim);
				view3D.screeny = atof(thirdword);
			}
			else{
				printf("view3D NOT RECOGNIZED");
			}
		}
		else{
			printf("NOT RECOGNIZED");
		}
	}

	// verify that at least one module defined
	if(activeMod == -1){
		printf("no modules defined, nothing is being drawn, no side effects\n");
	}

	// define view and draw state and draw last module defined
	matrix_identity( &gtm );
	if(is2D){
		matrix_setView2D( &vtm, &view2D );
		src = image_create( view2D.screeny, view2D.screenx );
	}
	else {
		matrix_setView3D( &vtm, &view3D );
		src = image_create( view3D.screeny, view3D.screenx );
	}
	module_draw(mod[activeMod]->item.module, vtm, gtm, ds, NULL, src);
	image_write(src, outfilename);

	// clean up
	fclose(infile);
	image_free(src);

	return(0);
}
