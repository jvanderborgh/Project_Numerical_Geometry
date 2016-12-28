#ifndef FUNCTIONS_H
#define FUNCTIONS_H

using namespace std;

/*******************************************/
/********* Signatures of functions *********/
/*******************************************/

void superTriangles(vector<Face*> &T, vector<Vertex*> &D, double &xmin, double &xmax, double &ymin, double &ymax, double &L);
void supressBigTriangles(vector<Face*> &T, double &xmin, double &xmax, double &ymin, double &ymax);

/********* Functions of the course *********/

/*********-------- HILBERT --------*********/
void  HilbertCoord(double x0, double y0, double xRed, double yRed, double xBlue, double yBlue, Vertex* V);
bool  vCompare(Vertex* v1, Vertex* v2);

/********* DELAUNAY TRIANGULATION  *********/
void  computeAdjacencies(vector<Face*> &cavity);
void  delaunayCavity(Face *f, Vertex *v, vector<Face*> &cavity, vector<Edge> &bnd, vector<Face*> &otherSide);
Face* lineSearch    (Face *f, Vertex *v);
int   orientationTest(Vertex *a, Vertex *b,Vertex *c);

/* Main Function of Delaunay Triangulation */
void  delaunayTrgl(vector<Vertex*> &S, vector<Face*> &T, int verbose);

#endif
