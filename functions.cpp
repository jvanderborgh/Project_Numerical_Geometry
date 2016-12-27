#include <map>
#include <stdio.h>
#include <vector>
#include "struct.h"
#include "functions_prof.h"
#include "robustPredicates.h"

using namespace std;
using namespace robustPredicates;

static int verb;

void computeAdjacencies (std::vector<Face*> &cavity)
{
    std::map<Edge, std::pair<int, Face*> >edgeToFace;
    for(int iFace = 0; iFace<cavity.size(); iFace++)
    {
        for (int iEdge =0; iEdge<3 ; iEdge ++)
        {
            Edge edge = cavity[iFace]->getEdge(iEdge);

            std::map<Edge, std::pair<int, Face*> >::iterator it = edgeToFace.find(edge);

            if(it == edgeToFace.end())
            {
                edgeToFace.insert(std::make_pair(edge,std::make_pair(iEdge,cavity[iFace])));
            }
            else
            {
                cavity[  iFace  ]->F[     iEdge      ] = it->second.second;
                it->second.second->F[it->second.first] = cavity[  iFace  ];
                edgeToFace.erase(it);
            }
        }
    }
}

void delaunayCavity(Face *f, Vertex *v, std::vector<Face*> &cavity, std::vector<Edge> &bnd, std::vector<Face*> &otherSide)
{
    if(f->deleted) return;  // marked as checked (otherSide)
    f->deleted = true;
    cavity.push_back(f);    // mark the triangle and push it

    for(int iNeigh=0; iNeigh<3; iNeigh++)
    {
        // If no neighbour, IT is a boundary
        if(f->F[iNeigh] == NULL){
            bnd.push_back(f->getEdge(iNeigh));
if(verb>3)
{
           printf(">>>>>> pushed edge 1 : (%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)\n",
                  f->getEdge(iNeigh).vmin->x,
                  f->getEdge(iNeigh).vmin->y,
                  f->getEdge(iNeigh).vmin->z,
                  f->getEdge(iNeigh).vmax->x,
                  f->getEdge(iNeigh).vmax->y,
                  f->getEdge(iNeigh).vmax->z);
}
        }
        // If neighbour is delaunay, IT is a boundary
        else if(!f->F[iNeigh]->inCircle(v))
        {
            bnd.push_back(f->getEdge(iNeigh));
if(verb>3)
{
           printf(">>>>>> pushed edge 2 : (%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)\n",
                  f->getEdge(iNeigh).vmin->x,
                  f->getEdge(iNeigh).vmin->y,
                  f->getEdge(iNeigh).vmin->z,
                  f->getEdge(iNeigh).vmax->x,
                  f->getEdge(iNeigh).vmax->y,
                  f->getEdge(iNeigh).vmax->z);   
}
            if(!f->F[iNeigh]->deleted)
            {
                otherSide.push_back(f->F[iNeigh]);  // otherSide triangle
                f->F[iNeigh]->deleted = true;       // mark it as checked
            }
        }
        // If neighbour is non-delaunay, get more fun :D
        else delaunayCavity(f->F[iNeigh], v, cavity, bnd, otherSide);
    }
}

int orientationTest(Vertex *a, Vertex *b,Vertex *c){
	/* FIRST VERSION */
    // double Or = (a->x-c->x)*(b->y-c->y) - (a->y-c->y)*(b->x-c->x);
    // printf("Or0 = %.3f\n",Or);
    // if(Or>0.0) return +1;
    // if(Or<0.0) return -1;
    // return 0;
    /* ROBST VERSION */
    double A[2]; A[0] = a->x; A[1] = a->y; // printf("A = %.3E, %.3E\n",A[0],A[1]);
    double B[2]; B[0] = b->x; B[1] = b->y; // printf("B = %.3E, %.3E\n",B[0],B[1]);
    double C[2]; C[0] = c->x; C[1] = c->y; // printf("C = %.3E, %.3E\n",C[0],C[1]);
    double D = robustPredicates::orient2d(A,B,C);
    if(D>0.0) return +1;
    if(D<0.0) return -1;
    return 0;
}

Face* lineSearch(Face *f, Vertex *v){
//    int step = 0;
    while(1)
    {
        //printf("%d \n",step);
        if(f==    NULL   ) return NULL; // If none... end ?
        if(f->inCircle(v))
        {
if(verb>3)
{
          printf(">>>>>> (%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)\n",
              f->V[0]->x,f->V[0]->y,f->V[0]->z,
              f->V[1]->x,f->V[1]->y,f->V[1]->z,
              f->V[2]->x,f->V[2]->y,f->V[2]->z);   
}
//            printf("%i ",step);
            return f;    // That's the one :)
        }
        Vertex c = f->centroid();       // just in order to have a point in the triangle

        for(int iNeigh=0; iNeigh<3; iNeigh++)
        {
if(verb>3)
{
          printf(">>>>>> (%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)\n",
              f->V[0]->x,f->V[0]->y,f->V[0]->z,
              f->V[1]->x,f->V[1]->y,f->V[1]->z,
              f->V[2]->x,f->V[2]->y,f->V[2]->z);   
}
            Edge e = f->getEdge(iNeigh);
            // looking for the direction of the search with orientation (crossing)
            if( orientationTest (&c, v, e.vmin) *
                orientationTest (&c, v, e.vmax) <=0
                &&
                orientationTest (e.vmin, e.vmax, &c) *
                orientationTest (e.vmin, e.vmax,  v) <=0)
            {
if(verb>3)
{
          printf(">>>>>> (%.3E,%.3E)(%.3E,%.3E)\n",
              e.vmin->x,e.vmin->y,
              e.vmax->x,e.vmax->y);   
}
                f = f->F[iNeigh];   // while(1) redo lineSearch until return
                break;              // break in order to redo the lineSearch
            }
        }
//        step = step + 1 ;
    }
}


