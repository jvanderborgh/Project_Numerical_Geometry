/*
 *  glfem.h
 *  Library for MECA1120 : Finite Elements for dummies
 *
 *  Copyright (C) 2015 UCL-EPL : Vincent Legat
 *  All rights reserved.
 *
 *  Pour GLFW (version utilisée 3.1.2)
 *  Pour l'installation de la librairie, voir http://www.glfw.org/
 *
 */

#ifndef _GLFEM_H_
#define _GLFEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GLFW/glfw3.h>

void glfemDrawColorElement(float *x, float *y, double *u, int n);
void glfemDrawElement(float *x, float *y, int n);
void glfemDrawNodes(float* x, float* y,int n);

void glfemMessage(char *message);

void glfemMakeRasterFont(void);
void glfemDrawMessage(int h, int v, char *message);
void glfemSetRasterSize(int width, int height);
void glfemInit(char *windowName);

#endif
