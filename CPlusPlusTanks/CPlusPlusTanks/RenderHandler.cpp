#include "stdafx.h"
#include "RenderHandler.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream> 
#include <math.h> 
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#pragma comment(lib, "Opengl32.lib")

RenderHandler::RenderHandler() {

}

RenderHandler::~RenderHandler() {

}

void RenderHandler::update() {
	//Update things
	glutPostRedisplay();
}

void RenderHandler::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // TODO draw our scene
	drawCircle(100.0, 100.0, 50.0, 500, 1.0, 1.0, 1.0, true);
	drawCircle(200.0, 100.0, 50.0, 500, 1.0, 1.0, 1.0, false);
	drawRect(250.0, 50.0, 50, 100, 1.0, 1.0, 1.0, true);
	drawRect(300.0, 50.0, 50, 100, 1.0, 1.0, 1.0, false);

    glutSwapBuffers();
}

//Render a circle, filled or not
//Note: Circle rendering code sourced from - http://slabode.exofire.net/circle_draw.shtml
//      Modified by Thomas Hayden for color and fill functionality
void RenderHandler::drawCircle(float cx, float cy, float radius, int num_segments, float r, float g, float b, bool fill) {
	glColor3f(r, g, b);
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = radius;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);//output vertex 
        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd();
	if (fill && radius > 0)
		drawCircle(cx,cy,radius-.1,num_segments,r,g,b,fill);
	glColor3f(1.0f, 1.0f, 1.0f);
}

//Render a rectangle, filled or not
//Note: The no fill function does not line up perfectly with filled rectangles
void RenderHandler::drawRect(float x, float y, float width, float height, float r, float g, float b, bool fill) {
	glColor3f(r, g, b);
	if(fill) {
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x + width, y);
			glVertex2f(x + width, y + height);
			glVertex2f(x, y + height);
		glEnd();
	} else {
		//Render side 1 of the rectangle
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x + width, y);
			glVertex2f(x + width, y - 1);
			glVertex2f(x, y - 1);
		glEnd();
		//Render side 2 of the rectangle
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x + 1, y);
			glVertex2f(x + 1, y + height);
			glVertex2f(x, y + height);
		glEnd();
		//Render side 3 of the rectangle
		glBegin(GL_QUADS);
			glVertex2f(x, y + height);
			glVertex2f(x + width, y + height);
			glVertex2f(x + width, y + height + 1);
			glVertex2f(x, y + height + 1);
		glEnd();
		//Render side 4 of the rectangle
		glBegin(GL_QUADS);
			glVertex2f(x + width, y);
			glVertex2f(x + width - 1, y);
			glVertex2f(x + width - 1, y + height);
			glVertex2f(x + width, y + height);
		glEnd();
	}
	glColor3f(1.0f, 1.0f, 1.0f);
}