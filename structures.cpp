#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector> // for std::vector
#include <map> // for std::map
#include <cmath>
#include <iostream>
using namespace std; // std::vector -> vector



// compare function to class vertex 
bool trie(Vertex* a, Vertex* b) // AS : Not int the course
{
  // printf("bits = %i \n",a->bits[0]);
  for(int i = 0; i < sizeof(a->bits) ;i++)
     {
       if(a->bits[i] < b->bits[i]) // return true if a < b
	{
	  return true;
	}
         if(a->bits[i] > b->bits[i]) // return false if a > b
	{
	  return false;
	}
	
	}
  return false; // if a == b
  
}
// swap
void swap(double& a, double& b) // AS: not in the course
{
  double temp = a;
  a = b;
  b = temp;
}

// hilbert coordinate for a vertex AS: In the course
void HilbertCoord(double x, double y,double x0, double y0, double xRed, double yRed, double xBlue, double yBlue, int d, int bits[])
{
  //free(bits);
  //bits = new int[10];
  for(int i = 0; i<d; i++)
    {
      double coordRed = (x-x0)* xRed + (y-y0) * yRed;
      double coordBlue = (x-x0) * xBlue + (y-y0) * yBlue;
      xRed/=2; yRed/=2; xBlue/=2; yBlue/=2;

      if (coordRed <= 0 && coordBlue <= 0) // quadrant 0
	{
	  x0 -= (xBlue+xRed); y0 -= (yBlue+yRed);
	  swap(xRed,xBlue) ; swap(yRed,yBlue) ;
	  bits[i] = 0;
	}
      else if (coordRed <= 0 && coordBlue >=0) // quadrant 1
	{
	  x0 += (xBlue-xRed); y0 += (yBlue+yRed);
	  bits[i] = 1;
	}
      else if (coordRed >= 0 && coordBlue >= 0) // quadrant 2
	{
	  x0 += (xBlue+xRed); y0 += (yBlue+yRed);
	  bits[i] = 2;
	}
      else if(coordRed >= 0 && coordBlue <=0) // quadrant 3
	{
	  x0 +=(-xBlue+xRed); y0 += (-yBlue+yRed);
	  swap(xRed,xBlue); swap(yRed,yBlue);
	  xBlue = -xBlue; yBlue = -yBlue;
	  xRed = -xRed; yRed = -yRed;
	  bits[i] = 3;
	}
    }
}


int orientationTest(Vertex *a,Vertex *b, Vertex *c) //AS:give in robustPredicate
{	
	// formula in syllabus p.25
  // non-robust
    double a11 = (a->x)-(c->x) ;
    double a12 = (a->y)-(c->y);
    double a21 = (b->x)-(c->x);
    double a22 = (b->y)-(c->y);
    double sign = (a11*a22)-(a21*a12);

	if (sign > 0.0) 
	{
	  // printf("1 \n");
	 return 1;
	}
	else if (sign < 0.0)
	{
	  //printf("-1 \n");
	 return -1;
	}
		else
	{
	  //printf("0 \n");
	 return 0;
	 }
}

void computeAdjacencies (std::vector<Face*> &cavity) //AS: in the course
{
    std::map<Edge, std::pair<int , Face* > >edgeToFace;

    for(int iFace=0 ; iFace<cavity.size() ; iFace++)
    {
        for (int iEdge=0; iEdge < 3 ; iEdge ++)
        {
            Edge edge = cavity[iFace]->getEdge(iEdge);

	    std::map < Edge, std::pair < int, Face* > >::iterator it = edgeToFace.find(edge);

	    if(it == edgeToFace.end())
            {// edge has not yet been touched , so create an entry
                edgeToFace.insert(std::make_pair (edge,std::make_pair(iEdge, cavity[iFace])));
            }
            else
            { // Connect the two neighboring triangles
                cavity[iFace]->F[iEdge]  = it->second.second;
                it->second.second->F[it->second.first] = cavity[iFace];
                // Erase edge from the map
                edgeToFace.erase(it);
            }
        }
    }
}

void delaunayCavity(Face *f, Vertex *v, std::vector<Face*> &cavity, std::vector<Edge> &bnd, std::vector<Face*> &otherSide) //AS: In the course without the lines commented
{
  //printf("delaunayCavity, bnd  = %i and cavity = %i and other = %i \n",bnd.size(),cavity.size(),otherSide.size());
    if(f->deleted)
     {
       // printf("if f-> deleted \n");
     	return;
     }
    //printf("after \n");
    f->deleted = true; // Mark the triangle
    cavity.push_back(f);
    //printf("delaunayCavity push_back, bnd  = %i and cavity = %i \n",bnd.size(),cavity.size());
    for(int iNeigh=0; iNeigh<3; iNeigh++)
    {
        if(f->F[iNeigh] == NULL)
	{
            bnd.push_back(f->getEdge(iNeigh));
	    // printf("delaunayCavity NULL bnd.push_back, bnd  = %i and cavity = %i \n",bnd.size(),cavity.size());
        }
        else if(!f->F[iNeigh]->inCircle(v))
        {
            bnd.push_back(f->getEdge(iNeigh));
	    // printf("delaunayCavity incircle bnd.push_back, bnd  = %i and cavity = %i \n",bnd.size(),cavity.size());

	    if(!f->F[iNeigh]->deleted)
		{
                	otherSide.push_back(f->F[iNeigh]);  
                	f->F[iNeigh]->deleted = true;       
            	}
        }
        else delaunayCavity(f->F[iNeigh], v, cavity, bnd, otherSide);
    }
}

