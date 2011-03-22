/*
 * ModelViewer.cpp
 *
 *  Created on: 14 Oct 2010
 *      Author: Ziggy
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>

#include "ModelViewer.h"

using namespace std;
int test;

ModelViewer::ModelViewer()
{
	sides = 3;
	setCoords();
	setTriangles();
	setEdges();
}
/**
 * Setting the coordinats neassesary to to create a unit cube
 */
void ModelViewer::setCoords()
{

		coordList.push_back(Vectormath::Aos::Vector3(-0.5,-0.5,-0.5));//0
		coordList.push_back(Vectormath::Aos::Vector3(-0.5,-0.5,0.5));//1
		coordList.push_back(Vectormath::Aos::Vector3(-0.5,0.5,-0.5));//2
		coordList.push_back(Vectormath::Aos::Vector3(-0.5,0.5,0.5));//3
		coordList.push_back(Vectormath::Aos::Vector3(0.5,-0.5,-0.5));//4
		coordList.push_back(Vectormath::Aos::Vector3(0.5,-0.5,0.5));//5
		coordList.push_back(Vectormath::Aos::Vector3(0.5,0.5,-0.5));//6
		coordList.push_back(Vectormath::Aos::Vector3(0.5,0.5,0.5));//7
}
/**
 * Setting the faces, each face contain 3 index numbers, these numbers represent the edges a single triangle contains.
 */
void ModelViewer::setTriangles()
{
	faces.push_back(face(4,1,5,0));//0
	faces.push_back(face(-5,2,3,0));//1
	faces.push_back(face(9,6,7,0));//2
	faces.push_back(face(8,-3,-9,0));//3
	faces.push_back(face(15,10,-6,0));//4
	faces.push_back(face(-2,14,-15,0));//5
	faces.push_back(face(18,-14,-1,0));//6
	faces.push_back(face(16,11,-18,0));//7
	faces.push_back(face(17,-4,-8,0));//8
	faces.push_back(face(12,-16,-17,0));//9
	faces.push_back(face(7,12,13,0));//10
	faces.push_back(face(11,10,-13,0));//11
}
/**
 * Setting up edges each edge contain 2 integers which is indexing the coordinates contained in the edge
 */
void ModelViewer::setEdges()
{
	edges.push_back(edge(0,0));//the empty edge, every edge need to have a positive index therefore edge 0 wil never be used
	edges.push_back(edge(0,4));//1
	edges.push_back(edge(4,6));//2
	edges.push_back(edge(6,2));//3
	edges.push_back(edge(2,0));//4
	edges.push_back(edge(4,2));//5
	edges.push_back(edge(6,7));//6
	edges.push_back(edge(7,3));//7
	edges.push_back(edge(3,2));//8
	edges.push_back(edge(3,6));//9
	edges.push_back(edge(5,7));//10
	edges.push_back(edge(1,5));//11
	edges.push_back(edge(3,1));//12
	edges.push_back(edge(1,7));//13
	edges.push_back(edge(4,5));//14
	edges.push_back(edge(6,5));//15
	edges.push_back(edge(0,1));//16
	edges.push_back(edge(3,0));//17
	edges.push_back(edge(0,5));//18

}
/**
 * Draw the model, this method can draw any mesh stored in face edge vertex
 */
void ModelViewer::draw()
{
	glPushMatrix();
	if(sides ==4)
	{
		glBegin(GL_QUADS);	// Drawing Using Triangles
		glColor3f(0.0,0.0,1.0);
		for(unsigned int j=0;j<faces.size();j++)
		{
				for(int i=0;i<4;i++)
				{
					if(faces[j].edge[i]>0) //if the edge is positive grab the first vertex in the edge
					{
						glVertex3f(coordList[edges[faces[j].edge[i]].start].getX(),
							coordList[edges[faces[j].edge[i]].start].getY(),
							coordList[edges[faces[j].edge[i]].start].getZ());
					}
					else // if the edge is negative grab the second vertex in the edge
					{
						glVertex3f(coordList[edges[faces[j].edge[i]*(-1)].stop].getX(),
							coordList[edges[faces[j].edge[i]*(-1)].stop].getY(),
							coordList[edges[faces[j].edge[i]*(-1)].stop].getZ());
					}
				}
		}
		glEnd();
	}
	else
	{
		glBegin(GL_TRIANGLES);	// Drawing Using Triangles
		glColor3f(0.0,0.0,1.0);
		for(unsigned int j=0;j<faces.size();j++)
		{
				for(int i=0;i<3;i++)
				{
					if(faces[j].edge[i]>0) //if the edge is positive grab the first vertex in the edge
					{
						glVertex3f(coordList[edges[faces[j].edge[i]].start].getX(),
							coordList[edges[faces[j].edge[i]].start].getY(),
							coordList[edges[faces[j].edge[i]].start].getZ());
					}
					else // if the edge is negative grab the second vertex in the edge
					{
						glVertex3f(coordList[edges[faces[j].edge[i]*(-1)].stop].getX(),
							coordList[edges[faces[j].edge[i]*(-1)].stop].getY(),
							coordList[edges[faces[j].edge[i]*(-1)].stop].getZ());
					}
				}
		}
		glEnd();
	}
	glPopMatrix();
	//drawHalfPoints();
	drawEdges();
}
/*
 * Draw the half half points, these are not stored so they will be calculated every frame.
 * For debugging
 */
