/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 12/2014
 *
 * The swarm
 */

#include "graphics.h"
#include "float.h"

static inline double point_dist(Point *x, Point *y){
	return 	(x->val[0] - y->val[0]) * (x->val[0] - y->val[0]) +
			(x->val[1] - y->val[1]) * (x->val[1] - y->val[1]) +
			(x->val[2] - y->val[2]) * (x->val[2] - y->val[2]);
}

// Leader 

/*
 * set the leader shape to the module and assign defaults to other attributes
 */
void leader_init(Leader *l, Module* shape){
	point_set3D(&(l->location), 0.0, 0.0, 0.0);
	vector_set(&(l->velocity), 0.0, 0.0, 0.0);
	color_set(&(l->color), 1.0, 1.0, 1.0);

	l->shape = shape;
}

/*
 * set the leader location
 */
void leader_setLocation(Leader *l, float x, float y, float z){
	point_set3D(&(l->location), x, y, z);
}

/*
 * set the leader velocity
 */
void leader_setVelocity(Leader *l, Vector *velocity){
	vector_copy(&(l->velocity), velocity);
}

/*
 * set the leader color
 */
void leader_setColor(Leader *l, Color *c){
	color_copy(&(l->color), c);
}

/*
 * set the Module* shape of the leader
 */
 void leader_setModule(Leader *l, Module *shape){
 	if(l->shape){
 		module_delete(l->shape);
 	}

 	l->shape = shape;
 }

/*
 * update the leader's location
 */
void leader_update(Leader *l){
	int verbose = 0;
	if(verbose) printf("updating leader\n");

	l->location.val[0] += l->velocity.val[0];
	l->location.val[1] += l->velocity.val[1];
	l->location.val[2] += l->velocity.val[2];
}

// Actor

/*
 * set the actor shape to the module and assign defaults to other attributes
 */
void actor_init(Actor *a, Leader *boss, Module* shape){
	a->dispersion = a->speed = 0.5;
	point_set3D(&(a->location), 0.0, 0.0, 0.0);
	color_set(&(a->color), 1.0, 1.0, 1.0);

	a->boss = boss;
	a->shape = shape;

}

/*
 * set the actor location
 */
void actor_setLocation(Actor *a, float x, float y, float z){
	point_set3D(&(a->location), x, y, z);
}

/*
 * set the actor velocity
 */
void actor_setSpeed(Actor *a, float speed){
	a->speed = speed;
}

/*
 * set the actor dispersion
 */
void actor_setDispersion(Actor *a, float dispersion){
	a->dispersion = dispersion; 
}

/*
 * set the actor color
 */
void actor_setColor(Actor *a, Color *c){
	color_copy(&(a->color), c);
}

/*
 * set the actor's boss, which informs the actor how to update
 */
void actor_setBoss(Actor *a, Leader *boss){
	a->boss = boss;
}

/*
 * update the actor's location according to:
 * -moving towards their leader
 * -staying a minimum distance from other actors
 */
void actor_update(Actor *a, Actor *others, int nothers){
	double genX, genY, genZ;
	double dist, closest[2];
	double distToOthers, distToBoss, alpha, minDist, thresholdDist;
	int i, verbose = 0;
	if(verbose) printf("updating actor\n");
	Actor closestActors[2];
	Vector toBoss, awayFromOthers, heading;
	Point otherAvgLoc;

	// find closest two actors
	closest[0] = closest[1] = DBL_MAX;
	for(i=0; i<nothers; i++){
		dist = point_dist(&(others[i].location), &(a->location));
		if(dist && (dist < closest[0])) {
			closest[0] = dist;
			closestActors[0] = others[i];
		}
	}
	for(i=0; i<nothers; i++){
		dist = point_dist(&(others[i].location), &(a->location));
		if(dist && (dist < closest[1]) && (dist != closest[0])) {
			closest[1] = dist;
			closestActors[1] = others[i];
		}
	}

	genX = a->dispersion - ((double)rand() / RAND_MAX) * 2.0 * a->dispersion;
	genY = a->dispersion - ((double)rand() / RAND_MAX) * 2.0 * a->dispersion;
	genZ = a->dispersion - ((double)rand() / RAND_MAX) * 2.0 * a->dispersion;

	// calculate vector away from average position of others
	point_avg(&otherAvgLoc, &(closestActors[0].location), &(closestActors[1].location));
	vector_set(&awayFromOthers, a->location.val[0] - otherAvgLoc.val[0], 
								a->location.val[1] - otherAvgLoc.val[1], 
								a->location.val[2] - otherAvgLoc.val[2]);
	distToOthers = vector_length(&awayFromOthers);
	vector_normalize(&awayFromOthers); 

	// calculate vector to leader
	vector_set(&toBoss, a->boss->location.val[0] - a->location.val[0],
						a->boss->location.val[1] - a->location.val[1],
						a->boss->location.val[2] - a->location.val[2]); 
	distToBoss = vector_length(&toBoss);
	vector_normalize(&toBoss);

	// andrew suggests vector blending with toBoss and awayFromOthers
	thresholdDist = 10; // getting too close, start evading
	minDist = 4.0; // bug size, time to really move away
	alpha = 0.0; // just going toward boss
	if(distToOthers < minDist){
		alpha = 1.0; // just going away from others
	} else if(distToOthers <= thresholdDist){
		alpha = (thresholdDist-distToOthers) / (thresholdDist-minDist);
	}
	vector_set(&heading,(1-alpha) * toBoss.val[0] + alpha * awayFromOthers.val[0], 
						(1-alpha) * toBoss.val[1] + alpha * awayFromOthers.val[1], 
						(1-alpha) * toBoss.val[2] + alpha * awayFromOthers.val[2] );
	vector_normalize(&heading);

	// update location according to new heading with jitter and speed
	a->location.val[0] += (heading.val[0] + genX) * a->speed;
	a->location.val[1] += (heading.val[1] + genY) * a->speed;
	a->location.val[2] += (heading.val[2] + genZ) * a->speed;
}

