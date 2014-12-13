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
	double genX, genY, genZ, dispersion;
	int verbose = 0;
	if(verbose) printf("updating leader\n");
	dispersion = vector_length(&(l->velocity))/3.0;
	genX = dispersion - ((double)rand() / RAND_MAX) * 2.0 * dispersion;
	genY = dispersion - ((double)rand() / RAND_MAX) * 2.0 * dispersion;
	genZ = dispersion - ((double)rand() / RAND_MAX) * 2.0 * dispersion;
	l->location.val[0] += l->velocity.val[0] + genX;
	l->location.val[1] += l->velocity.val[1] + genY;
	l->location.val[2] += l->velocity.val[2] + genZ;
}

// Actor

/*
 * set the actor shape to the module and assign defaults to other attributes
 */
void actor_init(Actor *a, Leader *boss, Module* shape){
	a->dispersion = 0.5;
	a->minDist = 4;
	a->thresholdDist = 6;
	a->id = 0;
	point_set3D(&(a->location), 0.0, 0.0, 0.0);
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
 * set the actor min dist from other actors
 */
void actor_setMin(Actor *a, float minDist){
	a->minDist = minDist; 
}

/*
 * set the actor threshold dist from other actors
 */
void actor_setThreshold(Actor *a, float thresholdDist){
	a->thresholdDist = thresholdDist; 
}

/*
 * set the actor dispersion
 */
void actor_setDispersion(Actor *a, float dispersion){
	a->dispersion = dispersion; 
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
	double distToOthers, alpha, distToBoss;
	double leaderSpeed = vector_length(&(a->boss->velocity));
	int i, verbose = 0;
	if(verbose) printf("updating actor\n");
	Actor closestActors[2];
	Vector toBoss, awayFromOthers, heading;
	Point otherAvgLoc;

	genX = a->dispersion - ((double)rand() / RAND_MAX) * 2.0 * a->dispersion;
	genY = a->dispersion - ((double)rand() / RAND_MAX) * 2.0 * a->dispersion;
	genZ = a->dispersion - ((double)rand() / RAND_MAX) * 2.0 * a->dispersion;

	// find closest two actors
	closest[0] = closest[1] = DBL_MAX;
	for(i=0; i<nothers; i++){
		dist = point_dist(&(others[i].location), &(a->location));
		if(others[i].id != a->id && (dist < closest[0])) {
			closest[0] = dist;
			closestActors[0] = others[i];
		}
	}
	for(i=0; i<nothers; i++){
		dist = point_dist(&(others[i].location), &(a->location));
		if(others[i].id != a->id && (dist < closest[1]) && (dist != closest[0])) {
			closest[1] = dist;
			closestActors[1] = others[i];
		}
	}
	
	// handle case where no other actors
	if(closest[0] == DBL_MAX)
		vector_set(&heading,a->boss->location.val[0] - a->location.val[0],
							a->boss->location.val[1] - a->location.val[1],
							a->boss->location.val[2] - a->location.val[2]); 
	else {
	
		// handle case where only one other actor
		if(closest[1] == DBL_MAX)
			vector_set(&awayFromOthers, a->location.val[0] - closestActors[0].location.val[0], 
										a->location.val[1] - closestActors[0].location.val[1], 
										a->location.val[2] - closestActors[0].location.val[2]);

		// calculate vector away from average position of others
		else{			
			point_avg(&otherAvgLoc, &(closestActors[0].location), &(closestActors[1].location));
			vector_set(&awayFromOthers, a->location.val[0] - otherAvgLoc.val[0], 
										a->location.val[1] - otherAvgLoc.val[1], 
										a->location.val[2] - otherAvgLoc.val[2] );
		}
		distToOthers = vector_length(&awayFromOthers);
		vector_normalize(&awayFromOthers); 

		// calculate vector to leader
		vector_set(&toBoss, a->boss->location.val[0] - a->location.val[0],
							a->boss->location.val[1] - a->location.val[1],
							a->boss->location.val[2] - a->location.val[2]); 
		distToBoss = vector_length(&toBoss);
		vector_normalize(&toBoss);

		// andrew suggests vector blending with toBoss and awayFromOthers
		alpha = 0.0; // just going toward boss
		if(distToOthers < a->minDist || distToBoss <= a->minDist){
			alpha = 1.0; // just going away from others
		} else if(distToOthers <= a->thresholdDist){
			alpha = (a->thresholdDist-distToOthers) / 
					(a->thresholdDist-a->minDist);
		}
		vector_set(&heading,(1-alpha) * toBoss.val[0] + alpha * awayFromOthers.val[0], 
							(1-alpha) * toBoss.val[1] + alpha * awayFromOthers.val[1], 
							(1-alpha) * toBoss.val[2] + alpha * awayFromOthers.val[2] );
	}
	vector_normalize(&heading);

	// update location according to new heading with jitter and speed
	a->location.val[0] += (heading.val[0]) * leaderSpeed + genX;
	a->location.val[1] += (heading.val[1]) * leaderSpeed + genY;
	a->location.val[2] += (heading.val[2]) * leaderSpeed + genZ;
}

/*
 * set the Module* shape of the actor
 */
void actor_setModule(Actor *a, Module *shape){
	if(a->shape){
		module_delete(a->shape);
	}

	a->shape = shape;
}

/*
 * set the id of the actor
 */
void actor_setID(Actor *a, int id){
	a->id = id;
}

// Swarm

/*
 * Place a swarm at start with a number of leaders that all have 
 * the same initial velocity. 
 */
Swarm *swarm_create(Point *start, Vector *initVel, Module *shape, 
					int numLeaders, int numActorsPerLeader, float spread){
	int i, j, id = 0, verbose = 1;
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
		leader_setLocation(&(s->leaders[i]), 
							start->val[0] + genX, 
							start->val[1] + genY, 
						   	start->val[2] + genZ);
		leader_setVelocity(&(s->leaders[i]), initVel);
		for(j=0; j<numActorsPerLeader; j++){
			genX = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
			genY = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
			genZ = spread - ((double)rand() / RAND_MAX) * 2.0 * spread;
			actor_init(&(s->actors[j+(i*numActorsPerLeader)]), &(s->leaders[i]), shape);
			actor_setLocation(&(s->actors[j+(i*numActorsPerLeader)]), 
								start->val[0] + genX, 
								start->val[1] + genY, 
				 				start->val[2] + genZ);
			actor_setID(&(s->actors[j+(i*numActorsPerLeader)]), id++);
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
 	int i, verbose = 0;
 	if(verbose) printf("drawing swarm\n");
	Matrix m, transGTM;
	Vector up, right, forward;
 	if (!s){
 		printf("no swarm to draw!\n");
 	}
 	vector_set(&up, 0, 1, 0);

 	// draw actors
 	for (i = 0; i < s->numActors; i++){

 		matrix_identity(&m);
	 	vector_copy(&forward, s->actors[i].leader->velocity);
	 	vector_cross(&forward, &up, &right);
	 	vector_cross(&right, &forward, &up);
	 	matrix_rotateXYZ(&m, &forward, &right, &up); 
		matrix_translate(&m,s->actors[i].location.val[0], 
							s->actors[i].location.val[1], 
							s->actors[i].location.val[2]);
		matrix_multiply(&m, GTM, &transGTM);
		
		module_draw(s->actors[i].shape, VTM, &transGTM, ds, lighting, src);

	}

	// draw leaders
	for (i = 0; i < s->numLeaders; i++){

 		matrix_identity(&m);
	 	vector_copy(&forward, s->leaders[i].velocity);
	 	vector_cross(&forward, &up, &right);
	 	vector_cross(&right, &forward, &up);
	 	matrix_rotateXYZ(&m, &forward, &right, &up); 
		matrix_translate(&m,s->leaders[i].location.val[0], 
							s->leaders[i].location.val[1], 
							s->leaders[i].location.val[2]);
		matrix_multiply(&m, GTM, &transGTM);

		module_draw(s->leaders[i].shape, VTM, &transGTM, ds, lighting, src);

	}
 	if(verbose) printf("swarm drawn\n");
 }
 



