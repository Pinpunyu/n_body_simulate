#ifndef _VecAlg_H_
#define _VecAlg_H_

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

typedef struct{
	double x,y,z;
}vector;


vector addVec(vector a,vector b){

	vector c = {a.x + b.x, a.y + b.y, a.z + b.z};
	return c;
}

vector scaleVec(double b,vector a){

    vector c = {b * a.x, b * a.y, b * a.z};
	return c;
}

vector subV(vector a,vector b){
    // Rij //
	
    vector c = {a.x - b.x, a.y - b.y, a.z - b.z};
	return c;
}

double mod(vector a){
	return sqrt(a.x * a.x + a.y*a.y + a.z*a.z);
}

#endif