void HilbertCoord(double x0, double y0, double xRed, double yRed, double xBlue, double yBlue, Vertex* V, int nbits)
{
    for(int i =0; i<nbits; i++)
    {
        double coordRed = (V->x-x0)*xRed  + (V->y-y0)*yRed ;
        double coordBlue= (V->x-x0)*xBlue + (V->y-y0)*yBlue;
        xRed /= 2; yRed /= 2; xBlue /=2; yBlue /=2;
        if      (coordRed <= 0 &&coordBlue <=0 )
        {
            // Quadrant 0
            x0 -=(xBlue+xRed);
            y0 -=(yBlue+yRed);
            swap(xRed,xBlue);
            swap(yRed,yBlue);
            V->bits[i] = 0;
        }
        else if (coordRed <=0 && coordBlue >= 0)
        {
            // Quadrant 1
            x0 += (xBlue-xRed);
            y0 += (yBlue-yRed);
            V->bits[i] = 1 ;
        }
        else if (coordRed >=0 && coordBlue >= 0)
        {
            //Quadrant 2
            x0 += (xBlue+xRed) ;
            y0 += (yBlue+yRed) ;
            V->bits[i] = 2;
        }
        else
        {
            //Quadrant 3
            x0 += (-xBlue+xRed) ;
            y0 += (-yBlue+yRed) ;
            swap(xRed,xBlue) ;
            swap(yRed,yBlue) ;
            xBlue = - xBlue;
            yBlue = - yBlue;
            xRed  = - xRed ;
            yRed  = - yRed ;
            V->bits[i]=3      ;
        }
    }
}


void delaunayTrgl(std::vector<Vertex*> &S, std::vector<Face*> &T, int verbose){

    verb = verbose;

    for(int iP=0; iP<S.size(); iP++){

    if(verbose>2){printf("\nIteration %i : (%.3E,%.3E,%.3E)\n",iP,S[iP]->x,S[iP]->y,S[iP]->z);}

    if(verbose>2){printf("%i >>> Looking for cavity\n",iP);} 
    // Choose the first non-delaunay so we can find the cavity
    Face *f = lineSearch(T[T.size()-1], S[iP]);

    std::vector<Face*> cavity   ; // push non-delaunay triangles
    std::vector<Edge> bnd       ; // so we can build new triang.
    std::vector<Face*> otherSide; // so we can compute adjencies

    if(verbose>2){printf("%i >>> Pushing in cavity\n",iP);}
    delaunayCavity(f, S[iP], cavity, bnd, otherSide);

    if(verbose>2){printf("%i >>> Validating cavity... ",iP);}
    if(bnd.size() != cavity.size() + 2) throw; // see course
    if(verbose>2){printf("OK\n");}

    for (int i=0; i<cavity.size(); i++)
    {
        /*------------------------------
        For each non-delaunay triangle :
        -re-initialize bool deleted
        -no neighbours triangles
        -Face(edge.v1,edge.v2,nvVertex);
        IN ORDER TO DO ADJENCIES !!! :D
        ------------------------------*/
        cavity[i]->deleted = false;
        cavity[i]->F[0] = cavity[i]->F[1] = cavity[i]->F[2] = NULL;
        cavity[i]->V[0] = bnd[i].vmin;
        cavity[i]->V[1] = bnd[i].vmax;
        cavity[i]->V[2] = S[iP];
    }

    if(verbose>2){printf("%i >>> Constructing triangles (vrt) \n",iP);}
    unsigned int cSize = cavity.size();
    for(int i=cSize; i<cSize+2; i++){
        /*------------------------------
        For each non-delaunay triangle :
        -re-initialize bool deleted
        -no neighbours triangles
        -Face(edge.v1,edge.v2,nvVertex);
        IN ORDER TO ADD TRIANGLES :))))
        ------------------------------*/
        Face *newf = new Face(bnd[i].vmin,bnd[i].vmax,S[iP]);
        T.push_back(newf);
        cavity.push_back(newf);
    }

    if(verbose>2){printf("%i >>> Constructing triangles (adj) \n",iP);}
    for(int i=0; i<otherSide.size(); i++)
    {
        otherSide[i]->deleted = false; if(otherSide[i])cavity.push_back(otherSide[i]);
    }
    computeAdjacencies(cavity);

// In order to print the triangles and to check them
// for(vector<Face*>::iterator i = T.begin(); i != T.end();++i)
// {
//     printf(">>>>>> Triangle : (%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)(%.3E,%.3E,%.3E)\n",
//         (*i)->V[0]->x,(*i)->V[0]->y,(*i)->V[0]->z,
//         (*i)->V[1]->x,(*i)->V[1]->y,(*i)->V[1]->z,
//         (*i)->V[2]->x,(*i)->V[2]->y,(*i)->V[2]->z);
// }
    }
}
