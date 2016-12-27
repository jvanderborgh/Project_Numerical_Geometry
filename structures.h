#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <algorithm> 	// useful for std::min
#include "robustPredicates.h"
using namespace robustPredicates;

// Structure vrtx (source:course)
struct Vertex{
	double x;
	double y;
	double z;
	int index;
	int bits[30];
	Vertex(double X, double Y, double Z) : x(X),y(Y),z(Z){}
};

// Structure edge (source:course)
struct Edge{
	Vertex *vmin;
	Vertex *vmax;
	Edge(Vertex *v1, Vertex *v2){
		vmin = std::min(v1,v2);
		vmax = std::max(v1,v2);
	}
	bool operator < (const Edge &other) const {
		if(vmin<other.vmin) return true;
		if(vmin>other.vmin) return false;
		if(vmax<other.vmax) return true;
		return false;
	}
};

// Structure face (source:course)
struct Face{
	Face *F[3];
	Vertex *V[3];
	bool deleted;
	Face(Vertex *v0, Vertex *v1, Vertex *v2){
		V[0] = v0; 
		V[1] = v1; 
		V[2] = v2;
		F[0] = F[1] = F[2] NULL;
		deleted = false;
    }
	Edge getEdge(int k)
	{
		return Edge (V[k],V[(k+1)%3]);
	}
	bool inCircle(Vertex *c)
	{
		/* version rP */    
		double A[2]; A[0] = V[0]->x; A[1] = V[0]->y;
    	double B[2]; B[0] = V[1]->x; B[1] = V[1]->y;
    	double C[2]; C[0] = V[2]->x; C[1] = V[2]->y;
    	double D[2]; D[0] = c->x;    D[1] = c->y;
		double E = robustPredicates::incircle(A,B,C,D)*robustPredicates::orient2d(A,B,C);
		return E>0.0;
	}
	Vertex centroid(){
		return Vertex((V[0]->x+V[1]->x+V[2]->x)/3.0,(V[0]->y+V[1]->y+V[2]->y)/3.0,(V[0]->z+V[1]->z+V[2]->z)/3.0);
	}
};

#endif

