#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "structures.h"
using namespace std;

/********************************************************
 *  SOME MACRO FOR ERROR MESSAGES
 *  (maybe put that into some header, it's very usefull)
 ********************************************************/
#define MSH_ERROR(msg, ...) do{ \
    fprintf(stderr,"\e[1;31m\n== ERROR (%s -> %s:%d):\n\e[0m\t" msg \
        "\nExiting Program...\n\n",__func__,__FILE__,__LINE__,##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
    } while(0)

#define MSH_WARN(msg,...) \
    fprintf(stderr,"\nwarning (%s -> %s:%d): " msg "\n",__func__,__FILE__,__LINE__,##__VA_ARGS__);

#ifdef DEBUG
#define MSH_ASSERT(exp,...) do{ \
        if(!(exp)) { \
            fprintf(stderr,"\e[1;31m\n== ERROR (%s -> %s:%d):\t assertion (" #exp ") Failed\n\e[0m\t" __VA_ARGS__ \
            "\nExiting Program...\n\n",__func__,__FILE__,__LINE__); \
            exit(EXIT_FAILURE); \
        }\
    } while(0)

#else
#define MSH_ASSERT(...)
#endif

void read_nodes_txt(vector<Vertex*> &S, vector<Face*> &T, const char* filename, double &xmin, double &ymin, double &zmin, double &xmax, double &ymax, double &zmax, int verbose)
{
    // OPENING file
    if(verbose>0)
        {printf("Opening file %s\n",filename);}
    MSH_ASSERT(filename!=NULL);
    FILE *file = fopen(filename,"r");
    if(file==NULL)
        MSH_ERROR("Cannot open file %s",filename);

    // PUSHING VERT
    if(verbose>0){printf("> Making vertices\n");}
    int n = 0;
    double xin(NAN),yin(NAN),zin(NAN);
    while(!feof(file))
    {
        xin = yin = zin = NAN;  
        /* Reading a line */
        fscanf(file,"%lf %lf %lf",&xin,&yin,&zin); 
        xmin = min(xmin,xin);
        xmax = max(xmax,xin);
        ymin = min(ymin,yin);
        ymax = max(ymax,yin);
        zmin = min(zmin,zin);
        zmax = max(zmax,zin);
        /* Making the Vertex */
        if(isnan(xin)) break;
        Vertex* V = new Vertex(xin,yin,zin);
        S.push_back(V); n++;
    }
    if(verbose>0){printf("> %i vertices\n",n);}
    if(verbose>0){printf("Closing file %s\n",filename);}
    if(verbose>0){printf("\n");}
    fclose(file);

    return;
}

void write_gmsh_Delaunay(vector<Vertex*> &S, vector<Face*> &T, vector<Vertex*> &D, const char* filename, int verbose)
{
    // OPENING file
    if(verbose>0){printf("Opening file %s\n",filename);}
    FILE *file = fopen(filename,"w");
    // Initialisation
    int nV = S.size();
    int nD = D.size();
    int nT = T.size();
    int a;
    int b;
    int c;
    vector<Vertex*> v;
    // Writing Header
    if(verbose>0){printf("> Writing Header\n");}
    fprintf(file,"$MeshFormat\n");
    fprintf(file,"2.2 0 %u \n",(unsigned) sizeof(double));
    fprintf(file,"$EndMeshFormat\n");
    // Writing Vertices
    if(verbose>0){printf("> Writing Vertices\n");}
    fprintf(file,"$Nodes\n");
    fprintf(file,"%i\n",nV+nD);
    for(int i = 0; i<nV ; i++)
    {
        fprintf(file,"%i %f %f %f\n",   i+1   ,S[i]->x,S[i]->y,S[i]->z);
        v.push_back(S[i]); S[i]->index = i+1;
    }
    for(int i = 0; i<nD ; i++)
    {
        fprintf(file,"%i %f %f %f\n",i+1+nV,D[i]->x,D[i]->y,D[i]->z); 
        v.push_back(D[i]); D[i]->index = i+1+nV;
    }
    fprintf(file,"$EndNodes\n");

    /* Writing Elements */
    if(verbose>0){printf("> Writing Elements\n");}
    fprintf(file,"$Elements\n");
    fprintf(file,"%i\n",nT);
    for(int i = 0; i<nT ; i++)
    {
        a = T[i]->V[0]->index; //find(v.begin(),v.end(),T[i]->V[0])-v.begin()+1;
        b = T[i]->V[1]->index; //find(v.begin(),v.end(),T[i]->V[1])-v.begin()+1;
        c = T[i]->V[2]->index; //find(v.begin(),v.end(),T[i]->V[2])-v.begin()+1;
        fprintf(file,"%i 2 0 %i %i %i\n",i+1,a,b,c);
    }
    fputs("$EndElements\n",file);

    fprintf(file,"$NodeData\n"
                "1\n\"Delaunay_triangulation\"\n"
                "1\n0.0\n3\n0\n1\n%u\n",nV+nD); 
    for (int i=0; i<nV; i++)
        fprintf(file,"%i %f\n",i+1,S[i]->z);
    for (int i=0; i<nD; i++)
        fprintf(file,"%i %f\n",i+1+nV,D[i]->z);
    fputs("$EndNodeData",file);

    // CLOSING file
    if(verbose>0){printf("Closing file %s\n",filename);}
    if(verbose>0){printf("\n");}

    fclose(file);
    return;
}

void write_gmsh_Hilbert(const char* filename, vector <Vertex*> &V)
{
    MSH_ASSERT(filename!=NULL); // Ok compris
    FILE* file = fopen(filename,"w");  //"w" argument pour dire qu'on écrit/write un fichier
    if(file==NULL)
        MSH_ERROR("Cannot open file %s",filename);
    /* Format for gmsh: in section 9.2 MSH binary file format */
    unsigned nV = V.size();
    fprintf(file,"$MeshFormat\n"  
                "2.2 0 %u\n"
                "$EndMeshFormat\n"
                "$Nodes\n"
                "%u\n",(unsigned) sizeof(double),nV);
    /*********** Print the nodes **********/
    for(int i=0; i<nV; i++)
    fprintf(file,"%u %.10E %.10E 0.0\n",i+1,V[i]->x,V[i]->y);
    fprintf(file,"$EndNodes\n");
    /********** End print the nodes *******/
  
    /********** Print the elements ********/
    fprintf(file,"$Elements\n"
                 "%u\n",nV-1);
    for(int i =0; i < nV-1; i++)
    fprintf(file,"%u 1 0 %u %u \n",i+1,i+1,i+2);
    fputs("$EndElements\n",file);
    /****** End print the elements *******/

    /******** Print the nodes data ******/
    fprintf(file,"$NodeData\n"
                 "1\n\"Hilbert_Sorting\"\n"
                 "1\n0.0\n3\n0\n1\n%u\n",nV); 
    for (int i=0; i<nV; i++)
    fprintf(file,"%u %.10E\n",i+1,V[i]->z);
    fputs("$EndNodeData",file);
    fclose(file);
}