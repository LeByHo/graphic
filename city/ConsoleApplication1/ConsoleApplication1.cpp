#include "stdafx.h"
#include<glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static int delay = 4000000;
static GLfloat Day = 0.2,  Time = 0.2, Move = 0.2, height =0.4, carMove= 0.2;
float k = 0.002, s = 0.2,m_height =0.1;
GLfloat axis = 1;
GLfloat scale = 1.0;
GLUquadricObj *pQuad;
int Width = 1000, Height = 1000, temp = 0,c_y=0,e_y=0,c_x=0,c_z=0,e_z=0,e_x=0;
int ct = 0;
GLfloat eye_x, eye_z = 1.0, left_x = -1, right_x = 1, size = 5;
void drawRectangle2(float a, float b, float c)
{
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.0f*c);
	glVertex3f(0.0f, 0.1f*b, 0.0f*c);
	glEnd();
}
void drawCircle(float a, int b)
{
	double PI = atan(1.0)*4.0;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (int i = -180; i <= 180; i = i + b)
	{
		double radian = i*PI / 180;
		glVertex3f(0.1f*sin(radian)*cos(0)*a, 0.1f*cos(radian)*cos(0)*a, 0.1f*sin(0));
	}
	glEnd();
}
void drawCylinder(float under, float up, float length, int num1, int num2, float color, float green)
{
	double PI = atan(1.0)*4.0;
	float x = (up - under) / num1;
	glPushMatrix();
	for (float i = 0; i < num1; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (int j = -180; j <= 180; j = j + num2)
		{
			glColor3f(1.0, 1.0, 1.0);
			glColor3f((fabs(i) / (float)num1) / 2.0 + color, (fabs(i) / (float)num1) / 4.0 + color, green);
			double radian = j*PI / 180;
			glVertex3f(0.1f*sin(radian)*cos(0) * up, 0.1f*cos(radian)*cos(0) * up, 0.1f*sin(0));
			glVertex3f(0.1f*sin(radian)*cos(0) * (up - x), 0.1f*cos(radian)*cos(0) * (up - x), 0.1f*sin(0) + 0.1*(length / ((float)num1)));
		}
		glEnd();
		up = up - x;
		glTranslatef(0.0, 0.0, 0.1*length / ((float)num1));
	}
	glPopMatrix();
}
void drawCylinder2(float under, float up, float length, int num1, int num2)
{
	double PI = atan(1.0)*4.0;
	float x = (up - under) / num1;
	glPushMatrix();
	for (float i = 0; i < num1; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (int j = -180; j <= 180; j = j + num2)
		{
		
			double radian = j*PI / 180;
			glVertex3f(0.1f*sin(radian)*cos(0) * up, 0.1f*cos(radian)*cos(0) * up, 0.1f*sin(0));
			glVertex3f(0.1f*sin(radian)*cos(0) * (up - x), 0.1f*cos(radian)*cos(0) * (up - x), 0.1f*sin(0) + 0.1*(length / ((float)num1)));
		}
		glEnd();
		up = up - x;
		glTranslatef(0.0, 0.0, 0.1*length / ((float)num1));
	}
	glPopMatrix();
}
void drawRectangle_1(float a, float b, float c)
{
	glBegin(GL_POLYGON);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glEnd();
	//옆면
	glBegin(GL_POLYGON);
	glColor3f(144 / 256.0, 144.0 / 256.0, 144.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(216 / 256.0, 216.0 / 256.0, 216.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.0f*c);
	glVertex3f(0.0f, 0.1f*b, 0.0f*c);
	glEnd();
	glPushMatrix();
	glTranslated(0.2f, -0.3f, 0.0f);
	glColor3f(234 / 256.0, 234.0 / 256.0, 234.0 / 256.0);
	drawRectangle2(5, 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.3f, 0.5f, 1.0f);
	drawRectangle2(1, 1, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, 0.5f, 1.0f);
	drawRectangle2(1, 1, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0f, 0.5f, 1.2f);
	if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(0.8 + Move / 20, 0.8 + Move / 20, 0.0);
	}
	drawRectangle2(2, 2, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.2f, 0.5f, 1.2f);
	if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(0, 0.8 + Move / 20, 0.8 + Move / 20);
	}
	drawRectangle2(2, 2, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.4f, 0.5f, 1.2f);
	if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(0.8 + Move / 20, 0.0, 0.8 + Move / 20);
	}
	drawRectangle2(2, 2, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, 0.5f, 1.2f);
	if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(0, 0.8 + Move / 20, 0.8 + Move / 20);
	}
	drawRectangle2(2, 2, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.8f, 0.5f, 1.2f);
	if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(0.8 + Move / 20, 0.8 + Move / 20, 0.0);
	}
	drawRectangle2(2, 2, 5);
	glPopMatrix();
}
void drawRectangle_2(float a, float b, float c)
{
	glBegin(GL_POLYGON);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glEnd();
	//옆면
	glBegin(GL_POLYGON);
	glColor3f(117/ 256.0, 117.0 / 256.0, 117.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(144 / 256.0, 144.0 / 256.0, 144.0 / 256.0);
	
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(144 / 256.0, 144.0 / 256.0, 144.0 / 256.0);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(144 / 256.0, 144.0 / 256.0, 144.0 / 256.0);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.0f*c);
	glVertex3f(0.0f, 0.1f*b, 0.0f*c);
	glEnd();
	glPushMatrix();
	glTranslated(0.2f, -0.3f, 0.0f);
	glColor3f(234 / 256.0, 234.0 / 256.0, 234.0 / 256.0);
	drawRectangle2(5, 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.1f, -0.01f, 0.7f);
	if (((int)Time % 360) < 180) {
		glColor3f(1.0, 1.0, 1.0);
	}
	else if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(1, 1, 0.0);
	}
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, -0.01f, 0.7f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.1f, -0.01f, 1.2f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, -0.01f, 1.2f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.1f, -0.01f, 1.7f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, -0.01f, 1.7f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.1f, -0.01f, 2.2f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, -0.01f, 2.2f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.1f, -0.01f, 2.6f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, -0.01f, 2.6f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
}
void drawRectangle_3(float a, float b, float c)
{
	glBegin(GL_POLYGON);
	
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glEnd();
	//옆면
	glBegin(GL_POLYGON);
	glColor3f(144 / 256.0, 144.0 / 256.0, 144.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(216 / 256.0, 216.0 / 256.0, 216.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.0f*c);
	glVertex3f(0.0f, 0.1f*b, 0.0f*c);
	glEnd();
	glPushMatrix();
	glTranslated(0.2f, -0.3f, 0.0f);
	glColor3f(234 / 256.0, 234.0 / 256.0, 234.0 / 256.0);
	drawRectangle2(5, 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.1f, -0.01f, 0.7f);
	if (((int)Time % 360) < 180) {
		glColor3f(1.0, 1.0, 1.0);
	}
	else if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(1,1, 0.0);
	}
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, -0.01f, 0.7f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.1f, -0.01f, 1.2f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.6f, -0.01f, 1.2f);
	drawRectangle2(3, 3, 3);
	glPopMatrix();
}
void drawRectangle_4(float a, float b, float c)
{
	glBegin(GL_POLYGON);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glEnd();
	//옆면
	glBegin(GL_POLYGON);
	glColor3f(144 / 256.0, 144.0 / 256.0, 144.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(216 / 256.0, 216.0 / 256.0, 216.0 / 256.0);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.1f*a, 0.1f*b, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(180 / 256.0, 180.0 / 256.0, 180.0 / 256.0);
	glVertex3f(0.0f, 0.1f*b, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.0f*c);
	glVertex3f(0.0f, 0.1f*b, 0.0f*c);
	glEnd();
	glPushMatrix();
	glTranslated(3.0f, -0.3f, 0.0f);
	glColor3f(180 / 256.0, 180.0 / 256.0,180.0 / 256.0);
	drawRectangle2(5, 5, 5);
	glPopMatrix();
	for (float i = 0; i < 6.5; i = i + 0.5) {
		for (float j = 0; j < 5.5; j = j + 0.5) {
			glPushMatrix();
			glTranslated((0.1 + i), -0.01f, (0.7 + j));
			glColor3f(1.0, 1.0, 1.0);
			if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
					if ((i == 0.5&&j == 2.5) || (i == 0.5&&j == 3.0) || (i == 0.5&&j == 3.5) || (i == 0.5&&j == 4.0) || (i == 1.0&&j == 4.5) || (i == 1.0&&j == 2.0) || (i == 1.5&&j == 5.0) || (i == 1.5&&j == 1.5) || (i == 2.0&&j == 5.0) || (i == 2.0&&j == 1.0) || (i == 2.5&&j == 4.5) || (i == 2.5&&j == 0.5) || (i == 3.0&&j == 4.0) || (i == 3.0&&j == 0.0) || (i == 3.5&&j == 4.5) || (i == 3.5&&j == 0.5)
						|| (i == 4.0&&j == 5.0) || (i == 4.0&&j == 1.0) || (i == 4.5&&j == 5.0) || (i == 4.5&&j == 1.5) || (i == 5.0&&j == 4.5) || (i == 5.0&&j == 2.0) || (i == 5.5&&j == 4.0) || (i == 5.5&&j == 3.5) || (i == 5.5&&j == 3.0) || (i == 5.5&&j == 2.5)) {
						glColor3f(1, 1, 0);
					}
			}
			drawRectangle2(3, 3, 3);
			glPopMatrix();
			}
			
		}
	}
