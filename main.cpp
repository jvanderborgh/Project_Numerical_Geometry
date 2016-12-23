#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream> /* Important pour pouvoir utiliser std::sort! */
#include <vector>
#include <map>
#include <cmath>
#include "reader_writer.h"
//#include "structures.h"
#include "robustPredicates.h"

// int main(int argc, char const *argv[])
// {
// 	double *Data, *Square;
 	
//  	/** Filling Data structure (X,Y,Val) **/
//  	unsigned n = read_nodes_txt("In/Exemple3.in", &Data); // n positif via unsigned
//   unsigned nSquare = read_nodes_txt("In/Exemple3.in", &Square); // n positif via unsigned

//     /** Printing the data **/
//  	/* printf("X\tY\tValue\t(%u pts)\n", n); // \t = 4 espaces */


//  	std::vector<Vertex*> S;  /* Vector of type Vertex from std library*/ 
//   std::vector<Face*> T;
//   struct Vertex *v0;       /* Pointeur of type Vertex */

// 	/* Initialisation des repères */

// 	/* Initial Hilbert Variable for the deep of the structure */
// 	int d(8); // Au dessus de d=8, les résultats ne changent plus :-)

//   double  xmin(0.0),xmax(0.0),
//           ymin(0.0),ymax(0.0);

//   double  x0(0.0)  ,  y0(0.0) , 
//           xRed(0.0),xBlue(0.0), 
//           yRed(0.0),yBlue(0.0);

//   unsigned ligne = 0;
//   for (int i = 0; i < n; ++i)
//   {
//   	int *bits         = new int[d]; /* Variable Hiblert */
// 	  struct Vertex *v0 = new Vertex(ligne+1,Data[3*i],Data[3*i+1],Data[3*i+2],bits);
//     S.push_back(v0);
//     /* Compute the extremen values of the R-box */
//     if(Data[3*i]>xmax){xmax = Data[3*i];}
//     if(Data[3*i]<xmin){xmin = Data[3*i];}
//     if(Data[3*i+1]>ymax){ymax = Data[3*i+1];}
//     if(Data[3*i+1]<ymin){ymin = Data[3*i+1];}
//     ligne++;
//   }
//   printf("xdist: %f ; ydist: %f\n",std::abs(xmax-xmin),std::abs(ymax-ymin));

//   printf("xmin: %f ; ymin: %f\n",xmin,ymin);
//   printf("xmax: %f ; ymax: %f\n",xmax,ymax);
  
//   square(xmin,xmax,ymin,ymax);

//   printf("xmin: %f ; ymin: %f\n",xmin,ymin);
//   printf("xmax: %f ; ymax: %f\n",xmax,ymax);
//   printf("xdist: %f ; ydist: %f\n",std::abs(xmax-xmin),std::abs(ymax-ymin));

//   /* Create the two fisrt super triangles of the mesh */
//  	int *bits1  = new int[d];
//  	Vertex* P1  = new Vertex(ligne + 1,xmin-0.1,ymin-0.1,1.0,bits1);
//  	int *bits2  = new int[d];
//  	Vertex* P2  = new Vertex(ligne + 2,xmin-0.1,ymax+0.1,1.0,bits2);
//  	int *bits3  = new int[d];
//  	Vertex* P3  = new Vertex(ligne + 3,xmax+0.1,ymax+0.1,1.0,bits3);
//  	int *bits4  = new int[d];
//  	Vertex* P4  = new Vertex(ligne + 4,xmax+0.1,ymin-0.1,1.0,bits4);
 	
//  	Face *super1 = new Face(P1,P4,P2);
//  	Face *super2 = new Face(P4,P3,P2);
 	
//  	/* Ajout des nouveaux points formant le cadre */
//  	S.push_back(P1);
//  	S.push_back(P2);
//  	S.push_back(P3);
//  	S.push_back(P4);



// /***********************TEST SQUARE **********************************/

//   //   int s = 0;
//   //   for (int v = 0; v < S.size(); v++)
//   //   {
//   //     Data[s]   = S[v]->x;
//   //     Data[s+1] = S[v]->y;
//   //     Data[s+2] = S[v]->z;
//   //     printf("V%d: x=%f; y=%f\n",v+1,Data[s],Data[s+1]);
//   //     s+=3;
//   //   }

//   //   unsigned* Triangles = (unsigned*)malloc(6*n*sizeof(unsigned)); // n = nombre de points et 2n triangles donc
//   //   unsigned* Segments_Square = (unsigned*)malloc(6*n*sizeof(unsigned));

//   //    Réaliser une grosse boucle for pour tous les triangles 
//   // Segments_Square[0] = 0;
//   // Segments_Square[1] = 1;

//   //   for (int i = 2; i < (2*S.size()-1); i+=2)
//   //   {
//   //     Segments_Square[i]   = Segments_Square[i-1];
//   //     Segments_Square[i+1] = Segments_Square[i]+1;
//   //   }
//   //   for (int i = 0; i < 2*S.size(); ++i)
//   //   {
//   //     printf("%u\n", Segments_Square[i]);
//   //   }
//   // write_gmsh_hilbert("Out/Square.out", Data, n, Segments_Square, 3);


