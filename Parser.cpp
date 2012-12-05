/*
 * stl-parser.cpp
 *
 *  Created on: Sep 15, 2012
 *      Author: prathamesh
 */

/*
 * Test file. Now redundant.
 * Functions in this file have been incorporated into the object class.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Vertex.h"
#include "Face.h"
#include "Edge.h"
#include <vector>
#include <list>

using namespace std;

//vector<Vertex> vertexList;
//vector<Face> faceList;
list<Vertex> vList;
list<Face> fList;
list<Edge> eList;
vector<Vertex*> addrList;

Vertex* InsertVertexDB(list<Vertex> &vchain, Vertex v, int &flag);
int ParseFile(char *fp, list<Vertex> &vchain, list<Face> &fchain, list<Edge> &echain);
void PrintVertices(list<Vertex> &vchain);
void PrintFaces(list<Face> &fchain);
void PrintEdges(list<Edge> &echain);

/*
int main()
{
	string currentLine;
	size_t blank1;
	size_t blank2;
	size_t blank3;
	int triangleNumber = 0;
	//int vertexCount = 0;
	//int faceCount = 0;

	ifstream stlFile("femur.STL");
	if(stlFile.is_open())
	{
		while(stlFile.good())
		{
			getline(stlFile, currentLine);
			currentLine.erase(0, currentLine.find_first_not_of(" "));

			if(currentLine.find("facet")!=string::npos)
			{
				blank1 = currentLine.find("normal") + 6;
				blank2 = currentLine.find(" ", blank1 + 1);
				blank3 = currentLine.find(" ", blank2 + 1);

				normal[0] = atof(currentLine.substr(blank1+1, blank2-1).c_str());
				normal[1] = atof(currentLine.substr(blank2+1, blank3-1).c_str());
				normal[2] = atof(currentLine.substr(blank3+1).c_str());

				//cout<<triangleNumber<<endl;
				//cout<<normal[0]<<" "<<normal[1]<<" "<<normal[2]<<endl;

				getline(stlFile, currentLine);
				if(currentLine.find("outer loop")!=string::npos)
				{
					int i = 0;
					getline(stlFile, currentLine);
					while(currentLine.find("endloop")==string::npos)
					{
						blank1 = currentLine.find("vertex") + 6;
						blank2 = currentLine.find(" ", blank1 + 1);
						blank3 = currentLine.find(" ", blank2 + 1);

						vertex[i][0] = atof(currentLine.substr(blank1+1, blank2-1).c_str());
						vertex[i][1] = atof(currentLine.substr(blank2+1, blank3-1).c_str());
						vertex[i][2] = atof(currentLine.substr(blank3+1).c_str());

						triAddr[i] = InsertVertexDB(vList, Vertex(vertex[i][0], vertex[i][1], vertex[i][2]));
						//vertexList.push_back(Vertex(vertex[i][0], vertex[i][1], vertex[i][2]));
						//vertexCount++;
						//cout<<vertex[i][0]<<" "<<vertex[i][1]<<" "<<vertex[i][2]<<endl;
						i++;
						getline(stlFile, currentLine);
					}

					Face f(triAddr[0], triAddr[1], triAddr[2]);
					fList.push_back(f);
					//faceList.push_back(Face(&vertexList[vertexCount-3], &vertexList[vertexCount-2], &vertexList[vertexCount-1]));
					//faceCount++;
					getline(stlFile, currentLine);
				}
				triangleNumber++;
			}
		}
	}

	else
	{
		cout<<"Error in opening STL File."<<endl;
	}

	PrintVertices(vList);
	PrintFaces(fList);

	return 0;
}*/

/*
int main()
{
	char filename[] = "femur-full.STL";
	ParseFile(filename, vList, fList, eList);
	PrintVertices(vList);
	PrintFaces(fList);
	PrintEdges(eList);
	cout<<vList.size()<<endl;
	cout<<fList.size()<<endl;
	return 0;
}
*/

