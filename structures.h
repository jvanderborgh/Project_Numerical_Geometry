#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__


#include <stdio.h>
#include <algorithm>
#include <vector>


struct Vertex // In the course (num and bits added)
{
  int num,(*bits); /* max 10 bits */
  double x,y,z;

  /* Constructeur */
  Vertex (int Num, double X, double Y, double Z, int (*Bits)) : num(Num), x(X), y(Y), z(Z), bits(Bits)
  {/* Il n'y as pas de méthodes définies sur cet objet :-) */}
  
  /* Constructeur */
  Vertex (double X, double Y, double Z) : x(X),y(Y),z(Z) 
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
  bool inCircle (Vertex *d) /* Can be found in Robust Predicates */
  {
   /* Matrix for incircle test */
   /* a = V0, b = V1 and c = V2 */
   double a11 = (V[0]->x) - (d->x);  double a12 = (V[0]->y) - (d->y); double a13 = a11*a11 + a12*a12;
   double a21 = (V[1]->x) - (d->x);  double a22 = (V[1]->y) - (d->y); double a23 = a21*a21 + a22*a22;
   double a31 = (V[2]->x) - (d->x);  double a32 = (V[2]->y) - (d->y); double a33 = a31*a31 + a32*a32;
   double det = a11*((a22*a33)-(a32*a23)) - a12*((a21*a33)-(a31*a23)) + a13*((a21*a32)-(a31*a22));

    /* Matrix for orientation test */
    double b11 = (V[0]->x)-(V[2]->x) ;
    double b12 = (V[0]->y)-(V[2]->y);
    double b21 = (V[1]->x)-(V[2]->x);
    double b22 = (V[1]->y)-(V[2]->y);
    double sign = (b11*b22)-(b21*b12);
   
  if(sign*det >= 0.0)
    return true;    /* d lies inside or on the circle */
  else
    return false;   /* d lies outside */
 }
 Vertex centroid () //Function not given
  {
  double cx = ((V[0]->x) + (V[1]->x) + (V[2]->x));  
  double cy = ((V[0]->y) + (V[1]->y) + (V[2]->y));
  double cz = ((V[0]->z) + (V[1]->z) + (V[2]->z));
    return Vertex(-100,cx/3.0,cy/3.0,cz/3.0,V[0]->bits); // bits aleatoire qui ne servira a rien
  }
};

/*******************************************/
/********* Signatures of functions *********/
/*******************************************/
void square(double &xmin, double &xmax, double &ymin, double &ymax);
bool trie(Vertex* v1, Vertex* v2);
void swap(double& v1, double& v2);
void printHilbert(std::vector<Vertex*> &S, int d);

/*******************************************/
/********* Functions of the course *********/
/*******************************************/

void  HilbertCoord(double x, double y,double x0, double y0, double xRed, double yRed, double xBlue, double yBlue, int d, int bits[]);
void  computeAdjacencies(std::vector<Face*> &cavity);
void  delaunayCavity(Face *f, Vertex *v, std::vector<Face*> &cavity, std::vector<Edge> &bnd, std::vector<Face*> &otherSide);
Face* lineSearch(Face *f, Vertex *v);
void  delaunayTrgl(std::vector<Vertex*> &S, std::vector<Face*> &T);//,char *name);

#endif