void ModelViewer::drawHalfPoints()
{
	for(unsigned int i=1;i<edges.size();i++)
	{
		Vectormath::Aos::Vector3 halfPoint = findHalfPointUsingFace(i);
		glPushMatrix();
			glTranslatef(halfPoint.getX(),halfPoint.getY(),halfPoint.getZ());
			glColor3f(0.0,1.0,0.0);
			gluSphere(gluNewQuadric(),0.01,32,32);
			glPopMatrix();
	}
}
/*
 *Draw the edges in bright red for debugging
 */
void ModelViewer::drawEdges()
{
	glBegin(GL_LINES);
	for(unsigned int i =1;i<edges.size();i++)
	{
		glColor3f(1.0,1.0,1.0);
		glVertex3f(coordList[edges[i].start].getX(),coordList[edges[i].start].getY(),coordList[edges[i].start].getZ());
		glVertex3f(coordList[edges[i].stop].getX(),coordList[edges[i].stop].getY(),coordList[edges[i].stop].getZ());
	}
	glEnd();
}


/*
 * find half point without using the face information. This method is nearly working but it was to complicated to debug.
 * This method returns a vector pointing to the calculated half point using 8 control points
 */
Vectormath::Aos::Vector3 ModelViewer::findHalfPoint(unsigned int edge)
{
	unsigned int tmpArray[8];
	unsigned int j=0;
	unsigned int t=0;
	unsigned int s=0;
	Vectormath::Aos::Vector3 halfp =(coordList[edges[edge].start]/2)+(coordList[edges[edge].stop]/2);
	unsigned int mainPoints[2] = {edges[edge].start,edges[edge].stop};
	unsigned int secondPoint[2];
	secondPoint[0]=-1;
	unsigned int thirdPoint[4];

	//find all edges connected to the edge provided with the parameter

	for (unsigned int i = 1; i<edges.size(); i++)
		{
			if(!(i==edge))
			{
				if((edges[i].start == edges[edge].start)||(edges[i].start ==edges[edge].stop))
				{
					tmpArray[j]=edges[i].stop;
					j++;
				}
				else if((edges[i].stop == edges[edge].start)||(edges[i].stop ==edges[edge].stop))
				{
					tmpArray[j]=edges[i].start;

					j++;
				}
			}
		}

	//find the point which is duplicated, these are the secondary points
	for(unsigned int i = 0;i<j;i++)
	{
		for(unsigned int k=0;k<j;k++)
		{
			if(!(k==i))
			{
				if(tmpArray[k]==tmpArray[i])

				{
					if(tmpArray[i]!=secondPoint[0])
					{
						bool b= true;
						for(unsigned int z=0; z<s;z++)
						{
							if(secondPoint[z]==tmpArray[i])//makes sure to not to make duplicates
							{
								b=false;
							}
						}
						if(b)
						{
							secondPoint[s]=tmpArray[i];
							halfp+=(coordList[tmpArray[i]])/8;
							s++;
						}
					}
				}
			}
		}
	}

	//find the vertices which is connected to the main edge as well as the secondary vertices
	for(unsigned int i=0;i<j;i++)
	{
		if((tmpArray[i]!=mainPoints[0])&&(tmpArray[i]!=mainPoints[1])
				&&(tmpArray[i]!=secondPoint[0])&&(tmpArray[i]!=secondPoint[1]))
		{
			for(unsigned int k=1;k<edges.size();k++)
			{
				if(edges[k].start==tmpArray[i])
				{
					if((edges[k].stop==secondPoint[0])||(edges[k].stop==secondPoint[1]))
					{
							thirdPoint[t]=tmpArray[i];
							halfp-=(coordList[thirdPoint[t]])/16;
							t++;
					}
				}
				if(edges[k].stop==tmpArray[i])
				{
					if((edges[k].start==secondPoint[0])||(edges[k].start==secondPoint[1]))
					{
							thirdPoint[t]=tmpArray[i];
							halfp-=(coordList[thirdPoint[t]])/16;
							t++;
					}
				}
			}
		}
	}

	//cout<<mainPoints[0]<<mainPoints[1]<<secondPoint[0]<<secondPoint[1]<<"1:   "<<thirdPoint[0]<<"  2:    "<<thirdPoint[1]<<"   3:    "<<thirdPoint[2]<<"   4:    "<<thirdPoint[3]<<endl;
	return halfp;
}