int ParseFile(char *fp, list<Vertex> &vchain, list<Face> &fchain, list<Edge> &echain)
{
	string currentLine;
	size_t blank1;
	size_t blank2;
	size_t blank3;

	double normal[3];
	double vertex[3][3];
	Vertex* triAddr[3];

	ifstream stlFile(fp);
	if(stlFile.is_open())
	{
		while(stlFile.good())
		{
			getline(stlFile, currentLine);
			currentLine.erase(0, currentLine.find_first_not_of(" "));

			if(currentLine.find("facet")!=string::npos)
			{
				blank1 = currentLine.find("normal") + 6;
				blank2 = currentLine.find(" ", blank1 + 1);
				blank3 = currentLine.find(" ", blank2 + 1);

				normal[0] = atof(currentLine.substr(blank1+1, blank2-1).c_str());
				normal[1] = atof(currentLine.substr(blank2+1, blank3-1).c_str());
				normal[2] = atof(currentLine.substr(blank3+1).c_str());

				getline(stlFile, currentLine);
				if(currentLine.find("outer loop")!=string::npos)
				{
					int i = 0;
					int repeatCount[3];
					getline(stlFile, currentLine);
					while(currentLine.find("endloop")==string::npos)
					{
						blank1 = currentLine.find("vertex") + 6;
						blank2 = currentLine.find(" ", blank1 + 1);
						blank3 = currentLine.find(" ", blank2 + 1);

						vertex[i][0] = atof(currentLine.substr(blank1+1, blank2-1).c_str());
						vertex[i][1] = atof(currentLine.substr(blank2+1, blank3-1).c_str());
						vertex[i][2] = atof(currentLine.substr(blank3+1).c_str());

						int repeated = 0;
						triAddr[i] = InsertVertexDB(vchain, Vertex(vertex[i][0], vertex[i][1], vertex[i][2]), repeated);
						repeatCount[i] = repeated;
						i++;
						getline(stlFile, currentLine);
					}

					if(repeatCount[0] + repeatCount[1] + repeatCount[2] == 2)
					{
						//Insert only two edges in DB
						list<Edge>::iterator edgeit;
						if(!repeatCount[0])
						{
							Edge e3(triAddr[2], triAddr[0]);
							echain.push_back(e3);
							edgeit = echain.end();
							triAddr[2]->addConnectedEdge(&(*edgeit), 1);
							triAddr[0]->addConnectedEdge(&(*edgeit), -1);

							Edge e1(triAddr[0], triAddr[1]);
							echain.push_back(e1);
							edgeit = echain.end();
							triAddr[0]->addConnectedEdge(&(*edgeit), 1);
							triAddr[1]->addConnectedEdge(&(*edgeit), -1);
						}
						else if(!repeatCount[1])
						{
							Edge e1(triAddr[0], triAddr[1]);
							echain.push_back(e1);
							edgeit = echain.end();
							triAddr[0]->addConnectedEdge(&(*edgeit), 1);
							triAddr[1]->addConnectedEdge(&(*edgeit), -1);

							Edge e2(triAddr[1], triAddr[2]);
							echain.push_back(e2);
							edgeit = echain.end();
							triAddr[1]->addConnectedEdge(&(*edgeit), 1);
							triAddr[2]->addConnectedEdge(&(*edgeit), -1);
						}
						else if(!repeatCount[2])
						{
							Edge e2(triAddr[1], triAddr[2]);
							echain.push_back(e2);
							edgeit = echain.end();
							triAddr[1]->addConnectedEdge(&(*edgeit), 1);
							triAddr[2]->addConnectedEdge(&(*edgeit), -1);

							Edge e3(triAddr[2], triAddr[0]);
							echain.push_back(e3);
							edgeit = echain.end();
							triAddr[2]->addConnectedEdge(&(*edgeit), 1);
							triAddr[0]->addConnectedEdge(&(*edgeit), -1);
						}
					}
					else
					{
						//Insert all three edges in DB
						list<Edge>::iterator edgeit;

						Edge e1(triAddr[0], triAddr[1]);
						echain.push_back(e1);
						edgeit = echain.end();
						triAddr[0]->addConnectedEdge(&(*edgeit), 1);
						triAddr[1]->addConnectedEdge(&(*edgeit), -1);

						Edge e2(triAddr[1], triAddr[2]);
						echain.push_back(e2);
						edgeit = echain.end();
						triAddr[1]->addConnectedEdge(&(*edgeit), 1);
						triAddr[2]->addConnectedEdge(&(*edgeit), -1);

						Edge e3(triAddr[2], triAddr[0]);
						echain.push_back(e3);
						edgeit = echain.end();
						triAddr[2]->addConnectedEdge(&(*edgeit), 1);
						triAddr[0]->addConnectedEdge(&(*edgeit), -1);
					}

					//Insert face in DB
					Face f(triAddr[0], triAddr[1], triAddr[2]);
					fchain.push_back(f);
					getline(stlFile, currentLine);
				}
			}
		}

		list<Vertex>::iterator vertexit;
		for(vertexit = vchain.begin(); vertexit != vchain.end(); vertexit++)
		{
			addrList.push_back(&(*vertexit));
		}
	}

	else
	{
		cout<<"Error in opening STL File."<<endl;
		return -1;
	}

	return 0;
}

Vertex* InsertVertexDB(list<Vertex> &vchain, Vertex v, int &flag)
{
	list<Vertex>::iterator it;
	flag = 0;
	for(it = vchain.begin(); it != vchain.end(); it++)
	{
		if(v.x < (*it).x - 0.00001)
		{
			vchain.insert(it, v);
			--it;
			return &(*it);
			break;
		}
		else if(v.x > (*it).x + 0.00001)
		{
			continue;
		}
		else
		{
			if(v.y < (*it).y - 0.00001)
			{
				vchain.insert(it, v);
				--it;
				return &(*it);
				break;
			}
			else if(v.y > (*it).y + 0.00001)
			{
				continue;
			}
			else
			{
				if(v.z < (*it).z - 0.00001)
				{
					vchain.insert(it, v);
					--it;
					return &(*it);
					break;
				}
				else if(v.z > (*it).z + 0.00001)
				{
					continue;
				}
				else
				{
					flag = 1;
					return &(*it);
					break;
				}
			}
		}
	}

	it = vchain.end();
	vchain.insert(it, v);
	--it;
	return &(*it);
}

void PrintVertices(list<Vertex> &vchain)
{
	list<Vertex>::iterator it;
	for(it = vchain.begin(); it != vchain.end(); it++)
	{
		cout<<(*it).x<<" "<<(*it).y<<" "<<(*it).z<<endl;
	}
}

void PrintFaces(list<Face> &fchain)
{
	list<Face>::iterator it;
	for(it = fchain.begin(); it != fchain.end(); it++)
	{
		cout<<"Face: "<<endl;
		cout<<it->v1->x<<" "<<it->v1->y<<" "<<it->v1->z<<endl;
		cout<<it->v2->x<<" "<<it->v2->y<<" "<<it->v2->z<<endl;
		cout<<it->v3->x<<" "<<it->v3->y<<" "<<it->v3->z<<endl;

	}

}

void PrintEdges(list<Edge> &echain)
{
	list<Edge>::iterator it;
	for(it = echain.begin(); it != echain.end(); it++)
	{
		cout<<"Edge: "<<endl;
		cout<<it->v1->x<<" "<<it->v1->y<<" "<<it->v1->z<<endl;
		cout<<it->v2->x<<" "<<it->v2->y<<" "<<it->v2->z<<endl;
	}

}
