/*
 * Face.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: prathamesh
 */

#include "Face.h"

Face::Face()
{

}

Face::Face(Vertex *vertex1, Vertex *vertex2, Vertex *vertex3)
{
	v1 = vertex1;
	v2 = vertex2;
	v3 = vertex3;
}

Face::Face(Vertex *vertex1, Vertex *vertex2, Vertex *vertex3, double *norm)
{
	v1 = vertex1;
	v2 = vertex2;
	v3 = vertex3;

	normal[0] = norm[0];
	normal[1] = norm[1];
	normal[2] = norm[2];

	faceArea=computeArea();
}

Face::~Face()
{

}

void Face::computeLengths(void)
{
	edgeLength[0] = sqrt((v1->x - v2->x)*(v1->x - v2->x) + (v1->y - v2->y)*(v1->y - v2->y) + (v1->z - v2->z)*(v1->z - v2->z));
	edgeLength[1] = sqrt((v2->x - v3->x)*(v2->x - v3->x) + (v2->y - v3->y)*(v2->y - v3->y) + (v2->z - v3->z)*(v2->z - v3->z));
	edgeLength[2] = sqrt((v3->x - v1->x)*(v3->x - v1->x) + (v3->y - v1->y)*(v3->y - v1->y) + (v3->z - v1->z)*(v3->z - v1->z));
	semiperimeter = (edgeLength[0]+ edgeLength[1]+ edgeLength[2])/2;
}

double Face::computeArea(void)
{
    computeLengths();
    faceArea = sqrt(semiperimeter*(semiperimeter-edgeLength[0])*(semiperimeter-edgeLength[1])*(semiperimeter-edgeLength[2]));
    return faceArea;
}
