//#include "structures.h"
#include "reader_writer.h" //#include "structures.h"
//#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector> // for std::vector
#include <map>    // for std::map
#include <cmath>
#include <iostream>
using namespace std; // std::vector -> vector
using namespace robustPredicates;

/************************************************/
/** Hilbert + functions for Hilbert **/
/************************************************/

/********  Hilbert ********/
void HilbertCoord(double x, double y,double x0, double y0, double xRed, double yRed, double xBlue, double yBlue, int d, int bits[]) /* OK COMPRIS*/
{
  for(int i = 0; i<d; i++) /* Profondeur  */
  {
      double coordRed  = (x-x0) * xRed  + (y-y0) * yRed;
      double coordBlue = (x-x0) * xBlue + (y-y0) * yBlue;
      xRed /=2; yRed /=2; 
      xBlue/=2; yBlue/=2;

      if (coordRed <= 0 && coordBlue <= 0)      /* Cadran 0 */
	{
	  x0 -= (xBlue+xRed);
	  y0 -= (yBlue+yRed);
	  swap(xRed,xBlue) ;
	  swap(yRed,yBlue) ;
	  bits[i] = 0;
	}
      else if (coordRed <= 0 && coordBlue >=0)  /* Cadran 1 */
	{
	  x0 += (xBlue - xRed);
	  y0 += (yBlue - yRed);
	  bits[i] = 1;
	}
      else if (coordRed >= 0 && coordBlue >= 0) /* Cadran 2 */
	{
	  x0 += (xBlue+xRed);
	  y0 += (yBlue+yRed);
	  bits[i] = 2;
	}
      else if(coordRed >= 0 && coordBlue <=0)   /* Cadran 3 */
	{
	  x0 +=(-xBlue+xRed);
	  y0 +=(-yBlue+yRed);
	  swap(xRed,xBlue);
	  swap(yRed,yBlue);
	  xBlue = -xBlue;
	  yBlue = -yBlue;
	  xRed = -xRed;
	  yRed = -yRed;
	  bits[i] = 3;
	}
  }
}
/********  SWAP Function ********/
void swap(double& v1, double& v2) /***/
{
	double temp = v1;
  	v1 = v2;
  	v2 = temp;
}
/********  Comparaison function********/
bool comp(Vertex* v1, Vertex* v2)
{
	for(int d = 0; d < nbits; d++)     // nbits connu car on inclut structures.h
  	{
  		if(v1->bits[d] < v2->bits[d])  // return true if a < b
  			return true;
        if(v1->bits[d] > v2->bits[d])  // return false if a > b
	  		return false;
	}
    return false;
}
/********  Super triangles********/
void SuperTriangle (vector<Vertex*> &Vertices, vector<Face*> &Triangles,double xmax,double xmin,double ymax,double ymin)
{
	unsigned n = Vertices.size();
  	/* Super triangle */
  	Vertex* P1 = new Vertex(xmin-0.5,ymin-0.5,0.6,n+1);    /* P2 **** P3 */
  	Vertex* P2 = new Vertex(xmin-0.5,ymax+0.5,0.6,n+2);	 /*    *       */
  	Vertex* P3 = new Vertex(xmax+0.5,ymax+0.5,0.6,n+3);    /*       *    */
  	Vertex* P4 = new Vertex(xmax+0.5,ymin-0.5,0.6,n+4);    /* P1 **** P4 */
  	/* Order calling of the points is of no importance */
  	Face *super1 = new Face(P1,P2,P4);
  	Face *super2 = new Face(P4,P2,P3);
  	/* We add the point in the same orientation of the Hilbert */
  	Vertices.push_back(P1);
  	Vertices.push_back(P2);
  	Vertices.push_back(P3);
  	Vertices.push_back(P4);

	super1->F[1] = super2;
  	super2->F[2] = super1;

  	Triangles.push_back(super1);
  	Triangles.push_back(super2);
}