// /***********************TEST SQUARE **********************************/













//  	super1->F[1] = super2;
//  	super2->F[2] = super1;
 
//  	T.push_back(super1);
//  	T.push_back(super2);

//  	/* Initialisation d'Hilbert avant l'appel de la fonction */

//  	x0   = (P1->x + P4->x)/2.0;     
//  	y0   = (P1->y + P2->y)/2.0;

 

//  	xRed  = (std::abs(P1->x)+std::abs(P4->x)) - x0;
//  	yRed  = 0.0;

//  	yBlue = (std::abs(P1->y)+std::abs(P2->y)) - y0;
//  	xBlue = 0.0;
 
 

//   /* To display the vector S */
//   //printHilbert(S,d);
  
//   /******************************************************************/
//   /******** Filling Hilbert bits coordinates for each vertex ********/
//   /******************************************************************/
//   for(int i = 0; i < S.size();i++)
//     HilbertCoord(S[i]->x,S[i]->y,x0,y0,xRed,yRed,xBlue,yBlue,d,S[i]->bits);
 
//   // sort of vertex by comparing its hilbert coordinate
// //  std::sort(S.begin()+4,S.end()-4,trie);
//   S.pop_back();
//   S.pop_back();
//   S.pop_back();
//   S.pop_back();
//   std::sort(S.begin(),S.end(),trie);

//   //printHilbert(S,d);

//   /****************************************************************/
//   /******************** DELAUNAY TRIANGULATION ********************/
//   /****************************************************************/


// // 	write_gmsh_txt("Out/triangle.out", Data, n, Triangles, 2);
// // 	write_gmsh_bin("Out/triangle.out", Data, n, Triangles, 2); // (quicker for large files)
//     double *hilbertData = (double*) malloc(5*n*sizeof(double)); 

//     int i = 0;
//     for (int v = 0; v < S.size(); v++)
//     {
//     	hilbertData[i]   = S[v]->x;
//     	hilbertData[i+1] = S[v]->y;
//     	hilbertData[i+2] = S[v]->z;
//     	i+=3;
//     }

//     unsigned* Triangles = (unsigned*)malloc(6*n*sizeof(unsigned)); // n = nombre de points et 2n triangles donc
//     unsigned* Segments  = (unsigned*)malloc(2*n*sizeof(unsigned));

//     /* Réaliser une grosse boucle for pour tous les triangles */
//   Segments[0] = 0;
// 	Segments[1] = 1;

//     for (int i = 2; i < 2*S.size(); i+=2)
//     {
//      	Segments[i]   = Segments[i-1];
//      	Segments[i+1] = Segments[i]+1;
//     }
//    // int INDEX = 0;
//     // for (int i = 0; i < 2*n; ++i)
//     // {
//     //   printf("%u\n", Segments[i]);
//     //   INDEX++;
//     // }
//   //printf("%d\n",INDEX );
//   // BUG DECELE
//   delaunayTrgl(S,T);//,argv[2]);


// //  write_gmsh_hilbert("Out/hilbert.out", Data, n, Segments, 2*S.size());
//   printf("Number of vertex %lu\n", S.size()); 
//   write_gmsh_hilbert("Out/hilbert.out", hilbertData, n, Segments, S.size()-1);
//   /* QUESTION => n peut-être = n+4
//               => 2*S.size => S.Size()
//   */
//   //write_gmsh_hilbert("Out/hilbert.out", Data, n, Segments, n);

//   write_gmsh_txt("Out/triangle.out", Data, n, Triangles, T.size());

//  	printf("---------~~~~   THE END ~~~~~---------");
//  	/** NEVER WRITE SOMETHING AFTER THESE LINES!!! **/
//  	free(Triangles);
//  	free(Segments);
//  	free(Data);
//   free(hilbertData);
//   free(Square);
//  	return 0;

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


// }

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/



// int main(int argc, char const *argv[])
// {
	
// 	// Data[3*i],Data[3*i+1] will contain ith node (for all i such that 0<=i<n)
// 	double *Data;
// 	/** Number of nodes and filling data structure **/
// 	unsigned n = read_nodes_txt("In/Exemple0.in", &Data); // n positif via unsigned
	// Data[3*i],Data[3*i+1] will contain ith node (for all i such that 0<=i<n)
//	double *Data;
	/** Number of nodes and filling data structure **/
//	unsigned n = read_nodes_txt("In/Exemple0.in", &Data); // n positif via unsigned

// 	printf("X\tY\tValue\t(%u pts)\n", n); // \t = 4 espaces

// 	unsigned i;
// 	for (i=0; i<n; i++)
// 	{
// 		printf("%3.2f\t%3.2f\t%3.2f\n", Data[3*i], Data[3*i+1], Data[3*i+2]);
// 	}


