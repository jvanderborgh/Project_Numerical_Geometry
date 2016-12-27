#ifndef READER_WRITER_H
#define READER_WRITER_H
void file_read( std::vector<Vertex*> &S, std::vector<Face*> &T, std::vector<Vertex*> &D, const char* filename, double* x0, double* y0, double* xRed, double* yRed, double* xBlue, double* yBlue, int verbose);
void file_write(std::vector<Vertex*> &S, std::vector<Face*> &T, std::vector<Vertex*> &D, const char* filename, int verbose);
bool vCompare(Vertex* v1, Vertex* v2);
#endif // READER_WRITER_H
/****************************************** ABOUT VERBOSE MODE ****************************************************/
/* https://www.quora.com/What-is-the-meaning-of-the-word-verbose-in-computer-science-as-well-as-in-native-English */
/******************************************************************************************************************/