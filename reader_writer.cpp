#include <stdlib.h>
#include <stdio.h>
#include "reader_writer.h"

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

unsigned read_nodes_txt(const char* filename, std::vector <Vertex*> &Data, double &xmin, double &xmax, double &ymin, double &ymax)
{
MSH_ASSERT(filename!=NULL)

	FILE* file = fopen(filename,"r");
	if(file==NULL)
		MSH_ERROR("Cannot open file %s",filename);
	
	unsigned line=0; /* Compteur de lignes dans le fichier */
	double xin, yin, valin;
	while(!feof(file))
	{
		line++;
		fscanf(file,"%lf %lf %lf",&xin,&yin,&valin);
		Vertex* vertex = new Vertex(xin,yin,valin);
    	Data.push_back(vertex);
    	
    	xmax = max(xmax,xin);
    	ymax = max(ymax,yin);
    	xmin = min(xmin,xin);
    	ymin = min(ymin,yin);
	}
	fclose(file);
	Data.pop_back(); /* For an unknown reason, last point is added twice */

	unsigned n = Data.size();
	return n;
}

void write_gmsh_Hilbert(const char* filename, std::vector <Vertex*> &Vertices, unsigned n)
{
	MSH_ASSERT(filename!=NULL); // Ok compris
  	FILE* out = fopen(filename,"w");  //"w" argument pour dire qu'on écrit/write un fichier
  	if(out==NULL)
		MSH_ERROR("Cannot open file %s",filename);
	/* Format for gmsh: in section 9.2 MSH binary file format */
  	fprintf(out,"$MeshFormat\n"  
    	        "2.2 0 %u\n"
              	"$EndMeshFormat\n"
              	"$Nodes\n"
              	"%u\n",(unsigned) sizeof(double),n);

 	for(int i=0; i<n; i++)
    fprintf(out,"%u %.10E %.10E 0.0\n",i+1,Vertices[i]->x,Vertices[i]->y);
  	fprintf(out,"$EndNodes\n");
  	/********** End print the nodes *******/
  
  	/********** print the elements ********/
  	fprintf(out,"$Elements\n"
             	"%u\n",n-1);       //
  	for(int i =0; i < n-1; i++)
    fprintf(out,"%u 1 0 %u %u \n",i+1,i+1,i+2);
  	fputs("$EndElements\n",out);
  	/****** End print the elements *******/

  	/******** print the nodes data ******/
  	fprintf(out,"$NodeData\n"
    	        "1\n\"Hilbert_Sorting\"\n"
             	"1\n0.0\n3\n0\n1\n%u\n",n); 
  	for (int i=0; i<n; i++)
    fprintf(out,"%u %.10E\n",i+1,Vertices[i]->val);
  	fputs("$EndNodeData",out);
  	fclose(out);
}

void write_gmsh_Delaunay(const char* filename, std::vector <Vertex*> &Vertices, std::vector <Face*> &Triangles, unsigned n)
{
	MSH_ASSERT(filename!=NULL); // Ok compris
  	FILE* out = fopen(filename,"w");  //"w" argument pour dire qu'on écrit/write un fichier
  	if(out==NULL)
		MSH_ERROR("Cannot open file %s",filename);
	/* Format for gmsh: in section 9.2 MSH binary file format */
 // 	printf("CACAPROUT0M\n");
  	fprintf(out,"$MeshFormat\n"  
            	"2.2 0 %u\n"
              	"$EndMeshFormat\n"
              	"$Nodes\n"
              	"%u\n",(unsigned) sizeof(double),n);

  	for(int i=0; i<n; i++)
    	fprintf(out,"%u %.10E %.10E 0.0\n",Vertices[i]->num+1,Vertices[i]->x,Vertices[i]->y);
   //   	printf("CACAPROUT0M\n");

  	fprintf(out,"$EndNodes\n");
  	/********** End print the nodes *******/
  	//printf("CACAPROUT0E\n");
  	
  	unsigned nT = Triangles.size();
  	/********** print the elements ********/
  	fprintf(out,"$Elements\n"
              "%u\n",nT);       //
  	for(int i =0; i < nT; i++)
  	{
  		printf("CACAPROUT0N\n");
    	fprintf(out,"%u 2 0 %u %u %u\n",i+1,Triangles[i]->V[0]->num + 1,
    										Triangles[i]->V[1]->num + 1,
    										Triangles[i]->V[2]->num + 1);
    }
  	fputs("$EndElements\n",out);
  	/****** End print the elements *******/
  	printf("CACAPROUT0N\n");

  	/******** print the nodes Vertices ******/
  	fprintf(out,"$NodeData\n"
            	"1\n\"Delaunay_triangulation\"\n"
            	"1\n0.0\n3\n0\n1\n%u\n",n); 
  	for (int i=0; i<n; i++)
    	fprintf(out,"%u %.10E\n",i+1,Vertices[i]->val);
  	fputs("$EndNodeData",out);
  	fclose(out);
  	printf("CACAPROUT0F\n");
}

