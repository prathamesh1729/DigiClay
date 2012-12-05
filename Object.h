/*
 * Object.h
 *
 *  Created on: Sep 17, 2012
 *      Author: prathamesh
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Vertex.h"
#include "Face.h"
#include "Edge.h"
#include <list>
#include <vector>

using namespace std;

class Object
{
public:
	list<Vertex> vertexList;
	// List of all unique vertices that define the object.
	// Vertices are stored in the vertexList list in ascending order of X, Y, Z coordinates respectively
	// Obtained when STL file is parsed and repeated vertices are filtered out.

	list<Face> faceList;
	// List of all unique faces that define the object.
	// Obtained directly when STL file is parsed.

	list<Edge> edgeList;
	// List of all unique edges that define the object.
	// Obtained when STL file is parsed and repeated edges are filtered out.

	vector<Vertex*> addrList;
	// Vector containing the addresses of vertexList elements.
	// Addresses are arranged in a sequence from the first vertexList element to the last.
	// addrList is populated when all vertices are inserted into the vertexList.
	// This is for quick access to vertices in the vertexList. (As the list does not support 'random' access)

	double boundingBox[6];
	// Elements: X min, Y min, Z min, X max, Y max, Z max.
	// Bounding box of the object read from STL file.
	// Computed after STL file is parsed.
	// Useful for display purposes.


	Object();
	~Object();
	// Default class constructor and destructor

	Vertex* InsertVertexDB(list<Vertex> &vchain, Vertex v, int &flag);
	// Inserts Vertex v into the list vchain.
	// Returns the address of the vertex after insertion into the list.
	// flag becomes 1 in case of repeated vertex. 0 otherwise.

	Edge* InsertEdgeDB(list<Edge> &echain, Vertex *v1, Vertex *v2);
	// Inserts Edge comprising of vertices v1 and v2 into the list echain.
	// Also inserts the corresponding edge as a connected edge in the two vertices v1 and v2.

	void PrintVertices(list<Vertex> &vchain);
	// Prints x, y, z coordinates of all vertices in the list vchain.

	void PrintFaces(list<Face> &fchain);
	// Prints x, y, z coordinates of all three vertices of all the faces in the list fchain.

	void PrintEdges(list<Edge> &echain);
	// Prints x, y, z coordinates of the two vertices of all the edges in the list echain.

	int ParseFile(char *fp, list<Vertex> &vchain, list<Face> &fchain, list<Edge> &echain);
	int NewParseFile(char *fp, list<Vertex> &vchain, list<Face> &fchain, list<Edge> &echain);
	int CompactParseFile(char *fp, list<Vertex> &vchain, list<Face> &fchain, list<Edge> &echain);
	// Parses STL file referred to by file pointer fp.
	// Data is extracted from the file in the form of faces, edges and vertices.
	// Faces are stored in the list fchain.
	// Edges are stored in the list echain. (Repeated edges are saved only once)
	// Vertices are stored in the list vchain. (Repeated vertices are saved only once)

	void ComputeBoundingBox(double *bBox);
	// Computes the bounding box of the Object. Incorrect function - do not use.
	// Useful for display.

	void UpdateAll(void);
	// Updates all vertices for the current timestep.
	// Carries out the steps for Verlet integration.
	// 1. Calculate the edge (spring) lengths and compute the spring force for each edge
	// 2. Compute the total force at each vertex.
	// 3. Calculate the new coordinates of the vertex using the time-step formula.

	int ConstrainVertex(list<Vertex> &vchain, Vertex v);
	// Constrains vertex v.
	// Checks if the vertex v is present in the list vchain.
	// If present, it sets the constrained flag.

	int ApplyExternalForce(list<Vertex> &vchain, Vertex v, double *extForce);
	// Applies external force of value given by extForce at vertex v.
};

#endif /* OBJECT_H_ */
