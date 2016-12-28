#ifndef FUNCTIONS_H
#define FUNCTIONS_H

using namespace std;

/*******************************************/
/********* Signatures of functions *********/
/*******************************************/

void superTriangles(vector<Face*> &T, vector<Vertex*> &D, double &xmin, double &xmax, double &ymin, double &ymax, double &x0, double &y0, double &xRed, double &yRed, double &xBlue, double &yBlue);

/*******************************************/
/********* Functions of the course *********/
/*******************************************/
void  HilbertCoord(double x0, double y0, double xRed, double yRed, double xBlue, double yBlue, Vertex* V);
bool vCompare(Vertex* v1, Vertex* v2);

void  computeAdjacencies(vector<Face*> &cavity);
void  delaunayCavity(Face *f, Vertex *v, vector<Face*> &cavity, vector<Edge> &bnd, vector<Face*> &otherSide);
Face* lineSearch(Face *f, Vertex *v);
int   orientationTest(Vertex *a, Vertex *b,Vertex *c);
void  delaunayTrgl(vector<Vertex*> &S, vector<Face*> &T, int verbose);

#endif // FUNCTIONS_H
