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

typedef struct{
	char name[256];
	float val;
} ParamListItem;

typedef struct{
	char name[256];
	char *definition[2000];
	int numlines;
	int numparams;
	ParamListItem *params;
	Module *module;
} ModuleItem;

// converts strings to float, allowing two term multiplication, 
// named variables or parameters in nums or module, respectively, sin and cos. 
static float stringToFloat(char *str, TableItem **numbs, int numnumbers, 
										ModuleItem *activeModule){
	char *searchname;
	char num[256], term1[256], term2[256];
	int j;
	strcpy(num, str);
	printf("stringToFloat %s\n", num);
	// check for multiplication and recurse through arguments
	if(strchr(num, '*')){
		//printf("performing multiplication %s\n", num);
		strcpy(term1, strtok(num, "*"));
		strcpy(term2, strtok(NULL, ""));
		return(	stringToFloat(term1, numbs, numnumbers, activeModule) *
				stringToFloat(term2, numbs, numnumbers, activeModule) ) ;
	}
	else if(strchr(num, '+')){
		//printf("performing multiplication %s\n", num);
		strcpy(term1, strtok(num, "+"));
		strcpy(term2, strtok(NULL, ""));
		return(	stringToFloat(term1, numbs, numnumbers, activeModule) +
				stringToFloat(term2, numbs, numnumbers, activeModule) ) ;
	}

	// check for the number as a key in the module parameters
	searchname = strtok (num,"()");
	if(activeModule){
		for(j=0;j<activeModule->numparams;j++){
			if(strcmp(activeModule->params[j].name, searchname) == 0){
				break;
			}
		}
	
		// if the number is found, return it
		if(j!=(activeModule->numparams)){
			//printf("found var %s\n", searchname);
			return(activeModule->params[j].val);
		}
	}
	
	// check for the number as a key in the numbers table
	for(j=0;j<numnumbers;j++){
		if(strcmp(numbs[j]->name, searchname) == 0){
			break;
		}
	}

	// if the number is found, return it
	if(j!=numnumbers){
		//printf("found var %s\n", searchname);
		return(numbs[j]->item.number);
	}
			
	// otherwise, check for sin or cos
	if(strcmp(searchname, "sin") == 0){
		searchname = strtok (NULL, "()");
		//printf("computing sin(%s)\n", searchname);
		return(sin(M_PI*stringToFloat(searchname, numbs, numnumbers, activeModule)/180.0));
	}
	else if(strcmp(searchname, "cos") == 0){
		searchname = strtok (NULL, "()");
		//printf("computing cos(%s)\n", searchname);
		return(cos(M_PI*stringToFloat(searchname, numbs, numnumbers, activeModule)/180.0));
	} 
	else {
		//printf("returning\n");
		return(atof(searchname));
	}
}