/************************************************/
/** Triangulation + functions for Triangulation **/
/************************************************/
void delaunayTrgl(vector<Vertex*> &Vertices, vector<Face*> &Triangles)
{
	/* Ajoute progresseivement tous les points dans le maillage */
    for(int iP = 0; iP < 4; iP++) //AS: in the course : int iP=0 ; iP < S . size ( ) ; iP++
	{
	  /* Cherche un mauvais point qui contient le nouveau point*/
	  Face *f = lineSearch(Triangles[0], Vertices[iP]);

	  vector<Face*> cavity   ; /* Elements of the cavity */
	  vector<Edge>  bnd      ; /* Boundary of the Cavity */
	  vector<Face*> otherSide; /* Triangles attached to the Boundary */
	  printf("Adding the %d th point\n",iP);
	  /* delaunayCavity call himself in a recursively way */
	  delaunayCavity(f, Vertices[iP], cavity, bnd, otherSide);
	  //  printf("throw iP, bnd  = %i and cavity = %i ans other = %i \n",bnd.size(),cavity.size(),otherSide.size());
	  if(bnd.size()!=cavity.size() + 2) throw iP; //AS : without iP
	  // printf("throw iP 2 \n");

	  printf("delaunayCavity was done sucessfully!\n");

	  for (int i=0; i<cavity.size(); i++)
	  {
	  /* reuse memory slots of invalid elements */
	    cavity[i]->deleted = false;
	    cavity[i]->F[0] = cavity[i]->F[1] = cavity[i]->F[2] = NULL;
	    cavity[i]->V[0] = bnd[i].vmin; // As: In course = bnd[ i ] .V[ 0 ] ;
	    cavity[i]->V[1] = bnd[i].vmax; // AS : In course =bnd[ i ] .V[ 1 ] ;
	    cavity[i]->V[2] = Vertices[iP];
	  }

	  for (int i=0; i<otherSide.size(); i++) //AS : Not in the course
	  {
	  /* reuse memory slots of invalid elements */
	  	otherSide[i]->deleted = false;
	  }

	  /** Add the new triangles in the cavity **/
	  unsigned cSize = cavity.size();
	  for(int i=cSize; i<cSize+2; i++)
	  {
	  	Face *newf = new Face(bnd[i].vmin,bnd[i].vmax,Vertices[iP]);
	    Triangles.push_back(newf);
	    cavity.push_back(newf);
	  }

	  for(int i=0; i<otherSide.size(); i++)
	  {
	    if(otherSide[i]){cavity.push_back(otherSide[i]);}
	  }
	  computeAdjacencies(cavity);
	  printf("Finish to add the %d th point\n",iP);
	} /* Normally add all the points at the end */
}



Face* lineSearch(Face *f, Vertex *v) /* OK COMPRIS */
{
	/* f est le triangle de départ pour arriver au triangle final contenant le point*/
	while(1) /* Condition infinie donc sortie forcée par return ou break*/
  	{
  		if(f==NULL)
		return NULL; // we should NEVER return here

    	if(f->inCircle(v))
      	{
			return f; /* Retourne le triangle de départ*/
      	}

      	Vertex c = f->centroid(); /* Cree un nouveau vertex qui est le centroide du triangle dans lequel se trouve le point */
      	for(int iNeigh=0; iNeigh<3; iNeigh++) 
      	{
			Edge e = f->getEdge(iNeigh);

			if( orientationTest(&c    , v     , e.vmin) * orientationTest(&c    , v     , e.vmax) <0
	    	&&  orientationTest(e.vmin, e.vmax, &c    ) * orientationTest(e.vmin, e.vmax, v     ) <0)
	  		{	
			    f = f->F[iNeigh];
	    		break;
	  		}
	  	}
    printf("Bug in line lineSearch! :-(\n");
    return NULL;           // we should NEVER return here
    }
}


int orientationTest(Vertex *a,Vertex *b, Vertex *c) /* OK COMPRIS*/
{
	return robustPredicates::orient2d ((double*) a, (double*) b, (double*) c);
}


