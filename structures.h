#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <algorithm>
#include <vector>
#include "robustPredicates.h"
using namespace std;
using namespace robustPredicates;

const int nbits = 8;



struct Vertex
{
  unsigned num;
  double x,y,val;
  int bits[nbits]; /* 8 bits */
  /* Contructeur */
  Vertex(double X, double Y, double VAL) : x(X), y(Y), val(VAL)
  {/* No methods associated to struct Vertices */}
  Vertex (double X, double Y, double VAL,int Num) : x(X), y(Y), val(VAL)
  {/* Il n'y as pas de méthodes définies sur cet objet :-) */}
  
};

struct Edge //In the course
{
  Vertex *vmin,*vmax;
  /* Constructeur */
  Edge(Vertex *v1, Vertex *v2)
  {
    vmin = std::min(v1,v2);
    vmax = std::max(v1,v2);
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

/**** METHODE DE ROBUST PREDICATES *****/
int orientationTest(Vertex *a, Vertex *b, Vertex *c); //Can be found in rubust predicate
/**** METHODE DE ROBUST PREDICATES *****/

struct Face
{
  Face   *F[3];
  Vertex *V[3];
  /* Initialisation variable booleenne de nom "deleted" */
  bool deleted;
  /* Constructeur Face */
  Face (Vertex *v0, Vertex *v1, Vertex *v2)
  {
    int ori = orientationTest(v0,v1,v2);   //added for orientation
    if (ori > 0)
    { // printf("ori = %i \n",ori);
      V[0] = v0; V[1] = v1; V[2] = v2;
    }
    else
    {
      V[0] = v1; V[1] = v0; V[2] = v2;
    }
    F[0] = F[1] = F[2] = NULL;
    deleted = false; //In the course
  }
  Edge getEdge(int k)
  {
    return Edge(V[k],V[(k+1)%3]) ;
  }
  bool inCircle (Vertex *d) {
  double circ = robustPredicates::incircle((double*) V[0], (double *) V[1], (double*) V[2], (double*) d);

  return circ>=0.0;
  }/* Can be found in Robust Predicates */

 Vertex centroid () //Function not given
  {
  double cx = ((V[0]->x)   + (V[1]->x)   + (V[2]->x));
  double cy = ((V[0]->y)   + (V[1]->y)   + (V[2]->y));
  double cz = ((V[0]->val) + (V[1]->val) + (V[2]->val));
  return Vertex(cx/3.0,cy/3.0,cz/3.0); // bits aleatoire qui ne servira a rien
  }
};

/*******************************************/
/********* Signatures of functions *********/
/*******************************************/

void square(double &xmin, double &xmax, double &ymin, double &ymax);
//bool sortHilbert (Vertex *v1,Vertex *v2);
bool comp(Vertex* v1, Vertex* v2);
void swap(double& v1, double& v2);
void SuperTriangle(vector<Vertex*> &Vertices, vector<Face*> &Triangles,double xmax,double xmin,double ymax,double ymin);
void printHilbert(std::vector<Vertex*> &S, int d);

/*******************************************/
/********* Functions of the course *********/
/*******************************************/

/**/
void HilbertCoord (double x, double y,double x0, double y0, double xRed, double yRed, double xBlue, double yBlue, int d, int bits[]);
/**/
void  delaunayTrgl(vector<Vertex*> &Vertices, vector<Face*> &Triangles);//,char *name);
void  computeAdjacencies(std::vector<Face*> &cavity);
Face* lineSearch(Face *f, Vertex *v);
void  delaunayCavity(Face *f, Vertex *v, std::vector<Face*> &cavity, std::vector<Edge> &bnd, std::vector<Face*> &otherSide);

#endif