void write_gmsh_txt(const char* filename, double* Data, unsigned dLength, unsigned* Triangles, unsigned tLength)
{
MSH_ASSERT(filename!=NULL); // Ok compris
MSH_ASSERT(Data!=NULL);
MSH_ASSERT(Triangles!=NULL);

	FILE* file = fopen(filename,"w"); //"w" argument pour dire qu'on écrit/write un fichier
	if(file==NULL)
		MSH_ERROR("Cannot open file %s",filename);

	/* format for gmsh: in section 9.2 MSH binary file format */
	fprintf(file,"$MeshFormat\n"
	             "2.2 0 %u\n"
	             "$EndMeshFormat\n"
	             "$Nodes\n"
	             "%u\n",(unsigned) sizeof(double),dLength); //u = Unsigned decimal integer
	/* print the nodes */
	unsigned i;
	for (i=0; i<dLength; i++)
		fprintf(file,"%u %.10E %.10E 0.0\n",i+1,Data[3*i],Data[3*i+1]);

	/* print the elements */
	fprintf(file,"$EndNodes\n"
                 "$Elements\n"
                 "%u\n",tLength);
	for (i=0; i<tLength; i++)
		fprintf(file,"%u 2 0 %u %u %u\n",i+1,Triangles[3*i]+1,
			                               Triangles[3*i+1]+1,
			                               Triangles[3*i+2]+1);
	fputs("$EndElements\n",file);
	fprintf(file,"$NodeData\n"
		         "1\n\"Delaunay_triangulation\"\n"
		         "1\n0.0\n3\n0\n1\n%u\n",dLength);

	for (i=0; i<dLength; i++)
		fprintf(file,"%u %.10E\n",i+1, Data[3*i+2]);
	fputs("$EndNodeData",file);
	fclose(file);
}

void write_gmsh_bin(const char* filename, double* Data, unsigned dLength, unsigned* Triangles, unsigned tLength) //bin=binary
{
MSH_ASSERT(filename!=NULL);
MSH_ASSERT(Data!=NULL);
MSH_ASSERT(Triangles!=NULL);

	FILE* file = fopen(filename,"wb");
	if(file==NULL)
		MSH_ERROR("Cannot open file %s",filename);

	/* format for gmsh */
	fprintf(file,"$MeshFormat\n"
	             "2.2 1 %u\n",(unsigned) sizeof(double)); // Paramètre GMSH Change ici pour à notre avis mettre en binaire l'ecriture
	int one = 1;
	fwrite(&one, sizeof(int), 1, file);

	fprintf(file,"\n$EndMeshFormat\n$Nodes\n%u\n",dLength);

	double zero = 0.0;
	/* print the nodes */
	unsigned i;
	for (i=1; i<=dLength; i++)
	{
		fwrite(&i, sizeof(unsigned), 1, file);
		fwrite(Data+3*i-3, sizeof(double), 2, file);
		fwrite(&zero, sizeof(double), 1, file);
	}

	/* print the elements */
	fprintf(file,"\n$EndNodes\n"
                 "$Elements\n"
                 "%u\n",tLength);

	unsigned header[3] = {2, tLength, 0};
	fwrite(header, sizeof(unsigned), 3, file);

	for (i=0; i<tLength; i++)
	{
		unsigned data[4] = {i+1,Triangles[3*i]+1,Triangles[3*i+1]+1,Triangles[3*i+2]+1};
  		fwrite(data, sizeof(unsigned), 4, file);
	}
	fputs("$EndElements\n",file);

	fprintf(file,"$NodeData\n"
	             "1\n\"Delaunay_triangulation\"\n"
	             "1\n0.0\n3\n0\n1\n%u\n",dLength);

	for (i=1; i<=dLength; i++)
	{
		fwrite(&i, sizeof(unsigned), 1, file);
		fwrite(Data+3*i-1,sizeof(double),1,file);
	}
	fputs("\n$EndNodeData",file);

	fclose(file);
}
/** UNUSED FUNCTION **/
// /* Gives an approximation for the number of lines in the file */
// static unsigned lines_estim(FILE* file){
// 	/* read the first line */
// 	char str[2048];
// 	if(fgets(str,2048,file)==NULL || str[0]=='\0'){
// 		MSH_WARN("Empty file");
// 		return 0;
// 	}

// 	/* count the number of charachter at the beginning of the file*/
// 	int c;
// 	for (c=0; str[c+1]!='\0'; c++);

// 	fseek(file,0L,SEEK_END);
// 	unsigned lines_approx = ftell(file)/c;
// 	fseek(file,0L,SEEK_SET);
// 	return lines_approx;
// }