/*
 * set the Module* shape of the leader
 */
 void actor_setModule(Actor *a, Module *shape){
 	if(a->shape){
 		module_delete(a->shape);
 	}

 	a->shape = shape;
 }

// Swarm

/*
 * Place a swarm at start with a number of leaders that all have 
 * the same initial velocity. 
 */
Swarm *swarm_create(Point *start, Vector *initVel, Module *shape, 
					int numLeaders, int numActorsPerLeader, float spread){
	int i, j, verbose = 1;
 	float genX, genY, genZ;

	if(verbose) printf("creating swarm\n");

	Swarm *s = malloc(sizeof(Swarm));
	s->leaders = malloc(sizeof(Leader)*numLeaders);
	s->actors = malloc(sizeof(Actor)*numActorsPerLeader*numLeaders);
	s->numActors = numActorsPerLeader*numLeaders;
	s->numLeaders = numLeaders;
	for(i=0; i<numLeaders; i++){
		genX = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
		genY = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
		genZ = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
		leader_init(&(s->leaders[i]), shape);
		leader_setLocation(&(s->leaders[i]), start->val[0] + genX, start->val[1] + genY, 
						   start->val[2] + genZ);
		leader_setVelocity(&(s->leaders[i]), initVel);
		for(j=0; j<numActorsPerLeader; j++){
			genX = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
			genY = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
			genZ = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
			actor_init(&(s->actors[j+(i*numActorsPerLeader)]), &(s->leaders[i]), shape);
			actor_setLocation(&(s->actors[i]), start->val[0] + genX, start->val[1] + genY, 
				 				start->val[2] + genZ);
		}
	}
	return s;
}

/*
 * free the swarm memory, setting numbers to zero
 */
void swarm_clear(Swarm *s){
 	if(s){
 		if(s->leaders)
 			free(s->leaders);
 		if(s->actors)
 			free(s->actors);
 		s->numLeaders = s->numActors = 0;
 	}
 }

/*
 * free the swarm memory, including the pointer to the swarm
 */
void swarm_free(Swarm *s){
 	if(s){
 		if(s->leaders)
 			free(s->leaders);
 		if(s->actors)
 			free(s->actors);
 		free(s);
 	}
 }

/*
 * update the swarm's leaders and actors
 */
void swarm_update(Swarm *s){
	int i, verbose = 1;
	if(verbose) printf("updating swarm\n");
	for (i = 0; i < s->numActors; i++)
		actor_update(&(s->actors[i]), &(s->actors[i+1]), s->numActors);
	for (i = 0; i < s->numLeaders; i++)
		leader_update(&(s->leaders[i]));
}

/* 
 * draws the swarm using the given view etc into the given image
 */
 void swarm_draw(Swarm *s, Matrix *VTM, Matrix *GTM, DrawState *ds, 
				Lighting *lighting, Image *src){
 	int i;
 	Element *translateE, *colorE, *bodyColorE, *identityE, *headE_old;
	Matrix m;

 	if (!s){
 		printf("no swarm to draw!\n");
 	}

 	// draw actors
 	for (i = 0; i < s->numActors; i++){
 		matrix_identity(&m);
		matrix_translate(&m, s->actors[i].location.val[0], s->actors[i].location.val[1], 
							s->actors[i].location.val[2]);
		translateE = element_init(ObjMatrix, &m);
		colorE = element_init(ObjColor, &(s->actors[i].color));
		bodyColorE = element_init(ObjBodyColor, &(s->actors[i].color));
		identityE = element_init(ObjIdentity, NULL);

		headE_old = s->actors[i].shape->head;
		s->actors[i].shape->head = identityE;
		identityE->next = translateE;
		translateE->next = colorE;
		colorE->next = bodyColorE;
		bodyColorE->next = headE_old;
		module_draw(s->actors[i].shape, VTM, GTM, ds, lighting, src);

		s->actors[i].shape->head = headE_old;
		element_delete(translateE);
		element_delete(colorE);
	}

	// draw leaders
	for (i = 0; i < s->numLeaders; i++){
 		matrix_identity(&m);
		matrix_translate(&m, s->leaders[i].location.val[0], s->leaders[i].location.val[1], 
							s->leaders[i].location.val[2]);
		translateE = element_init(ObjMatrix, &m);
		colorE = element_init(ObjColor, &(s->leaders[i].color));
		bodyColorE = element_init(ObjBodyColor, &(s->leaders[i].color));
		identityE = element_init(ObjIdentity, NULL);

		headE_old = s->leaders[i].shape->head;
		s->leaders[i].shape->head = identityE;
		identityE->next = translateE;
		translateE->next = colorE;
		colorE->next = bodyColorE;
		bodyColorE->next = headE_old;
		module_draw(s->leaders[i].shape, VTM, GTM, ds, lighting, src);

		s->leaders[i].shape->head = headE_old;
		element_delete(translateE);
		element_delete(colorE);
	}
 }
 



