/*
 * Vertex.h
 *
 *  Created on: Sep 16, 2012
 *      Author: prathamesh
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

//#include "Edge.h"
#include <vector>
#include <list>
#include <utility>

using namespace std;

class Edge;

class Vertex
{
public:
	Vertex();
	// Default class constructor

	Vertex(double xvalue, double yvalue, double zvalue);
	// Vertex construction with its x, y, z values

	~Vertex();
	// Default class destructor

	double computeTotalForce(int);
	// Computes the total force in specified direction at the vertex and returns the value.
	// 0: x direction force, 1: y direction force, 2: z direction force.
	// Total force is computed from the external force acting on the vertex and
	// the spring forces (of the connected edges) acting on the vertex.

	void computeTotalForce(void);
	// Computes total force in x, y, z and stores it in the totalForce variable.

	void computeNew(void);
	// Computes new coordinates of the vertex from the current and previous coordinates.
	// Step of Verlet integration.

	void addConnectedEdge(Edge* e, int flag);
	// Adds a connected edge to this vertex.
	// A connected edge is an edge that has this vertex as one of its end points.

	double x;
	double y;
	double z;
	// Current coordinates of the Vertex.

	double xprev;
	double yprev;
	double zprev;
	// Previous coordinates of the Vertex.

	double xnew;
	double ynew;
	double znew;
	// Newly computed coordinates of the Vertex.

	double mass;
	// Mass concentrated at the Vertex. Default value 1.0.

	double deltaT;
	// Time step for computation. Default value is 0.01.

	double externalForce[3];
	// External force acting on the vertex. Set using applyExternalForce method in Object class.
	// Default value is (0, 0, 0).

	double totalForce[3];
	// Total force acting on the vertex. Computed using the external force and
	// spring force due to connected edges.
	// Initial value is zero.

	bool constrained;
	// Decides if the  vertex is constrained (rigid/fixed). Default value if false.
	// Can be set using constrainVertex method in Object class.

	vector<pair<Edge*, int> > connectedEdges;
	// Vector of pairs. Each pair contains a pointer to a connected edge and a flag.
	// Flag is 1 if the connected edge has this vertex as v1.
	// Flag is -1 if the connected edge has this vertex as v2.
	// Flag is needed to decide the sign of the spring force due a connected edge.

};

#include "Edge.h"

#endif /* VERTEX_H_ */
