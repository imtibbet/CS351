/*
	Ian Tibbetts
	Fall 2014

	for easily generating modules
 */
#include <string.h>
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
	char name[256];
	Item item;
} TableItem;

int main(int argc, char *argv[]) {

	// variables for the view and image
	DrawState *ds;
	Image *src;
	View2D view2D;
	View3D view3D;
	Matrix vtm;
	Matrix gtm;

	// variables for parsing
	char *infilename, *outfilename;
	FILE *infile;
	char buff[1000];
	char *linein, *firstword, *secondword, *nextword, *searchname, *varname;
	char *delim = " \n";
	int i, j, is2D = 0;
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

		// get the first and second words
		firstword = strtok (buff,delim);
		secondword = strtok (NULL, delim);
		if(strcmp(firstword, "def") == 0){
			varname = strtok (NULL, delim);
			if(strcmp(secondword, "module") == 0){
				mod[++activeMod] = malloc(sizeof(TableItem));
				strcpy(mod[activeMod]->name, varname);
				mod[activeMod]->item.module = module_create();
			}
			else if(strcmp(secondword, "point") == 0){
				pt[numpoints] = malloc(sizeof(TableItem));
				strcpy(pt[numpoints]->name, varname);
				nextword = strtok (NULL, delim);
				x = atof(nextword);
				nextword = strtok (NULL, delim);
				y = atof(nextword);
				nextword = strtok (NULL, delim);
				if(nextword == NULL){
					point_set2D(&(pt[numpoints++]->item.point), x, y);
				} else {
					z = atof(nextword);
					point_set3D(&(pt[numpoints++]->item.point), x, y, z);
				}
			}
			else if(strcmp(secondword, "line") == 0){
				l[numlines] = malloc(sizeof(TableItem));
				strcpy(l[numlines]->name, varname);
				for(i=0;i<2;i++){
					searchname = strtok (NULL, delim);
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
				pl[numpolylines] = malloc(sizeof(TableItem));
				strcpy(pl[numpolylines]->name, varname);
				searchname = strtok (NULL, delim);
				i = 0;
				while(searchname != NULL){
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i++] = pt[j]->item.point;
							break;
						}
					}
					searchname = strtok (NULL, delim);
				}
				pl[numpolylines++]->item.polyline = *(polyline_createp(i, &(temppts[0])));
			}
			else if(strcmp(secondword, "polygon") == 0){
				pg[numpolygons] = malloc(sizeof(TableItem));
				strcpy(pg[numpolygons]->name, varname);
				searchname = strtok (NULL, delim);
				i = 0;
				while(searchname != NULL){
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i++] = pt[j]->item.point;
							break;
						}
					}
					searchname = strtok (NULL, delim);
				}
				pg[numpolygons++]->item.polygon = *(polygon_createp(i, &(temppts[0])));
			}
			else {
				printf(	"Seond word of def not not recognized.\n"
						"Must be module, point, line, polyline, polygon\n");
			}
		}
		else if(strcmp(firstword, "add") == 0){
			if(strcmp(secondword, "module") == 0){
				printf("can't add module, must def and put named modules only\n");
			} 
			else if(strcmp(secondword, "point") == 0){
				nextword = strtok (NULL, delim);
				x = atof(nextword);
				nextword = strtok (NULL, delim);
				y = atof(nextword);
				nextword = strtok (NULL, delim);
				if(nextword == NULL){
					point_set2D(&(temppts[0]), x, y);
				} else {
					z = atof(nextword);
					point_set3D(&(temppts[0]), x, y, z);
				}
				module_point(mod[activeMod]->item.module, &(temppts[0]));
			} 
			else if(strcmp(secondword, "line") == 0){
				for(i=0;i<2;i++){
					searchname = strtok (NULL, delim);
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
				searchname = strtok (NULL, delim);
				i = 0;
				while(searchname != NULL){
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i++] = pt[j]->item.point;
							break;
						}
					}
					searchname = strtok (NULL, delim);
				}
				polyline_set(&temppolyline, i, &(temppts[0]));
				module_polyline(mod[activeMod]->item.module, &temppolyline);
			}
			else if(strcmp(secondword, "polygon") == 0){
				searchname = strtok (NULL, delim);
				i = 0;
				while(searchname != NULL){
					for(j=0;j<numpoints;j++){
						if(strcmp(pt[j]->name, searchname) == 0){
							temppts[i++] = pt[j]->item.point;
							break;
						}
					}
					searchname = strtok (NULL, delim);
				}
				polygon_set(&temppolygon, i, &(temppts[0]));
				printf("polygon added to module %s\n", mod[activeMod]->name);
				polygon_print(&temppolygon, stdout);
				module_polygon(mod[activeMod]->item.module, &temppolygon);
			} 
			else {
				printf(	"Seond word of add not not recognized.\n"
						"Must be module, point, line, polyline, polygon"
						", rotateX, rotateY, rotateZ, rotateXYZ"
						", translate, scale, shear2D, or shearZ\n");
			}
		}
		else if(strcmp(firstword, "put") == 0){
			if(strcmp(secondword, "module") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<activeMod;j++){
					if(strcmp(mod[j]->name, searchname) == 0){
						break;
					}
				}
				if(j == activeMod)
					printf("%s module not found\n", searchname);
				else
					module_module(mod[activeMod]->item.module, mod[j]->item.module);
			} 
			else if(strcmp(secondword, "point") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<numpoints;j++){
					if(strcmp(pt[j]->name, searchname) == 0){
						break;
					}
				}
				if(j==numpoints)
					printf("%s point not found\n", searchname);
				else
					module_point(mod[activeMod]->item.module, &(pt[j]->item.point));
			} 
			else if(strcmp(secondword, "line") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<numlines;j++){
					if(strcmp(l[j]->name, searchname) == 0){
						break;
					}
				}
				if(j==numlines)
					printf("%s line not found\n", searchname);
				else
					module_line(mod[activeMod]->item.module, &(l[j]->item.line));
			} 
			else if(strcmp(secondword, "polyline") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<numpolylines;j++){
					if(strcmp(pl[j]->name, searchname) == 0){
						break;
					}
				}
				if(j==numpolylines)
					printf("%s polyline not found\n", searchname);
				else
					module_polyline(mod[activeMod]->item.module, &(pl[j]->item.polyline));
			} 
			else if(strcmp(secondword, "polygon") == 0){
				searchname = strtok (NULL, delim);
				for(j=0;j<numpolygons;j++){
					if(strcmp(pg[j]->name, searchname) == 0){
						break;
					}
				}
				if(j==numpolygons)
					printf("%s polygon not found\n", searchname);
				else
					module_polygon(mod[activeMod]->item.module, &(pg[j]->item.polygon));
			} 
			else {
				printf(	"Seond word of put not not recognized.\n"
						"Must be module, point, line, polyline, polygon\n");
			}
		}
		else if(strcmp(firstword, "view2D") == 0){
			is2D = 1;
			nextword = strtok (NULL, delim);
			if(strcmp(secondword, "vrp") == 0){
				x = atof(nextword);
				nextword = strtok (NULL, delim);
				y = atof(nextword);
				z = 0;
				point_set3D(&(view2D.vrp), x, y, z);
			}
			else if(strcmp(secondword, "x") == 0){
				x = atof(nextword);
				nextword = strtok (NULL, delim);
				y = atof(nextword);
				z = 0;
				vector_set(&(view2D.x), x, y, z);
			}
			else if(strcmp(secondword, "dx") == 0){
				view2D.dx = atof(nextword);
			}
			else if(strcmp(secondword, "screenx") == 0){
				view2D.screenx = atof(nextword);
			}
			else if(strcmp(secondword, "screeny") == 0){
				view2D.screeny = atof(nextword);
			}
			else{
				printf(	"Seond word of view2D not not recognized.\n"
						"Must be vrp, x, dx, screenx, or screeny\n");
			}
		}
		else if(strcmp(firstword, "view3D") == 0){
			is2D = 0;
			nextword = strtok (NULL, delim);
			if(strcmp(secondword, "vrp") == 0){
				x = atof(nextword);
				nextword = strtok (NULL, delim);
				y = atof(nextword);
				nextword = strtok (NULL, delim);
				z = atof(nextword);
				point_set3D(&(view3D.vrp), x, y, z);
			}
			else if(strcmp(secondword, "vpn") == 0){
				x = atof(nextword);
				nextword = strtok (NULL, delim);
				y = atof(nextword);
				nextword = strtok (NULL, delim);
				z = atof(nextword);
				vector_set(&(view3D.vpn), x, y, z);
			}
			else if(strcmp(secondword, "vup") == 0){
				x = atof(nextword);
				nextword = strtok (NULL, delim);
				y = atof(nextword);
				nextword = strtok (NULL, delim);
				z = atof(nextword);
				vector_set(&(view3D.vup), x, y, z);
			}
			else if(strcmp(secondword, "d") == 0){
				view3D.d = atof(nextword);
			}
			else if(strcmp(secondword, "du") == 0){
				view3D.du = atof(nextword);
			}
			else if(strcmp(secondword, "screenx") == 0){
				view3D.screenx = atof(nextword);
			}
			else if(strcmp(secondword, "screeny") == 0){
				view3D.screeny = atof(nextword);
			}
			else{
				printf(	"Seond word of view3D not not recognized.\n"
						"Must be vrp, vpn, vup, d, du, screenx, or screeny\n");
			}
		}
		else{
			printf(	"First word not not recognized.\n"
					"Must be def, add, put, view2D, or view3D\n");
		}
	}
	printf("EOF reached\n");

	// check that everything was defined correctly
	printf("User defined primitives:\n");
	for(j=0;j<numpoints;j++){
		printf("point named %s\n", pt[j]->name);
		point_print(&(pt[j]->item.point), stdout);
	}
	for(j=0;j<numlines;j++){
		printf("line named %s\n", l[j]->name);
		line_print(&(l[j]->item.line), stdout);
	}
	for(j=0;j<numpolylines;j++){
		printf("polyline named %s\n", pl[j]->name);
		polyline_print(&(pl[j]->item.polyline), stdout);
	}
	for(j=0;j<numpolygons;j++){
		printf("polygon named %s\n", pg[j]->name);
		polygon_print(&(pg[j]->item.polygon), stdout);
	}
	printf("User defined modules:\n");
	// verify that at least one module defined
	if(activeMod == -1){
		printf("no modules defined, nothing is being drawn, no side effects\n");
	} else {
		for(j=0;j<=activeMod;j++){
			printf("module named %s\n", mod[j]->name);
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
		printf("vtm in module generation:\n");
		matrix_print(&vtm, stdout);
		module_draw(mod[activeMod]->item.module, &vtm, &gtm, ds, NULL, src);
		image_write(src, outfilename);

		// some clean up
		image_free(src);
		for(j=0;j<=activeMod;j++){
			printf("freeing module named %s\n", mod[j]->name);
			module_clear(mod[j]->item.module);
			free(mod[j]);
		}
	}
	
	// rest of the clean up
	fclose(infile);
	for(j=0;j<numpoints;j++){
		printf("freeing point named %s\n", pt[j]->name);
		free(pt[j]);
	}
	for(j=0;j<numlines;j++){
		printf("freeing line named %s\n", l[j]->name);
		free(l[j]);
	}
	for(j=0;j<numpolylines;j++){
		printf("freeing polyline named %s\n", pl[j]->name);
		if(pl[j]->item.polyline.vertex)
			free(pl[j]->item.polyline.vertex);
		free(pl[j]);
	}
	for(j=0;j<numpolygons;j++){
		printf("freeing polygon named %s\n", pg[j]->name);
		if(pg[j]->item.polygon.vertex)
			free(pg[j]->item.polygon.vertex);
		free(pg[j]);
	}

	return(0);
}
