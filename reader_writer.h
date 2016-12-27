#ifndef READER_WRITER_H
#define READER_WRITER_H
#include "structures.h"
void read_nodes_txt(std::vector<Vertex*> &S, std::vector<Face*> &T, const char* filename, double &xmin, double &ymin, double &zmin, double &xmax, double &ymax, double &zmax, int verbose);
void write_gmsh_txt(std::vector<Vertex*> &S, std::vector<Face*> &T, std::vector<Vertex*> &D, const char* filename, int verbose);

void write_gmsh_Hilbert(const char* filename, std::vector <Vertex*> &V);

bool vCompare(Vertex* v1, Vertex* v2);
#endif // READER_WRITER_H
/****************************************** ABOUT VERBOSE MODE ****************************************************/
/* https://www.quora.com/What-is-the-meaning-of-the-word-verbose-in-computer-science-as-well-as-in-native-English */
/******************************************************************************************************************/