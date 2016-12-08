#include <stdlib.h>
#include <stdio.h>
#include "reader_writer.h"
#include "robustPredicates.h"
#include "structures.h"
#include


int main(int argc, char const *argv[])
{
// to mesure time execution
  clock_t start, finish; 
	double duration;
	start = clock();
  //printf("test\n");
  FILE* fichierin = fopen(argv[1],"r");
  //printf("test 2 \n");

  std::vector<Vertex*> S;
  std::vector<Face*> T;

  struct Vertex *v0;

  double a,b,c;
  double xmin = 0.0; double xmax = 0.0;
  double ymin = 0.0; double ymax = 0.0;
  int ligne = 0;

  // Initial Hilbert variables
 int d = 50;
 /* int bits[10];
 for(int i = 0;i<10;i++)
   {
     bits[i] = 0;
     }*/
 double x0 = 0.0;  double y0 = 0.0;
 double xRed = 0.0;  double xBlue = 0.0;
 double yRed = 0.0;  double yBlue = 0.0;


 
 while(1)
   {
     if (feof(fichierin))
       {
	 break;
       }
     
     fscanf(fichierin,"%lf %lf %lf \n",&a,&b,&c);
     // a += 1.e-4*(double) rand() / RAND_MAX;
     // b += 1.e-4*(double) rand() / RAND_MAX;
     // printf("%g %g %g\n",a,b,c);
     int *bits = new int[d];
     /*   for(int i = 0;i<d;i++)
       {
	 bits[i] = 0;
	 }*/
     struct Vertex *v0 = new Vertex (ligne+1,a,b,0.0,bits);
     S.push_back(v0);
     
     if (a>xmax)
       {
	 xmax = a;
       }
     if (a<xmin)
       {
	 xmin = a;
       }
     if (b>ymax)
       {
	 ymax = b;
       }
     if (b<ymin)
       {
	 ymin = b;
       }     ligne++;
   }
 fclose(fichierin);

 

 
 // Super triangle
 int *bits1 = new int[d];
 Vertex* ch1 = new Vertex(ligne + 1,xmin-0.1,ymin-0.1,0.0,bits1);
 int *bits2 = new int[d];
 Vertex* ch2 = new Vertex(ligne + 2,xmin-0.1,ymax+0.1,0.0,bits2);
 int *bits3 = new int[d];
 Vertex* ch3 = new Vertex(ligne + 3,xmax+0.1,ymax+0.1,0.0,bits3);
 int *bits4 = new int[d];
 Vertex* ch4 = new Vertex(ligne + 4,xmax+0.1,ymin-0.1,0.0,bits4);
 Face *super1 = new Face(ch1,ch4,ch2);
 Face *super2 = new Face(ch4,ch3,ch2);
 S.push_back(ch1);
 S.push_back(ch2);
 S.push_back(ch3);
 S.push_back(ch4);
 
 super1->F[1] = super2;
 super2->F[2] = super1;
 
 T.push_back(super1);
 T.push_back(super2);


 x0   = (ch1->x+ch4->x)/2.0;     y0    = (ch1->y+ch2->y)/2.0;
 xRed = (abs(ch1->x)+abs(ch4->x)) - x0;   xBlue = 0.0;
 yRed = 0.0;   yBlue = (abs(ch1->y)+abs(ch2->y)) - y0;

// to display the vector S
/* for(int i = 0;i<S.size();i++)
   {
     printf("S %i : %i %i %i \n",S[i]->num,S[i]->bits[0],S[i]->bits[1],S[i]->bits[2]);
     //     printf("%i %i %i %i %i \n",S[i]->bits[5],S[i]->bits[6],S[i]->bits[7],S[i]->bits[8],S[i]->bits[9]);
     }
*/
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






// int main(int argc, char const *argv[])
// {
	
// 	// Data[3*i],Data[3*i+1] will contain ith node (for all i such that 0<=i<n)
// 	double *Data;
// 	unsigned n = read_nodes_txt("In/Exemple2.in", &Data); // n positif via unsigned

// 	printf("X\tY\tValue\t(%u pts)\n", n); // \t = 4 espaces

// 	unsigned i;
// 	for (i=0; i<n; i++)
// 	{
// 		printf("%3.2f\t%3.2f\t%3.2f\n", Data[3*i], Data[3*i+1], Data[3*i+2]);
// 	}


//   	std::vector<Vertex*> S;
//   	struct Vertex *v0;




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
// 	printf("---------~~~~   THE END ~~~~~---------");

// 	free(Triangles);
// 	free(Segments);
// 	free(Data);
// 	write_gmsh_hilbert("Out/hilbert.out", Data, n, Segments, 1000);
// //	write_gmsh_hilbert("Out/hilbert.out", Data, n, Segments, n-1);

// 	return 0;
// }
