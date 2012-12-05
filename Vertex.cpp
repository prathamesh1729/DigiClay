/*
 * Vertex.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: prathamesh
 */

#include "Vertex.h"

Vertex::Vertex()
{

}

Vertex::Vertex(double xvalue, double yvalue, double zvalue)
{
	x = xvalue;
	y = yvalue;
	z = zvalue;

	//Elaborate construction
	xprev = xvalue;
	yprev = yvalue;
	zprev = zvalue;

	xnew = 0;
	ynew = 0;
	znew = 0;

	mass = 1.0;
	deltaT = 0.001;

	externalForce[0] = 0;
	externalForce[1] = 0;
	externalForce[2] = 0;

	totalForce[0] = 0;
	totalForce[1] = 0;
	totalForce[2] = 0;

	constrained = false;
}

Vertex::~Vertex()
{

}

double Vertex::computeTotalForce(int i)
{
	double totalSpringForce = 0;
	vector<pair<Edge*, int> >::iterator it;
	for(it = connectedEdges.begin(); it != connectedEdges.end(); it++)
	{
		totalSpringForce += ((((*it).first)->springForce[i]) * (*it).second * (-1));
	}

	totalForce[i] = externalForce[i] - totalSpringForce;
	return(totalForce[i]);
}

void Vertex::computeTotalForce(void)
{
	computeTotalForce(0);
	computeTotalForce(1);
	computeTotalForce(2);
}

void Vertex::computeNew(void)
{
	if(!constrained)
	{
		xnew = totalForce[0] * deltaT * deltaT / mass + 2 * x - xprev;
		ynew = totalForce[1] * deltaT * deltaT / mass + 2 * y - yprev;
		znew = totalForce[2] * deltaT * deltaT / mass + 2 * z - zprev;

		xprev = x;
		yprev = y;
		zprev = z;
		x = xnew;
		y = ynew;
		z = znew;
	}
}

void Vertex::addConnectedEdge(Edge* e, int flag)
{
	pair<Edge*, int> cE(e, flag);
	connectedEdges.push_back(cE);
}
