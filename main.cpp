#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <map>
#include <cmath>
#include "reader_writer.h"
#include "robustPredicates.h"
#include "structures.h"


<<<<<<< HEAD
int main(int argc, char const *argv[])
{
	double *Data;
 	
 	/** Filling Data structure (X,Y,Val) **/
 	unsigned n = read_nodes_txt("In/Exemple2.in", &Data); // n positif via unsigned
    /** Printing the data **/
 	printf("X\tY\tValue\t(%u pts)\n", n); // \t = 4 espaces

 	printf("AS0\n");

 	std::vector<Vertex*> S;  /* Vector of type Vertex from std library*/ 
  	std::vector<Face*> T;
  	struct Vertex *v0;       /* Pointeur of type Vertex */

	/* Initialisation des repères */

	/* Initial Hilbert Variable for the deep of the structure */
	int d = 3; 

  	double xmin(0.0),xmax(0.0),ymin(0.0),ymax(0.0);
  	unsigned ligne = 0;

  	double x0(0.0),y0(0.0), xRed(0.0),xBlue(0.0), yRed(0.0),yBlue(0.0);

  	for (int i = 0; i < n; ++i)
  	{
  		int *bits         = new int[d]; /* Variable Hiblert */
		struct Vertex *v0 = new Vertex (ligne+1,Data[3*i],Data[3*i+1],Data[3*i+2],bits);
     	S.push_back(v0);
     	if(Data[3*i]>xmax){xmax = Data[3*i];}
     	if(Data[3*i]<xmin){xmin = Data[3*i];}
     	if(Data[3*i+1]>ymax){ymax = Data[3*i+1];}
     	if(Data[3*i+1]<ymin){ymin = Data[3*i+1];}
     	ligne++;
  	}

  	/* Super triangle =>>> Ce ne serait pas un super RECTANGLE? */
  	/* Super Triangle divisé en 2??? */
 	int *bits1  = new int[d];
 	Vertex* P1 = new Vertex(ligne + 1,xmin-0.1,ymin-0.1,0.0,bits1);
 	int *bits2  = new int[d];
 	Vertex* P2 = new Vertex(ligne + 2,xmin-0.1,ymax+0.1,0.0,bits2);
 	int *bits3  = new int[d];
 	Vertex* P3 = new Vertex(ligne + 3,xmax+0.1,ymax+0.1,0.0,bits3);
 	int *bits4  = new int[d];
 	Vertex* P4 = new Vertex(ligne + 4,xmax+0.1,ymin-0.1,0.0,bits4);
 	
 	Face *super1 = new Face(P1,P4,P2);
 	Face *super2 = new Face(P4,P3,P2);
 	
 	/* Ajout des nouveaux points Pi formant le cadre */
 	S.push_back(P1);
 	S.push_back(P2);
 	S.push_back(P3);
 	S.push_back(P4);

 	super1->F[1] = super2;
 	super2->F[2] = super1;
 
 	T.push_back(super1);
 	T.push_back(super2);

 	/* Initialisation d'Hilbert avant l'appel de la fonction */

 	x0   = (P1->x + P4->x)/2.0;     
 	y0   = (P1->y + P2->y)/2.0;

 	xRed  = (std::abs(P1->x)+std::abs(P4->x)) - x0;
 	yRed  = 0.0;

 	yBlue = (std::abs(P1->y)+std::abs(P2->y)) - y0;
 	xBlue = 0.0;
 
 

/* To display the vector S */
 for(int i = 0;i<S.size();i++)
   {
     printf("S %i : %i %i %i \n",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
     //     printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
     }

 // for loops to find Hilbert coordinate for every vertex
 for(int i = 0; i < S.size();i++)
   {
     
     // printf("no hilbert \n");
     //printf("S : %i %i \n ",S[i]->bits[0],S[i]->bits[1]);
     HilbertCoord(S[i]->x,S[i]->y,x0,y0,xRed,yRed,xBlue,yBlue,d,S[i]->bits);
     //printf("hilbert \n");
     // printf("S %i : %i %i %i %i %i \n",i+1,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2],S[i]->bits[3],S[i]->bits[4]);
     // printf("bits %i = %i %i %i %i \n",i,bits[0],bits[1],bits[2],bits[3]);
   }

 // to display the vector S
 // printf("HILBERT : \n");
 /*  for(int i = 0;i<S.size();i++)
   {
     printf("oz\n");
     printf("S %i : %i %i %i \n",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
     //    printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
      }
 */
  // sort of vertex by comparing its hilbert coordinate
    std::sort(S.begin()+4,S.end()-4,trie);
    // 	write_gmsh_txt("Out/triangle.out", Data, n, Triangles, 2);
// 	write_gmsh_bin("Out/triangle.out", Data, n, Triangles, 2); // (quicker for large files)
    
 for(int i = 0;i<S.size();i++)
   {
     printf("S %i : %i %i %i \n",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
     //     printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
     }


    int i = 0;
    for (int v = 0; v < n; v++)
    {
    	Data[i]   = S[v]->x;
    	Data[i+1] = S[v]->y;
    	Data[i+2] = S[v]->z;
    	i+=3;
    }

 //   unsigned* Triangles = (unsigned*)malloc(6*n*sizeof(unsigned)); // n = nombre de points et 2n triangles donc
    unsigned* Segments = (unsigned*)malloc(6*n*sizeof(unsigned));

    /* Réaliser une grosse boucle for pour tous les triangles */
    Segments[0] = 0;
	Segments[1] = 1;

    for (int i = 2; i < 2*n-1; i+=2)
    {
     	Segments[i]   = Segments[i-1];
     	Segments[i+1] = Segments[i]+1;
    }
    // for (int i = 0; i < 2*n; ++i)
    // {
    // 	printf("%u\n", Segments[i]);
    // }
    printf("CACA0\n");
 	write_gmsh_hilbert("Out/hilbert.out", Data, n, Segments, n-1);
    printf("CACA11\n");

 	printf("---------~~~~   THE END ~~~~~---------");
 	/** NEVER WRITE SOMETHING AFTER THESE LINES!!! **/
 	//free(Triangles);
 	free(Segments);
 	free(Data);
 	return 0;

 // printf("SORTED HILBERT : \n");

// to display the shorted vector S 
/*for(int i = 0;i<S.size();i++)
   {
     //   printf("oz 2 \n");
     printf("S : %lf %lf \n ",S[i]->x,S[i]->y);
     printf("S %i: %i %i %i \n ",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
     //      printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
      }
*/
// printf("seg \n");


}
=======
// int main(int argc, char const *argv[])
// {
// 	printf("AS0\n");
// 	double *Data;
 	
//  	/** Filling Data structure (X,Y,Val) **/
//  	unsigned n = read_nodes_txt("In/Exemple0.in", &Data); // n positif via unsigned
//     /** Printing the data **/
//  	printf("X\tY\tValue\t(%u pts)\n", n); // \t = 4 espaces

//  	printf("AS0\n");

//  	std::vector<Vertex*> S;  /* Vector of type Vertex from std library*/ 
//   	std::vector<Face*> T;
//   	struct Vertex *v0;       /* Pointeur of type Vertex */

// 	/* Initialisation des repères */

// 	/* Initial Hilbert Variable for the deep of the structure */
// 	int d = 3; 

//   	double xmin(0.0),xmax(0.0),ymin(0.0),ymax(0.0);
//   	unsigned ligne = 0;

//   	double x0(0.0),y0(0.0), xRed(0.0),xBlue(0.0), yRed(0.0),yBlue(0.0);

//   	for (int i = 0; i < n; ++i)
//   	{
//   		int *bits         = new int[d]; /* Variable Hiblert */
// 		struct Vertex *v0 = new Vertex (ligne+1,Data[3*i],Data[3*i+1],Data[3*i+2],bits);
//      	S.push_back(v0);
//      	if(Data[3*i]>xmax){xmax = Data[3*i];}
//      	if(Data[3*i]<xmin){xmin = Data[3*i];}
//      	if(Data[3*i+1]>ymax){ymax = Data[3*i+1];}
//      	if(Data[3*i+1]<ymin){ymin = Data[3*i+1];}
//      	ligne++;
//   	}

//   	/* Super triangle =>>> Ce ne serait pas un super RECTANGLE? */
//   	/* Super Triangle divisé en 2??? */
//  	int *bits1  = new int[d];
//  	Vertex* P1 = new Vertex(ligne + 1,xmin-0.1,ymin-0.1,0.0,bits1);
//  	int *bits2  = new int[d];
//  	Vertex* P2 = new Vertex(ligne + 2,xmin-0.1,ymax+0.1,0.0,bits2);
//  	int *bits3  = new int[d];
//  	Vertex* P3 = new Vertex(ligne + 3,xmax+0.1,ymax+0.1,0.0,bits3);
//  	int *bits4  = new int[d];
//  	Vertex* P4 = new Vertex(ligne + 4,xmax+0.1,ymin-0.1,0.0,bits4);
 	
//  	Face *super1 = new Face(P1,P4,P2);
//  	Face *super2 = new Face(P4,P3,P2);
 	
//  	/* Ajout des nouveaux points Pi formant le cadre */
//  	S.push_back(P1);
//  	S.push_back(P2);
//  	S.push_back(P3);
//  	S.push_back(P4);

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
 
 

// /* To display the vector S */
//  for(int i = 0;i<S.size();i++)
//    {
//      printf("S %i : %i %i %i \n",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
//      //     printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
//      }

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
//     std::sort(S.begin()+4,S.end()-4,trie);
//     // 	write_gmsh_txt("Out/triangle.out", Data, n, Triangles, 2);
// // 	write_gmsh_bin("Out/triangle.out", Data, n, Triangles, 2); // (quicker for large files)
    
//     int i = 0;
//     for (int v = 0; v < n; v++)
//     {
//     	Data[i]   = S[v]->x;
//     	Data[i+1] = S[v]->y;
//     	Data[i+2] = S[v]->z;
//     	i+=3;
//     }

//  //   unsigned* Triangles = (unsigned*)malloc(6*n*sizeof(unsigned)); // n = nombre de points et 2n triangles donc
//     unsigned* Segments = (unsigned*)malloc(6*n*sizeof(unsigned));

//     /* Réaliser une grosse boucle for pour tous les triangles */
//     Segments[0] = 0;
// 	Segments[1] = 1;

//     for (int i = 2; i < 2*n-1; i+=2)
//     {
//      	Segments[i]   = Segments[i-1];
//      	Segments[i+1] = Segments[i]+1;
//     }
//     // for (int i = 0; i < 2*n; ++i)
//     // {
//     // 	printf("%u\n", Segments[i]);
//     // }
//     printf("CACA0\n");
//  	write_gmsh_hilbert("Out/hilbert.out", Data, n, Segments, n-1);
//     printf("CACA1\n");

//  	printf("---------~~~~   THE END ~~~~~---------");
//  	/** NEVER WRITE SOMETHING AFTER THESE LINES!!! **/
//  	//free(Triangles);
//  	free(Segments);
//  	free(Data);
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
>>>>>>> 5c4d4ea6e3834b04dff3e8fce9ffe28eee132780






/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/



// int main(int argc, char const *argv[])
// {
	
<<<<<<< HEAD
// 	// Data[3*i],Data[3*i+1] will contain ith node (for all i such that 0<=i<n)
// 	double *Data;
// 	/** Number of nodes and filling data structure **/
// 	unsigned n = read_nodes_txt("In/Exemple0.in", &Data); // n positif via unsigned
=======
	// Data[3*i],Data[3*i+1] will contain ith node (for all i such that 0<=i<n)
	double *Data;
	/** Number of nodes and filling data structure **/
	unsigned n = read_nodes_txt("In/Exemple0.in", &Data); // n positif via unsigned
>>>>>>> 5c4d4ea6e3834b04dff3e8fce9ffe28eee132780

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
