/*
 * Face.h
 *
 *  Created on: Sep 16, 2012
 *      Author: prathamesh
 */

#ifndef FACE_H_
#define FACE_H_

#include "Vertex.h"

class Face
{
public:
	Face();
	// Default class constructor

	Face(Vertex *vertex1, Vertex *vertex2, Vertex *vertex3);
	// Construction of face by passing addresses of the three vertices that define it.

	Face(Vertex *vertex1, Vertex *vertex2, Vertex *vertex3, double *norm);
	// Construction of face by passing addresses of the three vertices and the normal vector that define it.

	~Face();
	// Default class destructor.

	Vertex *v1;
	Vertex *v2;
	Vertex *v3;
	// Addresses of the vertices that define the face.

	double normal[3];
	// Normal vector for the face.

	double edgeLength[3];

	double semiperimeter;

	double faceArea;

	void computeLengths(void);
    // Compute length of the face edges.

	double computeArea(void);
    // Compute area of the face.

};

#endif /* FACE_H_ */
