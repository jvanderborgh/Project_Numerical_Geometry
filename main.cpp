#include <stdlib.h>
#include <stdio.h>
#include "delaunay.h"
#include "reader_writer.h"


int main(int argc, char const *argv[])
{
	// Data[3*i],Data[3*i+1] will contain ith node (for all i such that 0<=i<n)
	double *Data;
	std::vector<Point> Points(n);

	unsigned n = read_nodes_txt("In/Exemple0.in", &Data); // n positif via unsigned

	for (int i = 0 ; i < n; ++i)
	{
		Points[i] = new Point(Data[3*i], Data[3*i+1], Data[3*i+2]);
	}
	printf("X\tY\tValue\t(%u pts)\n", n); // \t = 4 espaces

	unsigned i;
	for (i=0; i<n; i++)
	{
		printf("%3.2f\t%3.2f\t%3.2f\n", Data[3*i], Data[3*i+1], Data[3*i+2]);
		printf("%3.2f\t%3.2f\t%3.2f\n", Points[i].x, Points[i].y, Points[i].z);
	}

//DATA CONTIENT X Y VAL est fixe
	// Triangles[3*i],[3*i+1],[3*i+2] indices will contain ith triangle
	unsigned* Triangles = malloc(6*n*sizeof(unsigned)); // n = nombre de points et 2n triangles donc
// TIRANGLES CONTIENT LES INDICES POUR LE TABLEAU DE DATA varie
//	unsigned* Segments = malloc(6*n*sizeof(unsigned));
    

	/* These are just 2 dummy triangles, 
	 * you should normally find them with your triangulation
	 */
	/*for (int i = 0; i < 2000; ++i)
	{
			Triangles[] = 
	}*/
	// first triangle
	Triangles[0] = 0;
	Triangles[1] = 1;
	Triangles[2] = 3;

	// second triangle
	Triangles[3] = 1;
	Triangles[4] = 2;
	Triangles[5] = 3;
    
    // Réaliser une grosse boucle for pour tous les triangles
    for (int i = 0; i < 6*n; ++i)
    {
    	for (int i = 0; i < count; ++i)
    	{
    		Segments[i] = i
    	}
    }
	Segments[0] = 0;
	Segments[1] = 1;
	//
	Segments[2] = 1;
	Segments[3] = 2;
	printf("Caca\n");

	write_gmsh_hilbert("Out/hilbert.out", Data, n, Segments, 2);
	//write_gmsh_txt("Out/triangle.out", Data, n, Triangles, 2);
	// write_gmsh_bin("Out/triangle.out", Data, n, Triangles, 2); // (quicker for large files)
	printf("Caca");

	free(Triangles);
	//free(Segments);
	free(Data);
	free(Points);
	return 0;
}
