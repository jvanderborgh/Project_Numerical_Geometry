#ifndef FUNCTIONS_PROF_H
#define FUNCTIONS_PROF_H
void computeAdjacencies (std::vector<Face*> &cavity);
void delaunayCavity(Face *f, Vertex *v, std::vector<Face*> &cavity, std::vector<Edge> &bnd, std::vector<Face*> &otherSide);
Face* lineSearch(Face *f, Vertex *v);
void delaunayTrgl(std::vector<Vertex*> &S, std::vector<Face*> &T, int verbose);
int orientationTest(Vertex *a, Vertex *b,Vertex *c);
void HilbertCoord(double x0, double y0, double xRed, double yRed, double xBlue, double yBlue, Vertex* V, int nbits);

#endif // FUNCTIONS_PROF_H
