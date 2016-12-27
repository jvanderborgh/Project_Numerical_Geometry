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
		V[0] = v0; //printf("v0 : %.3E, %.3E, %.3E\n",v0->x,v0->y,v0->z);
		V[1] = v1; //printf("v1 : %.3E, %.3E, %.3E\n",v1->x,v1->y,v1->z);
		V[2] = v2; //printf("v2 : %.3E, %.3E, %.3E\n",v2->x,v2->y,v2->z);
		F[0] = NULL;
		F[1] = NULL;
		F[2] = NULL;
		deleted = false;
    }
	Edge getEdge(int k){
		// printf("returned edge : (%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)\n",
  //                  V[   k   ]->x,V[   k   ]->y,V[   k   ]->z,
  //                  V[(k+1)%3]->x,V[(k+1)%3]->y,V[(k+1)%3]->z);
		return Edge (V[k],V[(k+1)%3]);
	}
	bool inCircle(Vertex *c){
		/* version #1 */ /*
		// Calcul des distances
		double ra = V[0]->x*V[0]->x+V[0]->y*V[0]->y; //printf("ra : %.3E\n",ra);
		double rb = V[1]->x*V[1]->x+V[1]->y*V[1]->y; //printf("rb : %.3E\n",rb);
		double rc = V[2]->x*V[2]->x+V[2]->y*V[2]->y; //printf("rc : %.3E\n",rc);
		double rd = c->x*c->x+c->y*c->y; //printf("rd : %.3E\n",rd);
		double T1  = V[0]->x*(V[1]->y*rc-V[2]->y*rb)+V[1]->x*(V[2]->y*ra-V[0]->y*rc)+V[2]->x*(V[0]->y*rb-V[1]->y*ra);
		double T2  = V[1]->x*(V[2]->y*rd-   c->y*rc)+V[2]->x*(   c->y*rb-V[1]->y*rd)+   c->x*(V[1]->y*rc-V[2]->y*rb);
		double T3  = V[2]->x*(   c->y*ra-V[0]->y*rd)+   c->x*(V[0]->y*rc-V[2]->y*ra)+V[0]->x*(V[2]->y*rd-   c->y*rc);
		double T4  =    c->x*(V[0]->y*rb-V[1]->y*ra)+V[0]->x*(V[1]->y*rd-   c->y*rb)+V[1]->x*(   c->y*ra-V[0]->y*rd);
		//printf("T1 : %.3E\n",T1);
		//printf("T2 : %.3E\n",T2);
		//printf("T3 : %.3E\n",T3);
		//printf("T4 : %.3E\n",T4);
		double T = T1-T2+T3-T4;
		//printf("T : %.3E - %.3E + %.3E - %.3E = %.3E\n",T1,T2,T3,T4,T);
		*/
		/* version #2 *//*
		double a11 = V[0]->x-c->x;
		double a21 = V[1]->x-c->x;
		double a31 = V[2]->x-c->x;
		double a12 = V[0]->y-c->y;
		double a22 = V[1]->y-c->y;
		double a32 = V[2]->y-c->y;
		double a13 = a11*a11+a12*a12;
		double a23 = a21*a21+a22*a22;
		double a33 = a31*a31+a32*a32;
		double T1 = a11*a22*a33+a12*a23*a31+a21*a32*a13-a11*a23*a32-a22*a13*a31-a33*a12*a21;
		a11 = V[0]->x-V[2]->x;
		a21 = V[0]->y-V[2]->y;
		a12 = V[1]->x-V[2]->x;
		a22 = V[1]->y-V[2]->y;
		double T2 = a11*a22-a12*a21;
		printf("E0 = %.3E\n",T1*T2);
		return T1*T2>0.0;
		*/
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
