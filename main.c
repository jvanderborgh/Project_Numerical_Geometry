#include <stdlib.h>
#include <stdio.h>
#include "reader_writer.h"


int main(int argc, char const *argv[])
{
	// Data[3*i],Data[3*i+1] will contain ith node (for all i such that 0<=i<n)
	double *Data;
	unsigned n = read_nodes_txt("In/Exemple0.in", &Data);

	printf("X\tY\tValue\t(%u pts)\n", n);

	unsigned i;
	for (i=0; i<n; i++)
		printf("%3.2f\t%3.2f\t%3.2f\n", Data[3*i], Data[3*i+1], Data[3*i+2]);


	// Triangles[3*i],[3*i+1],[3*i+2] will contain ith triangle
	unsigned* Triangles = malloc(6*n*sizeof(unsigned));


	/* These are just 2 dummy triangles, 
	 * you should normally find them with your triangulation
	 */
	// first triangle
	Triangles[0] = 0;
	Triangles[1] = 1;
	Triangles[2] = 3;

	// second triangle
	Triangles[3] = 1;
	Triangles[4] = 2;
	Triangles[5] = 3;

	write_gmsh_txt("Out/triangle.out", Data, n, Triangles, 2);
	// write_gmsh_bin("Out/triangle.out", Data, n, Triangles, 2); // (quicker for large files)

	free(Triangles);
	free(Data);

	return 0;
}