/*
 * Edge.h
 *
 *  Created on: Sep 16, 2012
 *      Author: prathamesh
 */

#ifndef EDGE_H_
#define EDGE_H_

#include "Vertex.h"
#include <cmath>

class Face;

class Edge
{
public:
	Edge();
	// Default class constructor.

	Edge(Vertex *vertex1, Vertex *vertex2);
	// Construction of an edge by passing addresses of the two vertices that define it.

	~Edge();
	// Default class destructor.

	double computeLength(void);
	// Computes current length of the edge by calculating the distance between the two vertices.

	void computeSpringForce(void);
	// Computes the force exerted by the edge (spring force) using Hooke's law.

	void computeSpringStiffness(void);
	// Computes the stiffness of the spring represented by this edge.

	Vertex *v1;
	Vertex *v2;
	// Addresses of the two vertices that form this edge.

	double originalLength;
	// Original length of this edge.

	double currentLength;
	// Present length of this edge.

	double springStiffness;
	// Spring stiffness (k value) of this edge.

	double springForce[3];
	// Force exerted by the edge.

	double modulus;
	// Young's modulus.

	double thickness;
	// Thickness of each face element.

	vector<Face*> connectedFaces;
	// Faces connected to this edge. Only 2.

	void addConnectedFace(Face*);
	// Adds a connected face.
};

#include "Face.h"

#endif /* EDGE_H_ */
