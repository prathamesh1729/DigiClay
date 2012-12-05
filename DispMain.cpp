/*
 * DispMain.cpp
 *
 *  Created on: Oct 9, 2012
 *      Author: prathamesh
 */

#include <GL/glut.h>
#include "Object.h"

int nMainWnd = -1;
GLfloat windowWidth, windowHeight;

GLfloat LightDiffuse[]= { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat LightPosition[]= { 3.0f, 3.0f, 0.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
GLfloat light_ambient[]= { 0.0f, 0.0f, 1.0f, 1.0f };

GLfloat xRotated, yRotated, zRotated;

int anchorX = 0, anchorY = 0;
bool rotation = false;
bool translation = false;
bool zoom = false;

Object obj;

double force[] = {-1.0, -1.0, -1.0};

void panView(float x, float y, float z)
{

	glMatrixMode( GL_PROJECTION );
	glTranslatef(x, y, z);
	glMatrixMode( GL_MODELVIEW );

}

void rotateView(float angle, float x, float y, float z)
{
	double m[ 16 ];
	glMatrixMode( GL_MODELVIEW );
	glGetDoublev( GL_MODELVIEW_MATRIX, m );
	glLoadIdentity();
	glRotatef( angle, x, y, z );
	glMultMatrixd( m );
}

void scaleView(double factor)
{
	glMatrixMode( GL_PROJECTION );
	glOrtho( -factor, factor, -factor, factor, 1, -1 );
	//glScalef(factor, factor, factor);
	glMatrixMode( GL_MODELVIEW );
}

void initGL(void)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void resizeGL(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	//if (w <= h)glOrtho (-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w,5.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	//else glOrtho (-5.0*(GLfloat)w/(GLfloat)h,5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -10.0, 10.0);
	//if (w <= h)glOrtho (-100.0, 100.0, -100.0*(GLfloat)h/(GLfloat)w, 100.0*(GLfloat)h/(GLfloat)w, -200.0, 200.0);
	//else glOrtho (-100.0*(GLfloat)w/(GLfloat)h, 100.0*(GLfloat)w/(GLfloat)h, -100.0, 100.0, -200.0, 200.0);
	//Part1.stl
	if (w <= h)glOrtho (-50.0, 50.0, -50.0*(GLfloat)h/(GLfloat)w,50.0*(GLfloat)h/(GLfloat)w, -50.0, 50.0);
	else glOrtho (-50.0*(GLfloat)w/(GLfloat)h,50.0*(GLfloat)w/(GLfloat)h, -50.0, 50.0, -50.0, 50.0);
	//Magnolia
	//if (w <= h)glOrtho (-100.0, 100.0, -100.0*(GLfloat)h/(GLfloat)w,100.0*(GLfloat)h/(GLfloat)w, -100.0, 100.0);
	//else glOrtho (-100.0*(GLfloat)w/(GLfloat)h,100.0*(GLfloat)w/(GLfloat)h, -100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void displayGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 1.0);
	glLoadIdentity();
	glTranslatef(0.0,0.0,0.0);
	glRotatef(xRotated,1.0,0.0,0.0);
	glRotatef(yRotated,0.0,1.0,0.0);
	glRotatef(zRotated,0.0,0.0,1.0);
	//glutSolidSphere(3.0, 50, 50);

	list<Face>::iterator it;
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_TRUE);

	for(it = obj.faceList.begin(); it != obj.faceList.end(); it++)
	{
		glNormal3d(it->normal[0], it->normal[1], it->normal[2]);
		glVertex3d(it->v1->x, it->v1->y, it->v1->z);
		glVertex3d(it->v2->x, it->v2->y, it->v2->z);
		glVertex3d(it->v3->x, it->v3->y, it->v3->z);
	}
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void idleGL(void)
{
	obj.UpdateAll();
	displayGL();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:
		glutDestroyWindow(nMainWnd);
		exit(0);
		break;
	case 'a':
		xRotated += 5.0;
		//rotateView(xRotated, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case 'd':
		xRotated -= 5.0;
		//rotateView(xRotated, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case 'w':
		yRotated += 5.0;
		//rotateView(yRotated, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case 's':
		yRotated -= 5.0;
		//rotateView(yRotated, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case 'q':
		zRotated += 5.0;
		//rotateView(zRotated, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case 'e':
		zRotated -= 5.0;
		//rotateView(zRotated, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case 'u':
		obj.UpdateAll();
		glutPostRedisplay();
		break;
	}
}

void processSpecialKeys(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		//panView(0.0f, 0.25f, 0.0f);
		panView(0.0f, 2.0f, 0.0f);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		//panView(0.0f, -0.25f, 0.0f);
		panView(0.0f, -2.0f, 0.0f);
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		//panView(-0.25f, 0.0f, 0.0f);
		panView(-2.0f, 0.0f, 0.0f);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		//panView(0.25f, 0.0f, 0.0f);
		panView(2.0f, 0.0f, 0.0f);
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_UP:
		scaleView(1.1f);
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		scaleView(0.9f);
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char **argv)
{

	char filename[] = "Part1.stl";
	obj.CompactParseFile(filename, obj.vertexList, obj.faceList, obj.edgeList);
	obj.ComputeBoundingBox(obj.boundingBox);
	obj.PrintVertices(obj.vertexList);
	obj.PrintFaces(obj.faceList);
	obj.PrintEdges(obj.edgeList);
	cout<<obj.vertexList.size()<<endl;
	cout<<obj.edgeList.size()<<endl;
	cout<<obj.faceList.size()<<endl;

	obj.ConstrainVertex(obj.vertexList, Vertex(-20, -20, -20));
	obj.ConstrainVertex(obj.vertexList, Vertex(-20, -20, 20));
	//obj.ConstrainVertex(obj.vertexList, Vertex(-20, 20, -20));
	//obj.ConstrainVertex(obj.vertexList, Vertex(-20, 20, 20));
	//obj.ConstrainVertex(obj.vertexList, Vertex(20, -20, 20));
	//obj.ConstrainVertex(obj.vertexList, Vertex(20, -20, -20));
	//obj.ConstrainVertex(obj.vertexList, Vertex(20, 20, -20));
	obj.ApplyExternalForce(obj.vertexList, Vertex(20, 20, 20), force);

	//Magnolia
	//obj.ConstrainVertex(obj.vertexList, Vertex(65.9253, -18.547, 9.9605));
	//obj.ConstrainVertex(obj.vertexList, Vertex(57.2781, -16.2601, -1.6234));
	//obj.ConstrainVertex(obj.vertexList, Vertex(24.7862, -11.5467, 9.174));
	//obj.ConstrainVertex(obj.vertexList, Vertex(8.7474, -11.0052, 0.8503));
	//obj.ApplyExternalForce(obj.vertexList, Vertex(-1.1186, -17.7861, 3.1771), force);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(300,300);
	nMainWnd = glutCreateWindow("Simple Display");

	xRotated = yRotated = zRotated = 0.0;

	initGL();
	glutDisplayFunc(displayGL);
	glutReshapeFunc(resizeGL);
	glutIdleFunc(idleGL);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();

	return 0;
}
