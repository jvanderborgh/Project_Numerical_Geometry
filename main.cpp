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

const int nbits = 8;

int main(int argc, char const *argv[])
{
    int verbose(1);
    const char* input  = "In/Exemple3.in";
    const char* output = "Out/Triangle.out";
    std::chrono::time_point<std::chrono::system_clock> start,end;
     // BEGIN
    if(verbose>0){printf("-----  -------============-------  -----\n|---    ------Main running------    ---|\n-----  -------============-------  -----\n\n");}
    /* Vectors initialisation */
    vector<Vertex*> vect_V;
    vector<Vertex*> vect_S;
    vector<Face*>   vect_F;
    double x0(0), xRed(1), xBlue(0);
    double y0(0), yRed(0), yBlue(1);
    /* Reading file */
    file_read(vect_V,vect_F,vect_S,input,&x0,&y0,&xRed,&yRed,&xBlue,&yBlue,verbose);
    /****** Begin HILBERT *******/
    for(int i = 0 ; i < vect_V.size() ; i++) 
    { 
        HilbertCoord(x0,y0,xRed,yRed,xBlue,yBlue,vect_V[i],nbits); 
    }
    sort(vect_V.begin(),vect_V.end(),vCompare);
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
    start = std::chrono::system_clock::now();
    delaunayTrgl(vect_V,vect_F,verbose);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if(verbose>0){printf("\n");}
    if(verbose>0){printf("Delaunay triangulation ended\n");}
    if(verbose>0){printf("------------------%.3Es \n", elapsed_seconds.count());}
    if(verbose>0){printf("\n");}
    /* Writing file */
    file_write(vect_V,vect_F,vect_S,output,verbose);
    // END
    printf("~~~~----------------------~~~~   THE END ~~~~~----------------------~~~~");
    return 0;
}