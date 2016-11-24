/*
 *  main.c
 *
 *  Created by Vincent Legat on 09/01/12.
 *  Modified for glfw3.1.2   25/01/16
 *  Copyright 2015 UCL-EPL. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <iostream>
//#include <vector>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "glfem.h"

int main( void )
{
    int width, height;
	float ratiox, ratioy;

    glfwInit();
	GLFWwindow* window =  glfwCreateWindow(500,500,"Simple example with graphics",NULL,NULL);
  	glfwMakeContextCurrent(window);

	glShadeModel (GL_SMOOTH);
	glfemMakeRasterFont();

    float myX[5] = { 1.0, 0.0, 0.0,  1.0, -0.05} ;
	float myY[5] = { 1.0,  1.0, 0.0, 0.0, -0.5} ;

    int i,j;
    float I,J;

    do
    {
    	double time = glfwGetTime();
        glfwGetFramebufferSize(window, &width, &height );
		height = height > 0 ? height : 1;
        glViewport(0,0,width,height );

		glClearColor( 0.9f, 0.9f, 0.8f, 0.0f );
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, (GLsizei) width, (GLsizei) height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		ratiox = fmax((float)width/height,1.0)*1.3;
		ratioy = fmax((float)height/width,1.0)*1.3;
		glOrtho (-ratiox, ratiox, -ratioy, ratioy, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Trace les segments de droite entre les noeuds
        glfemDrawElement(myX,myY,5);
        
        //
        for(i = 0; i < 2; ++i)
        {
         	for (j = 0; j < 2; ++j)
         	{
         		I = (float)(i);
         		J = (float)(j);
         		glfemDrawElement(&I,&J,1);
         	}
        }

        glColor3f (0.0, 1.0, 0.0); // Couleur des noeuds
        
        glfemDrawNodes(myX,myY,5); // Dessine les noeuds!


	    glColor3f (0.0, 0.0, 0.0);
        int my_integer = 8;
		char str[256];
		sprintf(str,"You can also write out things, like so : %d\n", my_integer);
		sprintf(str,"or the elapsed time since you open the window %f", time);

		glfemDrawMessage(24,44,str);

        glfwSwapBuffers(window);
		glfwPollEvents();

    }

    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   (!glfwWindowShouldClose(window)) );


	glfwTerminate();
    exit(EXIT_SUCCESS);
}