/**
 * Method for finding the half points using the face information. This method
 * returns a vector pointing to the calculated half point using 8 control points
 */
Vectormath::Aos::Vector3 ModelViewer::findHalfPointUsingFace(unsigned int edge)
{
	Vectormath::Aos::Vector3 halfp =(coordList[edges[edge].start]/2)+(coordList[edges[edge].stop]/2);
	unsigned int faceCounter =0;//added faces to setFaces
	unsigned int edgeCounter=0;//added edges to newEdges
	unsigned int spCounter=0;//second point counter
	unsigned int tpCounter=0;
	unsigned int mainPoints[2] = {edges[edge].start,edges[edge].stop};
	unsigned int secondPoints[2];
	unsigned int thirdPoints[4];
	int newEdges[4];//To calculate the last vertices
	unsigned int setFaces[2]; // set of faces connected to the edge
	bool secondFound=false;//Second point in ace is found but continue to gather edges

	for(unsigned int i = 0;i<faces.size();i++)//loop finding the second set of control points
	{
		for(unsigned int j = 0; j<3;j++)
		{
			if(faces[i].edge[j]==edge||faces[i].edge[j]*-1==edge)
			{
				secondFound = false;//boolean to make sure that that the method does not add 2 of every control point
				setFaces[faceCounter]=i;//Store the 2 faces found for later use
				faceCounter++;
				for(int k = 0; k<3;k++)
				{
					if(faces[i].edge[k]!=edge&&faces[i].edge[k]*-1!=edge)
					{
						newEdges[edgeCounter]=toAbsolute(faces[i].edge[k]);// Save edges For later use
						if(edges[newEdges[edgeCounter]].start!=mainPoints[0]&&
								edges[newEdges[edgeCounter]].start!=mainPoints[1]&&!secondFound)
							 //If the current edge's start point is not equal to any of the initial control points
							 //then add the start point to the list of control points.
						{
							secondPoints[spCounter]=edges[newEdges[edgeCounter]].start;
							halfp+=coordList[secondPoints[spCounter]]/8;
							spCounter++;
							secondFound = true;
						}
						else if(edges[newEdges[edgeCounter]].stop!=mainPoints[0]&&
								edges[newEdges[edgeCounter]].stop!=mainPoints[1]&&!secondFound)
							 //If the current edge's stop point is not equal to any of the initial control points
							 //then add the stop point to the list of control points.
						{
							secondPoints[spCounter]=edges[newEdges[edgeCounter]].stop;
							halfp+=coordList[secondPoints[spCounter]]/8;
							spCounter++;
							secondFound = true;
						}
						edgeCounter++;
					}
				}
			}
		}
	}
	//finding the last 4 control points
	for(unsigned int i = 0;i<faces.size();i++)
	{
		if(i!=setFaces[0]&&i!=setFaces[1])
		{
			for(int k=0;k<4;k++)
			{
				for(int j = 0; j<3;j++)
				{
					if(faces[i].edge[j]==newEdges[k]||faces[i].edge[j]*-1==newEdges[k])
					{
						int checkEdge;//integer to test the next edge in the face found
						int edgeSame = toAbsolute(faces[i].edge[j]);//Edge that is common for face i and one of the initial faces
						if(j==2)
						{
							checkEdge=0;
						}
						else
						{
							checkEdge= j+1;
						}
						//the edge is positive
						if(faces[i].edge[checkEdge]>0)
						{
							//if the start point of the edge we are checking are not equal to any of the points
							//in the edge given from the first loop then add the start point to the control points
							if(edges[edgeSame].start!=edges[faces[i].edge[checkEdge]].start&&
									edges[edgeSame].stop!=edges[faces[i].edge[checkEdge]].start)
							{
								thirdPoints[tpCounter]=edges[faces[i].edge[checkEdge]].start;
								tpCounter++;
							}
							//if the first if sentence then add the stop point to control points
							else
							{
								thirdPoints[tpCounter]=edges[faces[i].edge[checkEdge]].stop;
								tpCounter++;
							}
						}
						//if the edge is negative
						else
						{
							//if the start point of the edge we are checking are not equal to any of the points
							//in the edge given from the first loop then add the stop point to the control points
							if(edges[edgeSame].start!=edges[faces[i].edge[checkEdge]*-1].stop&&
									edges[edgeSame].stop!=edges[faces[i].edge[checkEdge]*-1].stop)
							{
								thirdPoints[tpCounter]=edges[faces[i].edge[checkEdge]*-1].stop;
								tpCounter++;
							}
							//if the first if sentence then add the start point to control points
							else
							{
								thirdPoints[tpCounter]=edges[faces[i].edge[checkEdge]*-1].start;
								tpCounter++;
							}
						}

					}
				}
			}
		}
	}
	//cout<<mainPoints[0]<<mainPoints[1]<<secondPoints[0]<<secondPoints[1]<<"    1:   "<<thirdPoints[0]<<"    2:   "<<thirdPoints[1]<<"    3:   "<<thirdPoints[2]<<"    4:   "<<thirdPoints[3]<<endl;
	halfp = (coordList[mainPoints[0]] + coordList[mainPoints[1]])/2 + (coordList[secondPoints[0]] + coordList[secondPoints[1]])/8-
		(coordList[thirdPoints[0]] + coordList[thirdPoints[1]]+ coordList[thirdPoints[2]] + coordList[thirdPoints[3]])/16;
	return halfp;
}


