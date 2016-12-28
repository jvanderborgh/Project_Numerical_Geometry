#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <algorithm> 	// useful for std::min
#include "robustPredicates.h"

using namespace std;
using namespace robustPredicates;

const int nbits = 8;

struct Vertex
{
	double x, y, z;
	int index;
	int bits[nbits]; /* 8 bits */
	/* Contructeur */
	Vertex(double X, double Y, double Z) : x(X),y(Y),z(Z)
	{/* No methods associated to struct Vertices */}
};

struct Edge
{
	Vertex *vmin, *vmax;
	/* Constructeur */
	Edge(Vertex *v1, Vertex *v2)
	{
		vmin = min(v1,v2);
		vmax = max(v1,v2);
	}
	/* Methode de redefinition de l'opérateur " < " */
	bool operator < (const Edge &other) const 
	{
		if(vmin<other.vmin) return true;
		if(vmin>other.vmin) return false;
		if(vmax<other.vmax) return true;
		return false;
	}
};

struct Face
{
	Face   *F[3]; /* Tableau de 3 triangles */
  	Vertex *V[3]; /* Tableau de 3 points    */
	bool deleted;
  	/* Constructeur Face */
	Face(Vertex *v0, Vertex *v1, Vertex *v2)
	{
		V[0] = v0; 
		V[1] = v1; 
		V[2] = v2;
		F[0] = F[1] = F[2] = NULL;
		deleted = false;
    }
    
    /************************/
    /*** METHODES DE FACE ***/
    /************************/

	Edge getEdge(int k)
	{
		return Edge (V[k],V[(k+1)%3]); /* %3 permet de retourner O si k=3 :-) */
	}
	bool inCircle(Vertex *c)
	{
		/* version rP */    
		double A[2]; A[0] = V[0]->x; A[1] = V[0]->y;
    	double B[2]; B[0] = V[1]->x; B[1] = V[1]->y;
    	double C[2]; C[0] = V[2]->x; C[1] = V[2]->y;
    	double D[2]; D[0] = c->x;    D[1] = c->y;
    	/************ robustPredicates::incircle ************/
  		/* Si + et sens anti-horloger => Dans     le cercle */
  		/* Si + et sens horloger      => Pas dans le cercle */
  		/* Si O                       => Cocicrulaires!     */
  		/* Si - et sens anti-horloger => Pas dans le cercle */
  		/* Si - et sens horloger      => Dans     le cercle */

  		/************ robustPredicates::orient2d ************/
 		/* Si sens anti-horloger => +      */
  		/* Si colinéaire         => O      */
  		/* Si sens horloger      => -      */
		double E = robustPredicates::incircle(A,B,C,D) * robustPredicates::orient2d(A,B,C);
		return E>0.0;
	}
	Vertex centroid()
	{	
		double cx = ((V[0]->x) + (V[1]->x) + (V[2]->x));
    	double cy = ((V[0]->y) + (V[1]->y) + (V[2]->y));
    	double cz = ((V[0]->z) + (V[1]->z) + (V[2]->z));
    	return Vertex(cx/3.0,cy/3.0,cz/3.0);
	}
};

#endif

