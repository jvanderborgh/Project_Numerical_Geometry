#ifndef READER_WRITER_H
#define READER_WRITER_H
#include "structures.h"

using namespace std;

void read_nodes_txt(vector<Vertex*> &S, vector<Face*> &T, const char* filename, double &xmin, double &ymin, double &zmin, double &xmax, double &ymax, double &zmax, int verbose);
void write_gmsh_txt(vector<Vertex*> &S, vector<Face*> &T, vector<Vertex*> &D, const char* filename, int verbose);

void write_gmsh_Hilbert(const char* filename, vector <Vertex*> &V);

#endif // READER_WRITER_H
/****************************************** ABOUT VERBOSE MODE ****************************************************/
/* https://www.quora.com/What-is-the-meaning-of-the-word-verbose-in-computer-science-as-well-as-in-native-English */
/******************************************************************************************************************/