/**
 * Method for subdividing the mesh, this method assumes that faces with positive edges is placed first in the
 * list of faces. The method will change the edge and face vector while adding coordinates to the coord list
 */
void ModelViewer::subDivide()
{
	vector<edge>tmp_edges;
	tmp_edges.push_back(edge(0,0));
	vector<face>tmp_faces;
	vector<int>edgesDone;
	vector<tmpInts>listConnection;// list connecting edges in the old edge list and in the temp edge list

	//Loop trough every face
	for(unsigned int i =0;i<faces.size();i++)//faces.size();i++)
	{
		int halfpoints[3];
		int startEdge = tmp_edges.size();
		int edgesInFace[9];
		int index =0; //for the temp int array describing the edges in the new faces
		int edgesCreated = 0;
		bool edgeUsed; //to not create duplicates

		int edgesUsed=0;
		for(int k=0;k<3;k++)
		{
			int current = faces[i].edge[k];
			edgesDone.push_back(current);
			if(current<0) // if negative
			{
				int workingEdge;
				for(unsigned int j = 0; j<listConnection.size();j++)
				{
					if(listConnection[j].prev==current*-1)//find the edge in the list connection
					{
						//add the two edges in a temporary list of edges contained in the new face
						workingEdge=listConnection[j].newv;
						edgesInFace[index]=-(workingEdge+1);
						edgesInFace[index+1]=-workingEdge;
						edgesUsed+=2;//so that the indexing of the list connection is still working
					}
				}
				halfpoints[k] = tmp_edges[workingEdge].stop;
			}
			else
			{
				int workingEdge;
				for(unsigned int j = 0; j<listConnection.size();j++)
				{
					if(listConnection[j].prev==current)
					{
						edgeUsed = true;
						workingEdge=listConnection[j].newv;
					}
					halfpoints[k] = tmp_edges[workingEdge].stop;
				}
				if(edgeUsed)
				{
					edgesInFace[index]=workingEdge;
					edgesInFace[index+1]=workingEdge+1;
					edgesUsed+=2;
					edgeUsed = false;
				}
				else
				{
					listConnection.push_back(tmpInts(current,startEdge+(2*k)-edgesUsed));//add to the temp list connecting the old and the new vector of edges
					Vectormath::Aos::Vector3 tmpVertex = findHalfPointUsingFace(current);//use the half point and create new edges
					unsigned int currentVertex = coordList.size();
					halfpoints[k]=currentVertex;
					coordList.push_back(tmpVertex);
					tmp_edges.push_back(edge(edges[current].start,currentVertex));
					tmp_edges.push_back(edge(currentVertex,edges[current].stop));
					edgesInFace[index]=startEdge+edgesCreated;
					edgesInFace[index+1]=startEdge+edgesCreated+1;
					edgesCreated+=2;
				}
			}
			index+=2;
		}

		// create the inner edges going for half point to half point
		tmp_edges.push_back(edge(halfpoints[0],halfpoints[1]));
		tmp_edges.push_back(edge(halfpoints[1],halfpoints[2]));
		tmp_edges.push_back(edge(halfpoints[2],halfpoints[0]));
		edgesInFace[6]=startEdge + edgesCreated;
		edgesInFace[7]=startEdge + edgesCreated+1;
		edgesInFace[8]=startEdge + edgesCreated+2;

		// is the temporary list of edges in this face to create 4 new faces.
		tmp_faces.push_back(face(edgesInFace[6], edgesInFace[7], edgesInFace[8],0));
		tmp_faces.push_back(face(edgesInFace[0],-edgesInFace[8], edgesInFace[5],0));
		tmp_faces.push_back(face(edgesInFace[1], edgesInFace[2],-edgesInFace[6],0));
		tmp_faces.push_back(face(edgesInFace[3], edgesInFace[4],-edgesInFace[7],0));
	}
	//replace the initial list of edges and faces with the new ones.
	edges.clear();
	faces.clear();
	edges=tmp_edges;
	faces= tmp_faces;
}


