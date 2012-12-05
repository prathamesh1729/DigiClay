/*
 * Object.cpp
 *
 *  Created on: Sep 17, 2012
 *      Author: prathamesh
 */

#include "Object.h"

Object::Object()
{

}

Object::~Object()
{

}

Vertex* Object::InsertVertexDB(list<Vertex> &vchain, Vertex v, int &flag)
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
				else if(v.z > (*it).z + 0.000001)
				{
					continue;
				}
				else
				{
					flag = 1;
					cout<<"Hit!"<<endl;
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

Edge* Object::InsertEdgeDB(list<Edge> &echain, Vertex *v1, Vertex *v2)
{
	list<Edge>::iterator localEdgeIt;
	Edge tempEdge(v1, v2);
	echain.push_back(tempEdge);
	localEdgeIt = echain.end();
	--localEdgeIt;
	v1->addConnectedEdge(&(*localEdgeIt), 1);
	v2->addConnectedEdge(&(*localEdgeIt), -1);
	return &(*localEdgeIt);
}

int Object::ParseFile(char *fp, list<Vertex> &vchain, list<Face> &fchain, list<Edge> &echain)
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
					Face f(triAddr[0], triAddr[1], triAddr[2], normal);
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

int Object::NewParseFile(char *fp, list<Vertex> &vchain, list<Face> &fchain, list<Edge> &echain)
{
	string currentLine;
	size_t blank1;
	size_t blank2;
	size_t blank3;
	size_t newline;

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
				currentLine.erase(0, blank1);
				currentLine.erase(0, currentLine.find_first_not_of(" "));

				blank2 = currentLine.find_first_of(" ");
				normal[0] = atof(currentLine.substr(0, blank2).c_str());
				currentLine.erase(0, blank2);
				currentLine.erase(0, currentLine.find_first_not_of(" "));

				blank3 = currentLine.find_first_of(" ");
				normal[1] = atof(currentLine.substr(0, blank3).c_str());
				currentLine.erase(0, blank3);
				currentLine.erase(0, currentLine.find_first_not_of(" "));

				newline = currentLine.find_first_of("\n");
				normal[2] = atof(currentLine.substr(0).c_str());

				getline(stlFile, currentLine);
				if(currentLine.find("outer loop")!=string::npos)
				{
					int i = 0;
					int repeatCount[3];
					getline(stlFile, currentLine);
					while(currentLine.find("endloop")==string::npos)
					{
						blank1 = currentLine.find("vertex") + 6;
						currentLine.erase(0, blank1);
						currentLine.erase(0, currentLine.find_first_not_of(" "));

						blank2 = currentLine.find_first_of(" ");
						vertex[i][0] = atof(currentLine.substr(0, blank2).c_str());
						currentLine.erase(0, blank2);
						currentLine.erase(0, currentLine.find_first_not_of(" "));

						blank3 = currentLine.find_first_of(" ");
						vertex[i][1] = atof(currentLine.substr(0, blank3).c_str());
						currentLine.erase(0, blank3);
						currentLine.erase(0, currentLine.find_first_not_of(" "));

						newline = currentLine.find_first_of("\n");
						vertex[i][2] = atof(currentLine.substr(0).c_str());

						int repeated = 0;
						triAddr[i] = InsertVertexDB(vchain, Vertex(vertex[i][0], vertex[i][1], vertex[i][2]), repeated);
						repeatCount[i] = repeated;
						i++;
						getline(stlFile, currentLine);
					}

					cout<<"Repeat Count: "<< (repeatCount[0] + repeatCount[1] + repeatCount[2]) << endl;
					if((repeatCount[0] + repeatCount[1] + repeatCount[2]) == 2)
					{
						//Insert only two or three edges in DB
						list<Edge>::iterator edgeit;
						bool putThatEdge = true;

						if(!repeatCount[0])
						{
							for(uint cei = 0; cei < triAddr[1]->connectedEdges.size(); cei++)
							{
								/*
								if(triAddr[1]->connectedEdges[i].second == 1)
								{
									if((triAddr[2] == triAddr[1]->connectedEdges[cei].first->v2))
									{
										putThatEdge = false;
									}
								}
								else if(triAddr[1]->connectedEdges[cei].second == -1)
								{
									if((triAddr[2] == triAddr[1]->connectedEdges[i].first->v1))
									{
										putThatEdge = false;
									}
								}
								*/
								if((triAddr[2] == triAddr[1]->connectedEdges[cei].first->v1) || (triAddr[2] == triAddr[1]->connectedEdges[cei].first->v2))
								{
									putThatEdge = false;
									break;
								}
							}

							if(putThatEdge)
							{
								Edge es(triAddr[1], triAddr[2]);
								echain.push_back(es);
								edgeit = echain.end();
								--edgeit;
								triAddr[1]->addConnectedEdge(&(*edgeit), 1);
								triAddr[2]->addConnectedEdge(&(*edgeit), -1);
							}

							Edge e3(triAddr[2], triAddr[0]);
							echain.push_back(e3);
							edgeit = echain.end();
							--edgeit;
							triAddr[2]->addConnectedEdge(&(*edgeit), 1);
							triAddr[0]->addConnectedEdge(&(*edgeit), -1);

							Edge e1(triAddr[0], triAddr[1]);
							echain.push_back(e1);
							edgeit = echain.end();
							--edgeit;
							triAddr[0]->addConnectedEdge(&(*edgeit), 1);
							triAddr[1]->addConnectedEdge(&(*edgeit), -1);
						}
						else if(!repeatCount[1])
						{
							for(uint cei = 0; cei < triAddr[2]->connectedEdges.size(); cei++)
							{
								if((triAddr[0] == triAddr[2]->connectedEdges[cei].first->v1) || (triAddr[0] == triAddr[2]->connectedEdges[cei].first->v2))
								{
									putThatEdge = false;
									break;
								}
							}

							if(putThatEdge)
							{
								Edge es(triAddr[2], triAddr[0]);
								echain.push_back(es);
								edgeit = echain.end();
								--edgeit;
								triAddr[2]->addConnectedEdge(&(*edgeit), 1);
								triAddr[0]->addConnectedEdge(&(*edgeit), -1);
							}

							Edge e1(triAddr[0], triAddr[1]);
							echain.push_back(e1);
							edgeit = echain.end();
							--edgeit;
							triAddr[0]->addConnectedEdge(&(*edgeit), 1);
							triAddr[1]->addConnectedEdge(&(*edgeit), -1);

							Edge e2(triAddr[1], triAddr[2]);
							echain.push_back(e2);
							edgeit = echain.end();
							--edgeit;
							triAddr[1]->addConnectedEdge(&(*edgeit), 1);
							triAddr[2]->addConnectedEdge(&(*edgeit), -1);
						}
						else if(!repeatCount[2])
						{
							for(uint cei = 0; cei < triAddr[0]->connectedEdges.size(); cei++)
							{
								if((triAddr[1] == triAddr[0]->connectedEdges[cei].first->v1) || (triAddr[1] == triAddr[0]->connectedEdges[cei].first->v2))
								{
									putThatEdge = false;
									break;
								}
							}

							if(putThatEdge)
							{
								Edge es(triAddr[0], triAddr[1]);
								echain.push_back(es);
								edgeit = echain.end();
								--edgeit;
								triAddr[0]->addConnectedEdge(&(*edgeit), 1);
								triAddr[1]->addConnectedEdge(&(*edgeit), -1);
							}

							Edge e2(triAddr[1], triAddr[2]);
							echain.push_back(e2);
							edgeit = echain.end();
							--edgeit;
							triAddr[1]->addConnectedEdge(&(*edgeit), 1);
							triAddr[2]->addConnectedEdge(&(*edgeit), -1);

							Edge e3(triAddr[2], triAddr[0]);
							echain.push_back(e3);
							edgeit = echain.end();
							--edgeit;
							triAddr[2]->addConnectedEdge(&(*edgeit), 1);
							triAddr[0]->addConnectedEdge(&(*edgeit), -1);
						}
					}
					else if((repeatCount[0] + repeatCount[1] + repeatCount[2]) <= 1)
					{
						//Insert all three edges in DB
						list<Edge>::iterator edgeit;

						Edge e1(triAddr[0], triAddr[1]);
						echain.push_back(e1);
						edgeit = echain.end();
						--edgeit;
						triAddr[0]->addConnectedEdge(&(*edgeit), 1);
						triAddr[1]->addConnectedEdge(&(*edgeit), -1);

						Edge e2(triAddr[1], triAddr[2]);
						echain.push_back(e2);
						edgeit = echain.end();
						--edgeit;
						triAddr[1]->addConnectedEdge(&(*edgeit), 1);
						triAddr[2]->addConnectedEdge(&(*edgeit), -1);

						Edge e3(triAddr[2], triAddr[0]);
						echain.push_back(e3);
						edgeit = echain.end();
						--edgeit;
						triAddr[2]->addConnectedEdge(&(*edgeit), 1);
						triAddr[0]->addConnectedEdge(&(*edgeit), -1);
					}
					else if((repeatCount[0] + repeatCount[1] + repeatCount[2]) == 3)
					{
						list<Edge>::iterator edgeit;
						//Zero, one, two or three edges may have to be inserted in DB.
						bool insertEdge01 = true;
						bool insertEdge12 = true;
						bool insertEdge20 = true;

						for(uint cei = 0; cei < triAddr[0]->connectedEdges.size(); cei++)
						{
							if((triAddr[1] == triAddr[0]->connectedEdges[cei].first->v1) || (triAddr[1] == triAddr[0]->connectedEdges[cei].first->v2))
							{
								insertEdge01 = false;
								break;
							}
						}

						for(uint cei = 0; cei < triAddr[1]->connectedEdges.size(); cei++)
						{
							if((triAddr[2] == triAddr[1]->connectedEdges[cei].first->v1) || (triAddr[2] == triAddr[1]->connectedEdges[cei].first->v2))
							{
								insertEdge12 = false;
								break;
							}
						}

						for(uint cei = 0; cei < triAddr[2]->connectedEdges.size(); cei++)
						{
							if((triAddr[0] == triAddr[2]->connectedEdges[cei].first->v1) || (triAddr[0] == triAddr[2]->connectedEdges[cei].first->v2))
							{
								insertEdge20 = false;
								break;
							}
						}

						if(insertEdge01)
						{
							Edge e1(triAddr[0], triAddr[1]);
							echain.push_back(e1);
							edgeit = echain.end();
							--edgeit;
							triAddr[0]->addConnectedEdge(&(*edgeit), 1);
							triAddr[1]->addConnectedEdge(&(*edgeit), -1);
						}

						if(insertEdge12)
						{
							Edge e2(triAddr[1], triAddr[2]);
							echain.push_back(e2);
							edgeit = echain.end();
							--edgeit;
							triAddr[1]->addConnectedEdge(&(*edgeit), 1);
							triAddr[2]->addConnectedEdge(&(*edgeit), -1);
						}

						if(insertEdge20)
						{
							Edge e3(triAddr[2], triAddr[0]);
							echain.push_back(e3);
							edgeit = echain.end();
							--edgeit;
							triAddr[2]->addConnectedEdge(&(*edgeit), 1);
							triAddr[0]->addConnectedEdge(&(*edgeit), -1);
						}
					}

					//Insert face in DB
					Face f(triAddr[0], triAddr[1], triAddr[2], normal);
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

		cout<<"Completed parsing file."<<endl;
	}

	else
	{
		cout<<"Error in opening STL File."<<endl;
		return -1;
	}

	return 0;
}

int Object::CompactParseFile(char *fp, list<Vertex> &vchain, list<Face> &fchain, list<Edge> &echain)
{
	string currentLine;
	size_t blank1;
	size_t blank2;
	size_t blank3;
	size_t newline;

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
				currentLine.erase(0, blank1);
				currentLine.erase(0, currentLine.find_first_not_of(" "));

				blank2 = currentLine.find_first_of(" ");
				normal[0] = atof(currentLine.substr(0, blank2).c_str());
				currentLine.erase(0, blank2);
				currentLine.erase(0, currentLine.find_first_not_of(" "));

				blank3 = currentLine.find_first_of(" ");
				normal[1] = atof(currentLine.substr(0, blank3).c_str());
				currentLine.erase(0, blank3);
				currentLine.erase(0, currentLine.find_first_not_of(" "));

				newline = currentLine.find_first_of("\n");
				normal[2] = atof(currentLine.substr(0).c_str());

				getline(stlFile, currentLine);
				if(currentLine.find("outer loop")!=string::npos)
				{
					int i = 0;
					int repeatCount[3];
					getline(stlFile, currentLine);
					while(currentLine.find("endloop")==string::npos)
					{
						blank1 = currentLine.find("vertex") + 6;
						currentLine.erase(0, blank1);
						currentLine.erase(0, currentLine.find_first_not_of(" "));

						blank2 = currentLine.find_first_of(" ");
						vertex[i][0] = atof(currentLine.substr(0, blank2).c_str());
						currentLine.erase(0, blank2);
						currentLine.erase(0, currentLine.find_first_not_of(" "));

						blank3 = currentLine.find_first_of(" ");
						vertex[i][1] = atof(currentLine.substr(0, blank3).c_str());
						currentLine.erase(0, blank3);
						currentLine.erase(0, currentLine.find_first_not_of(" "));

						newline = currentLine.find_first_of("\n");
						vertex[i][2] = atof(currentLine.substr(0).c_str());

						int repeated = 0;
						triAddr[i] = InsertVertexDB(vchain, Vertex(vertex[i][0], vertex[i][1], vertex[i][2]), repeated);
						repeatCount[i] = repeated;
						i++;
						getline(stlFile, currentLine);
					}

					cout<<"Repeat Count: "<< (repeatCount[0] + repeatCount[1] + repeatCount[2]) << endl;

					//Insert face in DB
					Face f(triAddr[0], triAddr[1], triAddr[2], normal);
					fchain.push_back(f);

					if((repeatCount[0] + repeatCount[1] + repeatCount[2]) <= 1)
					{
						//Insert all three edges in DB
						InsertEdgeDB(echain, triAddr[0], triAddr[1]);
						(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
						InsertEdgeDB(echain, triAddr[1], triAddr[2]);
						(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
						InsertEdgeDB(echain, triAddr[2], triAddr[0]);
						(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
					}
					else if((repeatCount[0] + repeatCount[1] + repeatCount[2]) == 2)
					{
						//Insert either two or three edges in DB
						list<Edge>::iterator edgeit;
						bool putThatEdge = true;
						unsigned int repeatedEdgeIndex;

						if(!repeatCount[0])
						{
							for(uint cei = 0; cei < triAddr[1]->connectedEdges.size(); cei++)
							{
								if((triAddr[2] == triAddr[1]->connectedEdges[cei].first->v1) || (triAddr[2] == triAddr[1]->connectedEdges[cei].first->v2))
								{
									putThatEdge = false;
									repeatedEdgeIndex = cei;
									break;
								}
							}

							if(putThatEdge)
							{
								InsertEdgeDB(echain, triAddr[1], triAddr[2]);
								(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
							}
							else
							{
								if(triAddr[1]->connectedEdges[repeatedEdgeIndex].first->connectedFaces.size() < 2)
									triAddr[1]->connectedEdges[repeatedEdgeIndex].first->addConnectedFace(&(*(--(fchain.end()))));
								cout<<"Connected Face size: "<<triAddr[1]->connectedEdges[repeatedEdgeIndex].first->connectedFaces.size()<<endl;
							}

							InsertEdgeDB(echain, triAddr[0], triAddr[1]);
							(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
							InsertEdgeDB(echain, triAddr[2], triAddr[0]);
							(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
						}

						else if(!repeatCount[1])
						{
							for(uint cei = 0; cei < triAddr[2]->connectedEdges.size(); cei++)
							{
								if((triAddr[0] == triAddr[2]->connectedEdges[cei].first->v1) || (triAddr[0] == triAddr[2]->connectedEdges[cei].first->v2))
								{
									putThatEdge = false;
									repeatedEdgeIndex = cei;
									break;
								}
							}

							if(putThatEdge)
							{
								InsertEdgeDB(echain, triAddr[2], triAddr[0]);
								(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
							}
							else
							{
								if(triAddr[2]->connectedEdges[repeatedEdgeIndex].first->connectedFaces.size() < 2)
									triAddr[2]->connectedEdges[repeatedEdgeIndex].first->addConnectedFace(&(*(--(fchain.end()))));
								cout<<"Connected Face size: "<<triAddr[2]->connectedEdges[repeatedEdgeIndex].first->connectedFaces.size()<<endl;
							}

							InsertEdgeDB(echain, triAddr[0], triAddr[1]);
							(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
							InsertEdgeDB(echain, triAddr[1], triAddr[2]);
							(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
						}

						else if(!repeatCount[2])
						{
							for(uint cei = 0; cei < triAddr[0]->connectedEdges.size(); cei++)
							{
								if((triAddr[1] == triAddr[0]->connectedEdges[cei].first->v1) || (triAddr[1] == triAddr[0]->connectedEdges[cei].first->v2))
								{
									putThatEdge = false;
									repeatedEdgeIndex = cei;
									break;
								}
							}

							if(putThatEdge)
							{
								InsertEdgeDB(echain, triAddr[0], triAddr[1]);
								(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
							}
							else
							{
								if(triAddr[0]->connectedEdges[repeatedEdgeIndex].first->connectedFaces.size() < 2)
									triAddr[0]->connectedEdges[repeatedEdgeIndex].first->addConnectedFace(&(*(--(fchain.end()))));
								cout<<"Connected Face size: "<<triAddr[0]->connectedEdges[repeatedEdgeIndex].first->connectedFaces.size()<<endl;
							}

							InsertEdgeDB(echain, triAddr[1], triAddr[2]);
							(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
							InsertEdgeDB(echain, triAddr[2], triAddr[0]);
							(--(echain.end()))->addConnectedFace(&(*(--(fchain.end()))));
						}
					}
					else if((repeatCount[0] + repeatCount[1] + repeatCount[2]) == 3)
					{
						//Zero, one, two or three edges may have to be inserted in DB.
						bool insertEdge[3] = {true, true, true};
						unsigned int repeatedEdge[3];

						for(int v = 0; v < 3; v++)
						{
							for(uint cei = 0; cei < triAddr[v]->connectedEdges.size(); cei++)
							{
								if((triAddr[(v+1)%3] == triAddr[v]->connectedEdges[cei].first->v1) || (triAddr[(v+1)%3] == triAddr[v]->connectedEdges[cei].first->v2))
								{
									insertEdge[v] = false;
									repeatedEdge[v] = cei;
									break;
								}
							}
							if(insertEdge[v])
							{
								InsertEdgeDB(echain, triAddr[v], triAddr[(v+1)%3]);
								(--(echain.end()))->addConnectedFace(&(*(fchain.end())));
							}
							else
							{
								if(triAddr[v]->connectedEdges[repeatedEdge[v]].first->connectedFaces.size() < 2)
									triAddr[v]->connectedEdges[repeatedEdge[v]].first->addConnectedFace(&(*(--(fchain.end()))));
								cout<<"Connected Face size: "<<triAddr[v]->connectedEdges[repeatedEdge[v]].first->connectedFaces.size()<<endl;
							}
						}
					}

					getline(stlFile, currentLine);
				}
			}
		}

		list<Vertex>::iterator vertexit;
		for(vertexit = vchain.begin(); vertexit != vchain.end(); vertexit++)
		{
			addrList.push_back(&(*vertexit));
		}

		cout<<"Completed parsing file."<<endl;
	}

	else
	{
		cout<<"Error in opening STL File."<<endl;
		return -1;
	}

	return 0;
}

void Object::ComputeBoundingBox(double *bBox)
{
	bBox[0] = vertexList.begin()->x;
	bBox[1] = vertexList.begin()->y;
	bBox[2] = vertexList.begin()->z;
	bBox[3] = vertexList.end()->x;
	bBox[4] = vertexList.end()->y;
	bBox[5] = vertexList.end()->z;
}

void Object::PrintVertices(list<Vertex> &vchain)
{
	list<Vertex>::iterator it;
	for(it = vchain.begin(); it != vchain.end(); it++)
	{
		cout<<"Vertex: "<<(*it).x<<" "<<(*it).y<<" "<<(*it).z<<endl;
		cout<<"Total Force: "<<(*it).totalForce[0]<<" "<<(*it).totalForce[1]<<" "<<(*it).totalForce[2]<<endl;
		cout<<"External Force: "<<(*it).externalForce[0]<<" "<<(*it).externalForce[1]<<" "<<(*it).externalForce[2]<<endl;
	}
}

void Object::PrintFaces(list<Face> &fchain)
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

void Object::PrintEdges(list<Edge> &echain)
{
	list<Edge>::iterator it;
	for(it = echain.begin(); it != echain.end(); it++)
	{
		cout<<"Edge: "<<endl;
		cout<<it->v1->x<<" "<<it->v1->y<<" "<<it->v1->z<<endl;
		cout<<it->v2->x<<" "<<it->v2->y<<" "<<it->v2->z<<endl;
		cout<<"Connected Faces: "<<it->connectedFaces.size()<<endl;
		for(unsigned int k = 0; k < it->connectedFaces.size(); k++)
		{
			cout<<"Facearea: "<<it->connectedFaces[k]->faceArea<<endl;
		}
	}

}

void Object::UpdateAll(void)
{
	// Update edge lengths
	// Update edge forces
	list<Edge>::iterator ite;
	for(ite = edgeList.begin(); ite != edgeList.end(); ite++)
	{
		ite->computeSpringStiffness();
		ite->computeSpringForce();
	}

	// Update total forces
	// Update coordinates
	list<Vertex>::iterator itv;
	for(itv = vertexList.begin(); itv != vertexList.end(); itv++)
	{
		itv->computeTotalForce();
		itv->computeNew();
	}
	PrintVertices(vertexList);
}

int Object::ConstrainVertex(list<Vertex> &vchain, Vertex v)
{
	list<Vertex>::iterator it;
	for(it = vchain.begin(); it != vchain.end(); it++)
	{
		if(v.x < (*it).x - 0.00001)
		{
			continue;
		}
		else if(v.x > (*it).x + 0.00001)
		{
			continue;
		}
		else
		{
			if(v.y < (*it).y - 0.00001)
			{
				continue;
			}
			else if(v.y > (*it).y + 0.00001)
			{
				continue;
			}
			else
			{
				if(v.z < (*it).z - 0.00001)
				{
					continue;
				}
				else if(v.z > (*it).z + 0.00001)
				{
					continue;
				}
				else
				{
					(*it).constrained = true;
					return 1;
				}
			}
		}
	}

	return 0;
}

int Object::ApplyExternalForce(list<Vertex> &vchain, Vertex v, double *extForce)
{
	list<Vertex>::iterator it;
	for(it = vchain.begin(); it != vchain.end(); it++)
	{
		if(v.x < (*it).x - 0.00001)
		{
			continue;
		}
		else if(v.x > (*it).x + 0.00001)
		{
			continue;
		}
		else
		{
			if(v.y < (*it).y - 0.00001)
			{
				continue;
			}
			else if(v.y > (*it).y + 0.00001)
			{
				continue;
			}
			else
			{
				if(v.z < (*it).z - 0.00001)
				{
					continue;
				}
				else if(v.z > (*it).z + 0.00001)
				{
					continue;
				}
				else
				{
					(*it).externalForce[0] = extForce[0];
					(*it).externalForce[1] = extForce[1];
					(*it).externalForce[2] = extForce[2];
					return 1;
				}
			}
		}
	}

	return 0;
}