// //DATA CONTIENT X Y VAL est fixe
// 	// Triangles[3*i],[3*i+1],[3*i+2] indices will contain ith triangle
// 	unsigned* Triangles = (unsigned*)malloc(6*n*sizeof(unsigned)); // n = nombre de points et 2n triangles donc
// // TIRANGLES CONTIENT LES INDICES POUR LE TABLEAU DE DATA varie
// 	unsigned* Segments = (unsigned*)malloc(6*n*sizeof(unsigned));
    

// 	/* These are just 2 dummy triangles, 
// 	 * you should normally find them with your triangulation
// 	 */
// 	/*for (int i = 0; i < 2000; ++i)
// 	{
// 			Triangles[] = 
// 	}*/
// 	// first triangle
// 	Triangles[0] = 0;
// 	Triangles[1] = 1;
// 	Triangles[2] = 3;

// 	// second triangle
// 	Triangles[3] = 1;
// 	Triangles[4] = 2;
// 	Triangles[5] = 3;
    
//     // Réaliser une grosse boucle for pour tous les triangles
//     Segments[0] = 0;
// 	Segments[1] = 1;

// 	// Segments[2] = 1;
// 	// Segments[3] = 2;

// 	// Segments[4] = 3;
// 	// Segments[5] = 4;

// 	// Segments[6] = 4;
// 	// Segments[7] = 5;

//     for (int i = 2; i < 2*n-1; i+=2)
//     {
//      	Segments[i]   = Segments[i-1];
//      	Segments[i+1] = Segments[i]+1;
//     }
//     // for (int i = 0; i < 2*n; ++i)
//     // {
//     // 	printf("%u\n", Segments[i]);
//     // }
	
// 	write_gmsh_txt("Out/triangle.out", Data, n, Triangles, 2);
// 	write_gmsh_bin("Out/triangle.out", Data, n, Triangles, 2); // (quicker for large files)
// 	write_gmsh_hilbert("Out/hilbert.out", Data, n, Segments, n-1);

// 	printf("---------~~~~   THE END ~~~~~---------");
// 	/** NEVER WRITE SOMETHING AFTER THESE LINES!!! **/
// 	free(Triangles);
// 	free(Segments);
// 	free(Data);

// 	return 0;
// }

/***************************************************/
/***************************************************/
/******* HILBERT FROM CODE ALEX AND QUENT **********/
/***************************************************/
/***************************************************/
// 
int main(int argc, char const *argv[])
{
  vector <Vertex*> Vertices ;
  vector <Face*>   Triangles;
//  vector <Vertex*> SuperVertices;

  // Data*  Datas;
  double xmax(0),ymax(0),xmin(0),ymin(0);
  unsigned n = read_nodes_txt("In/Exemple3.in",Vertices, xmin, xmax, ymin, ymax);

  /****** Begin HILBERT *******/
  for(int i=0; i<n; i++)
    HilbertCoord(Vertices[i]->x,Vertices[i]->y,0,0,xmax+0.5,0,0,ymax+0.5, nbits,Vertices[i]->bits);
    std::sort(Vertices.begin(),Vertices.end(),comp);
  for(int i=0; i<n; ++i)
    Vertices[i]->num = i;
  /******* End HILBERT ********/


  SuperTriangle(Vertices,Triangles,xmax,xmin,ymax,ymin);
//  SuperTriangle(SuperVertices,Triangles,xmax,xmin,ymax,ymin);
  // Faire accéder à num pour SuperVertices



 printVertices(Vertices);
//  printf("CACAPROUT0\n");
//  SuperTriangle(Vertices,Triangles,xmax,xmin,ymax,ymin);
//  write_gmsh_Delaunay("Out/Triangle.out",Vertices, Triangles, n);
//  printf("CACAPROUT1\n");
 // delaunayTrgl(Vertices,Triangles);
 // printf("CACAPROUT2\n");

  //write_gmsh_Delaunay("Out/Triangle.out",SuperVertices, Triangles, n);




  write_gmsh_Hilbert("Out/Hilbert.out",Vertices, n+4); /* +4 pour les super triangles!!! */

  printf("~~~~----------------------~~~~   THE END ~~~~~----------------------~~~~");
  return 0;
}



//printf("Point 9 : x = %f y = %f val = %f \n",data[8].x,data[8].y,data[8].val);

//   // Triangles[3*i],[3*i+1],[3*i+2] will contain ith triangle
// //  unsigned* Triangles = malloc(6*n*sizeof(unsigned));
//   /* These are just 2 dummy triangles,
//    * you should normally find them with your triangulation
//    */
//   // first triangle
// //  Triangles[0] = 0;
// //  Triangles[1] = 1;
// //  Triangles[2] = 2;

//   // second triangle
// //  Triangles[3] = 1;
// //  Triangles[4] = 2;
// //  Triangles[5] = 3;

//   //write_gmsh_txt("Out/triangle.out", Data, n, Triangles, 1);
//   //write_gmsh_bin("Out/triangle.out", Data, n, Triangles, 2); // (quicker for large files)


