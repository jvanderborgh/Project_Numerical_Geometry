#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>
#include <chrono>
#include <time.h>
#include "structures.h"
#include "functions.h"
#include "reader_writer.h"
#include "robustPredicates.h"
using namespace std;
using namespace robustPredicates;

int main(int argc, char const *argv[])
{
    int verbose(1);
    const char* input  = "In/Exemple3.in";
    const char* output = "Out/Triangle.out";
    chrono::time_point<chrono::system_clock> start,end;
    printf("-----  -------============-------  -----\n");
    printf("|---    ------Main running------    ---|\n");
    printf("-----  -------============-------  -----\n\n");
    /* Vectors initialization */
    vector<Vertex*> vect_V;
    vector<Vertex*> vect_D;
    vector<Face*>   vect_F;
    double xmin(0.0), ymin(0.0), zmin(0.0);
    double xmax(0.0), ymax(0.0), zmax(0.0);
    double x0(0.0), xRed(1.0), xBlue(0.0);
    double y0(0.0), yRed(0.0), yBlue(1.0);
    /* Reading file */
    read_nodes_txt(vect_V,vect_F, input, xmin, ymin, zmin, xmax, ymax, zmax,verbose);
    superTriangles(vect_F,vect_D, xmin, xmax, ymin, ymax, x0, y0, xRed, yRed, xBlue, yBlue);

    /****** Begin HILBERT *******/
    for(int i = 0 ; i < vect_V.size() ; i++) 
    {
//        HilbertCoord(x0,y0,xRed,yRed,xBlue,yBlue,vect_V[i]); 
        x0 = y0 = 0;
        
        HilbertCoord(x0,y0,xRed,yRed,xBlue,yBlue,vect_V[i]); 
    }
    sort(vect_V.begin(),vect_V.end(),vCompare);
    write_gmsh_Hilbert("Out/Hilbert.out",vect_V); /* +4 pour les super triangles!!! */
    /******* End HILBERT ********/

    // if(verbose>1)
    // {
    //     printf("Hilbert sorting : \n");
    //     int i; for(i=0;i<vect_V.size();i++)
    //     {
    //         printf("(%.3E,%.3E) : ",vect_V[i]->x,vect_V[i]->y);
    //         int j; for(j=0;j<nbits;j++)
    //         {
    //             printf("%d",vect_V[i]->bits[j]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }

    /* Delaunay triangulation */
    if(verbose>0){printf("Starting Delaunay triangulation\n");}
    start = chrono::system_clock::now();
    delaunayTrgl(vect_V,vect_F,verbose);
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    if(verbose>0){printf("\n");}
    if(verbose>0){printf("Delaunay triangulation ended\n");}
    if(verbose>0){printf("------------------%.3Es \n", elapsed_seconds.count());}
    if(verbose>0){printf("\n");}
    /* Writing file */
    write_gmsh_txt(vect_V,vect_F,vect_D,output,verbose);
    // END
    printf("-----  -------============-------  -----\n");
    printf("|---    ------   The END  ------    ---|\n");
    printf("-----  -------============-------  -----\n\n");    return 0;
}