// parse the active module's definition, populating its module
static int parseModule(int activeMod, ModuleItem **mod, 
						TableItem **pt, TableItem **v, TableItem **numbs, 
						TableItem **l, TableItem **pl, TableItem **pg, 
						int numparams, int numpoints, int numvectors, int numlines, 
						int numpolylines, int numpolygons, int numnumbers){
	// variables for parsing module definition
	const int maxline = 1000;
	const int maxpts = 50;
	const int maxparam = 50;
	char buff[maxline];
	char linein[maxline];
	char *params[maxparam];
	char varname[256];
	char tempparamval[256];
	char 	*firstword, *secondword, *xstr, *ystr, *zstr, *nextword, 
			*searchname;
	char *delim = " \n";
	int i, j, solid, templateMod = 0;
	int curLine = 0;
	int totalLines;
	int numAddedMods = 1;
	Point temppts[maxpts];
	Vector uvw[3];
	Line templine;
	Polyline temppolyline;
	Polygon temppolygon;
	float x, y, z, theta;
	
	// get the first and second words
	strcpy(buff, mod[activeMod]->definition[0]);
	firstword = strtok (buff,delim);
	secondword = strtok (NULL, delim);
	strcpy(varname, strtok (NULL, delim));
	// check for any parameters
	numparams = 0;
	params[numparams] = strtok (NULL, delim);
	while(params[numparams]!=NULL){
		//printf("encountered parameter %s\n", params[numparams]);
		params[++numparams] = strtok (NULL, delim);
	}
	mod[activeMod]->numparams = numparams;
	
	// if any parameters, parse and build table of parameters
	if(numparams){
		// printf("module has %d parameters, processing\n", numparams);
		mod[activeMod]->params = malloc(numparams*sizeof(ParamListItem));
		for(j=0;j<numparams;j++){
			strcpy(mod[activeMod]->params[j].name, strtok(params[j], "="));
			//printf("processing parameter %s\n", mod[activeMod]->params[j].name);
			strcpy(tempparamval, strtok(NULL, "="));
			mod[activeMod]->params[j].val = atof(tempparamval);
			sprintf(tempparamval, "%0.3f", mod[activeMod]->params[j].val);
			/*printf("parameter %s has default value %f\n", 
					mod[activeMod]->params[j].name, 
					mod[activeMod]->params[j].val);*/
			strcat(varname, tempparamval);
		}
	}
	printf("defining module named %s\n", varname);
	
	// create module
	strcpy(mod[activeMod]->name, varname);
	
	// populate module
	totalLines = mod[activeMod]->numlines;
	for(curLine=1;curLine<totalLines;curLine++){
		strcpy(buff, mod[activeMod]->definition[curLine]);
		strcpy(linein, strtok (buff, "\n"));
		printf("definition line %s\n",linein); // get crazy characters here
		
		// get the first and second words
		firstword = strtok (buff,delim);
		secondword = strtok (NULL, delim);
		
		// put named primitive into module
		if(strcmp(firstword, "put") == 0){
			
			// put module
			if(strcmp(secondword, "module") == 0){
				strcpy(varname, strtok (NULL, delim));
				// find template module if any
				for(j=0;j<activeMod;j++){
					if(strncmp(mod[j]->name, varname, strlen(varname)) == 0){
						break;
					}
				}
				
				// done if module is found, otherwise make a new one
				if(j == activeMod){
					printf("no template module for %s found\n", varname);
					continue;
				}
				templateMod = j;
				
				// check for any parameters
				numparams = 0;
				params[numparams] = strtok (NULL, delim);
				while(params[numparams]!=NULL){
					// printf("encountered parameter %s\n", params[numparams]);
					params[++numparams] = strtok (NULL, delim);
				}
				
				// build varname for search
				// loop over all defined parameters
				for(i=0;i<mod[templateMod]->numparams;i++){
					// printf("template parameter %s\n", mod[templateMod]->params[i].name);
					// loop over given params to see if new value given
					for(j=0;j<numparams;j++){
						strcpy(tempparamval, strtok(params[j], "="));
						// printf("given parameter %s\n", tempparamval);
						if(strcmp(mod[templateMod]->params[i].name, tempparamval) == 0){
							break;
						}
					}
					// if the parameter is found, overwrite the value in varname
					if(j!=numparams){
						// printf("overwriting var %s\n", tempparamval);
						strcpy(tempparamval, strtok(NULL, "="));
						sprintf(tempparamval, "%0.3f", atof(tempparamval));
						strcat(varname, tempparamval);
					} else {
						sprintf(tempparamval, "%0.3f", mod[templateMod]->params[i].val);
						strcat(varname, tempparamval);
					}
				}
				
				// find matching module if any
				for(j=0;j<activeMod;j++){
					if(strcmp(mod[j]->name, varname) == 0){
						break;
					}
				}
				
				// done if module is found, otherwise make a new one
				if(j != activeMod){
					printf("found module %s\n", varname);
					module_module(mod[activeMod]->module, mod[j]->module);
				}
				else{
					printf("make new instantiation of %s\n", varname);
					// get space for new module
					printf("numAddedMods=%d\n",numAddedMods);
					mod[activeMod+numAddedMods] = malloc(sizeof(ModuleItem));
					mod[activeMod+numAddedMods]->module = module_create();
					mod[activeMod+numAddedMods]->definition[0] = malloc(2*strlen(linein));
					strcpy(mod[activeMod+numAddedMods]->definition[0], linein);
					for(j=1;j<mod[templateMod]->numlines;j++){
						mod[activeMod+numAddedMods]->definition[j] = 
							malloc(2*strlen(mod[templateMod]->definition[j]));
						strcpy(	mod[activeMod+numAddedMods]->definition[j], 
								mod[templateMod]->definition[j]);
					}
					mod[activeMod+numAddedMods]->numlines = mod[templateMod]->numlines;
					numAddedMods += parseModule(activeMod+numAddedMods, mod, 
								pt, v, numbs, l, pl, pg, 
								numparams, numpoints, numvectors, numlines, 
								numpolylines, numpolygons, numnumbers);
					printf("made module\n");			
					module_module(mod[activeMod]->module, mod[activeMod+numAddedMods-1]->module);
				}				
			} 
			
			// put module
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
					module_point(mod[activeMod]->module, &(pt[j]->item.point));
			} 
			
			// put line
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
					module_line(mod[activeMod]->module, &(l[j]->item.line));
			} 
			
			// put polyline
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
					module_polyline(mod[activeMod]->module, &(pl[j]->item.polyline));
			} 
			
			// put polygon
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
					module_polygon(mod[activeMod]->module, &(pg[j]->item.polygon));
			} 
			
			// put not defined
			else {
				printf(	"Seond word of put not not recognized.\n"
						"Must be module, point, line, polyline, polygon\n");
			}
		}
		
		// add anonymous primitive into module
		else if(strcmp(firstword, "add") == 0){
		
			// add module
			if(strcmp(secondword, "module") == 0){
				printf(	"It is not legal to add modules. Modules must first "
						"be defined with a name and then put into active module\n");
			} 
		
			// add point
			else if(strcmp(secondword, "point") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				zstr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, mod[activeMod]);
				y = stringToFloat(ystr, numbs, numnumbers, mod[activeMod]);
				if(zstr == NULL){
					point_set2D(&(temppts[0]), x, y);
				} else {
					z = stringToFloat(zstr, numbs, numnumbers, mod[activeMod]);
					point_set3D(&(temppts[0]), x, y, z);
				}
				module_point(mod[activeMod]->module, &(temppts[0]));
			} 
		
			// add line
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
				module_line(mod[activeMod]->module, &templine);
			} 
		
			// add polyline
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
				module_polyline(mod[activeMod]->module, &temppolyline);
			}
		
			// add polygon
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
				module_polygon(mod[activeMod]->module, &temppolygon);
			} 
		
			// add cube
			else if(strcmp(secondword, "cube") == 0){
				nextword = strtok (NULL, delim);
				if(nextword)
					solid = atoi(nextword);
				else
					solid = 1;
				module_cube(mod[activeMod]->module, solid);
			}
		
			// add identity
			else if(strcmp(secondword, "identity") == 0){
				module_identity(mod[activeMod]->module);
			}
		
			// add rotateX
			else if(strcmp(secondword, "rotateX") == 0){
				nextword = strtok (NULL, delim);
				theta = M_PI*stringToFloat(nextword, numbs, numnumbers, mod[activeMod])/180.0;
				module_rotateX(mod[activeMod]->module, cos(theta), sin(theta));
			}
		
			// add rotateY
			else if(strcmp(secondword, "rotateY") == 0){
				nextword = strtok (NULL, delim);
				theta = M_PI*stringToFloat(nextword, numbs, numnumbers, mod[activeMod])/180.0;
				module_rotateY(mod[activeMod]->module, cos(theta), sin(theta));
			}
		
			// add rotateZ
			else if(strcmp(secondword, "rotateZ") == 0){
				nextword = strtok (NULL, delim);
				theta = M_PI*stringToFloat(nextword, numbs, numnumbers, mod[activeMod])/180.0;
				module_rotateZ(mod[activeMod]->module, cos(theta), sin(theta));
			}
		
			// add rotateXYZ
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
				module_rotateXYZ(mod[activeMod]->module, &(uvw[0]), &(uvw[1]), &(uvw[2]));
			} 
		
			// add translate
			else if(strcmp(secondword, "translate") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				zstr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, mod[activeMod]);
				y = stringToFloat(ystr, numbs, numnumbers, mod[activeMod]);
				if(zstr == NULL){
					module_translate2D(mod[activeMod]->module, x, y);
				} else {
					z = stringToFloat(zstr, numbs, numnumbers, mod[activeMod]);
					module_translate(mod[activeMod]->module, x, y, z);
				}
			} 
		
			// add scale
			else if(strcmp(secondword, "scale") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				zstr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, mod[activeMod]);
				y = stringToFloat(ystr, numbs, numnumbers, mod[activeMod]);
				if(zstr == NULL){
					module_scale2D(mod[activeMod]->module, x, y);
				} else {
					z = stringToFloat(zstr, numbs, numnumbers, mod[activeMod]);
					module_scale(mod[activeMod]->module, x, y, z);
				}
			} 
		
			// add shear2D
			else if(strcmp(secondword, "shear2D") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, mod[activeMod]);
				y = stringToFloat(ystr, numbs, numnumbers, mod[activeMod]);
				module_shear2D(mod[activeMod]->module, x, y);
			} 
		
			// add shearZ
			else if(strcmp(secondword, "shearZ") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, mod[activeMod]);
				y = stringToFloat(ystr, numbs, numnumbers, mod[activeMod]);
				module_shearZ(mod[activeMod]->module, x, y);
			} 
		
			// add not defined
			else {
				printf(	"Seond word of add not not recognized.\n"
						"Must be module, point, line, polyline, polygon, cube"
						", rotateX, rotateY, rotateZ, rotateXYZ"
						", translate, scale, shear2D, or shearZ\n");
			}
		}
	}
	return(numAddedMods);
}