/** Fonction de selection des triangles faisant partie de la cavité (toujours convexe!) **/
void delaunayCavity(Face *f, Vertex *v, vector<Face*> &cavity, vector<Edge> &bnd, vector<Face*> &otherSide) /* OK COMPRIS*/
{
	printf("Hello Cavity\n");
	int i = 0;
  //printf("delaunayCavity, bnd  = %i and cavity = %i and other = %i \n",bnd.size(),cavity.size(),otherSide.size());
    if(f->deleted)
    {
    	printf("Already marked\n");
    	return;
    } /* Le triangle a déjà été marqué! */
    /* Cette condition ne peut être remplie que pour un appel récursif de la fonction comme c'est le cas tout à la fin!*/

    /* Ne retourne rien dans la fonction principale */
       // printf("if f-> deleted \n");
    //printf("after \n");
    f->deleted = true;     /* Mark the triangle to be deleted */
    cavity.push_back(f);

    //printf("delaunayCavity push_back, bnd  = %i and cavity = %i \n",bnd.size(),cavity.size());
    for(int iNeigh=0; iNeigh<3; iNeigh++)
    {
        if(f->F[iNeigh] == NULL) /* Si le triangle est nul, on est sur le bord */
        {
        	bnd.push_back(f->getEdge(iNeigh)); /* Ajoute le coté à la frontière */
	    // printf("delaunayCavity NULL bnd.push_back, bnd  = %i and cavity = %i \n",bnd.size(),cavity.size());
        }
        else if(!f->F[iNeigh]->inCircle(v)) /* Si le triangle voisin ne contient pas le point dans son périmètre alors... */
        {
            bnd.push_back(f->getEdge(iNeigh)); /* On prends le coté commun et on l'ajoute à la frontière */
	    // printf("delaunayCavity incircle bnd.push_back, bnd  = %i and cavity = %i \n",bnd.size(),cavity.size());
	    	if(!f->F[iNeigh]->deleted) /* De plus si le triangle voisin n'est pas marqué... */
			{
            	otherSide.push_back(f->F[iNeigh]); /* On l'ajoute au triangles externe à la frontière */
            	f->F[iNeigh]->deleted = true;      /* On marque aussi ces triangles car bien que correct on doit changer leur edges... par rapport à ceux des nouveaux triangles */
        	}
        }
        else delaunayCavity(f->F[iNeigh], v, cavity, bnd, otherSide);
    }
}

/* Algorithm connecting triangles in a caviyt */
void computeAdjacencies (std::vector<Face*> &cavity)
{
    std::map< Edge, std::pair<int,Face*> >edgeToFace;

    for(int iFace=0 ; iFace<cavity.size() ; iFace++)
    {
        for (int iEdge=0; iEdge < 3 ; iEdge ++)
        {
            Edge edge = cavity[iFace]->getEdge(iEdge);
            std::map < Edge, std::pair < int, Face* > >::iterator it = edgeToFace.find(edge);

	    	if(it == edgeToFace.end())
        	{/* edge has not yet been touched , so create an entry */
            	edgeToFace.insert(std::make_pair(edge,std::make_pair(iEdge, cavity[iFace])));
        	}
        	else
        	{ 	/* Connect the two neighboring triangles */
            	cavity[iFace]->F[iEdge]  = it->second.second;
            	it->second.second->F[it->second.first] = cavity[iFace];
            	/* Erase edge from the map */
            	edgeToFace.erase(it);
        	}
    	}
    }
}


/************************************************/
/** PRINTING FUNCTIONS FOR DELAUNAY STRUCTURES **/
/************************************************/

void printVertices(std::vector<Vertex*> &Vertices)
{
	unsigned n = Vertices.size();
	printf("HILBERT:\n");
	printf("X\tY\tValue\tBits\t(%u pts)\t (%u bits)\n",n,nbits);

	for (int i=0; i<n; i++)
  	{
        printf("%d : x = %f y = %f val = %f \n",i+1,Vertices[i]->x,Vertices[i]->y,Vertices[i]->val);
//      printf("%d : bits = [ %d %d %d ]    \n",i+1,Vertices[i]->bits[0], Vertices[i]->bits[1], Vertices[i]->bits[2]);
  	}
}
// void printTriangles(std::vector<Face*> &Triangles)
// {
// 	unsigned n = Triangles.size();
// 	printf("HILBERT:\n");
// 	printf("X\tY\tValue\tBits\t(%u pts)\t (%u bits)\n",n,nbits);

// 	for (int i=0; i<n; i++)
//   	{
//         printf("%d : x = %f y = %f val = %f \n",i+1,Triangles[i]->x,Triangles[i]->y,Triangles[i]->val);
// //      printf("%d : bits = [ %d %d %d ]    \n",i+1,Vertices[i]->bits[0], Vertices[i]->bits[1], Vertices[i]->bits[2]);
//   	}
// }

// int main(int argc, char *argv[]) //AS : Some stuff in main? TO do again
// {
//   // to mesure time execution
//   clock_t start, finish; 
// 	double duration;
// 	start = clock();
//   //printf("test\n");
//   FILE* fichierin = fopen(argv[1],"r");
//   //printf("test 2 \n");

//   std::vector<Vertex*> S;
//   std::vector<Face*> T;

//   struct Vertex *v0;

//   double a,b,c;
//   double xmin = 0.0; double xmax = 0.0;
//   double ymin = 0.0; double ymax = 0.0;
//   int ligne = 0;

//   // Initial Hilbert variables
//  int d = 50;
//  /* int bits[10];
//  for(int i = 0;i<10;i++)
//    {
//      bits[i] = 0;
//      }*/
//  double x0 = 0.0;  double y0 = 0.0;
//  double xRed = 0.0;  double xBlue = 0.0;
//  double yRed = 0.0;  double yBlue = 0.0;


 
//  while(1)
//    {
//      if (feof(fichierin))
//        {
// 	 break;
//        }
     