void drawCylinder3(float under, float up, float length, int num1, int num2, float color, float green)
{
	double PI = atan(1.0)*4.0;
	float x = (up - under) / num1;
	glPushMatrix();
	for (float i = 0; i < num1; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (int j = -180; j <= 180; j = j + num2)
		{
			glColor3f(1.0, 1.0, 1.0);
			glColor3f((fabs(i)+Time / (float)num1) / 2.0 + color, (fabs(i) + Time / (float)num1) / 4.0 + color, green);
			double radian = j*PI / 180;
			glVertex3f(0.1f*sin(radian)*cos(0) * up, 0.1f*cos(radian)*cos(0) * up, 0.1f*sin(0));
			glVertex3f(0.1f*sin(radian)*cos(0) * (up - x), 0.1f*cos(radian)*cos(0) * (up - x), 0.1f*sin(0) + 0.1*(length / ((float)num1)));
		}
		glEnd();
		up = up - x;
		glTranslatef(0.0, 0.0, 0.1*length / ((float)num1));
	}
	glPopMatrix();
}
void init() {
	pQuad = gluNewQuadric();
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(156 / 256.0, 91 / 256.0, 54 / 256.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void timer(int t) {
	k = -0.001;
	
}
void move()
{
	carMove += m_height;
	if (carMove > 110) {
		carMove = 0;
	}
	height += m_height;
	if (height > 2.5)
		height = 0;
	Time += 0.25;
	Day += k;
	if (Day > 1.0) {
		k = 0.002;
		k = -k;
	}
	else if (Day < 0) {
		timer(0);
		k = -k;
	}

	Move += s;
	if (Move > 6.0) {
		s = -s;
	}
	if (Move < -6.0) {
		s = -s;
	}
	glutPostRedisplay();
}
void drawTree(float a, float b, float c) {
	glColor3f(171 / 256.0, 74.0 / 256.0, 18.0 / 256.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.1f*a, 0.1f, 0.0f);
	glVertex3f(0.1f*a, 0.0f, 0.0f);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.1f*a, 0.1f, 0.0f);
	glVertex3f(0.1f*a, 0.1f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f, 0.1f*c);
	glVertex3f(0.0f, 0.1f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.1f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.1f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.0f*c);
	glVertex3f(0.0f, 0.1f, 0.0f*c);
	glEnd();
	glPushMatrix();
	//leaf
	glTranslated(0.1f, 0.0f, 0.1f*c);
	glColor3f(3/ 256.0, 60.0 / 256.0, 0.0 / 256.0);
	glutSolidSphere(0.5, 30, 17);
	glPopMatrix();
	glPushMatrix();
	//fruit1빨강
	glTranslated(-0.25f, -0.8f, 0.13f*c);//옆(크면 오른쪽) ,앞뒤(높을수록 뒤로), 높이
	glColor3f(0.7, 0, 0);
	glutSolidSphere(0.1, 30, 17);
	glPopMatrix();
	glPushMatrix();
	//fruit2노랑
	glTranslated(0.35f, -0.5f, 0.13f*c);//옆(크면 오른쪽) ,앞뒤, 높이
	glColor3f(0.7, 0.7, 0);
	glutSolidSphere(0.1, 30, 17);
	glPopMatrix();
	glPushMatrix();
	//fruit3주황
	glTranslated(-0.03f, -0.8f, 0.15f*c);//옆(크면 오른쪽) ,앞뒤, 높이
	glColor3f(0.9, 0.5, 0.0);
	glutSolidSphere(0.1, 30, 17);
	glPopMatrix();
	//뒤로 왼쪽
}
void drawTree2(float a, float b, float c) {
	glColor3f(171 / 256.0, 74.0 / 256.0, 18.0 / 256.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.1f*a, 0.1f, 0.0f);
	glVertex3f(0.1f*a, 0.0f, 0.0f);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.1f*a, 0.1f, 0.0f);
	glVertex3f(0.1f*a, 0.1f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);

	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f, 0.1f*c);
	glVertex3f(0.0f, 0.1f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.0f, 0.1f*c);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.1f*a, 0.1f, 0.1f*c);
	glVertex3f(0.1f*a, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.1f*c);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.1f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.1f*c);
	glVertex3f(0.0f, 0.0f, 0.0f*c);
	glVertex3f(0.0f, 0.1f, 0.0f*c);
	glEnd();
	glPushMatrix();
	//leaf
	glTranslated(0.1f, 0.0f, 0.1f*c/3);
	glColor3f(3 / 256.0, 60.0 / 256.0, 0.0 / 256.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5f, -0.04f, 0.0f*c);
	glVertex3f(-0.5f, -0.04f, 0.0f*c);
	glVertex3f(-0.1f, -0.04f, 1.2f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//leaf
	glTranslated(0.1f, 0.0f, 1.0f );
	glColor3f(3 / 256.0, 80.0 / 256.0, 0.0 / 256.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5f, -0.05f, 0.0f);
	glVertex3f(-0.5f, -0.05f, 0.0f);
	glVertex3f(-0.1f, -0.05f, 1.2f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//fruit1빨강
	glTranslated(-0.23f, -0.8f, 0.07f*c);//옆(크면 오른쪽) ,앞뒤(높을수록 뒤로), 높이
	glColor3f(0.7, 0, 0);
	glutSolidSphere(0.1, 30, 17);
	glPopMatrix();
	glPushMatrix();
	//fruit2노랑
	glTranslated(0.30f, -0.5f, 0.08f*c);//옆(크면 오른쪽) ,앞뒤, 높이
	glColor3f(0.7, 0.7, 0);
	glutSolidSphere(0.1, 30, 17);
	glPopMatrix();
	glPushMatrix();
	//fruit3주황
	glTranslated(-0.03f, -0.8f, 0.15f*c);//옆(크면 오른쪽) ,앞뒤, 높이
	glColor3f(0.9, 0.5, 0.0);
	glutSolidSphere(0.1, 30, 17);
	glPopMatrix();
	//뒤로 왼쪽
}
void drawSquare(float a, float b, float c) {
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.1f*b, 0.0f);
	glVertex3f(0.1f*a, 0.0f, 0.0f);
	glEnd();

}
void drawSun(float a) {
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(a, 30, 17);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glTranslated(-1, 0, 0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.3, 0.5);
	glVertex3f(0.0,0.3,-0.5);
	glVertex3f(-0.5,0.3,0.0);
	glEnd();
	glTranslated(2, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.3, 0.5);
	glVertex3f(0.0, 0.3, -0.5);
	glVertex3f(0.5, 0.3, 0.0);
	glEnd();
	glTranslated(-1, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.3, 0.5);
	glVertex3f(-0.5, 0.3, 0.0);
	glVertex3f(0.5, 0.3, 0.0);
	glEnd();
	glTranslated(0, 0, -2);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.3, -0.5);
	glVertex3f(-0.5, 0.3, 0.0);
	glVertex3f(0.5, 0.3, 0.0);
	glEnd();
	glTranslated(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.3, 0.5);
	glVertex3f(-0.5, 0.3, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glEnd();
	glTranslated(-2, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.3, 0.5);
	glVertex3f(0.5, 0.3, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glEnd();
	glTranslated(2, 0, 2);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.3, -0.5);
	glVertex3f(-0.5, 0.3, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glEnd();
	glTranslated(-2, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.3, -0.5);
	glVertex3f(0.5, 0.3, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glEnd();
}
void drawMoon(float a) {
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(a, 30, 17);
}
void drawCloud(float a) {
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(a, 30, 17);
	glPushMatrix();
	glTranslated(1.2f*a, 0.3f, 0.0);
	glutSolidSphere(a, 30, 17);
	glPopMatrix();
	glPushMatrix();
	glTranslated(2.4f*a, 0.0, 0.0);
	glutSolidSphere(a, 30, 17);
	glPopMatrix();
}
void drawStar() {
	glColor3f(0.8+Move/20, 0.8+Move/20, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.3f, -0.2f, 0.0f);
	glVertex3f(-0.3f, -0.2f, 0.0f);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, -0.4f, 0.0f);
	glVertex3f(-0.3f, 0.2f, 0.0f);
	glVertex3f(0.3f, 0.2f, 0.0f);
	glEnd();
}
void drawLoadStand(float a,float b,float c) {
	drawRectangle2(a, b, c);
	glPushMatrix();
		glTranslated(0, 0, 0.5f);
		glRotated(60, 1, 0, 0);
		drawRectangle2(a, b, c);
		glPushMatrix();
			glTranslated(0.05f, 0.0f, 0.55f);
			if (((int)Time % 360) < 180) {
				glColor3f(1.0, 1.0, 1.0);
			}
			else if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
				glColor3f(0.8 + Move / 20, 0.8 + Move / 20, 0.0);
			}
			glutSolidSphere(0.05, 45, 45);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(0, 0, 0.5f);
		glRotated(-60, 1, 0, 0);
		drawRectangle2(a, b, c);
		glPushMatrix();
			glTranslated(0.05f, 0.05f, 0.55f);
			if (((int)Time % 360) < 180) {
				glColor3f(1.0, 1.0, 1.0);
			}
			else if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
				glColor3f(0.8 + Move / 20, 0.8 + Move / 20, 0.0);
			}
			glutSolidSphere(0.05, 45, 45);
		glPopMatrix();
	glPopMatrix();
}
void drawCar(float a, float b, float c) {
	glTranslated(0, 0, 0.2f);
	drawRectangle2(a, b, c);
	glPushMatrix();
		glColor3f(207 / 256.0, 54 / 256.0, 130 / 256.0);
		glTranslated(0, 0.1f, 0.2f);
		drawRectangle2(a, b/2, c);
	glPopMatrix();
	glPushMatrix();
		glTranslated(0.04f, 0.4f, -0.06f);
		glColor3f(0, 0, 0);
		glutSolidSphere(0.11, 44, 44);
	glPopMatrix();
	glPushMatrix();
		glTranslated(0.04f, 1.4f, -0.06f);
		glColor3f(0, 0, 0);
		glutSolidSphere(0.11, 44, 44);
	glPopMatrix();
	glPushMatrix();
		glTranslated(0.25f, 1.4f, -0.06f);
		glColor3f(0, 0, 0);
		glutSolidSphere(0.11, 44, 44);
	glPopMatrix();
	glPushMatrix();
		glTranslated(0.25f, 0.4f, -0.06f);
		glColor3f(0, 0, 0);
		glutSolidSphere(0.11, 44, 44);
	glPopMatrix();
	glPushMatrix();
		glTranslated(0.23f, 0.0f, 0.1f);
		if (((int)Time % 360) < 180) {	
			glColor3f(1.0, 1.0, 1.0);
		}
		else if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
			glColor3f(0.8 + Move / 20, 0.8 + Move / 20, 0.0);
		}
		glutSolidSphere(0.05, 44, 44);
	glPopMatrix();
	glPushMatrix();
		glTranslated(0.08f, 0.0f, 0.1f);
		glutSolidSphere(0.05, 44, 44);
	glPopMatrix();

}
void drawCar2(float a, float b, float c) {
	glTranslated(0, 0, 0.2f);
	drawRectangle2(a, b, 2*c);
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	glTranslated(0.05f, 0.3f, 0.1f);
	drawSquare(a / 1.5, b / 8, c);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.04f, 0.4f, -0.06f);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.11, 44, 44);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.04f, 1.7f, -0.06f);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.11, 44, 44);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.35f, 1.7f, -0.06f);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.11, 44, 44);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.35f, 0.4f, -0.06f);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.11, 44, 44);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.29f, 0.0f, 0.1f);
	if (((int)Time % 360) < 180) {
		glColor3f(1.0, 1.0, 1.0);
	}
	else if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(0.8 + Move / 20, 0.8 + Move / 20, 0.0);
	}
	glutSolidSphere(0.05, 44, 44);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.10f, 0.0f, 0.1f);
	glutSolidSphere(0.05, 44, 44);
	glPopMatrix();
}
void display() {
	float har, x, y, z;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glFrustum(left_x, right_x, -1.0, 1.0, 4.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(-1,0,0);
	gluLookAt(5+e_x, e_y+size-7 , 0 +e_z , 0+c_x , size+16+c_y , 0+c_z ,0 ,2, 0);
	
	//도로 그리기
	glRotated(90.0, 0.0, 1.0, 0.0);
	drawSquare(14.0, 1000.0, 10.0);
	
	for (int i = 0; i <  500; i=i+4) {
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(0.6, i, 0.1);
		drawSquare(2.0, 10.0, 10.0);
		glPopMatrix();
	}
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(5, 0, 0.1);
	drawSquare(14.0, 1000.0, 10.0);
	for (int i = 0; i < 500; i = i + 4) {
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(0.5, i, 0.1);
		drawSquare(2.0, 10.0, 10.0);
		glPopMatrix();
	}
	glPopMatrix();
	//하늘
	glPushMatrix();
		glColor3f(0, 0.0, Day);
		glTranslatef(-100, 100, 0);
		glRotated(90.0, 1.0, 0.0, 0.0);
		drawSquare(2000.0, 10000.0, 10.0);
		glTranslated(100, 0, 0);
		glRotatef(-(GLfloat)Time, 0.0, 0.0, 1.0);
		glPushMatrix();
			glTranslated(-8,0, 0);
			drawSun(1);
		glPopMatrix();
		glPushMatrix();
			glTranslated(8, 0, 0);
			drawMoon(1);
	glPopMatrix();
	glPopMatrix();
	//구름
	if (((int)Time % 360) < 180) {
		for (int i = 0; i < 2000; i = i + 20) {
			glPushMatrix();
			glTranslatef(-100 + i + Move, 99, 3);
			glRotated(90.0, 1.0, 0.0, 0.0);
			drawCloud(1);
			glPopMatrix();
		}
		for (int i = -100; i < 2000; i = i + 19) {
			glPushMatrix();
			glTranslatef(-100 + i - Move, 99, 5);
			glRotated(90.0, 1.0, 0.0, 0.0);
			drawCloud(1);
			glPopMatrix();
		}
	}
	// 별
	else if (((int)Time%360)>180 && ((int)Time%360)<360) {
		for (int i = 0; i < 2000; i = i + 19) {
			glPushMatrix();
			glTranslatef(-100 + i, 99.5, 2);
			glRotated(90.0, 1.0, 0.0, 0.0);
			drawStar();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-100 + i - 3, 99.5, 4);
			glRotated(90.0, 1.0, 0.0, 0.0);
			drawStar();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-100 + i + 4, 99.5, 6);
			glRotated(90.0, 1.0, 0.0, 0.0);
			drawStar();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-100 + i + 7, 99.5, 8);
			glRotated(90.0, 1.0, 0.0, 0.0);
			drawStar();
			glPopMatrix();
		}
	}
	//밑에 배경
	glPushMatrix();
	glColor3f(156 / 256.0, 91 / 256.0, 54 / 256.0);
	glTranslatef(-100, 99, -15);
	glRotated(90.0, 1.0, 0.0, 0.0);
	drawSquare(2000.0, 150.0, 10.0);
	glPopMatrix();
	//건물
	int count = 0;
	for (int i = 1; i < 100; i=i + 5) {
		glPushMatrix();
		glTranslatef(-1.2, i, 0);
		if(count%3==0)
		drawRectangle_1(10.0, 10.0, 10.0);
		else if(count%3==1)
			drawRectangle_2(10.0, 10.0, 30.0);
		else if(count%3==2)
			drawRectangle_3(10.0, 5.0, 20.0);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(13, i, 0);
		if (count % 3 == 0)
			drawRectangle_1(10.0, 10.0, 10.0);
		else if (count % 3 == 1)
			drawRectangle_2(10.0, 10.0, 30.0);
		else if (count % 3 == 2)
			drawRectangle_3(10.0, 5.0, 20.0);
		glPopMatrix();
		count++;
	}
	count = 0;
	for (int i = 1; i < 100; i = i + 5) {
		glPushMatrix();
		glTranslatef(-3.0, i, 0);
		if (count % 3 == 0)
			drawRectangle_2(10.0, 10.0, 30.0);
		else if (count % 3 == 1)
			drawRectangle_3(10.0, 5.0, 20.0);
		
		else if (count % 3 == 2)
			drawRectangle_1(10.0, 10.0, 10.0);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(10.0, i, 0);
		if (count % 3 == 0)
			drawRectangle_2(10.0, 10.0, 30.0);
		else if (count % 3 == 1)
			drawRectangle_3(10.0, 5.0, 20.0);

		else if (count % 3 == 2)
			drawRectangle_1(10.0, 10.0, 10.0);
		glPopMatrix();
		count++;
	}
	count = 0;
	for (int i = 1; i < 100; i = i + 5) {
		glPushMatrix();
		glTranslatef(-5.0, i, 0);
		if (count % 3 == 0)
			drawRectangle_3(10.0, 5.0, 20.0);
		else if (count % 3 == 1)	
			drawRectangle_1(10.0, 10.0, 10.0);
		else if (count % 3 == 2)
		drawRectangle_2(10.0, 10.0, 30.0);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(7.0, i, 0);
		if (count % 3 == 0)
			drawRectangle_3(10.0, 5.0, 20.0);
		else if (count % 3 == 1)
			drawRectangle_1(10.0, 10.0, 10.0);
		else if (count % 3 == 2)
			drawRectangle_2(10.0, 10.0, 30.0);
		glPopMatrix();
		count++;
	}
	//도로
	for (int i = 3; i < 100; i=i+3 ) {
		if (i%10==3||i%10==9){
		glColor3f(0.2, 0.2, 0.2);
		glPushMatrix();
		glTranslatef(-20, i, 0);	
		drawSquare(500.0, 14.0, 10.0);
		
		for (int j = -1; j < 74; j = j + 4) {
			glColor3f(1.0, 1.0, 1.0);
			glPushMatrix();
			glTranslatef(j, 0.5, 0.1);
			drawSquare(10.0, 2.0, 10.0);
			glPopMatrix();
		}
		glPopMatrix();
		}
	}
	//잔디
	
	glPushMatrix();
	glColor3f(89 / 256.0, 218.0 / 256.0, 80.0 / 256.0);
	glTranslatef(1.4, 0, -0.1);
	drawSquare(50.0, 1000.0, 10.0);
	glPopMatrix();
	//나무
	for (float i = 3.0; i < 24.0; i = i + 2.0) {
		glPushMatrix();
		glTranslatef(4.5, i + 8, 0);
		drawTree(2, i, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(1.5, i+8, 0);
		drawTree(2, i, 10);
		glPopMatrix();
	}
	for (float i = 64.0; i < 84.0; i = i + 2.0) {
		glPushMatrix();
		glTranslatef(4.2, i + 8, 0);
		drawTree2(2, i, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(1.8, i + 8, 0);
		drawTree2(2, i, 10);
		glPopMatrix();
	}
	//분수
	glPushMatrix();
		glTranslated(3.3, 48, -0.1);
		glColor3f(0.7, 0.7, 0.0);
		drawCylinder(16, 16, 5, 3, 3, 0.2, 0.6);
		glPushMatrix();
			glTranslated(0, 0, 0.1);
			drawCircle(16, 1);
		glPopMatrix();
		glPushMatrix();
			glTranslated(0.0, 0, 0.4);
			drawCylinder(14, 14, 4, 3, 3, 0.2, 0.6);
			glPushMatrix();
				glTranslated(0, 0, 0.1);
				drawCircle(14, 1);
			glPopMatrix();
					glPushMatrix();
						glColor4f(162 / 256.0, 246.0 / 256.0, 255.0 / 256.0, 0);
						glTranslated(0.0, 0, height/4);
						glutWireSphere(height/2.2, 33, 33);
					glPopMatrix();
					glPushMatrix();
						glTranslated(0.6, 0, height/2);
						glutWireSphere(height / 2, 33, 33);
					glPopMatrix();
					glPushMatrix();
						glTranslated(-0.6, 0, height / 2);
						glutWireSphere(height / 2, 33, 33);
					glPopMatrix();
					glPushMatrix();
						glTranslated(0, 0.6, height / 2);
						glutWireSphere(height / 2, 33, 33);
					glPopMatrix();
					glPushMatrix();
						glTranslated(0, -0.6, height / 2);
						glutWireSphere(height / 2, 33, 33);
					glPopMatrix();
					glPushMatrix();
						glTranslated(0, 0.0, height / 1.5);
						glutWireSphere(height / 2, 33, 33);
						glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
		glTranslated(3.3, 57, -0.1);
		glColor3f(0.7, 0.7, 0.0);
		drawCylinder(16, 16, 3, 3, 3, 0.2, 0.6);
		glPushMatrix();
		glTranslated(0, 0, 0.1);
		drawCircle(16, 1);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0.0, 0, 0.4);
		drawCylinder(14, 14, 4, 3, 3, 0.2, 0.6);
		glPushMatrix();
		glTranslated(0, 0, 0.1);
		drawCircle(14, 1);
		glPopMatrix();
		glPushMatrix();
		glColor4f(162 / 256.0, 246.0 / 256.0, 255.0 / 256.0, 0);
		glTranslated(0.0, 0, height / 4);
		glutWireSphere(height / 2.2, 33, 33);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0.6, 0, height / 2);
		glutWireSphere(height / 2, 33, 33);
		glPopMatrix();
		glPushMatrix();
		glTranslated(-0.6, 0, height / 2);
		glutWireSphere(height / 2, 33, 33);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, 0.6, height / 2);
		glutWireSphere(height / 2, 33, 33);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, -0.6, height / 2);
		glutWireSphere(height / 2, 33, 33);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0, 0.0, height / 1.5);
		glutWireSphere(height / 2, 33, 33);
		glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//가로등
	for (int i = 0; i < 200; i = i + 10) {
		glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslated(-0.1, i+2, 0);
			drawLoadStand(1, 1, 6);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslated(-3.5, i + 2, 0);
			drawLoadStand(1, 1, 6);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslated(6.5, i + 2, 0);
			drawLoadStand(1, 1, 6);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0, 0, 0);
			glTranslated(11.5, i + 2, 0);
			drawLoadStand(1, 1, 6);
		glPopMatrix();
	}
	//자동차
	glPushMatrix();
	glColor3f(171 / 256.0, 18 / 256.0, 94 / 256.0);
	glTranslated(0.1, 0+(carMove+1.5), 0);
	drawCar(3, 13, 2);
	glPopMatrix();
	glPushMatrix();
	glColor3f(171 / 256.0, 18 / 256.0, 94 / 256.0);
	glTranslated(5.1, 0 + carMove, 0);
	drawCar(3, 13, 2);
	glPopMatrix();
	//자동차2
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslated(0.8, 100- carMove, 0);
	drawCar2(4, 20, 3);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslated(5.8, 100-(carMove+1.5), 0);
	drawCar2(4, 20, 3);
	glPopMatrix();
	//타워
	glPushMatrix();
	glTranslated(-16,60,0);
	drawCylinder2(6.5, 6.5, 30, 30, 30);
	glPushMatrix();
	glTranslated(0, 0, 3);
	if (((int)Time % 360) < 180) {
		glColor3f(29 / 256.0, 219.0/156.0, 22.0 / 256.0);
	}
	else if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(0.8 + Move / 30, 0.8 + Move / 30, 0.8 + Move / 30);
	}
	
	drawCylinder2(15, 15, 12, 30, 30);
	glPushMatrix();
	glTranslated(0, 0, 1);
	if (((int)Time % 360) < 180) {
		glColor3f(243 / 256.0, 97.0 / 256.0, 220.0 / 256.0);
	}
	else if (((int)Time % 360) > 180 && ((int)Time % 360) < 360) {
		glColor3f(0.8 + Move / 20, 0, 0.0);
	}
	drawCylinder2(0, 15, 32, 30, 30);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//산
	glPushMatrix();
	glTranslated(-20, 20, 0);
	glColor3f(89 / 256.0, 180.0 / 256.0, 80.0 / 256.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 30.0, 0.0);
	glVertex3f(10.0, 10.0, 5);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-15, 50, 0);
	glColor3f(89 / 256.0,180.0 / 256.0, 80.0 / 256.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 50.0, 0.0);
	glVertex3f(5.0, 5.0, 5);
	glEnd();
	glPopMatrix();
	//빌딩
	glPushMatrix();
	glTranslated(10,50,0);
	glRotated(-30, 0, 0, 1);
	drawRectangle_4(65,20,65);
	glPopMatrix();
	glPushMatrix();
	glTranslated(15, 40, 0);
	glRotated(-30, 0, 0, 1);
	drawRectangle_4(65, 20, 65);
	glPopMatrix();
	glPopMatrix();
	glFlush();
	


}
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'a') {
		left_x -= 0.1;
		right_x -= 0.1;
	}
	if (key == 'd') {
		left_x += 0.1;
		right_x += 0.1;
	}
	if (key == 'w')
		size += 0.2;
	if (key == 's')
		size -= 0.2;
	if (key == 'x')
		c_y -= 1;
	if (key == 'X')
		c_y += 1;
	if(key == 'z')
		e_y -= 1;
	if (key == 'Z')
		e_y += 1;
	if (key == 'c')
		e_x -= 1;
	if (key == 'C')
		e_x += 1;
	if (key == 'v')
		c_x -= 1;
	if (key == 'V')
		c_x += 1;
	if (key == 'b')
		e_z -= 1;
	if (key == 'B')
		e_z += 1;
	if (key == 'n')
		c_z -= 1;
	if (key == 'N')
		c_z += 1;

}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Simple OpenGL Example");
	glutDisplayFunc(display);
	glutIdleFunc(move);
	
	glutKeyboardFunc(keyboard_handler);
	init();
	glutMainLoop();
	return 0;
}