#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>
#include <chrono>
#include <time.h>
#include "struct.h"
#include "functions_prof.h"
#include "functions_nous.h"
#include "robustPredicates.h"
using namespace std;
using namespace robustPredicates;

const int nbits = 8;

int main(int argc, char const *argv[])
{
    int verbose(0);
    const char* input  = "In/Exemple3.in";
    const char* output = "Out/Triangle.out";
    std::chrono::time_point<std::chrono::system_clock> start,end;
    /*----------------------------------
     --- REAL PROGRAM SCRIPT !!! :D ---
    ----------------------------------*/
    // BEGIN
    if(verbose>0){printf("-----  -------============-------  -----\n|---    ------Main running------    ---|\n-----  -------============-------  -----\n\n");}
    /* Vectors initialisation */
    vector<Vertex*> vect_V;
    vector<Vertex*> vect_S;
    vector<Face*>   vect_F;
    double x0 = 0.0; double xRed = 1.0; double xBlue= 0.0;
    double y0 = 0.0; double yRed = 0.0; double yBlue= 1.0;
    /* Reading file */
    file_read(vect_V,vect_F,vect_S,input,&x0,&y0,&xRed,&yRed,&xBlue,&yBlue,verbose);
    /* Hilbert Sort */
    int i; 
    for(i = 0 ; i < vect_V.size() ; i++) 
    { 
        HilbertCoord(x0,y0,xRed,yRed,xBlue,yBlue,vect_V[i],nbits); 
    }
    sort(vect_V.begin(),vect_V.end(),vCompare);
    if(verbose>1)
    {
        printf("Hilbert sorting : \n");
        int i; for(i=0;i<vect_V.size();i++)
        {
            printf("(%.3E,%.3E) : ",vect_V[i]->x,vect_V[i]->y);
            int j; for(j=0;j<nbits;j++)
            {
                printf("%d",vect_V[i]->bits[j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    /* Delaunay triangulation */
    if(verbose>0){printf("Delaunay triangulation began\n");}
    start = std::chrono::system_clock::now();
    delaunayTrgl(vect_V,vect_F,verbose);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if(verbose>0){printf("\n");}
    if(verbose>0){printf("Delaunay triangulation ended\n");}
    if(verbose>0){printf("------------------%.3Es \n", elapsed_seconds.count());}
    if(verbose>0){printf("\n");}
    /* Graphical User Interface*/
//    if(graph){graph_main(argc,argv,100,100,800,600,x0,y0,xRed,vect_V,vect_F);}
    /* Writing file */
    file_write(vect_V,vect_F,vect_S,output,verbose);
    // END
    printf("~~~~----------------------~~~~   THE END ~~~~~----------------------~~~~");
    return 0;
}

void printhelp()
{
    FILE *file = fopen("../_Readme.md","r");
    char buf[1000]; if (!file) return;
    while(fgets(buf,1000,file)!= NULL)
    {
        printf("%s",buf);
    }
    fclose(file);
}