/**
 * Preform a catmull clark subdivision on the mesh. Replacing all the face, edge vertex arrays with new arrays.
 */
void ModelViewer::catmullClark()
{
	vector<Vectormath::Aos::Vector3> tmp_coordList;
	vector<edge> tmp_edges;
	tmp_edges.push_back(edge(0,0));//first edge need to be empty
	vector<face>tmp_faces;

	unsigned int indexMP=faces.size();//index to the first mid point of an edge in tmp_coordList

	//Loop to find face points.
	for(unsigned int i = 0; i <faces.size();i++)
	{
		Vectormath::Aos::Vector3 fp = Vectormath::Aos::Vector3(0.0,0.0,0.0);
		for(int j =0; j<sides;j++)
		{
			int currentEdge = faces[i].edge[j];
			if(currentEdge>0)
			{
				fp = fp+ coordList[edges[currentEdge].start];
			}
			else
			{
				fp = fp+coordList[edges[currentEdge*-1].stop];
			}
		}
		fp= fp/sides;
		tmp_coordList.push_back(fp);
		faces[i].facePoint = i;
	}

	//Loop to find the midpoints on an edge, found by taking the average of each end of the edge and
	//the face points adjacent to the edge
	for(unsigned int i=1;i<edges.size();i++)
	{
		Vectormath::Aos::Vector3 ep = (coordList[edges[i].start]+coordList[edges[i].stop])/4;
		for(unsigned int j = 0; j<faces.size();j++)
		{
			for(int k = 0; k<sides;k++)
			{
				if(faces[j].edge[k]==i||faces[j].edge[k]*-1==i)
				{
					ep+=tmp_coordList[faces[j].facePoint]/4;
					break;
				}
			}
		}
		edges[i].halfPoint = indexMP+i-1;
		tmp_coordList.push_back(ep);
	}

	//Find all the new vertices using this formula (Q+(2*R)+((n-3)*V))/n
	for(unsigned int i = 0; i<coordList.size();i++)
	{
		Vectormath::Aos::Vector3 R = Vectormath::Aos::Vector3(0.0f,0.0f,0.0f);
		Vectormath::Aos::Vector3 Q = Vectormath::Aos::Vector3(0.0f,0.0f,0.0f);
		vector<int> facesFound;
		vector<int> edgesFound;
		for(unsigned int j = 1; j<edges.size();j++)
		{
			if(edges[j].start==i|| edges[j].stop==i)
			{
				R+=tmp_coordList[edges[j].halfPoint];
				edgesFound.push_back(j);
			}
		}
		R=R/edgesFound.size();

		for(unsigned int k=0;k<faces.size();k++)
		{
			for(int l=0;l<sides;l++)
			{
				bool faceAlreadyFound = false;
				for(unsigned int j=0;j<edgesFound.size();j++)
				{
					if(faces[k].edge[l]==edgesFound[j]||faces[k].edge[l]*-1==edgesFound[j])
					{
						for(unsigned int m = 0;m<facesFound.size();m++)
						{
							if(facesFound[m]==k)
							{
								faceAlreadyFound = true;
							}
						}
						if(!faceAlreadyFound)
						{
							Q+= tmp_coordList[faces[k].facePoint];
							facesFound.push_back(k);
						}
					}
				}
			}
		}
		Q=Q/facesFound.size();
		int n = facesFound.size();
		tmp_coordList.push_back((Q+(2*R)+((n-3)*coordList[i]))/n);
	}


	vector<tmpInts>listConnection; //Array with 2 ints to save the connection
									//between the old edges and the new edge created from the old edges
	bool edgeUsed[4];
	int useEdge[4];

	//Loop to create the new edges and new faces.
	for(unsigned int i =0; i < faces.size();i++)
	{
		int edgesInFace[12];
		int index = 0;
		unsigned int vertices[4];
		unsigned int startEdge = tmp_edges.size(); //First Edge
		for(int k =0; k<sides;k++)
		{
			if(faces[i].edge[k]>0)
			{
				vertices[k]=edges.size()+faces.size()+edges[faces[i].edge[k]].start-1;
			}
			else
			{
				vertices[k]=edges.size()+faces.size()+edges[faces[i].edge[k]*-1].stop-1;
			}
			for(unsigned int j = 0; j<listConnection.size();j++)
			{
				if(listConnection[j].prev==faces[i].edge[k]||listConnection[j].prev==faces[i].edge[k]*-1)
				{
					edgeUsed[k]=true;
					useEdge[k]=listConnection[j].newv;
					break;
				}
				else
				{
					edgeUsed[k]=false;
				}
			}
		}
		for( int k = 0;k<sides;k++)
		{
			int nextVertex;
			if(k==sides-1)
			{
				nextVertex = 0;
			}
			else
			{
				nextVertex = k+1;
			}
			if(!edgeUsed[k])
			{
				edgesInFace[index]=tmp_edges.size();
				edgesInFace[index+1]=tmp_edges.size()+1;
				listConnection.push_back(tmpInts(faces[i].edge[k],tmp_edges.size()));
				tmp_edges.push_back(edge(vertices[k],edges[toAbsolute(faces[i].edge[k])].halfPoint));
				tmp_edges.push_back(edge(edges[toAbsolute(faces[i].edge[k])].halfPoint,vertices[nextVertex]));
				index+=2;
			}
			else
			{
				if(faces[i].edge[k]>0)
				{
					edgesInFace[index]=useEdge[k];
					edgesInFace[index+1]=useEdge[k]+1;
					index+=2;
				}
				else
				{
					edgesInFace[index+1]=-useEdge[k];
					edgesInFace[index]=-(useEdge[k]+1);
					index+=2;
				}
			}
			edgesInFace[index]=tmp_edges.size();
			if(!(k==sides-1)) // So that the new mesh always use positive edges before negative edges.
			{
				tmp_edges.push_back(edge(edges[toAbsolute(faces[i].edge[k])].halfPoint,faces[i].facePoint));
			}
			else
			{
				tmp_edges.push_back(edge(faces[i].facePoint,edges[toAbsolute(faces[i].edge[k])].halfPoint));
			}
			index++;
		}
		//Creating the new faces
		if(sides == 3) //traingle
		{
			tmp_faces.push_back(face(edgesInFace[0],edgesInFace[2],edgesInFace[8],edgesInFace[7]));
			tmp_faces.push_back(face(edgesInFace[1],edgesInFace[3],edgesInFace[5],-edgesInFace[2]));
			tmp_faces.push_back(face(-edgesInFace[8],-edgesInFace[5],edgesInFace[4],edgesInFace[6]));
		}
		else//quad
		{
			tmp_faces.push_back(face(edgesInFace[0],edgesInFace[2],edgesInFace[11],edgesInFace[10]));
			tmp_faces.push_back(face(edgesInFace[1],edgesInFace[3],edgesInFace[5],-edgesInFace[2]));
			tmp_faces.push_back(face(edgesInFace[4],edgesInFace[6],edgesInFace[8],-edgesInFace[5]));
			tmp_faces.push_back(face(edgesInFace[7],edgesInFace[9],-edgesInFace[11],-edgesInFace[8]));
		}
	}

	edges.clear();
	faces.clear();
	coordList.clear();
	coordList=tmp_coordList;
	edges=tmp_edges;
	faces= tmp_faces;
	sides=4;
}


/**
 * reset all the vectors with information so that the mesh returns to its initial shape
 */
void ModelViewer::reset()
{
	edges.clear();
	faces.clear();
	coordList.clear();

	setCoords();
	setTriangles();
	setEdges();
	sides=3;
}

/**
 * take any int and returns the absolute value of that int
 */
int ModelViewer::toAbsolute(int x)
{
	if(x<0)
	{
		return x*-1;
	}
	return x;
}
