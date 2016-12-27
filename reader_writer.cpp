#include <stdio.h>
#include <vector>
#include <math.h>
#include "struct.h"
using namespace std;

void file_read(vector<Vertex*> &S, vector<Face*> &T, vector<Vertex*> &D, const char* filename, double* x0, double* y0, double* xRed, double* yRed, double* xBlue, double* yBlue, int verbose)
{
    // OPENING file
    if(verbose>0){printf("Opening file %s\n",filename);}
    FILE *file = fopen(filename,"r");
    // PUSHING VERT
    if(verbose>0){printf("> Making vertices\n");}
    int n = 0;
    char c;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;
    double x;
    double y;
    double z;
    while(!feof(file))
    {
        x = NAN; // TO AVOID BLANK LINE
        y = NAN; // TO AVOID BLANK LINE
        z = NAN; // TO AVOID BLANK LINE
        // READING A LINE
        fscanf(file,"%lf",&x); //printf("%f\n",x);
        xmin = min(xmin,x);
        xmax = max(xmax,x);
        fscanf(file,"%lf",&y); //printf("%f\n",y);
        ymin = min(ymin,y);
        ymax = max(ymax,y);
        fscanf(file,"%lf",&z); //printf("%f\n",z);
        zmin = min(zmin,z);
        zmax = max(zmax,z);
        fscanf(file,"%c", &c); //printf("%c\n",c);
        // MAKING THE VERTEX
        if(isnan(x)) break;
        //printf("x : %f ; y = %f ; z = %f\n",x   ,y   ,z   );
        Vertex* V = new Vertex(x,y,z);
        S.push_back(V); n++;
//        printf("x : %f ; y = %f ; z = %f\n",V->x,V->y,V->z);
    }
    if(verbose>0){printf("> %i vertices\n",n);}

    // MAKING SUPER-TRIANGLES
    if(verbose>0){printf("> Making supr-trngs\n");}
//    printf("%f\n",xmin);
//    printf("%f\n",xmax);
//    printf("%f\n",ymin);
//    printf("%f\n",ymax);
    x = xmax-xmin;
    y = ymax-ymin;
    double L = max(x,y);
    x = 0.5*(xmax+xmin);
    y = 0.5*(ymax+ymin);
    *x0 = x;
    *y0 = y;
    *xRed  = L;
    *yBlue = L;
    xmin = x-L; //printf("%f\n",xmin);
    xmax = x+L; //printf("%f\n",xmax);
    ymin = y-L; //printf("%f\n",ymin);
    ymax = y+L; //printf("%f\n",ymax);
    Vertex* T1 = new Vertex(xmin,ymin,0.0);
    Vertex* T2 = new Vertex(xmax,ymin,0.0);
    Vertex* T3 = new Vertex(xmax,ymax,0.0);
    Vertex* T4 = new Vertex(xmin,ymax,0.0);
    D.push_back(T1);
    D.push_back(T2);
    D.push_back(T3);
    D.push_back(T4);
    Face* F1 = new Face(T1,T2,T4);
    Face* F2 = new Face(T2,T3,T4);
    F1->F[1] = F2;
    F2->F[2] = F1;
    T.push_back(F1);
    T.push_back(F2);
    // CLOSING file
    if(verbose>0){printf("Closing file %s\n",filename);}
    if(verbose>0){printf("\n");}
    fclose(file);

    return;
}

void file_write(std::vector<Vertex*> &S, std::vector<Face*> &T, vector<Vertex*> &D, const char* filename, int verbose)
{
    // OPENING file
    if(verbose>0){printf("Opening file %s\n",filename);}
    FILE *file = fopen(filename,"w");
    // Initialisation
    int nVert = S.size();
    int nTrng = T.size();
    int nSupr = D.size();
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
    fprintf(file,"%i\n",nVert+nSupr);
    for(int i = 0; i<nVert ; i++)
    {
        fprintf(file,"%i %f %f %f\n",   i+1   ,S[i]->x,S[i]->y,S[i]->z);
        v.push_back(S[i]); S[i]->index = i+1;
    }
    for(int i = 0; i<nSupr ; i++)
    {
        fprintf(file,"%i %f %f %f\n",i+1+nVert,D[i]->x,D[i]->y,D[i]->z); 
        v.push_back(D[i]); D[i]->index = i+1+nVert;
    }
    fprintf(file,"$EndNodes\n");

    // Writing Elements
    if(verbose>0){printf("> Writing Elements\n");}
    fprintf(file,"$Elements\n");
    fprintf(file,"%i\n",nTrng);
    for(int i = 0; i<nTrng ; i++)
    {
        a = T[i]->V[0]->index; //find(v.begin(),v.end(),T[i]->V[0])-v.begin()+1;
        b = T[i]->V[1]->index; //find(v.begin(),v.end(),T[i]->V[1])-v.begin()+1;
        c = T[i]->V[2]->index; //find(v.begin(),v.end(),T[i]->V[2])-v.begin()+1;
        fprintf(file,"%i 2 0 %i %i %i\n",i+1,a,b,c);
    }
    fputs("$EndElements\n",file);

    fprintf(file,"$NodeData\n"
                "1\n\"Delaunay_triangulation\"\n"
                "1\n0.0\n3\n0\n1\n%u\n",nVert+nSupr); 
    for (int i=0; i<nVert; i++)
        fprintf(file,"%i %f\n",i+1,S[i]->z);
    for (int i=0; i<nSupr; i++)
        fprintf(file,"%i %f\n",i+1+nVert,D[i]->z);
    fputs("$EndNodeData",file);

    // CLOSING file
    if(verbose>0){printf("Closing file %s\n",filename);}
    if(verbose>0){printf("\n");}


    fclose(file);

    return;
}


bool vCompare(Vertex* v1, Vertex* v2)
{
    for(int i=0; i<10; i++)
    {
        if (v1->bits[i] < v2->bits[i]) return true;
        if (v1->bits[i] > v2->bits[i]) return false;
    }
    return false;
}
