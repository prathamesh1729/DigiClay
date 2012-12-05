/*
 * Main.cpp
 *
 *  Created on: Sep 19, 2012
 *      Author: prathamesh
 */

/*
#include <GL/glut.h>
#include "Object.h"

int nMainWnd = -1;
GLfloat zoom = 1.0;
GLfloat translateX = 0.0;
GLfloat translateY = 0.0;
GLfloat translateZ = 0.0;
GLfloat angleX = 0;
GLfloat angleY = 0;
GLfloat angleZ = 0;
GLfloat magnitude = 0.1;

GLfloat LightAmbient[]= { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat LightDiffuse[]= { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat LightPosition[]= { 3.0f, 3.0f, 0.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

double xextent = 10;
double yextent = 10;
double zextent = 10;
double sphereRadius = 10;

Object obj;
double force[] = {1.0, 1.0, 1.0};

void display(){

	//obj.UpdateAll();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 1.0);

	glLoadIdentity();
	//gluLookAt(80.0, 80.0, 80.0, 50.0, 50.0, 50.0, 0.0, 0.1, 0.0);
	//gluLookAt(obj.boundingBox[3] + (GLfloat)50, obj.boundingBox[4] + (GLfloat)50, obj.boundingBox[5] + (GLfloat)50, (obj.boundingBox[0] + obj.boundingBox[3])/2, (obj.boundingBox[1] + obj.boundingBox[4])/2, (obj.boundingBox[2] + obj.boundingBox[5])/2, 0.0, 0.1, 0.0);
	//gluLookAt(5.0, 5.0, 5.0, 1.0, 1.0, 1.0, 0.0, 0.1, 0.0);
	glScalef(zoom, zoom, zoom);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 1.0);
	glTranslatef(translateX, translateY, translateZ);


	list<Face>::iterator it;
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_TRUE);

	for(it = obj.faceList.begin(); it != obj.faceList.end(); it++)
	{
		//glColor3f((GLfloat)rand()/RAND_MAX, (GLfloat)rand()/RAND_MAX, (GLfloat)rand()/RAND_MAX);
		glNormal3d(it->normal[0], it->normal[1], it->normal[2]);
		glVertex3d(it->v1->x, it->v1->y, it->v1->z);
		glVertex3d(it->v2->x, it->v2->y, it->v2->z);
		glVertex3d(it->v3->x, it->v3->y, it->v3->z);
	}
	glEnd();

	//Nest comment
	glutWireCube(1.0);
	glutWireSphere(3.0, 10, 10);


	glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 3.0, 0.0);
		glVertex3f(2.0, 3.0, 0.0);
		glVertex3f(3.0, 1.5, 0.0);
		glVertex3f(4.0, 0.0, 0.0);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, 4.0, 4.0);
		glVertex3f(-1.0, 3.0, 1.0);
		glVertex3f(2.0, 3.0, -2.0);
	glEnd();
	//End Nest Comment
	glFlush();

}

void displayGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 1.0);

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
}

void dynDisplay(void)
{
	obj.UpdateAll();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	//glLoadIdentity();
	//glScalef(zoom, zoom, zoom);
	//glRotatef(angleX, 1.0, 0.0, 0.0);
	//glRotatef(angleY, 0.0, 1.0, 0.0);
	//glRotatef(angleZ, 0.0, 0.0, 1.0);
	//glTranslatef(translateX, translateY, translateZ);

	list<Face>::iterator it;
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_TRUE);

	for(it = obj.faceList.begin(); it != obj.faceList.end(); it++)
	{
		//glColor3f((GLfloat)rand()/RAND_MAX, (GLfloat)rand()/RAND_MAX, (GLfloat)rand()/RAND_MAX);
		glNormal3d(it->normal[0], it->normal[1], it->normal[2]);
		glVertex3d(it->v1->x, it->v1->y, it->v1->z);
		glVertex3d(it->v2->x, it->v2->y, it->v2->z);
		glVertex3d(it->v3->x, it->v3->y, it->v3->z);
	}
	glEnd();
	glFlush();
}

void init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0*magnitude, 100.0*magnitude, -100.0*magnitude, 100.0*magnitude, -100.0*magnitude, 100.0*magnitude);
	/////glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	//glOrtho((obj.boundingBox[0] - 50), (obj.boundingBox[3] + 50), (obj.boundingBox[1] - 50), (obj.boundingBox[4] + 50), (obj.boundingBox[2] - 50), (obj.boundingBox[5] + 50));
	//glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);

}

void initGL()
{
	xextent = obj.boundingBox[3] - obj.boundingBox[0];
	yextent = obj.boundingBox[4] - obj.boundingBox[1];
	zextent = obj.boundingBox[5] - obj.boundingBox[2];
	sphereRadius = sqrt(xextent * xextent + yextent * yextent + zextent * zextent);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:
		glutDestroyWindow(nMainWnd);
		exit(0);
		break;
	case 'z':
		zoom += 0.1;
		glutPostRedisplay();
		break;
	case 'x':
		zoom -= 0.1;
		glutPostRedisplay();
		break;
	case 'c':
		zoom -= 0.1;
		glutPostRedisplay();
		break;
	case 'a':
		translateX -= 10.0 * magnitude;
		glutPostRedisplay();
		break;
	case 'd':
		translateX += 10.0 * magnitude;
		glutPostRedisplay();
		break;
	case 'w':
		translateY += 10.0 * magnitude;
		glutPostRedisplay();
		break;
	case 's':
		translateY -= 10.0 * magnitude;
		glutPostRedisplay();
		break;
	case 'k':
		translateZ += 10.0 * magnitude;
		glutPostRedisplay();
		break;
	case 'j':
		translateZ -= 10.0 * magnitude;
		glutPostRedisplay();
		break;
	case '1':
		angleX += 10.0;
		glutPostRedisplay();
		break;
	case '2':
		angleX -= 10.0;
		glutPostRedisplay();
		break;
	case '3':
		angleY += 10.0;
		glutPostRedisplay();
		break;
	case '4':
		angleY -= 10.0;
		glutPostRedisplay();
		break;
	case '5':
		angleZ += 10.0;
		glutPostRedisplay();
		break;
	case '6':
		angleZ -= 10.0;
		glutPostRedisplay();
		break;
	case 'u':
		glutPostRedisplay();
		break;
	}
}

void dynProcessNormalKeys(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:
		glutDestroyWindow(nMainWnd);
		exit(0);
		break;
	case 'z':
		//zoom += 0.1;
		glScalef(1.1f, 1.1f, 1.1f);
		glutPostRedisplay();
		break;
	case 'x':
		//zoom -= 0.1;
		glScalef(0.9f, 0.9f, 0.9f);
		glutPostRedisplay();
		break;
	case 'c':
		//zoom -= 0.1;
		glScalef(0.9f, 0.9f, 0.9f);
		glutPostRedisplay();
		break;
	case 'a':
		//translateX -= 10.0 * magnitude;
		glTranslatef(-0.1f, 0.0f, 0.0f);
		glutPostRedisplay();
		break;
	case 'd':
		//translateX += 10.0 * magnitude;
		glTranslatef(0.1f, 0.0f, 0.0f);
		glutPostRedisplay();
		break;
	case 'w':
		//translateY += 10.0 * magnitude;
		glTranslatef(0.0f, 0.1f, 0.0f);
		glutPostRedisplay();
		break;
	case 's':
		//translateY -= 10.0 * magnitude;
		glTranslatef(0.0f, -0.1f, 0.0f);
		glutPostRedisplay();
		break;
	case 'k':
		//translateZ += 10.0 * magnitude;
		glTranslatef(0.0f, 0.0f, 0.1f);
		glutPostRedisplay();
		break;
	case 'j':
		//translateZ -= 10.0 * magnitude;
		glTranslatef(0.0f, 0.0f, -0.1f);
		glutPostRedisplay();
		break;
	case '1':
		//angleX += 10.0;
		glRotatef(10.0, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case '2':
		//angleX -= 10.0;
		glRotatef(-10.0, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case '3':
		//angleY += 10.0;
		glRotatef(10.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case '4':
		//angleY -= 10.0;
		glRotatef(-10.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case '5':
		//angleZ += 10.0;
		glRotatef(10.0, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case '6':
		//angleZ -= 10.0;
		glRotatef(-10.0, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case 'u':
		glutPostRedisplay();
		break;
	}
}

void processSpecialKeys(int key, int x, int y)
{
}

void mouseHandler(int button, int state, int x, int y)
{

}

void mouseMoveHandler(int x, int y)
{

}

void changeSize(int w, int h)
{

	if (h==0)
	{
		h=1;
	}

	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	GLfloat width = (GLfloat)w;
	GLfloat height = (GLfloat)h;
	//glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
	//glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);

	glOrtho(-200.0*magnitude*(width)/(width + height), 200.0*magnitude*(width)/(width + height), -200.0*magnitude*(height)/(width + height), 200.0*magnitude*(height)/(width + height), -100.0*magnitude, 100.0*magnitude);
	/////glOrtho(-20.0*(width)/(width + height), 20.0*(width)/(width + height), -20.0*(height)/(width + height), 20.0*(height)/(width + height), -10.0, 10.0);
	//glOrtho((obj.boundingBox[0] - 50), (obj.boundingBox[3] + 50), (obj.boundingBox[1] - 50), (obj.boundingBox[4] + 50), (obj.boundingBox[2] - 50), (obj.boundingBox[5] + 50));
	//glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

}

void initL()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}

void displayL()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidSphere (1.0, 20, 16);
	glFlush ();
}

void reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	glOrtho (-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w,
	5.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
	else
	glOrtho (-5.0*(GLfloat)w/(GLfloat)h,
	5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void reshapeGL(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	GLfloat xview = GLfloat(w)/min(GLfloat(w),GLfloat(h))*sphereRadius;
	GLfloat yview = GLfloat(h)/min(GLfloat(w),GLfloat(h))*sphereRadius;
	glOrtho(-1.0 * xview, xview, -1.0 * yview, yview, sphereRadius, -1.0 * sphereRadius);

	glMatrixMode(GL_MODELVIEW);

}

void scaleView(double factor)
{
	glMatrixMode( GL_PROJECTION );
	glOrtho( -factor, factor, -factor, factor, 1, -1 );
	glMatrixMode(GL_MODELVIEW);
}

void panView(double x, double y)
{
	glMatrixMode( GL_PROJECTION );
	glTranslated(x, y, 0);
	glMatrixMode(GL_MODELVIEW);

}

void rotateView(double x, double y, double z, double angle)
{
	double m[ 16 ];
	glMatrixMode( GL_MODELVIEW );
	glGetDoublev( GL_MODELVIEW_MATRIX, m );
	glLoadIdentity();
	glRotated( angle, x, y, z );
	glMultMatrixd( m );
	glMatrixMode(GL_MODELVIEW);

}


int main(int argc, char** argv){

	char filename[] = "Moon.stl";
	obj.ParseFile(filename, obj.vertexList, obj.faceList, obj.edgeList);
	obj.ComputeBoundingBox(obj.boundingBox);
	obj.PrintVertices(obj.vertexList);
	obj.PrintFaces(obj.faceList);
	obj.PrintEdges(obj.edgeList);
	cout<<obj.vertexList.size()<<endl;
	cout<<obj.faceList.size()<<endl;

	obj.ConstrainVertex(obj.vertexList, Vertex(0.308658, 0.46194, 1.5));
	obj.ConstrainVertex(obj.vertexList, Vertex(0.94054, 0.191342, 2.85066));
	obj.ConstrainVertex(obj.vertexList, Vertex(1, 0, 1.5));
	obj.ApplyExternalForce(obj.vertexList, Vertex(0.114181, 0, 2.07403), force);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(300,300);
	nMainWnd = glutCreateWindow("Simple Display");

	init();
	glutDisplayFunc(dynDisplay);
	glutKeyboardFunc(dynProcessNormalKeys);
	glutMouseFunc(mouseHandler);
	glutMotionFunc(mouseMoveHandler);

	glutReshapeFunc(reshape);
	//glutIdleFunc(display);
	//glutSpecialFunc(processSpecialKeys);

	glutMainLoop();
	return 0;
}
*/
