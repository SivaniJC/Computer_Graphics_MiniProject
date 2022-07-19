#include<iostream>
#include<stdio.h>
#include<string>
#include<math.h>
#include<GL/glut.h>
using namespace std;

void myDisplay();
void myInit();

void plane();
void box();

std::string scoring;
int score = 0;
int start = 0;
int count_r = 0;

int x = 0;
int y = 0;

int win1, win2;

int px = 0;
int px1 = 0;
int px2 = 0;
int px3 = 0;
int py = 0;
int pyvmax = 0;
int pyvmin = 0;
int py1 = 0;
int py2 = 0;
int py3 = 0;

int bx = 0;
int bxmax = 0;
int bxmin = 0;
int by = 0;
int bymax = 0;
int bymin = 0;

void Write(float x, float y, float z, float scale, char* s)
{
	int i, l = strlen(s);
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	for (i = 0; i < l; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
	glPopMatrix();
}

void drawScore(const char* text) {
	int x = 280, y = 380;

	glColor3f(1, 0, 0);
	glRasterPos2f(x, y);
	while (*text) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
		text++;
	}
}

void drawGameOverText() {

	glColor3f(255, 0, 0);
	std::string str;

	str = "Game Over!!  Press R to Retry";

	const char* text = str.data();
	int length = str.size();
	int x = 200, y = 200;

	glColor3f(1, 0, 0);
	glRasterPos2f(x, y);
	while (*text) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
		text++;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		if (py1 > bymin && py1<bymax && px1>bxmin && px1 < bxmax)
		{
			bx = bx;
			by = by;
			count_r++;
		}
		else if (py2 > bymin && py2<bymax && px2>bxmin && px2 < bxmax)
		{
			bx = bx;
			by = by;
			count_r++;
		}
		else if (py3 > bymin && py3<bymax && px3>bxmin && px3 < bxmax)
		{
			bx = bx;
			by = by;
			count_r++;	
		}
		else if (pyvmax < 365)
		{
			py = py + 2;
			bx = bx - 8;
			if (bx < -600)
			{
				bx = 0;
				score++;
				by = rand() % 365;		//rand() is used to generate a series of random numbers.
			}
		}
		else if (bx < -600)
		{
			bx = 0;
			score++;
			by = rand() % 365;
		}
		else {
			bx = bx - 8;
		}
		glutPostRedisplay();
	}
	else if (key == 's')
	{
		if (py1 > bymin && py1<bymax && px1>bxmin && px1 < bxmax)
		{
			bx = bx;
			by = by;
			count_r++;	
		}
		else if (py2 > bymin && py2<bymax && px2>bxmin && px2 < bxmax)
		{
			bx = bx;
			by = by;
			count_r++;	
		}
		else if (py3 > bymin && py3<bymax && px3>bxmin && px3 < bxmax)
		{
			bx = bx;
			by = by;
			count_r++;	
		}
		else if (pyvmin > 0)
		{
			py = py - 2;
			bx = bx - 8;
			if (bx < -600)
			{
				bx = 0;
				score++;
				by = rand() % 365;
			}
		}
		else if (bx < -600)
		{
			bx = 0;
			score++;
			by = rand() % 365;
		}
		else {
			bx = bx - 8;
		}
		glutPostRedisplay();
	}
	else if (key == 'r')
	{
		py = 0;
		bx = 0;
		by = 0;
		score = 0;
		glutPostRedisplay();
	}
}

void plane()
{
	px1 = 250 + px;
	py1 = 340 + py;
	pyvmax = py1;
	pyvmin = 310 + py;
	px2 = 165 + px;
	py2 = pyvmin;
	px3 = 170 + px;
	py3 = py1;
	
	glColor3f(0.747, 0.747, 0.747);
	glBegin(GL_POLYGON);
	glVertex2i(px2, pyvmin);
	glVertex2i(px1, py1);
	glVertex2i(170 + px, 340 + py);
	glEnd();
	
	glColor3f(0.847, 0.847, 0.847);
	glBegin(GL_POLYGON);
	glVertex2i(160 + px, 330 + py);
	glVertex2i(250 + px, 340 + py);
	glVertex2i(px3, 340 + py);
	glEnd();
	
}

void box()
{
	bxmax = 600 + bx;
	bxmin = 550 + bx;
	bymax = 200 + by;
	bymin = 0 + by;

	glColor3f(0.59, 0.227, 0.207);
	glBegin(GL_POLYGON);
	glVertex2i(bxmin, bymin);
	glVertex2i(bxmax, bymin);
	glVertex2i(600 + bx, bymax);
	glVertex2i(550 + bx, bymax);
	glEnd();
}

void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

// game code
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	plane();
	box();
	scoring = " Score: " + std::to_string(score);
	drawScore(scoring.data());
	glEnd();
	if (count_r > 0) {
		drawGameOverText();
		count_r = 0;
	}
	glFlush();
}

void frontsheet(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	Write(-0.50, 0.9, 1, 0.0007, (char*)"Global Academy Of Technology");
	Write(-0.55, 0.8, 1, 0.0006, (char*)"    Department of CSE");
	
	glColor3f(1.0, 0.0, 0.0);
	Write(-0.45, 0.6, 0.0, 0.0007, (char*)" Paper Plane Game");
	
	glColor3f(1.0, 1.0, 0.5);
	Write(-1.0, 0.1, 0.0, 0.0007, (char*)" Submitted BY:");
	
	glColor3f(1.0, 1.0, 1.0);
	Write(-0.2, 0.10, 0.0, 0.0006, (char*)" Sivani JC 1GA19CS148");
	
	glColor3f(0.0, 0.0, 1.0);
	Write(-0.05, -0.5, 0.0, 0.0005, (char*)"Instructions:");
	glColor3f(0.0, 1.0, 0.0);
	Write(-0.05, -0.6, 0.0, 0.0005, (char*)"Press 's' to move downwards");
	Write(-0.05, -0.7, 0.0, 0.0005, (char*)"Press 'w' to move upwards");
	Write(-0.05, -0.8, 0.0, 0.0005, (char*)" Press 'c' to Play ");
	glFlush();
}
void keyboards(unsigned char key, int x4, int y4)
{
	if (key == 'c' || key == 'C')
	{
		glutDestroyWindow(win1);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(700, 500);
		glutInitWindowPosition(500, 200);
		win2 = glutCreateWindow("Paper Game");
		glFlush();
		glutDisplayFunc(myDisplay);
		glutKeyboardFunc(keyboard);
		myInit();
		glutMainLoop();
	}
}
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 400.0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 200);
	win1 = glutCreateWindow("CG Mini project");
	glFlush();
	glutDisplayFunc(frontsheet);
	glutKeyboardFunc(keyboards);
	glutMainLoop();
}
