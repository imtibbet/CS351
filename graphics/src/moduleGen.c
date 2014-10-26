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
	Vector vector;
	Line line;
	Polyline polyline;
	Polygon polygon;
	Matrix matrix;
	Color color;
	float number;
	Module *module;
} Item;

typedef struct{
	char name[256];
	Item item;
} TableItem;

static float stringToFloat(char *str, TableItem **numbs, int numnumbers){
	char *curterm, *searchname;
	int j;
	float recresult = 1.0;
	if(strchr(str, '*')){
		curterm = strtok(str, "*");
		while(curterm)
			recresult *= stringToFloat(curterm, numbs, numnumbers);
		return(recresult);
	}
	// check for the number as a key in the numbers table
	searchname = strtok (str,"()");
	for(j=0;j<numnumbers;j++){
		if(strcmp(numbs[j]->name, searchname) == 0){
			break;
		}
	}

	// if the number is found, return it
	if(j!=numnumbers)
		return(numbs[j]->item.number);

	// otherwise, check for sin or cos
	if(strncmp(str, "sin", 3) == 0){
		searchname = strtok (NULL, "()");
		return(sin(M_PI*atof(searchname)/180.0));
	}
	else if(strncmp(str, "cos", 3) == 0){
		searchname = strtok (NULL, "()");
		return(cos(M_PI*atof(searchname)/180.0));
	} 
	else {
		return(atof(searchname));
	}
}
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
	int i, j, solid, is2D = 0;
	int activeMod = -1;
	int numpoints = 0;
	int numvectors = 0;
	int numlines = 0;
	int numpolylines = 0;
	int numpolygons = 0;
	int numnumbers = 0;
	TableItem *pt[1000], *v[1000], *numbs[1000], *l[1000], *pl[1000], *pg[1000], *mod[1000];
	Point temppts[50];
	Vector uvw[3];
	Line templine;
	Polyline temppolyline;
	Polygon temppolygon;
	float x, y, z, theta;

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
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				if(nextword == NULL){
					point_set2D(&(pt[numpoints++]->item.point), x, y);
				} else {
					z = stringToFloat(nextword, numbs, numnumbers);
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
			else if(strcmp(secondword, "vector") == 0){
				v[numvectors] = malloc(sizeof(TableItem));
				strcpy(v[numvectors]->name, varname);
				nextword = strtok (NULL, delim);
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				if(nextword == NULL){
					z = 0.0;
				} else {
					z = stringToFloat(nextword, numbs, numnumbers);
				}
				vector_set(&(v[numvectors++]->item.vector), x, y, z);
			}
			else if(strcmp(secondword, "number") == 0){
				numbs[numnumbers] = malloc(sizeof(TableItem));
				strcpy(numbs[numnumbers]->name, varname);
				nextword = strtok (NULL, delim);
				x = stringToFloat(nextword, numbs, numnumbers);
				numbs[numnumbers++]->item.number = x;
			}
			else {
				printf(	"Seond word of def not not recognized.\n"
						"Must be module, point, vector, line, polyline, "
						"polygon, or number\n");
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
		else if(strcmp(firstword, "add") == 0){
			if(strcmp(secondword, "module") == 0){
				printf(	"It is not legal to add modules. Modules must first "
						"be defined with a name and then put into active module\n");
			} 
			else if(strcmp(secondword, "point") == 0){
				nextword = strtok (NULL, delim);
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				if(nextword == NULL){
					point_set2D(&(temppts[0]), x, y);
				} else {
					z = stringToFloat(nextword, numbs, numnumbers);
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
			else if(strcmp(secondword, "cube") == 0){
				nextword = strtok (NULL, delim);
				if(nextword)
					solid = atoi(nextword);
				else
					solid = 1;
				module_cube(mod[activeMod]->item.module, solid);
			}
			else if(strcmp(secondword, "identity") == 0){
				module_identity(mod[activeMod]->item.module);
			}
			else if(strcmp(secondword, "rotateX") == 0){
				nextword = strtok (NULL, delim);
				theta = M_PI*stringToFloat(nextword, numbs, numnumbers)/180.0;
				module_rotateX(mod[activeMod]->item.module, cos(theta), sin(theta));
			}
			else if(strcmp(secondword, "rotateY") == 0){
				nextword = strtok (NULL, delim);
				theta = M_PI*stringToFloat(nextword, numbs, numnumbers)/180.0;
				module_rotateY(mod[activeMod]->item.module, cos(theta), sin(theta));
			}
			else if(strcmp(secondword, "rotateZ") == 0){
				nextword = strtok (NULL, delim);
				theta = M_PI*stringToFloat(nextword, numbs, numnumbers)/180.0;
				module_rotateZ(mod[activeMod]->item.module, cos(theta), sin(theta));
			}
			else if(strcmp(secondword, "rotateXYZ") == 0){
				for(i=0;i<3;i++){
					searchname = strtok (NULL, delim);
					for(j=0;j<numvectors;j++){
						if(strcmp(v[j]->name, searchname) == 0){
							uvw[i] = v[j]->item.vector;
							break;
						}
					}
				}
				module_rotateXYZ(mod[activeMod]->item.module, &(uvw[0]), &(uvw[1]), &(uvw[2]));
			} 
			else if(strcmp(secondword, "translate") == 0){
				nextword = strtok (NULL, delim);
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				if(nextword == NULL){
					module_translate2D(mod[activeMod]->item.module, x, y);
				} else {
					z = stringToFloat(nextword, numbs, numnumbers);
					module_translate(mod[activeMod]->item.module, x, y, z);
				}
			} 
			else if(strcmp(secondword, "scale") == 0){
				nextword = strtok (NULL, delim);
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				if(nextword == NULL){
					module_scale2D(mod[activeMod]->item.module, x, y);
				} else {
					z = stringToFloat(nextword, numbs, numnumbers);
					module_scale(mod[activeMod]->item.module, x, y, z);
				}
			} 
			else if(strcmp(secondword, "shear2D") == 0){
				nextword = strtok (NULL, delim);
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				module_shear2D(mod[activeMod]->item.module, x, y);
			} 
			else if(strcmp(secondword, "shearZ") == 0){
				nextword = strtok (NULL, delim);
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				module_shearZ(mod[activeMod]->item.module, x, y);
			} 
			else {
				printf(	"Seond word of add not not recognized.\n"
						"Must be module, point, line, polyline, polygon, cube"
						", rotateX, rotateY, rotateZ, rotateXYZ"
						", translate, scale, shear2D, or shearZ\n");
			}
		}
		else if(strcmp(firstword, "view2D") == 0){
			is2D = 1;
			nextword = strtok (NULL, delim);
			if(strcmp(secondword, "vrp") == 0){
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				z = 0;
				point_set3D(&(view2D.vrp), x, y, z);
			}
			else if(strcmp(secondword, "x") == 0){
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				z = 0;
				vector_set(&(view2D.x), x, y, z);
			}
			else if(strcmp(secondword, "dx") == 0){
				view2D.dx = stringToFloat(nextword, numbs, numnumbers);
			}
			else if(strcmp(secondword, "screenx") == 0){
				view2D.screenx = stringToFloat(nextword, numbs, numnumbers);
			}
			else if(strcmp(secondword, "screeny") == 0){
				view2D.screeny = stringToFloat(nextword, numbs, numnumbers);
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
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				z = stringToFloat(nextword, numbs, numnumbers);
				point_set3D(&(view3D.vrp), x, y, z);
			}
			else if(strcmp(secondword, "vpn") == 0){
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				z = stringToFloat(nextword, numbs, numnumbers);
				vector_set(&(view3D.vpn), x, y, z);
			}
			else if(strcmp(secondword, "vup") == 0){
				x = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				y = stringToFloat(nextword, numbs, numnumbers);
				nextword = strtok (NULL, delim);
				z = stringToFloat(nextword, numbs, numnumbers);
				vector_set(&(view3D.vup), x, y, z);
			}
			else if(strcmp(secondword, "d") == 0){
				view3D.d = stringToFloat(nextword, numbs, numnumbers);
			}
			else if(strcmp(secondword, "du") == 0){
				view3D.du = stringToFloat(nextword, numbs, numnumbers);
			}
			else if(strcmp(secondword, "screenx") == 0){
				view3D.screenx = stringToFloat(nextword, numbs, numnumbers);
			}
			else if(strcmp(secondword, "screeny") == 0){
				view3D.screeny = stringToFloat(nextword, numbs, numnumbers);
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
	for(j=0;j<numvectors;j++){
		printf("vector named %s\n", v[j]->name);
		vector_print(&(v[j]->item.vector), stdout);
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
	for(j=0;j<numvectors;j++){
		printf("freeing vector named %s\n", v[j]->name);
		free(v[j]);
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