//      fscanf(fichierin,"%lf %lf %lf \n",&a,&b,&c);
//      // a += 1.e-4*(double) rand() / RAND_MAX;
//      // b += 1.e-4*(double) rand() / RAND_MAX;
//      // printf("%g %g %g\n",a,b,c);
//      int *bits = new int[d];
//      /*   for(int i = 0;i<d;i++)
//        {
// 	 bits[i] = 0;
// 	 }*/
//      struct Vertex *v0 = new Vertex (ligne+1,a,b,0.0,bits);
//      S.push_back(v0);
     
//      if (a>xmax)
//        {
// 	 xmax = a;
//        }
//      if (a<xmin)
//        {
// 	 xmin = a;
//        }
//      if (b>ymax)
//        {
// 	 ymax = b;
//        }
//      if (b<ymin)
//        {
// 	 ymin = b;
//        }     ligne++;
//    }
//  fclose(fichierin);

 

 
//  // Super triangle
//  int *bits1 = new int[d];
//  Vertex* ch1 = new Vertex(ligne + 1,xmin-0.1,ymin-0.1,0.0,bits1);
//  int *bits2 = new int[d];
//  Vertex* ch2 = new Vertex(ligne + 2,xmin-0.1,ymax+0.1,0.0,bits2);
//  int *bits3 = new int[d];
//  Vertex* ch3 = new Vertex(ligne + 3,xmax+0.1,ymax+0.1,0.0,bits3);
//  int *bits4 = new int[d];
//  Vertex* ch4 = new Vertex(ligne + 4,xmax+0.1,ymin-0.1,0.0,bits4);
//  Face *super1 = new Face(ch1,ch4,ch2);
//  Face *super2 = new Face(ch4,ch3,ch2);
//  S.push_back(ch1);
//  S.push_back(ch2);
//  S.push_back(ch3);
//  S.push_back(ch4);
 
//  super1->F[1] = super2;
//  super2->F[2] = super1;
 
//  T.push_back(super1);
//  T.push_back(super2);


//  x0   = (ch1->x+ch4->x)/2.0;     y0    = (ch1->y+ch2->y)/2.0;
//  xRed = (abs(ch1->x)+abs(ch4->x)) - x0;   xBlue = 0.0;
//  yRed = 0.0;   yBlue = (abs(ch1->y)+abs(ch2->y)) - y0;

// // to display the vector S
// /* for(int i = 0;i<S.size();i++)
//    {
//      printf("S %i : %i %i %i \n",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
//      //     printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
//      }
// */
//  // for loops to find Hilbert coordinate for every vertex
//  for(int i = 0; i < S.size();i++)
//    {
     
//      // printf("no hilbert \n");
//      //printf("S : %i %i \n ",S[i]->bits[0],S[i]->bits[1]);
//      HilbertCoord(S[i]->x,S[i]->y,x0,y0,xRed,yRed,xBlue,yBlue,d,S[i]->bits);
//      //printf("hilbert \n");
//      // printf("S %i : %i %i %i %i %i \n",i+1,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2],S[i]->bits[3],S[i]->bits[4]);
//      // printf("bits %i = %i %i %i %i \n",i,bits[0],bits[1],bits[2],bits[3]);
//    }

//  // to display the vector S
//  // printf("HILBERT : \n");
//  /*  for(int i = 0;i<S.size();i++)
//    {
//      printf("oz\n");
//      printf("S %i : %i %i %i \n",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
//      //    printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
//       }
//  */
//   // sort of vertex by comparing its hilbert coordinate
//  std::sort(S.begin()+4,S.end()-4,trie);
//  // printf("SORTED HILBERT : \n");

// // to display the shorted vector S 
// /*for(int i = 0;i<S.size();i++)
//    {
//      //   printf("oz 2 \n");
//      printf("S : %lf %lf \n ",S[i]->x,S[i]->y);
//      printf("S %i: %i %i %i \n ",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
//      //      printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
//       }
// */
// // printf("seg \n");

//  try{
//    delaunayTrgl(S,T,argv[2]);
//  }
//  catch (int i){
//    printf("failed after %d points %d triangles\n",i,(int)T.size());
//  }
 
//  // display time execution
//  finish = clock(); 
// 	duration = (double)(finish - start) / CLOCKS_PER_SEC; 
// 	printf( "%f seconds\n", duration );
//  return 0;
// }