int main(int argc, char *argv[]) {

	// variables for the view and image
	DrawState *ds;
	Image *src;
	View2D view2D;
	View3D view3D;
	Matrix vtm;
	Matrix gtm;

	// variables for parsing input file
	const int maxdef = 1000;
	const int maxline = 1000;
	const int maxpts = 50;
	char *infilename, *outfilename;
	FILE *infile;
	char buff[maxline];
	char linein[maxline];
	char varname[256];
	char 	*firstword, *secondword, *xstr, *ystr, *zstr, *nextword, 
			*searchname;
	char *delim = " \n";
	int i, j, is2D = 0;
	int activeMod = -1;
	int drawMod = -1;
	int curLine = 0;
	int numparams = 0;
	int numpoints = 0;
	int numvectors = 0;
	int numlines = 0;
	int numpolylines = 0;
	int numpolygons = 0;
	int numnumbers = 0;
	TableItem 	*pt[maxdef], *v[maxdef], *numbs[maxdef], *l[maxdef], 
				*pl[maxdef], *pg[maxdef];
	ModuleItem 	*mod[maxdef];
	Point temppts[maxpts];
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
		return(1);
	}

	// loop until EOF is reached, generating modules
	while (fgets(buff,1000, infile)!=NULL){

		// skip empty lines
		if(!strtok(buff, "\n"))
			continue;
		// skip comment lines
		if(strncmp(buff,"#",1) == 0)
			continue;
		// parse line without newline
		strcpy(linein, strtok (buff, "\n"));
		printf("reading line: %s\n", linein); //dont get crazy characters here

		// get the first and second words
		firstword = strtok (buff,delim);
		if(!firstword){
			printf("no first word on this line, skipping\n");
			continue;
		}
		secondword = strtok (NULL, delim);
		if(!secondword){
			printf("no second word on this line, skipping\n");
			continue;
		}
		
		// select a named module to draw
		if(strcmp(firstword, "draw") == 0){
			for(j=0;j<activeMod;j++){
				if(strncmp(mod[j]->name, secondword, strlen(secondword)) == 0){
					break;
				}
			}
			printf("set to draw module %s\n", secondword);
			drawMod = j;
		}
		
		// define name primitives
		else if(strcmp(firstword, "def") == 0){
				
			strcpy(varname, strtok (NULL, delim));
			
			// def module
			if(strcmp(secondword, "module") == 0){
			
				// if a module has been previously defined, parse all lines
				if(activeMod == -1)
					activeMod++;
				else{
					mod[activeMod]->numlines = curLine;
					activeMod += parseModule(activeMod, mod, pt, v, numbs, l, pl, pg, 
								numparams, numpoints, numvectors, numlines, 
								numpolylines, numpolygons, numnumbers);
					printf("activeMod=%d\n",activeMod);
					curLine = 0;
				}
			
				// get space for new module
				mod[activeMod] = malloc(sizeof(ModuleItem));
				mod[activeMod]->module = module_create();
				mod[activeMod]->definition[curLine] = malloc(2*strlen(linein));
				strcpy(mod[activeMod]->definition[curLine++], linein);
			}
			
			// def point
			else if(strcmp(secondword, "point") == 0){
				pt[numpoints] = malloc(sizeof(TableItem));
				strcpy(pt[numpoints]->name, varname);
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				zstr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, NULL);
				y = stringToFloat(ystr, numbs, numnumbers, NULL);
				if(zstr == NULL){
					point_set2D(&(pt[numpoints++]->item.point), x, y);
				} else {
					z = stringToFloat(zstr, numbs, numnumbers, NULL);
					point_set3D(&(pt[numpoints++]->item.point), x, y, z);
				}
			}
			
			// def line
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
			
			// def polyline
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
			
			// def polygon
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
			
			// def vector
			else if(strcmp(secondword, "vector") == 0){
				v[numvectors] = malloc(sizeof(TableItem));
				strcpy(v[numvectors]->name, varname);
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				zstr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, NULL);
				y = stringToFloat(ystr, numbs, numnumbers, NULL);
				if(zstr == NULL){
					z = 0.0;
				} else {
					z = stringToFloat(zstr, numbs, numnumbers, NULL);
				}
				vector_set(&(v[numvectors++]->item.vector), x, y, z);
			}
			
			// def number
			else if(strcmp(secondword, "number") == 0){
				numbs[numnumbers] = malloc(sizeof(TableItem));
				strcpy(numbs[numnumbers]->name, varname);
				nextword = strtok (NULL, delim);
				x = stringToFloat(nextword, numbs, numnumbers, NULL);
				numbs[numnumbers++]->item.number = x;
			}
			
			// def not defined
			else {
				printf(	"Seond word of def not not recognized.\n"
						"Must be module, point, vector, line, polyline, "
						"polygon, or number\n");
			}
		}
			
		// apeend put line to definition of active module
		else if(strcmp(firstword, "put") == 0){
			if(activeMod==-1){
				printf("put must be after a named module has been defined\n");
				continue;
			}
			mod[activeMod]->definition[curLine] = malloc(2*strlen(linein));
			strcpy(mod[activeMod]->definition[curLine++], linein);
		}
		
		// append add line to definition of active module
		else if(strcmp(firstword, "add") == 0){
			if(activeMod==-1){
				printf("add must be after a named module has been defined\n");
				continue;
			}
			mod[activeMod]->definition[curLine] = malloc(2*strlen(linein));
			strcpy(mod[activeMod]->definition[curLine++], linein);
		}
		
		// define a 2D view
		else if(strcmp(firstword, "view2D") == 0){
		
			is2D = 1;
			
			// 2D vrp
			if(strcmp(secondword, "vrp") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, NULL);
				y = stringToFloat(ystr, numbs, numnumbers, NULL);
				z = 0;
				point_set3D(&(view2D.vrp), x, y, z);
			}
			
			// 2D x vector
			else if(strcmp(secondword, "x") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, NULL);
				y = stringToFloat(ystr, numbs, numnumbers, NULL);
				z = 0;
				vector_set(&(view2D.x), x, y, z);
			}
			
			// 2D dx
			else if(strcmp(secondword, "dx") == 0){
				xstr = strtok (NULL, delim);
				view2D.dx = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 2D screenx
			else if(strcmp(secondword, "screenx") == 0){
				xstr = strtok (NULL, delim);
				view2D.screenx = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 2D screeny
			else if(strcmp(secondword, "screeny") == 0){
				xstr = strtok (NULL, delim);
				view2D.screeny = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 2D not defined
			else{
				printf(	"Seond word of view2D not not recognized.\n"
						"Must be vrp, x, dx, screenx, or screeny\n");
			}
		}
			
		// define a 3D view
		else if(strcmp(firstword, "view3D") == 0){
		
			is2D = 0;
			
			// 3D vrp
			if(strcmp(secondword, "vrp") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				zstr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, NULL);
				y = stringToFloat(ystr, numbs, numnumbers, NULL);
				z = stringToFloat(zstr, numbs, numnumbers, NULL);
				point_set3D(&(view3D.vrp), x, y, z);
			}
			
			// 3D vpn
			else if(strcmp(secondword, "vpn") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				zstr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, NULL);
				y = stringToFloat(ystr, numbs, numnumbers, NULL);
				z = stringToFloat(zstr, numbs, numnumbers, NULL);
				vector_set(&(view3D.vpn), x, y, z);
			}
			
			// 3D vup
			else if(strcmp(secondword, "vup") == 0){
				xstr = strtok (NULL, delim);
				ystr = strtok (NULL, delim);
				zstr = strtok (NULL, delim);
				x = stringToFloat(xstr, numbs, numnumbers, NULL);
				y = stringToFloat(ystr, numbs, numnumbers, NULL);
				z = stringToFloat(zstr, numbs, numnumbers, NULL);
				vector_set(&(view3D.vup), x, y, z);
			}
			
			// 3D d
			else if(strcmp(secondword, "d") == 0){
				xstr = strtok (NULL, delim);
				view3D.d = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 3D du
			else if(strcmp(secondword, "du") == 0){
				xstr = strtok (NULL, delim);
				view3D.du = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 3D f
			else if(strcmp(secondword, "f") == 0){
				xstr = strtok (NULL, delim);
				view3D.f = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 3D b
			else if(strcmp(secondword, "b") == 0){
				xstr = strtok (NULL, delim);
				view3D.b = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 3D screnx
			else if(strcmp(secondword, "screenx") == 0){
				xstr = strtok (NULL, delim);
				view3D.screenx = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 3D screeny
			else if(strcmp(secondword, "screeny") == 0){
				xstr = strtok (NULL, delim);
				view3D.screeny = stringToFloat(xstr, numbs, numnumbers, NULL);
			}
			
			// 3D not defined
			else{
				printf(	"Seond word of view3D not not recognized.\n"
						"Must be vrp, vpn, vup, d, du, screenx, or screeny\n");
			}
		}
		
		// firstword not defined
		else{
			printf(	"First word not not recognized.\n"
					"Must be def, add, put, view2D, or view3D\n");
		}
	}
	
	// at the end of the file, parse the most recently defined module
	mod[activeMod]->numlines = curLine;
	activeMod += parseModule(activeMod, mod, pt, v, numbs, l, pl, pg, 
				numparams, numpoints, numvectors, numlines, 
				numpolylines, numpolygons, numnumbers);
	printf("EOF reached\n");
	printf("\ntotal number of modules defined = %d\n",activeMod);
	for(j=0;j<activeMod;j++){
		printf("module named %s\n", mod[j]->name);
	}

	// check that everything was defined correctly
	printf("\nUser defined primitives:\n");
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
	
	// verify that at least one module defined
	if(drawMod == -1){
		printf(	"Must use draw firstword to specify a module to draw.\n"
				" No module to draw, side effects\n");
	} else {

		// define view and draw state and draw last module defined
		matrix_identity( &gtm );
		if(is2D){
			matrix_setView2D( &vtm, &view2D );
			printf("\n2D view matrix:\n");
			matrix_print(&vtm, stdout);
			src = image_create( view2D.screeny, view2D.screenx );
		}
		else {
			matrix_setView3D( &vtm, &view3D );
			printf("\n3D view matrix:\n");
			matrix_print(&vtm, stdout);
			src = image_create( view3D.screeny, view3D.screenx );
		}
		printf("drawing module %s\n", mod[drawMod]->name);
		module_draw(mod[drawMod]->module, &vtm, &gtm, ds, NULL, src);
		image_write(src, outfilename);
		printf("image %s written\n", outfilename);

		// some clean up
		image_free(src);
		for(j=0;j<activeMod;j++){
			printf("freeing module named %s\n", mod[j]->name);
			module_clear(mod[j]->module);
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
		polyline_clear(&(pl[j]->item.polyline));
		free(pl[j]);
	}
	for(j=0;j<numpolygons;j++){
		printf("freeing polygon named %s\n", pg[j]->name);
		polygon_clear(&(pg[j]->item.polygon));
		free(pg[j]);
	}
	printf("\n");

	return(0);
}
