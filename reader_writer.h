#ifndef __READER_WRITER_H__
#define __READER_WRITER_H__
#include "structures.h"

/* Get nodes from a file
 *
 * @in filename: the name of the file
 * @out Data:    interlaced nodes data: X0,Y0,Value0,X1,Y1,Value1,...
 * @return:      the number of nodes
 */

// Je commente
unsigned read_nodes_txt(const char* filename, std::vector <Vertex*> &Data, double &xmin, double &xmax, double &ymin, double &ymax);


/* Write triangulation to file (either in txt or binary form)
 *
 * @in filename:  the name of the file
 * @in Data:      interlaced nodes data: X0,Y0,Value0,X1,Y1,Value1,...
 * @in dLength:   the number of nodes
 * @in Triangles: triangles node indices: T0_node0,T0_node1,T0_node2,T1_node0,T1_node1,T1_node2,
 * @in tLength:   the number of triangles
 * @in Segments:  edges node indices: E0_node0, E0_node1 etc 
 * @in sLength:   the number of segments in Hilbert sort
 */

// void write_gmsh_Delaunay ( std::vector<Vertex*> &S, std::vector<Face*> &T, char *name);
/* write_gmsh_Delaunay still need to be finished :-) */
void write_gmsh_Hilbert (const char* filename, std::vector <Vertex*> &Vertices, unsigned n);
void write_gmsh_Delaunay(const char* filename, std::vector <Vertex*> &Vertices, std::vector <Face*> &Triangles, unsigned n);

void write_gmsh_txt(const char* filename, double* Data, unsigned dLength, unsigned* Triangles, unsigned tLength);
void write_gmsh_bin(const char* filename, double* Data, unsigned dLength, unsigned* Triangles, unsigned tLength);


#endif