Face* lineSearch(Face *f, Vertex *v){ //AS: In the course without the commented line
  // printf("Sommet (%lf,%lf,%lf)\n",v[0].x,v[0].y,v[0].z);

  while(1) {
    // printf("Oz \n");
      if(f==NULL){
	//	printf("return 1 \n");
	return NULL; // we should NEVER return here
      }
      
      if(f->inCircle(v)){
	//	printf("incircle\n");
	return f;    
      }
      Vertex c = f->centroid();  
      
      for(int iNeigh=0; iNeigh<3; iNeigh++) {	
	Edge e = f->getEdge(iNeigh);
	//	printf("ori \n");
	if( orientationTest (&c, v, e.vmin) *
	    orientationTest (&c, v, e.vmax) <0
	    &&
	    orientationTest (e.vmin, e.vmax, &c) *
	    orientationTest (e.vmin, e.vmax,  v) <0)
	  {
	    //printf("if \n");
	    f = f->F[iNeigh];   		
	    break;              
	  }
	//	printf("break\n");
      }
      // printf("NEVER \n");
      // return NULL; // we should NEVER return here
    }
}


void P ( std::vector<Vertex*> &S, std::vector<Face*> &T, char *name) //AS : reader_writer
{
  FILE* fichierout = fopen(name,"w");
// ecriture dans le fichier
 fprintf(fichierout,"$MeshFormat \n");
 fprintf(fichierout,"2.2 0 8 \n");
 fprintf(fichierout,"$EndMeshFormat \n");
 fprintf(fichierout,"$Nodes\n");
 fprintf(fichierout,"%i\n",(int)S.size());
 
 int node,node2,node3;
 
 for(int i = 0; i<S.size() ;i++)
   {
     fprintf(fichierout,"%i %lf %lf %lf \n",S[i]->num,S[i]->x,S[i]->y,S[i]->z);
   }
 fprintf(fichierout, "$EndNodes\n");
 fprintf(fichierout,"$Elements\n");
 fprintf(fichierout,"%i \n",(int)T.size());
 
 for(int i = 0; i<T.size();i++)
   {
     fprintf(fichierout,"%i %i %i %i %i %i %i\n",i+1,2,1,99,T[i]->V[0]->num,T[i]->V[1]->num,T[i]->V[2]->num);     
   }
 fprintf(fichierout,"$EndElements\n");
 
 fclose(fichierout);
}
//AS : !!!! different
void delaunayTrgl(std::vector<Vertex*> &S, std::vector<Face*> &T,char *name)
{    
    for(int iP=4; iP<S.size()-3; iP++) //AS: in the course : int iP=0 ; iP < S . size ( ) ; iP++
	{
	  // Pour ecrire dans le fichier
	  //char name[256];
	  //sprintf(name,"pt%d.geo",0);
	  P(S,T,name); //AS : not in the course
	  Face *f = lineSearch(T[0], S[iP]); //not in the course

	  /*  if (!f) {
	    continue;
	    }*/
	   
	
	  std::vector<Face*> cavity   ; 
	  std::vector<Edge> bnd       ; 
	  std::vector<Face*> otherSide; 

	  delaunayCavity(f, S[iP], cavity, bnd, otherSide);
	  //  printf("throw iP, bnd  = %i and cavity = %i ans other = %i \n",bnd.size(),cavity.size(),otherSide.size());
	  if(bnd.size() != cavity.size() + 2) throw iP; //AS : without IPP
	  // printf("throw iP 2 \n");
	  for (int i=0; i<cavity.size(); i++)
	    {
	      // reuse memory slots of invalid elements
	      cavity[i]->deleted = false;
	      cavity[i]->F[0] = cavity[i]->F[1] = cavity[i]->F[2] = NULL;
	      cavity[i]->V[0] = bnd[i].vmin; // As: In course = bnd[ i ] .V[ 0 ] ;
	      cavity[i]->V[1] = bnd[i].vmax; // AS : In course =bnd[ i ] .V[ 1 ] ;
	      cavity[i]->V[2] = S[iP];
	    }

	  //
	    for (int i=0; i<otherSide.size(); i++) //AS : Not in the course
	      {
		otherSide[i]->deleted = false; 
	      }
	 
	  unsigned int cSize = cavity.size();

	  for(int i=cSize; i<cSize+2; i++)
	    {
	      Face *newf = new Face(bnd[i].vmin,bnd[i].vmax,S[iP]);
	      T.push_back(newf);
	      cavity.push_back(newf);
	    }

	  for(int i=0; i<otherSide.size(); i++)
	    {
	      if(otherSide[i])
		{
		  cavity.push_back(otherSide[i]);
		}
	    }
	  computeAdjacencies(cavity);
	}
}




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


