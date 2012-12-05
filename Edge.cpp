/*
 * Edge.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: prathamesh
 */

#include "Edge.h"

Edge::Edge()
{

}

Edge::Edge(Vertex *vertex1, Vertex *vertex2)
{
	v1 = vertex1;
	v2 = vertex2;

	originalLength = computeLength();
	springStiffness = 1.0;
	modulus = 1.0;
	thickness = 1.0;

	springForce[0] = 0;
	springForce[1] = 0;
	springForce[2] = 0;
}

Edge::~Edge()
{

}

double Edge::computeLength(void)
{
	currentLength = sqrt((v1->x - v2->x)*(v1->x - v2->x) + (v1->y - v2->y)*(v1->y - v2->y) + (v1->z - v2->z)*(v1->z - v2->z));
	return currentLength;
}

void Edge::computeSpringForce(void)
{
	springForce[0] = springStiffness * (currentLength - originalLength) / currentLength * (v2->x - v1->x);
	springForce[1] = springStiffness * (currentLength - originalLength) / currentLength * (v2->y - v1->y);
	springForce[2] = springStiffness * (currentLength - originalLength) / currentLength * (v2->z - v1->z);
}

void Edge::addConnectedFace(Face *f)
{
	cout<<"Connected faces - size before: "<<connectedFaces.size()<<endl;
	connectedFaces.push_back(f);
	cout<<"Connected faces - size after: "<<connectedFaces.size()<<endl;
}

void Edge::computeSpringStiffness(void)
{
	computeLength();
	springStiffness = 0;
	for(unsigned int i = 0; i < connectedFaces.size(); i++)
	{
		springStiffness += modulus * thickness * (connectedFaces[i]->computeArea()) / (currentLength * currentLength);
	}
}
